(function ($) {

  // Increase/decrease quantity
  Drupal.commerce_extra_quantity_quantity = function(selector, way, amount) {

    // Find out current quantity and figure out new one
    var quantity = parseFloat($(selector).val());
    if (way == 1) {
      // Increase
      var new_quantity = quantity+amount;
    }
    else if (way == -1) {
      // Decrease
      var new_quantity = quantity-amount;
    }
    else {
      var new_quantity = quantity;
    }

    // Set new quantity
    if (new_quantity >= 1) {
      $(selector).val(new_quantity).change();
    }

    // Set disabled class depending on new quantity
    if (new_quantity <= 1) {
      $(selector).prev('span').addClass('commerce-quantity-plusminus-link-disabled');
    }
    else {
      $(selector).prev('span').removeClass('commerce-quantity-plusminus-link-disabled');
    }

  }

}(jQuery));
;

(function($) {

  /**
   * Trigger the Update button when hitting the enter key.
   */
  Drupal.behaviors.commerceLineItemForm = {
    attach: function (context, settings) {
      // Click the update button, not the remove button on enter key if we are
      // on a text field.
      $('div.commerce-line-item-views-form > form input.form-text', context).keydown(function(event) {
        if (event.keyCode === 13) {
          // Prevent browser's default submit from being clicked.
          event.preventDefault();
          $('input#edit-submit', $(this).parents('form')).click();
        }
      });
    }
  }

})(jQuery);
;
(function($) {

Drupal.admin = Drupal.admin || {};
Drupal.admin.behaviors = Drupal.admin.behaviors || {};

/**
 * @ingroup admin_behaviors
 * @{
 */

/**
 * Apply active trail highlighting based on current path.
 *
 * @todo Not limited to toolbar; move into core?
 */
Drupal.admin.behaviors.toolbarActiveTrail = function (context, settings, $adminMenu) {
  if (settings.admin_menu.toolbar && settings.admin_menu.toolbar.activeTrail) {
    $adminMenu.find('> div > ul > li > a[href="' + settings.admin_menu.toolbar.activeTrail + '"]').addClass('active-trail');
  }
};

/**
 * @} End of "ingroup admin_behaviors".
 */

Drupal.admin.behaviors.shorcutcollapsed = function (context, settings, $adminMenu) {

  // Create the dropdown base 
  $("<li class=\"label\"><a>"+Drupal.t('Shortcuts')+"</a></li>").prependTo("body.menu-render-collapsed div.toolbar-shortcuts ul"); 

}

Drupal.admin.behaviors.shorcutselect = function (context, settings, $adminMenu) {

  // Create the dropdown base
  $("<select id='shortcut-menu'/>").appendTo("body.menu-render-dropdown div.toolbar-shortcuts");
    
  // Create default option "Select"
  $("<option />", {
    "selected"  :  "selected",
    "value"     :  "",
    "text"      :  Drupal.t('Shortcuts')
  }).appendTo("body.menu-render-dropdown div.toolbar-shortcuts select");
    
  // Populate dropdown with menu items
  $("body.menu-render-dropdown div.toolbar-shortcuts a").each(function() {
    var el = $(this);
    $("<option />", {
      "value"   :  el.attr("href"),
      "text"    :  el.text()
    }).appendTo("body.menu-render-dropdown div.toolbar-shortcuts select");
    });
    
  $("body.menu-render-dropdown div.toolbar-shortcuts select").change(function() {
    window.location = $(this).find("option:selected").val();
  });
  
  $('body.menu-render-dropdown div.toolbar-shortcuts ul').remove();

};

})(jQuery);
;
