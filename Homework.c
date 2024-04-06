#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int age;
    float salary;
} Employee;

int compareNames(const void *a, const void *b) {
    const Employee *employeeA = (const Employee *)a;
    const Employee *employeeB = (const Employee *)b;
    return strcmp(employeeA->name, employeeB->name);
}

int compareAges(const void *a, const void *b) {
    const Employee *employeeA = (const Employee *)a;
    const Employee *employeeB = (const Employee *)b;
    return employeeB->age - employeeA->age;
}

int loadNumberOfEmployees(const char *filename) {
    FILE *file = fopen(filename, "r");
    int n;
    fscanf(file, "%d", &n);
    fclose(file);
    return n;
}

void inputEmployeeData(Employee *employees, int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter name, age, and annual salary for employee #%d: ", i + 1);
        scanf("%99s %d %f", employees[i].name, &employees[i].age, &employees[i].salary);
    }
}

void writeEmployeesToFile(Employee *employees, int n, const char *filename) {
    FILE *file = fopen(filename, "w");
    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(file, "%s %d %.2f\n", employees[i].name, employees[i].age, employees[i].salary);
    }
    fclose(file);
}

void writeNamesToFile(Employee *employees, int n, const char *filename) {
    qsort(employees, n, sizeof(Employee), compareNames);
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < n; i++) {
        fprintf(file, "%s\n", employees[i].name);
    }
    fclose(file);
}

void writeAgesToFile(Employee *employees, int n, const char *filename) {
    qsort(employees, n, sizeof(Employee), compareAges);
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", employees[i].age);
    }
    fclose(file);
}

int main() {
    char filename[] = "number.txt";
    int n = loadNumberOfEmployees(filename);

    Employee *employees = (Employee *)malloc(n * sizeof(Employee));

    inputEmployeeData(employees, n);
    writeEmployeesToFile(employees, n, filename);
    writeNamesToFile(employees, n, "names.txt");
    writeAgesToFile(employees, n, "ages.txt");

    free(employees);

    return 0;
}
