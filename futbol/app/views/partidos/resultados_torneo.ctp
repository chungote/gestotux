<center><?php echo $html->image( 'titulo_resultados.png' ); ?></center>
<h2>Fecha: <?php echo $fecha['Fecha']['name']; ?></h2>
<div id="container">
   <ul class="tabs-nav">
    <?php
	foreach( $zonas as $zona ) { ?>
      <li><a href="#tab-<?php echo $zona['Zona']['id_zona']; ?>"><span><?php echo $zona['Zona']['nombre_zona']; ?></span></a></li>
    <?php } ?>
   </ul>
   <center>
    <?php
     foreach( $zonas as $zona ) { ?>
	<div id="tab-<?php echo $zona['Zona']['id_zona']; ?>"  class="tabs-container">
         <?php echo $this->requestAction( '/partidos/resultadosFecha/'.$fecha['Fecha']['id_fecha'].'/'.$zona['Zona']['id_zona'] );  ?>
      </div>
    <?php } ?>
</div>
<div>
	     <?php
		if( is_array( $navegacion['prev'] ) )
		{
			echo $html->link( '<<' . $navegacion['prev']['Fecha']['name'], '/partidos/resultados/fecha/'.$navegacion['prev']['Fecha']['id_fecha'] );
		}
		if( is_array( $navegacion['next'] ) )
		{
			echo $html->link( $navegacion['next']['Fecha']['name'] . '>>', '/partidos/resultados/fecha/'.$navegacion['next']['Fecha']['id_fecha'] );
		} ?>
	   </div>
</center>