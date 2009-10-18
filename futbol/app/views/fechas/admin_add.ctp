<h1>Agregar Fecha</h1><hr>
<?php
echo $form->create( 'Fecha', array( 'action' => 'add/'. $id_torneo )  );
echo $form->input( 'name', array( 'label' => 'Nombre' ) );
echo $form->input( 'fecha_inicio', array( 'label' => "Fecha de Inicio", 'dateFormat' => 'DMY', 'type' => 'date' ) );
echo $form->input( 'fecha_fin', array( 'label' => "Fecha de fin", 'dateFormat' => 'DMY', 'type' => 'date' ) );
echo $form->input( 'publicado', array( 'label' => "Publicado", 'type' => 'checkbox' ) );
echo "Torneo: " . $nombre_torneo;
echo $form->input( 'torneo_id', array( 'type' => 'hidden', 'value' => $id_torneo ) );
echo "<hr>";
echo $form->end( "Agregar" );
?>