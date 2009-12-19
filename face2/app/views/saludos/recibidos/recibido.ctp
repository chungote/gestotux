<fb:title>Saludos recibidos recientemente</fb:title>
<?php
if( sizeof( $saludos ) <= 0 ) {
?>
 <fb:explanation>
  <fb:message>No tienes mensajes de feliz sabado recibidos</fb:message>
  No tenemos ningun mensaje recidido para vos en nuestro sistema.
 </fb:explanation>
<?php
} else {

foreach( $saludos as $saludo ) {
?>
<table width="100%" cellspacing="8" cellpadding="2" border="0">
  <tbody>
    <tr>
      <td rowspan="3" valign="top"><fb:profile-pic uid="<?php echo $saludo['Saludos']['de'];?>" linked="false" size="square" /></td>
      <td colspan="2"><fb:name uid="<?php echo $saludo['Saludos']['de'];?>" linked="true" /> te envio un <b><?php echo $saludo['Saludos']['titulo']; ?></b></td>
    </tr>
    <tr>
      <td rowspan="2"><a href="http://apps.facebook.com/felizsabado/saludos/vercompleto/<?php echo $saludo['Saludos']['de'] . '/' . $saludo['Saludos']['para'] . '/' . $saludo['Saludos']['fecha']; ?>" ><img src="<?php echo $html->url( $saludo['Imagenes']['miniatura'], true ); ?>" alt="Ver saludo" /></a></td>
      <td><?php echo $saludo['Saludos']['mensaje']; ?><br /><br /><br /><SPAN style="font-style : italic;"><?php echo $saludo['Imagenes']['texto']; ?></SPAN></td>
    </tr>
    <tr>
      <td></td>
    </tr>
    <tr>
      <td colspan="2">&nbsp;</td>
      <td>
	<?php if( $saludo['Saludos']['imagenes_id'] != null ) { ?>
	  <a href="http://apps.facebook.com/felizsabado/saludos/vercompleto/<?php echo $saludo['Saludos']['de'] . '/' . $saludo['Saludos']['para'] . '/' . $saludo['Saludos']['fecha']; ?>" >Ver saludo completo</a>
	<?php } if( $saludo['Saludos']['publicado'] == 0 ) { ?>
	 - <a href="http://apps.facebook.com/felizsabado/saludos/publicar/<?php echo $saludo['Saludos']['de'] . '/' . $saludo['Saludos']['para'] . '/' . $saludo['Saludos']['fecha']; ?>" >Publicar en mi muro</a>
	<?php } if( $saludo['Saludos']['devuelto'] == null ) { ?>
	   - <a href="http://apps.facebook.com/felizsabado/saludos/devolver/<?php echo $saludo['Saludos']['de']. '/' . $saludo['Saludos']['para'] . '/' . $saludo['Saludos']['fecha']; ?>" >Devolver Saludo</a>
	<?php } if( $saludo['Saludos']['visto'] == 0 ) { ?>
	  - <a href="http://apps.facebook.com/felizsabado/saludos/marcarvisto/<?php echo $saludo['Saludos']['de'] . '/' . $saludo['Saludos']['para'] . '/' . $saludo['Saludos']['fecha']; ?>" >Marcar como visto</a>
	<?php } ?>
	  - <a href="http://apps.facebook.com/felizsabado/saludos/eliminar/<?php echo $saludo['Saludos']['de'] . '/' . $saludo['Saludos']['para'] . '/' .  $saludo['Saludos']['fecha']; ?>" >Eliminar</a>
	</td>
    </tr>
  </tbody>
</table>
<hr />

<?php }

} ?>