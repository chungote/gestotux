<?php $this->pageTitle = "..:: Aministrador de Usuario ::.. "; ?>
<h1>Administracion de usuario</h1><hr>
<br />
<div>
 Datos del usuario:<br />
 <b>Nombre:</b><?php echo $usuario['User']['username']; ?><br />
</div>
<br /><?php echo $html->link( "Cambiar Contrasena", '/admin/users/cambiar' ); ?><br />