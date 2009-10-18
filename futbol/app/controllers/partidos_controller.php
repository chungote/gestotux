<?php

class PartidosController extends AppController {

	var $name = 'Partidos';

	var $helpers = array( 'Javascript', 'Thumbnail', 'Lightbox', 'TabDisplay' );

	function beforeFilter() {
		$this->Auth->allow( 'ver', 'resultados', 'resultadosFecha' );
		$this->L10n = new L10n();
		$this->L10n->get("spa");
	}

	function ver( $id_partido = null ) {
		if( $id_partido == null ) { $this->redirect( '/pages/index' ); }
		$this->Partido->id = $id_partido;
		$id_fecha = $this->Partido->field( 'fecha_id' );
		$this->set( 'partido', $this->Partido->read() );
	}

	function resultados($que = null, $id ) {
		$zonas = array(); 
		if( $que == "torneo" ) {
			// Muestra los resultados de la ultima fecha jugada
			$zonas = $this->Partido->Zona->find( 'all', array( 'conditions' => array( 'Zona.publicado' => 1, 'Zona.torneo_id' => $id ) ) );
			// Busca las ultimas fechas
			if( $this->Partido->Fecha->find( 'list', array( 'conditions' => array( 'Fecha.publicado' => 1, 'Fecha.torneo_id' => $id ), 'fields' => 'id_fecha' ) ) == 0 )
			{ return $this->render( 'vacio_resultados' ); }
			$fechas = $this->Partido->Fecha->find( 'list', array( 'conditions' => array( 'Fecha.publicado' => 1, 'Fecha.torneo_id' => $id ), 'fields' => 'id_fecha' ) );
			// busco la lista de partidos con resultados
			if( $this->Partido->find( 'count', array( 'conditions' => array( 'NOT' => array( 'Partido.resultado_equipo_1' => null, 'Partido.resultado_equipo_2' => null ),
														'Partido.publicado' => 1,
														'Partido.fecha_id' => $fechas ),
										'fields' => 'DISTINCT Partido.fecha_id',
										'order' => array( 'Partido.fecha_id' => 'desc' ),
										'recursive' => -1 ) ) == 0 )
			{ return $this->render( 'vacio_resultados' ); }
			$ultima_fecha = $this->Partido->find( 'first', array( 'conditions' => array( 'NOT' => array( 'Partido.resultado_equipo_1' => null, 'Partido.resultado_equipo_2' => null ),
														'Partido.publicado' => 1,
														'Partido.fecha_id' => $fechas ),
										'fields' => 'DISTINCT Partido.fecha_id',
										'order' => array( 'Partido.fecha_id' => 'desc' ),
										'recursive' => -1 ) );
			// Ultima fecha jugada de la zona
			$this->Partido->Fecha->id = $ultima_fecha['Partido']['fecha_id'];
			$fecha = $this->Partido->Fecha->read();
			$this->set( 'fecha', $fecha );
			$this->set( 'navegacion',  $this->Partido->Fecha->find( 'neighbors', array( 'field' => 'id_fecha', 'value' => $ultima_fecha['Partido']['fecha_id'], 'fields' => array( 'id_fecha', 'name' ), 'conditions' => array( 'Fecha.torneo_id' => $fecha['Fecha']['torneo_id'] ) ) ) );
			$this->set( 'zonas', $zonas );
			return $this->render( 'resultados_torneo' );
		} else {
 			// muestra los resultados de una fecha especifica
			$this->Partido->Fecha->id = $id;
			$fecha = $this->Partido->Fecha->read();
			$this->set( 'navegacion', $this->Partido->Fecha->find( 'neighbors', array( 'field' => 'id_fecha', 'value' => $id, 'fields' => array( 'id_fecha', 'name' ), 'conditions' => array( 'Fecha.torneo_id' => $fecha['Fecha']['torneo_id'] ) ) ) );
			$this->set( 'fecha', $fecha );
			$zonas = $this->Partido->Zona->find( 'all', array( 'conditions' => array( 'Zona.publicado' => 1, 'Zona.torneo_id' => $fecha['Fecha']['torneo_id'] ) ) );
		}
		$this->set( 'que', $que ); $this->set( 'id', $id );
		$this->set( 'zonas', $zonas );
	}

	function resultadosFecha( $id_fecha = null, $id_zona = null ) {
		// Busco los partidos para esta fecha
		$this->Partido->unbindModel(  array( 'hasMany' => array( 'Sancionado' ) ) );
		$this->set( 'partidos', $this->Partido->find( 'all',
					 array( 'conditions' => array( 'Partido.publicado' => 1, 'Partido.fecha_id' => $id_fecha, 'Partido.zona_id' => $id_zona ),
						  'fields' => array( 'Partido.id_partido','Equipo1.nombre', 'Equipo2.nombre', 'Partido.resultado_equipo_1', 'Partido.resultado_equipo_2' ) ) ) );
		return $this->render();
      }

	function admin_index( $id_fecha = null, $id_fecha = null, $id_zona = null ) {
		$this->layout = 'admin';
		// Verifico que no pase parametros de busqueda
		if( isset( $this->data['partidos']['id_fecha'] ) ) { $this->Nav->setFecha( $this->data['partidos']['id_fecha'] ); }
		if( isset( $this->data['partidos']['id_zona'] ) ) { $this->Nav->setZona( $this->data['partidos']['id_zona'] ); }

		// Verifico el parametro '-'
		if( $id_fecha == '-' ) { $id_fecha = null; }

		// Verifico si no pasaron los parametros desde otra pantalla
		if( $this->Nav->idFecha() == null && $id_fecha != null ) { $this->Nav->setFecha( $id_fecha ); }
		if( $this->Nav->idZona() == null && $id_zona != null ) { $this->Nav->setZona( $id_zona ); }

		// Listados para el filtrado
		$this->set( 'lista_fechas', $this->Partido->Fecha->find( 'list', array( 'conditions' => array( 'Fecha.torneo_id' => $this->Nav->idTorneo() ) ) ) );
		$this->set( 'lista_zonas', $this->Partido->Zona->find( 'list', array( 'conditions' => array( 'Zona.torneo_id' => $this->Nav->idTorneo() ) ) ) );

		// Todos los partidos
		if( $this->Nav->idFecha() == null && $this->Nav->idZona() == null)
		{
			// Muestra todos los partidos de todas las fechas y todas las zonas
			$this->set( 'nombre_fecha', 'todas las fechas - todos las zonas' );
			$this->set( 'partidos', $this->paginate( 'Partido' ) );

		} else if( $this->Nav->idZona() == null && $this->Nav->idFecha() != null ) {
			$this->Partido->Fecha->id = $this->Nav->idFecha();
			$this->set( 'nombre_fecha', $this->Partido->Fecha->field( 'name' ) . ' - Todas las zonas ' );
			$this->Nav->setNombreFecha( $this->Partido->Fecha->field( 'name' ) );
			$this->set( 'partidos', $this->paginate( 'Partido', array( 'Partido.fecha_id' => $this->Nav->idFecha() ) ) );
			$this->set( 'id_fecha', $this->Nav->idFecha() );

		} else if( $this->Nav->idZona() != null && $this->Nav->idFecha() == null ) {
			$this->Partido->Zona->id = $this->Nav->idZona();
			$this->set( 'nombre_fecha', $this->Partido->Zona->field( 'nombre_zona' ) . ' - Todas las fechas ' );
			$this->Nav->setNombreZona( $this->Partido->Zona->field( 'nombre_zona' ) );
			$this->set( 'partidos', $this->paginate( 'Partido', array( 'Partido.zona_id' => $this->Nav->idZona() ) ) );
			$this->set( 'id_zona', $this->Nav->idZona() );

		} else if( $this->Nav->idZona() != null && $this->Nav->idFecha() != null ) {
			$this->Partido->Zona->id = $this->Nav->idZona();
			$this->Nav->setNombreZona( $this->Partido->Zona->field( 'nombre_zona' ) );
			$this->Partido->Fecha->id = $this->Nav->idFecha();
			$this->Nav->setNombreFecha( $this->Partido->Fecha->field( 'name' ) );
			$this->set( 'nombre_fecha', $this->Partido->Fecha->field( 'name' ) . ' - ' .$this->Partido->Zona->field( 'nombre_zona' ) );
			$this->set( 'partidos', $this->paginate( 'Partido', array( 'Partido.zona_id' => $this->Nav->idZona(), 'Partido.fecha_id' => $this->Nav->idFecha() ) ) );
			$this->set( 'id_zona', $this->Nav->idZona() );
			$this->set( 'id_fecha', $this->Nav->idFecha() );	
		}
		else
		{
			echo "Error!"; exit();
		}
	}

	function admin_agregar() {
		$this->layout = 'admin';
		if( !empty( $this->data ) ) {
			if ( $this->Partido->save( $this->data ) ) {
				$this->Session->setFlash( "El Partido ha sido guardado" );
				$this->redirect( array( 'action' => 'admin_index', $this->data['Partido']['fecha_id'] ) );
			} else {
				$this->Session->setFlash( "Error al intentar guardar el Partido" );
			}
		} else {
			// Busco los equipos que estan en la zona del torneo
			$equipos_zona = $this->Partido->Equipo1->TorneoZonaEquipo->find( 'list', array( 'conditions' => array( 'TorneoZonaEquipo.zona_id' => $this->Nav->idZona(), 'TorneoZonaEquipo.torneo_id' => $this->Nav->idTorneo() ) ) );
			$this->set( 'equipos',  $this->Partido->Equipo1->find( 'list',
							 array( 'conditions' =>
									array( 'publicado' => 1,
										 'admitido' => 1,
										 'id_equipo' => $equipos_zona )
								)
							) );
			$this->set( 'id_fecha', $this->Nav->idFecha() );
			$this->set( 'nombre_fecha', $this->Nav->nombreFecha() );
			$this->set( 'id_zona', $this->Nav->idZona() );
			$this->set( 'nombre_zona', $this->Nav->nombreZona() );
		}
	}

	function admin_eliminar( $id_partido = null ) {
		if( $id_partido == null ) {
			$this->Session->setFlash( "El identificador de partido es incorrecto" );
			$this->redirect( array( 'action' => 'admin_index' ) );
		}

		$this->Partido->del( $id_partido );
		$this->Session->setFlash( 'Partido eliminado correctamente' );
		$this->redirect( array( 'action' => 'admin_index' ) );
	}


	function admin_modificar( $id_partido = null ) {
		$this->layout = 'admin';
		if( !empty( $this->data ) ) {
			if( $this->Partido->save( $this->data ) ) {
				$this->Session->setFlash( 'Partido guardado correctamente' );
				$this->redirect( '/admin/partidos/index' );
			} else {
				$this->Session->setFlash( 'Error al guardar el partido' );
				$this->redirect( '/admin/partidos/index' );
			}
		} else {
			if( $id_partido == null ) {
				$this->Session->setFlash( 'Identificador de partido invalido' );
				$this->redirect( '/admin/partidos/index' );
			}
			$this->Partido->id = $id_partido;
			$fecha = $this->Partido->field( 'fecha_id' );
			$zona = $this->Partido->field( 'zona_id' );
			$this->Partido->Fecha->id = $fecha;
			$torneo = $this->Partido->Fecha->field( 'torneo_id' );
			$this->set( 'partido', $this->Partido->read() );
			$this->set( 'equipos', $this->Partido->Equipo1->TorneoZonaEquipo->find( 'list', array( 'conditions' => array( 'TorneoZonaEquipo.zona_id' => $this->Nav->idZona(), 'TorneoZonaEquipo.torneo_id' => $this->Nav->idTorneo() ) ) ) );
			$this->set( 'fechas', $this->Partido->Fecha->find( 'list', array( 'conditions' => array( 'torneo_id' => $torneo ) ) ) );
			$this->set( 'fecha', $fecha );
		}
	}

	function admin_resultados( $id_partido = null, $id_fecha = null ) {
		$this->layout = 'admin';
		if( !empty( $this->data ) )
		{
			if( isset( $this->data['Resultados']['id_partido'] ) )
			{
				$this->Partido->id = $this->data['Resultados']['id_partido'];
				$this->Partido->saveField( 'resultado_equipo_1', $this->data['Resultados']['resultado_equipo_1'] );
				$this->Partido->saveField( 'resultado_equipo_2', $this->data['Resultados']['resultado_equipo_2'] );
				$this->Session->setFlash( 'Resultado Guardado correctamente' );
				$this->redirect( '/admin/partidos/index/'.$this->data['Resultados']['fecha_id'] );
			} else {
				$this->Session->setFlash( 'Error al obtener datos' );
			}
		}
		else
		{
			if( $id_partido == null ) {
				$this->Session->setFlash( "El identificador de partido es incorrecto" );
				$this->redirect( '/admin/partidos/index/'.$id_fecha );
			}
			$this->Partido->id = $id_partido;
			$this->set( 'partido', $this->Partido->read() );
		}
	}

	function admin_publicar( $publicar = 0, $id_partido = null, $id_fecha = null ) {
		$this->Partido->id = $id_partido;
		$this->Partido->saveField( 'publicado', $publicar );
		$this->redirect( '/admin/partidos/index/'.$id_fecha );
	}
}
?>