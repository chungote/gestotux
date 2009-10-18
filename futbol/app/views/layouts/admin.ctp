<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<?php echo $html->charset(); ?>
	<title>
		<?php echo $title_for_layout; ?>
	</title>
	<?php
		echo $html->meta('icon');
		echo $html->css('finta');
		echo $html->css('admin');
		//echo $scripts_for_layout;
	?>
</head>
<div>
<div align="center" class="fondo-general">
<div class="separacion"></div>
<table cellpadding="0" border="0" cellspacing="0" width="800" class="tabla-general">
  <tbody>
    <tr class="menu-arriba">
    </tr>
    <tr>
		<td colspan="7"><?php echo $this->requestAction( '/users/ruta/' ); ?></td>
    </tr>
    <tr>
		<td colspan="7"><?php $session->flash(); ?></td>
    </tr>
    <tr>
		<td colspan="7"><?php echo $content_for_layout; ?></td>
    </tr>
    <tr class="menu-abajo">
      <td class="item-menu" colspan="7">
		<?php echo $html->link( 'Inicio', '/admin', array( 'class' => 'item-menu' ) ); ?> |
		<?php echo $html->link( 'Torneo', '/admin/torneos', array( 'class' => 'item-menu' ) ); ?>  |
		<?php echo $html->link( 'Zona', '/admin/zonas', array( 'class' => 'item-menu' ) ); ?> |
		<?php echo $html->link( 'Fechas', '/admin/fechas', array( 'class' => 'item-menu' ) ); ?> |
		<?php echo $html->link( 'Partidos', '/admin/partidos/index', array( 'class' => 'item-menu' ) ); ?> |
		<?php echo $html->link( 'Anuncios', '/admin/anuncios', array( 'class' => 'item-menu' ) ); ?> |
		<?php echo $html->link( 'Equipos', '/admin/equipos/index', array( 'class' => 'item-menu' ) ); ?> |
		<?php echo $html->link( 'Publicidades', '/admin/publicidades', array( 'class' => 'item-menu' ) ); ?> |
		<?php echo $html->link( 'Fotos', '/admin/fotos', array( 'class' => 'item-menu' ) ); ?> |
		<?php echo $html->link( 'Salir', '/users/logout', array( 'class' => 'item-menu' ) ); ?> |
		<?php echo $html->link( 'Ver Sitio', '/pages/index', array( 'class' => 'item-menu' ) ); ?>
	</td>
    </tr>
    <tr>
      <td colspan="11" class="pie"><?php echo $html->link( 'www.lafintafutbol.com.ar', '/' ); ?> :: copyright 2009 :: dise&ntilde;o: <?php echo $html->link( "Coudannes adv", 'http://www.coudannesadv.com.ar/' );?> /<?php echo $html->link( 'bscomputacion', 'http://www.bscomputacion.com.ar/' ); ?></td>
    </tr>
    <tr>
      <td colspan="11" class="pie">			<script type="text/javascript"><!--
			google_ad_client = "pub-1880233918301202";
			/* horizontal mi musica */
			google_ad_slot = "6225035208";
			google_ad_width = 468;
			google_ad_height = 15;
			//-->
			</script>
			<script type="text/javascript"
			src="http://pagead2.googlesyndication.com/pagead/show_ads.js">
			</script></td>
    </tr>
  </tbody>
</table>
</div>
</body>
</html>