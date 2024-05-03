#include <stdio.h>

int main() {
    FILE *file;
    char text[] = "Привет я студентка 32ИС!\n";

    // Создание нового файла для записи
    file = fopen("output.txt", "w");

    // Проверка на успешное создание файла
    if (file == NULL) {
        printf("Ошибка создания файла.\n");
        return 1;
    }

    // Запись текста в файл
    fprintf(file, "%s", text);

    // Закрытие файла
    fclose(file);

    printf("Текст успешно записан в файл 'output.txt'.\n");

    return 0;
}
