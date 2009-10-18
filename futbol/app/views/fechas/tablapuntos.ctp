<?php $this->pageTitle = "..:: Tabla de posiciones - La Finta Futbol ::.."; ?>
<center><?php echo $html->image( 'titulo_tablapuntos.png' ); ?></center>
<h2>Torneo:<?php echo $fecha['Torneo']['name']; ?></h2>
<h2>Fecha: <?php echo $fecha['Fecha']['name']; ?></h2>
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
         <?php echo $this->requestAction( '/fechas/tablafecha/'.$fecha['Torneo']['id_torneo'].'/'.$zona['Zona']['id_zona'] );  ?>
      </div>
    <?php } ?>
</div>