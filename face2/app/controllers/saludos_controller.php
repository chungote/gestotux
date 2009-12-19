<?php

class SaludosController extends AppController {
	var $name = 'Saludos';
	var $uses = array( 'Saludos', 'Imagenes' );

	function noleidos() {
		return $this->Saludos->noleidos( $this->getUidFacebook() );
	}

	function enviados() {
		return $this->Saludos->enviados( $this->getUidFacebook() );
	}

	function recibido( $uid_remitente = null ) {
		if( $uid_remitente != null ) {
			if( $this->Saludos->buscarNuevo( $uid_remitente, $this->getUidFacebook() ) > 0 ) {
					
				$this->set( 'saludosNuevos', $this->Saludos->detalleNuevo( $uid_remitente, $this->getUidFacebook() ) );
				$this->set( 'saludosAnteriores', $this->Saludos->detalleViejo( $uid_remitente, $this->getUidFacebook() ) );
				//$this->set( 'saludos', $this->Saludos->detalleNoLeido( $this->getUidFacebook() ) );
				$this->render( 'recibidos/recibidonya' );	
			} else {
				$this->set( 'saludos', $this->Saludos->detalleNoLeido( $this->getUidFacebook() ) );
				$this->render( 'recibidos/recibido' );
			}
		} else {
			$this->set( 'saludos', $this->Saludos->detalleNoLeido( $this->getUidFacebook() ) );
			$this->render( 'recibidos/recibido' );
		}
	}


	function crear( $id_imagen = null ) {
		$this->layout = 'usando';
		$this->set( 'id_imagen', $id_imagen );
		$this->render( 'envio/mensaje' );
	}

	function imagen() {
		$this->layout = 'usando';
		if( empty( $this->params['form']['titulo'] ) ) {
			$this->render( 'envio/titulovacio' );
			return;
		} else if( empty( $this->params['form']['texto'] ) ) {
			$this->render( 'envio/textovacio' );
			return;
		} else {
			// Busco las imagenes que no sean privadas
			$this->set( 'titulo', $this->params['form']['titulo'] );
			$this->set( 'texto', $this->params['form']['texto'] );
			$this->render( 'envio/imagen' );
		}
	}

	function amigos() {
		$this->layout = 'usando';
		//pr( $this->params );
		if( empty( $this->params['form']['titulo'] ) ) {
			$this->render( 'titulovacio' );
			return;
		} else if( empty( $this->params['form']['texto'] ) ) {
			$this->render( 'textovacio' );
		}
		else {
			//pr( $this );
			// Busco las imagenes que no sean privadas
			$this->set( 'contenido',
				$this->params['form']['texto'] );
			$this->set( 'titulo',
				$this->params['form']['titulo'] );
			if( $this->params['form']['imagen_id'] == -1 ) {
				$this->set( 'id_imagen', null );
			} else {
				$this->set( 'id_imagen', $this->params['form']['imagen_id'] );
			}
			$this->set( 'enviante', $this->getUidFacebook() );
			$this->set( 'excluir_ids', $this->Saludos->buscarEnviadosHoy( $this->getUidFacebook() ) );
			//$this->set( 'excluir_ids', array() );
			/// VERIFICO ACA SI TIENE PERMISO Y LO PIDO X FJSB
			if( $this->facebook->api_client->users_hasAppPermission( 'publish_stream' ) == 0  ) { // 0 = no
				$this->set( 'tiene_permiso', false );
			} else { $this->set( 'tiene_permiso', true ); }
			return $this->render( 'envio/amigos' );
		}
	}

	function publicar_enviado( $titulo, $imagen_id, $contenido, $de ) {
		// Publico a quien envio
		$mensaje = ' envio un saludo de '.$titulo;
		$adjunto = array();
		if( $imagen_id != null ) {
			$adjunto = array( 'description' => $contenido,
						'media' => array(
								array( 'type' => 'image',
									 'src' => $this->Imagenes->ruta_miniatura( $imagen_id ),
									 'href' => 'http://apps.facebook.com/felizsabado/'
								)
							 ) );
		} else {
			$adjunto = array( 'description' => $contenido );
		}
		$adjunto = json_encode( $adjunto );
		$acciones =  array(
				 array( 'text' => 'Mandar Feliz Sabado',
					  'href' => 'http://apps.facebook.com/felizsabado/saludos/crear' )
				); $acciones = json_encode( $acciones );
		$id_publicacion = $this->facebook->api_client->stream_publish( $mensaje, $adjunto, $acciones, null, $de );
		return;
	}

	function publicar_devuelto( $titulo, $imagen_id, $contenido, $de, $original ) {
		// Publico a quien envio
		$mensaje = ' devolvio el saludo de '.$titulo/*.' a {*'.$original'.}'*/;
		$adjunto = array();
		if( $imagen_id != null ) {
			$adjunto = array( 'description' => $contenido,
						'media' => array(
								array( 'type' => 'image',
									 'src' => $this->Imagenes->ruta_miniatura( $imagen_id ),
									 'href' => 'http://apps.facebook.com/felizsabado/'
								)
							 ) );
		} else {
			$adjunto = array( 'description' => $contenido );
		}
		$adjunto = json_encode( $adjunto );
		$acciones =  array(
				 array( 'text' => 'Mandar Feliz Sabado',
					  'href' => 'http://apps.facebook.com/felizsabado/saludos/crear' )
				); $acciones = json_encode( $acciones );
		$id_publicacion = $this->facebook->api_client->stream_publish( $mensaje, $adjunto, $acciones, null, $de );
		return;
	}

	function enviar() {
		if( !isset( $this->params['form']['imagen_id'] ) ) {
   echo "<fb:redirect url=\"http://apps.facebook.com/felizsabado/\" />";
			return;
		}
		if( $this->params['form']['imagen_id'] <= 0 ) {
			$this->params['form']['imagen_id'] = null;
		}
		foreach( $this->params['form']['ids'] as $usuario ) {
			$id = -1;
			if( $this->Saludos->guardar( $usuario, $this->getUidFacebook(), $this->params['form']['titulo'], $this->params['form']['contenido'], $this->params['form']['imagen_id'] ) ) {
				// Envio la notificacion
				$this->facebook->api_client->notifications_send( $usuario,
					" te ha enviado un <b>Saludo de ".$this->params['form']['titulo']."</b>.", 'user_to_user' );
			} else {
				echo "<fb:error message=\"Error - no se pudo guardar el saludo para el usuario ".$usuario."\"</fb:error>";
			}
		}
		$this->publicar_enviado( $this->params['form']['titulo'], $this->params['form']['imagen_id'], $this->Imagenes->texto( $this->params['form']['imagen_id'] ), $this->getUidFacebook() );
  echo "<fb:redirect url=\"http://apps.facebook.com/felizsabado/\" />";
		return;
	}


	function devolver( $uid_destinatario, $uid_remitente, $fecha ) {
		$this->layout = 'usando';
		$this->set( 'destinatario', $uid_destinatario );
		$this->set( 'de_anterior', $uid_destinatario );
		$this->set( 'para_anterior', $uid_remitente );
		$this->set( 'fecha_anterior', $uid_remitente );
		$this->render( 'devolucion/respuesta' );
	}

	function devolver_imagen() {
		$this->set( 'destinatario', $this->params['form']['destinatario'] );
		$this->set( 'titulo', $this->params['form']['titulo'] );
		$this->set( 'texto', $this->params['form']['texto'] );
		$this->set( 'para_anterior', $this->params['form']['para_anterior'] );
		$this->set( 'de_anterior', $this->params['form']['de_anterior'] );
		$this->set( 'fecha_anterior', $this->params['form']['fecha_anterior'] );
		$this->set( 'enviante', $this->getUidFacebook() );
		$this->set( 'imagen_id', -1 );
		$this->render( 'devolucion/imagen' );
	}

	function enviar_devolucion() {
		if( empty( $this->params['form']['titulo'] ) ) {
			$this->render( 'envio/titulovacio' );
			return;
		} else if( empty( $this->params['form']['texto'] ) ) {
			$this->render( 'envio/textovacio' );
			return;
		} else {
			$this->set( 'destinatario', $this->params['form']['destinatario'] );
			$this->set( 'titulo', $this->params['form']['titulo'] );
			$this->set( 'texto', $this->params['form']['texto'] );
			$this->set( 'para_anterior', $this->params['form']['para_anterior'] );
			$this->set( 'de_anterior', $this->params['form']['de_anterior'] );
			$this->set( 'fecha_anterior', $this->params['form']['fecha_anterior'] );
			$this->set( 'enviante', $this->getUidFacebook() );
			$this->set( 'id_imagen', $this->params['form']['imagen_id'] );
			$this->set( 'ruta_imagen', $this->Imagenes->ruta_miniatura( $this->params['form']['imagen_id'] ) );
			$this->set( 'texto_imagen', $this->Imagenes->texto_miniatura( $this->params['form']['imagen_id'] ) );
			$this->render( 'devolucion/enviar' );
		}
	}

	function enviado_devolucion() {
		// Enviar directamente
		if( $this->Saludos->guardar( $this->params['form']['destinatario'],
						     $this->getUidFacebook(),
						     $this->params['form']['titulo'],
						     $this->params['form']['texto'],
						     $this->params['form']['imagen_id'] ) ){
			// guardado correctamente
			// envio la notificacion
			$this->facebook->api_client->notifications_send( $this->params['form']['destinatario'],
					"<fb:name uid=\"".$this->getUidFacebook()."\"> te ha respondido el un <b>Saludo de ".$this->params['form']['titulo']."</b>." .
					"<a href=\"http://apps.facebook.com/felizsabado/vercompleto/".$this->params['form']['destinatario'].'/'.$this->getUidFacebook(), 'user_to_user' );
			$this->set( 'error', false );
			$this->Saludos->marcarDevuelto( $this->params['form']['de_anterior'], // el que envio el mensaje es a quien contestamos
								  $this->params['form']['para_anterior'],
								  $this->params['form']['fecha_anterior'] );
			// Publico que devolvio el saludo
			$this->publicar_devuelto( $this->params['form']['titulo'], $this->params['form']['imagen_id'], $this->params['form']['contenido'], $this->getUidFacebook(), $this->params['form']['de_anterior'] );
		} else {
			$this->set( 'error', true );
		}
		$this->render( 'devolucion/enviado' );
	}

	function vercompleto( $de, $para, $fecha ) {
		// Veo que id de imagen es
		if( $para != $this->getUidFacebook() ) {
			$this->render( 'permiso/intruso' ); return;
		}
		$datos = $this->Saludos->find( 'first',
						array( 'conditions' =>
							array( 'de' => $de ,
								'para' => $para,
								'fecha' => $fecha ) ) );
		$this->Saludos->marcarComoLeido( $de, $para, $fecha );
		$id_imagen = $datos['Saludos']['imagenes_id'];
		$this->set( 'datos', $datos );
		if( $id_imagen != null ) {
			$this->Imagenes->id = $id_imagen;
			$tipo = $this->Imagenes->field( 'tipo' );
			if( $tipo == "flash" ) {
				$this->render( 'ver/flash' );
			} else if( $tipo == "imagen" ) {
				$this->render( 'ver/imagen' );
			}
		} else {
			// Mensaje sin imagen
			$this->render( 'ver/normal' );
		}
	}



	function publicar( $de, $para, $fecha ) {
		if( $this->getUidFacebook() != $para ) {
			$this->render( 'permiso/intruso' );
		}
		if( $this->facebook->api_client->users_hasAppPermission( 'publish_stream' ) == 0  ) { // 0 = no
			$this->set( 'dir', 'http://apps.facebook.com/felizsabado/saludos/publicar/'.$de.'/'.$para.'/'.$fecha );
			$this->render( 'permiso/publicar' );
			return;
		}
		$datos = $this->Saludos->find( 'first',
							array( 'conditions' =>
								array( 'de' => $de ,
									'para' => $para,
									'fecha' => $fecha ) ) );
		$mensaje = ' recibio un saludo de Feliz Sabado';
		$adjunto = array();
		if( $datos['Saludos']['imagenes_id'] == 0 ) {
			$adjunto = array(
				'name' => $datos['Saludos']['titulo'],
				'href' => 'http://apps.facebook.com/felizsabado/saludos/vercompleto/'.$datos['Saludos']['de'].'/'.$datos['Saludos']['para'].'/'.$datos['Saludos']['fecha'],
				/*'caption' => $datos['Saludos']['titulo'],*/
				'description' => $datos['Saludos']['mensaje']
			);
		} else {
			if( $datos['Imagenes']['tipo'] == 'imagen' ) {
				$adjunto = array(
					'name' => $datos['Saludos']['titulo'],
					'href' => 'http://apps.facebook.com/felizsabado/saludos/vercompleto/'.$datos['Saludos']['de'].'/'.$datos['Saludos']['para'].'/'.$datos['Saludos']['fecha'],
					/*'caption' => $datos['Saludos']['titulo'],*/
					'description' => $datos['Saludos']['mensaje'] . '  ' . $datos['Imagenes']['texto'],
					'media' => array(
						array( 'type' => 'image',
							 'src' => Router::url( '/', true ) . $datos['Imagenes']['miniatura'],
							 'href' => 'http://apps.facebook.com/felizsabado/saludos/vercompleto/'.$datos['Saludos']['de'].'/'.$datos['Saludos']['para'].'/'.$datos['Saludos']['fecha']
						)
					)
				);
			} else if( $datos['Imagenes']['tipo'] == 'flash' ) {
				$adjunto = array(
					'name' => $datos['Saludos']['titulo'],
					'href' => 'http://apps.facebook.com/felizsabado/saludos/vercompleto/'.$datos['Saludos']['de'].'/'.$datos['Saludos']['para'].'/'.$datos['Saludos']['fecha'],
					/*'caption' => $datos['Saludos']['titulo'],*/
					'description' => $datos['Saludos']['mensaje']. '  ' . $datos['Imagenes']['texto'],
					'media' => array(
						array( 'type' => 'flash',
							 'swfsrc' => Router::url( '/', true ) . $datos['Imagenes']['ruta'],
							 'imgsrc' => Router::url( '/', true ) . $datos['Imagenes']['miniatura'],
							 'width' => '100',
							 'height' => '80',
							 'expanded_width' => '160',
							 'expanded_height' => '120'
						)
					)
				);
			}
		}
		$acciones = array(
				 array( 'text' => 'Mandar Feliz Sabado',
					  'href' => 'http://apps.facebook.com/felizsabado/saludos/crear' )
				);
		$acciones = json_encode( $acciones );
		$adjunto = json_encode( $adjunto );
		$id_publicacion = $this->facebook->api_client->stream_publish( $mensaje, $adjunto, $acciones );
		if( $id_publicacion == 340 ) {
			$this->render( 'permiso/excedido' );
		}
		$this->Saludos->guardarPublicado( $de, $para, $fecha, $id_publicacion );
		echo "<fb:redirect url=\"http://apps.facebook.com/felizsabado/\" />";
		return;
	}

	function eliminar( $de, $para, $fecha ) {
		// Veo si esta publicado
		$post_id = $this->Saludos->publicado( $de, $para, $fecha );
		$this->log( "Eliminando post: ".$post_id  );
		if( $post_id != null ) {
			// Eliminar el posteo
			$this->facebook->api_client->stream_remove( $post_id );
		}
		$this->Saludos->marcarAEliminar( $de, $para, $fecha );
		$this->render( 'recibidos/eliminar' );
	}


	function marcarvisto( $de, $para, $fecha ) {
		$this->Saludos->marcarComoLeido( $de, $para, $fecha );
  echo "<fb:redirect url=\"http://apps.facebook.com/felizsabado/\" />";
		return;
	}
}
?>