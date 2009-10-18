<?php
class InscripcionesController extends AppController {
 var $name = 'Inscripciones';
 var $uses = '';
 var $components = array( 'Email' );

 function beforeFilter() {
  $this->Auth->allow( 'index', 'enviar' );
 }

 function index() {
 }

 function enviar() {
  if( empty( $this->data ) )
  {
   $this->redirect( '/inscripciones/index' );
  }
  else
  {
   // Creo un email
   $this->Email->from = $this->data['Inscripcion']['nombre']. " <". $this->data['Inscripcion']['email'] . ">";
   $this->Email->to   = 'treslibrasbass@hotmail.com';
   $this->Email->replyTo = $this->data['Inscripcion']['nombre']. " <". $this->data['Inscripcion']['email'] . ">";
   $this->Email->subject = 'Nueva Inscripcion';
   $this->Email->template = 'inscripcion';
   $this->Email->send = 'html';
   $this->set( 'datos', $this->data['Inscripcion'] );
   $this->Email->send();
  }
 }

}
?>
