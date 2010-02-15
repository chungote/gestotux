<?php
$this->pageTitle = "..:: Ingreso a la administracion ::..";
// Muestro los mensajes de error de loggeo
if ($session->check('Message.auth')) $session->flash('auth');

echo $form->create( 'Personal', array( 'url' => array( 'controller' => 'personal', 'action' =>'login' ) ) );


?>
<center>
<table width="50%" cellspacing="0" border="0" cellpadding="0" align="center">
  <tbody>
    <tr>
      <td rowspan="4"><?php echo $html->image( 'costado.png' ); ?></td>
      <td align="center"><b>Formulario de Ingreso</b></td>
    </tr>
    <tr>
      <td align="left" valign="middle"><?php echo $form->input( 'usuario' ); ?></td>
    </tr>
    <tr>
      <td align="left" valign="middle"><?php echo $form->input( 'constrasena' ); ?></td>
    </tr>
    <tr>
      <td><?php echo $form->end( 'Ingresar' ); ?></td>
    </tr>
  </tbody>
</table>
</center>