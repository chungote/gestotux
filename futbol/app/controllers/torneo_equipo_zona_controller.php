<?php
class TorneoEquipoZonaController extends AppController {

	var $name = 'TorneoEquipoZona';
	var $uses = 'TorneoZonaEquipo';
	var $layout = 'admin';

	function admin_asignar( $id_equipo = null ) {
		if( $this->Nav->idEquipo() == null ) {
			$this->Nav->setEquipo( $id_equipo );
			$this->TorneoZonaEquipo->Equipo->id = $id_equipo;
			$this->Nav->setNombreEquipo( $this->TorneoZonaEquipo->Equipo->field( 'nombre' ) );
		}
		// Busco todas las relaciones con ese equipo
		if( $this->Nav->idTorneo() == null )
		{ $this->set( 'datos', $this->paginate( 'TorneoZonaEquipo', array( 'TorneoZonaEquipo.equipo_id' => $this->Nav->idEquipo() ) ) ); }
		else
		{ $this->set( 'datos', $this->paginate( 'TorneoZonaEquipo', array( 'TorneoZonaEquipo.equipo_id' => $this->Nav->idEquipo(), 'TorneoZonaEquipo.torneo_id' => $this->Nav->idTorneo() ) ) ); }
		$this->set( 'id_zona', $this->Nav->idZona() );
	}

	function admin_agregar( $novolver = false ) {
		if( !isset( $this->data ) )
		{
			$this->set( 'zonas', $this->TorneoZonaEquipo->Zona->find( 'list', array( 'conditions' => array( 'Zona.torneo_id' => $this->Nav->idTorneo() ) ) ) );
			$this->set( 'id_torneo', $this->Nav->idTorneo() );
			$this->set( 'nombre_torneo', $this->Nav->nombreTorneo() );
			$this->set( 'id_equipo', $this->Nav->idEquipo() );
			$this->set( 'nombre_equipo', $this->Nav->nombreEquipo() );
		}
		else
		{
			// Guardar la asignacion
			if( $this->TorneoZonaEquipo->save( $this->data ) )
			{
				$this->Session->setFlash( 'La asignaci&oacute;n se ha guardado correctamente' );
				if( !$novolver ) { $this->redirect( '/admin/torneo_equipo_zona/asignar' ); }
			}
			else
			{
				$this->Session->setFlash( 'No se pudo guardar la asignaci&oacute;n. Probablemente ya exista una asignaci&oacute;n de zona para este equipo en el torneo que se encuentra actualmente.' );
				if( !$novolver ) { $this->redirect( '/admin/torneo_equipo_zona/asignar' ); }
			}
		}
	}

	function admin_asigna_directo( $id_torneo, $id_equipo, $id_zona ) {
		$this->data = array( 'TorneoZonaEquipo' => array( 'torneo_id' => $id_torneo, 'equipo_id' => $id_equipo, 'zona_id' => $id_zona ) );
		$this->admin_agregar( true );
		$this->redirect( '/admin/equipos/index' );
	}

	function admin_eliminar( $id_equipo = null, $id_torneo = null, $id_zona = null ) {
		if( $this->TorneoZonaEquipo->deleteAll( array( 'equipo_id' => $id_equipo, 'torneo_id' => $id_torneo, 'zona_id' => $id_zona ), true ) )
		{
			$this->Session->setFlash( 'Asignaci&oacute;n eliminada correctamente' );
			$this->redirect( '/admin/torneo_equipo_zona/asignar' );
		}
		else
		{
			$this->Session->setFlash( 'No se pudo eliminar la asignaci&oacute;n. Seguramente ya existen partidos jugados que quedarian huerfanos si se elimina la asignaci&oacute;n.' );
			$this->redirect( '/admin/torneo_equipo_zona/asignar' );
		}
	}
}
?>
