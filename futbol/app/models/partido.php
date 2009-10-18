<?php

class Partido extends AppModel {

  var $name = 'Partido';
  var $primaryKey = 'id_partido';

  var $belongsTo = array( 'Fecha', 'Zona' );

  var $hasOne = array(
	'Equipo1' =>
		array( 'className' => 'Equipo',
			 'foreignKey' => false,
			 'conditions' => 'Equipo1.id_equipo = Partido.id_equipo_1' ),
	'Equipo2' =>
		array( 'className' => 'Equipo',
			 'foreignKey' => false,
			 'conditions' => 'Equipo2.id_equipo = Partido.id_equipo_2' ),
	'FotoPartido' =>
		array( 'className' => 'Foto',
			 'foreignKey' => false,
			 'conditions' => 'FotoPartido.foto_partido = Partido.id_partido' )
	);
  var $hasMany = array(
	'Sancionado' =>
		array( 'className' => 'Sancionado',
			 'dependent' => true ),
	'Amonestado' =>
		array( 'className' => 'Amonestado',
			 'dependet' => true ),
	'Goleador' =>
		array( 'className' => 'Goleador',
			 'order' => array( 'Goleador.minuto' => 'asc' ),
			 'dependet' => true ),
	'Fotos' =>
		array( 'className' => 'Foto',
			 'dependent' => true )
	);
}
?>