//
// Created by PROTON on 2025/9/28.
//
#include "../头文件/employee.h"
Employee::Employee(int id, string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}
void Employee::ShowInfo()
{
    cout << "职工编号:" << this->m_Id
        << "\t职工姓名:" << this->m_Name
        << "\t岗位:" << this->GetDeptName()
        <<"\t岗位职责:完成经理交代的任务" << endl;
}
string Employee::GetDeptName()
{
    return string("员工");
}


