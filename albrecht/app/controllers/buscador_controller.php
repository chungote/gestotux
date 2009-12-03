<?php
class BuscadorController extends AppController {
   var $name = 'Buscador';
   var $uses = array( 'Zona', 'Tipo', 'Propiedad', 'Moneda' );
   var $helpers = array( 'javascript', 'html', 'ajax' );

	function index()
	{
		// muestra la pagina grande del buscador
		// Hago las listas necesarias
		$this->set( 'zonas', $this->Zona->generateList( null, null, null, '{n}.Zona.id', '{n}.Zona.name' ) );
		$this->set( 'tipos', $this->Tipo->generateList( null, null, null, '{n}.Tipo.id', '{n}.Tipo.nombre' ) );
		$this->set( 'monedas', $this->Moneda->generateList( null, null, null, '{n].Moneda.id', '{n}.Moneda.simbolo' ) );
		$this->pageTitle = 'Buscador de Propiedades';
		$this->render();
	}

	function alquiler()
	{
		// Se propone buscar solamente alquileres
		$this->set( 'zonas', $this->Zona->generateList( null, null, null, '{n}.Zona.id', '{n}.Zona.name' ) );
		$this->set( 'tipos', $this->Tipo->generateList( null, null, null, '{n}.Tipo.id', '{n}.Tipo.nombre' ) );
		$this->set( 'monedas', $this->Moneda->generateList( null, null, null, '{n].Moneda.id', '{n}.Moneda.simbolo' ) );
		$this->pageTitle = 'Alquileres';
		$this->render();
	}

	function venta()
	{
		// Se propone solo buscar ventas
		$this->set( 'zonas', $this->Zona->generateList( null, null, null, '{n}.Zona.id', '{n}.Zona.name' ) );
		$this->set( 'tipos', $this->Tipo->generateList( null, null, null, '{n}.Tipo.id', '{n}.Tipo.nombre' ) );
		$this->set( 'monedas', $this->Moneda->generateList( null, null, null, '{n].Moneda.id', '{n}.Moneda.simbolo' ) );
		$this->pageTitle = 'Propiedades en Venta';
		$this->render();
	}

	function buscar()
	{
		$this->set( 'zonas',   $this->Zona  ->generateList( null, null, null, '{n}.Zona.id'  , '{n}.Zona.name'      ) );
		$this->set( 'tipos',   $this->Tipo  ->generateList( null, null, null, '{n}.Tipo.id'  , '{n}.Tipo.nombre'    ) );
		$this->set( 'monedas', $this->Moneda->generateList( null, null, null, '{n].Moneda.id', '{n}.Moneda.simbolo' ) );
		if( !empty($this->data ) )
		{
			// Empieza la busqueda
			//Genero las condiciones
			 //Venta o alquiler
				$condiciones = '';
				if( $this->data['buscador']['venta'] == 1 )
				{
					// Busca casas en venta
					$condiciones .= '`propiedad`.`estado` = \'venta\'';
				}
				else
				{
					// Busca casas en alquiler
					$condiciones .= '`propiedad`.`estado` = \'alquiler\'';
				}
				// Tipo de propiedad
				if( $this->data['buscador']['tipo_id'] != '' )
				{
					$condiciones .= ' AND `propiedad`.`tipo_id` = '.$this->data['buscador']['tipo_id'] . ' ';
				}
				// Zona
				if( $this->data['buscador']['zona_id'] != '' )
				{
					$condiciones .= ' AND `propiedad`.`zona_id` = '.$this->data['buscador']['zona_id']. ' ';
				}
				// Precio minimo
				if( $this->data['buscador']['precio_maximo'] != '' )
				{
					$condiciones .= ' AND `propiedad`.`precio` <= '.$this->data['buscador']['precio_maximo']. ' ';
					// calculo el precio en la moneda original 
				}
			$this->set( 'resultados', $this->Propiedad->findAll( $condiciones, array( 'propiedad.id', 'propiedad.direccion', 'Situacion.name', 'Zona.name', 'Tipo.nombre' ,'propiedad.dormitorios', 'propiedad.banos', 'propiedad.precio' ) ) );
		}
		else
		{
			$this->flash( 'Por favor ingrese un argumento de busqueda', '/buscador/index' );
		}
	}
}
?>