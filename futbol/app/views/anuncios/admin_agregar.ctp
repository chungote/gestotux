<h1>Agregar Anuncio</h1><hr>
<?php
	echo $form->create( 'Anuncio', array( 'action' => 'admin_agregar' ) );
	echo $form->input( 'titulo', array( 'label' => 'Titulo', 'type' => 'text' ) );
	echo $fck->fckeditor( array( 'Anuncio', 'contenido'), $html->base, $this->data['Anuncio']['Contenido' ]);
	echo $form->input( 'publicado', array( 'type' => 'checkbox') );
	echo $form->input( 'fin_fecha_publicacion', array( 'label' => 'Dejar de publicar en:', 'type' => 'date', 'dateFormat' => 'DMY' ) );
	echo $form->end('Agregar Anuncio');
?>