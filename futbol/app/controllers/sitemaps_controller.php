<?php
class SitemapsController extends AppController{

	var $name = 'Sitemaps';
	var $uses = array('Anuncios','Partidos');
	var $helpers = array('Time');
	var $components = array('RequestHandler');

	function beforeFilter() {
		$this->Auth->allow( 'index' );
	}

	function index (){
		$this->RequestHandler->respondAs('xml');
		$this->set( 'anuncios', $this->Anuncios->find( 'all', array( 'conditions' => array( 'Anuncios.publicado' => 1 ) ) ) );
		$this->set( 'partidos', $this->Partidos->find( 'all', array( 'conditions' => array( 'Partidos.publicado' => 1 ) ) ) );
		//debug logs will destroy xml format, make sure were not in drbug mode
		Configure::write ('debug', 0);
	}
}
?>