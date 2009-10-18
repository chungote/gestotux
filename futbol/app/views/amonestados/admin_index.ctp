<br /><h1>Amonestados para el partido:
    <?php echo $partido['Equipo1']['nombre'] .
          " vs " .
          $partido['Equipo2']['nombre'] .
          " el " .
          /*date( 'd/m/y',*/ $partido['Partido']['fecha_jugar'] /*)*/;
     ?>
</h1><hr>
<table class="tabla_admin">
 <tbody>
<?php
echo $html->tableHeaders( array( 'Equipo', 'Nombre', 'Cantidad', 'Publicado', 'Acciones' ) );

foreach( $datos as $dato )
{
  if( $dato['Amonestado']['publicado'] == 1 )
 { $dato['Amonestado']['publicado'] =  $html->link( "si", '/admin/amonestados/publicar/0/'.$dato['Amonestado']['id_amonestado'] ); }
 else
 { $dato['Amonestado']['publicado'] = $html->link( "no", '/admin/amonestados/publicar/1/'.$dato['Amonestado']['id_amonestado'] ); }
 echo $html->tableCells(
	array(
		array( $dato['Equipo']['nombre'],
			 $dato['Amonestado']['nombre_jugador'],
			 $dato['Amonestado']['cantidad'],
			$dato['Amonestado']['publicado'],
			$html->link( "Eliminar", '/admin/amonestados/eliminar/'.$dato['Amonestado']['id_amonestado'].'/'.$dato['Amonestado']['partido_id'], array(), 'Esta seguro que desea eliminar este amonestado?' )
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

<?php
echo $html->link( "Agregar Amonestado", '/admin/amonestados/agregar/'.$partido['Partido']['id_partido'] ). " - ";
echo $html->link( "Volver a partidos", '/admin/partidos/index/'.$partido['Fecha']['id_fecha'] ); ?>