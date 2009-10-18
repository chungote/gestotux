<br />
<?php
if( sizeof( $fotos) <= 0 )
{
return;
}
if( $portada == true )
{
 echo "<center>".$html->image( 'titulo_fotos.png' ) ."</center>";
}
?>
<table>
  <tbody>
    <tr>
<?php
foreach( $fotos as $foto )
{
	echo "<td>";
	echo $lightbox->img(
		$thumbnail->direccion( array( 'src' => $foto['Foto']['archivo'], 'w' => 140 ) ),
		'/futbol/'.$foto['Foto']['archivo'],
		$foto['Foto']['titulo'] );
	echo "</td>";
}
?>
    </tr>
<?php if( $portada == true ) { ?>
	<tr>
        <TD></TD>
	  <td></td>
	  <td><?php echo $html->image( 'ver_galeria.png', array( 'alt' => "Ver Galeria de Fotos", 'url' =>'/fotos/index' ) ); ?></td>
      </tr>
<?php } ?>
  </tbody>
</table>