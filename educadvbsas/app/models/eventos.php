<?php
class Eventos extends AppModel {
	var $name = "Eventos";
	var $useTable = "eventos";
	var $primaryKey = "id_evento";

	/*var $validate = array( 
	);*/

	function buscarEventosPortada( $id_mes = null, $id_ano = null  ) {
		$datos = $this->find( 'all', array(
				'conditions' => array(
					'mes' => $id_mes,
					'ano' => $id_ano,
					'publicado' => true ),
				'order' => array( 'dia', 'hora' ),
				'fields' => array( 'dia', 'titulo' ) ) );
		$a = array();
		foreach( $datos as $d ) {
			$a[$d['Eventos']['dia']][] = $d['Eventos'];
		}
		return $a;
	}

	function buscarEventos( $dia = null, $mes = null, $ano = null ) {
		return $this->find( 'all', array(
				'conditions' => array(
					'dia' => $dia,
					'mes' => $mes,
					'ano' => $ano,
					'publicado' => true )
				)
			);
	}
}
?>