<?php

class Equipo extends AppModel {

  var $name = 'Equipo';
  var $primaryKey = 'id_equipo';
  var $displayField = 'nombre';

  var $hasMany = 'TorneoZonaEquipo';

}
?>