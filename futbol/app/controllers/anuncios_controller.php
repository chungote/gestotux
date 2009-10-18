<?php

class AnunciosController extends AppController {

 var $name = 'Anuncios';
 var $uses = 'Anuncio';
 var $helpers = array( 'Fck' );

 var $paginate = array( 'Anuncio' =>
	array( 'limit' => 20, 'order' => array( 'Anuncio.modified' => 'asc' ) ) );

 function beforeFilter() {
  $this->Auth->allow( 'ver', 'ultimos', 'ver_todos' );
		$this->L10n = new L10n();
		$this->L10n->get("spa");
 }

 function ver( $id_anuncio = null ) {
  if( $id_anuncio == null ) {
   $this->Session->setFlash( 'El id del anuncio es invalido' );
   $this->redirect( array( 'controller' => 'pages', 'action' => 'index' ) );
   }
   $this->Anuncio->id = $id_anuncio;
   $this->Anuncio->saveField( 'veces_visto', $this->Anuncio->field( 'veces_visto' ) + 1 );
   $this->set( 'anuncio', $this->Anuncio->read() );
 }

 function ultimos( $cantidad = 5 ) {
  $conteo = $this->Anuncio->find( 'count' );
  if( $conteo > 0 ) {
	$this->set( 'anuncios', $this->Anuncio->find( 'all', array( 'order' => array( 'modified' => 'asc', 'veces_visto' => 'desc' ), 'conditions' => array( 'Anuncio.publicado' => 1, 'Anuncio.fecha_fin_publicado <=' => date( 'Y-m-d' ) ) ) ) );
  } else { return; }
  return $this->render();
 }


 function ver_todos() {
   $this->set( 'anuncios', $this->Anuncio->find( 'all',
						array( 'order' => array( 'modified' => 'asc', 'veces_visto' => 'desc' ),
							 'conditions' => array( 'Anuncio.publicado' => 1, 'Anuncio.fecha_fin_publicado <=' => date( 'Y-m-d' ) ),
							 'fields' => array( 'id_anuncio', 'titulo', 'modified', 'veces_visto' ) ) ) );
 }

 function admin_agregar() {
  $this->layout = 'admin';
  if ( !empty( $this->data ) ) {
     if ( $this->Anuncio->save( $this->data ) ) {
         $this->Session->setFlash( "El Anuncio ha sido guardado" );
         $this->redirect( array( 'action' => 'admin_index' ) );
     }
     else {
	   $this->Session->setFlash( "Error al intentar guardar el anuncio" );
     }
  }
 }

 function admin_index()  {
  $this->layout = 'admin';
  $this->set( 'anuncios', $this->paginate( 'Anuncio' ) );
 }

 function admin_modificar( $id_anuncio = null )
 {
  if( $id_anuncio == null )
  {
   $this->Session->setFlash( "El identificador de anuncio es incorrecto" );
   $this->redirect( array( 'action' => 'admin_index' ) );
  }
  $this->layout = 'admin';
  $this->Anuncio->id = $id_anuncio;
  if( !empty( $this->data ) )
  {
	if ($this->Anuncio->save($this->data)) {
		$this->Session->setFlash('El anuncio ha sido actualizado.');
		$this->redirect(array('action' => 'admin_index'));
	} else {
		$this->Session->setFlash( 'Error al intentar guardar el anuncio, verifique' );
	}
  }
  else
  {
   $this->data = $this->Anuncio->read();
  }
 }

 function admin_eliminar( $id_anuncio = null ) {
  if( $id_anuncio == null ) {
   $this->Session->setFlash( "El identificador de anuncio es incorrecto" );
   $this->redirect( array( 'action' => 'admin_index' ) );
  }

  $this->Anuncio->del( $id_anuncio );
  $this->Session->setFlash( 'Anuncio eliminado correctamente' );
  $this->redirect( array( 'action' => 'admin_index' ) );
 }

	function admin_publicar( $publicar, $id_anuncio ) {
		$this->Anuncio->id = $id_anuncio;
		$this->Anuncio->saveField( 'publicado', $publicar );
		$this->Session->setFlash( 'Anuncio modificada correctamente' );
		$this->redirect( array( 'action' =>'admin_index' ) );
	}

}
?>