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
#define CAR_CMD "CAR"

#define CMD_SIZE 1024
#define ARGS_SIZE 156

#define CONTINUE 1

char * car =
        "              ¿\n"
        "              |\n"
        "              |\n"
        "              |\n"
        "              |\n"
        "              |\n"
        "     ______   |\n"
        "    \\ _____\\  |\n"
        "        / / ,.:..-----▄▄▄▄\n"
        "       | | |            █████▄▄|¯`':.._ ,---.\n"
        "      .---. \\__                       .---.  \\\n"
        "     /     \\-- \\___=================-/     \\  :\n"
        "    :   o   : /                     :   o   :/\n"
        "     \\     /-´                       \\     /´\n"
        "      `---´                           `---´   BGM\n";


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
extern void cd(char *path);

/// "$ mkdir <path>"
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

/// Comando ingresado
extern char command[CMD_SIZE];

/// Argumentos del comando ingresado
extern char *args[ARGS_SIZE];

/// Número de argumentos
extern int argsLength;

/// ID del proceso hijo TODO: Implement fork()
extern pid_t pid;

/// Último directorio conocido por la Shell
// - Usado en caso de que cwd() retorne un error
extern char lastKnownDirectory[256];

extern int randomInRange(int min, int max);

extern void resetColor();

extern void randomColor();
