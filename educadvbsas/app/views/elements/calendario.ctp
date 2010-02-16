<?php
						/*$mes_hoy = date("n");
						$ano_hoy = date("Y");
$eventos = $this->requestAction( '/eventos/portada/'.$mes_hoy.'/'.$ano_hoy );*/
?>
<tr>
	<td class="tituloSeccionDerecha" width="175">Calendario</td>
</tr>
<tr>
	<td class="sinEspacio">
		<table width="175" border="0" align="center" cellpadding="0" cellspacing="0" bgcolor="#000000">
		  <tr>
			<td>
				<table width="100%" border="0" cellpadding="0" cellspacing="1">
					<tr class="topdays">
						<td height="25"><div align="center">Dom</div></td>
						<td><div align="center">Lun</div></td>
						<td><div align="center">Mar</div></td>
						<td><div align="center">Mie</div></td>
						<td><div align="center">Jue</div></td>
						<td><div align="center">Vie</div></td>
						<td><div align="center">Sab</div></td>
					</tr>
					<tr valign="top" bgcolor="#FFFFFF">
						<?php
						 // Veo con que dia empieza el mes
						$dia_hoy = date("j");
						$mes_hoy = date("n");
						$ano_hoy = date("Y");

						// Busco los eventos
						$eventos = $this->requestAction( '/eventos/portada/'.$mes_hoy.'/'.$ano_hoy );
						$dias_en_el_mes = date ( "t", mktime( 0, 0, 0, $mes_hoy, 0, $ano_hoy ) );
						$primer_dia_del_mes = date ("w", mktime( 0, 0, 0, $mes_hoy, 1, $ano_hoy ) );
						//echo "primer:".$primer_dia_del_mes;
						$ultimo_dia_del_mes = $primer_dia_del_mes + 1;
						$contador_casillas = 0;
						$dias_hasta_ahora = 0;

						// Hago los casilleros que sobran del mes anterior
						for( $i=1; $i<=$primer_dia_del_mes; $i++ ) {
							$dias_hasta_ahora++; $contador_casillas++;
							?><td width="25" height="25" class="beforedayboxes"></td><?php
						}
						// Recorro todos los dias del mes
						for( $i=1; $i<=$dias_en_el_mes; $i++ ) {
							$dias_hasta_ahora++; $contador_casillas++; $class="";
							if( $i == $dia_hoy ) {
								$class = "highlighteddayboxes";
							} else {
								if( isset( $events[$i] ) ) {
									$class = "hayEvento";
								} else {
									$class = "dayboxes";
								}
							}
							echo "<td width=\"25\" height=\"25\" class=\"$class\">\n";
							// Numero de Dia
							echo "<div align=\"right\"><span class=\"toprightnumber\">\n$i</span></div>";
							// Muestro los datos de un evento
							if( isset( $eventos[$i] ) ) {
								echo "<div align=\"left\"><span class=\"eventinbox\">\n";
								$alt = "";
								foreach( $eventos[$i] as $ev ) {
									$alt .= $ev['titulo'] . "\n";
								}
								echo $html->link( $html->image( 'evento_15x15_alpha.png', array( 'width' => 15,
																      'height' => 15,
																      'border' => 0,
																      'alt' => $alt,
																      'title' => $alt,
																      'escape' => false  ) ),
											array( 'controller' => 'eventos',
												 'action' => 'mostrarEventos',
												 'dia' => $i,
												 'mes' => $mes_hoy,
												 'ano' => $ano_hoy ),
											array( 'escape' => false ) );
								echo "</span></div>\n";
							} else { echo 'n'; }
							// Verifico cuando llego a sabado
							if( $contador_casillas == 7 ) { 
								$contador_casillas = 0;
								echo "</tr><tr valign=\"top\">\n";
							}
						}
						// Pongo los dias extras
						$casillas_extras = 7 - $contador_casillas;
						for ($i = 1; $i <= $casillas_extras; $i++) {
							echo "<td width=\"25\" height=\"25\" class=\"afterdayboxes\"></td>\n";
						}
						?>
					</tr>
				</table>
			</td>
		  </tr>
		</table>
	</td>
</tr>
<tr>
	<td class="derecha">
		<?php echo $html->link( 
			$html->image( 'flecha_derecha_ver_mas.png', array( 'alt' => "Ver más", 'border' => 0 ) ) . " Ver Eventos...",
					'', array( 'class' => 'verMasInfo', 'escape' => false ) ); ?>
	</td>
</tr>
<tr>
	<td class="pieSeccionDerecha">&nbsp;</td>
</tr>