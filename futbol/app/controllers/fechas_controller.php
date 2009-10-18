<?php
class FechasController extends AppController {
	var $name = 'Fechas';

	var $uses = array( 'Equipo', 'Fecha', 'Partido' );
	var $helpers = array( 'TabDisplay' );

	function beforeFilter() {
		$this->Auth->allow( 'index', 'proxima_fecha', 'cantfechasaactual', 'tablapuntos', 'fecha_jugada', 'fecha_jugadas', 'proxima_fechas', 'tablafecha' );
		$this->L10n = new L10n();
		$this->L10n->get("spa");
	}

	function fecha_jugadas( $id_torneo = null, $id_zona = null ) {
		if( $id_zona == null ) {
			// Busco la Zonas
			$this->set( 'zonas', $this->Partido->Zona->find( 'all', array( 'conditions' => array( 'Zona.publicado' => 1, 'Zona.torneo_id' => $id_torneo ) ) ) );
			// Busca las ultimas fechas
			if( $this->Partido->Fecha->find( 'list', array( 'conditions' => array( 'Fecha.publicado' => 1, 'Fecha.torneo_id' => $id_torneo ), 'fields' => 'id_fecha' ) ) == 0 )
			{ return $this->render( 'vacio_jugados' ); }
			$fechas = $this->Fecha->find( 'list', array( 'conditions' => array( 'Fecha.publicado' => 1, 'Fecha.torneo_id' => $id_torneo ), 'fields' => 'id_fecha' ) );
			// busco la lista de partidos con resultados
			if( $this->Partido->find( 'count', array( 'conditions' => array( 'NOT' => array( 'Partido.resultado_equipo_1' => null, 'Partido.resultado_equipo_2' => null ),
														'Partido.publicado' => 1,
														'Partido.fecha_id' => $fechas ),
										'fields' => 'DISTINCT Partido.fecha_id',
										'order' => array( 'Partido.fecha_id' => 'desc' ),
										'recursive' => -1 ) ) == 0 )
			{ return $this->render( 'vacio_jugados' ); }
			$ultima_fecha = $this->Partido->find( 'first', array( 'conditions' => array( 'NOT' => array( 'Partido.resultado_equipo_1' => null, 'Partido.resultado_equipo_2' => null ),
														'Partido.publicado' => 1,
														'Partido.fecha_id' => $fechas ),
										'fields' => 'DISTINCT Partido.fecha_id',
										'order' => array( 'Partido.fecha_id' => 'desc' ),
										'recursive' => -1 ) );
			// Ultima fecha jugada
			$this->Partido->Fecha->id = $ultima_fecha['Partido']['fecha_id'];
			$fecha = $this->Partido->Fecha->read();
			$this->set( 'fecha', $fecha );
			$this->set( 'id_torneo', $id_torneo );
			return $this->render();
		}
	}

	function fecha_jugada( $id_torneo = null, $id_zona = null ) {
		// Busca las ultimas fechas
		$fechas = $this->Fecha->find( 'list', array( 'conditions' => array( 'Fecha.publicado' => 1, 'Fecha.torneo_id' => $id_torneo ), 'fields' => 'id_fecha' ) );
		// busco la lista de partidos con resultados
		$ultima_fecha = $this->Partido->find( 'first', array( 'conditions' => array( 'NOT' => array( 'Partido.resultado_equipo_1' => null, 'Partido.resultado_equipo_2' => null ),
														'Partido.publicado' => 1,
														'Partido.fecha_id' => $fechas,
														'Partido.zona_id' => $id_zona ),
										'fields' => 'DISTINCT Partido.fecha_id',
										'order' => array( 'Partido.fecha_id' => 'desc' ),
										'recursive' => -1 ) );
		// Ultima fecha jugada
		$this->Partido->Fecha->id = $ultima_fecha['Partido']['fecha_id'];
		$fecha = $this->Partido->Fecha->read();
		$this->set( 'partidos', $this->Partido->find( 'all', array( 'conditions' => array( 'Partido.publicado' => 1, 'Partido.fecha_id' => $fecha['Fecha']['id_fecha'], 'Partido.zona_id' => $id_zona ),
						  'fields' => array( 'Partido.id_partido','Equipo1.nombre', 'Equipo2.nombre', 'Partido.resultado_equipo_1', 'Partido.resultado_equipo_2' ) ) ) );
		return $this->render();
	}

	function proxima_fechas( $id_torneo = null, $embebe = 0 ) {
		if( $id_torneo == null )
		{ $this->Session->setFlash( 'Error de torneo' ); /*$this->redirect( '/pages/index' ); */}
		$this->Fecha->unbindModel( array( 'hasOne' => array( 'FotoFecha' ) ) );
		if( $this->Fecha->find( 'count',
				array( 'conditions' =>
						array( 'Fecha.publicado' => 1,
							 'Fecha.torneo_id' => $id_torneo,
							 'Fecha.fecha_inicio >=' => date( 'Y-m-d' ) ),
					 'order' => array( 'Fecha.fecha_inicio' => 'desc' ),
					 'recursive' => 1 
					)
				) <= 0 ) { 	if( $embebe == 1 ) { return ""; } else { return $this->render( 'vacio' ); } }
		$this->Fecha->unbindModel( array( 'hasOne' => array( 'FotoFecha' ) ) );
		$fecha = $this->Fecha->find( 'first',
				array( 'conditions' =>
						array( 'Fecha.publicado' => 1,
							 'Fecha.torneo_id' => $id_torneo,
							 'Fecha.fecha_inicio >=' => date( 'Y-m-d' ) ),
					 'order' => array( 'Fecha.fecha_inicio' => 'asc' ),
					 'recursive' => 1 
					)
				);
		$this->set( 'fecha', $fecha );
		$this->set( 'id_torneo', $id_torneo );
		$this->set( 'zonas', $this->Partido->Zona->find( 'all', array( 'conditions' => array( 'Zona.publicado' => 1, 'Zona.torneo_id' => $id_torneo ) ) ) );
		if( $embebe == 1 )
		{ return $this->render(); }
	}

	function proxima_fecha( $id_fecha = null, $id_zona = null ) {
		$this->Fecha->Partido->unbindModel( array( 'hasOne' => array( 'FotoPartido' ) ) );
		$this->set( 'partidos', $this->Fecha->Partido->find( 'all', array( 'conditions' =>
								array( 'Partido.publicado' => 1,
									 'Partido.fecha_id' => $id_fecha,
									 'Partido.zona_id' => $id_zona ),
								'order' => 'Partido.fecha_jugar',
								'recursive' => 1 ) ) );
		return $this->render();
	}

	function admin_index( $id_torneo = null, $id_zona = null ) {
		$this->layout = 'admin';
		// Esta buscando un torneo especifico
		if( isset( $this->data ) ) {
			if( array_key_exists( 'Fecha', $this->data ) )
			{
				if( $this->data['Fecha']['id_torneo'] != null )
				{  $this->Nav->setTorneo( $this->data['Fecha']['id_torneo'] ); }
			}
		}
		if( $this->Nav->idTorneo() == null ) { $this->Nav->setTorneo( $id_torneo ); }
		$this->set( 'id_torneo', $this->Nav->idTorneo() );
		$this->set( 'id_zona', $this->Nav->idZona() );
		$this->set( 'fechas', $this->paginate( 'Fecha', array( 'Fecha.torneo_id' => $this->Nav->idTorneo() ) ) );
		$this->set( 'torneo', $this->Fecha->Torneo->find( 'first', array( 'conditions' => array( 'id_torneo' => $this->Nav->idTorneo() ), 'recursive' => -1  ) ) );
		$lista_torneos = $this->Fecha->Torneo->find( 'list' );
		$this->set( 'lista_torneos', $lista_torneos );
		$this->Nav->setNombreTorneo( $lista_torneos[$this->Nav->idTorneo()] );
	}

	function admin_add() {
		$this->layout = 'admin';
		if( !empty( $this->data ) )
		{
			if( $this->Fecha->save( $this->data ) )
			{ $this->redirect( '/admin/fechas/index/'.$id_torneo ); }
		}
		else
		{
			$this->set( 'id_torneo', $this->Nav->idTorneo() );
			$this->set( 'nombre_torneo', $this->Nav->nombreTorneo() );
		}
	}

	function admin_modificar( $id_fecha = null ) {
		$this->layout = 'admin';
		if( empty( $this->data ) )
		{
			if( $id_fecha == null ) { $this->Session->setFlash( 'Error de identificador de fecha' ); $this->redirect( '/admin/fechas/index' ); }
			$this->Fecha->id = $id_fecha;
			$this->data = $this->Fecha->read();
			$this->set( 'torneos', $this->Fecha->Torneo->find( 'list' ) );
			$this->set( 'id_torneo', $this->Nav->idTorneo() );
		}
		else
		{
			$this->set( 'torneos', $this->Fecha->Torneo->find( 'list' ) );
			if( $this->Fecha->save( $this->data ) )
			{
				$this->flash( 'La Fecha fue actualizada', '/admin/fechas/index/'.$this->data['Fecha']['torneo_id'] );
			}
		}
	}

	function admin_publicar( $publicar, $id_fecha ) {
		$this->Fecha->id = $id_fecha;
		$this->Fecha->saveField( 'publicado', $publicar );
		$this->flash( 'Cambio correcto', '/admin/fechas/index/'.$this->Fecha->field( 'torneo_id' ) );
	}

	function admin_eliminar( $id_fecha ) {
		// Elimina la fecha y todas las cosas relacionadas con ella, recursive = true
		$this->Fecha->del( $id_fecha, true );
		$this->flash( "Eliminacion correcta", '/admin/fechas/index' );
	}

	function tablapuntos( $id_torneo = null, $id_zona = null ) {
		if( $id_torneo == null )
		{ $e = array_shift( $this->requestAction( '/torneos/actuales' ) ); $id_torneo = $e['Torneo']['id_torneo']; unset( $e ); }
		$this->set( 'zonas', $this->Partido->Zona->find( 'all', array( 'conditions' => array( 'Zona.publicado' => 1, 'Zona.torneo_id' => $id_torneo ), 'recursive' => -1  )  ) );
		if( $this->Partido->Fecha->find( 'count', array( 'conditions' => array( 'Fecha.torneo_id' => $id_torneo, 'Fecha.publicado' => 1 ) ) ) == 0 )
		{ return $this->render( 'vacio_resultados' ); }
		$fechas = $this->Partido->Fecha->find( 'list', array( 'conditions' => array( 'Fecha.torneo_id' => $id_torneo, 'Fecha.publicado' => 1 ), 'fields' => 'Fecha.id_fecha' ) );
		// Busco la ultima fecha con partidos jugados
		$ids = $this->Partido->find( 'first', array(
								'conditions' => array(
									'Partido.publicado' => 1,
									'Partido.fecha_id' => $fechas,
									array ( "not" => array (
										"Partido.resultado_equipo_1" => null,
										'Partido.resultado_equipo_2' => null )
									)
								 ),
								'fields' => 'MAX(Partido.fecha_id) as id_fecha',
								'group' => 'Partido.fecha_id',
								'order' => array( 'Partido.fecha_id' => 'desc' ) )
							);
		$id_fecha = $ids[0]['id_fecha'];
		unset( $ids );
		// Genero la tabla
		$this->Fecha->id = $id_fecha;
		$fecha = $this->Fecha->read();
		$this->set( 'fecha', $fecha );
		$this->set( 'id_torneo', $id_torneo );
	}

	function tablafecha( $id_torneo = null, $id_zona = null )
	{
		// Busco las fechas que pertenecen a la zona
		$fechas = $this->Partido->Fecha->find( 'list', array( 'conditions' => array( 'publicado' => 1, 'Fecha.torneo_id' => $id_torneo ), 'recursive' => -1, 'fields' => 'id_fecha' )  );
		if( sizeof( $fechas ) <= 0 )
		{
			echo "No hay Fechas definidas con estos parametros" . $id_zona . ", " . $id_torneo;
		}
		//pr( $fechas );
		// Busco la ultima fecha con partidos jugados
		$ids = $this->Partido->find( 'first', array(
								'conditions' => array(
									'Partido.publicado' => 1,
									'Partido.zona_id' => $id_zona,
									array ( "not" => array (
										"Partido.resultado_equipo_1" => null,
										'Partido.resultado_equipo_2' => null )
									),
									'Partido.fecha_id' => $fechas
								 ),
								'fields' => 'MAX(Partido.fecha_id) as id_fecha',
								'group' => 'Partido.fecha_id',
								'order' => array( 'Partido.fecha_id' => 'desc' ) )
							);
//		$ids = $this->Fecha->find( 'first', array( 'conditions' => array( 'Fecha.publicado' => 1, 'Fecha.torneo_id' => $id_torneo, 'Fecha.fecha_inicio <=' => date('Y-m-d') ), 'fields' => 'id_fecha', 'recursive' => -1, 'order' => array( 'Fecha.fecha_fin' => 'desc' ) ) );
		//pr( $ids );
		$id_fecha = $ids[0]['id_fecha'];
		unset( $ids );
		// Genero la tabla
		$this->Fecha->id = $id_fecha;
		$fecha = $this->Fecha->read();
		$this->set( 'fecha', $fecha );
		// Busco todas las fechas que tiene el campeonato
		$fechas = $this->Fecha->find( 'list', array( 'conditions' => array( 'Fecha.publicado' => 1, 'Fecha.fecha_inicio <=' => date( 'Y-m-d', strtotime($fecha['Fecha']['fecha_fin'] ) ), 'Fecha.torneo_id' => $fecha['Fecha']['torneo_id'] ), 'fields' => 'Fecha.id_fecha', 'recursive' => -1 ) );
		if( sizeof( $fechas ) <= 0 )
		{ return "<div>No hay ninguna fecha definida, imposible calcular tabla de posiciones</div>"; }
		// Busco todos los partidos jugados en este torneo hasta la fecha que me piden
		$partidos = $this->Partido->find( 'all', array(
						'conditions' => array(
							'Partido.publicado' => 1,
							'Partido.fecha_id' => $fechas,
							'Partido.zona_id' => $id_zona,
							array ( "not" => array (
									"Partido.resultado_equipo_1" => null,
									'Partido.resultado_equipo_2' => null )
							)
					) ) );
		if( sizeof( $partidos ) <= 0 )
		{ return "<div>No hay ningun partido jugado, imposible calcular tabla de posiciones</div>"; }
		unset( $fechas );
		// Por cada partido empiezo a calcular los datos
		$tabla = array();
		foreach( $partidos as $partido )
		{
			// veo el resultado del partido
			if( !array_key_exists( $partido['Partido']['id_equipo_1'], $tabla ) )
			{ $tabla[$partido['Partido']['id_equipo_1']] = array( 'partidos_jugados' => 0,
												   'puntos' => 0,
												   'partidos_perdidos' => 0,
												   'partidos_jugados' => 0,
												   'partidos_ganados' => 0,
												   'partidos_empatados' => 0,
												   'goles_favor' => 0,
												   'goles_contra' => 0,
												   'id_equipo' => $partido['Partido']['id_equipo_1'] );
			}
			if( !array_key_exists( $partido['Partido']['id_equipo_2'], $tabla ) )
			{ $tabla[$partido['Partido']['id_equipo_2']] = array( 'partidos_jugados' => 0,
												   'puntos' => 0,
												   'partidos_jugados' => 0,
												   'partidos_perdidos' => 0,
												   'partidos_ganados' => 0,
												   'partidos_empatados' => 0,
												   'goles_favor' => 0,
												   'goles_contra' => 0,
												   'id_equipo' => $partido['Partido']['id_equipo_2'] );
			}
			// Partidos jugados
			$tabla[$partido['Partido']['id_equipo_1']]['partidos_jugados'] += 1;
			$tabla[$partido['Partido']['id_equipo_2']]['partidos_jugados'] += 1;
			// Sumo los puntos
			if( $partido['Partido']['resultado_equipo_1'] > $partido['Partido']['resultado_equipo_2'] )
			{
				// Gano equipo 1 -> suma 3 puntos
				$tabla[$partido['Partido']['id_equipo_1']]['puntos'] += 2;

				$tabla[$partido['Partido']['id_equipo_2']]['partidos_perdidos'] += 1;
				$tabla[$partido['Partido']['id_equipo_1']]['partidos_ganados'] += 1;
			}
			else if( $partido['Partido']['resultado_equipo_2'] > $partido['Partido']['resultado_equipo_1'] )
			{
				// Gano equipo 2 -> suma 3 puntos
				$tabla[$partido['Partido']['id_equipo_2']]['puntos'] += 2;
	
				$tabla[$partido['Partido']['id_equipo_1']]['partidos_perdidos'] += 1;
				$tabla[$partido['Partido']['id_equipo_2']]['partidos_ganados'] += 1;
			}
			else
			{
				// Empataron -> suman 1 cada uno
				$tabla[$partido['Partido']['id_equipo_1']]['puntos'] += 1;
				$tabla[$partido['Partido']['id_equipo_2']]['puntos'] += 1;

				// Aumento los contadores
				$tabla[$partido['Partido']['id_equipo_1']]['partidos_empatados'] += 1;
				$tabla[$partido['Partido']['id_equipo_2']]['partidos_empatados'] += 1;
			}
			/// Sumo los goles
			$tabla[$partido['Partido']['id_equipo_1']]['goles_favor'] += $partido['Partido']['resultado_equipo_1'];
			$tabla[$partido['Partido']['id_equipo_1']]['goles_contra'] += $partido['Partido']['resultado_equipo_2'];

			$tabla[$partido['Partido']['id_equipo_2']]['goles_favor'] += $partido['Partido']['resultado_equipo_2'];
			$tabla[$partido['Partido']['id_equipo_2']]['goles_contra'] += $partido['Partido']['resultado_equipo_1'];
		}
		unset( $partidos );
		// Ordeno los resultados
		foreach( $tabla as $llave => $valor )
		{
			$orden[$llave] = $valor['puntos'];
			$orden2[$llave] = $valor['goles_favor'] - $valor['goles_contra'];
			$orden3[$llave] = $valor['goles_favor'];
		}
		array_multisort( $orden, SORT_NUMERIC, SORT_DESC, $orden2, SORT_NUMERIC, SORT_DESC, $orden3, SORT_NUMERIC, SORT_DESC, $tabla );
		$this->set( 'tabla', $tabla );
		// busco la lista de equipos
		$this->set( 'equipos', $this->Equipo->find( 'list', array( 'conditions' => array( 'Equipo.publicado' => 1 ), 'recursive' => -1, 'fields' => 'Equipo.nombre' ) ) );
		return $this->render();
	}
}
?>
