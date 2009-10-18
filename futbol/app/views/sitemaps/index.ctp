<h1>Mapa del sitio</h1><hr>
<h4>Anuncios</h4>
<?php
foreach( $anuncios as $anuncio )
{
 echo $html->link( $anuncio['Anuncios']['titulo'], '/anuncios/ver/'.$anuncio['Anuncios']['id_anuncio'] );
}
?>
<h4>Fotos</h4>
<?php
foreach( $fotos as $foto )
{
 echo $html->link( $foto['Fotos']['titulo'], '/fotos/galeria/partido/'.$foto['Fotos']['partido_id'] );
}
?>