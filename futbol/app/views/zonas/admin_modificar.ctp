<h1>Guardar Zona</h1><hr>
<?php
	echo $form->create( 'Zona', array( 'action' => 'admin_modificar' ) );
	echo $form->input( 'id_zona', array( 'type' => 'hidden', 'value' => $datos['Zona']['id_zona'] ) );
	echo $form->input( 'nombre_zona', array( 'label' => 'Nombre', 'type' => 'text', 'value' => $datos['Zona']['nombre_zona'] ) );
	echo $form->input( 'publicado', array( 'type' => 'checkbox', 'value' => $datos['Zona']['publicado'] ) );
	echo $form->select( 'torneo_id', array( 'label' => 'Torneo', 'options' => $lista_torneos ) );
	echo "<hr>";
	echo $form->end('Guardar Zona');
?>