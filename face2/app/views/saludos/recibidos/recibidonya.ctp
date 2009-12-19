<fb:wall>
<?php
foreach( $saludosNuevos as $saludo ) {
?>
 <fb:wallpost uid="<?php echo $saludo['Saludos']['de']; ?>" t="<?php echo $saludo['Saludos']['fecha']; ?>">
   <fb:title><?php echo $saludo['Saludos']['titulo']; ?></fb:title>
   <?php echo $saludo['Saludos']['mensaje']; ?>
   <fb:wallpost-action href="http://apps.facebook.com/felizsabado/saludos/vercompleto/<?php echo $saludo['Saludos']['de'] . '/' . $saludo['Saludos']['para'] . '/' . $saludo['Saludos']['fecha']; ?>" >Ver saludo completo</fb:wallpost-action>
   <fb:wallpost-action href="http://apps.facebook.com/felizsabado/saludos/publicar/<?php echo $saludo['Saludos']['de'] . '/' . $saludo['Saludos']['para'] . '/' . $saludo['Saludos']['fecha']; ?>" >Publicar en mi muro</fb:wallpost-action>
   <fb:wallpost-action href="http://apps.facebook.com/felizsabado/saludos/devolver/<?php echo $saludo['Saludos']['de']; ?>" >Devolver Saludo</fb:wallpost-action>
   <fb:wallpost-action href="http://apps.facebook.com/felizsabado/saludos/marcarvisto/<?php echo $saludo['Saludos']['de'] . '/' . $saludo['Saludos']['para'] . '/' . $saludo['Saludos']['fecha']; ?>" >Marcar como visto</fb:wallpost-action>
   <fb:wallpost-action href="http://apps.facebook.com/felizsabado/saludos/eliminar/<?php echo $saludo['Saludos']['de'] . '/' . $saludo['Saludos']['para'] . '/' .  $saludo['Saludos']['fecha']; ?>" >Eliminar</fb:wallpost-action>
 </fb:wallpost>
<?php
}
?>
</fb:wall>
<!--
<div style="position: relative; overflow: hidden">
 <div class="feed-tag">
   <div class="feed-tag-main">
     <div class="feed-tag-main-item">
       <div class="newsfeed_header clearfix">
         <h2>Saludos anteriores</h2>
<?php
if( sizeof( $saludosAnteriores ) <= 0 ) {
?>
         <div class="newsfeed_no_stories">No hay saludos anteriores</div>
<?php
} else  {

 //foreach( $saludosAnteriores as $saludo ) {
?>
<div class="newsfeed">
 <div>
  contenido
</div>
<?php
 // }
}
?>
      </div>
    </div>
  </div>
 </div>
</div>
-->