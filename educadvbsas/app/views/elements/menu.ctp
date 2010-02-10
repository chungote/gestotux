<?php
/*
   /////////////////////////////////////////////////////////////////////////////////////
   // Realiza la función del menu en la pagina, tanto el principal como el de cada colegio
   /////////////////////////////////////////////////////////////////////////////////////
*/

// Busco los items de la base de datos??
// Veo si estoy en el menu principal o en el de los colegios
//pr( $this );
?>
<table id="menuprincipal" width="736" border="0" class="menu">
	<tr>
		<td id="espacio">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
		<td id="inicio"><?php echo $html->link(  'Inicio', '/', array( 'class' => "menuItem" ) ); ?></td>
		<td id="quienes"><?php echo $html->link(  'Quienes Somos', '/pages/quienes', array( 'class' => "menuItem" ) ); ?></td>
		<td id="colegios"><?php echo $html->link(  'Colegios', '/colegios', array( 'class' => "menuItem" ) ); ?></td>
		<td id="eventos"><?php echo $html->link(  'Eventos', '/eventos', array( 'class' => "menuItem" ) ); ?></td>
		<td id="galeria"><?php echo $html->link(  'Galería de Fotos', '/galeria', array( 'class' => "menuItem" ) ); ?></td>
		<!--<td><a href="#" class="menuItem">Trabaja con Nosotros</a></td>//-->
		<td id="contacto"><?php echo $html->link(  'Contacto', '/pages/contacto', array( 'class' => "menuItem" ) ); ?></td>
	</tr>
</table>