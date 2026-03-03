//
// Created by PROTON on 2025/9/28.
//
//#include "../头文件/boss.h"
//#include "../头文件/employee.h"
//#include "../头文件/manager.h"
//# include "../头文件/workerManager.h"
# include <windows.h>
# include "boss.cpp"
#include "employee.cpp"
#include "manager.cpp"
# include "workerManager.cpp"
#include <string>
#include <iostream>

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    WorkerManager wm;
    int choice = 0;
    while (true)
    {
        //展示菜单
        wm.ShowMenu();
        cout << "请输入您的选择:" << endl;
        cin >> choice;

        switch (choice)
        {
            case 0:
                //退出系统
                wm.ExitSystem();
                break;
            case 1: //添加职工
                wm.Add_Emp();
                break;
            case 2: //显示职工
                wm.Show_Emp();
                break;
            case 3: //删除职工
                wm.Del_Emp();
                break;
            case 4: //修改职工
                wm.Mod_Emp();
                break;
            case 5: //查找职工
                wm.Find_Emp();
                break;
            case 6: //排序职工
                wm.Sort_Emp();
                break;
            case 7: //清空文件
                wm.Clear_Emp();
                break;
            default:
                system("cls");
                break;
        }
    }

    system("pause");
    return 0;
}
