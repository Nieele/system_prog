#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>

#define EVENT_SIZE  (sizeof(struct inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + 16))

int main(int argc, char *argv[]) {
    int fd, wd;
    char buffer[BUF_LEN];
    struct inotify_event *event;

    if (argc < 2) {
        printf("Использование: %s <имя файла>\n", argv[0]);
        return 1;
    }

    // Создание экземпляра inotify
    fd = inotify_init();
    if (fd < 0) {
        perror("Ошибка inotify_init");
        return 1;
    }

    // Добавление наблюдения за изменениями в файле
    wd = inotify_add_watch(fd, argv[1], IN_MODIFY);
    if (wd < 0) {
        perror("Ошибка inotify_add_watch");
        return 1;
    }

    printf("Мониторинг изменений в файле %s...\n", argv[1]);

    while (1) {
        int length = read(fd, buffer, BUF_LEN);
        if (length < 0) {
            perror("Ошибка чтения из inotify");
            return 1;
        }

        // Обработка событий
        for (char *ptr = buffer; ptr < buffer + length; ptr += EVENT_SIZE + event->len) {
            event = (struct inotify_event *)ptr;
            if (event->mask & IN_MODIFY) {
                printf("Файл %s был изменен.\n", argv[1]);
            }
        }
    }

    // Удаление наблюдения и закрытие экземпляра inotify
    inotify_rm_watch(fd, wd);
    close(fd);

    return 0;
}
