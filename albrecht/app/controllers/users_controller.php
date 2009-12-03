<?php
class UsersController extends AppController {

  var $scaffold;
  var $components = array( 'othAuth' );
  var $helpers = array( 'othAuth', 'form' );
  var $layout = 'admin';
  //var $othAuthRestrictions = '*';

  function login()
  {
    if(isset($this->params['data']))
    {
        $auth_num = $this->othAuth->login($this->params['data']['User']);
        $this->set('auth_msg', $this->othAuth->getMsg( $auth_num ) );
    }
  }

  function logout()
  {
    $this->othAuth->logout();
    $this->flash('Usted ha salido correctamente de nuestra pagina!','/');
  }

  function noaccess()
  {
    $this->flash("Usted no tiene permisos para ingresar a esta seccion.",'/users/login');
  }

  function cambiarPass() {
	if( !empty($this->data) )
	{
		// Controlo que las 2 contraseñas sean iguales
		if( $this->data['user']['passwd_ant'] == $this->data['user']['passwd_nueva'] )
		{
			$this->set( 'mensaje', "La contraseña nueva no puede ser igual a la anterior" );
			$this->render();
			return;
		}
		else if( $this->data['user']['passwd_nueva'] != $this->data['user']['passwd_nueva_conf'] )
		{
			$this->set( 'mensaje', "Las contraseñas nuevas no coinciden" );
			$this->render();
			return;
		}
		else
		{
			//Guardo la contraseña
			$this->data['user']['passwd'] = $this->data['user']['passwd_nueva'];
			if( $this->User->save( $this->data ) )
			{
				$this->flash( 'Contraseña cambiada correctamente', '/admin' );
				return;
			}
		}
	}
	else
	{
		$this->render();
	}
  }

}
?>