<h1>Administrador de Zonas</h1>
<?php $this->pageTitle = "Zonas"; ?>
<?php echo $form->create( 'zona', array( 'action' => 'index') ) .
           "Filtrar por torneo:" .
           $form->select( 'id_torneo', array( 'options' => $lista_torneos, 'default' => $id_torneo ), array( 'class' => false ) ) .
           $form->end( 'Filtrar' ); ?>
<table class="tabla_admin">
 <tbody>
<?php
echo $html->tableHeaders( array( 'Nombre', 'Torneo', 'Publicada', 'Acciones' ) );

foreach( $zonas as $dato )
{
  if( $dato['Zona']['publicado'] == 1 )
 { $dato['Zona']['publicado'] =  $html->link( "si", '/admin/zonas/publicar/0/'.$dato['Zona']['id_zona'] ); }
 else
 { $dato['Zona']['publicado'] = $html->link( "no", '/admin/zonas/publicar/1/'.$dato['Zona']['id_zona'] ); }
 echo $html->tableCells(
	array(
		array( $dato['Zona']['nombre_zona'],
			 $dato['Torneo']['name'],
			$dato['Zona']['publicado'],
			$html->link( "Ver partidos", '/admin/partidos/index/'.$dato['Zona']['torneo_id'].'/-/'.$dato['Zona']['id_zona'] ) . " - " .
			//$html->link( "Eliminar", 'eliminar/'.$dato['Zona']['id_zona'], array(), 'Esta seguro que desea eliminar esta zona?' ) . " -  " .
			$html->link( "Modificar", 'modificar/'. $dato['Zona']['id_zona'] )
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

<?php echo $html->link( "Agregar Nueva Zona", array( 'controller' => 'zonas', 'action' => 'agregar', $id_torneo ) ); ?>