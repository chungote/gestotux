<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<meta name="verify-v1" content="Ss0fQISewOn4KoZgMHtTTVxawJ2IlDyv5nfpsLT8SSc=" />
	<?php echo $html->charset(); ?>
	<title>
		<?php echo $title_for_layout; ?>
	</title>
	<?php
		echo $html->meta('icon');
		echo $html->css('finta');
		echo $html->css( 'jquery.tabs' );
		echo $html->css( 'jquery.tabs-ie' );
		echo $javascript->link( array( 'prototype' ) );
		echo $javascript->link( array( 'lightbox' ) );
		echo $javascript->link( array( 'builder' ) );
		echo $javascript->link( array( 'effects' ) );
		echo $javascript->link( array( 'swfobject' ) );
		echo $javascript->link( array( 'jquery' ) );
		echo $scripts_for_layout;
	?>
	<?php echo $html->css('lightbox'); ?>
	<script type="text/javascript" src="<?php echo $this->webroot . 'js/'; ?>scriptaculous.js?load=effects"></script>
</head>
<body>
<div align="center" class="fondo-general">
<div class="separacion"></div>
<table cellpadding="0" border="0" cellspacing="0" width="800" class="tabla-general">
  <tbody>
    <tr>
     <td colspan="3">
      <table cellspacing="0" border="0" cellpadding="0">
		<tr class="menu-arriba">
      		<td width="100"><?php echo $html->image( 'liga.png', array( 'url' => '/pages/la_liga' ) ); ?></td>
      		<td width="5"><?php echo $html->image( 'separador.png' ); ?></td>
      		<td width="65"><?php echo $html->image( 'torneo.png', array( 'url' => '/torneos/anteriores' ) ); ?></td>
      		<td width="5"><?php echo $html->image( 'separador.png' ); ?></td>
      		<td width="110"><?php echo $html->image( 'inscripciones.png', array( 'url' => '/inscripciones' ) ); ?></td>
			<td width="290">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
      		<td width="95"><?php echo $html->image( 'ubicacion.png', array( 'url' => '/pages/construccion' ) ); ?></td>
      		<td width="5"><?php echo $html->image( 'separador.png' ); ?></td>
      		<td width="75"><?php echo $html->image( 'sponsors.png', array( 'url' => '/pages/sponsors' ) ); ?></td>
      		<td width="5"><?php echo $html->image( 'separador.png' ); ?></td>
			<td width="105"><?php echo $html->image( 'contactos.png', array( 'url' => '/pages/contacto' ) ); ?></td>
    		</tr>
      </table>
     </td>
    </tr>
    <tr>
      <td colspan="3" class="fecha">
		<?php //echo $time->nice(); ?>
		<div class="botones">
		<?php echo $html->image( 'home.png', array( 'url' => '/pages/index', 'class' => 'boton_home' ) ); ?>
		<?php echo $html->image( 'contacto.png', array( 'url' => '/pages/contacto', 'class' => 'boton_contacto' ) ); ?>
		</div>
	</td>
    </tr>
    <tr>
      <td valign="top" width="30" class="menu-izq"><?php echo $html->image( 'fond_arriba_izq.png', array( 'width' => 146 ) ); ?><?php echo $this->renderElement( 'menu' ); ?></td>
      <td valing="top" rowspan="2" style="margin-left: 2px; padding-left: 8px; padding-right: 8px; vertical-align: top; padding-top: 15px;" align="left">
		<div id="main">
			<div id="spinner" style="display: none; float: right;">
				<?php echo $html->image('spinner.gif'); ?>
			</div>
			<div id="content">
				<?php echo $content_for_layout; ?>
			</div>
		</div>
	</td>
      <td valign="top" width="30" class="menu-der"><?php echo $html->image( 'fond_arriba_der.png', array( 'width' => 199 ) ); ?><?php echo $this->renderElement( 'publicidades' ); ?></td>
    </tr>
    <tr>
	<td valign="bottom" width="30" heigth="18" class="menu-izq"><?php echo $html->image( 'fond_abajo_izq.png', array( 'width' => 146 ) ); ?></td>
	<td valign="bottom" width="30" heigth="18" class="menu-der"><?php echo $html->image( 'fond_abajo_der.png', array( 'width' => 199 ) ); ?></td>
    </tr>
    <tr><td colspan="3">&nbsp;</td></tr>
    <tr class="menu-abajo">
      <td colspan="3" class="menu-abajo-item">
		<?php echo $html->image( 'liga.png', array( 'url' => '/pages/la_liga' ) ); ?>
		<?php echo $html->image( 'separador.png' ); ?>
		<?php echo $html->image( 'torneo.png', array( 'url' => '/torneos' ) ); ?> 
		<?php echo $html->image( 'separador.png' ); ?>
		<?php echo $html->image( 'inscripciones.png', array( 'url' => '/inscripciones' ) ); ?>
		<?php echo $html->image( 'separador.png' ); ?>
		<?php echo $html->image( 'ubicacion.png', array( 'url' => '/pages/construccion' ) ); ?>
		<?php echo $html->image( 'separador.png' ); ?>
		<?php echo $html->image( 'sponsors.png', array( 'url' => '/pages/sponsors' ) ); ?>
		<?php echo $html->image( 'separador.png' ); ?>
		<?php echo $html->image( 'contactos.png', array( 'url' => '/pages/contacto' ) ); ?>
	</td>
    </tr>
    <tr>
      <td colspan="3" class="pie"><?php echo $html->link( 'www.lafintafutbol.com.ar', '/' ); ?> :: copyright 2009 :: dise&ntilde;o: <?php echo $html->link( "coudannesADV", 'http://www.coudannesadv.com.ar/' );?>/<?php echo $html->link( 'BScomputacion', 'http://www.bscomputacion.com/' ); ?></td>
    </tr>
    <tr>
      <td colspan="3" class="pie">
		<hr />
			<script type="text/javascript"><!--
			google_ad_client = "pub-1880233918301202";
			/* horizontal mi musica */
			google_ad_slot = "6225035208";
			google_ad_width = 468;
			google_ad_height = 15;
			//-->
			</script>
			<script type="text/javascript"
			src="http://pagead2.googlesyndication.com/pagead/show_ads.js">
			</script>
      </td>
    </tr>
  </tbody>
</table>
</div>
</body>
</html>