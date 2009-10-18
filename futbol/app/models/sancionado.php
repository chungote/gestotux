<?php

class Sancionado extends AppModel
{
 var $name = 'Sancionado';
 var $useTable = 'sanciones';

 var $belongsTo = array( 'Partido' =>
				array( 'className' => 'Partido',
					 'foreignKey' => 'partido_id',
					 'dependent' => true ),
				'Equipo' =>
				array( 'className' => 'Equipo',
					 'foreignKey' => 'equipo_id',
					 'dependent' => true ),
				'TipoSancion' =>
				array('className' => 'TipoSancion',
				      'foreignKey' => 'tipo_sancion_id' ) );

  var $validate = array(
	'publicado' => 'boolean' );

}
?>