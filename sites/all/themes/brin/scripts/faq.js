(function($) {
  Drupal.behaviors.faq = {
    attach : function() {
      Drupal.behaviors.faq.setActive(window.location.hash);

      $('.faq-header-link, .faq-question-link').click(function() {
        // Allow clicking again to collapse.
        if ($(this).hasClass('faq-question-link') && $(this).closest('.faq-item').hasClass('active')) {
          $(this).closest('.faq-item').removeClass('active');
        }
        else {
          Drupal.behaviors.faq.setActive($(this).attr('href'));
        }
      });

      $('#faq-show-all').click(function(e) {
        e.preventDefault();

        $('.faq-category-answers, .faq-item').addClass('active');
      });
    },

    setActive : function(hash, second) {
      if (second == undefined) {
        second = false;
      }

      var split = hash.split(':');
      var elem = $(split[0]);

      if (elem.length) {
        // Set active class on questions container.
        $('.faq-category-answers').removeClass('active');
        elem.addClass('active');

        // Set active class on link in menu.
        $('.faq-questions > div').removeClass('active');
        $('.faq-header-link[href="'+ split[0] + '"]').closest('.faq-questions > div').addClass('active');

        // Set active question.
        $('.faq-item').removeClass('active');
        if (split[1]) {
          $(hash.replace(':', '\\:')).addClass('active');
        }
      }
      else if (!second) {
        // Automatically choose first, if nothing else is chosen.
        Drupal.behaviors.faq.setActive($('.faq-menu').first().find('.faq-header-link').attr('href'), true);
      }
    },
  };
})(jQuery);
