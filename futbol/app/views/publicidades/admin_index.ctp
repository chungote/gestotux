<h1>Administrador de Publicidades</h1><hr>
<table  class="tabla_admin">
 <tbody>
<?php
echo $html->tableHeaders( array( 'Nombre', 'Cliente', 'Veces Vista', 'Imagenes', 'Publicado', 'Acciones' ) );

foreach( $datos as $dato )
{
 if( $dato['Publicidad']['publicado'] == 1 )
 { $dato['Publicidad']['publicado'] =  $html->link( "si", '/admin/publicidades/publicar/0/'.$dato['Publicidad']['id_publicidad'] ); }
 else
 { $dato['Publicidad']['publicado'] = $html->link( "no", '/admin/publicidades/publicar/1/'.$dato['Publicidad']['id_publicidad'] ); }
 echo $html->tableCells(
	array(
		array( $dato['Publicidad']['nombre'],
			 $dato['Publicidad']['cliente'],
			 $dato['Publicidad']['veces_visto'],
			 $html->image( $dato['Publicidad']['archivo'] ),
			 $dato['Publicidad']['publicado'],
			 $html->link( "Eliminar", 'eliminar/'.$dato['Publicidad']['id_publicidad'], array(), 'Esta seguro que desea eliminar esta publicidad?' ) . " - ".
			 $html->link( "Resetear Contador", 'resetear/'.$dato['Publicidad']['id_publicidad'] ) . " - " .
			 $html->link( "Modificar", '/admin/publicidades/modificar/' . $dato['Publicidad']['id_publicidad'] )
		)
	)
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

<?php echo $html->link( "Agregar Publicidad", array( 'controller' => 'publicidades', 'action' => 'agregar' ) ); ?>