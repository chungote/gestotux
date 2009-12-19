<fb:title><?php echo $this->pageTitle; ?></fb:title>
<fb:dashboard>
    <fb:action href="http://apps.facebook.com/felizsabado/saludos/crear">Enviar Saludos</fb:action>
    <fb:action href="http://apps.facebook.com/felizsabado/saludos/recibido">Ver saludos recibidos</fb:action>
   <!-- <fb:action href="http://apps.facebook.com/felizsabado/saludos/crear">Crear saludo personalizado</fb:action> -->
    <fb:create-button href="http://apps.facebook.com/felizsabado/saludos/crear">Nuevo saludo</fb:create-button>
    <fb:help href="http://apps.facebook.com/help.php">Ayuda</fb:help>
</fb:dashboard>
<div class="container"><?php echo $content_for_layout;?></div>