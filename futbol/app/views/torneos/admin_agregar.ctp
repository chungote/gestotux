<h1>Agregar Torneo</h1>
<?php
	echo $form->create( 'Torneo', array( 'action' => 'admin_agregar' ) );
	echo $form->input( 'name', array( 'label' => 'Nombre del Torneo' ) );
	echo $form->input( 'fecha_inicio', array( 'label' => 'Fecha de Inicio', 'dateFormat' => 'DMY' ) );
	echo $form->input( 'fecha_fin', array( 'label' => 'Fecha de Fin', 'dateFormat' => 'DMY' ) );
	echo $form->input( 'publicado', array( 'type' => 'checkbox' ) );
	echo $fck->fckeditor( array( 'Torneo', 'reglamento'), $html->base );
	echo $form->end( 'Agregar' );
?>