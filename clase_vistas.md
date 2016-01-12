# EVLista #

Una clase muy importante para un rapido desarollo de los componentes del programa.

## Principales Caracteristicas ##

Esta clase genera una ventana con un contenedor de tipo tabla al cual se le puede colocar cualquier modelo del tipo _QSqlTableModel_ o heredado de el. Ademas ya posee todos las acciones mas comunes declaradas para que solo sea necesario agregarlas e implementar los slots especificos si queremos o utilizar los que son mas genericos dependiendo de la situación.

### Metodos importantes ###

  * ` void EVLista::menuContextual( const QModelIndex &indice, QMenu *menu ) `
Metodo que permite agregar acciones al menu contextual para cierto indice especifico. El menu se genera automaticamente cada vez que el usuario presiona click derecho sobre un item de la lista de elementos que estamos mostrando.

  * ` void EVLista::agregar( bool autoeliminarid ) `
Metodo que agrega limpiamente un elemento a la lista, y si autoeliminar id es verdadero, antes de agregar el registro al final, elimina el primer campo.

  * ` void EVLista::eliminar() `
Elimina el o los indices que esten selecciónados en ese momento en la vista. Se debe reimplementar para cada tipo de eliminacion especifica.

  * `void EVLista::buscar()`
  * `void EVLista::imprimir()`
  * `void EVLista::pdf()`

Metodos vacios.

  * ` void EVLista::cerrar() `
Metodo llamado cuando se presiona la accion de cerrar o se cierra la ventana.

### Acciones inscrustadas ###

**ActCerrar:** Accion de cerrar ( _EActCerrar_ )

**ActImprimir:** Accion de imprimir ( _EActImprimir_  )

**ActPdf:** Accion de guardar como pdf ( _EActPdf_  )

**ActEmail:** Accion de enviar x email o alguna accion relacionada con emails ( _EActEmail_  )

**ActAgregar:** Accion para agregar nuevo registro ( _EActAgregar_  )

**ActEliminar:** Accion para eliminar el/los registros ( _EActEliminar_  )