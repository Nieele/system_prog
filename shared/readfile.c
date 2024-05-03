#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char ch;

    // Открытие файла для чтения
    file = fopen("z1.txt", "r");

    // Проверка на успешное открытие файла
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return 1;
    }

    // Чтение и вывод содержимого файла
    printf("Содержимое файла z1.txt:\n");
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    // Закрытие файла
    fclose(file);

    return 0;
}
