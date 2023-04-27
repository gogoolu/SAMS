#include <stdio.h>
#include <stdlib.h>
int myScan(void *p, char *type);

#define DECLARE(type) \
int scan_##type(type *p);\

#define DEFINE(type,fmt)                              \
int scan_##type(type *p)                                \
{                                                       \
    int ret = 0;                                        \
    do{                                                 \
        ret = scanf(fmt, p);                           \
        fflush(stdin);                                  \
        if(ret != 1)                                    \
            printf("Invalid input! please re-enter.");  \
    } while (ret != 1);                                 \
    return 0;                                           \
}                                                       \

DECLARE(int)
DECLARE(float)
DECLARE(char)

DEFINE(int,"%d")
DEFINE(float,"%f")
DEFINE(char,"%s")

int main(){
    int a= 0;
    scan_int(&a);
    float b = 0;
    scan_float(&b);
    char string[20] = "hello";
    scan_char(string);
    printf("%d %f %s", a, b, string);
    system("pause");


}


// int myScan(void *p, char *type)
// {
//     if (!strcmp(type, "int")) {
//         int ret = 0;
//         do {
//             ret = scanf("%d", (int *)p);
//             fflush(stdin);
//             if (ret != 1)
//                 printf("Invalid input! please re-enter.\n");
//         } while (ret != 1);
//     }
//     else if (!strcmp(type, "float")) {
//         int ret = 0;
//         do {
//             ret = scanf("%f", (float *)p);
//             fflush(stdin);
//             if (ret != 1)
//                 printf("Invalid input! please re-enter.\n");
//         } while (ret != 1);
//     }
//     else if (!strcmp(type, "string")) {
//         int ret = 0;
//         do {
//             ret = scanf("%s", (char *)p);
//             fflush(stdin);
//             if (ret != 1)
//                 printf("Invalid input! please re-enter.\n");
//         } while (ret != 1);
//     }
//     return 0;
// }