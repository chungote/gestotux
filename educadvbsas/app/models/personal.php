<?php
class Personal extends AppModel {
  var $name = 'Personal';
  var $useTable = 'personal';
  var $primaryKey = 'id_personal';

  var $validate = array(
	'razon_social' => array(
		'rule' => 'notEmpty',
		'required' => true,
		'message' => 'Por favor, ingrese un nombre completo'
	),
	'usuario' => array(
		'rule' => 'notEmpty',
		'required' => true,
		'message' => 'Por favor ingrese un nombre de usuario'
	),
	'contraseña' => array(
		'rule' => 'notEmpty',
		'required' => true,
		'message' => 'Ingrese una contraseña'
	),
	'cargo' => array(
		'rule' => 'alphaNumeric',
		'required' => false
	),
	'reseña' => array(
		'rule' => 'alphaNumeric',
		'required' => false
	)
  );
}
?>