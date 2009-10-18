<h1>Modificar Publicidad</h1><hr>
<?php
echo $form->create( 'Publicidad', array( 'url' => '/admin/publicidades/modificar', 'enctype' => 'multipart/form-data' ) );
echo $form->input( 'cliente', array( 'label' => "Cliente", 'value' => $Publicidad['Publicidad']['cliente'] ) );
echo $form->input( 'nombre', array( 'label' => "Nombre", 'value' => $Publicidad['Publicidad']['nombre'] ) );
echo $form->input( 'url', array( 'label' => "Direccion del link", 'value' => $Publicidad['Publicidad']['url'], 'between' => 'http://' ) );
echo $form->input( 'publicado', array( 'label' => "Publicado", 'type' => 'checkbox', 'value' => $Publicidad['Publicidad']['publicado'] ) );
echo $form->input( 'id_publicidad', array( 'type' => 'hidden', 'value' => $Publicidad['Publicidad']['id_publicidad'] ) );
echo "<hr>";
echo $form->end( "Guardar" );
?>