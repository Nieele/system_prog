#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int status;

    // Создание нового процесса
    pid = fork();

    if (pid < 0) {
        // Ошибка при создании процесса
        perror("Ошибка при создании процесса");
        exit(1);
    } else if (pid == 0) {
        // Это дочерний процесс
        printf("Дочерний процесс с PID: %d\n", getpid());
        // Имитация работы дочернего процесса
        sleep(3);
        exit(42); // Код возврата дочернего процесса
    } else {
        // Это родительский процесс
        printf("Родительский процесс с PID: %d\n", getpid());
        // Ожидание завершения дочернего процесса
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Дочерний процесс завершился с кодом: %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
