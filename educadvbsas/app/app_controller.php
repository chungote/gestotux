<?php
App::import('Core', 'l10n');
class AppController extends Controller {
	var $components = array( 'Auth' );
	var $helpers = array( 'Time', 'Html', 'Form', 'Javascript', 'Paginator' );

	function beforeFilter() {
		$this->columnas( true, true );
		$this->Auth->userModel = 'personal';
		$this->Auth->fields = array( 'username' => 'usuario', 'password' => 'contraseña' );
		$this->Auth->allow( '*' );
		$this->L10n = new L10n();
		$this->L10n->get("spa");
      }

	function columnas( $der = false, $izq = false ) {
		$this->set( 'col_der', $der );
		$this->set( 'col_izq', $izq );
	}
function referer()
                {
                        if (env('HTTP_REFERER') && FULL_BASE_URL )
                        {
                                $base = FULL_BASE_URL . $this->webroot;
                                if (strpos(env('HTTP_REFERER'), $base) == 0)
                                {
                                        $referer=substr(env('HTTP_REFERER'), strlen($base)-3);
                                        if (! SERVER_APACHE)
                                        {
                                                if (strpos($referer,"?url=")===0)
                                                {
                                                        $referer=substr($referer,5);
                                                }
                                                if (strpos($referer,"&"))
                                                {
                                                        $referer=explode("&",$referer);
                                                        $referer=$referer[0];
                                                }
                                        }
                                        return $referer;
                                }
                                else return '/';
                        }
                        else return '/';
                }

        function redirect ($url)
       {
                $this->autoRender = false;
                if(strpos($url, '/') !== 0)
                {
                        $url = '/'.$url;
                }
                if (function_exists('session_write_close'))
                {
                    session_write_close();
                }
                if (SERVER_APACHE)
                {
                        header ('Location: '.$this->base.$url);
                }
                else
                {
                        header('Location: http://' .  $_SERVER['HTTP_HOST'] .
$this->base . $url);
                }
            }

}
?>