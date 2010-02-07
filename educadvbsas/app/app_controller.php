<?php
App::import('Core', 'l10n');
class AppController extends Controller {
	var $components = array( 'Auth' );
	var $helpers = array( 'Time', 'Html', 'Form', 'Javascript', 'Paginator' );

	function beforeFilter() {
		$this->Auth->allow( 'display' );
		$this->L10n = new L10n();
		$this->L10n->get("spa");
      }
}
?>