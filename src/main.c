#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEVEL 5

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
chinese: 1, math: 2, English: 3, total: 4, ID: 5, name: 6
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
int compare(void *a, void *b, int type);
void swap(Std *a, Std *b);

int main()
{
    enum INDEX
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
        stds[numberOfStd].total = stds[numberOfStd].chinese + stds[numberOfStd].math + stds[numberOfStd].english;
        numberOfStd++;
    }
end:
    return 0;
}

int getTotalAverage()
{
    enum MODE
    {
        total,
        average
    };
    system("cls");
    int subject = 0;
    int mode = 0;
    printf("get CH:1,MA:2,EN:3,Total:4,ID:5\n");
    scanf("%d", &subject);
    printf("total:0, average:1\n");
    scanf("%d", &mode);
    float score = 0;
    for (int i = 0; i < numberOfStd; ++i)
        score += *(float *)getMember(&stds[i], subject);
    if (mode == total)
        score /= numberOfStd;
    getSheet();
    return 0;
}

int sortBy(int subject, int mode)
{
    for (int i = 0; i < numberOfStd - 1; ++i)
        for (int j = 0; j < numberOfStd - i - 1; ++j)
            if (compare(getMember(&stds[j], mode), getMember(&stds[j + 1], mode), mode) > 0)
                swap(&stds[j], &stds[j + 1]);
}

int searchBy(int index)
{
    enum INDEX
    {
        ID = 5,
        NAME
    };
    Std *result;
    void *query_p = NULL;
    printf("Enter the name or ID you want to query:\n");
    if (index == ID)
        scanf("%d", query_p);
    else if (index == NAME)
        scanf("%s", query_p);
    for (int i = 0; i < numberOfStd; ++i)
        if (!compare(getMember(&stds[i], index), query_p, index))
        {
            result = &stds[i];
            break;
        }
    getSheet();
}

int statisticAnaly()
{
    int statistic[LEVEL] = {0};
    for (int i = 0; i < numberOfStd; ++i)
        if (stds[i].total > 89 && stds[i].total < 101)
            statistic[0]++;
        else if (stds[i].total > 79 && stds[i].total < 90)
            statistic[1]++;
        else if (stds[i].total > 69 && stds[i].total < 80)
            statistic[2]++;
        else if (stds[i].total > 59 && stds[i].total < 70)
            statistic[3]++;
        else if (stds[i].total < 60)
            statistic[4]++;
    getSheet();
}

int getAll()
{
    getSheet();
}

void getSheet()
{
    ;
}

int compare(void *a, void *b, int type)
{
    int ret = 0;
    if (type <= 4)
        ret = (int)(*(float *)a - *(float *)b);
    else if (type == 5)
        ret = *(int *)a - *(int *)b;
    else if (type == 6)
        ret = strcmp((char *)a, (char *)b);
    return ret;
}

void swap(Std *a, Std *b)
{
    Std temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void *getMember(Std *student, int member)
{
    void *p = NULL;
    if (member <= 4)
        p = (float *)student + member - 1;
    if (member == 5)
        p = &(student->ID);
    if (member == 6)
        p = &(student->name);
    return p;
}