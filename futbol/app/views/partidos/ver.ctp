<?php //pr( $partido ); ?>
<table width="100%" cellspacing="0" border="0" cellpadding="2" align="center">
  <tbody>
    <tr>
     <td colspan="4"><?php echo "<center>" . $html->image( 'titulo_partido.png', array( 'border' => 0, 'align' => 'center', 'width' => 400 ) ) . "</center>"; ?></td>
    </tr>
    <tr>
      <td align="right" colspan="2"><b><?php echo $partido['Equipo1']['nombre']; ?></b></td>
      <td align="center">vs</td>
      <td align="left" colspan="1"><b><?php echo $partido['Equipo2']['nombre']; ?></b></td>
    </tr>
<?php unset( $partido['Equipo1'] ); unset( $partido['Equipo2'] ); ?>
    <tr>
      <td><?php echo $html->image( 'partido_resultados.png' ); ?></td>
      <td align="right"><?php echo $partido['Partido']['resultado_equipo_1']; ?></td>
      <td align="center" valign="middle"> - </td>
      <td align="left" colspan="1"><?php echo $partido['Partido']['resultado_equipo_2']; ?></td>
    </tr>
    <tr>
      <td><?php echo $html->image( 'partido_fecha.png' ); ?></td>
      <td colspan="3"><?php echo $partido['Fecha']['name']; ?></td>
   </tr>
   <tr>
      <TD><?php echo $html->image( 'partido_fechas.png' ); ?></TD>
      <td colspan="3"><?php echo date( 'd/m/y', strtotime( $partido['Partido']['fecha_jugar'] ) ); ?></td>
    </tr>
   <tr>
      <TD><?php echo $html->image( 'partido_cancha.png' ); ?></TD>
      <td colspan="3"><?php echo $partido['Partido']['cancha']; ?></td>
    </tr>
   <tr>
      <TD><?php echo $html->image( 'partido_zona.png' ); ?></TD>
      <td colspan="3"><?php echo $partido['Zona']['nombre_zona']; ?></td>
    </tr>
    <tr>
      <td colspan="4"><?php echo $html->image( 'partido_goleadores.png' ); ?></td>
    </tr>
<?php
// Muestro los goleadores
$a1 = array(); $a2 = array();
foreach( $partido['Goleador'] as $goleador )
{
 if( $goleador['equipo_id'] == $partido['Partido']['id_equipo_1'] )
 { $a1[] = $goleador; }
 else
 { $a2[] = $goleador; }
}
// Genero las celdas
$max = max( sizeof($a1), sizeof($a2) );
$filas = array();
for( $i=0; $i<$max; $i++ )
{
  $col = array( '' );
  if( array_key_exists($i, $a1) )
  {
	if( $a1[$i]['minuto'] == 0 ) {
		$col[] = $a1[$i]['nombre'];
	} else {
		$col[] = $a1[$i]['nombre'].' ('.$a1[$i]['minuto'].'\')';
	}
  } else { $col[] = ''; }
  $col[] = '';
  if( array_key_exists($i, $a2) )
  {
   	if( $a2[$i]['minuto'] == 0 ) {
		$col[] = $a2[$i]['nombre'];
	} else {
		$col[] = $a2[$i]['nombre'].' ('.$a2[$i]['minuto'].'\')';
	}
  } else { $col[] = ''; }
  $filas[] = $col;
}
echo $html->tableCells( $filas );
?>
    <tr>
      <td colspan="4"><?php echo $html->image( 'partido_amonestados.png' ); ?></td>
    </tr>
<?php
// Muestro los goleadores
$a1 = array(); $a2 = array();
foreach( $partido['Amonestado'] as $amonestado )
{
 if( $amonestado['equipo_id'] == $partido['Partido']['id_equipo_1'] )
 { $a1[] = $amonestado; }
 else
 { $a2[] = $amonestado; }
}
// Genero las celdas
$max = max( sizeof($a1), sizeof($a2) );
$filas = array();
for( $i=0; $i<$max; $i++ )
{
  $col = array( '' );
  if( array_key_exists($i, $a1) )
  {
	$col[] = $a1[$i]['nombre_jugador'];
  } else { $col[] = ''; }
  $col[] = '';
  if( array_key_exists($i, $a2) )
  {
   	$col[] = $a2[$i]['nombre_jugador'];
  } else { $col[] = ''; }
  $filas[] = $col;
}
echo $html->tableCells( $filas );
?>
    <tr>
      <td colspan="4"><?php echo $html->image( 'partido_sancionados.png' ); ?></td>
    </tr>
<?php
// Muestro los Sancionados
$a1 = array(); $a2 = array();
foreach( $partido['Sancionado'] as $sancionado )
{
 if( $sancionado['equipo_id'] == $partido['Partido']['id_equipo_1'] )
 { $a1[] = $sancionado; }
 else
 { $a2[] = $sancionado; }
}
// Genero las celdas
$max = max( sizeof($a1), sizeof($a2) );
$filas = array();
for( $i=0; $i<$max; $i++ )
{
  $col = array( '' );
  if( array_key_exists($i, $a1) )
  {
   $col[] = $a1[$i]['nombre_jugador']/*.'<br />'.$a1[$i]['TipoSancion']['nombre']*/;
  } else { $col[] = ''; }
  $col[] = '';
  if( array_key_exists($i, $a2) )
  {
   $col[] = $a2[$i]['nombre_jugador']/*.'<br />'.$a2[$i]['TipoSancion']['nombre']*/;
  } else { $col[] = ''; }
  $filas[] = $col;
}
echo $html->tableCells( $filas );
if( sizeof( $partido['Fotos'] ) > 0  ) {
?>
    <tr>
      <td colspan="4"><?php echo $html->image( 'partido_fotos.png' ); ?></td>
    </tr>

    <tr>
      <td colspan="4">
<table width="100%" cellspacing="0" border="0" cellpadding="3" align="center">
 <tbody>
<?php
/// Fotos
$min = min( 3, sizeof( $partido['Fotos'] ) );
for( $i=0; $i<$min; $i++ )
{
 echo "<td>";
  echo $lightbox->img(
		$thumbnail->direccion( array( 'src' => $partido['Fotos'][$i]['archivo'], 'w' => 140 ) ),
		'/'.$partido['Fotos'][$i]['archivo'],
		$partido['Fotos'][$i]['titulo'] );
  echo "</td>";
 }
?>
 </tbody>
</table>
      </td>
    </tr>
    <tr>
     <td colspan="4" align="right" valign="baseline"><?php echo $html->image( 'partido_vertodagaleria.png', array( 'alt' => 'Ver toda la galeria del partido', 'url' => '/fotos/galeria/partido/'.$partido['Partido']['id_partido'] ) ); ?></td>
    </tr>
<? } ?>
  </tbody>
</table>
<hr>
<div align="right"><?php echo $html->image( 'partido_volverresultados.png', array( 'alt' => 'Volver a resultados', 'url' => '/partidos/resultados/fecha/'.$partido['Partido']['fecha_id'] ) ); ?></div>