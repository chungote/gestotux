<?php $this->pageTitle = "..:: Inscripciones - La Finta Futbol ::.."; ?>
<center><?php echo $html->image( 'titulo_inscripcion.png' ); ?></center><br />
Por favor ingresa los siguentes datos:

<?php echo $form->create( 'Inscripcion', array( 'action' => 'enviar' ) ); ?>
<table>
  <tbody>
    <tr>
      <td><b>Nombre y Apellido:</b></td>
      <td><?php  echo $form->input( 'nombre', array( 'label' => '' ) );?></td>
    </tr>
    <tr>
      <td><b>Equipo:</b></td>
      <td><?php echo $form->input( 'equipo', array( 'label' => '' )  );?></td>
    </tr>
    <tr>
      <td><b>Email:</b></td>
      <td><?php  echo $form->input( 'email', array( 'label' => '' )  );?></td>
    </tr>
    <tr>
      <td><b>Telefono Fijo:</b></td>
      <td><?php  echo $form->input( 'tel_fijo', array( 'label' => '' )  );?></td>
    </tr>
    <tr>
      <td><b>Telefono Celular:</b></td>
      <td><?php  echo $form->input( 'tel_cel', array( 'label' => '' ) );?></td>
    </tr>
    <tr>
      <td><b>Experiencia en otra liga:</b></td>
      <td><?php  echo $form->input( 'experiencia', array( 'type' => 'textarea', 'label' =>'' ) );?></td>
    </tr>
  </tbody>
</table>
<?php  echo $form->end( "Enviar" ); ?>