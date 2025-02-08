#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATH_LEN 4096

// Función para listar recursivamente directorios
void list_recursive(const char *path, int depth) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;

    // Abrir directorio
    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        return;
    }

    // Imprimir cabecera del directorio
    printf("\n%s:\n", path);

    // Leer entradas del directorio
    while ((entry = readdir(dir)) != NULL) {
        char full_path[MAX_PATH_LEN];
        
        // Ignorar . y ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Construir ruta completa
        snprintf(full_path, MAX_PATH_LEN, "%s/%s", path, entry->d_name);

        // Obtener información del archivo
        if (lstat(full_path, &statbuf) == -1) {
            perror("lstat");
            continue;
        }

        // Imprimir entrada
        printf("%*s%s\n", depth * 2, "", entry->d_name);

        // Si es directorio, llamar recursivamente
        if (S_ISDIR(statbuf.st_mode) && !S_ISLNK(statbuf.st_mode)) {
            list_recursive(full_path, depth + 1);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *root = ".";

    if (argc > 1) {
        root = argv[1];
    }

    printf("Listado recursivo de: %s\n", root);
    list_recursive(root, 0);
    
    return 0;
}