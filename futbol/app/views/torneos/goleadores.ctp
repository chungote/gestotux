<?php $this->pageTitle = "..:: Goleadores - LaFintaFutbol ::.."; ?>
<?php if( sizeof( $datos ) <= 0 ) { ?>
<span>No existen goleadores definidos para este torneo y zona</span>
<?php }  else   {  ?>
<table class="tabla_sancionados">
 <tbody>
<?php
echo $html->tableHeaders(
			array(
				$html->image( 'goleadores_jugador.png' ),
				$html->image( 'goleadores_equipo.png' ),
				$html->image( 'goleadores_goles.png' ) ), array( 'class' => 'tabla_sancionados' ) );
foreach( $datos as $dato )
{
 echo $html->tableCells(
		array(
			 array(
				 array( $dato['nombre'], array( 'align' => 'center' ) ),
				 array( $dato['equipo'], array( 'align' => 'center' ) ),
				 array( $dato['goles'], array( 'align' => 'center' ) ) 
			)
		), array( 'class' => 'textosombra1' )
	 );
}
?>
 </tbody>
</table>
<?php } ?>