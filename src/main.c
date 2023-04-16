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

void getHomepage();                                                                         // draw homepage
void getSheet(void *p, int rows, int cols, char **colheader, char **rowheader, char *type); // get all sheet
int inputRecord();                                                                          // input students infor
int getTotalAverage();                                                                      // index ditto
int sortBy(int subject, int mode);                                                          // mode => descending:0, ascending:1, subject ditto
int searchBy(int index);                                                                    // searchBy by ID:5, name:6
int statisticAnaly();                                                                       // analysis statistic
int getAll();                                                                               // get all student infor list
void *getMember(Std *student, int member);                                                  // get struct member int index ditto
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
    system("pause");
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
        scanf("%s", stds[numberOfStd].name);
        printf("Enter chinese score:\n");
        scanf("%f", &stds[numberOfStd].chinese);
        printf("Enter math score:\n");
        scanf("%f", &stds[numberOfStd].math);
        printf("Enter English score:\n");
        scanf("%f", &stds[numberOfStd].english);
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
    float score[2][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}};
    // float score[2][5] = {0};
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < numberOfStd; ++j)
            score[0][i] = *(float *)getMember(&stds[j], i + 1);
        score[1][i] = score[0][i] / numberOfStd;
    }

    char *colheader[] = {"chinese", "math", "english", "total"};
    char *rowheader[] = {"total", "average"};
    getSheet(score, 2, 4, colheader, rowheader, "float");
    return 0;
}

int sortBy(int subject, int mode)
{
    for (int i = 0; i < numberOfStd - 1; ++i)
        for (int j = 0; j < numberOfStd - i - 1; ++j)
            if (compare(getMember(&stds[j], mode), getMember(&stds[j + 1], mode), mode) > 0)
                swap(&stds[j], &stds[j + 1]);
    char *colheader[] = {"ID", "name", "chinese", "math", "english", "total"};
    char *rowheader[] = {"0"};
    getSheet(stds, numberOfStd, 6, colheader, rowheader, "struct");
    return 0;
}

int searchBy(int index)
{
    enum INDEX
    {
        ID = 5,
        NAME
    };
    Std *result = (Std *)malloc(sizeof(Std));
    void *query_p = calloc(25, sizeof(char));

    if (index == ID)
    {
        printf("Enter the ID you want to query:\n");
        scanf("%d", (int *)query_p);
    }
    else if (index == NAME)
    {
        printf("Enter the name you want to query:\n");
        scanf("%s", (char *)query_p);
    }
    for (int i = 0; i < numberOfStd; ++i)
        if (!compare(getMember(&stds[i], index), query_p, index))
        {
            result[0] = stds[i];
            break;
        }
    free(query_p);
    char *colheader[] = {"ID", "name", "chinese", "math", "english", "total"};
    char *rowheader[] = {"0"};
    getSheet(result, 1, 6, colheader, rowheader, "struct");
    return 0;
}

int statisticAnaly()
{
    int statistic[2][LEVEL] = {0};
    for (int i = 0; i < numberOfStd; ++i)
        if (stds[i].total > 89 && stds[i].total < 101)
            statistic[0][0]++;
        else if (stds[i].total > 79 && stds[i].total < 90)
            statistic[0][1]++;
        else if (stds[i].total > 69 && stds[i].total < 80)
            statistic[0][2]++;
        else if (stds[i].total > 59 && stds[i].total < 70)
            statistic[0][3]++;
        else if (stds[i].total < 60)
            statistic[0][4]++;
    char *colheader[] = {"excellent", "good", "fair", "pass", "fail"};
    char *rowheader[] = {"number", "ratio"};
    getSheet(statistic, 2, 5, colheader, rowheader, "int");
    return 0;
}

int getAll()
{
    char *colheader[] = {"ID", "name", "chinese", "math", "english", "total"};
    char *rowheader[] = {"0"};
    getSheet(stds, numberOfStd, 6, colheader, rowheader, "struct");
    return 0;
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

void getSheet(void *p, int rows, int cols, char **colheader, char **rowheader, char *type)
{
    // judge type
    if (strcmp(type, "int") == 0)
    {
        int *arr = (int *)p;
        printf("%10s", "");
        for (int i = 0; i < cols; i++)
            printf("%10s", colheader[i]);
        printf("\n");
        // print rowheader and data
        for (int i = 0; i < rows; i++)
        {
            printf("%10s", rowheader[i]);
            for (int j = 0; j < cols; j++)
                printf("%10d", arr[i * cols + j]);
            printf("\n");
        }
    }
    else if (strcmp(type, "float") == 0)
    {
        float *arr = (float *)p;
        // print colheader
        printf("%10s", "");
        for (int i = 0; i < cols; i++)
            printf("%10s", colheader[i]);
        printf("\n");
        for (int i = 0; i < rows; i++)
        {
            printf("%10s", rowheader[i]);
            for (int j = 0; j < cols; j++)
                printf("%10.2f", arr[i * cols + j]);
            printf("\n");
        }
    }
    else if (strcmp(type, "char") == 0)
    {
        char *arr = (char *)p;
        // print colheader
        printf("%10s", "");
        for (int i = 0; i < cols; i++)
            printf("%10s", colheader[i]);
        printf("\n");
        for (int i = 0; i < rows; i++)
        {
            printf("%10s", rowheader[i]);
            for (int j = 0; j < cols; j++)
                printf("%10c", arr[i * cols + j]);
            printf("\n");
        }
    }
    else if (strcmp("struct", type) == 0)
    {
        Std *arr = (Std *)p;
        for (int i = 0; i < rows; ++i)
            printf("%d %s %f %f %f %f ", arr[i].ID, arr[i].name, arr[i].chinese, arr[i].math, arr[i].english, arr[i].total);
    }
    else
        printf("Unsupported type: %s\n", type);
    system("pause");
}