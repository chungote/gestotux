<center><?php echo $html->image( 'titulo_amonestados.png' ); ?></center>
<h1>Lista de amonestados para el <?php  echo $nombre_torneo; ?></h1><hr>
<p>Esta es la lista de amonestados actuales para el torneo.</p>
<b>Fecha calculada: </b><?php echo $fecha['Fecha']['name']; ?><br />
<!--<span style="font-size: x-small;"> Ejemplo: Contando desde la 2&ordm; Fecha  y tiene 1 fecha faltante vuelve a jugar en la 4&ordm; fecha</span>-->

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
         <?php echo $this->requestAction( '/amonestados/zona/'.$id_torneo.'/'.$zona['Zona']['id_zona'].'/'.$fecha['Fecha']['fecha_fin'] );  ?>
      </div>
    <?php } ?>
</div>