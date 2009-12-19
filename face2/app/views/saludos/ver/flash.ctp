<fb:wall>
 <fb:wallpost uid="<?php echo $datos['Saludos']['de']; ?>"></fb:wallpost>
  <fb:subtitle><?php echo $datos['Saludos']['titulo'];?></fb:subtitle>
  <?php echo $datos['Saludos']['mensaje']; ?><br />

	<fb:swf swfbgcolor="000000"
         imgstyle="border-width:3px; border-color:white;"
         swfsrc='<?php echo $datos['Imagenes']['ruta']; ?>'
         imgsrc='<?php echo $datos['Imagenes']['miniatura']; ?>'
         width='340'
         height='270' />
 <?php if( $datos['Saludos']['publicado'] == 0 ) { ?>
   <fb:wallpost-action href="http://apps.facebook.com/felizsabado/saludos/publicar/<?php echo $datos['Saludos']['de'] . '/' . $datos['Saludos']['para'] . '/' . $datos['Saludos']['fecha']; ?>" >Publicar en mi muro</fb:wallpost-action>
 <?php } if( $datos['Saludos']['devuelto'] == null ) { ?>
   <fb:wallpost-action href="http://apps.facebook.com/felizsabado/saludos/devolver/<?php echo $datos['Saludos']['de']. '/' . $datos['Saludos']['para'] . '/' . $datos['Saludos']['fecha']; ?>" >Devolver Saludo</fb:wallpost-action>
 <?php } if( $datos['Saludos']['visto'] == 0 ) { ?>
   <fb:wallpost-action href="http://apps.facebook.com/felizsabado/saludos/marcarvisto/<?php echo $datos['Saludos']['de'] . '/' . $datos['Saludos']['para'] . '/' . $datos['Saludos']['fecha']; ?>" >Marcar como visto</fb:wallpost-action>
 <?php } ?>
 </fb:wallpost>
</fb:wall>
<a href="http://apps.facebook.com/felizsabado/saludos/recibido/" >Volver a los mensajes recibidos</a>