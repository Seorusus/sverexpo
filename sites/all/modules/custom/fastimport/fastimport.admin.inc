<?php
/**
* @file
* Administration page callbacks for the annotate module.
*/
/**
* Импорт товаров по артикулу производителя и списку производителей.
* артикул производителя лежит в двух таблицах - данные и ревизии

`entity_type` = 'node', `entity_id` = $nid
`sv_field_data_field_artikul_fabriki`.`field_artikul_fabriki_value`

`entity_type` = 'node', `entity_id` = $nid
`sv_field_revision_field_artikul_fabriki`.`field_artikul_fabriki_value`


Логика работы импорта.
Массовое изменение товаров выбранных производителей. Поиск соответствия по артикулу (sku)
и обновление соответствующих товарных позиций (в зависимости от выбранного режима)
Данные вставляются в форму через TAB (символ табуляции) - копирование колонок из XLS-прайса.


Импорт может работать в трёх режимах:

1. [Импорт цен] импорт цен для выбранных производителей по артикулу
articul	price (цена на сайте)
Товары не попавшие в список (брэнд+артикул) игнорируются.

2. [Импорт остатков+предзаказ] Импорт остатков для производителей с предзаказом
articul	count (количество).
Реальное количество не учитывается - все товары с ненулевыми остатками включаются,
остальные (для выбранных производителей) - переводятся в предзаказ 
(включены, можно купить, но статус - предзаказ)

3. [Импорт остатков+выключение] Импорт остатков для производителей с выключением остальных товаров
articul	count (количество)
Товары с ненулевыми остатками включаются и попадают в продажу, остальные товары выбранных
производителей, не попавшие в импорт выключаются (status=0) и не скрываются из вывода на сайте.

Чтобы скрыть товары ненужного производителя - достаточно выбрать его в списке и ввести "что-нибудь" 
в поле для данных (отправка пустого поля запрещена - защита от невнимательности) 




field_artikul_fabriki_forma
* @ingroup forms
* @see system_settings_form().
*/

function fastimport_admin_settings() {
	$types = node_type_get_types();
	foreach($types as $node_type) {
		$options[$node_type->type] = $node_type->name;
	}
	
	print_r ($_SERVER); die ('*j(');

	$form['fastimport_node_types'] = array(
		'#type' => 'checkboxes',
		'#title' => t('Users may annotate these content types'),
		'#options' => $options,
//		'#default_value' => variable_get('fastimp_node_types', array('page')),
		'#description' => t('A text field will be available on these content types to
		make user-specific notes.'),
	);

	$form['#submit'][] = 'fastimport_admin_settings_submit';
		return system_settings_form($form);
	}
	
	
/**
* Process annotation settings submission.
*/
// function fastimport_admin_settings_submit($form, $form_state) {
	// print_r ($_POST); die();

// } // End foreach loop.	



/**
 * Commerce pickup settings form.
 */
function fastimport_settings_form_submit($form, &$form_state) {
if (!empty ($_POST)) {
	$err = false;
	$data = $form_state['input']['fastimport_data'];
	fastimport_import_data($data);
	//print_r ($form_state['input']['fastimport_producer']); //  [fastimport_producer] => Array ( [0] => 107 [1] => 143 [2] => 119 )
	if (isset ($form_state['input']['op_import_count']) || isset ($form_state['input']['op_import_count_off'])) {
		fastimport_import_count($form,$form_state,$form_state['input']['fastimport_producer']);
	} else if (isset ($form_state['input']['op_import_price'])) {
		fastimport_import_prices($form);
	}

	echo __LINE__;
	print_r ($_POST); die();
}

}
function fastimport_settings_form($form, &$form_state) {
// if (!empty ($_POST)) {
// echo __LINE__;
	// print_r ($_POST); die();
// }
	//print_r ($_SERVER); die ('*j(');
//var_dump($form);

/* // DRAFT BLOCK
  // Generate an array of bundles with addressfields.
  $options = array();
  $options = array();
  foreach (entity_get_info() as $entity_type => $entity) {
    if (!empty($entity['fieldable']) && $entity_type != 'group') {
      foreach($entity['bundles'] as $bundle_name => $bundle) {
        // Prefix the bundle name with the entity type.
        $options[$entity_type][$entity_type . '__' .$bundle_name] = check_plain($bundle['label']);
      }
    }
  }
  */

$form['#attached']['css'][] = drupal_get_path('module', 'fastimport') . '/fastimport.admin.css';  
  
  // Pickup producers and FILTER by fastimport_current_producers
  
  $dropdown_source = taxonomy_get_tree(3);
  $active_producers = fastimport_current_producers(); // false - отобразить всех; ?// false and
	$dropdown_array = array('0' => '--none--');
	foreach ($dropdown_source as $item) {
		$key = $item->tid;
		$value = $item->name;
		if (!empty($active_producers))
		if (!in_array($value,$active_producers))
			continue;
		$dropdown_array[$key] = $value;
	}

//producers filter dropdown
$form['fastimport_producer'] = array(
  '#weight' => '0',
  '#key_type' => 'associative',
  '#multiple_toggle' => '0',
  '#multiple' => '1',
  '#type' => 'select',
//  '#type' => 'checkboxes',
  '#options' => $dropdown_array,
  '#title' => 'Производители (CTRL + щелчок)',
  '#size' => 19,
  '#required' => TRUE,
);
unset($dropdown_array);

$form['fastimport_data'] = array(
  '#weight' => '1',
  '#type' => 'textarea',  
  '#title' => 'Данные в формате артикул | значение (цена/остаток)',
  '#required' => TRUE,
);
$form['#submit'] = array('fastimport_settings_form_submit');

$form['fastimport_submit_count'] = array(
  '#weight' => '3',
  '#type' => 'submit',  
  '#name' => 'op_import_count',  
  '#title' => t('Import count'),
  '#value' => 'Загрузить остатки + Предзаказ',
);

$form['fastimport_submit_count_off'] = array(
  '#weight' => '3',
  '#type' => 'submit',  
  '#name' => 'op_import_count_off',  
  '#title' => t('Import count and off'),
  '#value' => 'Загрузить остатки',
  '#style'=>'float:left;',
);

$form['fastimport_submit_count_info'] = array(
 '#weight' => '4',
 '#markup'=> '<div class="fastimport_info"><strong>Загрузка остатков:</strong>
  <ul>
    <li>Копируем из&nbsp;<strong style="color:red;font-size:20px;">остатков</strong>&nbsp;информацию в виде: артикул/количество</li>
    <li>Выбираем загружаемый бренд или бренды</li>
    <li>Нажимаем &quot;Загрузить остатки (+ Предзаказ)&quot;</li>
  </ul><hr/></div><br>');

$form['fastimport_submit_price'] = array(
  '#weight' => '5',
  '#type' => 'submit',  
  '#name' => 'op_import_price',  
  '#title' => 'Import price',
  '#value' => 'Загрузить цены',
);

$form['fastimport_submit_price_info'] = array(
 '#weight' => '6',
 '#markup'=> '<div class="fastimport_info"><strong>Загрузка цен:</strong>
  <ul>
    <li>Копируем из&nbsp;<strong style="color:red;font-size:20px;">цен</strong>&nbsp;информацию в виде: артикул/цена</li>
    <li>Выбираем загружаемый бренд или бренды</li>
    <li>Нажимаем &quot;Загрузить цены&quot;</li>
  </ul></div>');
 
  return system_settings_form($form);
}


/**
* import data into temp table (articul - value) 

CREATE TABLE IF NOT EXISTS `sv_fastimport_temp` (
  `sku` varchar(64) NOT NULL DEFAULT '',
  `value` varchar(128) NOT NULL DEFAULT '',
  KEY `sku` (`sku`)
) ENGINE=Memory DEFAULT CHARSET=utf8;

*/
	function fastimport_import_data($data,$table='sv_fastimport_temp') {	
// $result = db_query("SELECT nid, title FROM {node} WHERE type = :type", array(
  // ':type' => 'page',
// ));
		db_query ("TRUNCATE $table;");
		$data = trim ($data);
		$lines = explode ("\n",$data);
		$rows = array();
		foreach ($lines as $k=>$line) {
			$fields = explode ("\t",$line);
			if (count($fields)<2)
				continue;
			list ($model, $cnt) = $fields;
			$cnt = preg_replace('/[^0-9,]/','',$cnt); // точку(запятую т.е.) оставляем, цена может быть дробной
			$cnt = str_replace(',','.',$cnt);
			$model = addslashes($model);
			if (empty ($model) || empty ($cnt))
				continue;
			if (mb_strlen($model, 'utf-8')>25) //LED-JCDR-S MD-3W/WW/GU10
				continue;
			$cnt = (int) $cnt; //  для цен и остатков.. дробные части не учитываем. "НЕТ" и пр. в 0 
			$rows[] = "('$model','$cnt')";
		} 
		$q = "INSERT INTO $table VALUES ".implode(',',$rows);
		$result = db_exec($q); // db_query + $options['return'] =  Database::RETURN_AFFECTED;
		drupal_set_message('Данные загружены: строк '.$result, 'status');
	}
	
	
	function fastimport_current_producers(){
		$producers = array();
// old producerlist.. for 10.07.13		$producerList = 'GLOBO, Massive, ARTELAMP, Eglo, BATHGLASS, BERLINER MESSINGLAMPEN, JOALPA, LEDS C4, L`ARTE LUCE, MIRADA DE CRISTAL, ROYAL BOTANIA, Wunderlicht, Lussole,Favourite, Odeon Light, SLV,ROBERS,VIBIA,MarksLojd,ЭЛАТА';
		$producerList = "ARTELAMP,ARTURO,ALVAREZ,BATHGLASS,BERLINER,BERLINER MESSINGLAMPEN,Chiaro,Citilux,Dino,Eglo,Esto,FABBIAN,FEDE,FLOS,Favourite,GLOBO,HERNER GLAS,Illuminati,JOALPA,KOLARZ,L'ARTE LUCE,LEDS C4,LINEA LIGHT,LMZ,La Lampada,LampGustaf,Lussole,MIRADA DE CRISTAL,MW-Light,Mantra,Markslojd,Massive,Maytoni,NOVOTECH,Odeon Light,RIPERLAMP,ROYAL BOTANIA,Reccagni Angelo,SLV,Sferon,VIBIA,Wofi,Wunderlicht,ЭЛАТА";
		$producerList = explode(',',$producerList);
		foreach ($producerList as $v) {
			if ($producer = trim($v))
				$producers[] = $producer;
		}
		return $producers;		
	}
	
	/**
	* связка с sv_commerce_product и sv_commerce_product_revision
	 sv_field_revision_commerce_price 
	 sv_field_data_commerce_price
 	
entity_type = 'commerce_product' AND bundle = 'lamp' AND
commerce_price_amount = 100*price
	*/
function fastimport_import_prices(&$form){
	// отдельный запрос для проверки количества.. по идее должен закэшироваться, если места хватит.
	// иначе точное количество затронутых рядов узнать не получится. Обновляется 2 таблицы.. affected_rows=(UPDATE/2)?
	$q = "
	`sv_field_data_field_artikul_fabriki` art
	INNER JOIN sv_field_data_field_product product 
	ON product.entity_type = art.entity_type AND product.bundle = art.bundle AND product.entity_id = art.entity_id
	INNER JOIN `sv_commerce_product` cp ON cp.product_id =  product.field_product_product_id
	INNER JOIN sv_fastimport_temp tmp ON (tmp.sku = art.field_artikul_fabriki_value OR tmp.sku = cp.sku) 
	INNER JOIN sv_field_data_commerce_price price 
	ON price.entity_type = 'commerce_product' AND price.bundle = 'lamp' AND product.field_product_product_id = price.entity_id
	INNER JOIN sv_field_revision_commerce_price revision 
	ON revision.revision_id = price.revision_id AND price.entity_id = revision.entity_id AND price.entity_type = revision.entity_type
	";	
	$q1 = 'SELECT COUNT(*) as `cnt` FROM '.$q;
	$result = db_query($q1)->fetchField();
	
	$q = "
	UPDATE 
		$q
	SET `price`.commerce_price_amount = 100 * tmp.value	, `revision`.commerce_price_amount = 100 * tmp.value
	";
	$updated = db_exec($q);
	if ($result) {
		drupal_set_message('Записей обновлено: '.$result,'status');
	}
	// + программно сбросить кэш
	//db_query("DELETE FROM {cache};");

	drupal_flush_all_caches();
	header('Location:'.$_SERVER['REQUEST_URI']);
	exit();
}
	
	
// отключить/включить товар sv_commerce_product.status = 0 / =1
// отключить/включить товар sv_commerce_product.status = 0 / =1 ?
//

	
// обновляем field_count
// убираем наличие, если не из своих производителей	
function fastimport_import_count($form, &$form_state, $producers){
	$show_preorder = isset($form_state['input']['op_import_count']);
	if (!empty($producers)) //$producers = '(1,2,3)'; // выбранные продюсеры в таком формате
		$producers = "(". implode(',',$producers).")";

	if ($show_preorder) { // делаем предзаказ для указанных производителей
		// все товары выбранных производителей вкл (для простановки предзаказа)/выкл (снять с отображения)
		$status = 1;
	} else { // скрываем через status node и товары.
		$status = 0;
	}
		$q = "UPDATE 
			`sv_commerce_product` cp 
			INNER JOIN sv_field_data_field_product product ON cp.product_id =  product.field_product_product_id
			INNER JOIN `sv_taxonomy_index` ti ON ti.nid = product.entity_id AND product.entity_type = 'node'
			INNER JOIN sv_node AS node on node.nid = ti.nid
			INNER JOIN sv_node_revision AS node_revision on node.nid = node_revision.nid

			
			LEFT JOIN sv_field_data_field_ostatki ostatki 
			ON ostatki.entity_type = product.entity_type AND ostatki.bundle = product.bundle AND ostatki.entity_id = product.entity_id 
			
			
			SET cp.`status` = {$status}, node.status = {$status}, node_revision.status = {$status}, ostatki.field_ostatki_value = 0
			WHERE ti.tid IN {$producers}
		";
		$unpublic = db_exec($q); //(3 три таблицы?)
		drupal_set_message('Всего товаров затронуто: '.$unpublic,'status');//
	

	// $q = 'SELECT * 
	// FROM  `sv_field_data_field_artikul_fabriki` art
	// INNER JOIN sv_fastimport_temp tmp ON tmp.sku = art.field_artikul_fabriki_value	';
	
	// обновить количество товаров
		
		$q = "	`sv_field_data_field_artikul_fabriki` art
	INNER JOIN sv_fastimport_temp tmp ON tmp.sku = art.field_artikul_fabriki_value
	INNER JOIN sv_field_data_field_product product 
	ON product.entity_type = art.entity_type AND product.bundle = art.bundle AND product.entity_id = art.entity_id 
	
	INNER JOIN sv_commerce_product cp ON cp.product_id =  product.field_product_product_id
	
	INNER JOIN sv_field_data_field_ostatki ostatki 
	ON ostatki.entity_type = art.entity_type AND ostatki.bundle = art.bundle AND ostatki.entity_id = art.entity_id 
	
	INNER JOIN sv_node AS node on art.entity_id = node.nid
	INNER JOIN sv_node_revision AS node_revision on node.nid = node_revision.nid
";
		$q1 = 'SELECT COUNT(*) as `cnt` FROM '.$q;
		$result = db_query($q1)->fetchField();
		drupal_set_message('Совпадений по артикулу: '.$result,'status');
		
	$timestamp = time(); // for default sorting
	$q = "UPDATE 
			$q
	SET ostatki.field_ostatki_value = tmp.value, `cp`.`status` = 1,`node`.`status` = 1, node_revision.status = 1, node.changed=$timestamp ";
	
	$result = db_exec($q);
	
	// обновить последнюю ревизию остатков из основной таблицы
	$q = 'UPDATE `sv_field_revision_field_ostatki` revision INNER JOIN sv_field_data_field_ostatki ostatki 
	    ON revision.entity_type = ostatki.entity_type AND revision.bundle = ostatki.bundle AND revision.entity_id = ostatki.entity_id
		SET	revision.field_ostatki_value = ostatki.field_ostatki_value';
	db_query($q);
	drupal_flush_all_caches();
	header('Location:'.$_SERVER['REQUEST_URI']);
	exit();
}
	
	
	
	
	/*
	
if (empty ($data)) {
	$err = true;
	drupal_set_message('Не введены данные (артикул-значение)','error');
}
if (empty($form_state['input']['fastimport_producer'])) {
	$err = true;
	drupal_set_message('Не указаны брэнды','error');
}
if ($err) {
	drupal_goto(trim($_SERVER['REQUEST_URI'],'/'));
}
*/