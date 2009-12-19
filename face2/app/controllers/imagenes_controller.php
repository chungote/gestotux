<?php

class ImagenesController extends AppController {
	var $name = 'Imagenes';

	var $uses = 'Imagenes';
	var $components = array( 'RequestHandler' );

	function ultimas_agregadas() {
		$this->set( 'ultimas', $this->Imagenes->ultimas() );
		$this->render( 'novedades' );
	}

	function galeriaImagenes() {
		// Verifico los parametros para que no mande mugre
		$this->layout = 'ajax';
		//pr( $this->params );
		// Busco que uid de usuario es para mostrar sus imagenes
		/// en cuanto lo tenga implementado
		// Verifico los parametros
		$limite = 9;
		if( isset( $this->params['form']['limite'] ) ) {
			$limite = $this->params['form']['limite'];
		}
		$primero = 0;
		if( isset( $this->params['form']['primero'] ) ) {
			$primero = $this->params['form']['primero'];
		}
		//Busco las imagenes hasta donde me diga la cantidad
		$this->set( 'fotos', $this->Imagenes->find( 'list', array( 'conditions' =>
											array( 'tipo' => 'imagen',
												 'iid > '.$primero ),
						    				'limit' => $limite ) ) );
		$this->render( 'galeria' );
	}

	function galeriaflash( $limite = null, $primero = null) {
		// Verifico los parametros para que no mande mugre
		$this->layout = 'ajax';
		$this->response = 'ajax';
		//pr( $this->params );
		// Busco que uid de usuario es para mostrar sus imagenes
		/// en cuanto lo tenga implementado
		// Verifico los parametros
		$limite = 9;
		if( isset( $this->params['form']['limite'] ) ) {
			$limite = $this->params['form']['limite'];
		}
		$primero = 0;
		if( isset( $this->params['form']['primero'] ) ) {
			$primero = $this->params['form']['primero'];
		}
		//Busco las imagenes hasta donde me diga la cantidad
		$this->set( 'fotos', $this->Imagenes->find( 'list', array( 'conditions' =>
											array( 'tipo' => 'flash',
												 'iid > '.$primero ),
						    				'limit' => $limite ) ) );
		$this->render( 'galeria' );
	}

	function miniatura( $id_imagen = null ) {
		// Devuelve la miniatura de la imagen
		$this->layout = 'ajax';
		$this->response = 'ajax';
		if( $id_imagen == 0 || $id_imagen == null ) { exit; }
		$this->set( 'miniatura', $this->Imagenes->miniatura( $id_imagen ) );
		return $this->render( 'miniatura' );
	}

	function galeriapaginacion() {
		$this->layout = 'ajax';
		$this->response = 'ajax';
		$limite = 9;
		if( isset( $this->params['form']['limite'] ) ) {
			$limite = $this->params['form']['limite'];
		}
		$primero = 0;
		if( isset( $this->params['form']['primero'] ) ) {
			$primero = $this->params['form']['primero'];
		}
		$tipo = "imagen";
		if( isset( $this->params['form']['tipo'] ) ) {
			$tipo = $this->params['form']['tipo'];
		}
		if( $this->params['form']['avance'] == 's' ) {
			$siguiente = $this->Imagenes->find( 'count', array( 'conditions' =>
												array( 'tipo' => $tipo,
													 'iid > '.$primero ),
							    				'limit' => $limite ) );
			if( $siguiente - $limite > 0 ) {
				// hay siguientes
				$this->set( 'valor', "1|1" );
			} else { $this->set( 'valor', "0" ); }
		} else if( $this->params['form']['avance'] == 'a'  ) {
			$anterior = $this->Imagenes->find( 'count', array( 'conditions' =>
											array( 'tipo' => $tipo,
												 'iid < '.$primero ),
						    				'limit' => $limite ) );
			if( $anterior - $limite > 0 ) {
				// hay antes
				$this->set( 'valor', "1|1" );
			} else { $this->set( 'valor', "0" ); }
		} else {
			return $this->set( 'valor', "Error" );
		}
	}
}
?>