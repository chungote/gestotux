<h1><strong>UUUUUPS!</strong></h1>

<fb:explanation>
 <fb:message>&iquest;Porque aparece esto?</fb:message>
 Esto aparece porque el desarrollador del sistema esta trabajo en el codigo y se olvido de hacer una parte.
 <br /> Si esto no te gusta... no podes hacer nada al respecto....
</fb:explanation>

<fb:error>
  <fb:message>Falta una accion...</fb:message>
   <?php echo sprintf(__('The action %1$s is not defined in controller %2$s', true), "<em>" . $action . "</em>", "<em>" . $controller . "</em>");?>
   <?php echo sprintf(__('Create %1$s%2$s in file: %3$s.', true), "<em>" . $controller . "::</em>", "<em>" . $action . "()</em>", APP_DIR . DS . "controllers" . DS . Inflector::underscore($controller) . ".php");?>
	<pre>
	&lt;?php
	class <?php echo $controller;?> extends AppController {

		var $name = '<?php echo $controllerName;?>';

	<strong>
		function <?php echo $action;?>() {

		}
	</strong>
	}
	?&gt;
	</pre>
</fb:error>