<?php

class ImagenesController extends AppController
{
  var $name = 'imagenes';
  var $uses = 'imagen';
  var $othAuthRestrictions = array( 'agregarImagen', 'eliminar' );

 function agregarImagen( $id = null )
 {
	if( !empty( $this->data ) )
	{
		$this->layout = 'admin';
		// Veo si tiene los datos
		if( $this->data['imagen']['nombre'] == '' )
		{
			echo "Por favor, ingrese un nombre para el archivo";
		}
		else if( $this->data['imagen']['descripcion'] == '' )
		{
			echo "Por favor, ingrese una descripcion para el archivo";
		}
		else if( $this->data['imagen']['propiedad_id'] == '' )
		{
			echo "Error, no hay propiedad a la que asignar la foto!";
		}
		else
		{
			// Verifico si hay un archivo
			echo "<div style=\"color: blue;\">Datos correctos.</div>";
			//	print_r( $this->data );
			if( $this->data['imagen']['filename'] == '' )
			{
				echo "<div style=\"color: red;\">Falta el archivo.</div>";
				print_r( $this->params );
			}
			else
			{
				$this->imagen->setup();
				if( $this->imagen->save( $this->data , false ) )
				{
					echo "<div style=\"color: blue\">Imagen Agregada correctamente</div>";
					$this->flash( 'Volver a modificar propiedad', "/propiedades/modificar/{$id}" );
				}
			}
		}
	}
	else
	{
		// Muestro el formulario para agregar una propiedad
		if( $id == null )
		{
			$this->layout = 'admin';
			$this->flash( 'Error, no hay propiedad seteada', '/propiedades/lista' );
		}
		// leo los datos de la propiedad
		$this->imagen->Propiedad->id = $id;
		$this->set( 'propiedad',  $this->imagen->Propiedad->field( 'direccion' ) );
		$this->set( 'id', $this->imagen->Propiedad->field( 'id' ) );
		$this->layout = 'admin';
		$this->render();
	}
 }

	function eliminar( $id = null, $anterior = null )
	{
		if( $id != null )
		{
			if( $anterior == null ) { $anterior = 0; }
			$this->imagen->setup();
			if( $this->imagen->del( $id ) )
			{
				$this->flash( 'Imagen Eliminada Correctamente', '/propiedades/modificar/'.$anterior );
			}
			else
			{
				$this->flash( 'No se pudo eliminar la imagen', '/propiedades/modificar/'.$anterior );
			}
		}
	}

	function imagenesChicas( $id = null )
	{
		if( $id == null ) return array();
		$campos = array( 'filename', 'ruta', 'principal' );
		return $this->imagen->findAll( 'imagen.propiedad_id = '.$id.' AND imagen.visible = 1', $campos, 'imagen.orden ASC' );
	}

	function subirOrden( $id = null, $anterior = null ) {
		if( $id == null ) { $this->flash( 'imagen desconocida', '/propiedades/lista' ); }
		if( $anterior == null ) { $this->flash( 'propiedad desconocida', '/propiedades/lista' ); }
		$this->imagen->setup();
		// busco el orden que tiene ahora
		$this->imagen->id = $id;
		$orden = $this->imagen->field( 'orden' );
		if( $orden <= 0 )
		{
			// No hago nada, ya es el primero
			$this->flash( 'Imagen en el tope', '/propiedades/modificar/'.$anterior );
			return;
		}
		else
		{
			// Busco si hay una imagen antes
			$imagenes = $this->imagen->query( 'SELECT id, orden FROM imagenes WHERE orden <= '.$orden.' AND propiedad_id = '.$anterior.' AND id != '.$id );
			print_r( $imagenes );
			if( sizeof( $imagenes ) == 0 )
			{
				// No hay imagenes antes, simplemente disminuyo el numero
				$this->imagen->saveField( 'orden', $orden-1 );
				$this->flash( 'Imagen subida', '/propiedades/modificar/'.$anterior );
			}
			else
			{
				// Hay al menos una imagen antes, veo si es inmediata
				if( $imagenes[sizeof($imagenes)-1]['imagenes']['orden'] == $orden -1 )
				{
					// Intercambio los indices
					$orden_nuevo = $imagenes[sizeof($imagenes)-1]['imagenes']['orden'];
					$this->imagen->id = $imagenes[sizeof($imagenes)-1]['imagenes']['id'];
					$this->imagen->saveField( 'orden', $orden );
					$this->imagen->id = $id;
					$this->imagen->saveField( 'orden', $orden_nuevo );
					$this->flash( 'Imagen Subida 3', '/propiedades/modificar/'.$anterior );
				}
				else
				{
					// esta mas lejos que uno, simplemente disminuyo el numero
					$this->imagen->saveField( 'orden', $orden-1 );
					$this->flash( 'Imagen subida2', '/propiedades/modificar/'.$anterior );
				}
			}
		}
	}

	function principalSet( $id = null, $anterior = null ) {
		if( $id == null ) { $this->flash( 'Imagen desconocida', '/propiedades/lista' ); }
		if( $anterior == null ) { $this->flash( 'propiedad desconocida', '/propiedades/lista' ); }
		$this->imagen->setup();
		$this->imagen->id = $id;
		$this->imagen->saveField( 'principal', 1 );
		$this->imagen->query( 'UPDATE imagenes SET principal = 0 WHERE propiedad_id = '.$anterior.' AND id != '.$id );
		$this->flash( 'Modificacion exitosa', '/propiedades/modificar/'. $anterior );
   }

	function bajarOrden( $id = null, $anterior = null ) {
		if( $id == null ) { $this->flash( 'imagen desconocida', '/propiedades/lista' ); }
		if( $anterior == null ) { $this->flash( 'propiedad desconocida', '/propiedades/lista' ); }
		$this->imagen->setup();
		// busco el orden que tiene ahora
		$this->imagen->id = $id;
		$orden = $this->imagen->field( 'orden' );
		// Busco si hay una imagen despues
		$imagenes = $this->imagen->query( 'SELECT id, orden FROM imagenes WHERE orden >= '.$orden.' AND propiedad_id = '.$anterior.' AND id != '.$id );
		if( sizeof( $imagenes ) == 0 )
		{
			// No hay imagenes antes, simplemente aumento el numero
			$this->imagen->saveField( 'orden', $orden+1 );
			$this->flash( 'Imagen bajada', '/propiedades/modificar/'.$anterior );
		}
		else
		{
			// Hay al menos una imagen antes, veo si es inmediata
			if( $imagenes[0]['imagenes']['orden'] == $orden +1 )
			{
				// Intercambio los indices
				$orden_nuevo = $imagenes[0]['imagenes']['orden'];
				$this->imagen->id = $imagenes[0]['imagenes']['id'];
				$this->imagen->saveField( 'orden', $orden );
				$this->imagen->id = $id;
				$this->imagen->saveField( 'orden', $orden_nuevo );
				$this->flash( 'Imagen bajada', '/propiedades/modificar/'.$anterior );
			}
			else
			{
				// esta mas lejos que uno, simplemente disminuyo el numero
				$this->imagen->saveField( 'orden', $orden+1 );
				$this->flash( 'Imagen bajada', '/propiedades/modificar/'.$anterior );
			}
		}
	}

}
?>