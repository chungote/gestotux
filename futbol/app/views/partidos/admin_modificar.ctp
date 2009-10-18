<h1>Modificar partido</h1><hr>
<?php
echo $form->create( 'Partido', array( 'action' => 'modificar' )  );
echo $form->input( 'publicado', array( 'label' => "Publicado", 'type' => 'checkbox', 'value' => $partido['Partido']['publicado'] ) );
echo $form->input( 'cancha', array( 'label' => 'Cancha', 'value' => $partido['Partido']['cancha'] ) );
echo $form->input( 'fecha_jugar', array( 'label' => "Fecha y hora", 'dateFormat' => 'DMYH', 'value' => $partido['Partido']['fecha_jugar'] ) );
echo $form->input( 'fecha_id', array( 'label' => "Fecha", 'options' => $fechas, 'value' => $partido['Partido']['fecha_id'] ) );
echo $form->input( 'id_partido', array( 'type' => 'hidden', 'value' => $partido['Partido']['id_partido'] ) );
echo "<hr>";
echo $form->end( "Agregar" );
?>