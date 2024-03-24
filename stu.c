#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
int count = 0;
// Structure to represent a student record
struct Student {
    char name[50];
    int rollNumber;
    char course[50];
    char grades;
    struct Student* next;
};

struct Student* start =NULL;

// Function to insert a student record
void insertRecord(int *count) {
    struct Student* newStudent;
    newStudent = (struct Student*)malloc(sizeof(struct Student));
    
    
    printf("Enter Name: ");
    scanf("%s",&(newStudent->name));
    
    printf("Enter Roll Number: ");
    scanf("%d",&(newStudent->rollNumber));

    printf("Enter Course: ");
    scanf("%s",&(newStudent->course));

    printf("Enter Grades: ");
    scanf("%s",&(newStudent->grades));
    
    newStudent->next = start;
    start = newStudent;

    // Append the new record to the file
    FILE* file = fopen("student_records.txt", "a");
    if (file == NULL) {
        printf("Error opening file for appending.\n");
        return;
    }
    fprintf(file, "%s %d %s %c\n", newStudent->name, newStudent->rollNumber, newStudent->course, newStudent->grades);
    fclose(file);

    count++;
}

int checkValid(int RNum){
    struct Student* trav = start;
    while(trav!=NULL){
        if(trav->rollNumber==RNum){
            return 1;
        }
        trav=trav->next;
    }
    return 0;
}

// Function to delete a student record based on roll number 
void deleteRecord(int *count, int RNum) {
    if(checkValid(RNum)){
        struct Student* trav = start;
        struct Student* prev = NULL;
        while (trav != NULL) {
            if (trav->rollNumber == RNum) {
                if (prev == NULL) {
                    // If the first node matches, update the start pointer
                    start = trav->next;
                }
                else {
                    // If not the first node, update the previous node's next pointer
                    prev->next = trav->next;
                }

                free(trav);
                printf("Record deleted successfully.\n");
                count--;

                // Update the file after deletion
                FILE* file = fopen("student_records.txt", "w");
                if (file == NULL) {
                    printf("Error opening file for writing.\n");
                    return;
                }

                struct Student* current = start;

                while (current != NULL) {
                    fprintf(file, "%s %d %s %c\n", current->name, current->rollNumber, current->course, current->grades);
                    current = current->next;
                }

                fclose(file);
                return;
            }

        prev = trav;
        trav = trav->next;
    }

    printf("Record not found.\n");
}
}
// Function to display all student records
void showRecords(){
    int i = 0;
    struct Student* trav = start;

    if(trav!=NULL){
        printf("Student Records:\n");
        printf("--------------------------------------------------\n");
        printf("Name\t\tRoll Number\t\tCourse\t\tGrades\n");
        printf("--------------------------------------------------\n");
        while(trav!=NULL){
            printf("%s\t\t%d\t\t%s\t\t%c\n",trav->name,trav->rollNumber,trav->course,trav->grades);
            trav=trav->next;
        }
        printf("--------------------------------------------------\n");
    }
    else{
        printf("No records available.\n");
    }
}

// Function to search for a student record based on roll number
void searchRecord(int RNum) {
    struct Student* trav = start;
    if(checkValid(RNum)){
        while(trav->rollNumber!=RNum){
            trav=trav->next;
        }
        printf("Record found:\n");
        printf("--------------------------------------------------\n");
        printf("Name\t\tRoll Number\tCourse\t\tTotal Marks\n");
        printf("--------------------------------------------------\n");
        printf("%s\t\t%d\t\t%s\t\t%c\n", trav->name, trav->rollNumber, trav->course, trav->grades);
        printf("--------------------------------------------------\n");
        return;
    }
    else{
        printf("Record not found!\n");
    }
}

int main() {
    struct Student records[100]; // Assuming a maximum of 100 records
    //int count = 0;
    int choice, rollNumber;

    do {
        printf("\nStudent Record Management System\n");
        printf("1. Insert Record\n");
        printf("2. Delete Record\n");
        printf("3. Show Records\n");
        printf("4. Search Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertRecord(&count);
                break;
            case 2:
                printf("Enter Roll Number to delete: ");
                scanf("%d", &rollNumber);
                deleteRecord(&count, rollNumber);
                break;
            case 3:
                showRecords(&count,rollNumber);
                break;
            case 4:
                printf("Enter Roll Number to search: ");
                scanf("%d", &rollNumber);
                searchRecord(rollNumber);
                break;
            case 5:
                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
    return 0;
}
