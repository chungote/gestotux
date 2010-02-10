<?php
//pr( $noticia );
?>
<table cellspacing="0" cellpadding="7" border="0" align="center" width="93%">
  <tbody>
	<tr><td align="left" height="30" class="espacioInicial">&nbsp;</td></tr>
	<tr>
		<td class="tdTitulo" colspan="3">
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
	<tr>
		<td>
			<p class="titulo"><?php echo $noticia['Noticias']['titulo']; ?></p>
			<p class="subtitulo"><?php echo $noticia['Noticias']['subtitulo']; ?></p>
		</td>
	</tr>
	<tr>
		<td>
			<table cellspacing="3" bordercolor="#9999cc" align="center" width="90%">
				<tbody><tr>
					<td valign="top">
					<table>
						<tbody><tr>
							<td width="100%" class="colegiosDescripcion arriba">
								<table>
									<tbody><tr>
										<td class="descripcionQuienes" colspan="2"><p class="texto"><?php echo $noticia['Noticias']['textocompleto']; ?></p></td>
									</tr>
									<tr>
										<td class="descripcionQuienes" colspan="2">&nbsp;</td>
									</tr>
									<tr>
										<td class="verMasInfo" colspan="2">
											<?php echo $html->link( 
												$html->image( 'flecha_izquierda_volver.png', array( 'alt' => "ver más", 'border' => 0 ) ) . " Volver",
												'', array( 'class' => 'verMasInfo', 'escape' => false ) ); ?>
										</td>
									</tr>
									</tbody>
								</table>
							</td>
							<td>&nbsp;&nbsp;&nbsp;&nbsp;</td>
								<!-- imagenes laterales -->
				<?php if( count( $noticia['NoticiasFotos'] ) ) { ?>
							<td class="arriba" style="border-style: dotted; border-color: gray; border-width: 1px;">
								<table>
									<tbody>
									<?php foreach( $noticia['NoticiasFotos'] as $foto ) {
										if( $foto['publicado'] == true ) { ?>
									<tr>
										<td>
										<?php echo $html->link( 
												$html->image( $foto['miniatura'],
														 array( 'border' => 0,
															'align' => 'left',
															'width' => 73,
															'height' => 97,
															'alt' => $foto['titulo'] ) ),
												'/img'.DS.$foto['ruta'], array( 'escape' => false,
														      'title' => $foto['titulo'],
														      'rel' => 'lightbox['.$foto['noticia_id'].']' ) ); ?></td>
									</tr>
									<?php } } ?>
									</tbody>
								</table>
							</td>
				<?php } // Fin if imagenes ?>
						</tr>
						</tbody>
					</table>
					</td>
				</tr>
				</tbody>
			</table>
		</td>
	</tr>
  </tbody>
</table>