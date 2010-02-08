<?php
App::import('Core', 'l10n');
class AppController extends Controller {
	var $components = array( 'Auth' );
	var $helpers = array( 'Time', 'Html', 'Form', 'Javascript', 'Paginator' );

	function beforeFilter() {
		$this->set( 'col_der', true );
		$this->set( 'col_izq', true );
		$this->Auth->userModel = 'personal';
		$this->Auth->fields = array( 'username' => 'usuario', 'password' => 'contraseña' );
		$this->Auth->allow( 'display' );
		$this->L10n = new L10n();
		$this->L10n->get("spa");
      }
}
?>