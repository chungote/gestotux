<?php

class AppController extends Controller {

var $components  = array('othAuth'); // necessary, we need to have the othauth component so it can do it's business logic 
var $helpers = array('Html', 'OthAuth', 'Bordes', 'Thumbnail' ); // html is always needed, othauth helper is not a must, but you can do some cool things with it (see later on)
var $othAuthRestrictions = array( 'add','edit','delete');  // these are the global restrictions, they are very important. all the permissions defined above are weighted against these restrictions to calculate the total allow or deny for a specific request.

function beforeFilter()
    {
        
        $auth_conf = array(
                    'mode'  => 'oth',
                    'login_page'  => '/users/login',
                    'logout_page' => '/users/logout',
                    'access_page' => '/admin/index',
                    'hashkey'     => 'Tranfuga',
                    'noaccess_page' => '/users/noaccess',
                    'strict_gid_check' => false );
        
        $this->othAuth->controller = &$this;
        $this->othAuth->init($auth_conf);
        $this->othAuth->check();
        
    }


}
?>