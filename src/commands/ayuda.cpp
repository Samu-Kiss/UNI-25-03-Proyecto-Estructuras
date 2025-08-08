#include <iostream>
#include "../../include/commands.h"
#include "../../external/termcolor.hpp"

using namespace std;

void comandoAyuda(const string &param)
{
    if (param.empty())
    {
        cout << termcolor::blue;
        cout << "====================================================================================" << endl;
        cout << "                            >>> Comandos disponibles <<<                            " << endl;
        cout << "====================================================================================" << termcolor::reset << endl
             << endl;
        cout << "  help, ayuda [comando]             - Mostrar esta ayuda o ayuda de un comando" << endl;
        cout << "  exit, quit, salir                 - Salir de la consola" << endl;
        cout << "  cargar <nombre_archivo>           - Cargar secuencias desde un archivo" << endl;
        cout << "  listar_secuencias                 - Listar todas las secuencias en memoria" << endl;
        cout << "  histograma <descripcion>          - Mostrar histograma de una secuencia" << endl;
        cout << "  es_subsecuencia <subsec>          - Verificar si existe una subsecuencia" << endl;
        cout << "  enmascarar <subsecuencia>         - Enmascarar una subsecuencia" << endl;
        cout << "  guardar <nombre_archivo>          - Guardar secuencias en un archivo" << endl;
        cout << "  codificar <secuencia>             - Codificar una secuencia" << endl;
        cout << "  decodificar <secuencia>           - Decodificar una secuencia" << endl;
        cout << "  ruta_mas_corta <i> <j> <x> <y>    - Buscar ruta más corta" << endl;
        cout << "  base_remota <i> <j>               - Buscar base remota" << endl;
        cout << "  clear                             - Limpiar la pantalla" << endl;
        return;
    }

    if (param == "cargar")
    {
        cout << termcolor::blue << "cargar <nombre_archivo>" << termcolor::reset << endl;
        cout << "Carga en memoria los datos contenidos en el archivo identificado por nombre_archivo, es decir, utiliza adecuadamente las estructuras lineales para cargar la información de los genomas en memoria. Si dentro de la misma sesión de trabajo ya se han cargado otros archivos de secuencias (usando el comando cargar), la información debe sobreescribirse en memoria, es decir, no se deben combinar informaciones de secuencias de diferentes archivos."
             << endl;
    }
    else if (param == "listar_secuencias")
    {
        cout << termcolor::blue << "listar_secuencias" << termcolor::reset << endl;
        cout << "Imprime la cantidad de secuencias actualmente en memoria, y luego, en n líneas (una para secuencia) la información básica (nombre y cantidad de bases diferentes) de cada secuencia. Si la secuencia es completa (no tiene el código '-' ) indica la cantidad de bases exactas (contiene b bases); si la secuencia es incompleta (incluye uno o varios códigos '-') indica la cantidad mínima de bases, sin contar el código '-' (contiene al menos b bases)."
             << endl;
    }
    else if (param == "histograma")
    {
        cout << termcolor::blue << "histograma <descripcion_secuencia>" << termcolor::reset << endl;
        cout << "Imprime el histograma de una secuencia, en caso de que exista. El histograma se define como el conteo (frecuencia) de cada código en la secuencia. Por cada línea se escribe el código y la cantidad de veces que aparece en la secuencia. El ordenamiento del histograma está dado por la tabla correspondiente. El código '-' debe incluirse también como parte del histograma."
             << endl;
    }
    else if (param == "es_subsecuencia")
    {
        cout << termcolor::blue << "es_subsecuencia <subsecuencia>" << termcolor::reset << endl;
        cout << "Determina si una subsecuencia (secuencia corta de bases) dada por el usuario, existe dentro de las secuencias cargadas en memoria. Si es así, determina la cantidad de veces en las que esta subsecuencia dada se repite. No es necesario indicar el nombre de la secuencia donde se encuentra la repetición (el conteo es general sobre todas las secuencias cargadas en memoria)."
             << endl;
    }
    else if (param == "enmascarar")
    {
        cout << termcolor::blue << "enmascarar <subsecuencia>" << termcolor::reset << endl;
        cout << "Enmascara una subsecuencia (secuencia corta de bases) dada por el usuario, si existe. Los elementos que pertenecen a la subsecuencia se enmascaran cambiando cada base individual por el código 'X'. No es necesario indicar el nombre de la secuencia donde se realiza el enmascarado (el proceso es general sobre todas las secuencias cargadas en memoria)."
             << endl;
    }
    else if (param == "guardar")
    {
        cout << termcolor::blue << "guardar <nombre_archivo>" << termcolor::reset << endl;
        cout << "Guarda en el archivo nombre_archivo las secuencias cargadas en memoria. Se debe tener en cuenta la justificación (de líneas) de cada secuencia inicial, así como las posibles modificaciones que hayan sufrir las secuencias en memoria (después de enmascarar)."
             << endl;
    }
    else if (param == "codificar")
    {
        cout << termcolor::blue << "codificar <secuencia>" << termcolor::reset << endl;
        cout << "El comando debe generar el archivo binario con la correspondiente codificación de Huffman en el formato descrito más arriba, almacenándolo en disco bajo el nombre nombre_archivo.fabin . Si no hay secuencias cargadas en memoria, o si el archivo no puede escribirse correctamente, el comandodebe mostrar el mensaje correspondiente."
             << endl;
    }
    else if (param == "decodificar")
    {
        cout << termcolor::blue << "decodificar <secuencia>" << termcolor::reset << endl;
        cout << "El comando debe cargar en memoria las secuencias contenidas en el archivo binario nombre_archivo.fabin , que contiene una codificación Huffman de un conjunto de secuencias en el formato descrito más arriba. Si dentro de la misma sesión de trabajo ya se han cargado otros archivos de secuencias (usando el comando cargar), la información debe sobreescribirse en memoria, es decir, no se deben combinar informaciones de secuencias de diferentes archivos. Si por alguna razón no es posible cargar la información de codificación, o no es posible realizar el proceso de decodificación, el comando debe mostrar el mensaje de error"
             << endl;
    }
    else if (param == "ruta_mas_corta")
    {
        cout << termcolor::blue << "ruta_mas_corta <i> <j> <x> <y>" << termcolor::reset << endl;
        cout << "El comando debe imprimir en pantalla la secuencia de vértices (bases) del grafo que describen la ruta más corta entre la base ubicada en la posición [i, j] de la matriz de la secuencia descripcion_secuencia y la base ubicada en la posición [x, y] de la misma matriz. Así mismo, debe imprimir el costo total de la ruta, teniendo en cuenta el peso que tiene cada conexión entre bases"
             << endl;
    }
    else if (param == "base_remota")
    {
        cout << termcolor::blue << "base_remota <i> <j>" << termcolor::reset << endl;
        cout << "Para la base ubicada en la posición [i, j] de la matriz de la secuencia descripcion_secuencia , el comando busca la ubicación de la misma base (misma letra) más lejana dentro de la matriz. Para esta base remota, el comando debe imprimir en pantalla su ubicación, la secuencia de vértices (bases) que describen la ruta entre la base origen y la base remota, y el costo total de la ruta, teniendo en cuenta el peso que tiene cada conexión entre bases"
             << endl;
    }
    else if (param == "clear")
    {
        cout << termcolor::blue << "clear" << termcolor::reset << endl;
        cout << "Limpia la pantalla de la consola." << endl;
    }
    else if (param == "help" || param == "ayuda")
    {
        cout << termcolor::blue << "help, ayuda [comando]" << termcolor::reset << endl;
        cout << "Muestra la ayuda general o de un comando específico." << endl;
    }
    else if (param == "exit" || param == "quit" || param == "salir")
    {
        cout << termcolor::blue << "exit, quit, salir" << termcolor::reset << endl;
        cout << "Termina la ejecución de la aplicación." << endl;
    }
    else
    {
        cout << termcolor::red << "No existe ayuda para el comando: " << param << termcolor::reset << endl;
    }
}
