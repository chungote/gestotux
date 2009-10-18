<?php

class AmonestadosController extends AppController {

 var $name = 'Amonestados';
 var $uses = array( 'Amonestado', 'Partido' );
 var $helpers = array( 'TabDisplay' );

 function beforeFilter() {
   $this->Auth->allow( 'torneo', 'zona' );
 }

 function torneo( $id_torneo = null ) {
   // Muestra todos los amonestados de los torneos
   if( $id_torneo == null )
   { $e = array_shift( $this->requestAction( '/torneos/actuales' ) ); $id_torneo = $e['Torneo']['id_torneo']; $this->set( 'nombre_torneo', $e['Torneo']['name'] ); unset( $e ); }
   else
   { $this->Amonestado->Partido->Fecha->Torneo->id = $id_torneo; $this->set( 'nombre_torneo', $this->Amonestado->Partido->Fecha->Torneo->field( 'name' ) ); }
   $fechas = $this->Amonestado->Partido->Fecha->find( 'list', array( 'conditions' => array( 'Fecha.publicado' => 1, 'Fecha.torneo_id' => $id_torneo ), 'fields' => 'id_fecha' ) );
   // Busco la ultima fecha con partidos jugados
   $ids = $this->Amonestado->Partido->find( 'first', array(
						'conditions' => array(
							'Partido.publicado' => 1,
							'Partido.fecha_id' => $fechas,
							array ( "not" => array (
								"Partido.resultado_equipo_1" => null,
								'Partido.resultado_equipo_2' => null )
							) ),
						'fields' => 'MAX(Partido.fecha_id) as id_fecha',
						'group' => 'Partido.fecha_id',
						'order' => array( 'Partido.fecha_id' => 'desc' ) )
					);
	$id_fecha = $ids[0]['id_fecha'];
	unset( $ids ); unset( $fechas );
	// Genero la tabla
	$this->Amonestado->Partido->Fecha->id = $id_fecha;
	$fecha = $this->Amonestado->Partido->Fecha->read();
	$this->set( 'fecha', $fecha );
	$this->set( 'id_torneo', $id_torneo );
	$this->set( 'zonas', $this->Amonestado->Partido->Zona->find( 'all', array( 'conditions' => array( 'Zona.publicado' => 1, 'Zona.torneo_id' => $id_torneo ) ) ) );
   }



	function zona( $id_torneo = null, $id_zona = null, $fecha_fin = null ) {
	// Busco todas las fechas que tiene el campeonato
	$fechas = $this->Amonestado->Partido->Fecha->find( 'list', array( 'conditions' => array( 'Fecha.publicado' => 1, 'Fecha.fecha_inicio <=' => date( 'Y-m-d', strtotime( $fecha_fin ) ), 'Fecha.torneo_id' => $id_torneo ), 'fields' => 'Fecha.id_fecha', 'recursive' => -1 ) );
	if( sizeof( $fechas ) <= 0 )
	{ return "<div>No hay ninguna fecha definida, imposible calcular los amonestados</div>"; }
	// Busco todos los partidos jugados en este torneo hasta la fecha que me piden
	$partidos = $this->Amonestado->Partido->find( 'list', array(
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
	{ return "<div>No hay ningun partido jugado, imposible calcular los amonestados</div>"; }
	unset( $fechas );
	// Busco todos los sancionados de los partidos
	$amonestados = $this->Amonestado->find( 'all', array(
						'conditions' => array( 'partido_id' => $partidos, 'Amonestado.publicado' => 1 ),
						'group' => 'nombre_jugador',
						'fields' => array( 'Amonestado.nombre_jugador', 'SUM(Amonestado.cantidad) as suma', 'Equipo.nombre' ),
						'order' => array( 'suma' => 'desc', 'equipo_id' => 'asc', 'nombre_jugador' => 'asc' ) ) );
	$this->set( 'amonestados', $amonestados );
	return $this->render();
 }

 function admin_index( $id_partido = null ) {
  if( $id_partido == null )
  { $this->Session->setFlash( 'dato incorrecto' ); $this->redirect( '/admin' ); }
  $this->Amonestado->Partido->id = $id_partido;
  $this->set( 'partido', $this->Amonestado->Partido->read() );
  $this->set( 'datos', $this->paginate( 'Amonestado', array( 'partido_id' => $id_partido ) ) );
  $this->layout = 'admin';
 }

 function admin_eliminar( $id_amonestado = null, $id_partido = null ) {
  if( $id_amonestado == null ) {
   $this->Session->setFlash( "El identificador de amonestado es incorrecto" );
   $this->redirect( array( 'action' => 'admin_index' ) );
  }

  $this->Amonestado->del( $id_amonestado );
  $this->Session->setFlash( 'Amonestado eliminado correctamente' );
  $this->redirect( '/admin/amonestados/index/'.$id_partido );
 }

 function admin_publicar( $publicar, $id_amonestado = null ) {
  	$this->Amonestado->id = $id_amonestado;
	$this->Amonestado->saveField( 'publicado', $publicar );
	$this->Session->setFlash( 'Amonestado modificada correctamente' );
	$this->redirect( '/admin/amonestados/index/'. $this->Amonestado->field( 'partido_id' ) );
 }

 function admin_agregar( $id_partido = null ) {
	$this->layout = 'admin';
	if( empty( $this->data ) )
	{
		$this->Partido->id = $id_partido;
		$partido = $this->Partido->read();
		$this->set( 'partido', $id_partido );
		$equipos = $this->Partido->Equipo1->find( 'list', array( 'conditions' => array(
				'id_equipo' => array( $partido['Partido']['id_equipo_1'],
							    $partido['Partido']['id_equipo_2'] )
						) ) );
		$this->set( 'equipos', $equipos );
	}
	else
	{
		//pr( $this->data );
		if( $this->Amonestado->save( $this->data ) ) {
			$this->Session->setFlash( 'Amonestado agregado correctamente' );
			$this->redirect( '/admin/amonestados/index/'.$this->data['Amonestado']['partido_id'] );
		}
	}
 }
}
?>