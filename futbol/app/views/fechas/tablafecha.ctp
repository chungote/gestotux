<table width="100%" cellspacing="0" border="0" cellpadding="3" align="center">
 <tbody>
<?php
echo $html->tableHeaders( array( $html->image( 'tpos_pos.png'),
					   $html->image( 'tpos_equipo.png'),
					   $html->image( 'tpos_ptos.png' ),
					   $html->image( 'tpos_pj.png'),
					   $html->image( 'tpos_pg.png'),
					   $html->image( 'tpos_pp.png'),
					   $html->image( 'tpos_pe.png'),
					   $html->image( 'tpos_gf.png'),
					   $html->image( 'tpos_gc.png'),
					   $html->image( 'tpos_dg.png') ) );
if( isset( $tabla ) ) {
$posicion = 1;
foreach( $tabla as $item )
{
 echo $html->tableCells( array( array(
				array( $posicion, array( 'align' => 'center' ) ),
				$equipos[$item['id_equipo']],
				array( $item['puntos'], array( 'align' => 'center' ) ),
				array( $item['partidos_jugados'], array( 'align' => 'center' ) ),
				array( $item['partidos_ganados'], array( 'align' => 'center' ) ),
				array( $item['partidos_perdidos'], array( 'align' => 'center' ) ),
				array( $item['partidos_empatados'], array( 'align' => 'center' ) ),
				array( $item['goles_favor'], array( 'align' => 'center' ) ),
				array( $item['goles_contra'], array( 'align' => 'center' ) ),
				array( $item['goles_favor']-$item['goles_contra'], array( 'align' => 'center' ) ) ) ), array( 'class' => 'textosombra1' ) );
 $posicion++;
 }
}
else
{
 echo $html->tableCells( array( array( array( 'No existen partidos definidos todavia, no se puede calcular la posicion' ), array( 'colspan' => 5 ) ) ) );
}
?>
 </tbody>
</table>