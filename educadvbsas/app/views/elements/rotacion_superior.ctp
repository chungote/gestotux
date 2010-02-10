<div id="fotos">
	<script type="text/javascript">
		var fadeimages=new Array()
		// Este parche evita que se cuelge lod e las imagenes cuando vamos a otra sección que no sea la inical
		fadeimages[0]=["<?php echo $html->url( '/img/eama.jpg' ); ?>", "http://www.eama.edu.ar", "_new"] 
		fadeimages[1]=["<?php echo $html->url( '/img/iaf3.jpg' ); ?>", "http://www.iaf1.edu.ar", "_new"] 
		fadeimages[2]=["<?php echo $html->url( '/img/iada1.jpg' ); ?>", "http://www.iada.edu.ar", "_new"] 
		fadeimages[3]=["<?php echo $html->url( '/img/ialp2.jpg' ); ?>", "http://www.ialp.edu.ar", "_new"] 
		fadeimages[4]=["<?php echo $html->url( '/img/iamo1.jpg' ); ?>", "http://www.iamo.edu.ar", "_new"] 
		fadeimages[5]=["<?php echo $html->url( '/img/iab.jpg' ); ?>", "", ""] 
		var fadebgcolor="white"
		
		new fadeshow(fadeimages, 736, 240, 0, 3000, 1, "R")
	</script>
</div>