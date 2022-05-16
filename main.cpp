#include <mach-o/dyld.h>
#include <cstdio>

int main() {
    char path[512];
    unsigned size = 512;
    _NSGetExecutablePath(path, &size);
    path[size] = '\0';
    printf("The path is: %s\n", path);
}
