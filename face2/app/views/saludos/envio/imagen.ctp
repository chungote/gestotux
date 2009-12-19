<script>
 <!--
  function Each(array, block) {
    for (var i=0,l=array.length;i<l;i++){
      block(array[i]);
    }
  };

  function getBody() {
     return document.getElementById("body");
  }

  Each( getBody().getElementsByTagName("h1"), function(h1) {
    var spans = h1.getElementsByTagName("span");
      Each(spans, function(span){
         span.addEventListener('click', function(e){
             Each(spans, function(span){
               document.getElementById(span.getId().replace(/_tab/,'_block')).setStyle('display', 'none');
               span.setClassName("");
             });
         document.getElementById(span.getId().replace(/_tab/,'_block')).setStyle('display', 'block');
         span.setClassName("current");
      });
    });
  });

function cargarItem( i, j, row, id_imagen, ultimo ) {
 var cell = document.createElement('td');
 var nombre = "cell" + (i).toString() + (j).toString();
 //cell.setTextValue( nombre );
 cell.setId( nombre );
 //cell.setClassName( 'UIContentBox gray_box pas' );
 cell.setStyle( { border:'1px solid gray' , backgroundColor:'#ECEFF5', padding:'5px' } );
 //cell.setStyle('border', '1px solid black');
 var ajax2 = new Ajax();
 ajax2.responseType = Ajax.FBML;
 if( ultimo == 1 ) {
	ajax2.ondone = function( data ) {
		document.getElementById( nombre ).setInnerFBML( data );
	}
 } else {
	ajax2.ondone = function( data ) {
		document.getElementById( nombre ).setInnerFBML( data );
	}
	
	ocultar_cargando();
 }
 ajax2.onerror = function() { cell.setTextValue("No se puede mostrar la imagen"); }
 ajax2.post( '<?php echo $html->url( '/', true  ); ?>imagenes/miniatura/'+id_imagen );
 cell.addEventListener( 'click', function(e) {
		var id_imagen_form = document.getElementById( "imagen_form" );
		if( id_imagen_form.getValue() != -1 ) {
			document.getElementById( id_imagen_form.getValue() ).getParentNode().setStyle( 'border', '0px solid black' );
		} else if( id_imagen_form.getValue() == id_imagen ) {
			document.getElementById( id_imagen_form.getValue() ).getParentNode().setStyle( 'border', '0px solid black' );
			id_imagen_form.setValue( -1 );
		}
		id_imagen_form.setValue( id_imagen );
		document.getElementById( id_imagen ).getParentNode().setStyle('border', '4px solid #3B5998' );
	} );
 row.appendChild(cell);
}


function hacer_tabla_imagenes(text) {
  // Elimino la tabla anterior
 var ns = text.getNextSibling();
 if (ns.getTagName() == 'TABLE') {
     ns.getParentNode().removeChild(ns);
 }
 if( text == '' ) { return; }
 var table = document.createElement('table');
 table.setId( 'tabla' );
 var tbody = document.createElement('tbody');
 table.appendChild(tbody);
 var rows = text.getValue().split('\n');
 for (var i = 0; i < rows.length; i++) {
    var cols = rows[i].split('|');
    var row = document.createElement('tr');
    for (var j = 0; j < cols.length; j++) {
	if( i == rows.length && j == cols.length ) {
		cargarItem( i, j, row, cols[j], 1 );
      } else {
		cargarItem( i, j, row, cols[j], 0 );
	}
    }
    tbody.appendChild(row);
 }
 text.getParentNode().insertBefore(table, text.getNextSibling());
 table.setStyle( 'display', 'block' );
}

function mostrar_cargando(padre) {
 var cargador = document.createElement( 'span' );
 cargador.setId( 'caric' );
 cargador.setInnerXHTML('<center><img src="<?php echo $html->url('/img/cargando.gif', true  ); ?>" /></center>');
 padre.appendChild(cargador);
}

function ocultar_cargando() {
 document.getElementById('caric').setStyle('display','none' );
}

function mostrar_tabla() {
 document.getElementById( 'tabla' ).setStyle( 'display', 'block' );
}

function mostrar_error( obj ) {
  dialog = new Dialog(Dialog.DIALOG_CONTEXTUAL).setContext(obj).showMessage('Epa!', 'Hubo un error de comunicacion.... Intente recargar la pagina');
}

function hacer_siguiente( celda, limite, primero ) {
	//celda.setInnerXHTML( '<a href=\"pagsig( '+limite+','+primero+');\">Siguiente >></a>' );
	celda.setTextValue( 'Siguiente >>' );
}


function mostrarTablaImagenes() {
  mostrar_cargando(document.getElementById('imagenes_block'));
  // Busco los indices de las imagenes x ajax :)
  var ajax = new Ajax();
  ajax.responseType = Ajax.RAW;
  ajax.ondone = function( data ) {
	// cuando se ejecuta el ajax, pongo las fotos
	var obj = document.getElementById('fotos');
	obj.setTextValue(data);
	hacer_tabla_imagenes(obj);
  }
  ajax.onerror = function() {
    mostrar_error( document.getElementById('imagenes_block') );
    document.getElementById('imagenes_block').removeChild( document.getElementById('caric') );
  }
  var params={"limite":99,"primero":0};
  ajax.post( '<?php echo $html->url('/imagenes/galeriaimagenes', true  ); ?>', params );
  // Busco la navegacion
  /*var navajax = new Ajax();
  navajax.responseType = Ajax.RAW;
  navajax.ondone = function( data ) {
		// Analizo lo que me llega
		document.getElementById('sig_imagen').setInnerXHTML( data );
		var cant = data.split('|');
		if( cant > 0 ) {
			var obj = document.getElementById('sig_imagen');
			hacer_siguiente( obj, 9, 0 );
		}
  }
  navajax.onerror = function () {
	mostrar_error( document.getElementById( 'imagenes_block' ) );
  }
  var params={"limite":9,"primero":0,"tipo":'imagen',"avance":'s'};
  ajax.post( '<?php echo $html->url('/imagenes/galeriapaginacion', true  ); ?>', params );*/
  // Busco la navegacion
  /*var navajax2 = new Ajax();
  navajax2.responseType = Ajax.RAW;
  navajax2.ondone = function( data ) {
		// Analizo lo que me llega
		var cant = data.split('|');
		if( cant > 0 ) {
			var obj = document.getElementById('ant_imagen');
			hacer_anterior( obj, 9, 0 );
		}
  }
  var params={"limite":9,"primero":0,"tipo":'imagen',"avance":'a'};
  navajax2.post( '<?php echo $html->url('/imagenes/galeriapaginacion', true  ); ?>', params ); */

}


/*function mostrarTabFlash() {
  var pest = document.getElementById('animada_block' );
  var cont = document.getElementById( 'animada' );
  mostrar_cargando( pest );
  // Busco los indices de las imagenes x ajax :)
  var ajax = new Ajax();
  ajax.responseType = Ajax.RAW;
  ajax.ondone = function( data ) {
	// cuando se ejecuta el ajax, pongo las fotos
	cont.setTextValue(data);
	hacer_tabla_imagenes( cont );
  }
  ajax.onerror = function() {
    mostrar_error( pest );
    pest.removeChild( document.getElementById('caric') );
  }
  var params={"limite":9,"primero":0};
  ajax.post( 'http://tranfuga.no-ip.org/face2/imagenes/galeriaflash/9/0', params );
}*/

function sinimagen() {
	document.getElementById( 'formimagen' ).submit(); 
}

mostrarTablaImagenes();
//-->
</script>

<fb:explanation>
 <fb:message>Elige una imagen</fb:message>
  Elige una de las imagenes predefinidas haciendo click sobre ellas. La elegida se marcara con borde punteado Azul. Si no deseas elegir ninguna imagen, has click en  <b>Elegir amigos</b> para elegir a quien enviarlo.
</fb:explanation>

<style>
h1{
  height: 27px;
  margin: 0;
  position: relative;
  top: 1px;
}

h1 span.current{
  display: inline;
  background: white;
  border-bottom: 1px solid white;
}

h1 span{
  cursor: pointer;
   border: 1px dotted #777;
   padding: 5px;
   display: block;
   float: left;
   height: 15px;
   margin-right: 5px;
}

.block {
  border: 1px dotted #777;
  background: white;
  font-size: 20px;
  padding: 5px;
  margin: 0;
}
</style>
<form action="http://apps.facebook.com/felizsabado/saludos/amigos" method="POST" id="formimagen">
<input type="hidden" name="titulo" value="<?php echo $titulo; ?>" />
<input type="hidden" name="texto" value="<?php echo $texto; ?>" />
<input type="hidden" name="imagen_id" value="-1" id="imagen_form" />
<div id="body">
  <h1>
    <span class="current" id="imagenes_tab">Imagen</span>
    <!--<span id="animada_tab" onclick="mostrarTabFlash()">Animada</span>-->
  </h1>
  <div id="imagenes_block" class="block">
   <input type="button" value="No usar imagen" onclick="sinimagen()" />
   <!--<table width="100%" cellspacing="0" border="1" cellpadding="0">
    <tr>
     <td align="left" id="ant_imagen">&nbsp;</td>
     <td width="80%">&nbsp;</td>
     <td align="right" id="sig_imagen">&nbsp;</td>
    </tr>
   </table>-->
   <textarea id="fotos" style="display: none;"></textarea>

  </div>
<!--  <div id="animada_block" class="block" style="display: none">
    <textarea id="flash" style="display: none"></textarea>
  </div> -->
</div>
 <fb:submit>Elegir Amigos</fb:submit>
 <input type="button" value="cancelar" onclick="volver();"/>
</form>

