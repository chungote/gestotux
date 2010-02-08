<?php
$this->pageTitle = "..:: Ingreso a la administracion ::..";
// Muestro los mensajes de error de loggeo
if ($session->check('Message.auth')) $session->flash('auth');

echo $form->create( 'User', array( 'url' => array( 'controller' => 'users', 'action' =>'login' ) ) );


?>
<center>
<table width="50%" cellspacing="0" border="0" cellpadding="0" align="center">
  <tbody>
    <tr>
      <td rowspan="4"><?php echo $html->image( 'costado.png' ); ?></td>
      <td align="center"><b>Formulario de Ingreso</b></td>
    </tr>
    <tr>
      <td align="left" valign="middle"><?php echo $form->input( 'username' ); ?></td>
    </tr>
    <tr>
      <td align="left" valign="middle"><?php echo $form->input( 'password' ); ?></td>
    </tr>
    <tr>
      <td><?php echo $form->end( 'Ingresar' ); ?></td>
    </tr>
  </tbody>
</table>
</center>