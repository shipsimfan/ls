#include <los.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {
    const char* path;
    if (argc <= 1) {
        path = ".";
    } else {
        path = argv[1];
    }

    int64_t dd = open_directory(path);
    if (dd < 0) {
        printf("Error while opening %s: %li", argv[1], dd);
        exit(1);
    }

    Dirent entry;
    while (1) {
        int64_t status = read_directory(dd, &entry);
        if (status == 0) {
            break;
        } else if (status < 0) {
            printf("Error while reading directory: %li", status);
            exit(1);
        }

        if (entry.type == DIRENT_TYPE_DIRECTORY)
            printf("         ");
        else
            printf(" %8li", entry.size);

        printf(" %s\n", entry.name);
    }

    close_directory(dd);
}