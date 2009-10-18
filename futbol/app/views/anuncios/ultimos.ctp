<?php if( sizeof( $anuncios )> 0  ) { ?>
<br /><center><?php echo $html->image( 'titulo_ultimosanuncios.png' ); ?></center>
<?php
foreach( $anuncios as $anuncio )
{
 echo $html->div( 'anuncio',
 "<h2>".$html->image( 'anuncio.png' ).$anuncio['Anuncio']['titulo']."</h2>"
 . /*mb_substr(*/ $anuncio['Anuncio']['contenido']/*, 0, 60 )*/ . '<br />'
  , array( 'width' => '100%'  ) ); //fin div
}
echo $html->para( null, $html->image( 'ver_avisos.png', array( 'alt' => 'Ver todos los avisos', 'url' => '/anuncios/ver_todos', 'align' => 'right' ) ) );
}
?>