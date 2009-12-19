<?php
/***************************************************************************
CREATE TABLE IF NOT EXISTS `sab_saludos` (
  `de` bigint(20) NOT NULL COMMENT 'uid del enviador',
  `para` bigint(20) NOT NULL COMMENT 'uid del destinatario',
  `titulo` text NOT NULL,
  `mensaje` text NOT NULL COMMENT 'contenido del mensaje',
  `imagen_id` bigint(20) default NULL COMMENT 'imagen del mensaje',
  `fecha` timestamp NOT NULL default CURRENT_TIMESTAMP COMMENT 'fecha en que se envio',
  `visto` tinyint(1) NOT NULL,
  `saludo_id` bigint(20) NOT NULL auto_increment COMMENT 'numero de mensaje',
  PRIMARY KEY  (`saludo_id`),
  KEY `de` (`de`,`para`),
  KEY `para` (`para`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=9 ;
*/


class Saludos extends AppModel {

  var $name = 'Saludos';
  var $tableName = "saludos";
  var $primaryKey = 'id';

  var $belongsTo = 'Imagenes';

  function noleidos( $uid ) {
    return $this->find( 'count', array( 'conditions' => array( 'para' => $uid, 'visto' => 0, 'aeliminar' => null ) ) );
  }

  function enviados( $uid ) {
    return $this->find( 'count', array( 'conditions' => array( 'de' => $uid, 'aeliminar' => null ) ) );
  }

  function guardar( $id_destinatario, $id_remitente, $titulo, $contenido, $imagen_id ) {
	$datos = array ( 'Saludos' =>
 		array( 'de' => $id_remitente,
			 'para' => $id_destinatario,
			 'titulo' => $titulo,
			 'mensaje' => $contenido,
			 'imagenes_id' => $imagen_id,
			 'fecha' => time(),
			 'visto' => 0 ) );
	if( $this->save( $datos ) ) {
		return true;
	} else { return false; }
  }

  function detalleNoLeido( $uid ) {
   return $this->find( 'all', array( 'conditions' => array( /*'visto' => 0,*/ 'para' => $uid, 'aeliminar' => null ), 'order' => array( 'fecha' => 'desc' ) ) );
  }

  function buscarNuevo( $de, $para ) {
   return $this->find( 'count', array( 'conditions' => array( 'visto' => 0, 'para' => $para, 'de' => $de, 'aeliminar' => null ) ) );
  }

  function detalleNuevo( $de, $para ) {
   return $this->find( 'all', array( 'conditions' => array( 'visto' => 0, 'para' => $para, 'de' => $de, 'aeliminar' => null ), 'order' => array( 'fecha' => 'desc' ) ) );
  }

  function detalleViejo( $de, $para ) {
   return $this->find( 'all', array( 'conditions' => array( 'visto' => 1, 'para' => $para, 'de' => $de, 'aeliminar' => null ), 'order' => array( 'fecha' => 'desc' ) ) );
  }

  function buscarEnviadosHoy( $id_remitente ) {
    $datos = $this->find( 'all', array( 'conditions' => array( 'de' => $id_remitente, 'fecha >= '.strtotime( "-1 day" ), 'aeliminar' => null ),
						   'fields' => array( 'para' ) ) );
    $ret = array();
    foreach( $datos  as $d ) {
     $ret[] = $d['Saludos']['para'];
    }
    return $ret;
  }

  function marcarComoLeido( $de, $para, $fecha ) {
   $this->query( "UPDATE sab_saludos SET visto = 1 WHERE de = $de AND para = $para AND fecha = $fecha" );
  }

  function marcarAEliminar( $de, $para, $fecha ) {
	$this->query( "UPDATE sab_saludos SET aeliminar = 1 WHERE de = $de AND para = $para AND fecha = $fecha" );
  }

  function guardarPublicado( $de, $para, $fecha, $id_publicacion ) {
	$this->query( "UPDATE sab_saludos SET publicado = '$id_publicacion' WHERE de = $de AND para = $para AND fecha = $fecha" );
	//$this->log( "UPDATE sab_saludos SET publicado = '$id_publicacion' WHERE de = $de AND para = $para AND fecha = $fecha" );
  }

  function guardarDevuelto( $de, $para, $fecha ) {
      $this->query( "UPDATE sab_saludos SET devuelto = 1 WHERE de = $de AND para = $para AND fecha = $fecha" );
  }

  function publicado( $de, $para, $fecha ) {
	$dato = $this->find( 'first', array( 'conditions' => array( 'de' => $de, 'para' => $para, 'fecha' => $fecha, 'aeliminar' => null ), 'fields' => 'publicado' ) );
	return $dato['Saludos']['publicado'];
  }

  function eliminar_nopublicados() {
	$this->deleteAll( array( 'conditions' => array( 'aeliminar' => 1, 'publicado' => null ) ) );
  }

  function eliminar_vencidos() {
	//$this->updateAll( array( 'aeliminar' => 1 ), array( 'fecha < '.strtotime( "+3 months" ) ) );
	$this->log( array( 'aeliminar' => 1 ), array( 'fecha < '.strtotime( "+3 months" ) );
  }

}
?>