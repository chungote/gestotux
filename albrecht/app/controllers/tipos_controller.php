<?php
class TiposController extends AppController {
   var $name = 'Tipos';
   var $components = array( 'othAuth' );
   var $scaffold;
   var $layout = 'admin';
   var $othAuthRestrictions = array( 'add', 'modify', 'delete' );

	function lista()
	{
		return $this->Tipo->generateList( null, null, null, '{n}.Tipo.id','{n}.Tipo.nombre' );
	}
}
?>