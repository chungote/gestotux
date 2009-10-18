<h1>Modificar Equipo</h1><hr>
<?php
//pr( $equipo );
echo $form->create( 'Equipo', array( 'action' => 'agregar' )  );
echo $form->input( 'id_equipo', array( 'type' => 'hidden', 'value' => $equipo['Equipo']['id_equipo'] ) );
echo $form->input( 'nombre', array( 'label' => 'Nombre', 'value' =>$equipo['Equipo']['nombre'] ) );
echo $form->input( 'admitido', array( 'label' => "Admitido", 'type' => 'checkbox', 'value' => $equipo['Equipo']['admitido'] ) );
echo $form->input( 'publicado', array( 'label' => "Publicado", 'type' => 'checkbox', 'value' => $equipo['Equipo']['publicado'] ) );
echo "<hr>";
echo $form->end( "Guardar" );
?>