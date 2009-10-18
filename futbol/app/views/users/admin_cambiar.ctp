<h1>Cambiar contrase&ntilde;a</h1><hr>
<br />
<?php echo $form->create( 'User', array( 'url' => '/admin/users/cambiar' ) );
echo "Nombre de usuario:" . $data['User']['username'];
echo $form->input( 'username', array( 'type' => 'hidden', 'value' => $data['User']['username'] ) );
echo $form->input( 'group_id', array( 'type' => 'hidden', 'value' => $data['User']['grupo_id'] ) );
echo $form->input( 'pass_nueva', array( 'label' => 'Contrase&ntilde;a nueva', 'type' => 'password' ) );
echo $form->input( 'pass_nueva_2', array( 'label' => 'Confirmar Contrase&ntilde;a', 'type' => 'password' ) );
echo $form->input( 'id', array( 'type' => 'hidden', 'value' => $data['User']['id'] ) );
echo $form->end( 'Cambiar' );
?>