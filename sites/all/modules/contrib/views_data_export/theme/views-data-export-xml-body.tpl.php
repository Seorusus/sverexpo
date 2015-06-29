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

module_load_include('inc', 'pathauto', 'pathauto');
?>
<?php foreach ($themed_rows as $count => $row): ?>
  <<?php print $item_node; ?> id="<?= $row['nid'];?>" available="<?=$row['field_ostatki'] < 1 ? 'false' : 'true'; ?>">
  <?php unset($row['nid']);?>
    <url><?= $row['path'];?></url>
    <price><?=$row['commerce_price']/100; ?></price>
    <currencyId>RUR</currencyId>
    <categoryId><?= $row['tid'];?></categoryId>
    <picture>http://img.svetexpo.ru/goods/images/<?= pathauto_cleanstring($row['term_node_tid']);?>/<?= str_replace(array('/', '.', '(', ')','№', '=', ' '), '_', mb_strtolower($row['field_artikul_fabriki']));?>.jpg</picture>
    <delivery>true</delivery>

    <?= $row['commerce_price'] < 500000 ? '<local_delivery_cost>300</local_delivery_cost>' : '<local_delivery_cost>0</local_delivery_cost>'; ?>

    <name><?= $row['title'];?></name>

    <?php if(!empty($row['field_artikul_fabriki'])):?>
        <vendorCode><?= $row['field_artikul_fabriki'];?></vendorCode>
    <?php endif; ?>

    <?= $row['commerce_price'] < 300000 ? '<sales_notes>Минимальная сумма заказа - 3000 руб.</sales_notes>':''?>

     <?php if(!empty($row['field_strana_proishozhdenija'])):?>
        <country_of_origin><?= $row['field_strana_proishozhdenija'];?></country_of_origin>
     <?php endif; ?>

    <?php if(!empty($row['field_ves'])):?>
        <param name="Вес" unit="г"><?= $row['field_ves'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_shirina'])):?>
        <param name="Ширина" unit="см"><?= trim(trim($row['field_shirina'], '0'), '.');?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_vysota'])):?>
        <param name="Высота" unit="см"><?= trim(trim($row['field_vysota'], '0'), '.');?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_min_vysota'])):?>
        <param name="Минимальная высота" unit="см"><?= $row['field_min_vysota'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_maks_vysota'])):?>
        <param name="Максимальная высота" unit="см"><?= $row['field_maks_vysota'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_dlina'])):?>
        <param name="Длина" unit="см"><?=  trim(trim($row['field_dlina'], '0'), '.');?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_glubina_vrezki'])):?>
        <param name="Глубина врезного отверстия" unit="см"><?= $row['field_glubina_vrezki'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_obem'])):?>
        <param name="Объем" unit="л"><?= $row['field_obem'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_rast_ot_steny'])):?>
        <param name="Расстояние от стены" unit="см"><?= trim(trim($row['field_rast_ot_steny'], '0'), '.');?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_napr_sob'])):?>
        <param name="Напряжение" unit="Вт"><?= trim(trim($row['field_napr_sob'], '0'), '.');?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_obshai_moshn_vych'])):?>
        <param name="Общая мощность" unit="Вт"><?= $row['field_obshai_moshn_vych'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_type_tsokol_sob'])):?>
        <param name="Тип цоколя" unit=""><?= $row['field_type_tsokol_sob'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_komplektacija'])):?>
        <param name="Комплектация лампочками" unit=""><?= $row['field_komplektacija'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_count_lamp_cult'])):?>
        <param name="Количество лампочек" unit="шт"><?= $row['field_count_lamp_cult'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_maks_mosh_1_lamp'])):?>
        <param name="Максимальная мощность одной лампочки" unit="Вт"><?= $row['field_maks_mosh_1_lamp'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_klass_zazemlenija'])):?>
        <param name="Класс электробезопасности" unit=""><?= $row['field_klass_zazemlenija'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_stepen_zashhity'])):?>
        <param name="Степень пылевлагозащиты" unit=""><?= $row['field_stepen_zashhity'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_hrustal'])):?>
        <param name="Хрусталь" unit=""><?= $row['field_hrustal'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_tip_hrustalja'])):?>
        <param name="Название хрусталя" unit=""><?= $row['field_tip_hrustalja'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_material_karkas'])):?>
        <param name="Материал каркаса" unit=""><?= $row['field_material_karkas'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_kovannyi'])):?>
        <param name="Кованый" unit=""><?= $row['field_kovannyi'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_material_abajura'])):?>
        <param name="Материал плафона/абажура" unit=""><?= $row['field_material_abajura'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_cvet_abazhura'])):?>
        <param name="Цвет плафона/абажура" unit=""><?= $row['field_cvet_abazhura'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_stil'])):?>
        <param name="Стиль" unit=""><?= $row['field_stil'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_floristika'])):?>
        <param name="Флористика" unit=""><?= $row['field_floristika'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_serie'])):?>
        <param name="Серия" unit=""><?= $row['field_serie'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_nasolnechbatar'])):?>
        <param name="На солнечных батареях" unit=""><?= $row['field_nasolnechbatar'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_svetodiodnyi'])):?>
        <param name="Светодиодный" unit=""><?= $row['field_svetodiodnyi'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_podsvetka'])):?>
        <param name="Подсветка предметов" unit=""><?= $row['field_podsvetka'];?></param>
    <?php endif; ?>

    <?php if(!empty($row['field_detskiy'])):?>
        <param name="Детский" unit=""><?= $row['field_detskiy'];?></param>
    <?php endif; ?>

    </<?php print $item_node; ?>>
<?php endforeach; ?>
