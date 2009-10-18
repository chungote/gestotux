<center><?php echo $html->image( 'titulo_proximafecha.png' ); ?></center>
Partidos Planificados para <?php echo $fecha['Fecha']['name']; ?>
<div id="container">
   <ul class="tabs-nav">
    <?php
	foreach( $zonas as $zona ) { ?>
      <li><a href="#tab-<?php echo $zona['Zona']['id_zona']; ?>"><span><?php echo $zona['Zona']['nombre_zona']; ?></span></a></li>
    <?php } ?>
   </ul>

   <?php
     foreach( $zonas as $zona ) { ?>
	<div id="tab-<?php echo $zona['Zona']['id_zona']; ?>"  class="tabs-container">
         <?php echo $this->requestAction( '/fechas/proxima_fecha/'.$fecha['Fecha']['id_fecha'].'/'.$zona['Zona']['id_zona'] );  ?>
      </div>
    <?php } ?>
</div>