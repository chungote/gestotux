<h1>Agregar Asignaci&oacute;n</h1>
<b>Equipo:</b><?php echo $nombre_equipo; ?><br />
<b>Torneo:</b><?php echo $nombre_torneo; ?><br />
<?php
echo $form->create( 'TorneoZonaEquipo', array( 'url' => '/admin/torneo_equipo_zona/agregar' )  );
echo $form->input( 'torneo_id', array( 'type' => 'hidden', 'value' => $id_torneo ) );
echo $form->input( 'equipo_id', array( 'type' => 'hidden', 'value' => $id_equipo ) );
echo $form->input( 'zona_id', array( 'label' => 'Zona', 'options' => $zonas ) );
echo "<hr>";
echo $form->end( "Agregar" );
?>