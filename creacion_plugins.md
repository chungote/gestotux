#Como generar y compilar nuevos plugins en el programa

# Introduccion #

La idea basica de este programa es poder sumar caracteristicas al mismo simplemente agregardo una libreria dinamica que se pueda cargar en tiempo de ejecucion cuando cargue el programa y desde ahi, poder trabajar tranquilamente sin preocuparse por las consideraciones generales del programa, como manejo de ventanas, barras de herramientas, menus y actualizaciones.

# Como generar un nuevo plugin #

## Estructura ##

Cada plugin tiene necesariamente una estructura predefinida, puede ser de cualquiera de estos 3 tipos:
  * **Plugin general:** Es una libreria general que agrega una caracteristica simple al programa, como una barra de acciones, un nuevo menu, o todo un sistema completo de facturacion.
  * **Plugin de Informacion:** Es una libreria que posee los metodos para poder mejorar la interfaz de usuario con los datos especificos de un cliente, dandole un titlo al programa, un icono a la ventana principal entre otros datos.
  * **Plugin de base de datos:** -todavia no implementado-

## Creacion ##

Para generar un nuevo plugin, hacemos una nueva carpeta dentro de la carpeta de plugins, y generamos el archivo .pro necesario.
Se recomienda que se establezcan las siguientes variables para que se pueda cargar automaticamente al iniciarse el programa:

```
TEMPLATE = lib
CONFIG += dll \
plugin \
help
DESTDIR = ../../bin/plugins
INCLUDEPATH += ../../utiles
LIBS += ../../bin/libutiles.a
```

Definimos a este subproyecto como una libreria tipo plugin y le agregamos dll para que se gener como archivo dll en windows. La adicion de help es para que se pueda usar el sistema interno de ayuda. Agregamos ademas la libreria utiles que contiene las ventanas, visores de resumenes, acciones estandar y el sistema de ayuda.

### Clase principal ###

Cuando se inicializa el plugin, se carga una clase que tiene como finalidad hacer la inicializacion del plugin antes de usarlo.
Para eso, implmementamos una de las interfaces elegidas:

**EPlugin**
> Esta clase nos da las funciones minimas y necesarias que se precisan para que el plugin pueda cargarse correctamente. Las funciones son las siguientes:

` QList<QAction *> accionesBarra() const = 0; `
Es la funcion que se llamara cuando se busquen las acciones para colocar en la barra de herramientas.

` virtual bool inicializar( QSettings *pref ) = 0; `
Es la funcion que se llamara antes que ninguna y se utiliza para inicializar todas las acciones, funciones y demas cosas que sean necesarias. El objeto pref, apunta a las preferencias del programa, es un objeto global y estatico. Si la inicializacion se hizo correctamente, debe retornar **true**, o **false** en otro caso.

` virtual QWidgetList formsPreferencias() = 0; `
Devuelve la lista de QWidgets que se cargaran cuando se abran las preferencias del programa. Revise la pagina de formularios\_preferencias para ver como implementarlo.

` virtual QString nombre() const = 0; `
Devuelve el nombre interno del plugin. Sirve para buscar actualizaciones.

` virtual int tipo() const = 0; `
Devuelve el tipo de plugin que es ( comentado al principio ).

` virtual void crearMenu( QMenuBar *m ) = 0; `
Esta funcion le pasa la barra del menu para que se puedan crear todas las entradas necesarias.

` virtual bool verificarTablas() = 0; `
Esta funcion tiene la finalidad de verificar que las tablas en la base de datos de este plugin estan en estado consistente y que existen. Si esta funcion devuelve **false**, se intentaran crear nuevamente las tablas.

` virtual double version() const = 0; `
Devuelve la version del programa. Utilizada cuando se verifican las actualizaciones.

` virtual void agregarVentana( QWidget *v ) = 0; `
Esta es una señal a la cual se debe llamar cada vez que se quiera agregar una nueva ventana.

## Agregando tablas de base de datos ##

Para cada plugin, existe un metodo que le permite conocer si estan las tablas creadas pra usar. Este metodo de verificar tablas, de retornar falso, intentara crearlas a travez del archivo embebido que se encuentra en el directorio `:/sql`, y el cual debe tener la siguiente forma:

`<nombrePlugin>.<DriverSQL>.sql`

  * el **nombrePlugin** debe ser el mismo que el retornado por el metodo `QString nombre() const `

  * El **DriverSQL** debe ser el mismo que esta puesto en la lista de documentacion de qt.

Ejemplo:
  * **hicomp.QSQLITE.sql** se ejecutara si el metodo de verificacion de tablas del plugin _hicomp_ retorna falso.

Recuerde que la sintaxis de este archivo es un archivo sql.
Consideraciones especiales:
### SQLite ###
Esta base de datos al estar embebida en un archivo, es bastante lenta cuando se utilizan campos **blob** y su rango de tipos de datos es limitado.
Recuerde que debe colocar los valores para el proximo indice dentro de la tabla _sqlite`_`sequence_ sino no se podran insertar los datos nuevos mediante el programa.

De no encontrar el archivo, o no encontrar el archivo para el driver correspondiente, no se cargará el plugin.

### MySql ###
Generalmente no tendra gran cantidad de problemas con este plugin. Solo verifique que el codigo funciona sin problemas mediante una interfaz web.
Es probable que esta caracteristica se deshabilite para este driver, ya que al tratarse de una base de datos externa, las tablas deben ser generadas cada vez que se crea una base de datos para los clientes.

Para ver como embeber archivos en el plugin, visita la pagina [embeber\_archivos](embeber_archivos.md).

## Inicializacion ##

Cuando un plugin es cargado por el programa principal, se ejecutara el metodo _inicializar()_.
Dentro de este metodo generalmente se realizan todas las inicializaciones de acciones y verificaciones extras a la de la base de datos.
No intente crear barras de tareas o demas dentro de este metodo.

## Barra lateral ##

Para mostrar acciones de este plugin dentro de la barra lateral del programa, se debe implementar el metodo
`` QList<QActionGroup `*`> accionesBarra() ``

Para entender como funciona este sistema de barra lateral vea barra\_lateral.

## Menus ##

Para generar o agregar cosas dentro de los menus actuales, existe el metodo
`` void crearMenu( QMenuBar `*` ) ``
El parametro pasado como puntero es la barra de menu, asique se puede usar como si fuera la funcion _menuBar()_ de cualquier QMainWindow.
Para un ejemplo de esto vea generar\_menu ( proximamente )

## Otros Metodos ##

` QString directorioBackup() ` Devuelve el directorio donde se hara el backup on-line ( a implmenetar )

` QString directorioActualizaciones() ` Devuelve el directorio donde se buscaran las actualizaciones especificas. ( a re implementar ).