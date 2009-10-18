<?php

class SituacionesController extends AppController {
  var $name = "Situaciones";
  var $components = array( 'othAuth' );
  var $scaffold;
  var $uses = "Situacion";
  var $layout = 'admin';
  var $othAuthRestrictions = '*';
}

?>