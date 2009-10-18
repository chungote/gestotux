<?php

class CaracteristicasController extends AppController {
  var $name = "Caracteristicas";
  var $components = array( 'othAuth' );
  var $scaffold;
  var $layout = 'admin';
  var $othAuthRestrictions = '*';

}

?>