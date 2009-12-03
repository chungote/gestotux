<?php

class ZonasController extends AppController {
  var $name = "Zonas";
  var $components = array( 'othAuth' );
  var $scaffold;
  var $layout = 'admin';

	function lista()
	{
		return $this->Zona->generateList( null, null, null, '{n}.Zona.id', '{n}.Zona.name' );
	}
}

?>