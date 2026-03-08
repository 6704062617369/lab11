#include <stdio.h>
#include <stdlib.h>

#define NUM_STUDENTS 10
#define NUM_EXAMS 3

typedef struct
{
    char name[100];
    int scores[NUM_EXAMS];
} Student;

void writeData();
void readAndProcessData();

int main()
{
    printf("Student Record System\n");
    writeData();
    printf("\nProcessing Results\n");
    readAndProcessData();
    return 0;
}

void writeData()
{
    FILE *fp;
    Student std[NUM_STUDENTS];

    fp = fopen(".\\lab11\\no2\\std10.dat", "wb");
    if (fp == NULL)
    {
        printf("Error\n");
        exit(1);
    }

    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        printf("\nStudent #%d\n", i + 1);
        printf("Enter Full Name: ");
        scanf(" %[^\n]s", std[i].name);

        for (int j = 0; j < NUM_EXAMS; j++)
        {
            printf("Exam score #%d: ", j + 1);
            scanf("%d", &std[i].scores[j]);
        }
    }

    fwrite(std, sizeof(Student), NUM_STUDENTS, fp);
    fclose(fp);
}

void readAndProcessData()
{
    FILE *fp;
    Student std[NUM_STUDENTS];

    fp = fopen(".\\lab11\\no2\\std10.dat", "rb");
    if (fp == NULL)
    {
        printf("Error\n");
        exit(1);
    }

    fread(std, sizeof(Student), NUM_STUDENTS, fp);

    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        int total = 0;
        int lowScoreCount = 0;

        printf("\n----------------------------\n");
        printf("Name: %s\n", std[i].name);

        printf("Scores < 10: ");
        for (int j = 0; j < NUM_EXAMS; j++)
        {
            total += std[i].scores[j];
            if (std[i].scores[j] < 10)
            {
                printf("[Exam %d: %d] ", j + 1, std[i].scores[j]);
                lowScoreCount++;
            }
        }

        if (lowScoreCount == 0)
        {
            printf("None");
        }

        float average = (float)total / NUM_EXAMS;
        printf("\nTotal Score: %d", total);
        printf("\nAverage Score: %.2f\n", average);
    }

    fclose(fp);
}
