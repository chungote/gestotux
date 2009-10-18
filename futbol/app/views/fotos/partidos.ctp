<?php $this->pageTitle = "..:: Galeria por partidos de la ". $nombre_fecha . " - La Finta Futbol ::.."; ?>
<center><?php echo $html->image( 'titulo_fotos.png' ); ?></center>
<h1>Partido de la <?php echo $nombre_fecha; ?></h1><hr>
<?php echo $html->image( 'boton_verxfecha.png', array( 'alt' => "Ver fotos de ".$nombre_fecha, 'border' => 0, 'url' => '/fotos/galeria/fechas/'.$id_fecha ) ); ?>
<table width="100%" cellspacing="2" border="0" cellpadding="0" align="center">
  <tbody>
    <tr>
<?php
$cuenta_foto = 0; $class = 1;
foreach( $partidos as $partido )
{
 unset( $partido['Sancionado'] ); unset( $partido['Goleador'] ); unset( $partido['Fotos'] );
 //pr( $partido );
 if( $cuenta_foto >= 3 )
 {
  echo "</tr><tr>";
  $cuenta_foto = 0;
  if( $class == "1" ) { $class = "2"; } else { $class = "1"; }
 }
  if( !isset( $partido['FotoPartido']['archivo'] ) )
  {
	$partido['FotoPartido']['archivo'] = IMAGES_URL. 'sinfoto.png';
  }
  echo "<td align=\"center\" class=\"textosombra".$class."\">" .
	$html->image(
		$thumbnail->direccion(
			array( 'src' => $partido['FotoPartido']['archivo'],
				 'w' => 140 ) ),
		 array( 'url' => '/fotos/galeria/partido/'.$partido['Partido']['id_partido'] )
	 ) .
	"<br />".
       $html->link( $partido['Equipo1']['nombre'] . " vs " . $partido['Equipo2']['nombre'], '/fotos/galeria/partido/'.$partido['Partido']['id_partido'], array( 'class' => 'titulo_galeria') ).
      "</td>";
	$cuenta_foto += 1;
}
?>
</tr></tbody></table>