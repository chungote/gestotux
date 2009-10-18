<h1>Agregar Publicidad</h1><hr>
<?php
echo $form->create( 'Publicidad', array( 'url' => '/admin/publicidades/agregar', 'enctype' => 'multipart/form-data' ) );
echo $form->input( 'cliente', array( 'label' => "Cliente" ) );
echo $form->input( 'nombre', array( 'label' => "Nombre" ) );
echo $form->input( 'url', array( 'label' => "Direccion del link", 'between' => 'http://' ) );
echo "Archivo de imagen:";
echo $form->file( 'archivo_subido' );
echo $form->input( 'publicado', array( 'label' => "Publicado", 'type' => 'checkbox' ) );
echo "<hr>";
echo $form->end( "Agregar" );
?>