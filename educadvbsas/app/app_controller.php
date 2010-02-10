<?php
App::import('Core', 'l10n');
class AppController extends Controller {
	var $components = array( 'Auth' );
	var $helpers = array( 'Time', 'Html', 'Form', 'Javascript', 'Paginator' );

	function beforeFilter() {
		$this->columnas( true, true );
		$this->Auth->userModel = 'personal';
		$this->Auth->fields = array( 'username' => 'usuario', 'password' => 'contraseña' );
		$this->Auth->allow( '*' );
		$this->L10n = new L10n();
		$this->L10n->get("spa");
      }

	function columnas( $der = false, $izq = false ) {
		$this->set( 'col_der', $der );
		$this->set( 'col_izq', $izq );
	}
}
?>