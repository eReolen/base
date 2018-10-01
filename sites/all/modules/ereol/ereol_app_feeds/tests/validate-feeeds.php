<?php

require_once __DIR__.'/../vendor/autoload.php';

use Opis\JsonSchema\Schema;
use Opis\JsonSchema\Validator;

$items = [
	// feed url, schema url
	['http://ereolen.vm/app/feed/frontpage', 'file://'.__DIR__.'/schema/frontpage.schema.json'],
	['http://ereolen.vm/app/feed/themes', 'file://'.__DIR__.'/schema/themes.schema.json'],
];

foreach ($items as $item) {
	[$feedUrl, $schemaUrl] = $item;
	$data = json_decode(file_get_contents($feedUrl));
	$schema = Schema::fromJsonString(file_get_contents($schemaUrl));

	$validator = new Validator();

	$result = $validator->schemaValidation($data, $schema);

	echo $feedUrl, PHP_EOL;
	if ($result->isValid()) {
		echo '$data is valid', PHP_EOL;
	} else {
		$error = $result->getFirstError();
		echo '$data is invalid', PHP_EOL;
		echo "Error: ", $error->keyword(), PHP_EOL;
		echo 'Arguments: ', json_encode($error->keywordArgs(), JSON_PRETTY_PRINT), PHP_EOL;
		echo 'Data: ', json_encode($error->data(), JSON_PRETTY_PRINT), PHP_EOL;
		echo 'Pointer: ', json_encode($error->dataPointer());
	}
}
