<!-- contenido del menu -->
<table cellpadding="0" align="center">
 <tbody>
<?php
$ids = $this->requestAction( '/publicidades/random' );
foreach( $ids as $id )
{
 /*$imagen = $this->requestAction( '/publicidades/publicita/'.$id );
 echo $imagen;*/
 echo "<tr><td style=\"margin-bottom: 5px;\">" .
 $this->requestAction( '/publicidades/publicita/'.$id ) .
 "</td></tr>";
}
?>
 </tbody>
</table>