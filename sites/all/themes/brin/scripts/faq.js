(function($) {
  Drupal.behaviors.faq = {
    attach : function() {
      if (window.location.hash) {
        Drupal.behaviors.faq.setActive(window.location.hash);
      }

      $('.faq-header-link, .faq-question-link').click(function() {
        // Allow clicking again to collapse.
        if ($(this).hasClass('faq-question-link') && $(this).closest('.faq-item').hasClass('active')) {
          $(this).closest('.faq-item').removeClass('active');
        }
        else {
          Drupal.behaviors.faq.setActive($(this).attr('href'));
        }
      });
    },

    setActive : function(hash) {
      var split = hash.split(':');
      var elem = $(split[0]);

      // Set active class on questions container.
      $('.faq-category-answers').removeClass('active');
      elem.addClass('active');

      // Set active class on link in menu.
      $('.faq-questions > div').removeClass('active');
      $('.faq-header-link[href="'+ split[0] + '"]').closest('.faq-questions > div').addClass('active');

      // Set active question.
      if (split[1]) {
        $('#' + split[1]).addClass('active');
      }
    },
  };
})(jQuery);
