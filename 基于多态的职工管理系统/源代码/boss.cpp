//
// Created by PROTON on 2025/9/30.
//
#include "../头文件/boss.h"

Boos::Boos(int id, string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}
void Boos::ShowInfo()
{
    cout << "职工编号:" << this->m_Id
         << "\t职工姓名:" << this->m_Name
         << "\t岗位:" << this->GetDeptName()
         <<"\t岗位职责:完成公司所有任务" << endl;
}
string Boos::GetDeptName()
{
    return string("老板");
}

