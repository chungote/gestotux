<h1>Agregar Tipo de Sancion</h1><hr>
<?php
	echo $form->create( 'TipoSancion', array( 'url' => '/admin/tipo_sancion/agregar' ) );
	echo $form->input( 'nombre', array( 'label' => 'Nombre', 'type' => 'text' ) );
	echo $form->input( 'publicado', array( 'type' => 'checkbox') );
	echo $form->end('Agregar Tipo de Sancion');
?>