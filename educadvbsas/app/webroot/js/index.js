window.onload = function() {
	//init();
	crearLinks();
}

function crearLinks() {
	// Recorro todos los H3 dentro de la Sidebar1
	var opciones1 = $$("#sidebar1 h3");
	opciones1.each(function(opcion) {
						   // Genero la accion del clic por cada uno
						   opcion.onclick = function() {
							   // utilizo el id de cada h3 como nombre de secci�n
							   mostrarSeccion(opcion.id);
						   }
				})
}

function mostrarSeccion(nombre) {
	$Ajax(nombre+".html", {
		  cache: true,
		  onfinish: function(html) {
			  // Comienzo efecto de salida - Ejemplo 1
			  new Effect.Fade("mainContent", {
							  duration: 0.5,
							  afterFinish: function() {
								  // Comienzo efecto de aparici�n de contenido
								  $("mainContent").innerHTML = html;
								  new Effect.Appear("mainContent");
							  }
			});
			  // Segunda opci�n de efecto
			  //$("mainContent").innerHTML = html;
			  // Comienzo efecto de Highlight
			  //new Effect.Highlight("mainContent", {duration: 1});
		  },
		  avisoCargando: "divCargando"
	}); 
}
