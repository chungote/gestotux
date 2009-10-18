<?php
class ResultadosController extends AppController {

	var $name = 'Resultados';

	function beforeFilter() {
		$this->Auth->allow( 'ver_ultimo' );
	}

	function ver_ultimo( $id_torneo ) {
		$fechas = $this->Resultado->Fecha->find( 'list', array( 'conditions' => array( 'torneo_id' => $id_torneo ), 'fields' => 'id_fecha' ) );
		if( sizeof( $fechas ) <= 0 )
		{ return "<h1>No hay fechas definidas para este torneo</h1><hr>"; exit(); }
		$resultado = $this->Resultado->find( 'first', array( 'conditions' => array( 'Resultado.fecha_id' => $fechas, 'Resultado.publicado' => 1 ), 'order' => array( 'Resultado.modified' => 'desc' ), 'fields' => 'archivo' ) );
		if( sizeof( $fechas ) <= 0 )
		{ return "<h1>No hay resultados definidos para este torneo</h1><hr>"; exit(); }
		$this->set( 'resultado', $resultado );
		$this->Resultado->Fecha->Torneo->id = $id_torneo;
		$this->set( 'nombre_torneo', $this->Resultado->Fecha->Torneo->field( 'name' ) );
		// Busco las tablas de resultados que tengan otras fechas
		$this->set( 'resultados',  $this->Resultado->find( 'all', array( 'conditions' => array( 'Resultado.fecha_id' => $fechas, 'Resultado.publicado' => 1 ) ) ) );
	}

	function admin_index( $id_fecha = null ) {
		$this->layout = 'admin';
		if( $id_fecha == null )
		{
			// muestro todas las tablas de posiciones
			$this->set( 'datos', $this->Resultado->find( 'all' ) );
		}
		else
		{
			// Muestro las tablas de una fecha en especial
			$this->set( 'datos', $this->Resultado->find( 'all', array( 'conditions' => array( 'fecha_id' => $id_fecha ) ) ) );
			$this->set( 'fecha', $this->Resultado->Fecha->find( 'first', array( 'conditions' => array( 'id_fecha' => $id_fecha ), 'fields' => 'name' ) ) );
		}
	}

	function admin_agregar() {
		$this->layout = 'admin';
		if( !empty( $this->data ) )
		{
			// Verifico que este bien subido el archivo y lo copio
			if ((isset($this->data['Resultado']['archivo_subido']['error']) && $this->data['Resultado']['archivo_subido']['error'] == 0) || (!empty($this->data['Resultado']['archivo_subido']['tmp_name']) && $this->data['Resultado']['archivo_subido']['tmp_name'] != 'none'))
 			{
				$direccion =  'files' . DS . 'resultados' . DS . $this->data['Resultado']['archivo_subido']['name'];
				$destino = WWW_ROOT . $direccion;
				// Nombre de archivo busco el nombre de la fecha + un numero
				//$nombre_archivo = "
				if( !copy( $this->data['Resultado']['archivo_subido']['tmp_name'] , $destino ) )
				{
					$this->flash( "Error al copiar el archivo" );
				}
				$this->data['Resultado']['archivo'] = $direccion;
				$this->data['Resultado']['nombre'] = $this->data['Resultado']['archivo_subido']['name'];
				// El archivo se subio bien
				if( $this->Resultado->save( $this->data ) )
				{
					$this->redirect( '/admin/resultados' );
				}
			} else {
				// Error al subir el archivo
				$this->flash(' NO se pudo subir el archivo', '/admin/resultados/index' );
			}
		}
		else
		{
			$this->set( 'fechas', $this->Resultado->Fecha->find( 'list' ) );
		}
	}

	function admin_eliminar( $id_posicion ) {
		// Elimino el archivo
		$dato = $this->Resultado->find( 'first', array( 'conditions' => array( 'id_resultado' => $id_posicion ), 'fields' => 'archivo' ) );
		
		if( unlink( $dato['Resultado']['archivo'] ) )
		{
			$this->Resultado->del( $id_posicion );
			$this->redirect( '/admin/resultados' );
		}
		else
		{
			$this->flash( 'Error al eliminar el archivo!', '/admin/resultados/index' );
		}
	}

	function admin_publicar( $publicar, $id_posicion ) {
		$this->Resultado->id = $id_posicion;
		$this->Resultado->saveField( 'publicado', $publicar );
		$this->redirect( '/admin/resultados' );
	}
}
?>
