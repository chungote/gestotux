<!-- Muestra las fotos de un torneo mas un link para verlas por fechas -->
<?php $this->pageTitle = "..:: Fotos - ". $nombre_torneo. " - La Finta Futbol ::.."; ?>
<center><?php echo $html->image( 'titulo_fotos.png' ); ?></center>
<h2><?php echo $nombre_torneo; ?></h2>
<div><?php echo $html->image( 'boton_verxfecha.png', array( 'alt' => "Ver por fechas", 'url' => '/fotos/galeria/fechas/'.$id_torneo  ) ); ?></div><br />
<table width="100%" cellspacing="2" border="0" cellpadding="0" align="center" style="border-bottom-color : #59b034; border-bottom-style : solid; border-bottom-width : 2px; border-collapse : separate; border-left-color : #59b034; border-left-style : solid; border-left-width : 2px; border-right-color : #59b034; border-right-style : solid; border-right-width : 2px; border-spacing : 1px 0px; border-top-color : #59b034; border-top-style : solid; border-top-width : 2px;">
  <tbody>
    <tr>
<?php
//pr( $fotos );
$cuenta_foto = 0; $class = 1;
foreach( $fotos as $foto )
{
 if( $cuenta_foto >= 3 )
 {
  echo "</tr><tr>";
  if( $class == "1" ) { $class = "2"; } else { $class = "1"; }
  $cuenta_foto = 0;
 }
  echo "<td class=\"textosombra".$class."\" align=\"center\">";
  echo $lightbox->img(
		$thumbnail->direccion( array( 'src' => $foto['Foto']['archivo'], 'w' => 140 ) ),
		'/'.$foto['Foto']['archivo'],
		$foto['Foto']['titulo'] );
  echo "</td>";
  $cuenta_foto += 1;
}
// pr( $this->passedArgs );
$paginator->options( array( 'url' => $this->passedArgs ) );
?>
   <tr><TD colspan="3"></TD></tr>
    <tr align="center" valign="baseline" bgcolor="lightGray">
      <td><?php echo $paginator->prev('<< Anterior'/*, null, '', array('class' => 'disabled')*/); ?></td>
      <td><?php echo $paginator->counter( array( 'format' => 'Pagina %page% de %pages%, %current% de %count%' ) ); ?></td>
      <td><?php echo $paginator->next('Siguiente >>'/*, null, '', array('class' => 'disabled')*/); ?></td>
    </tr>
  </tbody>
</table>