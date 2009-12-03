<?php
class SeccionesController extends AppController {
   var $name = 'Secciones';
   var $uses ='';
   var $components = array('SwiftMailer');
   var $layout = 'default';

   function acerca() {
	$this->pageTitle = 'Quienes Somos';
   }

   function contacto() {
     $this->pageTitle = 'Formulario de Contacto';
     if( !empty( $this->data['datos'] ) )
     {
      // Verifico que existan todos los datos
      if( empty( $this->data['datos']['nombre'] ) )
	{
          $this->set( 'mensaje','Por Favor, ingrese un nombre' );
      }
	else if( empty( $this->data['datos']['email'] ) )
	{
	    $this->set( 'mensaje', 'Por Favor, ingrese un email de contacto' );
	}
	else if( empty( $this->data['datos']['telefono'] ) )
	{
	    $this->set( 'mensaje', 'Por Favor, ingrese un telefono' );
	}
	else if( empty( $this->data['datos']['mensaje'] ) )
	{
	    $this->set( 'mensaje', 'Por Favor, ingrese un mensaje' );
	}
      else
      {
       // Todos los datos son correctos
	 $this->SwiftMailer->connection = 'native';
	 if($this->SwiftMailer->connect())
	 {
		// Empiezo a armar el email
		$this->SwiftMailer->addTo( 'to', 'consulta@albrechtpropiedades.com.ar' );
		$this->SwiftMailer->addTo( 'from', $this->data['datos']['email'] );
		$mensaje = "Ha recibido un nuevo mensaje a travez de la web.\n\n\n"
				. "\n<p><b>Nombre:</b> " . $this->data['datos']['nombre']." </p>\n"
				. "<p><b>Direccion de email:</b> " . $this->data['datos']['email'] . "</p>\n"
				. "<p><b>Telefono de contacto:</b> " . $this->data['datos']['telefono'] . "</p>\n"
				. "<p><b>Mensaje:</b> \n " . $this->data['datos']['mensaje'] . "</p> \n"
				. "<p>\n\n Por favor, no responda a este email, fue generado solo con propositos informativos.</p> \n";
		if( !$this->SwiftMailer->sendWrap( 'Nuevo Contacto', $mensaje, 'plain' ) )
		{
			echo "The mailer failed to Send. Errors:";
			pr($this->SwiftMailer->errors());
			exit();
		}
	 }
	 else
	 {
		// Error
		$this->set( 'mensaje', 'Ha ocurrido un error al enviar el mensaje' );
	 }
       // Envio los datos x mail
       $this->render( 'confirmacion.contacto' );
      }
     }
     else
     {
      $this->pageTitle = 'Formulario de Contacto';
     }
   }

   function tasacion() {
     $this->pageTitle = "Tasaciones";
     if( !empty( $this->data['tasacion'] ) )
     {
      // Verifico que existan todos los datos
      if( empty( $this->data['tasacion']['nombre'] ) )
	{
          $this->set( 'mensaje','Por Favor, ingrese un nombre' );
      }
	else if( empty( $this->data['tasacion']['email'] ) )
	{
	    $this->set( 'mensaje', 'Por Favor, ingrese un email de contacto' );
	}
	else if( empty( $this->data['tasacion']['telefono'] ) )
	{
	    $this->set( 'mensaje', 'Por Favor, ingrese un telefono' );
	}
	else if( empty( $this->data['tasacion']['mensaje'] ) )
	{
	    $this->set( 'mensaje', 'Por Favor, ingrese un mensaje' );
	}
      else if( empty( $this->data['tasacion']['inmueble'] ) )
	{
		$this->set( 'mensaje', 'Por favor, ingrese un tipo de inmueble' );
	}
      else if( empty( $this->data['tasacion']['direccion'] ) )
	{
		$this->set( 'mensaje', 'Por favor, ingrese una direccion de la propiedad' );
	}
      else if( empty( $this->data['tasacion']['barrio'] ) )
	{
		$this->set( 'mensaje', 'Por favor, ingrese un barrio para el inmueble' );
	}
	else
      {
       // Todos los datos son correctos
	 $this->SwiftMailer->connection = 'native';
	 if($this->SwiftMailer->connect())
	 {
		// Empiezo a armar el email
		//$this->SwiftMailer->addTo( 'to', 'juiraze@yahoo.com.ar' );
		$this->SwiftMailer->addTo( 'to', 'tasaciones@albrechtpropiedades.com.ar' );
		$this->SwiftMailer->addTo( 'from', $this->data['tasacion']['email'] );
		$mensaje = "Ha recibido un nuevo pedido de tasacion a travez de la web.\n\n\n"
				. "\n Nombre: " . $this->data['tasacion']['nombre']." \n"
				. "Direccion de email: " . $this->data['tasacion']['email'] . "\n"
				. "Telefono de contacto: " . $this->data['tasacion']['telefono'] . " \n"
				. "Tipo de Inmueble: " .$this->data['tasacion']['inmueble']. " \n"
				. "Cantidad de Ambientes: ". $this->data['tasacion']['ambientes'] . " \n"
				. "Direccion: " . $this->data['tasacion']['direccion'] . " \n"
				. "Barrio: " . $this->data['tasacion']['barrio'] . " \n"
				. "Mensaje: \n " . $this->data['tasacion']['mensaje'] . " \n"
				. "\n\n Por favor, no responda a este email, fue generado solo con propositos informativos. \n";
		if( !$this->SwiftMailer->sendWrap( 'Nuevo Pedido de Tasacion', $mensaje, 'html' ) )
		{
			echo "The mailer failed to Send. Errors:";
			pr($this->SwiftMailer->errors());
			exit();
		}
	 }
	 else
	 {
		// Error
		$this->set( 'mensaje', 'Ha ocurrido un error al enviar el mensaje' );
	 }
       // Envio los tasacion x mail
	 $this->pageTitle = "Tasaciones";
       $this->render( 'confirmacion.tasacion' );
      }
      $this->pageTitle = "Tasaciones";
   }
  }
}
?>