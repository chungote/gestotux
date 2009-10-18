<?php
class Torneo extends AppModel {
 var $name = 'Torneo';
 var $tableName = 'torneos';
 var $primaryKey = 'id_torneo';

 var $hasMany = array( 'Fechas' => array( 'dependent' => true, 'className' => 'Fecha' ),
			     'TorneoZonaEquipo' );

 var $haOne = array( 'FotoTorneo' =>
			array( 'className' => 'Foto',
				 'dependent' => false,
				 'condition' => 'Torneo.id_torneo = FotoTorneo.foto_torneo' ) );

 var $validate = array(
	'fecha_inicio' => 'date',
	'fecha_fin' => 'date',
	'publicado' => 'boolean' );
}
?>
