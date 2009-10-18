<h1>Modificar Fecha</h1><hr>
<?php
echo $form->create( 'Fecha', array( 'action' => 'modificar' ) );
echo $form->input( 'name',         array( 'label' => 'Nombre' ) );
echo $form->input( 'fecha_inicio', array( 'label' => "Fecha de Inicio", 'dateFormat' => 'DMY'  ) );
echo $form->input( 'fecha_fin',    array( 'label' => "Fecha de fin", 'dateFormat' => 'DMY' ) );
echo $form->input( 'publicado',    array( 'label' => "Publicado", 'type' => 'checkbox' ) );
echo $form->input( 'torneo_id',    array( 'label' => "Torneo", 'options' => $torneos, 'default' => $id_torneo ) );
echo $form->input( 'id_fecha',     array( 'type' => 'hidden' ) );
echo "<hr>";
echo $form->end( "Guardar" );
?>