<?php
class NoticiasController extends AppController {
	var $uses = 'Noticias';
	var $scaffold;

	function ultimas() {
		return $this->Noticias->ultimas();
	}
	
	function leer( $id_noticia = null ) {
		if( $id_noticia == null ) {
			$this->Session->setFlash( 'La noticia es invalida' );
			$this->redirect( '/' );
		}
	
		$this->Noticias->id = $id_noticia;
		$this->set( 'noticia', $this->Noticias->read() );
		$this->set( 'col_izq', false );
		$this->set( 'col_der', false );
	}
	
	function resumenes() {
		$this->set( 'noticias', $this->Noticias->ultimas() );
		$this->set( 'col_izq', false );
		$this->set( 'col_der', false );
		
	}
}
?>