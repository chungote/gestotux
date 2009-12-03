<?php

class PropiedadesController extends AppController {

 var $name = "Propiedades";
 var $components = array( 'othAuth' );
 var $uses = array( "Propiedad", "Caracteristica" );
 var $othAuthRestrictions = array( 'agregar', 'modificar', 'eliminar', 'lista', 'agregarImagen' );
 var $helpers = array( 'javascript', 'ajax', 'bordes' );

 function lista()
 {
   $this->layout = 'admin';
   $this->pageTitle = "Listado de Propiedades";
   $condicion = "";
   if( $this->data['filtro']['zona'] != 0 )
   {
    $condicion = " propiedad.zona_id = ". $this->data['filtro']['zona'];
   }
   else if( $this->data['filtro']['estado'] != 0 )
   {
	if( $condicion == "" ) { $condicion .= " AND "; }
	$condicion .= " propiedad.estado = ".$this->data['filtro']['estado'];
   }
   else if( $this->data['filtro']['situacion'] != 0 )
   {
	if( $condicion == "" ) { $condicion .= " AND "; }
	$condicion .= " propiedad.situacion_id = ".$this->data['filtro']['situacion'];
   }
   $this->set( 'propiedades', $this->Propiedad->findAll( $condicion ) );
   $this->set( 'cantidad', $this->Propiedad->findCount( $condicion ) );
   $this->set( 'estados', array( 'venta' => 'Venta', 'compra' => 'Compra', 'alquiler' => 'Alquiler', 'inactivo' => 'Inactivo' ) );
   $this->set( 'situaciones', $this->Propiedad->Situacion->generateList( null, null, null, '{n}.Situacion.id', '{n}.Situacion.name' ) );
   $this->set( 'zonas', $this->Propiedad->Zona->generateList( null, null, null, '{n}.Zona.id', '{n}.Zona.name' ) );
 }

 function agregar()
 {
   $this->layout = 'admin';
   $this->pageTitle = "Agregar nueva propiedad";
   $this->set( 'zonas', $this->Propiedad->Zona->generateList( null, null, null, '{n}.Zona.id', '{n}.Zona.name' ) );
   $this->set( 'situaciones', $this->Propiedad->Situacion->generateList( null, null, null, '{n}.Situacion.id', '{n}.Situacion.name' ) );
   $this->set( 'estados', array( 'venta' => 'Venta', 'compra' => 'Compra', 'alquiler' => 'Alquiler', 'inactivo' => 'Inactivo' ) );
   $this->set( 'tipos', $this->Propiedad->Tipo->generateList( null, null, null, '{n}.Tipo.id', '{n}.Tipo.nombre' ) );
   $this->set( 'caracteristicas', $this->Propiedad->Caracteristicas->generateList( null, null, null, '{n}.Caracteristica.id', '{n}.Caracteristica.name' ) );
   $this->set( 'monedas', $this->Propiedad->Moneda->generateList( null, null, null, '{n}.Moneda.id', '{n}.Moneda.simbolo' ) );
   $this->set( 'car_todas', $this->Caracteristica->generateList( null, null, null, '{n}.Caracteristica.id', '{n}.Caracteristica.name' ) );
  if( !empty( $this->data ) )
  {
	// Chequeo que esten todos los datos
	if( $this->Propiedad->save( $this->data ) )
	{
		// Se guardo correctamente la propiedad
		//print_r( $this->data );
		$this->flash( 'Propiedad guardada correctamente', '/propiedades/lista' );
	}
      else
	{
		$this->set('errorMessage', 'Please correct errors below.');
		$this->render();
      }
  }
  else
  {

	// Acordarse de eliminar los items al compararlos cuando modifico
  }
 }

 function eliminar( $id = null )
 {
  if( $id > 0 )
  {
     $this->Propiedad->delete( $id );
     $this->flash( 'Elemento eliminado', '/propiedades/lista' );
  }
  else
  {
    $this->flash( 'El id no puede ser menor que cero', '/propiedades/lista' );
  }
 }

 function modificar( $id = null )
 {
	if( !empty( $this->data ) )
	{
		if( $this->Propiedad->save( $this->data ) )
		{
			$this->flash( 'Datos modificados correctamente', '/propiedades/lista' );
		}
		else
		{
			$this->set( 'zonas', $this->Propiedad->Zona->generateList( null, null, null, '{n}.Zona.id', '{n}.Zona.name' ) );
			$this->set( 'situaciones', $this->Propiedad->Situacion->generateList( null, null, null, '{n}.Situacion.id', '{n}.Situacion.name' ) );
			$this->set( 'estados', array( 'venta' => 'Venta', 'compra' => 'Compra', 'alquiler' => 'Alquiler', 'inactivo' => 'Inactivo' ) );
			$this->set( 'tipos', $this->Propiedad->Tipo->generateList( null, null, null, '{n}.Tipo.id', '{n}.Tipo.nombre' ) );
			$this->set( 'caracteristicas', $this->Caracteristica->generateList( '`Caracteristica`.`id` IN ( SELECT `caracteristica_id` FROM `propiedad_caracteristica` WHERE `propiedad_id` = '.$id .' ) ', null, null, '{n}.Caracteristica.id', '{n}.Caracteristica.name' ) );
			$this->set( 'monedas', $this->Propiedad->Moneda->generateList( null, null, null, '{n}.Moneda.id', '{n}.Moneda.simbolo' ) );
   /*if( $caracteristicas == array() )
   { $caracteristicas = array( -1 => 'Agregar Caracteristicas' ); }*/
			$this->set( 'car_todas', $this->Caracteristica->generateList( '`Caracteristica`.`id` NOT IN ( SELECT `caracteristica_id` FROM `propiedad_caracteristica` WHERE `propiedad_id` = '.$id .' ) ', null, null, '{n}.Caracteristica.id', '{n}.Caracteristica.name' ) );
			$this->set('errorMessage', 'Datos errados, modifique' );
			$this->render();
		}
	}
	else
	{
		$this->layout = 'admin';
		$this->pageTitle = "Modificar propiedad";
		$this->Propiedad->id = $id;
		$this->set( 'zonas', $this->Propiedad->Zona->generateList( null, null, null, '{n}.Zona.id', '{n}.Zona.name' ) );
		$this->set( 'situaciones', $this->Propiedad->Situacion->generateList( null, null, null, '{n}.Situacion.id', '{n}.Situacion.name' ) );
		$this->set( 'estados', array( 'venta' => 'Venta', 'compra' => 'Compra', 'alquiler' => 'Alquiler', 'inactivo' => 'Inactivo' ) );
		$this->set( 'tipos', $this->Propiedad->Tipo->generateList( null, null, null, '{n}.Tipo.id', '{n}.Tipo.nombre' ) );
		//print_r( $this->Propiedad->Caracteristicas->generateList( null, null, null, '{n}.Caracteristica.id', '{n}.Caracteristica.name' ) );
		$this->set( 'caracteristicas', $this->Caracteristica->generateList( '`Caracteristica`.`id` IN ( SELECT `caracteristica_id` FROM `propiedad_caracteristica` WHERE `propiedad_id` = '.$id .' ) ', null, null, '{n}.Caracteristica.id', '{n}.Caracteristica.name' ) );
		$this->set( 'car_todas', $this->Caracteristica->generateList( '`Caracteristica`.`id` NOT IN ( SELECT `caracteristica_id` FROM `propiedad_caracteristica` WHERE `propiedad_id` = '.$id .' ) ', null, null, '{n}.Caracteristica.id', '{n}.Caracteristica.name' ) );
		$this->set( 'monedas', $this->Propiedad->Moneda->generateList( null, null, null, '{n}.Moneda.id', '{n}.Moneda.simbolo' ) );
		$this->data = $this->Propiedad->read();
	}
}

 function ofertas()
 { 
  // Devuelve las ultimas n propeidades en oferta ordenadas x fecha de modificacion
  return $this->Propiedad->findAll('propiedad.situacion_id = 1 AND propiedad.estado != \'inactivo\'', null, 'propiedad.modified DESC', 9 );
 }

 function ver( $id = null )
 {
  if( $id == null )
  {
   $this->flash( 'Por favor, elija una propiedad', '/buscador/buscar' );
  }
  // Busco la propiedad
  if( $this->Propiedad->findCount( 'propiedad.id = '.$id ) > 0 )
  {
    $this->Propiedad->id = $id;
    $this->set( 'propiedad', $this->Propiedad->read() );
  }
  else
  {
   $this->flash( 'Por favor, elija una propiedad valida', '/buscador/buscar' );
  }
 }

 function imprimir( $id = null )
 {
  if( $id == null )
  {
   $this->flash( 'Por favor, elija una propiedad', '/buscador/buscar' );
  }
  // Busco la propiedad
  if( $this->Propiedad->findCount( 'propiedad.id = '.$id ) > 0 )
  {
    $this->Propiedad->id = $id;
    $this->set( 'propiedad', $this->Propiedad->read() );
    $this->layout = 'imprimir';
    $this->render();
  }
  else
  {
   $this->flash( 'Por favor, elija una propiedad valida', '/buscador/buscar' );
  }
 }

}

?>