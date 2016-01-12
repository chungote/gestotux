# Servicio de E-mail #

## Introducción ##

El servicio de email dentro del programa esta pensado para poder ser utilizado opcionalmente como un plugin, pero al mismo tiempo estar integrado dentro de todo el programa en si estando disponible mediante la librería general.

## Configuración ##

El plugin mismo de email posee un formulario de configuracion que permite definir uno o varios servidores SMTP para el uso. De todos estos servidores, es posible definir uno como predeterminado, el cual será utilizado para enviar los emails.

## Uso dentro del codigo ##

La utilizacion de este sistema se hace muy facilmente.
La librería general del programa posee un objeto **EEmail** del cual debemos obtener una instancia para poder trabajar con el y enviar los emails desde alli.
Para obtener una instancia utilizamos el método:
`EEmail::instancia()`
El cual nos devolverá una instancia nueva si el objeto no ha sido declarado o la instancia general del programa si ya se ha utilizado.
Para poder enviar un email, obtenemos un objeto del tipo `Mail` mediante el metodo `email()`.
Cuando hayamos terminado de crear todos los datos del email, procedemos a mandarlo mediante la función `enviar( Mail* email )`.

En resumen su uso sería de la siguiente manera:
```
EEmail *e = EEmail::instancia();
Mail *mail = e->email();
.....
.....
e->enviar( mail );
```