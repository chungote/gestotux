<fb:request-form action="http://apps.facebook.com/felizsabado/saludos/enviado_devolucion" method="POST" invite="false" type="Feliz Sabado"
     content="<?php echo $texto; echo htmlentities("<fb:req-choice label=\"Aceptar\" url=\"http://apps.facebook.com/felizsabado/saludos/recibido/".$enviante."/>" ); ?>" >
 <fb:wall>
  <fb:wallpost uid="<?php echo $destinatario; ?>" >
	<b>Enviar Mensaje:</b><br />
      <h3><?php echo $titulo; ?></h3><br />
	<?php if( $id_imagen !=null ) { ?>
		<img src="<?php echo $html->url( $ruta_imagen, true ); ?>" alt="" /><br /><br />
		<center><span style="font-style: italic;"><?php echo $texto_imagen; ?></span></center>
	<?php } ?>
      <?php echo $texto; ?>
 </fb:wall>
 <INPUT type="hidden" name="texto" value="<?php echo $texto; ?>" />
 <INPUT type="hidden" name="titulo" value="<?php echo $titulo; ?>" />
 <input type="hidden" name="destinatario" value="<?php echo $destinatario; ?>" />
 <input type="hidden" name="para_anterior" value="<?php echo $para_anterior; ?>" />
 <input type="hidden" name="de_anterior" value="<?php echo $de_anterior; ?>" />
 <input type="hidden" name="fecha_anterior" value="<?php echo $fecha_anterior; ?>" />
 <input type="hidden" name="id_imagen" value="<?php echo $id_imagen; ?>" />

 <fb:request-form-submit uid="<?php echo $destinatario; ?>" />
</fb:request-form>