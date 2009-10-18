<?php
class NavComponent extends Object {

	var $controller = null;
		var $datos = array (
		'Torneo' => array( 'id_torneo' => null, 'nombre_torneo' => null ),
		'Fecha'  => array( 'id_fecha'  => null, 'nombre_fecha'  => null ),
		'Zona'   => array( 'id_zona'   => null, 'nombre_zona'   => null ),
		'Equipo' => array( 'id_equipo' => null, 'nombre_equipo' => null ) );
	var $components = array( 'Session' );

	//called before Controller::beforeFilter()
	function initialize(&$controller, $settings = array()) {
		// saving the controller reference for later use
		$this->controller =& $controller;
		if( $this->Session->check( "nav" ) ) {
			// Los datos existen y los cargo
			$this->datos = $this->Session->read( "nav" );
		} else {
			$this->Session->write( "nav", $this->datos );
		}
	}

	function nivel() {
		$nivel = 0;
		foreach( $this->datos as $dato )
		{ if( $dato[ $this->KeyName( $dato, 0 ) ] != null ) { $nivel++; } }
		return $nivel;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// Torneo
	function setTorneo( $id_torneo = null ) {
		$this->datos['Torneo']['id_torneo'] = $id_torneo;
		if( $id_torneo == null ) {
			$this->datos['Torneo']['nombre_torneo'] = null;
			$this->datos['Fecha']['nombre_fecha'] = null;
			$this->datos['Fecha']['id_fecha'] = null;
			$this->datos['Zona']['nombre_zona'] = null;
			$this->datos['Zona']['id_zona'] = null;
			$this->datos['Equipo']['id_equipo'] = null;
			$this->datos['Equipo']['nombre_equipo'] = null;
		}
		$this->Session->write( "nav", $this->datos );
	}

	function setNombreTorneo( $torneo = null ) {
		$this->datos['Torneo']['nombre_torneo'] = $torneo;
		if( $torneo == null ) { $this->datos['Torneo']['id_torneo'] = null; }
		$this->Session->write( "nav", $this->datos );
	}

	function nombreTorneo() { return $this->datos['Torneo']['nombre_torneo']; }
	function idTorneo() { return $this->datos['Torneo']['id_torneo']; }

	////////////////////////////////////////////////////////////////////////////////////
	// Fecha
	function setFecha( $id_fecha = null ) {
		$this->datos['Fecha']['id_fecha'] = $id_fecha;
		if( $id_fecha == null ) { $this->datos['Fecha']['nombre_fecha'] = null; }
		$this->Session->write( "nav", $this->datos );
	}

	function setNombreFecha( $fecha = null ) {
		$this->datos['Fecha']['nombre_fecha'] = $fecha;
		if( $fecha == null ) { $this->datos['Fecha']['id_fecha'] = null; }
		$this->Session->write( "nav", $this->datos );
	}

	function nombreFecha() { return $this->datos['Fecha']['nombre_fecha']; }
	function idFecha() { return $this->datos['Fecha']['id_fecha']; }

	////////////////////////////////////////////////////////////////////////////////////
	// Zona
	function setZona( $id_zona = null ) {
		$this->datos['Zona']['id_zona'] = $id_zona;
		if( $id_zona == null ) { $this->datos['Zona']['nombre_zona'] = null; }
		$this->Session->write( "nav", $this->datos );
	}

	function setNombreZona( $zona = null ) {
		$this->datos['Zona']['nombre_zona'] = $zona;
		if( $zona == null ) { $this->datos['Zona']['id_zona'] = null; }
		$this->Session->write( "nav", $this->datos );
	}

	function nombreZona() { return $this->datos['Zona']['nombre_zona']; }
	function idZona() { return $this->datos['Zona']['id_zona']; }

	////////////////////////////////////////////////////////////////////////////////////
	// Equipo
	function setEquipo( $id_equipo = null ) {
		$this->datos['Equipo']['id_equipo'] = $id_equipo;
		if( $id_equipo == null ) { $this->datos['Equipo']['nombre_equipo'] = null; } else { $this->setFecha(); }
		$this->Session->write( "nav", $this->datos );
	}

	function setNombreEquipo( $equipo = null ) {
		$this->datos['Equipo']['nombre_equipo'] = $equipo;
		if( $equipo == null ) { $this->datos['Equipo']['id_equipo'] = null; }
		$this->Session->write( "nav", $this->datos );
	}

	function nombreEquipo() { return $this->datos['Equipo']['nombre_equipo']; }
	function idEquipo() { return $this->datos['Equipo']['id_equipo']; }


	function limpiar() {
		$this->datos['Torneo']['nombre_torneo'] = null;
		$this->datos['Torneo']['id_torneo'] = null;
		$this->datos['Fecha']['nombre_fecha'] = null;
		$this->datos['Fecha']['id_fecha'] = null;
		$this->datos['Zona']['nombre_zona'] = null;
		$this->datos['Zona']['id_zona'] = null;
		$this->datos['Equipo']['id_equipo'] = null;
		$this->datos['Equipo']['nombre_equipo'] = null;
	}

      function KeyName(array $a, $pos) {
		$temp = array_slice($a, $pos, 1, true);
		return key($temp);
	}

}
?>