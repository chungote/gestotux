<?php $this->pageTitle = "..:: Fotos de ".$nombre_fecha." -  La Finta Futbol ::.."; ?>
<!-- Muestra las fotos de un torneo mas un link para verlas por fechas -->
<center><?php echo $html->image( 'titulo_fotos.png' ); ?></center>
<h1><?php echo $nombre_fecha; ?></h1><hr>
<?php echo $html->image( 'boton_verxfecha.png', array( 'alt' => "Ver fotos por fecha", 'border' => 0, 'url' => '/fotos/galeria/fechas/'.$id_torneo ) ); ?>&nbsp;
<?php echo $html->image( 'boton_verxpartido.png', array( 'alt' => 'Ver fotos por partido', 'border' => 0, 'url' => '/fotos/galeria/partidos/'.$id_fecha ) ); ?><br />
<table width="100%" cellspacing="2" border="0" cellpadding="0" align="center">
  <tbody>
    <tr>
<?php
if( isset( $fotos ) ) {
$cuenta_foto = 0; $class = 1;
foreach( $fotos as $foto )
{
 if( $cuenta_foto >= 3 )
 {
  if( $class == "1" ) { $class = "2"; } else { $class = "1"; }
  echo "</tr><tr>";
  $cuenta_foto = 0;
 }
  echo "<td>";
  //pr( $foto );
  echo $lightbox->img(
		$thumbnail->direccion( array( 'src' => $foto['Foto']['archivo'], 'w' => 140 ) ),
		'/futbol/'.$foto['Foto']['archivo'],
		$foto['Foto']['titulo'] );
  echo "</td>";
  $cuenta_foto += 1;
}
?>
    <tr align="center" valign="baseline" bgcolor="lightGray">
      <td><?php echo $paginator->prev('<< Anterior'/*, null, '', array('class' => 'disabled')*/); ?></td>
      <td><?php echo $paginator->counter( array( 'format' => 'Pagina %page% de %pages%, %current% de %count%' ) ); ?></td>
      <td><?php echo $paginator->next('Siguiente >>'/*, null, '', array('class' => 'disabled')*/); ?></td>
    </tr>
<?php
}
else
{
 echo "<center>No existen fotos para esta fecha</center>";
}
?>
  </tbody>
</table>