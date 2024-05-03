#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>

int main() {
    struct utsname unameData;
    int num_cores;

    // Получение информации о системе
    uname(&unameData);
    num_cores = sysconf(_SC_NPROCESSORS_ONLN);

    // Вывод информации о системе
    printf("Информация о системе:\n");
    printf("  - Операционная система: %s %s\n", unameData.sysname, unameData.release);
    printf("  - Версия Ubuntu: %s\n", unameData.version);
    printf("  - Количество ядер процессора: %d\n", num_cores);

    return 0;
}
