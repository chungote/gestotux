<fb:wall>
 <fb:wallpost uid="<?php echo $datos['Saludos']['de']; ?>" t="<?php echo $datos['Saludos']['fecha']; ?>" >
  <fb:subtitle><?php echo $datos['Saludos']['titulo']; ?></fb:subtitle>
  <?php echo $datos['Saludos']['mensaje']; ?>
  <fb:wallpost-action href="http://apps.facebook.com/felizsabado/saludos/crear">Nuevo Saludo</fb:wallpost-action>
 <?php if( $datos['Saludos']['publicado'] == 0 ) { ?>
   <fb:wallpost-action href="http://apps.facebook.com/felizsabado/saludos/publicar/<?php echo $datos['Saludos']['de'] . '/' . $datos['Saludos']['para'] . '/' . $datos['Saludos']['fecha']; ?>" >Publicar en mi muro</fb:wallpost-action>
 <?php } if( $datos['Saludos']['devuelto'] == null ) { ?>
   <fb:wallpost-action href="http://apps.facebook.com/felizsabado/saludos/devolver/<?php echo $datos['Saludos']['de']. '/' . $datos['Saludos']['para'] . '/' . $datos['Saludos']['fecha']; ?>" >Devolver Saludo</fb:wallpost-action>
 <?php } if( $datos['Saludos']['visto'] == 0 ) { ?>
   <fb:wallpost-action href="http://apps.facebook.com/felizsabado/saludos/marcarvisto/<?php echo $datos['Saludos']['de'] . '/' . $datos['Saludos']['para'] . '/' . $datos['Saludos']['fecha']; ?>" >Marcar como visto</fb:wallpost-action>
 <?php } ?>
  <fb:wallpost-action href="http://apps.facebook.com/felizsabado/saludos/eliminar/<?php echo $datos['Saludos']['de'] . '/' . $datos['Saludos']['para'] . '/' . $datos['Saludos']['fecha']; ?>" >Eliminar</fb:wallpost-action>
 </fb:wallpost>
</fb:wall>