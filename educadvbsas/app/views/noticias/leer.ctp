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
												$html->image( 'flecha_izquierda_volver.png', array( 'alt' => "ver más" ) ) . " Volver",
												'', array( 'class' => 'verMasInfo', 'escape' => false ) ); ?>
										</td>
									</tr>
									</tbody>
								</table>
							</td>
							<td>&nbsp;&nbsp;&nbsp;&nbsp;</td>
								<!-- imagenes laterales -->
				<?php if( isset( $noticia['Imagenes'] ) ) { ?>
							<td class="arriba">
								<table>
									<tbody>
									<tr>
										<td><img border="0" align="left" width="73" height="97" src="./uploaded_images/noticias/1.png"></td>
									</tr>
									<tr>
										<td><img border="0" align="left" width="73" height="97" src="./uploaded_images/noticias/2.png"></td>
									</tr>
									<tr>
										<td><img border="0" align="left" width="73" height="97" src="./uploaded_images/noticias/3.png"></td>
									</tr>
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