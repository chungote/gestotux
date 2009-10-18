<?php
class MapaController extends AppController{

	var $name = 'Mapa';
//	var $uses = array('Post', 'Info');
	var $helpers = array('Time');
	var $components = array('RequestHandler');

	function index (){	
//		$this->set('posts', $this->Post->find('all', array( 'conditions' => array('is_published'=>1,'is_public'=>'1'), 'fields' => array('date_modified','id'))));
//		$this->set('pages', $this->Info->find('all', array( 'conditions' => array('ispublished' => 1 ), 'fields' => array('date_modified','id','url'))));
//debug logs will destroy xml format, make sure were not in drbug mode
Configure::write ('debug', 0);
	}
}
?>
