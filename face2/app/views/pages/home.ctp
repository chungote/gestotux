<!-- Pagina de Canvas -->
<fb:title>Saludos de Feliz Sabado!</fb:title>
<?php
$noleidos = $this->requestAction( '/saludos/noleidos' );

if( $noleidos > 0 ) {
?>
Tienes <? echo $noleidos; ?> saludos recibidos que no has visto! <A href="http://apps.facebook.com/felizsabado/saludos/recibido">Ver ahora!</A>
<?php } ?>
<br />
Has enviado <? echo $this->requestAction( '/saludos/enviados' ); ?> saludos.

<?php echo  $this->requestAction( '/imagenes/ultimas_agregadas' ); ?>