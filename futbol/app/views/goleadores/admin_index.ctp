<h1>Goleadores para el partido:
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
echo $html->tableHeaders( array( 'Equipo', 'Nombre', 'Minuto', 'Publicado', 'Acciones' ) );

foreach( $goleadores as $dato )
{
  if( $dato['Goleador']['publicado'] == 1 )
 { $dato['Goleador']['publicado'] =  $html->link( "si", '/admin/goleadores/publicar/0/'.$dato['Goleador']['id_goleador'] ); }
 else
 { $dato['Goleador']['publicado'] = $html->link( "no", '/admin/goleadores/publicar/1/'.$dato['Goleador']['id_goleador'] ); }
 echo $html->tableCells(
	array(
		array( $dato['Equipo']['nombre'],
			 $dato['Goleador']['nombre'],
			 $dato['Goleador']['minuto'],
			$dato['Goleador']['publicado'],
			$html->link( "Eliminar", '/admin/goleadores/eliminar/'.$dato['Goleador']['id_goleador'].'/'.$dato['Goleador']['partido_id'], array(), 'Esta seguro que desea eliminar este goleador?' )
			//$html->link( "Modificar", 'modificar/'. $dato['Goleador']['id_goleador'] )
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
if( $hacer_equipo_1 > 0 || $hacer_equipo_2 > 0 ) {
echo $html->link( "Agregar Goleador", '/admin/goleadores/agregar/'.$id_partido ). " - ";
}
echo $html->link( "Volver a partidos", '/admin/partidos/index/'.$partido['Fecha']['id_fecha'] ); ?>