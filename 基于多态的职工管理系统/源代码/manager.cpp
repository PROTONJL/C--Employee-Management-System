//
// Created by PROTON on 2025/9/30.
//
#include "../头文件/manager.h"

Manager::Manager(int id, string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}
void Manager::ShowInfo()
{
    cout << "职工编号:" << this->m_Id
         << "\t职工姓名:" << this->m_Name
         << "\t岗位:" << this->GetDeptName()
         <<"\t岗位职责:完成老板交代的任务，并给员工发布任务" << endl;
}
string Manager::GetDeptName()
{
    return string("经理");
}
