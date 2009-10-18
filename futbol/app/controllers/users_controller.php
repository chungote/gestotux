<?php
class UsersController extends AppController {
	var $name = "Users";
	var $belongsTo = "Grupo";
	var $layout = 'admin';
	var $scaffold;

	function beforeFilter() {
		$this->L10n = new L10n();
		$this->L10n->get("spa");
	}

      function login() {
		$this->layout = 'login';
	}

	function logout() {
		$this->redirect($this->Auth->logout());
	}

	function cpanel() {
		$this->layout = 'admin';
		$this->pageTitle = '.:: Administracion ::..';
	}

	function admin_login() {
		$this->redirect( '/users/login' );
	}

	function admin_index() {
		$this->layout = 'admin';
		$this->set( 'usuario', $this->Auth->user() );
	}

	function admin_cambiar() {
		if( !empty( $this->data ) ) {
			$this->Auth->fields = array( 'user' => 'username', 'password' => 'password' );
			if( $this->data['User']['pass_nueva'] != $this->data['User']['pass_nueva_2'] )
			{
				$this->Session->setFlash( "La contrase&ntilde;a nueva no coincide" );
				$this->redirect( '/admin/users/cambiar' );
			}
			$this->data['User']['password'] = $this->data['User']['pass_nueva'];
			unset( $this->data['User']['pass_nueva'] );
			unset( $this->data['User']['pass_nueva_2'] );
			$datos = $this->data['User'];
			$datos['password'] = $this->Auth->password( $datos['password'] );
			if( $this->User->save( $datos ) )
			{
				$this->Session->setFlash( "Contrase&ntilde;a cambiada correctamente" );
				$this->redirect( '/admin' );
			}
		}
		else
		{
			$this->set( 'data', $this->Auth->user() );
		}
	}

	function ruta() {
		$salida = $this->render( 'panel' );
		if( $this->Nav->idTorneo() != null )
		{
			$this->set( 'id_torneo', $this->Nav->idTorneo() );
			$this->set( 'nombre_torneo', $this->Nav->nombreTorneo() );
			$salida .= $this->render( 'ruta_torneo' );
		}
		if( $this->Nav->idFecha() != null )
		{
			$this->set( 'id_fecha', $this->Nav->idFecha() );
			$this->set( 'nombre_fecha', $this->Nav->nombreFecha() );
			$salida .= $this->render( 'ruta_fecha' );
		}
		if( $this->Nav->idZona() != null ) {
			$this->set( 'id_zona', $this->Nav->idZona() );
			$this->set( 'nombre_zona', $this->Nav->nombreZona() );
			$salida .= $this->render( 'ruta_zona' );
		}
		if( $this->Nav->idEquipo() != null ) {
			$this->set( 'id_equipo', $this->Nav->idEquipo() );
			$this->set( 'nombre_equipo', $this->Nav->nombreEquipo() );
			$salida .= $this->render( 'ruta_equipo' );
		}
		return $salida;
	}

}
?>