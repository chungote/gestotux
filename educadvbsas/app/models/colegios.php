<?php
class Colegios extends AppModel {
  var $name = "Colegios";
  var $useTable = 'colegios';
  var $primaryKey = 'id_colegio';
  var $displayField = 'siglas';
 
  var $validate = array( 
	'publicado' => array( 'rule' => array( 'boolean' ), 'required' => true, 'message' => 'Ingrese si esta publicado o no' ),
	'siglas' => array( 'rule' => 'notEmpty', 'required' => false, 'message' => 'Ingrese las siglas para el colegio' ),
	'nombre' => array( 'rule' => 'notEmpty', 'required' => true, 'message' => 'Ingrese un nombre para el colegio' ),
	'imagen_banner' => array( 'rule' => 'alphaNumeric', 'required' => false, 'allowEmpty' => true )
  );

  var $hasMany = array( 'Noticias' );
}
?>