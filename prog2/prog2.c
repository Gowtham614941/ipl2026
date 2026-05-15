#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    float gpa;
} Student;


void input_records(Student* data, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Entry %d ---\n", i + 1);
        printf("Enter ID: ");
        scanf("%d", &data[i].id);
        
        printf("Enter Name: ");
        scanf(" %[^\n]s", data[i].name); 
        
        printf("Enter GPA: ");
        scanf("%f", &data[i].gpa);
    }
}


long* create_indexed_file(const char* filename, Student* data, int n) {
    FILE* fp = fopen(filename, "w");
    if (!fp) return NULL;

    long* positions = malloc(n * sizeof(long));

    for (int i = 0; i < n; i++) {
   
        positions[i] = ftell(fp);
        
   
        fprintf(fp, "%d %s %.2f\n", data[i].id, data[i].name, data[i].gpa);
    }

    fclose(fp);
    return positions;
}


void display_record_at(const char* filename, long pos) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return;

    fseek(fp, pos, SEEK_SET);

    int id;
    char name[50];
    float gpa;

    if (fscanf(fp, "%d %s %f", &id, name, &gpa) == 3) {
        printf("\n[Seek Success] Offset %ld -> ID: %d, Name: %s, GPA: %.2f\n", pos, id, name, gpa);
    } else {
        printf("\nError reading record at position %ld\n", pos);
    }

    fclose(fp);
}

int main() {
    int n;
    const char* db_file = "students.txt";

    printf("Enter number of records to create: ");
    scanf("%d", &n);


    Student* list = (Student*)malloc(n * sizeof(Student));


    input_records(list, n);


    long* seek_positions = create_indexed_file(db_file, list, n);


    if (n > 0) {
        int choice;
        printf("\nEnter record index to retrieve (0 to %d): ", n - 1);
        scanf("%d", &choice);

        if (choice >= 0 && choice < n) {
            display_record_at(db_file, seek_positions[choice]);
        } else {
            printf("Invalid index.\n");
        }
    }


    free(list);
    free(seek_positions);
    return 0;
}