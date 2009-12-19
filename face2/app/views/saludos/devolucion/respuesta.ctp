<fb:wall>
 <fb:wallpost uid="<? echo $destinatario; ?>" >
 <b> Devolviendo el saludo!</b> <br /> Ingresa el mensaje que queres enviarle.
<fb:editor action="http://apps.facebook.com/felizsabado/saludos/devolver_imagen" labelwidth="100">
 <fb:editor-text label="Titulo" name="titulo" value=""/>
 <fb:editor-textarea label="Mensaje" name="texto"/>
 <input type="hidden" name="destinatario" value="<?php echo $destinatario; ?>" />
 <input type="hidden" name="de_anterior" value="<?php echo $de_anterior; ?>" />
 <input type="hidden" name="para_anterior" value="<?php echo $para_anterior; ?>" />
 <input type="hidden" name="fecha_anterior" value="<?php echo $fecha_anterior; ?>" />
 <fb:editor-buttonset>
    <fb:editor-button value="Enviar"/>
  <fb:editor-cancel />
 </fb:editor-buttonset>
</fb:editor>

</fb:wall>