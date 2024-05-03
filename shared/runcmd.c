#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[100];

    // Ввод команды от пользователя
    printf("Введите команду для выполнения: ");
    fgets(command, sizeof(command), stdin);

    // Выполнение команды и вывод результата
    printf("Результат выполнения команды:\n");
    system(command);

    return 0;
}
