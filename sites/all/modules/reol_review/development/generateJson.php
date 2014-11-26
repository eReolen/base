<?php

$items = array(
  array(
    'nid' => '100',
    'title' => 'Anmelder Det Første Svar',
    'description' => 'Vi har anmeldt denne fine bog',
    'isbn' => '9788792539731',
    'credate' => '1416577066',
    'author' => 'Michael Søby Andersen',
    'book_title' => 'Det Første Svar',
    'link' => 'http://www.litteratursiden.dk/node/111526',
  ),
  array(
    'nid' => '101',
    'title' => 'Nu er det Bortført',
    'description' => 'Vi har anmeldt endnu en fin bog',
    'isbn' => '9788792639318',
    'credate' => '1416577066',
    'author' => 'Thomas Fini Hansen',
    'book_title' => 'Bortført',
    'link' => 'http://www.litteratursiden.dk/node/111526',
  ),
  array(
    'nid' => '102',
    'title' => 'Så har vi Det Gode Håb',
    'description' => 'Vi har anmeldt en lydbog!',
    'isbn' => '9788792165473',
    'credate' => '1416577066',
    'author' => 'Rasmus Lückow Nielsen',
    'book_title' => 'Det Gode Håb',
    'link' => 'http://www.litteratursiden.dk/node/111526',
  ),
  array(
    'nid' => '103',
    'title' => 'Endnu en lydbog: Det Første Jeg Tænker På',
    'description' => 'En lydbog igen',
    'isbn' => '9788702083859',
    'credate' => '1416577066',
    'author' => 'Carsten Michael Kaa',
    'book_title' => 'Det Første Jeg Tænker På',
    'link' => 'http://www.litteratursiden.dk/node/111526',
  ),
);
echo json_encode($items);
