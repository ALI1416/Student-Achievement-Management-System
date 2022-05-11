#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define N 128                   //最大结构体数量
#define stlen sizeof(struct st) //结构体长度
#define PW "123"                //密码

struct st
{
  int no;       //序号
  int flag;     //标记
  char num[8];  //学号
  char name[8]; //姓名
  float cpp;    // C语言成绩
  float eng;    //英语成绩
  float math;   //数学成绩
  float ave;    //平均分
};

struct st s[N];
int tot = 0;   //结构体个数
int flag0 = 0; //标记为0的个数

int all(int t);
int change();
int delall();
int delpart();
int display();
int find();
int findswitch(int t);
int index();
int input();
int insert();
int judge();
int main();
int part(int t);
int password();
int print(int t);
int recycle();
int reset();
int save();
int sort();
int sortswitch(int x);

int judge()
{
  printf("\t\t\t\t******************************\n");
  printf("\t\t\t\t*      ■【回车键】确认      *\n");
  printf("\t\t\t\t*      ▲【其他键】取消      *\n");
  printf("\t\t\t\t******************************\n");
  if (getch() == 13)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

//输入
int input()
{
  FILE *fp;
  fp = fopen("data.dat", "ab+");
  // system("cls");
  printf("◆请输入【学号】【姓名】【C语言成绩】【英语成绩】【高数成绩】\n");
  printf("◆【学号】输入【0】保存并返回主菜单\n");
  for (int i = 0; i < N - tot; i++)
  {
    scanf("%s", s[i].num);                           //先输入学号
    if (strlen(s[i].num) == 1 && s[i].num[0] == '0') //如果输入的长度为1并且是0，退出
    {
      fclose(fp);
      return 0; //非正常退出关闭文件
    }
    scanf("%s%f%f%f", &s[i].name, &s[i].cpp, &s[i].eng, &s[i].math); //再次输入剩下数据
    s[i].ave = (s[i].cpp + s[i].eng + s[i].math) / 3;                //计算平均分
    s[i].no = ++tot;                                                 //新增结构体序号自增
    s[i].flag = 0;                                                   //，标记为0
    flag0++;                                                         //标记0个数自增
    fwrite(&s[i], stlen, 1, fp);                                     //写入文件
  }
  fclose(fp); //正常退出关闭文件
  printf("数据已超出，请删除后再添加。\n");
  return 1;
}

//输出
int print(int t)
{
  system("cls");
  if ((t == 0 && flag0 == 0) || (t == 1 && tot == flag0)) //显示数据为0，或回收站数据为0
    return 0;
  else
  {
    FILE *fp;
    fp = fopen("data.dat", "rb");
    fread(s, stlen, tot, fp);
    printf("序号\t学号\t姓名\tC语言\t英语\t高数\t平均分\n");
    for (int i = 0; i < tot; i++)
    {
      if (s[i].flag == t)
        printf("%d\t%s\t%s\t%.2f\t%.2f\t%.2f\t%.2f\n",
               s[i].no, s[i].num, s[i].name, s[i].cpp, s[i].eng, s[i].math, s[i].ave);
    }
    fclose(fp);
    return 1;
  }
}

int display()
{
  if (flag0 == 0)
  {
    printf("无数据！\n");
  }
  else
  {
    print(0); //输出显示
    printf("\t\t\t\t******************************\n");
    printf("\t\t\t\t*    ◆以上为学生数据：      *\n");
    printf("\t\t\t\t*    ◆请选择操作：          *\n");
    printf("\t\t\t\t*      ■1.多项删除          *\n");
    printf("\t\t\t\t*      ■2.全部删除          *\n");
    printf("\t\t\t\t*      ■3.修改              *\n");
    printf("\t\t\t\t*      ■4.插入              *\n");
    printf("\t\t\t\t*      ▼5.查找              *\n");
    printf("\t\t\t\t*      ▼6.排序              *\n");
    printf("\t\t\t\t*      ▼7.另存为...         *\n");
    printf("\t\t\t\t*    ▲【其他键】返回主菜单  *\n");
    printf("\t\t\t\t******************************\n");
    switch (getch())
    {
    case '1': //多项删除
    {
      printf("\t\t\t\t******************************\n");
      printf("\t\t\t\t*    ◆正在进行多项删除操作  *\n");
      printf("\t\t\t\t*    ◆输入【序号】删除      *\n");
      printf("\t\t\t\t*    ◆多项之间加【空格】    *\n");
      printf("\t\t\t\t*    ▲结束加【0】           *\n");
      printf("\t\t\t\t******************************\n");
      part(1);
    }
    break;

    case '2': //全部删除
    {
      printf("\t\t\t\t******************************\n");
      printf("\t\t\t\t*    ◆确定【全部删除】吗？  *\n");
      printf("\t\t\t\t******************************\n");
      if (judge() == 1)
      {
        all(1);
        printf("全部删除成功！\n");
      }
      else
      {
        printf("您已取消全部删除。\n");
      }
    }
    break;

    case '3': //数据修改
    {
      printf("\t\t\t\t******************************\n");
      printf("\t\t\t\t*    ◆正在进行数据修改操作  *\n");
      printf("\t\t\t\t*    ■请输入要修改的【序号】*\n");
      printf("\t\t\t\t*    ▲【0】取消             *\n");
      printf("\t\t\t\t******************************\n");
      change();
    }
    break;

    case '4': //插入
    {
      insert();
    }
    break;

    case '5': //查找
    {
      find();
    }
    break;

    case '6': //排序
    {
      sort();
    }
    break;

    case '7': //另存为
    {
      save();
    }
    break;
    }
  }
  getch();
  return 0;
}

//部分
int part(int t)
{
  int x[N], i = 0, co = 0;
  while (1)
  {
    scanf("%d", &x[i]);
    co++;
    if (x[0] == 0)
      return 0;
    if (x[i++] == 0)
      break;
  }
  co--;
  printf("◆操作的学生序号为：");
  for (i = 0; i < co; i++)
  {
    printf("【%d】", x[i]);
  }
  printf("\n");
  if (judge() == 1)
  {
    if (t == 1)
      flag0 -= co;
    if (t == 0)
      flag0 += co;
    FILE *fp;
    fp = fopen("data.dat", "wb+");
    for (int i = 0; i < co; i++)
    {
      s[x[i] - 1].flag = t; //替换的值
    }
    fwrite(s, stlen, tot, fp);
    fclose(fp);
  }
  else
    return 0;
}

//部分
int delpart()
{
  struct st s2[N];
  int x[N], i = 0, j = 0, co = 0, k = 1;
  while (1)
  {
    scanf("%d", &x[i]);
    co++;
    if (x[0] == 0)
      return 0;
    if (x[i++] == 0)
      break;
  }
  co--;
  printf("操作的学生序号为：");
  for (i = 0; i < co; i++)
  {
    printf("【%d】", x[i]);
  }
  printf("\n");
  if (judge() == 1)
  {
    for (i = 0; i < co; i++)
      s[x[i] - 1].flag = 2; //替换的值
    for (i = 0; i < tot; i++)
    {
      if (s[i].flag != 2)
      {
        s2[j++] = s[i];
        s2[j - 1].no = k++;
      }
    }
    tot = tot - co;
    FILE *fp;
    fp = fopen("data.dat", "wb+");
    fwrite(s2, stlen, tot, fp);
    fclose(fp);
  }
  else
    return 0;
}

//全部
int delall()
{
  struct st s2[N];
  int i = 0, j = 0, k = 1;

  for (i = 0; i < tot; i++)
  {
    if (s[i].flag == 0)
    {
      s2[j++] = s[i];
      s2[j - 1].no = k++;
    }
  }
  tot = flag0;
  FILE *fp;
  fp = fopen("data.dat", "wb+");
  fwrite(s2, stlen, tot, fp);
  fclose(fp);
  return 0;
}

//全部
int all(int t)
{

  if (t == 1)
    flag0 = 0;
  if (t == 0)
    flag0 = tot;
  FILE *fp;
  fp = fopen("data.dat", "wb+");
  for (int j = 0; j < tot; j++)
    s[j].flag = t; //替换的值
  fwrite(s, stlen, tot, fp);
  fclose(fp);
  return 0;
}

//回收站
int recycle()
{
  if (tot == flag0)
    printf("无数据！\n");
  else
  {
    print(1);
    printf("\t\t\t\t******************************\n");
    printf("\t\t\t\t*    ◆以上为回收站数据：    *\n");
    printf("\t\t\t\t*    ◆请选择操作：          *\n");
    printf("\t\t\t\t*      ■1.多项恢复          *\n");
    printf("\t\t\t\t*      ■2.全部恢复          *\n");
    printf("\t\t\t\t*      ■3.多项彻底删除      *\n");
    printf("\t\t\t\t*      ■4.清空回收站        *\n");
    printf("\t\t\t\t*    ▲【其他键】返回主菜单  *\n");
    printf("\t\t\t\t******************************\n");
    switch (getch())
    {
    case '1':
    {
      printf("\t\t\t\t******************************\n");
      printf("\t\t\t\t*    ◆输入【序号】恢复      *\n");
      printf("\t\t\t\t*    ◆多项之间加【空格】    *\n");
      printf("\t\t\t\t******************************\n");
      part(0);
      printf("数据恢复成功！正在返回上一级。\n");
    }
    break;

    case '2':
    {
      printf("\t\t\t\t******************************\n");
      printf("\t\t\t\t*    ◆确定【全部恢复】吗？  *\n");
      printf("\t\t\t\t******************************\n");
      if (judge() == 1)
      {
        all(0);
        printf("全部恢复成功！正在返回上一级。\n");
      }
      else
        printf("您已取消全部恢复，正在返回上一级。\n");
    }
    break;

    case '3':
    {
      printf("\t\t\t\t******************************\n");
      printf("\t\t\t\t*    ◆输入【序号】彻底删除  *\n");
      printf("\t\t\t\t*    ◆多项之间加【空格】    *\n");
      printf("\t\t\t\t******************************\n");
      delpart();
      printf("彻底删除成功！正在返回上一级。\n");
    }
    break;

    case '4':
    {
      printf("\t\t\t\t******************************\n");
      printf("\t\t\t\t*    ◆确定【清空回收站】吗？*\n");
      printf("\t\t\t\t******************************\n");
      if (judge() == 1)
      {
        delall();
        printf("清空回收站成功！正在返回上一级。\n");
      }
      else
        printf("您已取消清空回收站，正在返回上一级。\n");
    }
    break;
    }
  }
  Sleep(500);
  return 0;
}

//子排序
int sortswitch(int x)
{
  struct st t, s0[N];
  int i, j, k = 0;
  FILE *fp;
  fp = fopen("data.dat", "rb");
  fread(s, stlen, tot, fp);
  fclose(fp);
  for (i = 0; i < tot; i++)
  {
    if (s[i].flag == 0)
      s0[k++] = s[i];
  }
  for (i = 0; i < flag0 - 1; i++)
  {
    k = i;
    for (j = i + 1; j < flag0; j++)
    {
      if (x == 1 && strcmp(s0[k].num, s0[j].num) > 0)
        k = j;
      if (x == 2 && strcmp(s0[k].name, s0[j].name) > 0)
        k = j;
      if (x == 3 && s0[k].cpp < s0[j].cpp)
        k = j;
      if (x == 4 && s0[k].eng < s0[j].eng)
        k = j;
      if (x == 5 && s0[k].math < s0[j].math)
        k = j;
      if (x == 6 && s0[k].ave < s0[j].ave)
        k = j;
      if (k != i)
      {
        t = s0[i];
        s0[i] = s0[k];
        s0[k] = t;
      }
    }
  }
  printf("序号\t学号\t姓名\tC语言\t英语\t高数\t平均分\n");
  for (i = 0; i < flag0; i++)
    printf("%d\t%s\t%s\t%.2f\t%.2f\t%.2f\t%.2f\n",
           s0[i].no, s0[i].num, s0[i].name, s0[i].cpp, s0[i].eng, s0[i].math, s0[i].ave);
  system("PAUSE");
  return 0;
}

int insert()
{
  printf("请输入要插入的【序号】\n");
  int no;
  scanf("%d", &no);
  if (no == 0)
    return 0;
  if (no > tot)
  {
    printf("输入有误！\n");
    return 0;
  }
  if (no > 0 && no <= tot)
  {
    for (int i = tot + 1; i > no - 1; i--)
    {
      s[i] = s[i - 1];
      s[i].no++;
    }
    printf("请输入【学号】【姓名】【C语言成绩】【英语成绩】【高数成绩】\n");
    printf("(输入【0】取消并返回主菜单)\n");
    i = no - 1;
    scanf("%s", s[i].num);
    if (strlen(s[i].num) == 1 && s[i].num[0] == '0')
      return 0;
    scanf("%s%f%f%f", &s[i].name, &s[i].cpp, &s[i].eng, &s[i].math);
    s[i].ave = (s[i].cpp + s[i].eng + s[i].math) / 3;
    printf("\t\t\t\t******************************\n");
    printf("\t\t\t\t*    ◆确定【修改数据】吗？  *\n");
    printf("\t\t\t\t******************************\n");
    if (judge() == 1)
    {
      FILE *fp;
      fp = fopen("data.dat", "wb+");
      fwrite(s, stlen, tot + 1, fp);
      fclose(fp);
      tot++;
      flag0++;
      printf("修改成功！\n");
    }
    else
      printf("您已取消修改，正在返回上一级。\n");
  }
  return 0;
}

int change()
{
  int no;
  scanf("%d", &no);
  if (no == 0)
    return 0;
  if (no > tot)
  {
    printf("未找到！\n");
    return 0;
  }
  if (no > 0 && no <= tot)
  {
    int i = no - 1;
    printf("◆原数据为：\n");
    printf("序号\t学号\t姓名\tC语言\t英语\t高数\t平均分\n");
    printf("%d\t%s\t%s\t%.2f\t%.2f\t%.2f\t%.2f\n",
           s[i].no, s[i].num, s[i].name, s[i].cpp, s[i].eng, s[i].math, s[i].ave);
    printf("◆请输入修改后的数据：\n");
    printf("请输入【学号】【姓名】【C语言成绩】【英语成绩】【高数成绩】\n");
    printf("(输入【0】取消并返回主菜单)\n");
    scanf("%s", s[i].num);
    if (strlen(s[i].num) == 1 && s[i].num[0] == '0')
      return 0;
    scanf("%s%f%f%f", &s[i].name, &s[i].cpp, &s[i].eng, &s[i].math);
    s[i].ave = (s[i].cpp + s[i].eng + s[i].math) / 3;
    printf("\t\t\t\t******************************\n");
    printf("\t\t\t\t*    ◆确定【修改数据】吗？  *\n");
    printf("\t\t\t\t******************************\n");
    if (judge() == 1)
    {
      FILE *fp;
      fp = fopen("data.dat", "wb+");
      fwrite(s, stlen, tot, fp);
      fclose(fp);
      printf("修改成功！\n");
    }
    else
      printf("您已取消修改，正在返回上一级。\n");
    Sleep(500);
  }
  return 0;
}

int findswitch(int t)
{
  int i;
  char ch[8];
  gets(ch);
  for (i = 0; i < tot; i++)
  {
    if (t == 1 && strcmp(ch, s[i].num) == 0)
      break;
    if (t == 2 && strcmp(ch, s[i].name) == 0)
      break;
  }
  if (s[i].flag == 0 && i < tot)
  {
    printf("已找到！\n");
    printf("序号\t学号\t姓名\tC语言\t英语\t高数\t平均分\n");
    printf("%d\t%s\t%s\t%.2f\t%.2f\t%.2f\t%.2f\n",
           s[i].no, s[i].num, s[i].name, s[i].cpp, s[i].eng, s[i].math, s[i].ave);
  }
  else
    printf("未找到！\n");
  system("PAUSE");
  return 0;
}

int find()
{
  while (1)
  {
    system("cls");
    printf("\t\t\t\t******************************\n");
    printf("\t\t\t\t*    ◆请选择查找方式        *\n");
    printf("\t\t\t\t*      ■1.学号              *\n");
    printf("\t\t\t\t*      ■2.姓名              *\n");
    printf("\t\t\t\t*    ▲0.返回主菜单          *\n");
    printf("\t\t\t\t******************************\n\n");
    switch (getch())
    {
    case '1':
      printf("请输入要查找的【学号】\n");
      findswitch(1);
      break;
    case '2':
      printf("请输入要查找的【姓名】\n");
      findswitch(2);
      break;
    case '0':
      return 0;
      break;
    default:
      printf("输入有误！请重新输入。\n");
      Sleep(500);
    }
  }
}

//排序
int sort()
{
  while (1)
  {
    system("cls");
    printf("\t\t\t\t******************************\n");
    printf("\t\t\t\t*    ◆请选择排序方式(降序)：*\n");
    printf("\t\t\t\t*      ■1.学号              *\n");
    printf("\t\t\t\t*      ■2.姓名(测试)        *\n");
    printf("\t\t\t\t*      ■3.C语言成绩         *\n");
    printf("\t\t\t\t*      ■4.英语成绩          *\n");
    printf("\t\t\t\t*      ■5.高数成绩          *\n");
    printf("\t\t\t\t*      ■6.平均分            *\n");
    printf("\t\t\t\t*    ▲0.返回主菜单          *\n");
    printf("\t\t\t\t******************************\n\n");
    switch (getch())
    {
    case '1':
      printf("按照【学号】排序如下：      \n");
      sortswitch(1);
      break;
    case '2':
      printf("按照【姓名(测试)】排序如下：\n");
      sortswitch(2);
      break;
    case '3':
      printf("按照【C语言成绩】排序如下： \n");
      sortswitch(3);
      break;
    case '4':
      printf("按照【英语成绩】排序如下：  \n");
      sortswitch(4);
      break;
    case '5':
      printf("按照【高数成绩】排序如下：  \n");
      sortswitch(5);
      break;
    case '6':
      printf("按照【平均分】排序如下：    \n");
      sortswitch(6);
      break;
    case '0':
      return 0;
      break;
    default:
      printf("输入有误！请重新输入。\n");
      Sleep(500);
    }
  }
}

//保存
int save()
{
  system("cls");
  while (1)
  {
    system("cls");
    printf("\t\t\t\t******************************\n");
    printf("\t\t\t\t*    ◆请选择导出方式：      *\n");
    printf("\t\t\t\t*      ■1.txt文本文档       *\n");
    printf("\t\t\t\t*      ■2.xls表格文件       *\n");
    printf("\t\t\t\t*    ▲0.返回主菜单          *\n");
    printf("\t\t\t\t******************************\n");
    int ch = getch();
    if (ch == '0')
      return 0;
    if (ch == '1' || ch == '2')
    {
      FILE *fp;
      if (ch == '1')
        fp = fopen("data.txt", "w");
      if (ch == '2')
        fp = fopen("data.xls", "w");
      fprintf(fp, "序号\t学号\t姓名\tC语言\t英语\t高数\t平均分\n");
      for (int i = 0; i < tot; i++)
        if (s[i].flag == 0)
          fprintf(fp, "%d\t%s\t%s\t%.2f\t%.2f\t%.2f\t%.2f\n",
                  s[i].no, s[i].num, s[i].name, s[i].cpp, s[i].eng, s[i].math, s[i].ave);
      fclose(fp);
      printf("导出成功！\n");
    }
    if (!(ch == '0' || ch == '1' || ch == '2'))
      printf("输入有误！请重新输入。\n");
    Sleep(500);
  }
}

//重置
int reset()
{
  printf("\t\t\t\t******************************\n");
  printf("\t\t\t\t*    ◆确定【重置系统】吗？  *\n");
  printf("\t\t\t\t******************************\n");
  if (judge() == 1)
  {
    FILE *fp;
    fp = fopen("data.dat", "w");
    fclose(fp);
    tot = 0;
    flag0 = 0;
    printf("重置成功！正在返回上一级。\n");
  }
  else
    printf("您已取消重置，正在返回上一级。\n");
  Sleep(500);
  return 0;
}

int index()
{
  FILE *fp;
  if ((fp = fopen("data.dat", "r")) == NULL) //如果没有文件
    fp = fopen("data.dat", "wb+");           //创建一个文件
  fp = fopen("data.dat", "rb");
  fseek(fp, 0L, SEEK_END); //指向文件尾
  tot = ftell(fp) / stlen; //结构体个数
  fseek(fp, 0L, SEEK_SET); //指向文件头
  fread(s, stlen, tot, fp);
  for (int i = 0; i < tot; i++)
  {
    if (s[i].flag == 0)
      flag0++; //查找标记为0的个数
  }
  fclose(fp);
  while (1)
  {
    system("cls");
    printf("\t\t\t\t******************************\n");
    printf("\t\t\t\t*    欢迎使用学生管理系统    *\n");
    printf("\t\t\t\t*      按键进入相应功能      *\n");
    printf("\t\t\t\t******************************\n");
    printf("\t\t\t\t*    ■1.输入学生数据        *\n");
    printf("\t\t\t\t*    ▼2.显示                *\n");
    printf("\t\t\t\t*    ▼3.回收站              *\n");
    printf("\t\t\t\t*    ■4.重置系统            *\n");
    printf("\t\t\t\t*    ●0.退出                *\n");
    printf("\t\t\t\t******************************\n");
    switch (getch())
    {
    case '1':
      input();
      break;
    case '2':
      display();
      break;
    case '3':
      recycle();
      break;
    case '4':
      reset();
      break;
    case '0':
      return 0;
      break;
    default:
      printf("输入有误！请重新输入。\n");
      Sleep(500);
    }
  }
}

int password()
{
  printf("请输入口令！\n");
  char get[16], pw[] = PW; //密码
  int count = 3;
  while (count)
  {
    gets(get);
    if (strcmp(get, pw) == 0)
    {
      printf("口令正确！正在进入系统...\n");
      Sleep(500);
      return 1;
    }
    else
    {
      if (count != 1)
      {
        printf("口令错误！请重新输入！\n");
        printf("您还有%d次机会！\n", --count);
      }
      else
      {
        printf("口令错误！按任意键退出系统！\n");
        getch();
        return 0;
      }
    }
  }
}

int main()
{
  system("mode con cols=94 lines=30"); // 94行30列（居中）
  SetConsoleTitle("学生管理系统");     //标题
  system("color F0");                  //白底黑字
  printf("欢迎使用学生管理系统\n");
  if (password() == 1)
    index();
  else
    return 0;
}
