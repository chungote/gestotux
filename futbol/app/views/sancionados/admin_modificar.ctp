<?php //pr( $partido ); ?>
<h1>Sancionados para el partido:
    <?php echo $partido['Equipo1']['nombre'] .
          " vs " .
          $partido['Equipo2']['nombre'] .
          " el " .
          date( 'd/m/y G:i', strtotime( $partido['Partido']['fecha_jugar'] ) );
     ?>
</h1><hr>
<?php
//pr( $sancionado );
echo $form->create( 'Sancionado', array( 'action' => 'agregar' ) );
echo $form->input( 'equipo_id', array( 'type' => 'hidden', 'value' => $sancionado['Sancionado']['equipo_id'] ) );
echo $form->input( 'partido_id', array( 'type' => 'hidden', 'value' => $partido['Partido']['id_partido'] ) );
echo $form->input( 'nombre_jugador', array( 'label' => 'Nombre del jugador', 'type' => 'text', 'value' => $sancionado['Sancionado']['nombre_jugador'] ) );
echo $form->input( 'tipo_sancion_id', array( 'label' => 'Tipo de sancion', 'options' => $tipos_sancion,'value' => $sancionado['Sancionado']['tipo_sancion_id'] ) );
echo $form->input( 'cant_fechas', array( 'label' => 'Cantidad de fechas suspendido', 'value' => $sancionado['Sancionado']['cant_fechas'] ) );
echo $form->input( 'publicado', array( 'label' => "Publicado", 'type' => 'checkbox', 'value' => $sancionado['Sancionado']['publicado'] ) );
echo $form->input( 'id', array( 'type' => 'hidden', 'value' => $sancionado['Sancionado']['id'] ) );
echo "<hr>";
echo $form->end( "Agregar" );
?>