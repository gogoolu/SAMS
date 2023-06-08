#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedList.h"

#define LEVEL 5
int numberOfStd = 0;
Head* head = NULL;

Std stds[60]; // 主数组
/* index
chinese: 1, math: 2, English: 3, total: 4, ID: 5, name: 6
*/
#define DECLARE(type)       \
int scan_##type(type *p);   \

#define DEFINE(type,FMT)                                \
int scan_##type(type *p)                                \
{                                                       \
    int ret = 0;                                        \
    do{                                                 \
        ret = scanf(FMT, p);                            \
        fflush(stdin);                                  \
        if(ret != 1)                                    \
            printf("Invalid input! please re-enter.\n");\
    } while (ret != 1);                                 \
    return 0;                                           \
}                                                       \
DECLARE(int)
DECLARE(float)
DECLARE(char)

DEFINE(int,"%d")
DEFINE(float,"%f")
DEFINE(char,"%s")

void getHomepage();
int inputRecord();                  // input students infor
int getTotalAverage();              // index ditto
int sortBy(int subject, int mode);  // mode => ascending:1, descending:0, subject ditto
int searchBy(int index);            // searchBy by ID:5, name:6
int statisticAnaly();               // analysis statistic
int getAll();                       // get all student infor list
// int fileIO(int mode);               // read file and write file. read: 0, wirte: 1
void getSheet(void *p, int rows, int cols, char **colheader, char **rowheader, char *type);
void *getMember(Std *student, int member);  // get struct member, index ditto
int compare(void *a, void *b, int type);
void swap(Std *a, Std *b);

enum INDEX { CH = 1, MA, EN, TOTAL, ID, NAME };

int main()
{
    head = initHead();
    enum MODE { ascending, descending};
    while (1)
    {
        getHomepage();
        int index = 0;
        scan_int(&index);
        switch (index) {
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


int inputRecord()
{
    while (1)
    {
        system("cls");
        int temp = 0;
        printf("Enter ID(Enter -1 to stop input.):\n");
        scan_int(&temp);
        if (temp == -1)
            goto end;
        Std newStu;
        addNode(head, &newStu);
        for (int i = 0; i < numberOfStd; ++i)
            // if (temp == *(int *)getMember(&(getNode(head, i)->data), ID)) {
            if (temp == getNode(head, i)->data.ID) {
                printf("Duplicate ID!\n");
                system("pause");
                goto end;
            }
        getNode(head, numberOfStd)->data.ID = temp;
        printf("Enter name:\n");
        scan_char(getNode(head, numberOfStd)->data.name);
        printf("Enter chinese score:\n");
        scan_float(&(getNode(head, numberOfStd)->data.chinese));
        printf("Enter math score:\n");
        scan_float(&(getNode(head, numberOfStd)->data.math));
        printf("Enter English score:\n");
        scan_float(&(getNode(head, numberOfStd)->data.english));
        getNode(head, numberOfStd)->data.total = getNode(head, numberOfStd)->data.chinese + getNode(head, numberOfStd)->data.math + getNode(head, numberOfStd)->data.english;
        numberOfStd++;
    }
end:
    return 0;
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
    printf("11.Write to a file");
    printf("12.Read from a file");
    printf("0.Exit\n");
    printf("Please enter your choice:\n");
}

int getTotalAverage()
{
    if (numberOfStd == 0) {
        printf("Student information has not been entered yet\n");
        system("pause");
        goto end;
    }
    enum MODE { total, average };
    system("cls");
    float score[2][4] = {0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < numberOfStd; ++j)
            score[0][i] += *(float *)getMember(&(getNode(head, j)->data), i + 1);
            
        score[1][i] = score[0][i] / numberOfStd;
    }
    char *colheader[] = {"chinese", "math", "english", "total"};
    char *rowheader[] = {"total", "average"};
    getSheet(score, 2, 4, colheader, rowheader, "float");
end:
    return 0;
}

int sortBy(int subject, int mode)
{
    if (numberOfStd == 0) {
        printf("Student information has not been entered yet\n");
        system("pause");
        goto end;
    }
    for (int i = 0; i < numberOfStd - 1; ++i)
        for (int j = 0; j < numberOfStd - i - 1; ++j)
            if (mode == 0) {
                if (compare(getMember(&(getNode(head, j)->data), subject), getMember(&(getNode(head, j+1)->data), subject), subject) > 0)
                    swap(&(getNode(head, j)->data), &(getNode(head, j+1)->data));
            } else {
                if (compare(getMember(&(getNode(head, j)->data), subject), getMember(&(getNode(head, j+1)->data), subject), subject) < 0)
                    swap(&(getNode(head, j)->data), &(getNode(head, j+1)->data));
            }
    char *colheader[] = {"ID", "name", "chinese", "math", "english", "total"};
    char *rowheader[] = {"0"};
    getSheet(head, numberOfStd, 6, colheader, rowheader, "struct linkedList");
end:
    return 0;
}

int searchBy(int index)
{
    int flag = 0;
    if (numberOfStd == 0) {
        printf("Student information has not been entered yet\n");
        system("pause");
        goto end;
    }
    enum INDEX { ID = 5, NAME };
    Std *result = (Std *)malloc(sizeof(Std));
    void *query_p = calloc(25, sizeof(char));
    if (index == ID) {
        printf("Enter the ID you want to query:\n");
        scan_int(query_p);
    }
    else if (index == NAME) {
        printf("Enter the name you want to query:\n");
        scan_char(query_p);
    }
    for (int i = 0; i < numberOfStd; ++i)
        if (!compare(getMember(&(getNode(head, i)->data), index), query_p, index)) {
            result[0] = getNode(head, i)->data;
            flag = 1;
            break;
        }
    free(query_p);
    if (!flag) {
        printf("The search object does not exist!\n");
        system("pause");
        goto end;
    }
    char *colheader[] = {"ID", "name", "chinese", "math", "english", "total"};
    char *rowheader[] = {"0"};
    getSheet(result, 1, 6, colheader, rowheader, "struct array");
end:
    return 0;
}

int statisticAnaly()
{
    if (numberOfStd == 0) {
        printf("Student information has not been entered yet\n");
        system("pause");
        goto end;
    }
    int statistic[2][LEVEL] = {0};
    for (int i = 0; i < numberOfStd; ++i)
        if (getNode(head, i)->data.total > 269 && getNode(head, i)->data.total < 301)
            statistic[0][0]++;
        else if (getNode(head, i)->data.total > 239 && getNode(head, i)->data.total < 271)
            statistic[0][1]++;
        else if (getNode(head, i)->data.total > 209 && getNode(head, i)->data.total < 241)
            statistic[0][2]++;
        else if (getNode(head, i)->data.total > 179 && getNode(head, i)->data.total < 210)
            statistic[0][3]++;
        else if (getNode(head, i)->data.total < 181)
            statistic[0][4]++;
    char *colheader[] = {"excellent", "good", "fair", "pass", "fail"};
    char *rowheader[] = {"number", "ratio"};
    getSheet(statistic, 2, 5, colheader, rowheader, "int");
end:
    return 0;
}

int getAll()
{
    if (numberOfStd == 0) {
        printf("Student information has not been entered yet\n");
        system("pause");
        goto end;
    }
    char *colheader[] = {"ID", "name", "chinese", "math", "english", "total"};
    char *rowheader[] = {"0"};
    getSheet(head, numberOfStd, 6, colheader, rowheader, "struct linkedList");
end:
    return 0;
}

// int fileIO(int mode)
// {

// }

int compare(void *a, void *b, int mode)
{
    int ret = 0;
    if (mode <= 4)  //subject compare
        ret = (int)(*(float *)a - *(float *)b);
    else if (mode == 5) //id compare
        ret = *(int *)a - *(int *)b;
    else if (mode == 6) //name compare
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
    if (strcmp(type, "int") == 0) {
        int *arr = (int *)p;
        printf("%10s", "");
        for (int i = 0; i < cols; i++)
            printf("%10s", colheader[i]);
        printf("\n");
        // print rowheader and data
        for (int i = 0; i < rows; i++) {
            printf("%10s", rowheader[i]);
            for (int j = 0; j < cols; j++)
                printf("%10d", arr[i * cols + j]);
            printf("\n");
        }
    }
    else if (strcmp(type, "float") == 0) {
        float *arr = (float *)p;
        // print colheader
        printf("%10s", "");
        for (int i = 0; i < cols; i++)
            printf("%10s", colheader[i]);
        printf("\n");
        for (int i = 0; i < rows; i++) {
            printf("%10s", rowheader[i]);
            for (int j = 0; j < cols; j++)
                printf("%10.2f", arr[i * cols + j]);
            printf("\n");
        }
    }
    else if (strcmp(type, "char") == 0) {
        char *arr = (char *)p;
        // print colheader
        printf("%10s", "");
        for (int i = 0; i < cols; i++)
            printf("%10s", colheader[i]);
        printf("\n");
        for (int i = 0; i < rows; i++) {
            printf("%10s", rowheader[i]);
            for (int j = 0; j < cols; j++)
                printf("%10c", arr[i * cols + j]);
            printf("\n");
        }
    }
    else if (strcmp(type, "struct linkedList") == 0) {
        Head* head = (Head *)p;
        for (int i = 0; i < cols; i++)
            printf("%10s", colheader[i]);
        printf("\n");
        for (int i = 0; i < rows; ++i)
            printf("%10d %10s %10.2f %10.2f %10.2f %10.2f\n", getNode(head, i)->data.ID, getNode(head, i)->data.name, getNode(head, i)->data.chinese, getNode(head, i)->data.math, getNode(head, i)->data.english, getNode(head, i)->data.total);
    }
    else if (strcmp(type, "struct array") == 0) {
        Std *arr = (Std *)p;
        for (int i = 0; i < cols; i++)
            printf("%10s", colheader[i]);
        printf("\n");
        for (int i = 0; i < rows; ++i)
            printf("%10d %10s %10.2f %10.2f %10.2f %10.2f\n", arr[i].ID, arr[i].name, arr[i].chinese, arr[i].math, arr[i].english, arr[i].total);
    }
    else
        printf("Unsupported type: %s\n", type);
    system("pause");
}
