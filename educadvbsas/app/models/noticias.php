<?php
class Noticias extends AppModel {
 var $useTable = 'noticias';
 var $primaryKey = 'id_noticia';

 var $validate = array( 'titulo' => array( 'alphaNumeric' => array( 'rule' => 'notEmpty', 'reiquired' => true, 'message' => 'Un titulo es necesario' ) ),
	'publicado' => array( 'rule' => 'boolean', 'required' => true, 'message' => 'Elija si esta publicado o no' ),
	'subtitulo' => array( 'rule' => 'alphaNumeric', 'required' => true, 'message' => 'Ingrese un subtitulo' ),
	'resumen' => array( 'rule' => 'aplhaNumeric' ),
	'texto_completo' => array( 'rule' => 'notEmpty', 'required' => true, 'message' => 'Ingrese un contenido' ),
	'fecha_publicado' => array( 'rule' => 'date', 'required' => true )
 	);

  var $belongsTo = array( 'Colegio' );

	function ultimas() {
		$this->find( 'all', array( 'conditions' => array( 'publicado' => 1 ), 'order' => array( 'fecha_publicado' => 'desc' ), 'limit' => 3 ) );
	}
}
?>