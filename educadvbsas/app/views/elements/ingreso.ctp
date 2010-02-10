<?php
// Ingreso a la intranet ( por ahora adminitración )
?>
<tr>
 <td class="tituloSeccionIzquierda">Ingreso</td>
</tr>
<tr>
	<td class="espacioIntermedio">&nbsp;</td>
</tr>
<tr>
	<td class='parrafoIzquierda'>
	<?php echo $form->create( 'Personal', array( 'url' => array( 'controller' => 'personal', 'action' =>'login' ) ) ); ?>
	<table width="50%" cellspacing="0" border="0" cellpadding="0" align="center">
		<tbody>
			<tr>
				<td align="center"><b>Formulario de Ingreso</b></td>
			</tr>
			<tr>
				<td align="left" valign="middle"><?php echo $form->input( 'usuario', array( 'size' => 10 ) ); ?></td>
			</tr>
			<tr>
				<td align="left" valign="middle"><?php echo $form->input( 'constraseña', array( 'size' => 10 ) ); ?></td>
			</tr>
			<tr>
				<td><?php echo $form->end( 'Ingresar' ); ?></td>
			</tr>
		</tbody>
	</table>
	</td>
</tr>
<tr>
	<td class="pieSeccionIzquierda">&nbsp;</td>
</tr>