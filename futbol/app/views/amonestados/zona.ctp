<table class="tabla_sancionados">
 <tbody>
<?php
echo $html->tableHeaders(
			array(
				$html->image( 'amonestados_cantidad.png' ),
				$html->image( 'amonestados_jugador.png' ),
				$html->image( 'amonestados_equipo.png' ) ), array( 'class' => 'tabla_sancionados' ) );
foreach( $amonestados as $amonestado )
{
 $amonestado['Amonestado']['cantidad'] = "";
 for( $i = 0; $i<$amonestado[0]['suma']; $i++ )
 { $amonestado['Amonestado']['cantidad'] .= $html->image( 'amarilla.png' ); }
 echo $html->tableCells(
		array(
			 array(
				 array( $amonestado['Amonestado']['cantidad'], array( 'align' => 'center' ) ),
				 array( $amonestado['Amonestado']['nombre_jugador'], array( 'align' => 'center' ) ),
				 array( $amonestado['Equipo']['nombre'], array( 'align' => 'center' ) )
			)
		), array( 'class' => 'textosombra1' )
	 );
}
?>
 </tbody>
</table>