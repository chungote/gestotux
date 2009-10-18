<?php $this->pageTitle = "..:: Galeria de Fotos - La Finta Futbol ::.."; ?>
<center><?php echo $html->image( 'titulo_fotos.png' ); ?></center>
<table width="100%" cellspacing="0" cellpadding="0" align="center" style="border-bottom-color : #59b034; border-bottom-style : solid; border-bottom-width : 2px; border-collapse : separate; border-left-color : #59b034; border-left-style : solid; border-left-width : 2px; border-right-color : #59b034; border-right-style : solid; border-right-width : 2px; border-spacing : 1px 0px; border-top-color : #59b034; border-top-style : solid; border-top-width : 2px;">
  <tbody>
    <tr>
      <td bgcolor="lightGray">Elija el Torneo del cual desea ver las fotos</td>
    </tr>
<?php
 $class = 0;
foreach( $torneos as $torneo )
{
  if( $class == "1" ) { $class = "2"; } else { $class = "1"; }
 echo $html->tableCells( array(
				array( array( $html->link( $torneo['Torneo']['name'], '/fotos/galeria/torneo/'.$torneo['Torneo']['id_torneo'] ), array( 'class' => "textosombra".$class )  )
					)
				) );
}
?>
    <tr>
      <td align="center" valign="middle" bgcolor="lightGray">Ultimas Imagenes agregadas</td>
    </tr>
    <tr style="border-bottom-color : #59b034; border-bottom-style : dashed; border-bottom-width : 1px; border-left-color : #59b034; border-left-style : dashed; border-left-width : 1px; border-right-color : #59b034; border-right-style : dashed; border-right-width : 1px; border-spacing : 3px 2px; border-top-color : #59b034; border-top-style : dashed; border-top-width : 1px;">
      <td><?php echo $this->requestAction( '/fotos/ultimas' ); ?></td>
    </tr>
  </tbody>
</table>