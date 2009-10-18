<?php

class PublicidadesController extends AppController {
	 var $name = 'Publicidades';
	 var $uses = 'Publicidad';

	 function beforeFilter() {
		$this->Auth->allow( 'random', 'publicita' );
	 }

	 function admin_index() {
		$this->layout = 'admin';
		$this->set( 'datos', $this->paginate() );
	 }

	function admin_agregar() {
		$this->layout = 'admin';
		if( !empty( $this->data ) )
		{
			// Verifico que este bien subido el archivo y lo copio
			if ((isset($this->data['Publicidad']['archivo_subido']['error']) && $this->data['Publicidad']['archivo_subido']['error'] == 0) || (!empty($this->data['Publicidad']['archivo_subido']['tmp_name']) && $this->data['Publicidad']['archivo_subido']['tmp_name'] != 'none'))
 			{
				$destino = WWW_ROOT . 'img' . DS . 'publicidades' . DS . $this->data['Publicidad']['archivo_subido']['name'];
				// Nombre de archivo busco el nombre de la fecha + un numero
				//$nombre_archivo = "
				if( !copy( $this->data['Publicidad']['archivo_subido']['tmp_name'] , $destino ) )
				{
					$this->flash( "Error al copiar el archivo", '/admin/publicidades' );
				}
				$this->data['Publicidad']['archivo'] = 'publicidades' . DS . $this->data['Publicidad']['archivo_subido']['name'];
				// El archivo se subio bien
				if( $this->Publicidad->save( $this->data ) )
				{
					$this->redirect( '/admin/publicidades' );
				}
			} else {
				// Error al subir el archivo
				$this->flash(' NO se pudo subir el archivo', '/admin/publicidades/index' );
			}
		}
		else
		{ $this->render(); }
	}

	function admin_eliminar( $id_publicidad = null ) {
		// Elimino el archivo
		$dato = $this->Publicidad->find( 'first', array( 'conditions' => array( 'id_publicidad' => $id_publicidad ), 'fields' => 'archivo' ) );
		$this->Publicidad->del( $id_publicidad );
		pr($dato);
		if( unlink( $dato['Publicidad']['archivo'] ) )
		{
			$this->redirect( '/admin/publicidades/index' );
		}
		else
		{
			$this->Session->setFlash( 'Error al eliminar el archivo!' );
			$this->redirect( '/admin/publicidades/index' );
		}
	}

	function admin_publicar( $publicar, $id_publicidad ) {
		$this->Publicidad->id = $id_publicidad;
		$this->Publicidad->saveField( 'publicado', $publicar );
		$this->Session->setFlash( 'Publicidad modificada correctamente' );
		$this->redirect( '/admin/publicidades/index' );
	}

	function admin_modificar( $id_publicidad = null  ) {
		$this->layout = 'admin';
		if( !empty( $this->data ) )
		{
			if( $this->Publicidad->save( $this->data ) )
			{
				$this->flash( 'Publicidad modificada correctamente', '/admin/publicidades/index' );
				return;
			}
			else
			{
				$this->flash( 'Error al guardar la publicidad', '/admin/publicidades/index' );
				return;
			}
		}
		else
		{
			$this->Publicidad->id = $id_publicidad;
			$this->set( 'Publicidad', $this->Publicidad->read() );
		}
	}

	function random () {
		// Devuelve un array random de publicidades
		$r = $this->Publicidad->find( 'list', array( 'conditions' => array( 'publicado' => 1 ), 'limit' => 8 ) );
		//shuffle( $r );
		return $r;
	}

	function publicita( $id_publicidad ) {
		//aumento el contador
		$this->Publicidad->id = $id_publicidad;
		$cant_veces = $this->Publicidad->field( 'veces_visto' );
		$this->Publicidad->saveField( 'veces_visto', $cant_veces+1 );
		$this->set( 'imagen', $this->Publicidad->field( 'archivo' ) );
		$this->set( 'alt', $this->Publicidad->field( 'nombre' ) );
		$this->set( 'url', $this->Publicidad->field( 'url' ) );
		return $this->render();
	}

	function admin_resetear( $id_publicidad = null ) {
		if( $id_publicidad == null ) { $this->Session->setFlash( 'El id de publicidad es incorrecto' ); $this->redirect( '/admin/publicidades/index' ); }
		$this->Publicidad->id = $id_publicidad;
		$this->Publicidad->saveField( 'veces_visto', 0 );
		$this->Session->setFlash( 'Contador reseteado correctamente' );
		$this->redirect( '/admin/publicidades/index' );
	}
}
?>