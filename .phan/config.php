<?php

/**
 * This configuration will be read and overlaid on top of the
 * default configuration. Command line arguments will be applied
 * after this file is read.
 *
 * @see src/Phan/Config.php
 * See Config for all configurable options.
 */
return [
    'backward_compatibility_checks' => true,
    'target_php_version' => 7.2,
   
    'ignore_undeclared_functions_with_known_signatures' => false,

    'whitelist_issue_types' => [
        'PhanCompatiblePHP7',  // This only checks for **syntax** where the parsing may have changed. This check is enabled by `backward_compatibility_checks`
        'PhanDeprecatedFunctionInternal',  // Warns about a few functions deprecated in 7.0 and later.
        //'PhanUndeclaredFunction',  // Check for removed functions such as split() that were deprecated in php 5.x and removed in php 7.0.
	'PhanInvalidConstantFQSEN',
    ],

    'directory_list' => [
        '.',
    ],

    'exclude_analysis_directory_list' => [
        'vendor/',
        'profiles/ding2/'
    ],
];
