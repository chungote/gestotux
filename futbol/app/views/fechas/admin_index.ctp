<h1>Administrador de Fechas</h1>
<!-- Filtrador de fechas -->
<?php echo $form->create( 'Fecha', array( 'url' => '/admin/fechas/index'  ) ) .
           "Torneo:" . $form->select( 'id_torneo', array( 'options' => $lista_torneos ) ) . $form->end( "Buscar" ); ?>
<table  class="tabla_admin">
 <tbody>
 <?php echo $html->tableHeaders( array( 'Nombre', 'Inicio - Fin', 'Publicado', 'Acciones' ), array( 'class' => 'tabla_admin' ) ); ?>
 <?php
	$class = "1";
	 foreach( $fechas as $fecha )
	{
		if( $class == "1" ) { $class = "2"; } else { $class = "1"; }
 		if( $fecha['Fecha']['publicado'] == 1 )
		 { $fecha['Fecha']['publicado'] =  $html->link( "si", '/admin/fechas/publicar/0/'.$fecha['Fecha']['id_fecha'] ); }
		 else
 		{ $fecha['Fecha']['publicado'] = $html->link( "no", '/admin/fechas/publicar/1/'.$fecha['Fecha']['id_fecha'] ); }
		echo $html->tableCells(
			array(
				array(
					$fecha['Fecha']['name'],
					date( 'd/m/y', strtotime( $fecha['Fecha']['fecha_inicio'] ) ). " -> " . date( 'd/m/y', strtotime( $fecha['Fecha']['fecha_fin'] ) ),
					$fecha['Fecha']['publicado'],
					$html->link( "Modificar", array( 'controller' => 'fechas' , 'action' => 'modificar', $fecha['Fecha']['id_fecha'] ) ) . " - " .
					$html->link( "Eliminar", array( 'controller' => 'fechas' , 'action' => 'eliminar', $fecha['Fecha']['id_fecha'] ), array(), 'Esta seguro de querer eliminar esta fecha? \n Si lo hace eliminara tambien todos los datos y fotos relacionados con ella seran eliminados. Si no desea eliminar todo, despublique la fecha.' ) . " - ".
					$html->link( "Partidos", array( 'controller' => 'partidos' , 'action' => 'index', $fecha['Fecha']['torneo_id'], $fecha['Fecha']['id_fecha'], null ) )
				)
			), array( 'class' => "textosombra".$class )
		);
	}
 ?>
    <tr>
      <td><?php echo $paginator->prev('<< Anterior', null, null, array('class' => 'disabled')); ?></td>
      <td colspan="2"><?php echo $paginator->counter( array( 'format' => 'Pagina %page% de %pages%, %current% de %count%' ) ); ?></td>
      <td><?php echo $paginator->next('Siguiente >>', null, null, array('class' => 'disabled')); ?></td>
    </tr>
 </tbody>
</table>

<?php echo $html->link( "Agregar Fecha", 'add/'.$id_torneo ); ?>