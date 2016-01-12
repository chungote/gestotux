Esta pagina explica como hacer el mappeo para que los QComboBox tengan los ID's de los datos cargados.

# Introduccion #

Generalmente cuando colocamos los datos de un campo especifico dentro de un combo box donde el usuario tiene que seleccionar solo una opción, no poseemos el mappeo pos->id del item que esta seleccionando.
Para tal efecto hemos creado una clase que nos permite obtener el ID de la base de datos dependiendo del elemento seleccionado en el combobox.

# Detalles #

La clase en cuestión se llama: **ECBTabla**.

Esta clase permite definir los siguientes elementos posibles:

Tabla**: Tabla o vista de la cual se obtendrán los datos.** **ID**: Permite especificar el codigo sql para obtener el campo id deseado.
Texto**: Permite especificar el codigo sql para obtener el campo que se le mostrará al usuario. Puede ser tanto una concatenación como un campo simple, siempre que el driver de la base de datos lo interprete.** **Filtro**: Perimte especificar el codigo sql para filtrar los datos que se le mostrarán al usuario.
Orden**: Permite especificar el orden en que se mostrarán los elementos en el combobox.**

Los elementos _orden_ y _filtro_ pueden ser nulos.

La clase guarda un mapa interno donde se mappea la posicion del combobox, con el identificador de la base de datos pasado como parametro. Por ahora solo se permite un identificador entero.
La inicialización de los datos se produce de manera diferida, 600 ms luego de finalizado el constructor para que no bloquee el inicio del mostrado del formulario.