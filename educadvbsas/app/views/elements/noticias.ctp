<?php
 // Funcion que muestra las primeras noticias
$noticias = $this->requestAction( array( 'controller' => 'noticias', 'action' => 'ultimas'  ) );
//pr( $noticias );
if (count($noticias) > 0)
{
?>
<tr>
 <td class="tituloSeccionIzquierda">Noticias</td>
</tr>
<?php
	foreach( $noticias as $noticia )
	{
	 ?>
	<tr><td class="espacioIntermedio">&nbsp;</td></tr>
	<tr>
		<td class='parrafoIzquierda'>
			<?php echo $html->link( $noticia['Noticias']['titulo'], array( 'controller' => 'noticias', 'action' => 'leer', 'id' =>  $noticia['Noticias']['id_noticia'] ), array( 'class' => "parrafoIzquierda" ) ); ?>
			</a>
			<br />
		</td>
	</tr>
	<?php
	}
}
?>
	<tr>
		<td class="pieSeccionIzquierda">&nbsp;</td>
	</tr>