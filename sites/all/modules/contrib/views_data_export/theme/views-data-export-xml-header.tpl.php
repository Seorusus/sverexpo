<?php
/**
 * @file views-view-table.tpl.php
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $rows: An array of row items. Each row is an array of content
 *   keyed by field ID.
 * - $header: an array of headers(labels) for fields.
 * - $themed_rows: a array of rows with themed fields.
 * @ingroup views_templates
 */

// Short tags act bad below in the html so we print it here.
print '<?xml version="1.0" encoding="UTF-8" ?>';
?>

<yml_catalog date="<?= date('Y-m-d h:i'); ?>">
  <shop>
    <name><?= variable_get('site_name');?></name>
    <company>Svetexpo</company>
    <url><?= $GLOBALS['base_url']; ?></url>
    <currencies>
      <currency id="RUR" rate="1" plus="0"/>
    </currencies>
    <categories>
      <?php
      $tree = taxonomy_get_tree(2, 0, 1);
      foreach ($tree as $parent_term):
        $parent_terms = taxonomy_get_children($parent_term->tid); ?>
        <category id="<?php echo $parent_term->tid;?>"><?php echo $parent_term->name;?></category>
        <?php if(is_array($parent_terms)){
        foreach($parent_terms as $children_term):?>
          <category id="<?php echo $children_term->tid ?>" parentId="<?php echo $parent_term->tid ?>"><?php echo $children_term->name;?></category>
        <?php endforeach;
      } ?>

      <?php endforeach;?>
    </categories>
<<?php print $root_node; ?>>
