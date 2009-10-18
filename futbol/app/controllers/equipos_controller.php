<?php
class EquiposController extends AppController {

	var $name = 'Equipos';

	function admin_index() {
		$this->layout = 'admin';
		$this->set( 'equipos', $this->paginate( 'Equipo' ) );
		$this->Nav->setEquipo();
		$this->set( 'id_zona', $this->Nav->idZona() );
		$this->set( 'id_torneo', $this->Nav->idTorneo() );
		$this->set( 'nombre_zona', $this->Nav->nombreZona() );
	}

	function admin_agregar() {
		$this->layout = 'admin';
		if( !empty( $this->data ) ) {
			if ( $this->Equipo->save( $this->data ) ) {
				$this->Session->setFlash( "El Equipo ha sido guardado" );
				$this->redirect( array( 'action' => 'admin_index' ) );
			} else {
				$this->Session->setFlash( "Error al intentar guardar el Equipo" );
			}
		}
	}

	function admin_modificar( $id_equipo = null ) {
		$this->layout = 'admin';
		if( !empty( $this->data ) ) {
			if ( $this->Equipo->save( $this->data ) ) {
				$this->Session->setFlash( "El Equipo ha sido guardado" );
				$this->redirect( array( 'action' => 'admin_index' ) );
			} else {
				$this->Session->setFlash( "Error al intentar guardar el Equipo" );
			}
		}
		else
		{
			$this->Equipo->id = $id_equipo;
			$this->set( 'equipo', $this->Equipo->read() );
		}
	}

	function admin_eliminar( $id_equipo = null ) {
		if( $id_equipo == null ) {
			$this->Session->setFlash( "El identificador de equipo es incorrecto" );
			$this->redirect( array( 'action' => 'admin_index' ) );
		}

		$this->Equipo->del( $id_equipo );
		$this->Session->setFlash( 'Equipo eliminado correctamente' );
		$this->redirect( array( 'controller' => 'equipos', 'action' => 'admin_index' ) );
	}

	function admin_publicar( $publicar = 0, $id_equipo = null ) {
		if( $id_equipo == null ) {
			$this->redirect( '/admin/equipos/index' );
		}
		$this->Equipo->id = $id_equipo;
		$this->Equipo->saveField( 'publicado', $publicar );
		$this->Session->setFlash( 'Equipo modificado correctamente' );
		$this->redirect( '/admin/equipos/index' );
	}

}
?>
