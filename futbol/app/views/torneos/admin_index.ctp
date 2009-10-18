<h1>Administrador de torneos</h1>
<table class="tabla_admin">
 <tbody>
<?php
echo $html->tableHeaders( array( 'Nombre', 'Fecha Inicio', 'Fecha Fin', 'Publicado', 'Acciones' ) );

foreach( $datos as $dato )
{
  if( $dato['Torneo']['publicado'] == 1 )
 { $dato['Torneo']['publicado'] =  $html->link( "si", '/admin/torneos/publicar/0/'.$dato['Torneo']['id_torneo'] ); }
 else
 { $dato['Torneo']['publicado'] = $html->link( "no", '/admin/torneos/publicar/1/'.$dato['Torneo']['id_torneo'] ); }
 echo $html->tableCells(
	array(
		array( $dato['Torneo']['name'],
			date( 'd-m-Y', strtotime( $dato['Torneo']['fecha_inicio'] ) ),
			date( 'd-m-Y', strtotime( $dato['Torneo']['fecha_fin'] ) ),
			$dato['Torneo']['publicado'],
			$html->link( "Ver Fechas", '/admin/fechas/index/'.$dato['Torneo']['id_torneo'] ) . " - " .
			$html->link( "Ver Zonas", '/admin/zonas/index/'.$dato['Torneo']['id_torneo'] ) . " - " .
			$html->link( "Eliminar", 'eliminar/'.$dato['Torneo']['id_torneo'], array(), 'Esta seguro que desea eliminar este campeonato?' ) . " -  " .
			$html->link( "Modificar", 'modificar/'. $dato['Torneo']['id_torneo'] )
		)
	)
  );
}

?>
 </tbody>
</table>

<?php echo $html->link( "Agregar Torneo", array( 'controller' => 'torneos', 'action' => 'agregar' ) ); ?>