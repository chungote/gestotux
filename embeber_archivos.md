# Embeber Archivos #

## Introduccion ##

**¿Por que quiero embeber archivos en mi plugin?**
Muy sencillo, evita que tengas que distribuir las imagenes y datos sql del programa con el ejecutable, evitando posibles perdidas de datos porque esos archivos han sido eliminados.
Aunque solo aumentan el tamaño del archivo ejecutable, o del _.dll_ o _.so_ del plugin, tenemos la certeza de que estaran ahi cuando los necesitemos.

## Como incluir archivos ##

Para eso se debe generar un archivo _.qrc_ y agregarlo al proyecto.
Para ver como esta conformado el archivo, vea el archivo _templates/qrc_.
He aqui un ejemplo:
```
<RCC>
    <qresource>
     <file>icono.png</file>
    </qresource>
    <qresource prefix="sql">
    </qresource>
</RCC>
```
Esto generar una estructura con icono.png y una carpeta vacia con nombre _sql_.

Lo vamos a agregar al proyecto con el siguiente texto dentro de nuestro archivo _.pro_

```
RESOURCES = archivo.qrc
```

Pero, para poder utilizar estos archivos debemos agregar una funcion macro de Qt en nuestro programa; si estamos en un plugin, en la funcion ` inicializar() `.

```
  Q_INIT_RESOURCE( archivo.qrc )
```

De esta forma tendremos a nuestra disposicion todos los archivos que incluyamos.
Para acceder a ellos debemos usar una direccion especial.
Por ejemplo, para ver el archivo _icono.png_ que incluimos dentro del archivo embebido, debemos usar la ruta de acceso siguiente:
```
 label1->setIcon( QIcon( ":/icono.png" ) );
```
El _`:/`_ le indicara al programa que utilice los archivos embebidos.

**Nota:**
Los archivos embebidos se hacen disponibles entre todos los plugins cargados y son compartidos como si fuera un directorio comun. Recuerde que debe incluir siempre sus archivos en su plugin, a no ser que esten incluidos dentro de las librerias estaticas o el programa principal