<table>
 <tbody>
<?php
$ids = $this->requestAction( '/torneos/actuales' );
foreach( $ids as $torneo )
{
?>
    <tr>
      <td colspan="2"><?php echo $html->link( $torneo['Torneo']['name'], '/torneos/index/'.$torneo['Torneo']['id_torneo'], array(  'class' => 'item-menu' ) ); ?></td>
    </tr>
    <tr>
      <td width="5"></td>
      <td><?php echo $html->image( 'reglamento.png', array( 'alt' => "- reglamento", 'url' => '/pages/reglamento', 'class' => 'item-menu' ) ); ?></td>
    </tr>
    <tr>
      <td></td>
      <td><?php echo $html->image( 'resultados.png', array( 'alt' => "- resultados", 'url' => '/partidos/resultados/torneo/'. $torneo['Torneo']['id_torneo'], 'class' => 'item-menu' ) ); ?></td>
    </tr>
    <tr>
      <td></td>
      <td><?php echo $html->image( 'tabla_de_posicion.png', array( 'alt' => "- tabla de posicion", 'url' => '/fechas/tablapuntos/'.$torneo['Torneo']['id_torneo'], 'class' => 'item-menu' ) ); ?></td>
    </tr>
    <tr>
      <td></td>
      <td><?php echo $html->image( 'sancionados.png', array( 'alt' => "- sancionados", 'url' => '/sancionados/tabla/'. $torneo['Torneo']['id_torneo'], 'class' => 'item-menu' ) ); ?></td>
    </tr>
    <tr>
      <td></td>
      <td><?php echo $html->image( 'goleadores.png', array( 'alt' => "- goleadores", 'url' => '/torneos/goleadores/'. $torneo['Torneo']['id_torneo'], 'class' => 'item-menu' ) ); ?></td>
    </tr>
    <tr>
      <td></td>
      <td><?php echo $html->image( 'amonestados.png', array( 'alt' => "- amonestados", 'url' => '/amonestados/torneo/'. $torneo['Torneo']['id_torneo'], 'class' => 'item-menu' ) ); ?></td>
    </tr>
    <tr>
      <td></td>
      <td><?php echo $html->image( 'proxima_fecha.png', array( 'alt' => "- proxima fecha", 'url' => '/fechas/proxima_fechas/'. $torneo['Torneo']['id_torneo'], 'class' => 'item-menu' ) ); ?></td>
    </tr>
    <tr>
      <td></td>
      <td><?php echo $html->image( 'fotos.png', array( 'alt' => "- fotos", 'url' =>  '/fotos/galeria/torneo/'.$torneo['Torneo']['id_torneo'], 'class' => 'item-menu' ) ); ?></td>
    </tr>
<?php
} //fin item de torneo repetido
?>
    <tr>
      <td colspan="2"><?php echo $html->image( 'como_llegar.png', array( 'alt' => "Como llegar?", 'url' => /*'/torneos'*/'/pages/construccion', 'class' => 'item-menu' ) ); ?></td>
    </tr>
    <tr>
	<td></td>
      <td><?php echo $html->image( 'como_llegar1.png', array( 'alt' => "- como llegar", 'url' => /*'/torneos'*/'/pages/construccion', 'class' => 'item-menu' ) ); ?></td>
    </tr>
    <tr>
      <TD></TD>
      <td><?php echo $html->image( 'plano_complejo.png', array( 'alt' => "- plano complejo", 'url' => /*'/torneos'*/'/pages/construccion', 'class' => 'item-menu' ) ); ?></td>
    </tr>
    <tr>
     <td colspan="2"><?php echo $html->image( 'inscripcion.png', array( 'alt' => "Inscripcion", 'url' => '/inscripciones', 'class' => 'item-menu' ) ); ?></td>
    </tr>
    <tr>
     <td colspan="2">
	<?php echo $flash->renderSwf( IMAGES_URL . 'banner_chiquito_opt.swf', 100, 125, 'flash', array( 'params' => array( 'bgcolor' => '#4D4948' ) ) ); ?>
	<div id="flash"></div>
     </td>
    </tr>
 </tbody>
</table>