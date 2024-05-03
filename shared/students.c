#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

typedef struct {
    char name[50];
    int age;
    float grade;
} Student;

void addStudent(Student students[], int *count) {
    if (*count < MAX_STUDENTS) {
        printf("Введите имя студента: ");
        scanf("%s", students[*count].name);
        printf("Введите возраст студента: ");
        scanf("%d", &students[*count].age);
        printf("Введите средний балл студента: ");
        scanf("%f", &students[*count].grade);
        (*count)++;
    } else {
        printf("Нет места для добавления нового студента.\n");
    }
}

void displayStudents(Student students[], int count) {
    printf("Список студентов:\n");
    for (int i = 0; i < count; i++) {
        printf("Имя: %s, Возраст: %d, Средний балл: %.2f\n", students[i].name, students[i].age, students[i].grade);
    }
}

int compareStudents(const void *a, const void *b) {
    return strcmp(((Student *)a)->name, ((Student *)b)->name);
}

void searchUnsorted(Student students[], int count, char *name) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("Студент найден:\nИмя: %s, Возраст: %d, Средний балл: %.2f\n", students[i].name, students[i].age, students[i].grade);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Студент с именем %s не найден.\n", name);
    }
}

void searchSorted(Student students[], int count, char *name) {
    Student *result = bsearch(name, students, count, sizeof(Student), compareStudents);
    if (result != NULL) {
        printf("Студент найден:\nИмя: %s, Возраст: %d, Средний балл: %.2f\n", result->name, result->age, result->grade);
    } else {
        printf("Студент с именем %s не найден.\n", name);
    }
}

void selectionSort(Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < count; j++) {
            if (students[j].grade < students[minIndex].grade) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Student temp = students[i];
            students[i] = students[minIndex];
            students[minIndex] = temp;
        }
    }
}

void bubbleSort(Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].grade > students[j + 1].grade) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

void insertionSort(Student students[], int count) {
    for (int i = 1; i < count; i++) {
        Student key = students[i];
        int j = i - 1;
        while (j >= 0 && students[j].grade > key.grade) {
            students[j + 1] = students[j];
            j = j - 1;
        }
        students[j + 1] = key;
    }
}

void writeToFile(Student students[], int count, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%s %d %.2f\n", students[i].name, students[i].age, students[i].grade);
        }
        fclose(file);
        printf("Данные успешно записаны в файл %s.\n", filename);
    } else {
        printf("Ошибка при открытии файла %s.\n", filename);
    }
}

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;

    int choice;
    char name[50];

    do {
        printf("\nМеню:\n");
        printf("1. Добавить студента\n");
        printf("2. Вывести список студентов\n");
        printf("3. Поиск студента по имени в неупорядоченном списке\n");
        printf("4. Поиск студента по имени в упорядоченном списке\n");
        printf("5. Сортировка списка студентов: \n");
        printf("6. Записать данные студентов в файл\n");
        printf("0. Выйти\n");
        printf("Введите ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                printf("Введите имя студента для поиска: ");
                scanf("%s", name);
                searchUnsorted(students, count, name);
                break;
            case 4:
                printf("Введите имя студента для поиска: ");
                scanf("%s", name);
                qsort(students, count, sizeof(Student), compareStudents);
                searchSorted(students, count, name);
                break;
            case 5:
                printf("Выберите метод сортировки:\n");
                printf("1. Сортировка выбором\n");
                printf("2. Сортировка обменом\n");
                printf("3. Сортировка вставками\n");
                printf("Введите ваш выбор: ");
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        selectionSort(students, count);
                        break;
                    case 2:
                        bubbleSort(students, count);
                        break;
                    case 3:
                        insertionSort(students, count);
                        break;
                    default:
                        printf("Неверный выбор.\n");
                }
                printf("Список студентов после сортировки:\n");
                displayStudents(students, count);
                break;
            case 6:
                writeToFile(students, count, "students.txt");
                break;
            case 0:
                printf("До свидания!\n");
                break;
            default:
                printf("Неверный выбор.\n");
        }

    } while (choice != 0);

    return 0;
}
