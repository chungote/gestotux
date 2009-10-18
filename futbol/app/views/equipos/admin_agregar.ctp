<h1>Agregar Equipo</h1><hr>
<?php
echo $form->create( 'Equipo', array( 'action' => 'agregar' )  );
echo $form->input( 'nombre', array( 'label' => 'Nombre' ) );
echo $form->input( 'admitido', array( 'label' => "Admitido", 'type' => 'checkbox' ) );
echo $form->input( 'publicado', array( 'label' => "Publicado", 'type' => 'checkbox' ) );
echo "<hr>";
echo $form->end( "Agregar" );
?>