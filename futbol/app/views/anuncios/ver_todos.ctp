<?php $this->pageTitle = "..:: Anuncios - La Finta Futbol ::.."; ?>
<?php echo $html->image( 'titulo_anuncios.png', array( 'width' => 400 ) ); ?>
<p align="left" style="font-size : x-small;">Haga click sobre el anuncio que desea ver.</p>
<table width="100%" cellspacing="0" cellpadding="0">
<?php
echo $html->tableHeaders( array( 'Titulo', 'Fecha', 'Lecturas' ) );
foreach( $anuncios as $anuncio )
{
 echo $html->tableCells( array( array(
		$html->link( $anuncio['Anuncio']['titulo'], '/anuncios/ver/'.$anuncio['Anuncio']['id_anuncio'] ),
		$anuncio['Anuncio']['modified'],
		$anuncio['Anuncio']['veces_visto'] ) ) );
}
?>
</table>