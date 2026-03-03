//
// Created by PROTON on 2025/9/30.
//

# pragma once
# include <iostream>
using namespace std;
# include "worker.h"

class Manager : public Worker
{
public:
    Manager(int id, string name, int dId);
    void ShowInfo() override;
    string GetDeptName() override;

};