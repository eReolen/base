<?php

/**
 * @file
 * Defines the sensible defaults for error messages in publizon.
 */

$errors = array(
  -1 => array(
    'error_code' => '-1',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>Unknown error</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
  105 => array(
    'error_code' => '105',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>ebookid er ikke er gyldigt isbn nummer (#105).</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
  114 => array(
    'error_code' => '114',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>Ugyldigt kortnummer og/eller pinkode (#114).</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
  118 => array(
    'error_code' => '118',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>Biblioteket kunne ikke autoriseres (#118).</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
  120 => array(
    'error_code' => '120',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>Antallet af samtidige lån er overskredet (#120).</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
  125 => array(
    'error_code' => '125',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>Biblioteket har nået forbrugsgrænsen i indeværende måned. Kontakt evt. dit lokale bibliotek for yderligere oplysninger (#125).</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
  126 => array(
    'error_code' => '126',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>Biblioteket har nået grænsen for antal udlån i indeværende måned. Kontakt evt. dit lokale bibliotek for yderligere oplysninger (#126).</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
  128 => array(
    'error_code' => '128',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>Bogen er ikke tilgængelig for udlån (#128).</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
  129 => array(
    'error_code' => '129',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>Bogen kan højst genlånes én gang (#129).</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
  130 => array(
    'error_code' => '130',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>Bogen kan først lånes igen 90 dage efter sidste låns udløb (#130).</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
  131 => array(
    'error_code' => '131',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>Bogen kan ikke lånes (#131).</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
  134 => array(
    'error_code' => '134',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>Kortet er midlertidigt blokeret (#134)</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
  135 => array(
    'error_code' => '135',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>Grænsen for antal tilladte lån på bogen er nået (#135)</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
  136 => array(
    'error_code' => '136',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>De opkøbte klip er alle taget i brug (#136).</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
  137 => array(
    'error_code' => '137',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>Dit bibliotek tillader kun op til X samtidige reserveringer (#137).</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
  138 => array(
    'error_code' => '138',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>Der skete en uventet fejl. (#138).</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
  139 => array(
    'error_code' => '139',
    'show_bookmark' => 0,
    'show_reserve' => 0,
    'error_text' => array(
      'value' => '<p>Ugyldigt clientid. (#139).</p>',
      'format' => 'ding_wysiwyg',
    ),
  ),
);
