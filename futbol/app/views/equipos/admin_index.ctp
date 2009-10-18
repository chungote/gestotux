<h1>Administrador de Equipos</h1>
<table  class="tabla_admin">
 <tbody>
 <?php echo $html->tableHeaders( array( 'Nombre', 'Admitido', 'Publicado', 'Acciones' ), array( 'class' => 'tabla_admin' ) ); ?>
 <?php
	$class = "1"; //pr( $equipos );
	 foreach( $equipos as $equipo )
	{
		if( $class == "1" ) { $class = "2"; } else { $class = "1"; }
 		if( $equipo['Equipo']['publicado'] == 1 )
		 { $equipo['Equipo']['publicado'] =  $html->link( "si", '/admin/equipos/publicar/0/'.$equipo['Equipo']['id_equipo'] ); }
		 else
 		{ $equipo['Equipo']['publicado'] = $html->link( "no", '/admin/equipos/publicar/1/'.$equipo['Equipo']['id_equipo'] ); }
 		if( $equipo['Equipo']['admitido'] == 1 )
		 { $equipo['Equipo']['admitido'] =  $html->link( "si", '/admin/equipos/admitir/0/'.$equipo['Equipo']['id_equipo'] ); }
		 else
 		{ $equipo['Equipo']['admitido'] = $html->link( "no", '/admin/equipos/admitir/1/'.$equipo['Equipo']['id_equipo'] ); }
		if( isset( $id_zona ) )
		{ $equipo['Equipo']['Accion'] = " - " .$html->link( 'Asignar a '.$nombre_zona, '/admin/torneo_equipo_zona/asigna_directo/'.$id_torneo.'/'.$equipo['Equipo']['id_equipo'].'/'.$id_zona ); 	}
		else
		{ $equipo['Equipo']['Accion'] = ""; }
		echo $html->tableCells(
			array(
				array(
					$equipo['Equipo']['nombre'],
					$equipo['Equipo']['admitido'],
					$equipo['Equipo']['publicado'],
					$html->link( "Modificar", '/admin/equipos/modificar/'. $equipo['Equipo']['id_equipo'] ) . " - " .
					$html->link( "Asignar Zona", '/admin/torneo_equipo_zona/asignar/'.$equipo['Equipo']['id_equipo'] ) .
					$equipo['Equipo']['Accion']
					//$html->link( "Eliminar", '/admin/equipos/eliminar/'.$equipo['Equipo']['id_equipo'] , array(), 'Esta seguro de querer eliminar este equipo? \n Si lo hace eliminara tambien todos los partidos relacionados con este equipo seran eliminados. Si no desea eliminar todo, despublique la fecha.' )
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

<?php echo $html->link( "Agregar Equipo", 'agregar' ); //pr( $equipos ); ?>