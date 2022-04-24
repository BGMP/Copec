////////////////////////////////////////////////////////////////////////////////
//
// Shell (Generic)
//
// Desc: main.h
// Archivo de encabezado para  Shell.
//
// 2022-04-17 (José Benavente & Vicente Bascuñán)
// Incepción del archivo.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Macros:
////////////////////////////////////////////////////////////////////////////////

#define CHDIR_CMD "cd"
#define PWD_CMD "cwd"
#define MAKEDIR_CMD "mkdir"
#define LS_CMD "ls"
#define EXIT_CMD "Salir"
#define TIME_CMD "seconds"
#define SYSINFO_CMD "stats"

#define MAKEITGOOD_CMD "MAKEITGOOD"
#define JOKER_CMD "JOKER"

#define CMD_SIZE 1024
#define ARGS_SIZE 156

#define CONTINUE 1

////////////////////////////////////////////////////////////////////////////////
// Prototipos:
////////////////////////////////////////////////////////////////////////////////

/// "$ cwd"
extern void cwd();

/// "$ seconds"
extern void seconds();

/// "$ stats"
extern void stats();

/// "$ cd <path>"
/// @param nombre del directorio al que se desea acceder
extern void cd(char *path);

/// "$ mkdir <path>"
/// @param path nombre del directorio que se desea crear
extern void makedir(char *path);

/// "$ ls"
extern void listdir();

/// prompt de nuestra Shell
extern void prompt();

/// método para interpretar la sintáxis de los comandos escritos por el usuario
extern void parse();

/// método para evaluar los comandos escritos por el usuario
extern int eval();

////////////////////////////////////////////////////////////////////////////////
// Globales:
////////////////////////////////////////////////////////////////////////////////

/// comando ingresado
extern char command[CMD_SIZE];

/// argumentos del comando ingresado
extern char *args[ARGS_SIZE];

/// número de argumentos del comando
extern int argsLength;

/// último directorio conocido por la Shell
/// usado en caso de que cwd() retorne un error
extern char lastKnownDirectory[256];

/// flag que indica si nos encontramos en modo multi-color o no
extern int MAKEITGOOD;

/// retorna un número aleatorio entre min y max
extern int randomInRange(int min, int max);

/// devuelve el color de la Shell al por defecto
extern void resetColor();

/// hace que el color de las letras en la Shell cambie aleatoriamente
extern void randomColor();

/// hace que el color de fondo de la Shell cambie aleatoriamente
extern void randomBackgroundColor();

/// Mensaje de bienvenida a la Shell
extern char * welcomeMsg;
