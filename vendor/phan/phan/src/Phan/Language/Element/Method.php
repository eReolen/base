<?php declare(strict_types=1);

namespace Phan\Language\Element;

// Note: This file uses both class Phan\Language\Element\Flags and namespace ast\flags
use ast;
use ast\Node;
use Phan\Analysis\Analyzable;
use Phan\AST\UnionTypeVisitor;
use Phan\CodeBase;
use Phan\Config;
use Phan\Exception\CodeBaseException;
use Phan\Language\Context;
use Phan\Language\FQSEN\FullyQualifiedMethodName;
use Phan\Language\Scope\FunctionLikeScope;
use Phan\Language\Type\GenericArrayType;
use Phan\Language\UnionType;
use Phan\Memoize;

/**
 * Phan's representation of a class's method.
 *
 * @phan-file-suppress PhanPartialTypeMismatchArgument
 */
class Method extends ClassElement implements FunctionInterface
{
    use Analyzable;
    use Memoize;
    use FunctionTrait;
    use ClosedScopeElement;

    /**
     * @var ?FullyQualifiedMethodName If this was originally defined in a trait, this is the trait's defining fqsen.
     * This is tracked separately from getDefiningFQSEN() in order to not break access checks on protected/private methods.
     * Used for dead code detection.
     */
    private $real_defining_fqsen;

    /**
     * @param Context $context
     * The context in which the structural element lives
     *
     * @param string $name
     * The name of the typed structural element
     *
     * @param UnionType $type
     * A '|' delimited set of types satisfied by this
     * typed structural element.
     *
     * @param int $flags
     * The flags property contains node specific flags. It is
     * always defined, but for most nodes it is always zero.
     * ast\kind_uses_flags() can be used to determine whether
     * a certain kind has a meaningful flags value.
     *
     * @param FullyQualifiedMethodName $fqsen
     * A fully qualified name for the element
     *
     * @param ?array<int,Parameter> $parameter_list
     * A list of parameters to set on this method
     */
    public function __construct(
        Context $context,
        string $name,
        UnionType $type,
        int $flags,
        FullyQualifiedMethodName $fqsen,
        $parameter_list
    ) {
        $internal_scope = new FunctionLikeScope(
            $context->getScope(),
            $fqsen
        );
        $context = $context->withScope($internal_scope);
        if ($type->hasTemplateType()) {
            $this->recordHasTemplateType();
        }
        parent::__construct(
            $context,
            FullyQualifiedMethodName::canonicalName($name),
            $type,
            $flags,
            $fqsen
        );

        // Presume that this is the original definition
        // of this method, and let it be overwritten
        // if it isn't.
        $this->setDefiningFQSEN($fqsen);
        $this->real_defining_fqsen = $fqsen;

        // Record the FQSEN of this method (With the current Clazz),
        // to prevent recursing from a method into itself in non-quick mode.
        $this->setInternalScope($internal_scope);

        if ($parameter_list !== null) {
            $this->setParameterList($parameter_list);
        }
        $this->checkForTemplateTypes();
    }

    /**
     * Sets hasTemplateType to true if it finds any template types in the parameters or methods
     * @return void
     */
    public function checkForTemplateTypes()
    {
        if ($this->getUnionType()->hasTemplateTypeRecursive()) {
            $this->recordHasTemplateType();
            return;
        }
        foreach ($this->parameter_list as $parameter) {
            if ($parameter->getUnionType()->hasTemplateTypeRecursive()) {
                $this->recordHasTemplateType();
                return;
            }
        }
    }

    /**
     * @return bool
     * True if this is a magic phpdoc method (declared via (at)method on class declaration phpdoc)
     */
    public function isFromPHPDoc() : bool
    {
        return $this->getPhanFlagsHasState(Flags::IS_FROM_PHPDOC);
    }

    /**
     * Sets whether this is a magic phpdoc method (declared via (at)method on class declaration phpdoc)
     * @param bool $from_phpdoc - True if this is a magic phpdoc method
     * @return void
     */
    public function setIsFromPHPDoc(bool $from_phpdoc)
    {
        $this->setPhanFlags(
            Flags::bitVectorWithState(
                $this->getPhanFlags(),
                Flags::IS_FROM_PHPDOC,
                $from_phpdoc
            )
        );
    }

    /**
     * @return bool
     * True if this method is intended to be an override of another method (contains (at)override)
     */
    public function isOverrideIntended() : bool
    {
        return $this->getPhanFlagsHasState(Flags::IS_OVERRIDE_INTENDED);
    }

    /**
     * Sets whether this method is intended to be an override of another method (contains (at)override)
     * @param bool $is_override_intended

     * @return void
     */
    public function setIsOverrideIntended(bool $is_override_intended)
    {
        $this->setPhanFlags(
            Flags::bitVectorWithState(
                $this->getPhanFlags(),
                Flags::IS_OVERRIDE_INTENDED,
                $is_override_intended
            )
        );
    }

    /**
     * @return bool
     * True if this is an abstract method
     */
    public function isAbstract() : bool
    {
        return $this->getFlagsHasState(ast\flags\MODIFIER_ABSTRACT);
    }

    /**
     * @return bool
     * True if this is a final method
     */
    public function isFinal() : bool
    {
        return $this->getFlagsHasState(ast\flags\MODIFIER_FINAL);
    }

    /**
     * @return bool
     * True if this method returns a reference
     */
    public function returnsRef() : bool
    {
        return $this->getFlagsHasState(ast\flags\FUNC_RETURNS_REF);
    }

    /**
     * @return bool
     * True if this is a magic method
     * (Names are all normalized in FullyQualifiedMethodName::make())
     */
    public function getIsMagic() : bool
    {
        return \array_key_exists($this->getName(), FullyQualifiedMethodName::MAGIC_METHOD_NAME_SET);
    }

    /**
     * @return bool
     * True if this is a magic method which should have return type of void
     * (Names are all normalized in FullyQualifiedMethodName::make())
     */
    public function getIsMagicAndVoid() : bool
    {
        return \array_key_exists($this->getName(), FullyQualifiedMethodName::MAGIC_VOID_METHOD_NAME_SET);
    }

    /**
     * @return bool
     * True if this is the `__construct` method
     * (Does not return true for php4 constructors)
     */
    public function getIsNewConstructor() : bool
    {
        return ($this->getName() === '__construct');
    }

    /**
     * @return bool
     * True if this is the magic `__call` method
     */
    public function getIsMagicCall() : bool
    {
        return ($this->getName() === '__call');
    }

    /**
     * @return bool
     * True if this is the magic `__callStatic` method
     */
    public function getIsMagicCallStatic() : bool
    {
        return ($this->getName() === '__callStatic');
    }

    /**
     * @return Method
     * A default constructor for the given class
     */
    public static function defaultConstructorForClass(
        Clazz $clazz,
        CodeBase $code_base
    ) : Method {
        if ($clazz->getFQSEN()->getNamespace() === '\\' && $clazz->hasMethodWithName($code_base, $clazz->getName())) {
            $old_style_constructor = $clazz->getMethodByName($code_base, $clazz->getName());
        } else {
            $old_style_constructor = null;
        }

        $method_fqsen = FullyQualifiedMethodName::make(
            $clazz->getFQSEN(),
            '__construct'
        );

        $method = new Method(
            $old_style_constructor ? $old_style_constructor->getContext() : $clazz->getContext(),
            '__construct',
            $clazz->getUnionType(),
            0,
            $method_fqsen,
            $old_style_constructor ? $old_style_constructor->getParameterList() : null
        );

        if ($old_style_constructor) {
            $method->setRealParameterList($old_style_constructor->getRealParameterList());
            $method->setNumberOfRequiredParameters($old_style_constructor->getNumberOfRequiredParameters());
            $method->setNumberOfOptionalParameters($old_style_constructor->getNumberOfOptionalParameters());
            $method->setRealReturnType($old_style_constructor->getRealReturnType());
            $method->setUnionType($old_style_constructor->getUnionType());
        }

        return $method;
    }

    /**
     * @param Clazz $clazz - The class to treat as the defining class of the alias. (i.e. the inheriting class)
     * @param string $alias_method_name - The alias method name.
     * @param int $new_visibility_flags (0 if unchanged)
     * @return Method
     *
     * An alias from a trait use, which is treated as though it was defined in $clazz
     * E.g. if you import a trait's method as private/protected, it becomes private/protected **to the class which used the trait**
     *
     * The resulting alias doesn't inherit the Node of the method body, so aliases won't have a redundant analysis step.
     */
    public function createUseAlias(
        Clazz $clazz,
        string $alias_method_name,
        int $new_visibility_flags
    ) : Method {

        $method_fqsen = FullyQualifiedMethodName::make(
            $clazz->getFQSEN(),
            $alias_method_name
        );

        $method = new Method(
            $this->getContext(),
            $alias_method_name,
            $this->getUnionTypeWithUnmodifiedStatic(),
            $this->getFlags(),
            $method_fqsen,
            $this->getParameterList()
        );
        $method->setPhanFlags($this->getPhanFlags());
        switch ($new_visibility_flags) {
            case ast\flags\MODIFIER_PUBLIC:
            case ast\flags\MODIFIER_PROTECTED:
            case ast\flags\MODIFIER_PRIVATE:
                // Replace the visibility with the new visibility.
                $method->setFlags(Flags::bitVectorWithState(
                    Flags::bitVectorWithState(
                        $method->getFlags(),
                        ast\flags\MODIFIER_PUBLIC | ast\flags\MODIFIER_PROTECTED | ast\flags\MODIFIER_PRIVATE,
                        false
                    ),
                    $new_visibility_flags,
                    true
                ));
                break;
            default:
                break;
        }

        $defining_fqsen = $this->getDefiningFQSEN();
        if ($method->isPublic()) {
            $method->setDefiningFQSEN($defining_fqsen);
        }
        $method->real_defining_fqsen = $defining_fqsen;

        $method->setRealParameterList($this->getRealParameterList());
        $method->setRealReturnType($this->getRealReturnType());
        $method->setNumberOfRequiredParameters($this->getNumberOfRequiredParameters());
        $method->setNumberOfOptionalParameters($this->getNumberOfOptionalParameters());

        return $method;
    }

    /**
     * @param Context $context
     * The context in which the node appears
     *
     * @param CodeBase $code_base
     *
     * @param Node $node
     * An AST node representing a method
     *
     * @return Method
     * A Method representing the AST node in the
     * given context
     */
    public static function fromNode(
        Context $context,
        CodeBase $code_base,
        Node $node,
        FullyQualifiedMethodName $fqsen
    ) : Method {

        // @var array<int,Parameter>
        // The list of parameters specified on the
        // method
        $parameter_list =
            Parameter::listFromNode(
                $context,
                $code_base,
                $node->children['params']
            );

        // Create the skeleton method object from what
        // we know so far
        $method = new Method(
            $context,
            (string)$node->children['name'],
            UnionType::empty(),
            $node->flags ?? 0,
            $fqsen,
            $parameter_list
        );
        $doc_comment = $node->children['docComment'] ?? '';
        $method->setDocComment($doc_comment);

        // Parse the comment above the method to get
        // extra meta information about the method.
        $comment = Comment::fromStringInContext(
            $doc_comment,
            $code_base,
            $context,
            $node->lineno ?? 0,
            Comment::ON_METHOD
        );

        // Add each parameter to the scope of the function
        // NOTE: it's important to clone this,
        // because we don't want any assignments to modify the original Parameter
        foreach ($parameter_list as $parameter) {
            $method->getInternalScope()->addVariable(
                $parameter->cloneAsNonVariadic()
            );
        }
        foreach ($comment->getTemplateTypeList() as $template_type) {
            $method->getInternalScope()->addTemplateType($template_type);
        }

        if (!$method->isPHPInternal()) {
            // If the method is Analyzable, set the node so that
            // we can come back to it whenever we like and
            // rescan it
            $method->setNode($node);
        }

        // Keep an copy of the original parameter list, to check for fatal errors later on.
        $method->setRealParameterList($parameter_list);

        $method->setNumberOfRequiredParameters(array_reduce(
            $parameter_list,
            function (int $carry, Parameter $parameter) : int {
                return ($carry + ($parameter->isRequired() ? 1 : 0));
            },
            0
        ));

        $method->setNumberOfOptionalParameters(array_reduce(
            $parameter_list,
            function (int $carry, Parameter $parameter) : int {
                return ($carry + ($parameter->isOptional() ? 1 : 0));
            },
            0
        ));

        // Check to see if the comment specifies that the
        // method is deprecated
        $method->setIsDeprecated($comment->isDeprecated());

        // Set whether or not the element is internal to
        // the namespace.
        $method->setIsNSInternal($comment->isNSInternal());

        // Set whether or not the comment indicates that the method is intended
        // to override another method.
        $method->setIsOverrideIntended($comment->isOverrideIntended());
        $method->setSuppressIssueList($comment->getSuppressIssueList());

        if ($method->getIsMagicCall() || $method->getIsMagicCallStatic()) {
            $method->setNumberOfOptionalParameters(FunctionInterface::INFINITE_PARAMETERS);
            $method->setNumberOfRequiredParameters(0);
        }

        $is_trait = $context->getScope()->isInTraitScope();
        // Add the syntax-level return type to the method's union type
        // if it exists
        if ($node->children['returnType'] !== null) {
            // TODO: Avoid resolving this, but only in traits
            $return_union_type = (new UnionTypeVisitor($code_base, $context))->fromTypeInSignature(
                $node->children['returnType']
            );
            $method->setUnionType($method->getUnionType()->withUnionType($return_union_type));
            // TODO: Replace 'self' with the real class when not in a trait
        } else {
            $return_union_type = UnionType::empty();
        }
        $method->setRealReturnType($return_union_type);

        // If available, add in the doc-block annotated return type
        // for the method.
        if ($comment->hasReturnUnionType()) {
            $comment_return_union_type = $comment->getReturnType();
            if (!$is_trait) {
                $comment_return_union_type = $comment_return_union_type->withSelfResolvedInContext($context);
            }

            $method->setUnionType($method->getUnionType()->withUnionType($comment_return_union_type));
            $method->setPHPDocReturnType($comment_return_union_type);
        }

        // Defer adding params to the local scope for user functions. (FunctionTrait::addParamsToScopeOfFunctionOrMethod)
        // See PostOrderAnalysisVisitor->analyzeCallToMethod
        $method->setComment($comment);

        return $method;
    }

    /**
     * @return UnionType
     * The type of this method in its given context.
     */
    public function getUnionType() : UnionType
    {
        $union_type = parent::getUnionType();

        // If the type is 'static', add this context's class
        // to the return type
        if ($union_type->hasStaticType()) {
            $union_type = $union_type->withType(
                $this->getFQSEN()->getFullyQualifiedClassName()->asType()
            );
        }

        // If the type is a generic array of 'static', add
        // a generic array of this context's class to the return type
        if ($union_type->genericArrayElementTypes()->hasStaticType()) {
            // TODO: Base this on the static array type...
            $key_type_enum = GenericArrayType::keyTypeFromUnionTypeKeys($union_type);
            $union_type = $union_type->withType(
                $this->getFQSEN()->getFullyQualifiedClassName()->asType()->asGenericArrayType($key_type_enum)
            );
        }

        return $union_type;
    }

    public function getUnionTypeWithUnmodifiedStatic() : UnionType
    {
        return parent::getUnionType();
    }

    /**
     * @return FullyQualifiedMethodName
     */
    public function getFQSEN() : FullyQualifiedMethodName
    {
        return $this->fqsen;
    }

    /**
     * @return \Generator
     * @phan-return \Generator<Method>
     * The set of all alternates to this method
     */
    public function alternateGenerator(CodeBase $code_base) : \Generator
    {
        // Workaround so that methods of generic classes will have the resolved template types
        yield $this;
        $fqsen = $this->getFQSEN();
        $alternate_id = $fqsen->getAlternateId() + 1;

        $fqsen = $fqsen->withAlternateId($alternate_id);

        while ($code_base->hasMethodWithFQSEN($fqsen)) {
            yield $code_base->getMethodByFQSEN($fqsen);
            $fqsen = $fqsen->withAlternateId(++$alternate_id);
        }
    }

    /**
     * @param CodeBase $code_base
     * The code base with which to look for classes
     *
     * @return Method[]
     * The Methods that this Method is overriding
     * (Abstract methods are returned before concrete methods)
     *
     * @throws CodeBaseException if 0 methods were found.
     */
    public function getOverriddenMethods(
        CodeBase $code_base
    ) : array {
        // Get the class that defines this method
        $class = $this->getClass($code_base);

        // Get the list of ancestors of that class
        $ancestor_class_list = $class->getAncestorClassList(
            $code_base
        );

        $defining_fqsen = $this->getDefiningFQSEN();

        $method_list = [];
        $abstract_method_list = [];
        // Hunt for any ancestor classes that define a method with
        // the same name as this one.
        foreach ($ancestor_class_list as $ancestor_class) {
            // TODO: Handle edge cases in traits.
            // A trait may be earlier in $ancestor_class_list than the parent, but the parent may define abstract classes.
            // TODO: What about trait aliasing rules?
            if ($ancestor_class->hasMethodWithName($code_base, $this->getName())) {
                $method = $ancestor_class->getMethodByName(
                    $code_base,
                    $this->getName()
                );
                if ($method->getDefiningFQSEN() === $defining_fqsen) {
                    // Skip it, this method **is** the one which defined this.
                    continue;
                }
                // We initialize the overridden method's scope to ensure that
                // analyzers are aware of the full param/return types of the overridden method.
                $method->ensureScopeInitialized($code_base);
                if ($method->isAbstract()) {
                    // TODO: check for trait conflicts, etc.
                    $abstract_method_list[] = $method;
                    continue;
                }
                $method_list[] = $method;
            }
        }
        // Return abstract methods before concrete methods, in order to best check method compatibility.
        $method_list = array_merge($abstract_method_list, $method_list);
        if (count($method_list) > 0) {
            return $method_list;
        }

        // Throw an exception if this method doesn't override
        // anything
        throw new CodeBaseException(
            $this->getFQSEN(),
            "Method $this with FQSEN {$this->getFQSEN()} does not override another method"
        );
    }

    /**
     * @return FullyQualifiedMethodName the FQSEN with the original definition (Even if this is private/protected and inherited from a trait). Used for dead code detection.
     *                                  Inheritance tests use getDefiningFQSEN() so that access checks won't break.
     *
     * @suppress PhanPartialTypeMismatchReturn TODO: Allow subclasses to make property types more specific
     */
    public function getRealDefiningFQSEN() : FullyQualifiedMethodName
    {
        return $this->real_defining_fqsen ?? $this->getDefiningFQSEN();
    }

    /**
     * @return string
     * A string representation of this method signature (preferring phpdoc types)
     */
    public function __toString() : string
    {
        $string = '';
        // TODO: should this representation and other representations include visibility?

        $string .= 'function ';
        if ($this->returnsRef()) {
            $string .= '&';
        }
        $string .= $this->getName();

        $string .= '(' . \implode(', ', $this->getParameterList()) . ')';

        $union_type = $this->getUnionTypeWithUnmodifiedStatic();
        if (!$union_type->isEmpty()) {
            $string .= ' : ' . (string)$union_type;
        }

        return $string;
    }

    /**
     * @return string
     * A string representation of this method signature
     * (Based on real types only, instead of phpdoc+real types)
     */
    public function toRealSignatureString() : string
    {
        $string = '';

        $string .= 'function ';
        if ($this->returnsRef()) {
            $string .= '&';
        }
        $string .= $this->getName();

        $string .= '(' . \implode(', ', $this->getRealParameterList()) . ')';

        if (!$this->getRealReturnType()->isEmpty()) {
            $string .= ' : ' . (string)$this->getRealReturnType();
        }

        return $string;
    }

    public function getMarkupDescription() : string
    {
        $string = '';
        // It's an error to have visibility or abstract in an interface's stub (e.g. JsonSerializable)
        if ($this->isPrivate()) {
            $string .= 'private ';
        } elseif ($this->isProtected()) {
            $string .= 'protected ';
        } else {
            $string .= 'public ';
        }

        if ($this->isAbstract()) {
            $string .= 'abstract ';
        }

        if ($this->isStatic()) {
            $string .= 'static ';
        }

        $string .= 'function ';
        if ($this->returnsRef()) {
            $string .= '&';
        }
        $string .= $this->getName();

        $string .= '(' . implode(', ', array_map(function (Parameter $parameter) : string {
            return $parameter->toStubString();
        }, $this->getRealParameterList())) . ')';

        if (!$this->getRealReturnType()->isEmpty()) {
            $string .= ' : ' . (string)$this->getRealReturnType();
        }

        return $string;
    }

    /**
     * Returns this method's visibility ('private', 'protected', or 'public')
     */
    public function getVisibilityName() : string
    {
        if ($this->isPrivate()) {
            return 'private';
        } elseif ($this->isProtected()) {
            return 'protected';
        } else {
            return 'public';
        }
    }

    /**
     * Returns a PHP stub that can be used in the output of `tool/make_stubs`
     */
    public function toStub(bool $class_is_interface = false) : string
    {
        $string = '    ';
        // It's an error to have visibility or abstract in an interface's stub (e.g. JsonSerializable)
        if (!$class_is_interface) {
            $string .= $this->getVisibilityName() . ' ';

            if ($this->isAbstract()) {
                $string .= 'abstract ';
            }
        }

        if ($this->isStatic()) {
            $string .= 'static ';
        }

        $string .= 'function ';
        if ($this->returnsRef()) {
            $string .= '&';
        }
        $string .= $this->getName();

        $string .= '(' . implode(', ', array_map(function (Parameter $parameter) : string {
            return $parameter->toStubString();
        }, $this->getRealParameterList())) . ')';

        if (!$this->getRealReturnType()->isEmpty()) {
            $string .= ' : ' . (string)$this->getRealReturnType();
        }
        if ($this->isAbstract()) {
            $string .= ';';
        } else {
            $string .= ' {}';
        }

        return $string;
    }

    /**
     * Does this method have template types anywhere in its parameters or return type?
     * (This check is recursive)
     */
    public function hasTemplateType() : bool
    {
        return $this->getPhanFlagsHasState(Flags::HAS_TEMPLATE_TYPE);
    }

    private function recordHasTemplateType()
    {
        $this->setPhanFlags($this->getPhanFlags() | Flags::HAS_TEMPLATE_TYPE);
    }

    /**
     * Attempt to convert this template method into a method with concrete types
     * Either returns the original method or a clone of the method with more type information.
     */
    public function resolveTemplateType(
        CodeBase $code_base,
        UnionType $object_union_type
    ) : Method {
        $defining_fqsen = $this->getDefiningClassFQSEN();
        $defining_class = $code_base->getClassByFQSEN($defining_fqsen);
        if (!$defining_class->isGeneric()) {
            // ???
            return $this;
        }
        $expected_type = $defining_fqsen->asType();

        foreach ($object_union_type->getTypeSet() as $type) {
            if (!$type->hasTemplateParameterTypes()) {
                continue;
            }
            if (!$type->isObjectWithKnownFQSEN()) {
                continue;
            }
            $expanded_type = $type->withIsNullable(false)->asExpandedTypes($code_base);
            foreach ($expanded_type->getTypeSet() as $candidate) {
                if (!$candidate->isTemplateSubtypeOf($expected_type)) {
                    continue;
                }
                // $candidate is $expected_type<T...>
                $result = $this->cloneWithTemplateParameterTypeMap($candidate->getTemplateParameterTypeMap($code_base));
                return $result;
            }
        }
        return $this;
    }

    /**
     * @param array<string,UnionType> $template_type_map
     * A map from template type identifier to a concrete type
     */
    private function cloneWithTemplateParameterTypeMap(array $template_type_map) : Method
    {
        $result = clone($this);
        $result->cloneParameterList();
        foreach ($result->parameter_list as $parameter) {
            $parameter->setUnionType($parameter->getUnionType()->withTemplateParameterTypeMap($template_type_map));
        }
        $result->setUnionType($result->getUnionType()->withTemplateParameterTypeMap($template_type_map));
        $result->setPhanFlags($result->getPhanFlags() & ~Flags::HAS_TEMPLATE_TYPE);
        if (Config::get_track_references()) {
            // Quick and dirty fix to make dead code detection work on this clone.
            // Consider making this an object instead.
            // @see AddressableElement::addReference()
            $result->reference_list = &$this->reference_list;
        }
        return $result;
    }
}