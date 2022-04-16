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

#define CMD_SIZE 256
#define ARGS_SIZE 16

#define CONTINUE 1

#define EXIT_CMD "Salir"
#define PWD_CMD "cwd"
#define TIME_CMD "seconds"
#define CHDIR_CMD "cd"
#define SYSINFO_CMD "stats"
#define MAKEDIR_CMD "mkdir"
#define LS_CMD "ls"

char command[CMD_SIZE];         // Comando ingresado
char *args[ARGS_SIZE];          // Argumentos del comando
int argsLength;                 // Cantidad de argumentos
pid_t pid;                      // ID del proceso hijo

void prompt();
void parse();
int eval();

void cwd();
void seconds();
void stats();
void cd(char *path);
void makedir(char *path, mode_t mode);
void listdir();

int main() {
    int status;

    printf("Escribe 'Salir' para salir.\n\n");
    do {
        prompt(); // Enviamos el prompt al usuario
        parse(); // Leemos el comando, y lo almacenamos en "command"
        status = eval(args);
    } while (status != EXIT_SUCCESS);

    return 0;
}

void prompt() {
    cwd();
    printf("$ ");
}

void parse() {
    fgets(command, CMD_SIZE, stdin); // Esperamos a que el usuario ingrese un comando, y lo capturamos
    if ((strlen(command) > 0) && (command[strlen(command) - 1] == '\n')) { // En caso de no ser un comando vacío, y tener un salto de línea al final
        command[strlen(command) - 1] = '\0'; // Removemos el salto de línea
    }

    char *p;
    int i = 0;
    p = strtok(command, " "); // split
    while (p != NULL) {
        if (i > 0) args[i - 1] = p; // exclude the command itself, and only add arguments to args[]

        p = strtok(NULL, " ");
        i++;
    }

    argsLength = i;
}

int eval() {
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
        makedir(args[0], S_IRWXU); // TODO: Pass mode as argument OR flag
    } else if (!strcmp(LS_CMD, command)) {
        listdir();
    } else {
        printf("%s: Comando no encontrado.\n", command);
    }

    return CONTINUE;
}

// FIXME: Handle errors everywhere
void cwd() {
    char CWD[256];
    if (getcwd(CWD, sizeof(CWD)) == NULL) {
        perror("getcwd() error");
    } else {
        printf("%s", CWD);
    }
}

void seconds() {
    time_t seconds;
    seconds = time(NULL);
    if (seconds == ((time_t) -1)) {
        perror("time() error");
    } else {
        printf("Segundos desde el primero de Enero de 1970: %ld", seconds);
    }
}

// FIXME: Consider '1 DAY' instead of '1 DAYS'
void stats() {
    struct sysinfo systemInfo;
    const long minute = 60;
    const long hour = minute * 60;
    const long day = hour * 24;

    sysinfo(&systemInfo);
    printf("=== Stats del Sistema ===\n");
    printf("=> Uptime: %ld días con %ld:%02ld:%02ld\n",
           systemInfo.uptime / day,
           ((systemInfo.uptime % day) / hour),
           (systemInfo.uptime & hour) / minute,
           systemInfo.uptime % minute
           );
    printf("=> Ram Total: %lu MB\n", systemInfo.totalram / (1024 * 1024));
    printf("=> Ram Libre: %lu MB\n", systemInfo.freeram / (1024 * 1024));
    printf("=> Procesos actuales: %d\n", systemInfo.procs);
}

void cd(char *path) {
    int response = chdir(path);
}

void makedir(char *path, mode_t mode) {
    int response = mkdir(path, mode);
}

void listdir() {
    struct dirent *entry;
    DIR *dir;

    if ((dir = opendir(".")) == NULL) {
        perror("opendir() error");
    } else {
        while ((entry = readdir(dir)) != NULL) {
            printf("%i %s\n", entry->d_type, entry->d_name); // TODO: Map entry->d_type to names
        }
    }

    closedir(dir);
}

