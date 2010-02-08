<?php
class ColegiosController extends AppController {
	var $name = 'Colegios';
	var $uses = 'Colegios';
	var $scaffold;

	function beforeFilter() {
		$this->set( 'col_der', false );
		$this->set( 'col_izq', false );
	}
}
?>
