<fb:header>Elegir Amigos</fb:header>
<script>
<!--
function permiso() {
 Facebook.showPermissionDialog( 'publish_stream,read_stream' );
}
//-->
</script>
<?php if( $tiene_permiso == false ) { ?>
<script>
<!--
permiso();
//-->
</script>
<?php } ?>

<fb:request-form action="http://apps.facebook.com/felizsabado/saludos/enviar"
                 method="POST"
                 invite="false"
                 type="Feliz Sabado"
                 content="<?php echo $contenido."    ".htmlentities("<fb:req-choice url=\"http://apps.facebook.com/felizsabado/saludos/recibido/".$enviante."\" label=\"Aceptar\" /> "); ?> ">
 <INPUT type="hidden" name="contenido" value="<?php echo $contenido; ?>">
 <INPUT type="hidden" name="titulo" value="<?php echo $titulo; ?>">
 <INPUT type="hidden" name="imagen_id" value="<?php echo $id_imagen; ?>" >
 <fb:multi-friend-selector showborder="true"
				   actiontext="Enviar saludo a los siguientes amigos."
				   email_invite="false"
				   bypass="cancel"
				   max="35"
				   exclude_ids="<?php echo implode(',', $excluir_ids ); ?> ">
</fb:request-form>