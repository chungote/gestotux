<?php

class AdminController extends AppController {

   var $name = "admin";
   var $components = array( 'othAuth' );
   // Define un template alternativo
   var $layout = 'admin';
   // Deja usar el controlador sin un modelo
   var $uses = "";
   // Permite que solo usuarios loggeados puedan usar el componente
   var $othAuthRestrictions = '*';

   function index()
   {
    // Se muestra la pagina de inicio
   }

   function galeria()
   {
    //echo "<p>".$this->gallery->imageBlock()."</p>";
   }

}

?>