<?php 

class bordesHelper extends Helper {
	var $helpers = array (
		'html'
	);

	var $initialized = true;

	function init() {}

	function hacerborde( $titulo = null, $contenido = null )
	{
		 $img1 = $this->html->image('titulo_consulta_borde_izq.jpg' );
	 $return  = "<table cellpadding=\"0\" cellspacing=\"0\" width=\"100%\" border=\"0\">\n"
		     ." <tbody>\n"
		     ."  <TR>\n"
                 ."   <td height=\"21\" width=\"17\">".$img1."</TD>\n"
                 ."   <td colspan=\"2\" width=\"94%\" style=\"background-color : #eb3d00; color: white; text-align: center\"><span style=\"font-size: medium;\">".$titulo."</span></td>\n"
                 ."   <td style=\"background-image : url('./img/titulo_consulta_borde.jpg'); background-position : right; background-repeat : no-repeat;\">&nbsp;</td>\n"
                 ."  </TR>\n"
                 ."  <tr>\n"
                 ."    <td colspan=\"4\" style=\"border-left-color : #DA251D; border-left-style : solid; border-left-width : 2px; border-right-color : #DA251D; border-right-style : solid; border-right-width : 2px; padding-left : 7px; padding-right : 7px; margin: 0px;\">\n"
                 . $contenido . "\n"
                 ."    </td>\n"
                 ."   </tr>\n"
                 ."   <tr>\n"
                 ."    <td width=\"20\" valign=\"bottom\">".$this->html->image( 'bordeinfizq.png' ) . "</td>\n"
                 ."    <td colspan=\"2\" style=\"border-bottom-color : #eb3d00; border-bottom-style : solid; border-bottom-width : 2px;\">&nbsp;</td>\n"
                 ."    <td width=\"20\" valign=\"bottom\">".$this->html->image( 'bordeinfder.png' ) ."</td>\n"
                 ."  </tr>\n"
                 ." </tbody>\n"
                 ."</table>\n";
	 return $return;
      }
}
?>