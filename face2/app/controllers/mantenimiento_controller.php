<?php

class MantenimientoController extends AppController {
	var $name="Mantenimiento";
	var $uses = array( 'Usuario', 'Saludos', 'Imagenes' );
	var $layout = 'admin';
	var $helpers = array( 'Form' );

	function index() {
		// Pagina principal del administrador
		
	}

	function eliminado() {
		$this->log( "Usuario eliminando nuestra aplicacion" );
		$this->log( $this );
		$usuario = $this->facebook->get_loggedin_user();
		if ( $usuario != NULL && $this->facebook->fb_params['uninstall'] == 1) {
			//The user has removed your app
			// Elimino todos los mensajes que fueron a este usuario
			$this->Saludos->eliminarRecibidosDe( $usuario );
			// Los mensajes que mando se quedan.
			$this->Usuario->eliminarUsuario( $usuario );
			$this->Imagenes->eliminarPrivadasDe( $usuario );
		}
	}

	function primerUso() {
		$this->log( "Usuario ".$this->facebook->get_loggedin_user()." agrego nuestra aplicacion" );
		/*
		  Ingreso el usuario como usuario del programa hasta que se de de baja
		  @todo Ver que permisos voy a necesitar
		*/
		// Lo agrego a la base de datos de usuarios que estan utilizando el programa
		$this->Usuario->agregarUsuario( $this->facebook->get_loggedin_user() );
		echo "<fb:redirect url=\"http://apps.facebook.com/felizsabado/\" />";
		return;
	}

	function agregarimagen() {
		$this->render( 'agregarimagen' );
	}

	function subirimagen() {
		// La imagen se recibio x post
		if( empty( $this->data ) ) {
			$this->render( 'agregarimagen' );	
		} else {
			
		}
	}

	function eliminacion() {
		$this->set( 'candidatos', $this->Saludos->find( 'all', array( 'conditions' => array( 'aeliminar' => 1 ) ) ) );
	}

	function eliminar_nopost() {
		$this->Saludos->eliminar_nopublicados();
		echo "<fb:redirect url=\"http://apps.facebook.com/felizsabado/mantenimiento/\" />";
		return;
	}

	function eliminar_todo() {
		$datos = $this->Saludos->fin( 'all', array( 'conditions' => array( 'aeliminar' => 1 ) ) );
		foreach( $datos as $dato ) {
			if( $dato['Saludos']['publicado'] != null ) {
				$this->facebook->api_client->stream_remove( $dato['Saludos']['publicado'] );
			}
		}
		$this->Saludos->deleteAll( array( 'conditions' => array( 'aeliminar' => 1 ) ) );
		echo "<fb:redirect url=\"http://apps.facebook.com/felizsabado/mantenimiento/\" />";
		return;
	}

	function eliminar_vencidos() {
		$this->Saludos->eliminar_vencidos();
		echo "<fb:redirect url=\"http://apps.facebook.com/felizsabado/mantenimiento/\" />";
		return;
	}
}
?>