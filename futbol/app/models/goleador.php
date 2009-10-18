<?php

class Goleador extends AppModel {

  var $name = 'Goleador';
  var $primaryKey = 'id_goleador';
  var $display = 'nombre';
  var $useTable = 'goleadores';

  var $belongsTo =
	array( 'Partido' =>
			array( 'className' => 'Partido',
				 'foreignKey' => 'partido_id',
				 'dependent' => true ),
		 'Equipo' =>
			array( 'className' => 'Equipo',
				 'foreignKey' => 'equipo_id',
				 'dependent' => false )
		);
}
?>