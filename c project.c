#include <stdio.h>
#include <string.h>

typedef struct Student
{
    char studentName[50];
    char studentId[15];
    char studentDept[10];
    char studentAddress[100];
    char studentContactNum[15];
    float studentCGPA;
} Student;

void createAccount();
void displayInfo();
void updateInfo();
void deleteInfo();
void searchInfo();

int main()
{
    char option;

    while (1)
    {
        printf("\n\t\t====== Student Management Database System ======\n");
        printf("\n\t\t\t1. Create Student Account");
        printf("\n\t\t\t2. Display All Students Information");
        printf("\n\t\t\t3. Update Student Information");
        printf("\n\t\t\t4. Delete Student Information");
        printf("\n\t\t\t5. Search Student Information");
        printf("\n\t\t\t0. Exit");

        printf("\n\n\n\t\t\tEnter Your Option: ");
        scanf(" %c", &option);

        switch (option)
        {
        case '1':
            createAccount();
            break;
        case '2':
            displayInfo();
            break;
        case '3':
            updateInfo();
            break;
        case '4':
            deleteInfo();
            break;
        case '5':
            searchInfo();
            break;
        case '0':
            printf("\n\t\t\t====== Thank You ======\n");
            return 0;
        default:
            printf("\n\t\t\tInvalid Option, Please Enter the Right Option!\n");
        }
    }
}

void createAccount()
{
    FILE *fileOne = fopen("studentInfo.bin", "ab+");
    if (fileOne == NULL)
    {
        printf("\n\t\t\tError opening the file!\n");
        return;
    }

    Student studentInformation;

    printf("\n\t\t\t====== Create Student Account ======\n");

    printf("\n\t\t\tEnter Student's Name: ");
    getchar();
    fgets(studentInformation.studentName, sizeof(studentInformation.studentName), stdin);
    studentInformation.studentName[strcspn(studentInformation.studentName, "\n")] = '\0';

    printf("\t\t\tEnter Student's ID: ");
    fgets(studentInformation.studentId, sizeof(studentInformation.studentId), stdin);
    studentInformation.studentId[strcspn(studentInformation.studentId, "\n")] = '\0';

    printf("\t\t\tEnter Student's Department: ");
    fgets(studentInformation.studentDept, sizeof(studentInformation.studentDept), stdin);
    studentInformation.studentDept[strcspn(studentInformation.studentDept, "\n")] = '\0';

    printf("\t\t\tEnter Student's Address: ");
    fgets(studentInformation.studentAddress, sizeof(studentInformation.studentAddress), stdin);
    studentInformation.studentAddress[strcspn(studentInformation.studentAddress, "\n")] = '\0';

    printf("\t\t\tEnter Student's Contact Number: ");
    fgets(studentInformation.studentContactNum, sizeof(studentInformation.studentContactNum), stdin);
    studentInformation.studentContactNum[strcspn(studentInformation.studentContactNum, "\n")] = '\0';

    printf("\t\t\tEnter Student's Current CGPA: ");
    scanf("%f", &studentInformation.studentCGPA);

    fwrite(&studentInformation, sizeof(studentInformation), 1, fileOne);

    printf("\n\n\t\t\tInformation has been stored successfully\n");
    fclose(fileOne);
}

void displayInfo()
{
    FILE *fileOne = fopen("studentInfo.bin", "rb");
    if (fileOne == NULL)
    {
        printf("\n\t\t\tError opening the file!\n");
        return;
    }

    Student studentInformation;

    printf("\n\t\t\t====== All Students Information ======\n");

    printf("\n\n\t\t%-20s%-13s%-10s%-25s%-15s%-s\n", "Name", "ID", "Dept.", "Address", "Contact", "CGPA");
    printf("\t\t----------------------------------------------------------------------------------------");

    while (fread(&studentInformation, sizeof(studentInformation), 1, fileOne) == 1)
    {
        printf("\n\n\t\t%-20s%-13s%-10s%-25s%-15s%-.2f", studentInformation.studentName, studentInformation.studentId, studentInformation.studentDept, studentInformation.studentAddress, studentInformation.studentContactNum, studentInformation.studentCGPA);
    }

    printf("\n\n\n\t\t\tEnter any keys to continue.......");
    getchar();
    fclose(fileOne);
}

void updateInfo()
{
    FILE *fileOne = fopen("studentInfo.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");
    if (fileOne == NULL || temp == NULL)
    {
        printf("\n\t\t\tError opening files!\n");
        return;
    }

    Student studentInformation, tempInformation;

    int choice, flag = 0;

    printf("\n\t\t\t====== Update Students Information ======\n");

    printf("\n\t\t\tEnter Student's ID: ");
    getchar();
    fgets(tempInformation.studentId, sizeof(tempInformation.studentId), stdin);
    tempInformation.studentId[strcspn(tempInformation.studentId, "\n")] = '\0';

    while (fread(&studentInformation, sizeof(studentInformation), 1, fileOne) == 1)
    {
        if (strcmp(studentInformation.studentId, tempInformation.studentId) == 0)
        {
            flag++;
            printf("\n\t\t\tChoose your option :\n\t\t\t1. Update Student Name\n\t\t\t2. Update Student Dept.\n\t\t\t3. Update Student Address\n\t\t\t4. Update Student Contact No.\n\t\t\t5. Update Student CGPA");
            printf("\n\n\t\t\tEnter Your Option : ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("\n\t\t\tEnter Student's Name to Update: ");
                getchar();
                fgets(tempInformation.studentName, sizeof(tempInformation.studentName), stdin);
                tempInformation.studentName[strcspn(tempInformation.studentName, "\n")] = '\0';
                strcpy(studentInformation.studentName, tempInformation.studentName);
            }
            else if (choice == 2)
            {
                printf("\n\t\t\tEnter Student's Dept. to Update: ");
                getchar();
                fgets(tempInformation.studentDept, sizeof(tempInformation.studentDept), stdin);
                tempInformation.studentDept[strcspn(tempInformation.studentDept, "\n")] = '\0';
                strcpy(studentInformation.studentDept, tempInformation.studentDept);
            }
            else if (choice == 3)
            {
                printf("\n\t\t\tEnter Student's Address to Update: ");
                getchar();
                fgets(tempInformation.studentAddress, sizeof(tempInformation.studentAddress), stdin);
                tempInformation.studentAddress[strcspn(tempInformation.studentAddress, "\n")] = '\0';
                strcpy(studentInformation.studentAddress, tempInformation.studentAddress);
            }

            else if (choice == 4)
            {
                printf("\n\t\t\tEnter Student's Contact No. to Update: ");
                getchar();
                fgets(tempInformation.studentContactNum, sizeof(tempInformation.studentContactNum), stdin);
                tempInformation.studentContactNum[strcspn(tempInformation.studentContactNum, "\n")] = '\0';
                strcpy(studentInformation.studentContactNum, tempInformation.studentContactNum);
            }
            else if (choice == 5)
            {
                printf("\n\t\t\tEnter Student's CGPA to Update: ");
                scanf("%f", &tempInformation.studentCGPA);
                studentInformation.studentCGPA = tempInformation.studentCGPA;
            }
            else
            {
                printf("\n\t\t\tInvalid Option.\n");
            }
        }

        fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
    }

    if (flag == 0)
    {
        printf("\n\t\t\tStudent Id is not found\n");
    }

    fclose(fileOne);
    fclose(temp);

    remove("studentInfo.bin");
    rename("temp.bin", "studentInfo.bin");

    printf("\n\t\t\tEnter any keys to continue.......");
    getchar();
}

void deleteInfo()
{
    FILE *fileOne = fopen("studentInfo.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");
    if (fileOne == NULL || temp == NULL)
    {
        printf("\n\t\t\tError opening files!\n");
        return;
    }

    Student studentInformation, tempInformation;

    int choice, flag = 0;

    printf("\n\t\t\t====== Delete Student Information ======\n");

    printf("\n\t\t\tEnter Student's ID: ");
    getchar();
    fgets(tempInformation.studentId, sizeof(tempInformation.studentId), stdin);
    tempInformation.studentId[strcspn(tempInformation.studentId, "\n")] = '\0';

    while (fread(&studentInformation, sizeof(studentInformation), 1, fileOne) == 1)
    {
        if (strcmp(studentInformation.studentId, tempInformation.studentId) == 0)
        {
            flag++;
            printf("\n\t\t\tAre you sure to delete?\n\t\t\t1. Yes\n\t\t\t2. Back\n\t\t\tEnter Your Option: ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("\n\n\t\t\tInformation has been deleted successfully!\n");
            }
            else if (choice == 2)
            {
                fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
            }
            else
            {
                printf("\n\t\t\tInvalid Option.\n");
                fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
            }
        }
        else
        {
            fwrite(&studentInformation, sizeof(studentInformation), 1, temp);
        }
    }

    if (flag == 0)
    {
        printf("\n\t\t\tStudent Id is not found\n");
    }

    fclose(fileOne);
    fclose(temp);

    remove("studentInfo.bin");
    rename("temp.bin", "studentInfo.bin");

    printf("\n\t\t\tEnter any keys to continue.......");
    getchar();
}

void searchInfo()
{
    FILE *fileOne = fopen("studentInfo.bin", "rb");
    if (fileOne == NULL)
    {
        printf("\n\t\t\tError opening the file!\n");
        return;
    }

    Student studentInformation;
    int choice, flag = 0;
    char studentID[15], studentDept[10];

    printf("\n\t\t\t====== Search Student Information ======\n");

    printf("\n\t\t\tChoose your option:\n\t\t\t1. Search by Student ID\n\t\t\t2. Search by Student Dept.");
    printf("\n\n\t\t\tEnter Your Option: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("\n\t\t\tEnter Student ID: ");
        getchar();
        fgets(studentID, sizeof(studentID), stdin);
        studentID[strcspn(studentID, "\n")] = '\0';

        while (fread(&studentInformation, sizeof(studentInformation), 1, fileOne) == 1)
        {
            if (strcmp(studentInformation.studentId, studentID) == 0)
            {
                flag++;
                printf("\n\t\t\tStudent Name: %s\n\t\t\tStudent ID: %s\n\t\t\tStudent Dept.: %s\n\t\t\tStudent Address: %s\n\t\t\tStudent Contact No.: %s\n\t\t\tStudent CGPA: %.2f\n",
                    studentInformation.studentName, studentInformation.studentId, studentInformation.studentDept,
                    studentInformation.studentAddress, studentInformation.studentContactNum, studentInformation.studentCGPA);
            }
        }
    }
    else if (choice == 2)
    {
        printf("\n\t\t\tEnter Student Dept.: ");
        getchar();
        fgets(studentDept, sizeof(studentDept), stdin);
        studentDept[strcspn(studentDept, "\n")] = '\0';

        printf("\n\n\t\t%-20s%-13s%-10s%-25s%-15s%-s\n", "Name", "ID", "Dept.", "Address", "Contact", "CGPA");
        printf("\t\t----------------------------------------------------------------------------------------");

        while (fread(&studentInformation, sizeof(studentInformation), 1, fileOne) == 1)
        {
            if (strcmp(studentInformation.studentDept, studentDept) == 0)
            {
                flag++;
                printf("\n\n\t\t%-20s%-13s%-10s%-25s%-15s%-.2f", studentInformation.studentName, studentInformation.studentId, studentInformation.studentDept, studentInformation.studentAddress, studentInformation.studentContactNum, studentInformation.studentCGPA);
            }
        }
    }
    else
    {
        printf("\n\t\t\tInvalid Option\n");
    }

    if (flag == 0)
    {
        printf("\n\t\t\tNo matching record found\n");
    }

    fclose(fileOne);

    printf("\n\n\t\t\tEnter any keys to continue.......");
    getchar();
}
