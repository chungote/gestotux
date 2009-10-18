<?php
/*******************************
TABLE `anuncios` (
  `id_anuncio` bigint(1) NOT NULL auto_increment,
  `titulo` text NOT NULL,
  `contenido` longblob NOT NULL,
  `created` datetime NOT NULL,
  `modified` datetime NOT NULL,
  `publicado` tinyint(3) NOT NULL default '0',
  `fecha_fin_publicado` tinyint(3) NOT NULL,
  PRIMARY KEY  (`id_anuncio`)
*/
class Anuncio extends AppModel {
 var $name = 'Anuncio';
 var $primaryKey = 'id_anuncio';

 var $validate = array(
    'titulo' => array(
		'rule' => 'notEmpty',
		'required' => true,
		'message' => 'El titulo no debe estar vacio' ),
    'contenido' => array(
		'rule' => 'notEmpty',
		'required' => true,
		'message' => 'El contenido no debe estar vacio'  ),
    'publicado' => array(
		'rule' => array('boolean'),
		'message' => 'Por favor indique un valor logico para publicado' ),
    'fecha_fin_publicado' => array( 'trule' => 'date' )
 );
}
?>