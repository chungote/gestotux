<?php $this->pageTitle = "..:: Galeria por fechas - La Finta Futbol ::.."; ?>
<center><?php echo $html->image( 'titulo_fotos.png' ); ?></center>
<h1>Fechas del <?php echo $nombre_torneo; ?></h1><hr>
<?php echo $html->image( 'boton_fotos_torneo.png', array( 'alt' => "Ver fotos de ".$nombre_torneo, 'border' => 0, 'url' => '/fotos/galeria/torneo/'.$id_torneo ) ); ?><br /><br />
<table width="100%" cellspacing="2" border="0" cellpadding="0" align="center">
  <tbody>
    <tr>
<?php
$cuenta_foto = 0; $class = 1;
foreach( $fechas as $fecha )
{
 //pr( $fecha );
 if( $cuenta_foto >= 3 )
 {
  echo "</tr><tr>";
  $cuenta_foto = 0;
  if( $class == "1" ) { $class = "2"; } else { $class = "1"; }
 }
  if( !isset( $fecha['FotoFecha']['archivo'] ) )
  {
	$fecha['FotoFecha']['archivo'] = IMAGES_URL. 'sinfoto.png';
  }
  echo "<td align=\"center\" class=\"textosombra".$class."\">" .
	$html->image(
		$thumbnail->direccion(
			array( 'src' => $fecha['FotoFecha']['archivo'],
				 'w' => 140 ) ),
		 array( 'url' => '/fotos/galeria/fecha/'.$fecha['Fecha']['id_fecha'] )
	 ) .
	"<br />".
       $html->link( $fecha['Fecha']['name'], '/fotos/galeria/fecha/'.$fecha['Fecha']['id_fecha'], array( 'class' => 'titulo_galeria') ).
      "</td>";
	$cuenta_foto += 1;
}
?>
</tr></tbody></table>