<?php
class Caracteristica extends AppModel {
   var $name = 'Caracteristica';
    var $validate = array( 'name' => VALID_NOT_EMPTY );

  function beforeDelete()
  {
	///@todo Verifico que no este en uso
	return false;
  }
}
?>