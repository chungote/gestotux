<?php
App::import( 'vendor','facebook', array( '/facebook/facebook.php' ) );

class AppController extends Controller {
     var $facebook;

	/* Feliz Sabado en gm
     var $__fbApiKey = 'aa8e76089dc5d15835c4d28e7450fc13';
     var $__fbSecret = 'cef1c3076c8222e221fb8951ece8e9ee';*/

	/* Feliz sabado test */
     var $__fbApiKey = '961dbb493e70a1c8be86670ac5a16443';
     var $__fbSecret = 'ac5b137f3f6c4f29db3c6332104bf47b';

     function __construct() {
        parent::__construct();

         // Prevent the 'Undefined index: facebook_config' notice from being thrown.
         $GLOBALS['facebook_config']['debug'] = NULL;

         // Create a Facebook client API object.
         $this->facebook = new Facebook($this->__fbApiKey, $this->__fbSecret);
     }

    /**
      * Name: beforeFilter
      * Desc: Performs necessary steps and function calls prior to executing
      *       any view function calls.
      */
     function beforeFilter() {
         $this->user = $this->facebook->require_login();
     }

	function getUidFacebook() {
		return $this->facebook->user;
	}
}
?>