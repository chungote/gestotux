#Introduccion al visor de resumenes

# Introduccion #

La clase de visor de resumenes se creo para eliminar el problema que implica tener que controlar todos los pasos y acciones necesarias para ver, mantener e imprimir los distintos resumenes que se pueden llegar a generar en el programa. Mayormente si trabajo principal es mostrar el resumen cuando este este generado, cambiar entre los distintos tipos de vistas que haya y embeber y mantener las acciones de impresion, pdf y su correspondiente barra de tareas.

# Como usarlo #

Para utilizar este visor de resumenes es necesario linkear nuestro plugin con la libreria general del programa, la cual por razones mas que odvias nos dara la clase que permite crear la ventana y mantener todo lo demas antes expresado. La Clase es _EVisorInformes_.
Su constructor es lo que mas nos interesa:

`EVisorInformes(QPrinter *impre = new QPrinter( QPrinterInfo::defaultPrinter() ), QWidget *parent = 0);`
Como primer parametro ponemos la impresora que estaremos utilizando para "pintar" el reporte y como segundo parametros pondremos a quien queremos que sea su padre. Luego