# 学生成绩管理系统v3.0

---



## 下载源码

`git clone git@github.com:gogoolu/SAMS.git`



## 运行

`.\bin\main.exe`



## 该系统的主要函数及功能

*  ` void getHomepage();                // draw homepage` 
* `int inputRecord();                 // input students infor`
* `int getTotalAverage();             // index ditto
  `
* `int sortBy(int subject, int mode); // mode => descending:0, ascending:1, subject ditto
  `
* `int searchBy(int index);           // searchBy by ID:5, name:6
  `
* `int statisticAnaly();              // analysis statistic
  `
* `int getAll();                      // get all student infor list
  `
* `void getSheet(void *p, int rows, int cols, char **colheader, char **rowheader, char *type);`

除`getHomepage()`函数以外，其他函数只负责操作数据，最终由`getSheet()`函数将数据按格式打印成表格

