<?php

/**
 * @file
 * Template file for the answers section of the FAQ page if set to show
 * categorized questions at the top of the page.
 */
?>

<div class="faq-category-answers <?php echo $category_display == 'subcategory' ? 'sub' : 'root'; ?>" id="category-<?php echo $term->tid; ?>">
  <h2><?php echo $category_name; ?></h2>

  <?php foreach ($nodes as $i => $node): ?>
    <div class="faq-item" id="category-<?php echo $term->tid; ?>:answer-<?php echo $node['nid']; ?>">
      <a class="faq-question-link" href="#category-<?php echo $term->tid; ?>:answer-<?php echo $node['nid']; ?>">
        <div class="faq-question">
          <?php print $node['question']; ?>
        </div>
      </a>

      <div class="faq-answer">
        <?php print $node['body']; ?>
        <?php if (isset($node['links'])): ?>
          <?php print $node['links']; ?>
        <?php endif; ?>
      </div>
    </div>

  <?php endforeach; ?>
</div>
