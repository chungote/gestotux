<?php
class GoleadoresController extends AppController {

	var $name = 'Goleadores';
	var $uses = 'Goleador';

	function admin_index( $id_partido = null ) {
		$this->layout = 'admin';
		if( $id_partido == null ) {
			$this->Session->setFlash( 'El partido no existe!' );
			$this->redirect( '/admin/partidos' );
		}
		$this->Goleador->Partido->id = $id_partido;
		$partido = $this->Goleador->Partido->read();
		$this->set( 'partido', $this->Goleador->Partido->read() );
		$this->set( 'goleadores', $this->paginate( 'Goleador', array( 'partido_id' => $id_partido ) ) );
		$this->set( 'id_partido', $id_partido );
		// Busco los goleadores para cada equipo
		$cant_equipo_1 = $this->Goleador->find( 'count', array( 'conditions' => array( 'partido_id' => $id_partido, 'equipo_id' => $partido['Partido']['id_equipo_1'] ) ) );
		$hacer_equipo_1 = $partido['Partido']['resultado_equipo_1'] - $cant_equipo_1;
		$cant_equipo_2 = $this->Goleador->find( 'count', array( 'conditions' => array( 'partido_id' => $id_partido, 'equipo_id' => $partido['Partido']['id_equipo_2'] ) ) );
		$hacer_equipo_2 = $partido['Partido']['resultado_equipo_2'] - $cant_equipo_2;
		$this->set( 'hacer_equipo_1', $hacer_equipo_1 );
		$this->set( 'hacer_equipo_2', $hacer_equipo_2 );
	}

	function admin_agregar( $id_partido = null ) {
		$this->layout = 'admin';
		if( !empty( $this->data ) ) {
			//pr( $this->data );
			$this->Goleador->Partido->id = $this->data['Goleadores']['id_partido'];
			$partido = $this->Goleador->Partido->read();
			unset( $partido['Fecha'] ); unset( $partido['Sancionado'] );
			unset( $partido['Equipo1']['created'] );
			unset( $partido['Equipo1']['modified'] );
			unset( $partido['Equipo2']['created'] );
			unset( $partido['Equipo2']['modified'] );
			//pr( $partido );
			// guardo los goleadores de cada equipo
			for( $i = 1; $i <= $this->data['Goleadores']['hacer_equipo_1']; $i++ ) {
				$this->Goleador->create();
				$goleador['Goleador']['nombre'] = $this->data['Goleadores']['nombre_1_'.$i];
				$goleador['Goleador']['minuto'] = $this->data['Goleadores']['minuto_1_'.$i];
				$goleador['Goleador']['equipo_id'] = $partido['Equipo1']['id_equipo'];
				$goleador['Goleador']['publicado'] = true;
				$goleador['Goleador']['partido_id'] = $partido['Partido']['id_partido'];
				$this->Goleador->save( $goleador );
			}
			for( $i = 1; $i <= $this->data['Goleadores']['hacer_equipo_2']; $i++ ) {
				$this->Goleador->create();
				$goleador['Goleador']['nombre'] = $this->data['Goleadores']['nombre_2_'.$i];
				$goleador['Goleador']['minuto'] = $this->data['Goleadores']['minuto_2_'.$i];
				$goleador['Goleador']['equipo_id'] = $partido['Equipo2']['id_equipo'];
				$goleador['Goleador']['publicado'] = true;
				$goleador['Goleador']['partido_id'] = $partido['Partido']['id_partido'];
				$this->Goleador->save( $goleador );
			}
			$this->Session->setFlash( 'Goleadores guardados correctamente' );
			$this->redirect( '/admin/partidos/index/'.$partido['Partido']['fecha_id'] );
		} else {
			if( $id_partido == null ) {
			 	$this->Session->setFlash( 'El partido es invalido!' );
				$this->redirect( '/admin/goleadores/index/'.$id_partido );
			}
			// Leo los datos del partido
			$this->Goleador->Partido->id = $id_partido;
			$partido = $this->Goleador->Partido->read();
			$this->set( 'partido', $this->Goleador->Partido->read() );
			//Verificar cuantos goleadores ya existen en ese partido en cada equipo
			// Busco los goleadores para cada equipo
			$cant_equipo_1 = $this->Goleador->find( 'count', array( 'conditions' => array( 'partido_id' => $id_partido, 'equipo_id' => $partido['Partido']['id_equipo_1'] ) ) );
			$hacer_equipo_1 = $partido['Partido']['resultado_equipo_1'] - $cant_equipo_1;
			$cant_equipo_2 = $this->Goleador->find( 'count', array( 'conditions' => array( 'partido_id' => $id_partido, 'equipo_id' => $partido['Partido']['id_equipo_2'] ) ) );
			$hacer_equipo_2 = $partido['Partido']['resultado_equipo_2'] - $cant_equipo_2;
			if( $hacer_equipo_1 <= 0 && $hacer_equipo_2 <= 0 ) {
				$this->Session->setFlash( 'Ya existen los goleadores para este partido' );
				$this->redirect( '/admin/goleadores/index/'.$id_partido );
			}
			$this->set( 'hacer_equipo_1', $hacer_equipo_1 );
			$this->set( 'hacer_equipo_2', $hacer_equipo_2 );
			
		}
	}

	function admin_eliminar( $id_goleador = null, $id_partido = null ) {
	if( $id_goleador == null ) {
		$this->Session->setFlash( "El identificador de goleador es incorrecto" );
		$this->redirect( array( 'action' => 'admin_index' ) );
	}

	$this->Goleador->del( $id_goleador );
	$this->Session->setFlash( 'goleador eliminado correctamente' );
	$this->redirect( '/admin/goleadores/index/'.$id_partido );
	}
}
?>
