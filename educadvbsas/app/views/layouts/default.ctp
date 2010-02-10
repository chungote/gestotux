<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<!-- Copyright 2008 MVG Consulting. All rights reserved. -->
	<?php echo $html->charset(); ?>
	<title><?php echo $title_for_layout; ?></title>
	<?php
	 echo $html->meta( 'icon' );
	 //echo $html->css( 'cake.generic' );
	 echo $html->css( 'estilos_local' );
	 echo $html->css( 'cal' );
	 echo $html->css( 'lightbox' );

	 echo $javascript->link( 'prototype' );
	 echo $javascript->link( 'fadeimages' );
	 echo $javascript->link( 'lightbox' );
	 echo $javascript->link( 'menu' );
	 echo $scripts_for_layout;
	?>
	<script type="text/javascript" src="<?php echo $this->webroot . 'js/'; ?>scriptaculous.js?load=effects,builder"></script>
	<style type="text/css">
	<!--
		.Estilo9 {font-size: small}
	-->
	</style>
	<script language="JavaScript" type="text/JavaScript">
	<!--
	function MM_jumpMenu(targ,selObj,restore){ //v3.0
	  eval(targ+".location='"+selObj.options[selObj.selectedIndex].value+"'");
	  if (restore) selObj.selectedIndex=0;
	}
	function MM_openBrWindow(theURL,winName,features) { //v2.0
	  window.open(theURL,winName,features);
	}
	//-->
	</script>
</head>
<body class= "twoColElsLtHdr" onload="inicializar()">
<div id="container">
	<div id="header">
		<?php echo $html->image( 'logocopia.jpg', array( 'width' => 736, 'height' => 90, 'alt' => "Escuelas Adventistas - ABo" ) ); ?>
	</div>
	<?php echo $this->element( 'rotacion_superior' ); ?>
	<?php echo $this->element( 'menu' ); ?>
	<table width="736" border="0">
		<tr>
			<?php if( $col_izq ) { ?>
			<!-- COLUMNA DERECHA -->
			<td width="153" valign="top">
				<table>
					<tr>
						<td>
							<?php echo $this->element( 'noticias' ); ?>
						</td>
						<td class="espacioIntermedio">&nbsp;</td>
						<td>
							<?php echo $this->element( 'ingreso' ); ?>
						</td>
					</td>
				</table>
			</td>
			<?php } ?>
			<!-- Separador -->
			<td width="10" class="fondo_seccion_izquierda">&nbsp;</td>
			<!-- Contenido -->
			<td align="center" valign="top">
				<?php echo $content_for_layout; ?>
			</td>
			<!-- Separador -->
			<td width="10" class="fondo_seccion_derecha">&nbsp;</td>
			<?php if( $col_der ) { ?>
			<!-- Columna Izquierda -->
			<td width="190" class="centrado">
				<table width="175">
					<tr>
						<td class="espacioInicial">&nbsp;</td>
					</tr>
					<?php echo "calendario";//hacerCalendario(); ?>
					<tr>
						<td class="espacioInicial">&nbsp;</td>
					</tr>
					<tr>
						<td><?php echo "donaciones"; ?></td>
					</tr>
					<tr>
						<td class="pieSeccionDerecha">&nbsp;</td>
					</tr>
				</table>
			</td>
			<?php } ?>
		</tr>
	</table>
	<div class="linea_doble_bordo" width="736" height="3">&nbsp;</div>
	<div class="pieDePagina">
		&copy; 2009 - Departamento de Educaci&oacute;n - Asociaci&oacute;n Bonaerense - Iglesia Adventista del 7mo. d&iacute;a &reg;
		<br>
		&copy; 2009 - MVG Consulting
	</div>
<?php echo $cakeDebug; ?>
</div>
</body>
</html>