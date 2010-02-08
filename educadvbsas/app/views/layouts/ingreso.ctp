<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<!-- Copyright 2008 MVG Consulting. All rights reserved. -->
	<?php echo $html->charset(); ?>
	<title><?php echo $title_for_layout; ?></title>
	<?php
	 echo $html->meta( 'icon' );
	 echo $html->css( 'estilos_local' );
	 echo $scripts_for_layout;
	?>
</head>
<body class= "twoColElsLtHdr">
<div id="container">
	<div id="header">
		<?php echo $html->image( 'logocopia.jpg', array( 'width' => 736, 'height' => 90, 'alt' => "Escuelas Adventistas - ABo" ) ); ?>
	</div>
	<table width="736" border="0">
		<tr>
			<!-- Separador -->
			<td width="10" class="fondo_seccion_izquierda">&nbsp;</td>
			<!-- Contenido -->
			<td align="center" valign="top">
				<?php echo $content_for_layout; ?>
			</td>
			<!-- Separador -->
			<td width="10" class="fondo_seccion_derecha">&nbsp;</td>
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