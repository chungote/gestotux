<?php //pr( $partido ); ?>
<h1>Sancionados para el partido:
    <?php echo $partido['Equipo1']['nombre'] .
          " vs " .
          $partido['Equipo2']['nombre'] .
          " el " .
          /*date( 'd/m/y',*/ $partido['Partido']['fecha_jugar'] /*)*/;
     ?>
</h1><hr>
<?php
echo $form->create( 'Sancionado', array( 'action' => 'agregar' ) );
//Array con los dos equipos
$equipo[$partido['Equipo1']['id_equipo']] = $partido['Equipo1']['nombre'];
$equipo[$partido['Equipo2']['id_equipo']] = $partido['Equipo2']['nombre'];
echo $form->input( 'equipo_id', array( 'label' => 'Equipo', 'options' => $equipo ) );
echo $form->input( 'partido_id', array( 'type' => 'hidden', 'value' => $partido['Partido']['id_partido'] ) );
echo $form->input( 'nombre_jugador', array( 'label' => 'Nombre del jugador', 'type' => 'text' ) );
echo $form->input( 'tipo_sancion_id', array( 'label' => 'Tipo de sancion', 'options' => $tipos_sancion ) );
echo $form->input( 'cant_fechas', array( 'label' => 'Cantidad de fechas suspendido' ) );
echo $form->input( 'publicado', array( 'label' => "Publicado", 'type' => 'checkbox' ) );
echo "<hr>";
echo $form->end( "Agregar" );
?>