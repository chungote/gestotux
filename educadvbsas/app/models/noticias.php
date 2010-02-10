<?php
class Noticias extends AppModel {
 var $useTable = 'noticias';
 var $primaryKey = 'id_noticia';
 var $displayField = 'titulo';

 var $validate = array( 
	'titulo' => array(
		'rule' => 'notEmpty',
		'required' => true,
		'message' => 'Un titulo es necesario' ),
	'publicado' => array(
		'rule' => array('boolean'),
		'required' => true,
		'message' => 'Elija si esta publicado o no' ),
	'subtitulo' => array(
		'rule' => 'notEmpty',
		'reiquired' => true,
		'message' => 'Ingrese un subtitulo' ),
	'resumen' => array(
		'rule' => 'notEmpty',
		'required' => false,
		'message' => 'El resumen no debe estar vacio' ),
	'textocompleto' => array(
		'rule' => 'notEmpty',
		'required' => true,
		'message' => 'Ingrese un contenido' ),
	'colegio_id' => array(
		'allowEmpty' => true,
		'required' => false  )
 	);

  var $belongsTo = array( 'Colegios' );
  var $hasMany = array( 'NoticiasFotos' );

	function ultimas() {
		return $this->find( 'all', array( 'conditions' => array( 'Noticias.publicado' => true ), 'order' => array( 'Noticias.modified' => 'desc' ), 'limit' => 3 ) );
	}
}
?>