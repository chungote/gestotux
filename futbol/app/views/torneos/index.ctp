<?php $this->pageTitle = "..:: ".$torneo['Torneo']['name']." - La Finta Futbol ::.."; ?>
<h1><?php echo $torneo['Torneo']['name'];?></h1>
<?php echo $this->requestAction( '/fechas/fecha_jugadas/'.$torneo['Torneo']['id_torneo'] ); ?> <br />
<?php echo $this->requestAction( '/fechas/proxima_fechas/'.$torneo['Torneo']['id_torneo'].'/1' ); ?>
<br />
<center><?php echo $html->image( 'titulo_datos_torneo.png' ); ?></center>
<table width="100%" cellspacing="0" cellpadding="6" align="center">
  <tr>
   <td><b>Fecha de Inicio:</b> <?php echo date( 'd/m/Y', strtotime( $torneo['Torneo']['fecha_inicio'] ) ); ?></td>
   <td><b>Fecha de Fin:</b> <?php echo date( 'd/m/Y', strtotime( $torneo['Torneo']['fecha_fin'] ) ); ?></td>
  </tr>
  <tr>
   <td><?php echo $html->image( 'boton_reglamentos.png', array( 'alt' => "Reglamentos y Premios", 'url' => "/torneos/reglamento/".$torneo['Torneo']['id_torneo'] ) ); ?></td>
   <td><?php echo $html->image( 'boton_posiones_actual.png', array( 'alt' => "Ver Tabla de Posiciones", 'url' => "/fechas/tablapuntos/".$torneo['Torneo']['id_torneo'] ) ); ?></td>
  </tr>
  <tr>
   <td><?php echo $html->image( 'boton_sanciones.png', array( 'alt' => "Ver Sancionados por fechas", 'url' => "/sancionados/tabla/" .$torneo['Torneo']['id_torneo'] ) ); ?></td>
   <td><?php echo $html->image( 'boton_fotos_torneo.png', array( 'alt' => "Ver fotos del torneo", 'url' => "/fotos/galeria/torneo/" .$torneo['Torneo']['id_torneo'] ) ); ?></td>
  </tr>
  <tr>
   <td><?php echo $html->image( 'boton_amonestados.png', array( 'alt' => "Ver amonestados", 'url' => "/amonestados/torneo/" .$torneo['Torneo']['id_torneo'] ) ); ?></td>
   <td><?php echo $html->image( 'boton_goleadores.png', array( 'alt' => "Ver goleadores por zona", 'url' => "/torneos/goleadores/" .$torneo['Torneo']['id_torneo'] ) ); ?></td>
  </tr>
</table>
<br /><br />
<div align="center"><?php echo $html->image( 'boton_anteriores.png', array( 'alt' => "Ver torneos anteriores", 'url' => '/torneos/anteriores' ) ); ?></div>