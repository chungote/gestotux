<?php
if( isset( $partido ) )
{
?>
<h1>Sancionados para el partido:
    <?php echo $partido['Equipo1']['nombre'] .
          " vs " .
          $partido['Equipo2']['nombre'] .
          " el " .
          /*date( 'd/m/y',*/ $partido['Partido']['fecha_jugar'] /*)*/;
     ?>
</h1><hr>
<?php
} else {
?>
<h1>Administrador de Sancionados</h1>
<?php } ?>
<table cellspacing="0" cellpadding="0" class="tabla_admin">
 <tbody>
<?php
//pr( $partido );
echo $html->tableHeaders( array( 'Equipo', 'Nombre', 'Tipo Sancion', 'Cant Fechas', 'Publicado', 'Acciones' ), array( 'class' => 'tabla_admin_cabecera' ) );

foreach( $datos as $dato )
{
 unset( $dato['Partido'] );
 if( $dato['Sancionado']['publicado'] == 1 )
 { $dato['Sancionado']['publicado'] =  $html->link( "si", '/admin/sancionados/publicar/0/'.$dato['Sancionado']['id'] ); }
 else
 { $dato['Sancionado']['publicado'] = $html->link( "no", '/admin/sancionados/publicar/1/'.$dato['Sancionado']['id'] ); }
 echo $html->tableCells(
	array(
		array( $dato['Equipo']['nombre'],
			 $dato['Sancionado']['nombre_jugador'],
			 $dato['TipoSancion']['nombre'],
			 $dato['Sancionado']['cant_fechas'],
			$dato['Sancionado']['publicado'],
			$html->link( "Eliminar", '/admin/sancionados/eliminar/'.$dato['Sancionado']['id'].'/'.$dato['Sancionado']['partido_id'], array(), 'Esta seguro que desea eliminar este archivo de sancionados?' ) . " - " .
			$html->link( "Modificar", '/admin/sancionados/modificar/'.$dato['Sancionado']['id'].'/'.$dato['Sancionado']['partido_id'] )
		)
	)
  );
}

?>
 </tbody>
</table>

<?php echo $html->link( "Agregar Sancionado", array( 'controller' => 'sancionados', 'action' => 'agregar', $partido['Partido']['id_partido'] ) ); ?>
<?php echo " - " .$html->link( "Volver a partidos", '/admin/partidos/index/'.$partido['Fecha']['id_fecha'] ); ?>