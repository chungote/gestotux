<br />
<h1>Goleadores para el partido:
    <?php echo $partido['Equipo1']['nombre'] .
          " vs " .
          $partido['Equipo2']['nombre'] .
          " el " .
          date( 'd/m/y', strtotime( $partido['Partido']['fecha_jugar'] ) );

echo $form->create( 'Goleadores', array( 'url' => '/admin/goleadores/agregar' ) );
     ?>
</h1><hr>
<?php if( $hacer_equipo_1 > 0 ) { ?>
<h3><?php echo $partido['Equipo1']['nombre'] . ' ('.$partido['Partido']['resultado_equipo_1']. ')'; ?></h3>
<?php
  for( $i = 1; $i <= $hacer_equipo_1; $i++ ) {
  echo $form->input( 'nombre_1_'.$i, array( 'label' => 'Goleador '.$i, 'size' => '25' ) );
  echo $form->input( 'minuto_1_'.$i, array( 'label' => 'Minuto', 'size' => 4 ) );
  }
}
if( $hacer_equipo_2 > 0 ) {
?>
<h3><? echo $partido['Equipo2']['nombre'] . ' ('.$partido['Partido']['resultado_equipo_2']. ')'; ?></h3>
<?php
 for( $j = 1; $j <= $hacer_equipo_2; $j++ ) {
   echo $form->input( 'nombre_2_'.$j, array( 'label' => 'Goleador '.$j, 'size' => '25' ) );
   echo $form->input( 'minuto_2_'.$j, array( 'label' => 'Minuto', 'size' => 4 ) );
 }
}
echo $form->input( 'id_partido', array( 'type' => 'hidden', 'value' => $partido['Partido']['id_partido'] ) );
echo $form->input( 'hacer_equipo_1', array( 'type' => 'hidden', 'value' => $hacer_equipo_1 ) );
echo $form->input( 'hacer_equipo_2', array( 'type' => 'hidden', 'value' => $hacer_equipo_2 ) );
echo $form->end( 'Guardar' );
?>