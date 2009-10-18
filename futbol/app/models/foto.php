<?php

class Foto extends AppModel {
   var $name = 'Foto';
   var $primaryKey = 'id_foto';

   var $belongsTo = 'Partido';
}
?>