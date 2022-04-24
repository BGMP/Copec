Shell
===
Programa en C que simula una Shell, y permite la ejecución de llamadas al sistema de Linux. El uso de las llamadas
al sistema es realizado mediante comandos.

### Compilación
Para compilar el programa, se debe ejecutar el script de compilación presente en la raíz del proyecto:
```
chmod +x build.sh
./build.sh
```
El script creará un directorio dentro de la raíz del proyecto llamado 'build/', y dentro de él se encontrará el binario
'Shell'.

Para compilar manualmente:
```
cc src/main.c -I include/ -o Shell
```
El binario se llamará también 'Shell'.

### Ejecución
Para ejecutar la Shell, simplemente ejecutar el binario 'Shell'.

```
./Shell
```

### Comandos
Todos los comandos disponibles en la consola:
  * `cwd`: Imprime en pantalla el directorio actual.
  * `seconds`: Imprime en pantalla la cantidad de segundos transcurridos desde el primero de Enero de 1970 (EPOCH).
  * `stats`: Imprime en pantalla el uptime del sistema, información de la RAM y procesos actuales.
  * `ls`: Imprime en pantalla los archivos del directorio en donde se ejecute.
  * `mkdir <path>`: Crea un nuevo directorio con el nombre del argumento 'path'. Por defecto, el directorio es generado
  dentro de donde la ruta en donde se encuentre el usuario al momento de la ejecución del comando. Si 'path' contempla
  más de un directorio (a/b/c/dir) el directorio a generar será 'dir' en este caso, dentro de la ruta especificada.
    * path: Nombre del nuevo directorio.
  * `cd <path>`: Mueve al usuario dentro del directorio 'path'.
    * path: Nombre de la ruta al cual el usuario desea moverse.
  * `Salir`: Termina la ejecución del programa.

#### Comandos de Funcionalidades Extra
  * `MAKEITGOOD`: Activa un modo en que la Shell imprime con letras de un color aleatorio. Para desactivarlo basta con 
  usar el comando por segunda vez.
  * `JOKER`: Activa un modo en que la Shell imprime con fondo de un color aleatorio. Para desactivarlo usar el comando
  por segunda vez.
