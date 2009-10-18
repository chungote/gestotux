<br /><h1>Agregar nueva foto al partido: <?php echo $partido['Equipo1']['nombre'] .
          " vs " .
          $partido['Equipo2']['nombre'] .
          " el " .
          date( 'd/m/y H:i', strtotime( $partido['Partido']['fecha_jugar'] ) );
     ?></h1><hr>
<?php
echo $form->create( 'Foto', array( 'url' => '/admin/fotos/agregar/'.$que.'/'.$id, 'enctype' => 'multipart/form-data'  ) );

if( $que == "partido" ) {
 echo $form->input( 'partido_id', array( 'type' => 'hidden', 'value' => $id ) );
 echo $form->input( 'fecha_id', array( 'type' => 'hidden', 'value' => $partido['Partido']['fecha_id'] ) );
} else {
 echo $form->input( 'partido_id', array( 'label' => 'Partido', 'options' => $partidos ) );
 echo $form->input( 'fecha_id', array( 'label' => 'Fecha', 'options' => $fechas ) );
}
echo $form->input( 'titulo', array( 'label' => 'Titulo' ) );
echo $form->file( 'archivo_subido', array( 'label' => 'Archivo de imagen' ) );
echo $form->input( 'comentario', array( 'label' => 'Comentario', 'type' => 'textarea' ) );
echo $form->input( 'publicado', array( 'label' => 'Publicado', 'type' => 'checkbox' ) );
echo $form->input( 'foto_partido', array( 'label' => 'Poner como foto del partido', 'type' => 'checkbox' ) );
echo $form->input( 'foto_fecha', array( 'label' => 'Poner como foto de la fecha', 'type' => 'checkbox' ) );
echo $form->input( 'foto_torneo', array( 'label' => 'Poner como foto del torneo', 'type' => 'checkbox' ) );
echo $form->input( 'que', array( 'type' => 'hidden', 'value' => $que ) );
echo $form->input( 'id', array( 'type' => 'hidden', 'value' => $id ) );
echo $form->end( 'Enviar' );
?>