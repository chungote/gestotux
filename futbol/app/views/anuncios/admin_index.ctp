<h1>Administrador de anuncios</h1>
<table class="tabla_admin">
 <tbody>
<?php
echo $html->tableHeaders( array( 'Titulo', 'Publicado', 'Acciones' ) );

foreach( $anuncios as $dato )
{
  if( $dato['Anuncio']['publicado'] == 1 )
 { $dato['Anuncio']['publicado'] =  $html->link( "si", '/admin/anuncios/publicar/0/'.$dato['Anuncio']['id_anuncio'] ); }
 else
 { $dato['Anuncio']['publicado'] = $html->link( "no", '/admin/anuncios/publicar/1/'.$dato['Anuncio']['id_anuncio'] ); }
 echo $html->tableCells(
	array(
		array( $dato['Anuncio']['titulo'],
			$dato['Anuncio']['publicado'],
			$html->link( "Eliminar", 'eliminar/'.$dato['Anuncio']['id_anuncio'], array(), 'Esta seguro que desea eliminar este Anuncio?' ) . " -  " .
			$html->link( "Modificar", 'modificar/'. $dato['Anuncio']['id_anuncio'] )
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

<?php echo $html->link( "Agregar Nuevo Anuncio", array( 'controller' => 'anuncios', 'action' => 'agregar' ) ); ?>