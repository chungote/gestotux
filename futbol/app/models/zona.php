<?php
/*
CREATE TABLE `futbol`.`zonas` (
`id_zona` INT NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`nombre_zona` TEXT NOT NULL ,
`torneo_id` INT NOT NULL ,
`descripcion` TEXT NOT NULL
) ENGINE = InnoDB;
*/
class Zona extends AppModel {
	var $name = 'Zona';

	var $tableName = "zonas";
	var $primaryKey = "id_zona";
	var $displayField = "nombre_zona";

	var $belongsTo = "Torneo";
	var $hasMany = "TorneoZonaEquipo";

	function beforeDelete( $cascade ) {
		// Busco si tiene zonas asociadas
		$this->Session->setFlash( 'No se pueden eliminar zonas todavia, porque de existir partidos quedarian huerfanos. Despubliquelas para que desaparezcan de la pagina.' );
		return false;
	}	
}

?>