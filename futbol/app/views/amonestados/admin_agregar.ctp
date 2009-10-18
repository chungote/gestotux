<br />
<h1>Agregar Amonestado</h1><hr>
<?php
//pr( $partido );
echo $form->create( 'Amonestado', array( 'action' => 'admin_agregar' ) );
echo $form->input( 'nombre_jugador', array( 'label' => 'Nombre del Jugador', 'type' => 'text' ) );
echo $form->input( 'equipo_id', array( 'values' => $equipos ) );
echo $form->input( 'cantidad', array( 'label' => 'Cantidad' ) );
echo $form->input( 'publicado', array( 'label' => 'Publicado', 'type' => 'checkbox' ) );
echo $form->input( 'partido_id', array( 'type' => 'hidden', 'value' => $partido ) );
echo $form->end( 'Agregar' );
?>