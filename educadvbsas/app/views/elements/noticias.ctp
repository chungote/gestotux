<?php
 // Funcion que muestra las primeras noticias
$noticias = $this->requestAction( array( 'controller' => 'noticias', 'action' => 'ultimas'  ) );
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
			<a href="index.php?accion=noticias&amp;not=<?php echo $noticia['id']; ?>" class="parrafoIzquierda">
				<?php echo $noticia['titulo']; ?>
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