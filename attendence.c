#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_NAME_LENGTH 50
#define MAX_DEPARTMENT_LENGTH 50
#define MAX_PHONE_LENGTH 15
#define MAX_LINE_LENGTH 256

typedef struct {
    char name[MAX_NAME_LENGTH];
    int usn;
    char department[MAX_DEPARTMENT_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    int pa;
} Student;

int main() {
    const char *filename = "student_details.txt";
    FILE *file = fopen(filename, "r+");
    if (!file) {
        fprintf(stderr, "Error opening file: %s (%s)\n", filename, strerror(errno));
        return 1;
    }

    Student students[4];
    char line[MAX_LINE_LENGTH];

    int i = 0;
    while (i < 4 && fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "%49s %d %14s %49s %d", students[i].name, &students[i].usn, students[i].phone, students[i].department, &students[i].pa) != 5) {
            fprintf(stderr, "Error parsing line %d\n", i+1);
            return 1;
        }
        i++;
    }

    rewind(file);
    for (int j = 0; j < 5; j++) {
        printf("Enter present/absent status for %s (P/A): ", students[j].name);
        char status;
        fflush(stdin);
        scanf("%c", &status);
        if (status == 'p' || status == 'P') {
            students[j].pa = 1;
        } else if (status == 'a' || status == 'A') {
            students[j].pa = 0;
        } else {
            printf("Invalid input. Please enter P or A.\n");
            continue;
        }

        printf("%s\n", (students[j].pa == 1) ? "Present" : "Absent");

        fprintf(file, "%s\t %d\t %s\t %s\t %d\n", students[j].name, students[j].usn, students[j].phone, students[j].department, students[j].pa);
    }

    fclose(file);
    return 0;
}
