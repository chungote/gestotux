<h1>Modificar Torneo</h1>
<?php
	echo $form->create( 'Torneo', array( 'action' => 'admin_modificar' ) );
	echo $form->input( 'id_torneo', array( 'type' => 'hidden', 'value' => $this->data['Torneo']['id_torneo'] ) );
	echo $form->input( 'name', array( 'label' => 'Nombre del Torneo', 'value' => $this->data['Torneo']['name'] ) );
	echo $form->input( 'fecha_inicio', array( 'label' => 'Fecha de Inicio', 'dateFormat' => 'DMY', 'value' => $this->data['Torneo']['fecha_inicio' ] ) );
	echo $form->input( 'fecha_fin', array( 'label' => 'Fecha de Fin', 'dateFormat' => 'DMY', 'value' => $this->data['Torneo']['fecha_fin' ] ) );
	echo $form->input( 'publicado', array( 'type' => 'checkbox', 'value' => $this->data['Torneo']['publicado' ] ) );
	echo $fck->fckeditor( array( 'Torneo', 'reglamento'), $html->base, $this->data['Torneo']['reglamento' ]);
	echo $form->end( 'Guardar' );
?>