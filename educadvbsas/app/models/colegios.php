<?php
class Colegios extends AppModel {
  var $name = "Colegios";
  var $useTable = 'colegios';
  var $primaryKey = 'id_colegio';
 
  var $validate = array( 
	'publicado' => array( 'rule' => 'boolean', 'required' => true, 'message' => 'Ingrese si esta publicado o no' ),
	'siglas' => array( 'rule' => 'alphaNumeric', 'required' => false, 'message' => 'Ingrese las siglas para el colegio' ),
	'nombre' => array( 'rule' => 'alphaNumeric', 'required' => true, 'message' => 'Ingrese un nombre para el colegio' ),
	'imagen_banner' => array( 'rule' => 'alphaNumeric', 'required' => false )
  );

  var $hasMany = array( 'Noticias' );
}
?>