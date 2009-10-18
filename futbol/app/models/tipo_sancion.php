<?php

class TipoSancion extends AppModel {
  var $name = 'TipoSancion';
  var $primaryKey = 'id_tipo_sancion';
  var $displayField = 'nombre';

  var $hasMany = array(
		'Sancionados' =>
			array( 'className' => 'Sancionado',
				 'dependent' => true )
		);
}
?>