<?php

class Propiedad extends AppModel
{
 var $name = "propiedad";
 var $useTable = "propiedades";
 var $belongsTo = array(
			'Situacion' =>
				array( 'className' => 'Situacion',
					'fields' => array( 'name' ),
					'foreignKey' => 'situacion_id',
					'dependent' => 'false' ),
			'Zona' =>
				array( 'className' => 'Zona',
					'fields' => array( 'name', 'caracteristicas' ),
					'foreignKey' => 'zona_id',
					'dependent' => 'false' ),
			'Tipo' =>
				array( 'className' => 'Tipo',
					'foreignKey' => 'tipo_id',
					'dependent' => 'false' ),
			'Moneda' =>
				array( 'className' => 'Moneda',
					 'foreignKey' => 'moneda_id',
					 'dependent' => 'false' )
		 );
 var $hasAndBelongsToMany = array(
			'Caracteristicas' =>
				array( 'className' => 'caracteristica',
					'joinTable' => 'propiedad_caracteristica',
					'foreignKey' => 'propiedad_id',
					'associationForeignKey' => 'caracteristica_id',
					'conditions' => '',
					'order' => '',
					'limits' => '',
					'unique' => true,
					'finderQuery' => '',
					'deleteQuery' => '' )
			);

 var $hasMany = array(
			'Imagenes' =>
				array( 'className' => 'imagen',
					 'foreignKey' => 'propiedad_id',
					 'dependent' => true
					)
				);

  // Validaciones
  var $validate = array(
			'direccion' => VALID_NOT_EMPTY,
			'ciudad' => VALID_NOT_EMPTY,
			'provincia' => VALID_NOT_EMPTY,
			'codigo_postal' => VALID_NOT_EMPTY,
			'precio' => VALID_NOT_EMPTY,
			'precio' => VALID_NUMBER,
			'banos' => VALID_NOT_EMPTY,
			'banos' => VALID_NUMBER,
			'pisos' => VALID_NOT_EMPTY,
			'pisos' => VALID_NUMBER,
			'cochera' => VALID_NOT_EMPTY,
			'cochera' => VALID_NUMBER,
			'tipo_id' => VALID_NOT_EMPTY,
			'metros_cuadrados' => VALID_NOT_EMPTY,
			'metros_cuadrados' => VALID_NUMBER,
			'dimension_x' => VALID_NOT_EMPTY,
			'dimension_x' => VALID_NUMBER,
			'dimension_y' => VALID_NOT_EMPTY,
			'dimension_y' => VALID_NUMBER,
			'zona_id' => VALID_NOT_EMPTY,
			'situacion_id' => VALID_NOT_EMPTY,
			'estado_id' => VALID_NOT_EMPTY );
}
?>