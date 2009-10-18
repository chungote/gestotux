<?php

class TorneoZonaEquipo extends AppModel {
	var $name = "TorneoZonaEquipo";
	var $displayField = 'equipo_id';
	var $primaryKey = 'equipo_id';

	var $belongsTo = array( 'Torneo', 'Zona', 'Equipo' );

	function beforeSave() {
		//Verifico que no exista ya la asignaci&oacute;n
		if( $this->find( 'count', array( 'conditions' =>
						 array( 'TorneoZonaEquipo.torneo_id' => $this->data['TorneoZonaEquipo']['torneo_id'],
							  'TorneoZonaEquipo.zona_id' => $this->data['TorneoZonaEquipo']['zona_id'],
							  'TorneoZonaEquipo.equipo_id' => $this->data['TorneoZonaEquipo']['equipo_id'] ) ) )  > 0 )
		{ return false; }
		else
		{ return true; }
	}

	function beforeDelete(boolean $cascade) {
		//Verificar que no existan partidos jugados con este torneo, zona y equipo

	}
}
?>