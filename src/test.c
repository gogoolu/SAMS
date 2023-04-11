#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    float chinese;
    float math;
    float english;
    float total;
    int ID;
    char name[25];
} Std;
void swap(int *a, int *b);
int *sort(int *arr, int n);
void *getMember(Std *student, int member);
int main()
{
    int a[] = {1, 1, 100, 99, 88, 4, 29};
    sort(a, 7);
    for (int i = 0; i < 7; ++i)
        printf("%d ", a[i]);
    return 0;
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

int *sort(int *arr, int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] > arr[j + 1])
            {
                swap(arr + j, arr + j + 1);
            }
    }
    return arr;
}

void swap(int *a, int *b)
{
    int temp = 0;
    temp = *a;
    *a = *b;
    *b = temp;
}