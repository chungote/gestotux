<h1>Administrador de Partidos para <?php echo $nombre_fecha; ?></h1>
<!-- Formulario de control de fecha -->
<div>
<?php
echo $form->create( 'partidos', array( 'action' => 'index') ) . "Filtrar por fecha:" .
     $form->select( 'id_fecha', array( 'options' => $lista_fechas ), array( 'class' => false ) ) . "  Zona: " .
     $form->select( 'id_zona', array( 'options' => $lista_zonas ), array( 'class' => false ) ).
     $form->end( 'Filtrar' );
?>
</div>
<table cellspacing="0" cellpadding="0" class="tabla_admin">
 <tbody>
 <?php echo $html->tableHeaders( array( 'Equipo 1', 'Equipo 2', 'Cancha', 'Fecha', 'Publicado', 'Acciones' ), array( 'class' => 'tabla_admin' ) ); ?>
 <?php
	$class = "1";
	foreach( $partidos as $partido )
	{
		// publicado
 		if( $partido['Partido']['publicado'] == 1 )
		 { $partido['Partido']['publicado'] =  $html->link( "si", '/admin/partidos/publicar/0/'.$partido['Partido']['id_partido'].'/'.$partido['Fecha']['id_fecha'] ); }
		 else
 		{ $partido['Partido']['publicado'] = $html->link( "no", '/admin/partidos/publicar/1/'.$partido['Partido']['id_partido'].'/'.$partido['Fecha']['id_fecha'] ); }
		// Acciones
		$partido['Partido']['Acciones'] = $html->link( "Modificar", '/admin/partidos/modificar/'. $partido['Partido']['id_partido'] ) . " - " .
			$html->link( "Eliminar", '/admin/partidos/eliminar/'.$partido['Partido']['id_partido'] , array(), 'Esta seguro de querer eliminar este partido? \n Si lo hace eliminara tambien todos los datos y fotos relacionados con ella seran eliminados. Si no desea eliminar todo, despublique la fecha.' );
			if( $partido['Partido']['fecha_jugar'] > date('y-m-d h:m:s') ) {
				// Acciones para cuando el partido ya se jugo
				if( $partido['Partido']['resultado_equipo_1'] == null ) {
					$partido['Partido']['Acciones'] .= " - " . $html->link( "Poner Resultado", '/admin/partidos/resultados/'.$partido['Partido']['id_partido'].'/'.$partido['Partido']['fecha_id'] ) . " - ";
				} else {
					$partido['Partido']['Acciones'] .= " - " . $html->link( "Modificar Resultado", '/admin/partidos/resultados/'.$partido['Partido']['id_partido'].'/'.$partido['Partido']['fecha_id'] ) . " - ";
					$partido['Partido']['Acciones'] .= $html->link( "Goleadores", '/admin/goleadores/index/'.$partido['Partido']['id_partido'] ) . " - ";
				}
				$partido['Partido']['Acciones'] .= $html->link( "Sancionados", '/admin/sancionados/index/'.$partido['Partido']['id_partido'] );
				$partido['Partido']['Acciones'] .=  " - " . $html->link( "Amonestados", '/admin/amonestados/index/'.$partido['Partido']['id_partido'] );
				$partido['Partido']['Acciones'] .= " - " . $html->link( "Fotos", '/admin/fotos/index/partido/'.$partido['Partido']['id_partido'] );
			}
		// Fin Acciones
		echo $html->tableCells(
			array(
				array(
					$partido['Equipo1']['nombre'] . '(' . $partido['Partido']['resultado_equipo_1'] . ')',
					$partido['Equipo2']['nombre'] . '(' . $partido['Partido']['resultado_equipo_2'] . ')',
					$partido['Partido']['cancha'],
					date( 'd/m/y', strtotime( $partido['Partido']['fecha_jugar'] ) ),
					$partido['Partido']['publicado'],
					$partido['Partido']['Acciones']
				)
			), array( 'class' => "textosombra" . $class )
		);
		if( $class == "1" ) {
			$class = "2";
		} else {
			 $class = "1";
		}
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
 if( isset( $id_fecha ) && isset( $id_zona ) )
 {
  echo $html->link( "Agregar Partido", array( 'controller' => 'partidos', 'action' => 'agregar', $id_fecha, $id_zona ) );
 } ?>