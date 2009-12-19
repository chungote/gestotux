<fb:explanation>
 <fb:message>Como crear un nuevo saludo de feliz sabado</fb:message>
 Para crear un nuevo saludo de feliz sabado,escribe el mensaje que deseas enviar.
</fb:explanation>
<?php if( $id_imagen == null ) { ?>
<fb:editor action="http://apps.facebook.com/felizsabado/saludos/imagen" labelwidth="100">
<?php } else { ?>
<fb:editor action="http://apps.facebook.com/felizsabado/saludos/amigos" labelwidth="100">
 <input type="hidden" value="<?php echo $id_imagen; ?>" name="imagen_id" />
<?php } ?>
 <fb:editor-text label="Titulo" name="titulo" value=""/>
 <fb:editor-textarea label="Mensaje" name="texto"/>
 <fb:editor-buttonset>
    <fb:editor-button value="Siguiente"/>
  <fb:editor-cancel />
 </fb:editor-buttonset>
</fb:editor>