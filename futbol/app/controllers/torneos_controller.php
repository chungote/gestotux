<?php
class TorneosController extends AppController {
	var $name = 'Torneos';
	var $helpers = array( 'Fck', 'TabDisplay' );
	var $cacheQueries = true;
	var $uses = array( 'Torneo', 'Goleadores', 'Equipo' );
	//var $scaffold;

	function beforeFilter() {
		// Metodos que usuarios no loggeados pueden usar del controlador
		$this->Auth->allow( 'index', 'view', 'reglamento', 'actuales', 'anteriores', 'goleadores', 'goleadoresZona' );
		$this->L10n = new L10n();
		$this->L10n->get("spa");
	}

	function index( $id_torneo = null ) {
		// Muestra la informacion del torneo actual mas link para torneos anteriores
		// Selecciono el torneo que no este con status de archivado
		$torneo = array();
		if( $id_torneo == null )
		{
			$ts = $this->Torneo->find( 'first', array( 'order' => 'Torneo.fecha_fin DESC', 'conditions' => array( 'publicado' => 1 ), 'fields' => 'id_torneo', 'recursive' => -1 ) );
			$id_torneo = $ts['Torneo']['id_torneo'];
			
		}
		$this->Torneo->id = $id_torneo;
		$this->set( 'torneo', $this->Torneo->read() );
	}

	function reglamento( $id_torneo = null ) {
		if( $id_torneo == null )
		{
			// Busco el torneo actual
			$id = $this->Torneo->find( 'first', array( 'conditions' => array( 'Torneo.publicado' => 1, 'Torneo.fecha_fin >=' => date( 'y-m-d' ) ), 'fields' => 'id_torneo' ) );
			$id_torneo = $id['Torneo']['id_torneo'];
		}
		$datos = $this->Torneo->find( 'first', array( 'conditions' => array( 'id_torneo' => $id_torneo ) ) );
		$this->set( 'torneo', $datos['Torneo'] );
	}

	function anteriores() {
		$this->set( 'torneos', $this->Torneo->find( 'all', array( 'conditions' => array( 'Torneo.publicado' => 1 ), 'recursive' => -1 ) ) );
	}

	function admin_index(){
		$this->layout = 'admin';
		$this->set( 'datos', $this->Torneo->find( 'all' ) );
		$this->Nav->setTorneo( null );
	}

	function admin_agregar() {
		$this->layout = 'admin';
		if( !empty( $this->data ) ) {
			if ( $this->Torneo->save( $this->data ) ) {
				$this->Session->setFlash( "El Torneo ha sido guardado" );
				$this->redirect( array( 'action' => 'admin_index' ) );
			} else {
				$this->Session->setFlash( "Error al intentar guardar el torneo" );
			}
		}
	}

	function admin_modificar( $id_torneo = null ) {
		$this->layout = 'admin';
		$this->Torneo->id = $id_torneo;
		if( empty( $this->data ) ) {
			$this->data = $this->Torneo->read();
		} else {
			if( $this->Torneo->save( $this->data ) ) {
				$this->flash( 'El torneo fue actualizado', '/admin/torneos' );
			}
		}
	}

	function admin_eliminar( $id_torneo = null )
	{
		$this->layout = 'admin';
		if( $id_torneo == null ) {
			 $this->Session->setFlash( 'Id de campeonato incorrecto' );
			 $this->redirect( '/admin/torneos/index' );
		} else if( $this->Torneo->del( $id_torneo ) ) {
			$this->Session->setFlash( 'Torneo eliminado correctamente' );
		} else {
			$this->Session->setFlash( 'Error al intentar eliminar el torneo' );
		}
		// Verificar si se quiere eliminar las fechas del campeonato y todo lo relacionado con esas fechas
		$this->redirect( '/admin/torneos/index' );
	}

	function admin_publicar( $publicar, $id ) {
		$this->Torneo->id = $id;
		$this->Torneo->saveField( 'publicado', $publicar );
		$this->redirect( '/admin/torneos/index' );
	}

	function actuales() {
		$this->layout = '';
		$torneos = $this->Torneo->find( 'all', array( 'conditions' => array( 'Torneo.publicado' => 1, 'Torneo.fecha_inicio <=' => date('Y-m-d'), 'Torneo.fecha_fin >=' => date('Y-m-d') ), 'fields' => array( 'id_torneo', 'name' ), 'recursive' => -1 ) );
		return $torneos;
	}

	function goleadores( $id_torneo = null ) {
		if( $id_torneo == null )
		{ $actuales = $this->Torneo->find( 'first', array( 'conditions' => array( 'Torneo.publicado' => 1, 'Torneo.fecha_inicio <=' => date('Y-m-d'), 'Torneo.fecha_fin >=' => date('Y-m-d') ), 'fields' => array( 'id_torneo', 'name' ), 'recursive' => -1 ) );
		  $id_torneo = $actuales['Torneo']['id_torneo']; 
		  $this->set( 'nombre_torneo', $actuales['Torneo']['name'] );
		  unset( $actuales );
		} else {
			$this->Torneo->id = $id_torneo;
			$this->set( 'nombre_torneo', $this->Torneo->field( 'name' ) );
		}
		$this->set( 'zonas', $this->Torneo->Fechas->Partido->Zona->find( 'all', array( 'conditions' => array( 'Zona.publicado' => 1, 'Zona.torneo_id' => $id_torneo ) ) ) );
		$this->set( 'id_torneo', $id_torneo );
		$this->render( 'goleadores_general' );
	}

	function goleadoresZona( $id_torneo = null, $id_zona = null ) {
		//Busco los partidos del torneo
		$ids_fechas = $this->Torneo->Fechas->find( 'list', array( 'conditions' => array( 'Fechas.publicado' => 1, 'Fechas.torneo_id' => $id_torneo ), 'fields' => 'id_fecha' ) );
		$ids_partidos = $this->Torneo->Fechas->Partido->find( 'list', array( 'conditions' => array( 'Partido.publicado' => 1, 'Partido.fecha_id' => $ids_fechas, 'Partido.zona_id' => $id_zona ), 'fields' => 'id_partido' ) );
		unset( $ids_fechas );
		$goleadores = $this->Goleadores->find( 'all',
								 array( 'conditions' => array( 'Goleadores.publicado' => 1, 'Goleadores.partido_id' => $ids_partidos ),
									  'fields' => array( 'DISTINCT Goleadores.nombre', 'Goleadores.equipo_id', 'COUNT( Goleadores.nombre ) AS goles' ),
									  'group' => array( 'Goleadores.nombre' ),
									  'order' => array( 'goles' => 'desc' ),
									  'recursive' => 0 ) );
		unset( $ids_partidos );
		$equipos = $this->Equipo->find( 'list', array( 'fields' => 'nombre' ) );
		$completo = array();
		foreach( $goleadores as $goleador )
		{
			$listo['nombre'] = $goleador['Goleadores']['nombre'];
			$listo['equipo'] = $equipos[ $goleador['Goleadores']['equipo_id'] ];
			$listo['goles'] = $goleador[0]['goles'];
			$completo[] = $listo;
		}
		unset( $goleadores ); unset( $equipos );
		$this->set( 'datos', $completo );
		return $this->render( 'goleadores' );
	}
}
?>
