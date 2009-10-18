<h1>Modificar foto</h1><hr>
<?php
echo $form->create( 'Foto', array( 'action' => 'modificar', 'enctype' => 'multipart/form-data'  ) );
echo $form->input( 'id_foto', array( 'type' => 'hidden', 'value' => $Foto['id_foto'] ) );
echo $form->input( 'fecha_id', array( 'label' => 'Fecha', 'options' => $fechas, 'value' => $Foto['fecha_id'] ) );
echo $form->input( 'titulo', array( 'label' => 'Titulo', 'value' => $Foto['titulo'] ) );
echo $form->input( 'comentario', array( 'label' => 'Comentario', 'type' => 'textarea', 'value' => $Foto['comentario'] ) );
echo $form->input( 'publicado', array( 'label' => 'Publicado', 'type' => 'checkbox', 'value' => $Foto['publicado'] ) );
if( $Foto['foto_partido'] == 0 )
{
  echo $form->input( 'foto_partido', array( 'label' => 'Poner como foto del partido', 'type' => 'checkbox', 'value' => 0 ) );
}
else
{
  echo $form->input( 'foto_partido', array( 'label' => 'Poner como foto del partido', 'type' => 'checkbox', 'value' => 1 ) );
}
if( $Foto['foto_fecha'] == 0 )
{
  echo $form->input( 'foto_fecha', array( 'label' => 'Poner como foto de la fecha', 'type' => 'checkbox', 'value' => 0 ) );
}
else
{
  echo $form->input( 'foto_fecha', array( 'label' => 'Poner como foto de la fecha', 'type' => 'checkbox', 'value' => 1 ) );
}
if( $Foto['foto_torneo'] == 0 )
{
  echo $form->input( 'foto_torneo', array( 'label' => 'Poner como foto del torneo', 'type' => 'checkbox', 'value' => 0 ) );
}
else
{
  echo $form->input( 'foto_torneo', array( 'label' => 'Poner como foto del torneo', 'type' => 'checkbox', 'value' => 1 ) );
}
echo $form->end( 'Guardar' );
?>