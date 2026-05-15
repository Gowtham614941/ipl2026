#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[30];
    float gpa;
} Student;

void storeRecords(int n,const char *filename);
void getRecord(int m,const char *filename);
void deleteRecord(int m,const char *filename);

int main() 
{
    const char *filename = "students.dat";
    int n, m, choice,idtodel;
 
    printf("Enter number of records to store: ");
    scanf("%d", &n);
    storeRecords(n,filename);

    printf("\nEnter record number to retrieve: ");
    scanf("%d", &m);
    getRecord(m,filename);

    printf("\nEnter record number to delete: ");
    scanf("%d", &idtodel);


    deleteRecord(idtodel,filename);

    return 0;
}


void storeRecords(int n,const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) return;

    Student s;
    for (int i = 0; i < n; i++) {
        printf("Enter ID, Name, GPA for student %d: ", i + 1);
        scanf("%d %s %f", &s.id, s.name, &s.gpa);
        fwrite(&s, sizeof(Student), 1, fp);
    }
    fclose(fp);
}


void getRecord(int m,const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return;

    Student s;
    // Seek to (m-1) * size of one structure
    fseek(fp, (m - 1) * sizeof(Student), SEEK_SET);

    if (fread(&s, sizeof(Student), 1, fp)) {
        printf("\nRecord %d: ID=%d, Name=%s, GPA=%.2f\n", m, s.id, s.name, s.gpa);
    } else {
        printf("\nRecord not found.\n");
    }
    fclose(fp);
}


void deleteRecord(int targetId,const char *filename) {
    FILE *fp = fopen(filename, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (!fp || !temp) {
        printf("Error opening files.\n");
        return;
    }
    Student s;
    int found = 0;

    // Read every record from the source file
    while (fread(&s, sizeof(Student), 1, fp)) {
        
        if (s.id == targetId) {
            found = 1;
        } else {
            fwrite(&s, sizeof(Student), 1, temp);
        }
    }

    
    fclose(fp);  
    fclose(temp);
     
    
    remove(filename);
    rename("temp.dat", filename);

    if (found) {
        printf("Record with ID %d deleted.\n", targetId);
    } else {
        printf("Record with ID %d not found.\n", targetId);
    }
    printf("\n--- Updated Records ---\n");
    FILE *finalFp = fopen(filename, "rb");
    if (finalFp) {
        int i = 1;
        while (fread(&s, sizeof(Student), 1, finalFp)) {
            printf("Record %d: ID=%d, Name=%s, GPA=%.2f\n", i++, s.id, s.name, s.gpa);
        }
    fclose(finalFp);
    }
}