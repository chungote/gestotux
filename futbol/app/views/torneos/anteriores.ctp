<h1>Todos los torneos</h1><hr>
<table class="tabla_sancionados">
 <tbody>
<?php
echo $html->tableHeaders( array( 'Nombre', 'Fecha Inicio', 'Fecha Fin' ) );
foreach( $torneos as $torneo )
{
 echo $html->tableCells(
			array(
				 array(
					 array(
						 $html->link( $torneo['Torneo']['name'], '/torneos/index/'.$torneo['Torneo']['id_torneo'] ),
						 array( 'align' => 'center' ) ),
					 array( date( 'd/m/Y', strtotime( $torneo['Torneo']['fecha_inicio'] ) ), array( 'align' => 'center' ) ),
					 array( date( 'd/m/Y', strtotime( $torneo['Torneo']['fecha_fin'] ) ), array( 'align' => 'center' ) )
				)
			), array( 'class' => 'textosombra1' )
		 );
}
?>
 </tbody>
</table>