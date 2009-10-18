<table width="100%" cellspacing="0" cellpadding="2" align="center"  class="tabla_sancionados">
 <tbody>
<?php
 echo $html->tableHeaders( array( $html->image( 'sancionados_equipo.png' ), ' ', $html->image( 'sancionados_equipo.png' ) ) );
if( sizeof( $partidos ) > 0 ) { 
$class = "1";
foreach( $partidos as $partido )
{
 unset( $partido['Sancionado'] ); unset( $partido['Fecha'] );
 echo $html->tableCells(
		array(
			array(
				array( $html->link( $partido['Equipo1']['nombre'], '/partidos/ver/'.$partido['Partido']['id_partido'] ), array( 'align' => 'right' ) ) ,
				array( $html->link( $partido['Partido']['resultado_equipo_1'] . " - " . $partido['Partido']['resultado_equipo_2'], '/partidos/ver/'.$partido['Partido']['id_partido'] ) , array( 'align' => 'center' ) ),
				array( $html->link( $partido['Equipo2']['nombre'], '/partidos/ver/'.$partido['Partido']['id_partido'] ), array( 'align' => 'left' ) )
			) ), array( 'class' => 'textosombra1' ) );
}
}
else
{
 echo $html->tableCells( array( array( 'No existen partidos con resultados' ) ) );
}
?>
 </tbody>
</table>