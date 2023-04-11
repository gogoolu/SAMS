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
void *getMember(Std *student, int member);
int main()
{
    Std lihua = {1, 2, 3, 4, 5, "lihua"};
    printf("%s", (float *)getMember(&lihua, 6));
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