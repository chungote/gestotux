<h1>Administrador de Tipos de Sancion</h1>
<table class="tabla_admin">
 <tbody>
<?php
echo $html->tableHeaders( array( 'Nombre', 'Publicado', 'Acciones' ), array( 'class' => 'tabla_admin_cabecera' ) );

foreach( $datos as $dato )
{
  if( $dato['TipoSancion']['publicado'] == 1 )
 { $dato['TipoSancion']['publicado'] =  $html->link( "si", '/admin/anuncios/publicar/0/'.$dato['TipoSancion']['id_tipo_sancion'] ); }
 else
 { $dato['TipoSancion']['publicado'] = $html->link( "no", '/admin/anuncios/publicar/1/'.$dato['TipoSancion']['id_tipo_sancion'] ); }
 echo $html->tableCells(
	array(
		array( $dato['TipoSancion']['nombre'],
			$dato['TipoSancion']['publicado'],
			$html->link( "Eliminar", 'eliminar/'.$dato['TipoSancion']['id_tipo_sancion'], array(), 'Esta seguro que desea eliminar este Tipo de Sancion?. Se eliminaran todas las sanciones colocadas en cualquier partido que corresponda con este tipo.' ) . " -  " .
			$html->link( "Modificar", 'modificar/'. $dato['TipoSancion']['id_tipo_sancion'] )
		)
	)
  );
}

?>
    <tr>
      <td><?php echo $paginator->prev('<< Anterior', null, null, array('class' => 'disabled')); ?></td>
      <td colspan="1" class="disabled"><?php echo $paginator->counter( array( 'format' => 'Pagina %page% de %pages%, %current% de %count%' ) ); ?></td>
      <td><?php echo $paginator->next('Siguiente >>', null, null, array('class' => 'disabled')); ?></td>
    </tr>
 </tbody>
</table>

<?php echo $html->link( "Agregar Nuevo Tipo de Sancion", array( 'controller' => 'tipo_sancion', 'action' => 'agregar' ) ); ?>