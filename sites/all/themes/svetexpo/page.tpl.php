<?php if ($tabs): echo render($tabs); endif; ?> 
<div class="overlay"></div>

<div class="popup recall_popup">
	<div class="popup_top"></div>
	<div class="popup_content">
		<div class="popup_close"></div>
		<div class="popup_box">
			<div class="popup_header">
				Заказать обратный звонок
			</div>
			<div class="popup_form">
<form id="feedback-form" method="post" action="/" onsubmit="return checkfb();">	
				<div class="popup_form_section">
					<span>
						Ваше имя:
					</span>
					<input type="text" name="fb_name" value="">
				</div>
				<div class="popup_form_section">
					<span>
						Номер телефона:
					</span>
					<input type="text" name="fb_phone" value="">
				</div>
				<div class="popup_form_button">
					<button type="submit" class="but"><span>Заказать</span></button>
				</div>
</form>						
			</div>
		</div>
	</div>
	<div class="popup_bottom"></div>
</div>

<div class="container">
	<div class="light">
		<div class="site">
			<header>
				<a href="<?php print $front_page; ?>" class="logo"></a>
				<div class="header_box">
					<div class="header_box_phone">
						<span>
							8-495-961-73-84
						</span>
					</div>
					<div class="header_box_sep"></div>
					<div class="header_box_worktime">
						Мы работаем каждый день <span>с 10-00 до 20-00</span><br>без обеда и выходных
					</div>
				</div>
				<div class="cart_box">
					<a href = "/cart"> <?php print theme('image', array('path' => path_to_theme() . '/img/cart.png')); ?>
						<span>Корзина</span>
						<div class="cart_content">
							<?php print render($page['top_cart']); ?>
						</div>			
					</a>
				</div>
				<div class="login_box">
					<form method="post" action="/user">
					<input name="name" id="login_name" type="text" placeholder="Введите логин" value="" >
					<input name="pass" type="password" placeholder="Введите пароль" value="" >
					<input name="form_id" type="hidden" value="user_login" >
					<input type="submit" value="Войти">
					</form>
				</div>
				<a href="#" class="recall">
					<span>
						Заказать<br>обратный звонок
					</span>
				</a>
			</header>
			
			<nav>
			<?php print render($page['header_menu']); ?>

		   <div class="nav_shadow"></div>
              <div class="search_form">
                <?php
                $view = views_get_view('search_on_site');
                $view->set_display('page');
                $view->init_handlers();
                $exposed_form = $view->display_handler->get_plugin('exposed_form');
                print $exposed_form->render_exposed_form(TRUE);
                ?>
              </div>
			</nav>
			<div class="content">
                <?php if(drupal_is_front_page()) print render($page['takeathome']); ?>

<?php if (isset($breadcrumb)) {
    print render($breadcrumb);
} ?>
<?php if ($messages): ?>
    <div id="messages">
        <div class="section clearfix">
             <?php print $messages; ?>
        </div>
    </div> <!-- /.section, /#messages -->
  <?php endif; ?>			
<?php if ($page && !(isset($node) && $node && ($node->type=='lamp' || $node->type == 'streetlamp' ))): ?>
<h1 class="title"><?php print $title; ?></h1>
<?php endif; ?>

			<?php print render($page['content']); ?>

                <?php if(drupal_is_front_page()) print render($page['takeathome']); ?>
			
<?php $current = taxonomy_term_load(arg(2)); ?>
<?php if ($current): ?>
    <div class="taxonomy-description">
        <?php echo $current->description; ?>
    </div>
<?php endif; ?>				

			</div>
			<aside>
				<div class="menu">
					<div class="menu_left_shadow"></div>
					<div class="menu_right_shadow"></div>
					<div class="menu_top"></div>
					<div class="menu_content">
					
      <?php if ($page['sidebar_first']): ?>
        <div id="sidebar-first" class="sidebar">
          <?php print render($page['sidebar_first']); ?>
        </div>
      <?php endif; ?>
				</div>
					<div class="menu_bottom"></div>
				</div>
				<div class="aside_info_box">
					<div class="aside_info_box_header">
						Приходите к нам в магазин
					</div>
					<p>
						Все светильники отмеченные значком <?php print "<img src='" . $base_path . path_to_theme() . "/img/in.png' />"; ?> можно посмотреть в нашем магазине
						по адресу: <span>Нахимовский проспект, дом 24, павильон № 3, этаж 1, сектор B, место 338</span>
					</p>
	
					<p>
						<span>Мы работаем каждый день с 10-00 до 20-00</span>
					</p>
					<p>
						Скажите что пришли по объявлению на сайте и получите <span>ПРИЯТНЫЙ СЮРПРИЗ</span>
					</p>
                    <?php
                    print theme('image', array(
                        'path' => path_to_theme() . '/img/present.png',
                        'attributes' => array('class' => 'bottom_image'),
                        'alt' => 'Present',
                    )); ?>
				</div>
				<div class="banner_box">
					<a href="/delivery.html">
                        <?php print theme('image', array('path' => path_to_theme() . '/img/free_delivery.png','alt' => 'Free')); ?>
					</a>
				</div>
				<div class="list_header">
					Бренды
				</div>
      <?php if ($page['sidebar_first']): ?>
        <div id="sidebar-second" class="sidebar">
          <?php print render($page['sidebar_second']); ?>
        </div>
      <?php endif; ?>
                <div class="list_header">Статьи</div>
                <div class="article_block">
                    <?php print views_embed_view('articles_page', 'article_block'); ?>
                </div>
				</aside>
			<div class="clear"></div>
		</div>
	</div>
</div>

<footer>
	<div class="copyright">
		<span>SvetExpo</span> - магазин люстр и светильников
		<br>
		Все права защищены, 2012-2013
	</div>
	<div class="footer_box">
		<div class="footer_menu">
			<?php print render($page['header_menu']); ?>			
		</div>
		<div class="footer_contacts">
			<div class="footer_phone">
				<span>Телефон:</span> 8 (495) 961-73-84, 8 (495) 779-12-69
			</div>
			<span>Адрес:</span> Нахимовский проспект, дом 24, павильон № 3, этаж 1, сектор B, место 338
		</div>
	</div>
</footer>