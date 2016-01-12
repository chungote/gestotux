# Guia de Desarrollo #

¿Como esta compuesto el programa?

El programa se divide en 3 partes principales, destacandose que en realidad todo depende del plugin que estes cargando. Como caracteristicas principales se destaca la capacidad de hacer backups sin importar que plugin se utilize, actualizar el programa por internet con un servidor ftp y tener la opcion de manejar el estilo y personalizar visualmente el programa.

Estas son las 3 partes principales del programa:

### Programa principal ###

Es el que le da el esqueleto a todo el programa general, mostrando la ventana principal y encargandose de  las barras de tareas, barra de herramientas, actualizaciones, backups y el manejo de las ventanas.
Es importante saber, que por cada cambio que se realize en el codigo del programa principal, se debe hacer una recompilacion de los plugins.

La ventana principal carga inicialmente y verifica los plugins, generando a travez de los metodos de barra de herramientas y de barra lateral, las acciones que se utilizaran en el programa automaticamente.
Tambien realiza un control sobre la periodiocidad de los backups y muestra un mensaje si esta vencido el plazo.

### Libreria comun ###

La libreria comun, contiene entre otras cosas, acciones que se vuelven repetitivas de implementar en cada formulario, como la accion de cerrar, y el esqueleto con imagen de la accion de agregar, ver, modificar, eliminar y buscar. De esta forma solo se debe invocar el constructor de cada clase y conectar el slot correspondiente a la accion requerida. Las clases de acciones tienen el siguiente formato: ` EActCerrar `, y al invocar automaticamente el constructor, se añade la imagen y el texto. Vea la pagina [acciones\_predefinidas](acciones_predefinidas.md).
Tambien contiene la estructura del visor de resumenes, que permite mantener de manera clara un resumen viendolo desde una perspectiva de "vista previa de impresion" y genera las acciones para imprimir, cambiar zoom y demas automaticamente. Solo se debe crear una ventana de **EVisorResumen** y quedará lista para su uso conectando la señal necesaria. Para mas informacion vea la pagina [visor\_de\_resumenes](visor_de_resumenes.md).

### Renderizador de Informes ###

El renderizador de informes esta basado en el proyecto ncreport, que compilado como una liberia externa permite cargar archivos xml con la definicion de los reportes y hacer consultas sobre la base de datos que se encuentra activa, dando una visual profesional a todos los reportes. Ademas permite una rapida actualizacion de los reportes, al tratarse de archivos que se encuentran fuera de la aplicacion.
Para ver como generar y llamar al generador de reportes vea la pagina [generar\_reportes](generar_reportes.md).

### Plugins ###

Los plugins son la parte mas importante del programa, y son los que realizaran la parte _pesada_ del programa. Vea la pagina [creacion\_plugins](creacion_plugins.md) para mas informacion.

**Plugins actuales**
  * email
  * compras
  * ventas
  * productos
  * gastos
  * caja
  * pagos
  * servicios
  * proveedor