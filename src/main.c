#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int numberOfStd = 0;

typedef struct
{
    float chinese;
    float math;
    float english;
    float total;
    int ID;
    char name[25];
} Std;
Std stds[60]; // 主数组
/* index
chinese: 1,
math: 2,
English: 3,
total: 4,
ID: 5,
name: 6
*/

void getHomepage();                        // draw homepage
void getSheet();                           // get all sheet
int inputRecord();                         // input students infor
int getTotalAverage();                     // index ditto
int sortBy(int subject, int mode);         // mode => descending:0, ascending:1, subject ditto
int searchBy(int index);                   // searchBy by ID:5, name:6
int statisticAnaly();                      // analysis statistic
int getAll();                              // get all student infor list
void *getMember(Std *student, int member); // get struct member int index ditto

int main()
{
    enum SUBJECT
    {
        CH = 1,
        MA,
        EN,
        TOTAL,
        ID,
        NAME
    };
    enum MODE
    {
        descending,
        ascending
    };
    while (1)
    {
        getHomepage();
        int index = 0;
        scanf("%d", &index);
        switch (index)
        {
        case 0:
            exit(0);
        case 1:
            inputRecord();
            break;
        case 2:
            getTotalAverage();
            break;
        case 3:
            sortBy(TOTAL, descending);
            break;
        case 4:
            sortBy(TOTAL, ascending);
            break;
        case 5:
            sortBy(ID, ascending);
            break;
        case 6:
            sortBy(NAME, ascending);
            break;
        case 7:
            searchBy(ID);
            break;
        case 8:
            searchBy(NAME);
            break;
        case 9:
            statisticAnaly();
            break;
        case 10:
            getAll();
            break;
        default:
            break;
        }
    }
}

void getHomepage()
{
    system("cls");
    printf("1.Input record\n");
    printf("2.Calculate total and average score of course\n");
    printf("3.Sort in descending order by score\n");
    printf("4.Sort in asending order by score\n");
    printf("5.Sort in ascending order by number\n");
    printf("6.Sort in dictionary order by name\n");
    printf("7.Search by number\n");
    printf("8.Search by name\n");
    printf("9.Statistic analysis\n");
    printf("10.List record\n");
    printf("0.Exit\n");
    printf("Please enter your choice:\n");
}

int inputRecord()
{
    while (1)
    {
        system("cls");
        int temp = 0;
        printf("Enter ID(Enter -1 to stop input.):\n");
        scanf("%d", &temp);
        if (temp == -1)
            goto end;
        stds[numberOfStd].ID = temp;
        printf("Enter name:\n");
        scanf("%s", &stds[numberOfStd].name);
        printf("Enter chinese score:\n");
        scanf("%d", &stds[numberOfStd].chinese);
        printf("Enter math score:\n");
        scanf("%d", &stds[numberOfStd].math);
        printf("Enter English score:\n");
        scanf("%d", &stds[numberOfStd].english);
        numberOfStd++;
    }
end:
    return 0;
}

int getTotalAverage()
{
    system("cls");
    int subject = 0;
    int mode = 0;
    printf("get CH:1,MA:2,EN:3,Total:4,ID:5\n");
    scanf("%d", &subject);
    printf("descending:0, ascending:1\n");
    scanf("%d", &mode);
    for (int i = 0; i < numberOfStd; ++i)
    {
    }
}

void getSheet()
{
    ;
}

void *getMember(Std *student, int member)
{
    void *p = NULL;
}