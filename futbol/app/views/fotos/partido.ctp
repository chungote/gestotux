<?php $this->pageTitle = "..:: Fotos del partido -  La Finta Futbol ::.."; ?>
<center><?php echo $html->image( 'titulo_fotos.png' ); ?></center>
<!-- Muestra las fotos de un torneo mas un link para verlas por fechas -->
<h1>Fotos del <?php echo $partido['Equipo1']['nombre'] .
          " vs " .
          $partido['Equipo2']['nombre'] .
          " el " .
          date( 'd/m/y H:i', strtotime( $partido['Partido']['fecha_jugar'] ) );
     ?></h1><hr>
<?php echo $html->image( 'boton_verxpartido.png', array( 'alt' => "Ver fotos por partidos", 'border' => 0, 'url' => '/fotos/galeria/partidosfechas/'.$partido['Partido']['fecha_id'] ) ); ?>
<table width="100%" cellspacing="2" border="0" cellpadding="0" align="center">
  <tbody>
    <tr>
<?php
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
  </tbody>
</table>