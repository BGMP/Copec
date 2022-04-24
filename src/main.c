////////////////////////////////////////////////////////////////////////////////
//
// Shell (Generic)
//
// Desc: main.c
// Archivo principal de Shell.
//
// 2022-04-17 (José Benavente & Vicente Bascuñán)
// Incepción del archivo.
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/sysinfo.h>
#include <sys/stat.h>

#include "main.h"

////////////////////////////////////////////////////////////////////////////////
// Globales:
////////////////////////////////////////////////////////////////////////////////

char command[CMD_SIZE];
char *args[ARGS_SIZE];
int argsLength;
char lastKnownDirectory[256];
int MAKEITGOOD = 0;
int JOKER = 0;

char * welcomeMsg  = "\n"
        "              ¿\n"
        "              |\n"
        "              |      SHELL SIMULATOR\n"
        "              |           by\n"
        "              |      José Benavente\n"
        "              |            &\n"
        "     ______   |     Vicente Bascuñán\n"
        "    \\ _____\\  |\n"
        "        / / ,.:..-----▄▄▄▄\n"
        "       | | |            █████▄▄|¯`':.._ ,---.\n"
        "      .---. \\__                       .---.  \\\n"
        "     /     \\-- \\___=================-/     \\  :\n"
        "    :   o   : /                     :   o   :/\n"
        "     \\     /-´                       \\     /´\n"
        "      `---´                           `---´   BGM\n"
        "\n";

int main() {
    int status;
    srand(time(NULL));

    printf("%s", welcomeMsg);
    printf("Escribe 'Salir' para salir.\n\n");
    do {
        prompt();               // enviamos el prompt al usuario
        parse();                // leemos el comando, y lo almacenamos en "command"
        status = eval(args);    // evaluamos el comando, y asignamos la respuesta a "status"
    } while (status != EXIT_SUCCESS);

    return 0;
}

void prompt() {
    cwd();
    printf("$ ");
}

void parse() {
    fgets(command, CMD_SIZE, stdin); // esperamos a que el usuario ingrese un comando, y lo capturamos
    if ((strlen(command) > 0) && (command[strlen(command) - 1] == '\n')) { // en caso de no ser un comando vacío, y tener un salto de línea al final
        command[strlen(command) - 1] = '\0'; // removemos el salto de línea
    }

    char *p;
    int i = 0;
    p = strtok(command, " "); // split
    while (p != NULL) {
        if (i > 0) args[i - 1] = p; // excluímos el comando, y sólo agregamos sus argumentos a args[]

        p = strtok(NULL, " ");
        i++;
    }

    argsLength = i;
}

int eval() {
    if (MAKEITGOOD) randomColor();
    if (JOKER) randomBackgroundColor();

    if(!strcmp("", command)) return CONTINUE;

    if (!strcmp(EXIT_CMD, command)) {
        return EXIT_SUCCESS;
    } else if (!strcmp(PWD_CMD, command)) {
        cwd();
        printf("\n");
    } else if (!strcmp(TIME_CMD, command)) {
        seconds();
        printf("\n");
    } else if (!strcmp(CHDIR_CMD, command)) {
        cd(args[0]);
    } else if (!strcmp(SYSINFO_CMD, command)) {
        stats();
    } else if (!strcmp(MAKEDIR_CMD, command)) {
        makedir(args[0]);
    } else if (!strcmp(LS_CMD, command)) {
        listdir();
    } else if (!strcmp(MAKEITGOOD_CMD, command)) {
        if (MAKEITGOOD) resetColor();
        else {
            randomColor();
        }
        MAKEITGOOD = !MAKEITGOOD;
    } else if (!strcmp(JOKER_CMD, command)) {
        if (JOKER) resetColor();
        else {
            randomBackgroundColor();
        }
        JOKER = !JOKER;
    } else {
        printf("%s: Comando no encontrado.\n", command);
    }

    return CONTINUE;
}

void cwd() {
    char CWD[256];

    if (getcwd(CWD, sizeof(CWD)) != NULL) {
        strcpy(lastKnownDirectory, CWD);
        printf("%s", CWD);
        return;
    }

    printf("%s", lastKnownDirectory);
    switch (errno) {
        case EACCES:
            printf("Permisos insuficientes\n");
            break;
        case EFAULT:
        case EINVAL:
            printf("No se pudo obtener el directorio actual\n");
            break;
        case ENAMETOOLONG:
            printf("No se pudo obtener el directorio actual: El nombre de la ruta excede el máximo de caracteres\n");
            break;
        case ENONET:
            printf("No se pudo obtener el directorio actual: El directorio ha sido desvinculado\n");
            break;
        case ENOMEM:
            printf("No se pudo obtener el directorio actual: Memoria insuficiente\n");
            break;
        case ERANGE:
            printf("No se pudo obtener el directorio actual: Error de asignación de memoria interno\n");
            break;
        default:
            printf("No se pudo listar el directorio actual: Error desconocido\n");
            break;
    }
}

void seconds() {
    time_t seconds;
    seconds = time(NULL);
    if (seconds == ((time_t) -1)) {
        perror("time() error");
    } else {
        printf("Segundos desde el EPOCH (primero de Enero de 1970): %ld", seconds);
    }
}

void stats() {
    struct sysinfo systemInfo;
    if (sysinfo(&systemInfo) != -1) {
        const long minute = 60;
        const long hour = minute * 60;
        const long day = hour * 24;

        const long sysDay = systemInfo.uptime / day;
        const long sysHour = (systemInfo.uptime % day) / hour;
        const long sysMinutes = (systemInfo.uptime % hour) / minute;
        const long sysSeconds = systemInfo.uptime % minute;

        printf("=== Stats del Sistema ===\n");
        printf("=> Uptime: %ld %s, %02ld:%02ld:%02ld\n",
               sysDay,
               sysDay == 1 ? "día" : "días",
               sysHour,
               sysMinutes,
               sysSeconds
        );

        printf("=> Ram Total: %lu MB\n", systemInfo.totalram / (1024 * 1024));
        printf("=> Ram Libre: %lu MB\n", systemInfo.freeram / (1024 * 1024));
        printf("=> Procesos actuales: %d\n", systemInfo.procs);

        return;
    }

    switch (errno) {
        case EFAULT:
            printf("Dirección 'info' inválida al obtener información del sistema");
            break;
        default:
            printf("No se pudo obtener la información del sistema: Error desconocido\n");
            break;
    }
}

void cd(char *path) {
    if (chdir(path) != -1) return;

    switch (errno) {
        case EACCES:
            printf("Permisos insuficientes");
            break;
        case EFAULT:
            printf("La ruta apunta fuera de la dirección de espacio accesible\n");
            break;
        case EIO:
            printf("Error de I/O\n");
            break;
        case ELOOP:
            printf("Demasiados symlinks al resolver la ruta\n");
            break;
        case ENAMETOOLONG:
            printf("La longitud de la ruta es demasiado larga\n");
            break;
        case ENOENT:
        case ENOTDIR:
            printf("%s: El directorio o el archivo no existe\n", path);
            break;
        case ENOMEM:
            printf("Memoria de kernel insuficiente\n");
            break;
        default:
            printf("No se pudo crear el directorio: Error desconocido\n");
            break;
    }
}

void makedir(char *path) {
    if (mkdir(path, S_IRWXU) != -1) return;

    switch (errno) {
        case EACCES:
            printf("Permisos insuficientes\n");
            break;
        case EDQUOT:
            printf("Cuota de bloques de disco insuficiente\n");
            break;
        case EEXIST:
            printf("No se pudo crear el directorio: El archivo ya existe\n");
            break;
        case EFAULT:
            printf("La ruta apunta fuera de la dirección de espacio accesible\n");
            break;
        case EINVAL:
            printf("La ruta del directorio contiene caracteres inválidos\n");
            break;
        case ELOOP:
            printf("Demasiados symlinks al resolver la ruta\n");
            break;
        case EMLINK:
            printf("Demasiados links al directorio padre\n");
            break;
        case ENAMETOOLONG:
            printf("La longitud de la ruta es demasiado larga\n");
            break;
        case ENOMEM:
            printf("Memoria de kernel insuficiente\n");
            break;
        case ENOSPC:
            printf("No se pudo crear el directorio: Espacio insuficiente");
            break;
        case ENONET:
        case ENOTDIR:
            printf("No se pudo crear el directorio: La ruta es inválida\n");
            break;
        case EPERM:
            printf("No se pudo crear el directorio: El sistema no soporta la creación de directorios\n");
            break;
        case EROFS:
            printf("No se pudo crear el directorio: La ruta apunta a un archivo de sólo lectura en el sistema\n");
            break;
        default:
            printf("No se pudo crear el directorio: Error desconocido\n");
            break;
    }
}

void listdir() {
    struct dirent *entry;
    struct stat fileStat;

    DIR *dir = opendir(".");

    if (dir == NULL) {
        perror("opendir() error");
        return;
    }

    if ((entry = readdir(dir)) == NULL) {
        printf("Error al listar el directorio. Es posible que este ya no exista\n");
        return;
    }

    do {
        stat(entry->d_name, &fileStat);
        if (S_ISDIR(fileStat.st_mode)) {
            printf("%5s %s\n", "DIR", entry->d_name);
        } else {
            printf("%5s %s\n", "FILE", entry->d_name);
        }
    } while ((entry = readdir(dir)) != NULL);

    closedir(dir);
}

void randomColor() {
    int random = randomInRange(30, 37);
    printf("\033[1;%im", random);
}

void resetColor() {
    printf("\033[0m");
}

void randomBackgroundColor() {
    int random = randomInRange(40, 47);
    printf("\033[%im", random);
}

int randomInRange(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}
