#include <los.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char* argv[]) {
    const char* path;
    if (argc <= 1) {
        path = ".";
    } else {
        path = argv[1];
    }

    int64_t dd = open_directory(path);
    if (dd < 0) {
        printf("Error while opening %s: %s\n", argv[1], strerror(dd));
        exit(1);
    }

    Dirent entry;
    while (1) {
        int64_t status = read_directory(dd, &entry);
        if (status == 0) {
            break;
        } else if (status < 0) {
            printf("Error while reading directory: %s\n", strerror(status));
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
