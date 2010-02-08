<?php
class PersonalController extends AppController {
	var $name = "Personal";

      function login() {
		$this->layout = 'ingreso';
	}

	function logout() {
		$this->redirect($this->Auth->logout());
	}

	function cpanel() {
		$this->layout = 'admin';
		$this->pageTitle = '.:: Administracion ::..';
	}

	function admin_login() {
		$this->redirect( '/personal/login' );
	}

	function admin_index() {
		$this->layout = 'admin';
		$this->set( 'usuario', $this->Auth->user() );
	}

	function admin_cambiar() {
		if( !empty( $this->data ) ) {
			if( $this->data['Personal']['pass_nueva'] != $this->data['Personal']['pass_nueva_2'] )
			{
				$this->Session->setFlash( "La contrase&ntilde;a nueva no coincide" );
				$this->redirect( '/admin/personal/cambiar' );
			}
			$this->data['Personal']['password'] = $this->data['Personal']['pass_nueva'];
			unset( $this->data['Personal']['pass_nueva'] );
			unset( $this->data['Personal']['pass_nueva_2'] );
			$datos = $this->data['Personal'];
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
}
?>