<center><?php $this->pageTitle = 'Goleadores'; echo $html->image( 'titulo_goleadores.png' ); ?></center>
<h1>Lista de goleadores para el <?php echo $nombre_torneo; ?></h1><hr>

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
         <?php echo $this->requestAction( '/torneos/goleadoresZona/'.$id_torneo.'/'.$zona['Zona']['id_zona'] );  ?>
      </div>
    <?php } ?>
</div>