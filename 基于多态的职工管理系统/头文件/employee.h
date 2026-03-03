//
// Created by PROTON on 2025/9/28.
//
# pragma  once
# include <string>
# include <iostream>
using namespace std;
# include "worker.h"
class Employee : public Worker
{
public:
    Employee(int id, string name, int dId);
    // 显示个人信息
    void ShowInfo() override;
    // 获取岗位名称
    string GetDeptName() override;
};

