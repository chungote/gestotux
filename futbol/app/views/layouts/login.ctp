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
		echo $scripts_for_layout;
	?>
</head>
<div>
<div align="center" class="fondo-general">
<div class="separacion"></div>
<br /><br />
<table cellpadding="0" border="0" cellspacing="0" width="800" class="tabla-general">
  <tbody>
    <tr>
		<td colspan="7"><?php $session->flash(); ?></td>
    </tr>
    <tr>
		<td colspan="7"><?php echo $content_for_layout; ?></td>
    </tr>
    <tr>
      <td colspan="11" class="pie"><?php echo $html->link( 'www.lafintafutbol.com.ar', '/' ); ?> :: copyright 2009 :: dise&ntilde;o: <?php echo $html->link( "Coudannes adv", 'http://www.coudannesadv.com.ar/' );?> /<?php echo $html->link( 'bscomputacion', 'http://www.bscomputacion.com.ar/' ); ?></td>
    </tr>
  </tbody>
</table>
</div>
</body>
</html>