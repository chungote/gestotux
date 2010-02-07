function inicializar() {
$('colegios').observe( 'mouseover','mostrarMenuColegios' ); 
$('colegios').observe( 'mouseout', 'ocultarMenuColegios' );
}

function ocultarMenuColegios( event ) {
}

function mostrarMenuColegios( event ) {
  event.findElement( 'a' ).setStyle( { backgroundColor: 'yellow', textColor: 'black' } );
  }