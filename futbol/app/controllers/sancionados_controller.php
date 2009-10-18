<?php
class SancionadosController extends AppController {

	var $name = 'Sancionados';
	var $modelName = 'Sancionado';

	var $helpers = array( 'TabDisplay' );

	function beforeFilter() {
		$this->Auth->allow( 'ver', 'tabla', 'tablazona' );
		$this->L10n = new L10n();
		$this->L10n->get("spa");
	}

	function admin_index( $id_partido = null ) {
		$this->layout = 'admin';
		if( $id_partido == null ) {
			// Muestro todos los sancionados
			$this->set( 'datos', $this->paginate() );
		} else {
			$this->set( 'datos', $this->paginate( array( 'partido_id' => $id_partido ) ) );
			$this->Sancionado->Partido->id = $id_partido;
			$this->set( 'partido', $this->Sancionado->Partido->read() );
		}
	}

	function admin_agregar( $id_partido = null ) {
		$this->layout = 'admin';
		if( !empty( $this->data ) )
		{
			if( $this->Sancionado->save( $this->data ) )
			{
				$this->Session->setFlash( 'Sancionado guardado correctamente' );
				$this->redirect( '/admin/sancionados/index/'.$this->data['Sancionado']['partido_id'] );
			}
		}
		if( $id_partido == null ) {
			$this->Session->setFlash( 'El partido es invalido' );
			$this->redirect( array( 'action' => 'admin_index' ) );
		}
		$this->Sancionado->Partido->id = $id_partido;
		$this->set( 'partido', $this->Sancionado->Partido->read() );
		$this->set( 'tipos_sancion', $this->Sancionado->TipoSancion->find( 'list', array( 'conditions' => array( 'publicado' => 1 ) ) ) );
	}

	function admin_publicar( $publicar, $id_sancionado ) {
		$this->Sancionado->id = $id_sancionado;
		$this->Sancionado->saveField( 'publicado', $publicar );
		$this->redirect( '/admin/sancionados' );
	}

	function tabla( $id_torneo = null ) {
		// Obtengo los datos del torneo
		if( $id_torneo == null ) { $this->redirect( '/pages/index' ); }
		$this->Sancionado->Partido->Fecha->Torneo->id = $id_torneo;
		$this->set( 'nombre_torneo', $this->Sancionado->Partido->Fecha->Torneo->field( 'name' ) );
		$this->set( 'id_torneo', $id_torneo );

		// Busca las ultimas fechas
		if( $this->Sancionado->Partido->Fecha->find( 'count', array( 'conditions' => array( 'Fecha.publicado' => 1, 'Fecha.torneo_id' => $id_torneo ), 'fields' => 'id_fecha' ) ) == 0 )
		{ return $this->render( 'vacio_sancionados' ); }
		$fechas = $this->Sancionado->Partido->Fecha->find( 'list', array( 'conditions' => array( 'Fecha.publicado' => 1, 'Fecha.torneo_id' => $id_torneo ), 'fields' => 'id_fecha' ) );
		// busco la lista de partidos con resultados
		$ultima_fecha = $this->Sancionado->Partido->find( 'first', array( 'conditions' => array( 'NOT' => array( 'Partido.resultado_equipo_1' => null, 'Partido.resultado_equipo_2' => null ),
														'Partido.publicado' => 1,
														'Partido.fecha_id' => $fechas ),
										'fields' => 'DISTINCT Partido.fecha_id',
										'order' => array( 'Partido.fecha_id' => 'desc' ),
										'recursive' => -1 ) );
		//pr( $ultima_fecha );
		// Ultima fecha jugada
		$this->Sancionado->Partido->Fecha->id = $ultima_fecha['Partido']['fecha_id'];
		$fecha = $this->Sancionado->Partido->Fecha->read();
		$this->set( 'fecha', $fecha );

		$this->set( 'zonas', $this->Sancionado->Partido->Zona->find( 'all', array( 'conditions' => array( 'Zona.publicado' => 1, 'Zona.torneo_id' => $id_torneo ) ) ) );
		$this->render( 'tabla_general' );
	}

	function tablaZona( $id_torneo = null, $id_zona = null, $id_fecha = null ) {
		$this->cacheQuery = true;
		// Veo que fechas existen y calculo cuales partidos estan actualmente en esas fechas
		$fechas = $this->Sancionado->Partido->Fecha->find( 'list', array( 'conditions' => array( 'Fecha.publicado' => 1, 'Fecha.torneo_id' => $id_torneo ), 'fields' => 'id_fecha' ) );
		$partidos = $this->Sancionado->Partido->find( 'list', array( 'conditions' => array( 'Partido.publicado' => 1, 'Partido.fecha_id' => $fechas, 'Partido.zona_id' => $id_zona ), 'fields' => 'id_partido' ) );
		// Selecciono la lista de sancionados que estan actualmente sancionados
		$sancionados = $this->Sancionado->find( 'all', array( 'conditions' => array( 'Sancionado.publicado' => 1, 'Sancionado.partido_id' => $partidos ), 'recursive' => 1 ) );

		$lista = array();
		foreach( $sancionados as $s )
		{
			$this->Sancionado->Partido->Fecha->unbindModel( array( 'hasOne' => array( 'FotoFecha' ) ) );
			$cantidad = $this->Sancionado->Partido->Fecha->find( 'count', array(
							 'conditions' => array(
								'Fecha.publicado' => 1,
								'Fecha.torneo_id' => $id_torneo,
								'Fecha.id_fecha BETWEEN ? AND ?' => array( $s['Partido']['fecha_id'] , $id_fecha ) ) ) );
			if( $cantidad > 0 )
			{
				$faltan = ( $s['Sancionado']['cant_fechas'] + 1 ) - $cantidad;
				if( $faltan > 0 )
				{
					$s['Sancionado']['quedan_fechas'] = $faltan;
					$lista[] = $s;
				}
			}
		}
		$this->set( 'sancionados', $lista );
		return $this->render( 'tabla_zona' );
	}

	function admin_modificar( $id_sancionado = null, $id_partido = null ) {
		$this->layout = 'admin';
		if( !empty( $this->data ) )
		{
			if( $this->Sancionado->save( $this->data ) )
			{
				$this->Session->setFlash( 'Sancionado guardado correctamente' );
				$this->redirect( '/admin/sancionados/index/'.$this->data['Sancionado']['partido_id'] );
			}
		}
		if( $id_partido == null ) {
			$this->Session->setFlash( 'El partido es invalido' );
			$this->redirect( array( 'action' => 'admin_index' ) );
		}
		if( $id_sancionado == null ) {
			$this->Session->setFlash( 'El sancionado es invalido' );
			$this->redirect( array( 'action' => 'admin_index' ) );
		}
		$this->Sancionado->id = $id_sancionado;
		$this->set( 'sancionado', $this->Sancionado->read() );
		$this->Sancionado->Partido->id = $id_partido;
		$this->set( 'partido', $this->Sancionado->Partido->read() );
		$this->set( 'tipos_sancion', $this->Sancionado->TipoSancion->find( 'list', array( 'conditions' => array( 'publicado' => 1 ) ) ) );
	}

	function admin_eliminar( $id_sancionado = null, $id_partido = null ) {
		if( $id_sancionado == null || $id_partido == null ) {
			$this->Session->setFlash( 'Identificadores invalidos' );
			$this->redirect( '/admin/sancionados/index' );
		}

		if( $this->Sancionado->del( $id_sancionado ) )
		{
			$this->Session->setFlash( 'Sancionado eliminado correctamente' );
		} else {
			$this->Session->setFlash( 'Error al eliminar el sancionado' );
		}
		$this->redirect( '/admin/sancionados/index/'.$id_partido );
	}
}
?>
