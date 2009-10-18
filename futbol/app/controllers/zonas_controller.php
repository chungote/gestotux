<?php
class ZonasController extends AppController {

	var $name = 'Zonas';

	function beforeFilter() {
		$this->Auth->allow( 'index' );
	}

	function admin_index( $id_torneo = null ) {
		// Muestra la lista de zonas
		$this->layout = 'admin';
		if( isset( $this->data['zona'] ) )
		{ $this->Nav->setTorneo( $this->data['zona']['id_torneo'] ); }
		if( $this->Nav->idTorneo() == null && $id_torneo == null ) { $this->Session->setFlash( "Elija un torneo para agregar una zona." ); $this->redirect( '/admin/torneos' ); }
		if( $this->Nav->idTorneo() == null ) { $this->Nav->setTorneo( $id_torneo ); }
		$this->set( 'zonas', $this->paginate( 'Zona', array( 'Zona.torneo_id' => $this->Nav->IdTorneo() ) ) );
		$lista_torneos = $this->Zona->Torneo->find( 'list', array( 'conditions' => array( 'publicado' => 1 ) ) );
		$this->set( 'lista_torneos', $lista_torneos  );
		$this->Nav->setNombreTorneo( $lista_torneos[ $this->Nav->idTorneo() ] );
		$this->set( 'id_torneo', $this->Nav->IdTorneo() );
 	}

	function admin_publicar( $publicar, $id_zona ) {
		$this->Zona->id = $id_zona;
		$this->Zona->saveField( 'publicado', $publicar );
		$this->Session->setFlash( 'Zona modificada correctamente' );
		$this->redirect( array( 'action' =>'admin_index' ) );
	}

	function admin_agregar( $id_torneo = null ) {
  		$this->layout = 'admin';
		if ( !empty( $this->data ) ) {
			if ( $this->Zona->save( $this->data ) ) {
				$this->Session->setFlash( "La zona ha sido guardado" );
				$this->redirect( array( 'action' => 'admin_index' ) );
			} else {
				$this->Session->setFlash( "Error al intentar guardar la zona" );
			}
	 	 } else {
 			$this->set( 'lista_torneos', $this->Zona->Torneo->find( 'list' ) );
			$this->set( 'id_torneo', $this->Nav->idTorneo() );
	  	}
	}

	function admin_modificar( $id_zona = null ) {
		$this->layout = 'admin';
		if( empty( $this->data ) )
		{
			$this->Zona->id = $id_zona;
			$this->set( 'datos', $this->Zona->read() );
			$this->set( 'lista_torneos', $this->Zona->Torneo->find( 'list' ) );
		}
		else
		{
			if ( $this->Zona->save( $this->data ) ) {
				$this->Session->setFlash( "La zona ha sido guardado" );
				$this->redirect( array( 'action' => 'admin_index' ) );
			} else {
				$this->Session->setFlash( "Error al intentar guardar la zona" );
			}
		}
		
	}

}
?>
