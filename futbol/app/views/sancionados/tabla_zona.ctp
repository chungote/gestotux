<table class="tabla_sancionados">
 <tbody>
<?php
echo $html->tableHeaders(
			array(
				$html->image( 'sancionados_jugador.png' ),
				$html->image( 'sancionados_equipo.png' ),
				$html->image( 'sancionados_tipo.png' ),
				$html->image( 'sancionados_fecha.png' ) ), array( 'class' => 'tabla_sancionados' ) );
foreach( $sancionados as $sancionado )
{
 echo $html->tableCells(
		array(
			 array(
				 array( $sancionado['Sancionado']['nombre_jugador'], array( 'align' => 'center' ) ),
				 array( $sancionado['Equipo']['nombre'], array( 'align' => 'center' ) ),
				 array( $sancionado['TipoSancion']['nombre'], array( 'align' => 'center' ) ),
				 array( $sancionado['Sancionado']['quedan_fechas'], array( 'align' => 'center' ) )
			)
		), array( 'class' => 'textosombra1' )
	 );
}
?>
 </tbody>
</table>