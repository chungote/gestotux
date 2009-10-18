<h1>Resultados para el partido:
    <?php echo $partido['Equipo1']['nombre'] .
          " vs " .
          $partido['Equipo2']['nombre'] .
          " el " .
          /*date( 'd/m/y',*/ $partido['Partido']['fecha_jugar'] /*)*/;
     ?>
</h1><hr>
<?php
echo $form->create( 'Resultados', array( 'url' => '/admin/partidos/resultados' ) );
echo $form->input( 'id_partido', array( 'type' => 'hidden', 'value' => $partido['Partido']['id_partido'] ) );
echo $form->input( 'fecha_id', array( 'type' => 'hidden', 'hidden', 'value' => $partido['Partido']['fecha_id'] ) );
echo $form->input( 'resultado_equipo_1', array( 'label' => 'Goles de '. $partido['Equipo1']['nombre'], 'value' => $partido['Partido']['resultado_equipo_1'] ) );
echo $form->input( 'resultado_equipo_2', array( 'label' => 'Goles de '. $partido['Equipo2']['nombre'], 'value' => $partido['Partido']['resultado_equipo_2'] ) );
echo $form->end( 'Guardar' );
?>