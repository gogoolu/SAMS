#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ===============================================

int numberOfStd = 0;

typedef struct
{
    char name[25];
    int ID;
    float math;
    float chinese;
    float english;
    float total;
} Std;
Std stds[60]; // 主数组

// ===================主要功能函数=================

/*生成主页*/
void drawUI();
/*交互函数*/
int router();
/*导入学生成绩及信息*/
int inputInfor();
/*计算每门课的平均分*/
int getAverageScore();
/*排序函数*/
int sort(); // 1.按语文成绩排序 2.按数学成绩排序 3.按英语成绩排序 4.按总分排序 5.按学号排序
/*通过ID查询*/
void queryScoreByID();
/*统计学生层次*/
void getStdLayer();
/*获取学生信息*/
void getStdInfor();
/*输出三门课程均优秀或不及格的学生*/
void getTopLayerAndLowLayer();

// =================小功能函数=====================

void sortByChinese();
void sortBymath();
void sortByenglish();
void sortByTotal();
void sortByID();
/*交换总数组中的元素*/
void swap(Std *a, Std *b);
/*getStdLayer函数的语文成绩层次统计函数*/
void chineseLayer(int *chinese);
/*getStdLayer函数的数学成绩参差统计函数*/
void mathLayer(int *math);
/*getStdLayer函数的英语层次统计函数*/
void englishLayer(int *english);
/*打印getStdLayer函数生成的分层表*/
void layerUI(int flag, int *subject);
/*打印出成绩在一个范围内的所有学生信息的函数*/
void printStdInRange(float small, float large);

// ===============================================

int main()
{
    do
    {
        system("cls");
        drawUI();
    } while (router());

    system("pause");
    return 0;
}

/*生成主页*/
void drawUI()
{
    printf("欢迎来到学生成绩管理系统v1.0\n");
    printf("1.录入学生信息\n2.计算每门课程平均分\n3.成绩排序\n4.按学号查询成绩\n5.统计学生成绩层次\n6.输出每个学生的信息\n7.输出三门课程均优秀或不及格的学生\n0.退出程序\n");
}

/*交互函数*/
int router()
{
    int temp = 0;

    int ret = scanf("%d", &temp);
    switch (temp)
    {
    case 0:
        return 0;
    case 1:
        inputInfor();
        break;
    case 2:
        getAverageScore();
        break;
    case 3:
        sort();
        break;
    case 4:
        queryScoreByID();
        break;
    case 5:
        getStdLayer();
        break;
    case 6:
        getStdInfor();
        break;
    case 7:
        getTopLayerAndLowLayer();
        break;
    }
    return 1;
}

/*导入学生成绩及信息*/
int inputInfor()
{
    system("cls");
    int i = numberOfStd;

    printf("输入学生姓名：");
    scanf("%s", stds[i].name);
    printf("输入学生学号：");
    scanf("%d", &stds[i].ID);
    printf("输入学生语文成绩：");
    scanf("%f", &stds[i].chinese);
    printf("输入学生数学成绩：");
    scanf("%f", &stds[i].math);
    printf("输入学生英语成绩：");
    scanf("%f", &stds[i].english);
    stds[i].total = stds[i].chinese + stds[i].math + stds[i].english;
    numberOfStd++;
    return 1;
}

/*计算每门课的平均分*/
int getAverageScore()
{
    float chinese = 0;
    float math = 0;
    float english = 0;
    for (int i = 0; i < numberOfStd; i++)
    {
        chinese += stds[i].chinese;
        math += stds[i].math;
        english += stds[i].english;
    }
    printf("********************************\n");
    printf("** 语文   ** 数学   ** 英语   **\n");
    printf("********************************\n");
    printf("** %4.2f ** %4.2f ** %4.2f **\n", chinese / numberOfStd, math / numberOfStd, english / numberOfStd);
    printf("********************************\n");
    system("pause");
    return 1;
}

int sort()
{
    int benchmark;
    printf("1.按语文成绩排序 2.按数学成绩排序 3.按英语成绩排序 4.按总分排序 5.按学号排序\n");
    scanf("%d", &benchmark);
    system("cls");
    switch (benchmark)
    {
    case 1:
        sortByChinese();
        break;
    case 2:
        sortBymath();
        break;
    case 3:
        sortByenglish();
        break;
    case 4:
        sortByTotal();
        break;
    case 5:
        sortByID();
        break;
    default:
        return 0;
        break;
    }

    printf("**********************************************************************************\n");
    printf("*** 学号 ** 姓名 ** 语文 ** 数学 ** 英语 ** 总分 ** 平均分 ***\n");
    printf("**********************************************************************************\n");
    for (int i = 0; i < numberOfStd; ++i)
    {
        printf("*** %-4d ** %s ** %4.2f ** %4.2f ** %4.2f ** %4.2f ** %4.2f ***\n", stds[i].ID, stds[i].name, stds[i].chinese, stds[i].math, stds[i].english, stds[i].total, stds[i].total / 3);
        printf("*********************************************************************************\n");
    }
    system("pause");
    return 1;
}

/*交换总数组中的元素*/
void swap(Std *a, Std *b)
{
    Std temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void sortByChinese()
{
    for (int i = 0; i < numberOfStd - 1; i++)
        for (int j = 0; j < numberOfStd - i - 1; j++)
            if (stds[j].chinese > stds[j + 1].chinese)
                swap(&stds[j], &stds[j + 1]);
}
void sortBymath()
{
    for (int i = 0; i < numberOfStd - 1; i++)
        for (int j = 0; j < numberOfStd - i - 1; j++)
            if (stds[j].math > stds[j + 1].math)
                swap(&stds[j], &stds[j + 1]);
}
void sortByenglish()
{
    for (int i = 0; i < numberOfStd - 1; i++)
        for (int j = 0; j < numberOfStd - i - 1; j++)
            if (stds[j].english > stds[j + 1].english)
                swap(&stds[j], &stds[j + 1]);
}
void sortByTotal()
{
    for (int i = 0; i < numberOfStd - 1; i++)
        for (int j = 0; j < numberOfStd - i - 1; j++)
            if (stds[j].total > stds[j + 1].total)
                swap(&stds[j], &stds[j + 1]);
}
void sortByID()
{
    for (int i = 0; i < numberOfStd - 1; i++)
        for (int j = 0; j < numberOfStd - i - 1; j++)
            if (stds[j].ID > stds[j + 1].ID)
                swap(&stds[j], &stds[j + 1]);
}
/*通过ID查询信息*/
void queryScoreByID()
{
    int ID = 0;
    printf("请输入你需要查询的ID\n");
    scanf("%d", &ID);
    for (int i = 0; i < numberOfStd; ++i)
    {
        if (stds[i].ID == ID)
        {
            printf("**********************************************************************************\n");
            printf("*** 学号 ** 姓名 ** 语文 ** 数学 ** 英语 ** 总分 ** 平均分 ***\n");
            printf("**********************************************************************************\n");
            printf("*** %-4d ** %s ** %4.2f ** %4.2f ** %4.2f ** %4.2f ** %4.2f ***\n", stds[i].ID, stds[i].name, stds[i].chinese, stds[i].math, stds[i].english, stds[i].total, stds[i].total / 3);
            printf("*********************************************************************************\n");
            system("pause");
        }
    }
}

/*统计学生层次*/
void getStdLayer()
{
    int chinese[5] = {0};
    int math[5] = {0};
    int english[5] = {0};

    int temp = 0;
    printf("输入所查询科目: 1.语文 2.数学 3.英语\n");
    scanf("%d", &temp);

    switch (temp)
    {

    case 1:
        chineseLayer(chinese);
        layerUI(temp, chinese);
        break;
    case 2:
        mathLayer(math);
        layerUI(temp, math);
        break;
    case 3:
        englishLayer(english);
        layerUI(temp, english);
        break;
    }
}

/*getStdLayer函数的语文成绩参差统计函数*/
void chineseLayer(int *chinese)
{
    for (int i = 0; i < numberOfStd; i++)
    {
        if (stds[i].chinese > 89 && stds[i].chinese < 101)
            chinese[0]++;
        else if (stds[i].chinese < 90 && stds[i].chinese > 79)
            chinese[1]++;
        else if (stds[i].chinese < 80 && stds[i].chinese > 69)
            chinese[2]++;
        else if (stds[i].chinese < 79 && stds[i].chinese > 59)
            chinese[3]++;
        else
            chinese[4]++;
    }
}

/*getStdLayer函数的数学成绩参差统计函数*/
void mathLayer(int *math)
{
    for (int i = 0; i < numberOfStd; i++)
    {
        if (stds[i].math > 89 && stds[i].math < 101)
            math[0]++;
        else if (stds[i].math < 90 && stds[i].math > 79)
            math[1]++;
        else if (stds[i].math < 80 && stds[i].math > 69)
            math[2]++;
        else if (stds[i].math < 79 && stds[i].math > 59)
            math[3]++;
        else
            math[4]++;
    }
}

/*getStdLayer函数的英语层次统计函数*/
void englishLayer(int *english)
{
    for (int i = 0; i < numberOfStd; i++)
    {
        if (stds[i].english > 89 && stds[i].english < 101)
            english[0]++;
        else if (stds[i].english < 90 && stds[i].english > 79)
            english[1]++;
        else if (stds[i].english < 80 && stds[i].english > 69)
            english[2]++;
        else if (stds[i].english < 79 && stds[i].english > 59)
            english[3]++;
        else
            english[4]++;
    }
}

/*打印getStdLayer函数生成的分层表*/
void layerUI(int flag, int *subject)
{
    printf("***********************************\n");

    switch (flag)
    {
    case 1:
        printf("*** 总分    **  人数 ** 百分比 *****\n");
        break;
    case 2:
        printf("*** 语文    **  人数 ** 百分比 *****\n");
        break;
    case 3:
        printf("*** 数学    **  人数 ** 百分比 *****\n");
        break;
    case 4:
        printf("*** 英语    **  人数 ** 百分比 *****\n");
        break;
    }
    printf("***********************************\n");
    printf("*** 优秀    **  %4d  ** %.2f%% ****************************\n", subject[0], 1.0 * subject[0] / numberOfStd * 100);
    printf("*** 良好    **  %4d  ** %.2f%% ****************************\n", subject[1], 1.0 * subject[1] / numberOfStd * 100);
    printf("*** 中等    **  %4d  ** %.2f%% ****************************\n", subject[2], 1.0 * subject[2] / numberOfStd * 100);
    printf("*** 及格    **  %4d  ** %.2f%% ****************************\n", subject[3], 1.0 * subject[3] / numberOfStd * 100);
    printf("*** 不及格  **  %4d  ** %.2f%% ****************************\n", subject[4], 1.0 * subject[4] / numberOfStd * 100);
    system("pause");
}

/*获取学生信息*/
void getStdInfor()
{
    printf("**********************************************************************************\n");
    printf("*** 学号 ** 姓名 ** 语文 ** 数学 ** 英语 ** 总分 ** 平均分 ***\n");
    printf("**********************************************************************************\n");
    sortByID();
    for (int i = 0; i < numberOfStd; i++)
    {
        printf("*** %-4d ** %s ** %4.2f ** %4.2f ** %4.2f ** %4.2f ** %4.2f ***\n", stds[i].ID, stds[i].name, stds[i].chinese, stds[i].math, stds[i].english, stds[i].total, stds[i].total / 3);
        printf("*********************************************************************************\n");
    }
    system("pause");
}

/*输出三门课程均优秀或不及格的学生*/
void getTopLayerAndLowLayer()
{
    int temp = 0;
    printf("1.每门科目均优秀者 2.每门科目均不及格者");
    scanf("%d", &temp);
    switch (temp)
    {
    case 1:
        printStdInRange(89, 101);
        break;
    case 2:
        printStdInRange(-1, 60);
        break;
    default:
        break;
    }
}

/*打印出成绩在一个范围内的所有学生信息的函数*/
void printStdInRange(float small, float large)
{
    sortByID();

    printf("**********************************************************************************\n");
    printf("*** 学号 ** 姓名 ** 语文 ** 数学 ** 英语 ** 总分 ** 平均分 ***\n");
    printf("**********************************************************************************\n");
    for (int i = 0; i < numberOfStd; i++)
    {
        if (stds[i].chinese > small && stds[i].math > small && stds[i].english > small && stds[i].chinese < large && stds[i].math < large && stds[i].english < large)
        {
            printf("*** %-4d ** %s ** %4.2f ** %4.2f ** %4.2f ** %4.2f ** %4.2f ***\n", stds[i].ID, stds[i].name, stds[i].chinese, stds[i].math, stds[i].english, stds[i].total, stds[i].total / 3);
            printf("*********************************************************************************\n");
        }
    }
    system("pause");
}