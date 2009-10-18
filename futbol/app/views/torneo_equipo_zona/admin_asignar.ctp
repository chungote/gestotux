<h1>Administrador de Zona por Torneo</h1>
<table  class="tabla_admin">
 <tbody>
 <?php echo $html->tableHeaders( array( 'Torneo', 'Zona', 'Acciones' ), array( 'class' => 'tabla_admin' ) ); ?>
 <?php
	$class = "1"; //pr( $datos );
	 foreach( $datos as $dato )
	{
		if( $class == "1" ) { $class = "2"; } else { $class = "1"; }
		echo $html->tableCells(
			array(
				array(
					$dato['Torneo']['name'],
					$dato['Zona']['nombre_zona'],
					$html->link( "Eliminar", '/admin/torneo_equipo_zona/eliminar/'.$dato['TorneoZonaEquipo']['equipo_id'].'/'.$dato['TorneoZonaEquipo']['torneo_id'].'/'.$dato['TorneoZonaEquipo']['zona_id'] , array(), 'Esta seguro de querer eliminar esta asignacion?' )
				)
			), array( 'class' => "textosombra".$class )
		);
	}
 ?>
    <tr>
      <td><?php echo $paginator->prev('<< Anterior', null, null, array('class' => 'disabled')); ?></td>
      <td colspan="4"><?php echo $paginator->counter( array( 'format' => 'Pagina %page% de %pages%, %current% de %count%' ) ); ?></td>
      <td><?php echo $paginator->next('Siguiente >>', null, null, array('class' => 'disabled')); ?></td>
    </tr>
 </tbody>
</table>

<?php echo $html->link( "Agregar Asignacion", 'agregar' ); ?>