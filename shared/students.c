#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <locale.h>

#define MAX_STUDENTS        16
#define MAX_LENGTH_NAME     50
#define SIZE_NUM_BUFFER     256

/*-------------------------- Utility -----------------------------------*/

bool readString(char* buffer, size_t buffSize) {
    if (buffSize < 1)
        return false;

    if (!fgets(buffer, buffSize, stdin))
        return false;

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    return true;
}

bool readInt(int* num) {
    char buffer[SIZE_NUM_BUFFER];

    if (!readString(buffer, SIZE_NUM_BUFFER))
        return false;

    if (sscanf(buffer, "%d", num) != 1) {
        *num = 0;
        return false;
    }

    return true;
}

bool readFloat(float* num) {
    char buffer[SIZE_NUM_BUFFER];

    if (!readString(buffer, SIZE_NUM_BUFFER))
        return false;

    if (sscanf(buffer, "%f", num) != 1) {
        *num = 0.0f;
        return false;
    }

    return true;
}

/*-------------------------- Student -----------------------------------*/

typedef struct {
    char* name;
    uint8_t age;
    float grade;
} Student;

Student* createStudent() {
    Student* temp = (Student*)malloc(sizeof(Student));

    if (!temp)
        return temp;

    temp->name = (char*)malloc(sizeof(char) * MAX_LENGTH_NAME);

    if (!temp->name) {
        free(temp);
        return NULL;
    }

    return temp;
}

void freeStudent(Student* student) {
    free(student->name);
    free(student);
}

Student* readStudent() {
    Student* temp = createStudent();

    if (!temp)
        return temp;

    if (readString(temp->name, MAX_LENGTH_NAME)) {
        int age;
        if (readInt(&age)) {
            temp->age = (uint8_t)age;
            if (readFloat(&temp->grade)) {
                return temp;
            }
        }
    }

    freeStudent(temp);
    return NULL;
}

void displayStudent(const Student* student) {
    printf("Имя: %s, Возраст: %d, Средний балл: %.2f\n",
        student->name,
        student->age,
        student->grade
    );
}

int compareStudents(const void* first, const void* second) {
    const Student* student1 = *(const Student**)first;
    const Student* student2 = *(const Student**)second;

    return strcmp(student1->name, student2->name);
}

/*--------------------- Student Container ------------------------------*/

typedef struct {
    Student** students;
    size_t count;
} StudentsContainer;

StudentsContainer* createStudentsContainer() {
    StudentsContainer* temp = (StudentsContainer*)malloc(sizeof(StudentsContainer));

    if (!temp)
        return temp;

    temp->students = (Student**)malloc(sizeof(Student) * MAX_STUDENTS);

    if (!temp->students) {
        free(temp);
        return NULL;
    }

    temp->count = 0;
    return temp;
}

void freeStudentsContainer(StudentsContainer** conatiner) {
    for (size_t i = 0; i < (*conatiner)->count; ++i) {
        freeStudent((*conatiner)->students[i]);
    }
    free((*conatiner)->students);
    free(*conatiner);
}

void displayStudentsContainer(const StudentsContainer* container) {
    printf("\nСписок студентов:\n");
    for (size_t i = 0; i < container->count; ++i) {
        displayStudent(container->students[i]);
    }
}

bool addStudent(StudentsContainer* container, Student* student) {
    if (container->count >= MAX_STUDENTS)
        return false;

    container->students[container->count] = student;
    container->count++;

    return true;
}

/*------------------------------- Searching -----------------------------*/

Student* searchUnsorted(const StudentsContainer* container, const char* name) {
    for (size_t i = 0; i < container->count; ++i) {
        if (!strcmp(container->students[i]->name, name)) {
            return container->students[i];
        }
    }

    return NULL;
}

Student* searchSorted(const StudentsContainer* container, const char* name) {
    Student* key = createStudent();
    strncpy(key->name, name, MAX_LENGTH_NAME);

    Student** result = bsearch(&key, container->students, container->count, sizeof(Student*), compareStudents);

    freeStudent(key);
    return result ? *result : NULL;
}

/*------------------------------- Sortings ------------------------------*/

void selectionSort(StudentsContainer* container) {
    for (size_t i = 0; i < container->count - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < container->count; ++j) {
            if (container->students[j]->grade < container->students[minIndex]->grade) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Student* temp = container->students[i];
            container->students[i] = container->students[minIndex];
            container->students[minIndex] = temp;
        }
    }
}

void bubbleSort(StudentsContainer* container) {
    for (size_t i = 0; i < container->count - 1; ++i) {
        for (size_t j = 0; j < container->count - i - 1; ++j) {
            if (container->students[j]->grade > container->students[j + 1]->grade) {
                Student* temp = container->students[j];
                container->students[j] = container->students[j + 1];
                container->students[j + 1] = temp;
            }
        }
    }
}

void insertionSort(StudentsContainer* container) {
    for (size_t i = 1; i < container->count; i++) {
        Student* key = container->students[i];
        int j = i - 1;
        while (j >= 0 && container->students[j]->grade > key->grade) {
            container->students[j + 1] = container->students[j];
            --j;
        }
        container->students[j + 1] = key;
    }
}

//------------------------ Work with files --------------------------------

bool writeToFile(const StudentsContainer* container, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file)
        return false;

    int errorStatus = 0;
    for (size_t i = 0; i < container->count; ++i) {
        errorStatus = fprintf(file, "%s %d %.2f\n",
            container->students[i]->name,
            container->students[i]->age,
            container->students[i]->grade
        );
    }

    fclose(file);

    if (errorStatus < 0)
        return false;

    return true;
}

//----------------------------- Printing --------------------------------

void printMenu() {
    printf("\nМеню:\n");
    printf("1. Добавить студента\n");
    printf("2. Вывести список студентов\n");
    printf("3. Поиск студента по имени в неупорядоченном списке\n");
    printf("4. Поиск студента по имени в упорядоченном списке\n");
    printf("5. Сортировка списка студентов:\n");
    printf("6. Записать данные студентов в файл\n");
    printf("0. Выйти\n");
    printf("Введите ваш выбор: ");
}

void printSortMenu() {
    printf("Выберите метод сортировки:\n");
    printf("1. Сортировка выбором\n");
    printf("2. Сортировка обменом\n");
    printf("3. Сортировка вставками\n");
    printf("Введите ваш выбор: ");
}

//----------------------------------------------------------------------

int main() {
    setlocale(LC_ALL, "");

    StudentsContainer* container = createStudentsContainer();

    if (!container)
        return EXIT_FAILURE;

    char name[MAX_LENGTH_NAME];
    int choice;

    do {
        printMenu();

        if (!readInt(&choice))
            choice = -1;

        Student* temp;
        switch (choice) {
        case 1:
            printf("Введите имя студента, возраст и средний балл:\n");
            temp = readStudent();
            if (temp) {
                if (!addStudent(container, temp)) {
                    freeStudent(temp);
                }
            }

            break;
        case 2:
            displayStudentsContainer(container);
            break;
        case 3:
            printf("Введите имя студента для поиска: ");
            readString(name, MAX_LENGTH_NAME);

            temp = searchUnsorted(container, name);
            temp ? displayStudent(temp) : printf("\nСтудент не найден\n");

            break;
        case 4:
            printf("Введите имя студента для поиска: ");
            readString(name, MAX_LENGTH_NAME);

            qsort(container->students, container->count, sizeof(Student*), compareStudents);

            displayStudentsContainer(container);

            temp = searchSorted(container, name);
            temp ? displayStudent(temp) : printf("Студент не найден\n");

            break;
        case 5:
            printSortMenu();
            if (!readInt(&choice))
                break;
            switch (choice) {
            case 1:
                selectionSort(container);
                break;
            case 2:
                bubbleSort(container);
                break;
            case 3:
                insertionSort(container);
                break;
            default:
                printf("Неверный выбор.\n");
            }
            printf("Список студентов после сортировки:\n");
            displayStudentsContainer(container);
            break;
        case 6:
            writeToFile(container, "students.txt") ? printf("Файл записан") : printf("Ошибка записи");
            break;
        case 0:
            printf("До свидания!\n");
            break;
        default:
            printf("Неверный выбор.\n");
        }
    } while (choice != 0);

    freeStudentsContainer(&container);

    return EXIT_SUCCESS;
}
