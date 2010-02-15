<!-- Muestra el resumen de todas las noticias principales hasta cierto punto -->
<table cellspacing="0" cellpadding="7" border="0" align="center" width="100%">
  <tbody>
	<tr><td align="left" height="30" class="espacioInicial" colspan="2">&nbsp;</td></tr>
	<tr>
		<td class="tdTitulo" colspan="2">
			<table cellspacing="0" cellpadding="0">
				<tbody>
					<tr>
						<td class="fondoTitulosAntes">&nbsp;</td>
						<td class="fondoTitulosDurante">Noticias</td>
						<td class="fondoTitulosDespues">&nbsp;</td>
					</tr>
				</tbody>
			</table>
		</td>
	</tr>
<?php
foreach( $noticias as $noticia ) { ?>
	<tr>
		<td colspan="2">
			<p class="titulo">
				<?php echo $html->link( $noticia['Noticias']['titulo'], '/noticias/leer/'.$noticia['Noticias']['id_noticia'] ); ?>
			</p>
			<p class="subtitulo"><?php echo $noticia['Noticias']['subtitulo']; ?></p>
		</td>
	</tr>
	<tr>
		<td colspan="2">
			<p><?php echo $noticia['Noticias']['resumen']; ?></p>
		</td>
	</tr>
	<tr>
		<td></td>
		<td class="verMasInfo">
				<?php echo $html->link( 
						$html->image( 'flecha_derecha_ver_mas.png', array( 'alt' => "Leer más", 'border' => 0 ) ) . " Leer mas",
							'', array( 'class' => 'verMasInfo', 'escape' => false ) ); ?>
		</td>
	</tr>
	<tr>
		<td colspan="2">
			&nbsp;
		</td>
	</tr>
<?php } ?>
  </tbody>
</table>