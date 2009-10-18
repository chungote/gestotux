<h1>Agregar Zona</h1><hr>
<?php
	echo $form->create( 'Zona', array( 'action' => 'admin_agregar' ) );
	echo $form->input( 'nombre_zona', array( 'label' => 'Nombre', 'type' => 'text' ) );
	echo $form->input( 'publicado', array( 'type' => 'checkbox') );
	echo $form->select( 'torneo_id', array( 'label' => 'Torneo', 'options' => $lista_torneos ) );
	echo $form->end('Agregar Zona');
?>