<h1>AJA!</h1>

<fb:explanation>
 <fb:message>&iquest;Porque aparece esto?</fb:message>
 Esto aparece porque el desarrollador del sistema esta trabajo en el codigo y no quiere que veas lo que esta haciendo.
 <br /> Si esto no te gusta... no podes hacer nada al respecto....
</fb:explanation>

<fb:error>
  <fb:message><?php __('Missing View'); ?></fb:message>
  <?php echo sprintf(__('The view for %1$s%2$s was not found.', true), "<em>" . $controller . "Controller::</em>", "<em>". $action . "()</em>");?>
  <?php echo sprintf(__('Confirm you have created the file: %s', true), $file);?>
</fb:error>