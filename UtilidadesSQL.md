# Documentación de la clase Util

# Introducción #

Esta clase ubicada dentro de la carpeta util provee un método multi base de datos de comparar cadenas de texto al estilo razón social sin que permita repetir elementos por cambios de espacios o comas.

# Detalles #

Esta clase se creó para generar los métodos que sean necesarios para evitar los duplicados en la base de datos.

Actualmente consiste de dos funciones importantes:

## comparacionSQL ##

Esta función recibe una cadena de caracteres cualquiera y le elimina los espacios iniciales y finales, espacios intermedios y coloca todas las palabras en mayúsuculas.

## funcionComparacionSQL ##

Esta función recibe un nombre de campo de base de datos y le aplica las funciones sql necesarias según el driver de base de datos actual que realize las mismas acciones sobre el campo que la función anterior.

## Uso conjunto ##

El principal uso se podrá dar en la situación en que se desea conocer si existen duplicados al agregar un nuevo cliente por ejemplo. Al intentar agregar el cliente, se verifica si este no existe ya.
Se genera una consulta que contenga el conteo de elementos en el cual la condición WHERE tendrá como primer parámetro la salida de la función _funcionComparacionSQL_ y como elemento de igualaciòn _comparacionSQL_.