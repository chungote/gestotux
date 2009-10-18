<?php
class FotosController extends AppController {

	var $name = 'Fotos';
	var $uses = 'Foto';
	var $helpers = array( 'Javascript', 'Thumbnail', 'Lightbox' );
	var $components = array( 'Thumbs', 'RequestHandler' );

	// Paginacion para la galeria
	var $paginate = array( 'fields' => array( 'Foto.id_foto', 'Foto.archivo', 'Foto.titulo', 'Foto.publicado' ), 'limit' => 12, 'order' => array( 'Foto.modified' => 'asc' ) );

	function beforeFilter() {
		$this->Auth->allow( 'index', 'ultimas', 'galeria' );
	}

	function index() {
		$this->layout = 'galeria';
		$todas = $this->Foto->findAll();
		$this->set( 'torneos', $this->Foto->Partido->Fecha->Torneo->find( 'all', array( 'conditions' => array( 'publicado' => 1 ) ) ) );
	}

	function ultimas( $portada = false ) {
		// Devuleve las ultmas n fotos agregadas
		$fotos = $this->Foto->find( 'all',
					 array(
						'conditions' => array( 'Foto.publicado' => 1 ),
						'order' => 'Foto.modified DESC',
						'limit' => 3,
						'fields' => array( 'archivo', 'id_foto', 'titulo' )
				 ) );
		$this->set( 'fotos', $fotos );
		$this->set( 'portada', $portada );
		if( $portada && sizeof( $fotos ) <= 0 ) { return; }
		return $this->render();
	}


	function galeria( $que = null, $id = null, $parameters = null ) {
		switch( $que ) {
			case "torneo": {
				// Muestro todas las fechas con su imagen correspondiente
				$fechas = $this->Foto->Partido->Fecha->find( 'list', array( 'conditions' => array( 'Fecha.publicado' => 1, 'Fecha.torneo_id' => $id ), 'fields' => 'Fecha.id_fecha' ) );
				if( sizeof( $fechas ) <= 0 ) { return; } // no hay fechas definidas
				//Busco los partidos que son de esas fechas
				$partidos = $this->Foto->Partido->find( 'list', array( 'conditions' => array( 'Partido.publicado' => 1, 'Partido.fecha_id' => $fechas ),'fields' => 'Partido.id_partido' ) );
				// Muestro todas las fotos que pertenecen a esas fechas
				$fotos = $this->Foto->find( 'count', array( 'conditions' => array( 'Foto.partido_id' => $partidos, 'Foto.publicado' => 1 ) ) );
				if( sizeof( $fotos ) <= 0 ) { echo "No existen fotos para este campeonato"; return; }
				$fotos = $this->paginate( array( 'Foto.partido_id' => $partidos, 'Foto.publicado' => 1 ) );
				$this->set( 'fotos', $fotos );
				$this->Foto->Partido->Fecha->Torneo->id = $id;
				$this->set( 'nombre_torneo', $this->Foto->Partido->Fecha->Torneo->field( 'name' ) );
				$this->set( 'id_torneo', $id );
				return $this->render( 'torneo' );
				break;
			}
			case "fechas": {
				//Muestra la lista de fechas con su foto correspondiente - el id es el id de compeonato
				$fechas = $this->Foto->Partido->Fecha->find( 'all', array( 'conditions' => array( 'Fecha.publicado' => 1, 'Fecha.torneo_id' => $id ) ) );
				if( sizeof( $fechas ) <= 0 ) { return; } // no hay fechas definidas
				$this->set( 'fechas', $fechas );
				$this->Foto->Partido->Fecha->Torneo->id = $id;
				$this->set( 'nombre_torneo', $this->Foto->Partido->Fecha->Torneo->field( 'name' ) );
				$this->set( 'id_torneo', $id );
				return $this->render( 'fechas' );
				break;
			}
			case "fecha": {
				// Muestra la galeria de todas las fotos de una fecha especifica - id es el id de la fecha
				$partidos = $this->Foto->Partido->find( 'list', array( 'conditions' => array( 'Partido.publicado' => 1, 'Partido.fecha_id' => $id ),'fields' => 'Partido.id_partido' ) );
				if( sizeof( $partidos ) > 0 ) { 
					$fotos = $this->paginate( array( 'Foto.partido_id' => $partidos, 'Foto.publicado' => 1 ) );
					$this->set( 'fotos', $fotos );
				}
				$this->Foto->Partido->Fecha->id = $id;
				$fecha = $this->Foto->Partido->Fecha->read();
				$this->set( 'nombre_fecha', $fecha['Fecha']['name'] );
				$this->set( 'id_torneo', $fecha['Fecha']['torneo_id'] );
				$this->set( 'id_fecha', $fecha['Fecha']['id_fecha'] );
				return $this->render( 'fecha' );
				break;
			}
			case "partidos": {
				$partidos = $this->Foto->Partido->find( 'all', array( 'conditions' => array( 'Partido.publicado' => 1, 'Partido.fecha_id' => $id ),'fields' => array( 'Partido.id_partido', 'Equipo1.nombre', 'Equipo2.nombre', 'FotoPartido.archivo' ), 'recursive' => 1 ) );
				if( sizeof( $partidos ) <= 0 ) { return; }
				$this->set( 'partidos', $partidos );
				$this->Foto->Partido->Fecha->id = $id;
				$this->set( 'nombre_fecha', $this->Foto->Partido->Fecha->field( 'name' ) );
				$this->set( 'id_fecha', $id );
				return $this->render( 'partidos' );
				break;
			}
			case "partido": {
				// Muestra la galeria de todas las fotos de unpartido especifico
				$fotos = $this->paginate( array( 'Foto.partido_id' => $id, 'Foto.publicado' => 1 ), array( 'Foto.id_foto', 'Foto.archivo', 'Foto.titulo' ) );
				$this->set( 'fotos', $fotos );
				$this->Foto->Partido->id = $id;
				$this->set( 'partido', $this->Foto->Partido->read() );
				$this->set( 'id_partido', $this->Foto->Partido->field( 'fecha_id' ) );
				return $this->render( 'partido' );
				break;
			}
			default: {
				// No se que rayos es.... cancelo
				exit();
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Administracion
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	function admin_index( $que = null, $id = null ) {
		$this->layout = 'admin';
				$this->paginate = array( 'limit' => 10,
					 'order' => array( 'Foto.modified' => 'asc' ),
					 'recursive' => -1 );
		if( $que == null )
		{
			$this->set( 'todas', $this->paginate( 'Foto' ) );
			$this->set( 'nombre_fecha', "complejo" );
			$this->set( 'que', null );
			$this->set( 'id', null );
			$this->render();
		}
		else
		{
			if( $que == "torneo" ) {
				$fechas = $this->Foto->Partido->Fecha->find( 'list', array( 'conditions' => array( 'torneo_id' => $id ), 'fields' => 'id_fecha' ) );
				$partidos = $this->Foto->Partido->find( 'list', array( 'conditions' => array( 'Partido.fecha_id' => $fechas ), 'fields' => 'id_partido' ) );
				$this->set( 'todas', $this->paginate( 'Foto', array( 'Foto.partido_id' => $partidos ) ) );
				$this->Foto->Partido->Fecha->Torneo->id = $id;
				$this->set( 'nombre_fecha', $this->Foto->Partido->Fecha->Torneo->field( 'name' ) );
			} else if( $que == "fecha" ) {
				$partidos = $this->Foto->Partido->find( 'list', array( 'conditions' => array( 'Partido.fecha_id' => $id ), 'fields' => 'id_partido' ) );
				$this->set( 'todas', $this->paginate( 'Foto', array( 'Foto.partido_id' => $partidos ) ) );
				$this->Foto->Partido->Fecha->id = $id;
				$this->set( 'nombre_fecha', $this->Foto->Partido->Fecha->field( 'name' ) );
			} else if( $que == "partido" ) {
				$this->set( 'todas', $this->paginate( 'Foto', array( 'Foto.partido_id' => $id ) ) );
				$this->Foto->Partido->id = $id;
				$partido = $this->Foto->Partido->read();
				$nombre_fecha = $partido['Fecha']['name'] . " - " . $partido['Equipo1']['nombre'] . " - " . $partido['Equipo1']['nombre'];
				$this->set( 'nombre_fecha', $nombre_fecha );
			}
			$this->set( 'que', $que );
			$this->set( 'id', $id );
			$this->render();
		}
	}

	function admin_agregar( $que = null, $id = null ) {
		$this->layout='admin';
		if( !empty( $this->data ) )
		{
			// Veo si el archivo se subio bien
			if ((isset($this->data['Foto']['archivo_subido']['error']) && $this->data['Foto']['archivo_subido']['error'] == 0) || (!empty($this->data['Foto']['archivo_subido']['tmp_name']) && $this->data['Foto']['archivo_subido']['tmp_name'] != 'none'))
			{
				// Pongo una galeria con el id de la fecha a la que pertenece
				$dir_galeria =  'img' . DS . 'galeria' . DS ;
				// Verifico si existe el directorio
				if( !$this->verificarDirGaleria( $this->data['Foto']['fecha_id'], $dir_galeria ) )
				{
					$this->flash( "Error al crear el directorio de la galeria", '/admin/fotos/index'.$this->data['Foto']['que'].'/'.$this->data['Foto']['id'] );
					return;
				}
				$dir_galeria .= $this->data['Foto']['fecha_id'] . DS;
				$dir_archivo = $dir_galeria . $this->data['Foto']['archivo_subido']['name'];
				if( file_exists( $dir_archivo ) )
				{
					$dir_archivo .= $this->data['Foto']['archivo_subido']['size'];
				}
				////////////////////////////////////////////////////////////////////////////////
				// Redimensionar la imagen a un tamaño razonable ( 800 x 600 )
				////////////////////////////////////////////////////////////////////////////////
				$this->Thumbs->width = 640;
				$this->Thumbs->height = 480;
				$this->Thumbs->generateThumbnail( $this->data['Foto']['archivo_subido']['tmp_name'], // source
									   $dir_archivo, // $destination
									   false, // $overwrite = true
									   false // $display = false
									);
				////////////////////////////////////////////////////////////////////////////////
				////////////////////////////
				// LA MINIATURA SE GENERARA AUTOMATICAMENTE CON CACHE
				////////////////////////////
				$this->data['Foto']['archivo'] = $dir_archivo;
				if( $this->Foto->save( $this->data ) )
				{
					// Pongo las fotos como correspondientes a la fecha o torneo si corresponde
					if( $this->data['Foto']['foto_fecha'] == 1 )
					{
					 $this->hacerFotoFecha( $this->Foto->id, $this->data['Foto']['fecha_id'] );
					}
					if( $this->data['Foto']['foto_torneo']  == 1 )
					{
					 $this->hacerFotoTorneo( $this->Foto->id, $this->data['Foto']['fecha_id'] );
					}
					if( $this->data['Foto']['foto_partido'] == 1 )
					{
					 $this->hacerFotoPartido( $this->Foto->id, $this->data['Foto']['partido_id'] );
					}
					$this->flash( "Archivo agregado correctamente", '/admin/fotos/index/'.$this->data['Foto']['que'].'/'.$this->data['Foto']['id'] );
					return;
				}
				else
				{
					$this->Session->setFlash( "No se pudo guardar la foto en la base de datos de la pagina" );
					$this->redirect( '/admin/fotos/index/'.$this->data['Foto']['que'].'/'.$this->data['Foto']['id'] );
					return;
				}
			}
			else
			{
				// Error de subir archivo
				$this->Session->setFlash( "Error al intentar subir el archivo" );
				$this->redirect( '/admin/fotos/index' );
				return;
			}
		}
		else
		{
			/// Actuo segun sea lo que quiere agregar
			if( $que == "torneo" ) {
				$this->set( 'fechas', $this->Foto->Partido->Fecha->find( 'list', array( 'conditions' => array( 'torneo_id' => $id ) ) ) );
				/*$this->set( 'partidos', $this->Foto->Partido->find( 'list',
						array(
						'conditions' =>
							 array( 'Partido.fecha_id' =>
								 $this->Foto->Partido->Fecha->find( 'list', array( 'conditions' => array( 'torneo_id' => $id ), 'fields' => 'id_fecha' ) )
								),
						'fields' => array( 'Partido.id_partido', 'CONCAT( CONCAT( Equipo1.nombre , " vs " ), Equipo2.nombre )' ),
						'recursive' => 2 ) ) );*/
			} else if( $que == "fecha" ) {
				$this->set( 'fechas', $this->Foto->Partido->Fecha->find( 'list', array( 'conditions' => array( 'id_fecha' => $id ) ) ) );
				$this->set( 'partidos', $this->Foto->Partido->find( 'list', array( 'conditions' => array( 'Partido.fecha_id' => $id ) ) ) );
			} else if( $que == "partido" ) {
				$this->set( 'partidos', $this->Foto->Partido->find( 'list', array( 'conditions' => array( 'Partido.id_partido' => $id ) ) ) );
				$this->Foto->Partido->id = $id;
				$this->set( 'partido', $this->Foto->Partido->read() );
				$this->set( 'fechas', $this->Foto->Partido->Fecha->find( 'list', array( 'conditions' => array( 'id_fecha' => $this->Foto->Partido->field( 'fecha_id' ) ) ) ) );
			}
			$this->set( 'que', $que );
			$this->set( 'id', $id );
		}
	}

	function verificarDirGaleria( $nombre, $direccion ) {
		$verificar = $direccion . $nombre;
		if( file_exists( $verificar ) )
		{ return true; }
		else
		{
			// intento crearlo
			if( is_writable( $direccion ) )
			{
				if( mkdir( $verificar ) )
				{
					return true;
				}
				else
				{
					$this->flash( "No se pudo crear el directorio", '/admin/fotos/index' );
				}
			}
			else
			{
				$this->flash( "El directorio de la galeria no es escribible", '/admin/fotos/index' );
			}
		}
	}

	function hacerFotoFecha( $id_foto, $id_fecha ) {
		// Busco los partidos de la fecha
		$partidos = $this->Foto->Partido->find( 'list', array( 'conditions' => array( 'Partido.fecha_id' => $id_fecha ) ) );
		$this->Foto->updateAll( array( 'Foto.foto_fecha' => 0 ), array( 'Foto.partido_id' => $partidos ) );
		$this->Foto->id = $id_foto;
		$this->Foto->saveField( 'foto_fecha', $id_fecha );
	}

	function hacerFotoPartido( $id_foto, $id_partido ) {
		$this->Foto->updateAll( array( 'Foto.foto_partido' => 0 ), array( 'Foto.partido_id' => $id_partido ) );
		$this->Foto->id = $id_foto;
		$this->Foto->saveField( 'foto_fecha', $id_partido );
	}

	function hacerFotoTorneo( $id_foto, $id_torneo ) {
		$fechas = $this->Foto->Partido->Fecha->find( 'list', array( 'conditions', array( 'id_torneo' => $id_torneo ) ) );
		$partidos = $this->Foto->Partido->find( 'list', array( 'conditions' => array( 'Partido.fecha_id' => $fechas ) ) );
		$this->Foto->updateAll( array( 'Foto.foto_torneo' => 0 ), array( 'Foto.partido_id' => $fechas ) );
		$this->Foto->id = $id_foto;
		$this->Foto->saveField( 'foto_torneo', $id_torneo );
	}

	function admin_eliminar( $id_foto = null, $que = null, $id = null ) {
		// Elimino el archivo
		$dato = $this->Foto->find( 'first', array( 'conditions' => array( 'id_foto' => $id_foto ), 'fields' => 'archivo' ) );
		$this->Foto->del( $id_foto );
		if( unlink( $dato['Foto']['archivo'] ) )
		{
			$this->flash( "Archivo eliminado correctamente", '/admin/fotos/index/'.$que.'/'.$id );
		}
		else
		{
			$this->flash( 'Error al eliminar el archivo!', '/admin/fotos/index/'.$que.'/'.$id );
		}
	}

	function admin_publicar( $publicar, $id_foto, $que, $id ) {
		$this->Foto->id = $id_foto;
		$this->Foto->saveField( 'publicado', $publicar );
		$this->flash( 'Foto cambiada', '/admin/fotos/index/'.$que.'/'.$id );
	}

}
?>