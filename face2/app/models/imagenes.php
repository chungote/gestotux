<?php

class Imagenes extends AppModel {
  var $name = "Imagenes";
  var $primaryKey = "iid";

  var $belongsToMany = 'Saludos';

	function fotosPublicas() {
		return $this->find( 'list', array( 'conditions' => array( 'privada' => 0, 'tipo' => 'imagenes', 'publicada' => 1 ), 'fields' => array( 'miniatura' ) ) );
	}

	function flashPublicos() {
		return $this->find( 'list', array( 'conditions' => array( 'privada' => 0, 'tipo' => 'flash', 'publicada' => 1 ), 'fields' => array( 'miniatura' ) ) );
	}

	function miniatura( $id_imagen ) {
		return $this->find( 'first', array( 'conditions' => array( 'iid' => $id_imagen, 'publicada' => 1 ), 'fields' => array( 'iid', 'miniatura', 'texto' ) ) );
	}

	function ruta_miniatura( $id_imagen ) {
		$datos = $this->find( 'first', array( 'conditions' => array( 'iid' => $id_imagen, 'publicada' => 1 ), 'fields' => array( 'iid', 'miniatura' ) ) );
		return Router::url( '/', true ) . $datos['Imagenes']['miniatura'];
	}

	function texto( $id_imagen ) {
		$datos = $this->find( 'first', array( 'conditions' => array( 'iid' => $id_imagen, 'publicada' => 1 ), 'fields' => array( 'iid', 'texto' ) ) );
		return $datos['Imagenes']['texto'];
	}

	function ultimas() {
		return $this->find( 'all', array( 'conditions' => array( 'publicada' => 1 ), 'order' => array( 'iid' => 'desc' ), 'limit' => '3' ) );
	}
}

?>