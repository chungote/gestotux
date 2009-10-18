<?php
class TipoSancionController extends AppController {

	var $name = 'TipoSancion';

      function admin_index() {
		$this->layout = 'admin';
		$this->set( 'datos', $this->paginate() );
	}

	function admin_agregar() {
		$this->layout = 'admin';
		if( !empty( $this->data ) ) {
			if( $this->TipoSancion->save( $this->data ) )
			{
				$this->Session->setFlash( "Tipo de sancion guardado" );
				$this->redirect( '/admin/tipo_sancion/index' );
			}
		}
	}

	function admin_eliminar( $id_tipo = null ) {
		if( $id_tipo == null ) {
			$this->Session->setFlash( 'Error, no se puede eliminar un tipo de sanción indefinida' );
			$this->redirect( '/admin/tipo_sancion/index' );
		} else {
			if( $this->TipoSancion->del( $id_tipo ) )	{
				$this->Session->setFlash( 'Tipo de sancion eliminada correctamente' );
			} else {
				$this->Session->setFlash( 'Error al intentar eliminar el tipo de sancion' );
			}
		}
		$this->redirect( '/admin/tipo_sancion/index' );
	}
}
?>
