#include <stdio.h>

#define MAX_NAME_LENGTH 50
#define MAX_DEPARTMENT_LENGTH 50
#define MAX_PHONE_LENGTH 15

struct student {
    char name[MAX_NAME_LENGTH];
    int usn;
    char department[MAX_DEPARTMENT_LENGTH];
    char phone[MAX_PHONE_LENGTH];
};

int main() {
    int numStudents;
    char department[MAX_DEPARTMENT_LENGTH];
    FILE *file = fopen("student_details.txt", "a");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    printf("Choose the department:\n");
    printf("1. AIML\n2. CS\n");
    int departmentChoice;
    scanf("%d", &departmentChoice);

    switch (departmentChoice) {
        case 1:
            strcpy(department, "AIML");
            break;
        case 2:
            strcpy(department, "CS");
            break;
        default:
            printf("Invalid department choice\n");
            fclose(file);
            return 1;
    }

    printf("Enter the number of students: ");
    scanf("%d", &numStudents);

    struct student students[numStudents];

    for (int i = 0; i < numStudents; i++) {
        printf("Enter student %d's name: ", i + 1);
        scanf("%49s", students[i].name);
        printf("Enter student %d's USN: ", i + 1);
        scanf("%d", &students[i].usn);
        printf("Enter student %d's department: %s\n", i + 1, department);
        printf("Enter student %d's phone number: ", i + 1);
        scanf("%14s", students[i].phone);
        strcpy(students[i].department, department);
    }

    printf("\nAttendance Registered to file:\n");
    for (int i = 0; i < numStudents; i++) {
        fprintf(file, "%s\t %d\t %s\t %s\t %d\n", students[i].name, students[i].usn, students[i].phone, students[i].department,0);
    }

    fclose(file);
    return 0;
}

