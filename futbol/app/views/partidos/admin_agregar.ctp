<h1>AgregarPartido</h1><hr>
<?php
echo "<b>Zona:</b> ". $nombre_zona . "<br />";
echo "<b>Fecha:</b> " . $nombre_fecha;

echo $form->create( 'Partido', array( 'action' => 'agregar' )  );
echo "Equipos:";
echo $form->select( 'id_equipo_1', array( 'label' => 'Equipo 1', 'options' => $equipos ) );
echo "  Vs ";
echo $form->select( 'id_equipo_2', array( 'label' => 'Equipo 2', 'options' => $equipos ) );
echo $form->input( 'cancha', array( 'label' => 'Cancha' ) );
echo $form->input( 'fecha_jugar', array( 'label' => "Fecha y hora", 'dateFormat' => 'DMYH' ) );
echo $form->input( 'fecha_id', array( 'type' => 'hidden', 'value' => $id_fecha  ) );
echo $form->input( 'zona_id', array( 'type' => 'hidden', 'value' => $id_zona  ) );
echo $form->input( 'publicado', array( 'label' => "Publicado", 'type' => 'checkbox' ) );
echo "<hr>";
echo $form->end( "Agregar" );
?>