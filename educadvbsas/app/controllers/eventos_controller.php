<?php
class EventosController extends AppController {
 	var $name = 'Eventos';
	var $uses = 'Eventos';
	//var $scaffold;

	function portada() {
		if( $this->params['named']['id_mes'] == null ) { $id_mes = date( "n" ); } else { $id_mes = $this->params['named']['id_mes']; }
		if( $this->params['named']['id_ano'] == null ) { $id_ano = date( "Y" ); } else { $id_ano = $this->params['named']['id_ano']; }
		return $this->Eventos->buscarEventosPortada( $id_mes, $id_ano );
	}

	function mostrarEventos() {
		if( $this->params['named']['dia'] == null ) { $dia = date( "j" ); } else { $dia = $this->params['named']['dia']; }
		if( $this->params['named']['mes'] == null ) { $mes = date( "n" ); } else { $mes = $this->params['named']['mes']; }
		if( $this->params['named']['ano'] == null ) { $ano = date( "Y" ); } else { $ano = $this->params['named']['ano']; }
		$this->columnas( true, false );
		$dato = $this->Eventos->buscarEventos( $dia, $mes, $ano );
		//pr( $dato );
	}

}
?>