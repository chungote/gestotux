<table width="100%" cellspacing="0" cellpadding="3"  class="tabla_sancionados">
 <tbody>
<?php
echo $html->tableHeaders( array( $html->image( 'proxfecha_equipo.png' ),
					   ' ',
					   $html->image( 'proxfecha_equipo.png' ),
					   $html->image( 'proxfecha_hora.png' ),
					   $html->image( 'proxfecha_cancha.png' ) ) );
if( sizeof( $partidos ) > 0 ) {
foreach( $partidos as $partido )
{
 //pr( $partido );
 echo $html->tableCells(
		array(
			array(
				array( $partido['Equipo1']['nombre'], array( 'align' => 'right' ) ),
				array( " vs ", array( 'align' => 'center' ) ),
				array( $partido['Equipo2']['nombre'], array( 'align' => 'left' ) ),
				date( 'd/m/Y G:i', strtotime( $partido['Partido']['fecha_jugar'] ) ),
				array( $partido['Partido']['cancha'], array( 'align' => 'center' ) )
			) ), array( 'class' => 'textosombra1' ) );
}
}
?>
 </tbody>
</table>