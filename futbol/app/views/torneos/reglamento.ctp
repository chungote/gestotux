<?php $this->pageTitle = "..:: Reglamento de ".$torneo['name']." - La Finta Futbol ::.."; ?>
<center><?php echo $html->image( 'titulo_reglamento.png' ); ?></center>
<?php echo $torneo['reglamento']; ?>
<?php echo $html->link( "Volver al torneo", '/torneos' ); ?>