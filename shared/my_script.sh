#!/bin/bash

# Создание каталога
mkdir my_backup

# Копирование файла
cp hello.txt my_backup/

# Переименование файла
mv my_backup/hello.txt my_backup/greetings.txt

# Удаление файла
rm my_backup/greetings.txt

# Поиск файла
echo "Список всех файлов с расширением .txt:"
find . -type f -name "*.txt"

# Архивация файлов
tar -czf my_archive.tar.gz my_backup

# Управление процессами
echo "Завершение всех процессов firefox:"
pkill firefox

# Перенаправление вывода
ls -l > file_list.txt

# Вывод содержимого созданного файла
echo "Содержимое файла file_list.txt:"
cat file_list.txt

