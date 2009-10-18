<?php if( !isset( $zonas ) ) { ?>
 <span>No existen fechas definidas dentro de este torneo.</span>
<?php } ?>
<h1>Resultados para la <?php echo $fecha['Fecha']['name']; ?></h1><hr>
<div id="container">
   <ul class="tabs-nav">
    <?php
	foreach( $zonas as $zona ) { ?>
      <li class=""><a href="#tab-<?php echo $zona['Zona']['id_zona']; ?>"><span><?php echo $zona['Zona']['nombre_zona']; ?></span></a></li>
    <?php } ?>
   </ul>

   <?php
     foreach( $zonas as $zona ) { ?>
	<div id="tab-<?php echo $zona['Zona']['id_zona']; ?>" class="tabs-container">
         <?php echo $this->requestAction( '/fechas/fecha_jugada/'.$id_torneo.'/'.$zona['Zona']['id_zona'] );  ?>
      </div>
    <?php } ?>
</div>