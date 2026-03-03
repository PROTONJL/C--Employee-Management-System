//
// Created by PROTON on 2025/9/28.
//
# include "../头文件/workerManager.h"
using namespace std;
WorkerManager::WorkerManager()
{
    //1.文件不存在
    ifstream ifs;
    ifs.open(FILENAME, ios::in);//读文件
    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        //初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    //2.文件存在，数据为空
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        //文件为空
        cout << "文件为空" << endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        //初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    else
    {
        this->m_FileIsEmpty = false;
        //回退文件指针
        ifs.seekg(0, ios::beg);
        int count = 0;
        while (!ifs.eof())
        {
            Worker *worker = NULL;
            int id;
            string name;
            int dId;
            ifs >> id >> name >> dId;
        }
    }
    //3.文件存在，数据不为空
    int num = this->get_EmpNum();
    //cout << "当前共有" << num << "名员工" << endl;
    this->m_EmpNum = num;
    //开辟空间
    this->m_EmpArray = new Worker*[this->m_EmpNum];
    //将文件中的数据存到数组中
    this->Init_Emp();
    //测试代码
//    for (int i = 0; i < this->m_EmpNum; i++)
//    {
//        cout << "编号:" << this->m_EmpArray[i]->m_Id
//             << "姓名:" << this->m_EmpArray[i]->m_Name
//             << "岗位:" << this->m_EmpArray[i]->GetDeptName()
//             << "岗位职责:" << this->m_EmpArray[i]->m_DeptId << endl;
//    }

}
void WorkerManager::ShowMenu()
{
    cout << "欢迎使用职工管理系统" << endl;
    cout << "0.退出管理程序" << endl;
    cout << "1.增加职工信息" << endl;
    cout << "2.显示职工信息" << endl;
    cout << "3.删除离职职工" << endl;
    cout << "4.修改职工信息" << endl;
    cout << "5.查找职工信息" << endl;
    cout << "6.按照编号排序" << endl;
    cout << "7.清空所有文档" << endl;
}
void WorkerManager::ExitSystem()
{
    cout << "欢迎下次使用" << endl;
    exit(0);
}
//添加职工
void WorkerManager::Add_Emp()
{
    cout << "输入添加职工数量" << endl;
    int addNum = 0;
    cin >> addNum;
    if (addNum>0)
    {
        int newSize = this->m_EmpNum + addNum;
        Worker **newSpace = new Worker*[newSize];
        if(this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }
        //批量添加新数据
        for (int i = 0; i < addNum; i++)
        {
            int id;
            string name;
            int dSelect;

            cout << "请输入第" << i + 1 << "个新职工编号:" << endl;
            cin >> id;
            cout << "请输入第" << i + 1 << "个新职工姓名:" << endl;
            cin >> name;
            cout << "请选择该职工的岗位:" << endl;
            cout << "1.普通员工" << endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;
            cin >> dSelect;

            Worker *worker = NULL;
            switch (dSelect)
            {
                case 1: // 普通员工
                    worker = new Employee(id, name, 1);
                    break;
                case 2: // 经理
                    worker = new Manager(id, name, 2);
                    break;
                case 3: // 老板
                    worker = new Boos(id, name, 3);
                    break;
                default:
                    break;
            }
            newSpace[this->m_EmpNum + i] = worker;
        }
        delete []this->m_EmpArray;
        this->m_EmpArray = newSpace;
        this->m_EmpNum = newSize;

        //更新文件状态
        this->m_FileIsEmpty = false;
        cout << "添加成功" <<addNum<<"名新员工"<< endl;
        //保存
        this->save();
    }
    else
    {
        cout << "输入有误" << endl;
        return;
    }


}

void WorkerManager::save()
{
    ofstream ofs;
    ofs.open("empFile.txt", ios::out);//
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << endl;
    }
    ofs.close();
}

//统计文件中的人数
int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open("empFile.txt", ios::in);
    int id;
    string name;
    int dId;
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        //统计人数
        num++;
    }
    ifs.close();
    return num;

}
//初始化职工
void WorkerManager::Init_Emp()
{
    ifstream ifs;
    ifs.open("empFile.txt", ios::in);
    int id;
    string name;
    int dId;
    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        Worker *worker = NULL;
        if(dId==1)
        {
            worker = new Employee(id, name, dId);
        }
        else if(dId==2)
        {
            worker = new Manager(id, name, dId);
        }
        else
        {
            worker = new Boos(id, name, dId);
        }
        this->m_EmpArray[index] = worker;
        index++;
    }
    ifs.close();
}
//显示所有职工
void WorkerManager::Show_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或为空" << endl;
    }
    else
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            //利用多态调用接口
            this->m_EmpArray[i]->ShowInfo();
        }
    }
    //按任意键清屏
    system("pause");
    system("cls");
}
//删除职工
void WorkerManager::Del_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或为空" << endl;
        return;
    }
    else
    {
        cout << "输入要删除的职工编号" << endl;
        int id = 0;
        cin >> id;
        int index = IsExist(id);
        if (index != -1)//存在
        {
            for(int i = index; i < this->m_EmpNum - 1; i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
            this->m_EmpNum--;
            this->save();
            cout << "删除成功" << endl;
        }
        else
        {
            cout << "删除失败，该职工不存在" << endl;
        }

    }
    system("pause");
    system("cls");
}
//判断职工是否存在，存在返回职工在数组中的位置，不存在返回-1
int WorkerManager::IsExist(int id)
{
    int index = -1;
    for (int i = 0; i < this->m_EmpNum; i++)
        if (this->m_EmpArray[i]->m_Id == id)
        {
            //找到了
            index = i;
            break;
        }
    return index;
}
//修改职工
void WorkerManager::Mod_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或为空" << endl;
    }
     else
    {
         cout << "输入要修改的职工编号" << endl;
         int id;
         cin >> id;

         int index = IsExist(id);
         if (index != -1)//存在
         {
             delete this->m_EmpArray[index];
             int newId=0;
             string newName="";
             int dSlect = 0;
             cout <<"‘查到："<<id<<"号职工，请输入新的职工编号："<<endl;
             cin >> newId;
             cout<<"请输入新的职工姓名："<<endl;
             cin >> newName;
             cout << "请选择该职工的岗位:" << endl;
             cout << "1.普通员工" << endl;
             cout << "2.经理" << endl;
             cout << "3.老板" << endl;
             cin >> dSlect;
             Worker *worker = NULL;
             switch (dSlect)
             {
                 case 1:
                     worker = new Employee(newId, newName, 1);
                     break;
                 case 2:
                     worker = new Manager(newId, newName, 2);
                     break;
                 case 3:
                     worker = new Boos(newId, newName, 3);
                     break;
                 default:
                     break;
             }
             this->m_EmpArray[index] = worker;
             this->save();
             cout << "修改成功" << endl;
         }
         else
         {
             cout << "修改失败，该职工不存在" << endl;
         }
    }
    system("pause");
    system("cls");
}
//查找职工
void WorkerManager::Find_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或为空" << endl;
    }
     else
    {
         cout << "输入要查找的方式：" << endl;
         cout << "1.按职工编号查找" << endl;
         cout << "2.按职工姓名查找" << endl;
         int way=0;
         cin >> way;
         if(way==1)
         {
             int id;
             cout << "输入要查找的职工编号" << endl;
             cin>>id;
             int index = IsExist(id);
             if (index != -1)//存在
             {
                 cout << "找到该职工" << endl;
                 this->m_EmpArray[index]->ShowInfo();
             }
             else
             {
                 cout << "查找失败，该职工不存在" << endl;
             }
         }
         else if(way==2)
         {
             string name;
             cout << "输入要查找的职工姓名" << endl;
             cin>>name;
             //加入判断是否查到
             bool isFind = false;
             for (int i = 0; i < this->m_EmpNum; i++)
             {
                 if (this->m_EmpArray[i]->m_Name == name)
                 {
                     cout << "找到该职工，职工编号为：" <<this->m_EmpArray[i]->m_Id<< endl;
                     isFind = true;
                     this->m_EmpArray[i]->ShowInfo();
                 }
             }
             if(!isFind)
             {
                 cout << "没有找到该职工" << endl;
             }
         }
         else
         {
             cout << "输入有误" << endl;
         }

    }
    system("pause");
    system("cls");
}
//排序职工
void WorkerManager::Sort_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或为空" << endl;
    }
    else
    {
        cout << "选择排序方式：" << endl;
        cout << "1.编号升序" << endl;
        cout << "2.编号降序" << endl;
        cout << "3.姓名升序" << endl;
        cout << "4.姓名降序" << endl;
        int way;
        cin >> way;
        for (int i = 0; i < this->m_EmpNum - 1; i++)
        {
            for (int j = 0; j < this->m_EmpNum - 1 - i; j++)
            {
                if (way == 1)
                {
                    if (this->m_EmpArray[j]->m_Id > this->m_EmpArray[j + 1]->m_Id)
                    {
                        Worker *temp = this->m_EmpArray[j];
                        this->m_EmpArray[j] = this->m_EmpArray[j + 1];
                        this->m_EmpArray[j + 1] = temp;
                        continue;
                    }
                }
                else if (way == 2)
                {
                    if (this->m_EmpArray[j]->m_Id < this->m_EmpArray[j + 1]->m_Id)
                    {
                        Worker *temp = this->m_EmpArray[j];
                        this->m_EmpArray[j] = this->m_EmpArray[j + 1];
                        this->m_EmpArray[j + 1] = temp;
                        continue;
                    }
                }
                else if (way == 3)
                {
                    if (this->m_EmpArray[j]->m_Name > this->m_EmpArray[j + 1]->m_Name)
                    {
                        Worker *temp = this->m_EmpArray[j];
                        this->m_EmpArray[j] = this->m_EmpArray[j + 1];
                        this->m_EmpArray[j + 1] = temp;
                        continue;
                    }
                }
                else if (way == 4)
                {
                    if (this->m_EmpArray[j]->m_Name < this->m_EmpArray[j + 1]->m_Name)
                    {
                        Worker *temp = this->m_EmpArray[j];
                        this->m_EmpArray[j] = this->m_EmpArray[j + 1];
                        this->m_EmpArray[j + 1] = temp;
                        continue;
                    }
                }
                else
                {
                    break;
                }
            }

        }
        cout <<"输入有误"<<endl;
    }
    system("pause");
    system("cls");
}
//清空文件
void WorkerManager::Clear_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或为空" << endl;
    }
    else
    {
        cout << "确定清空文件吗？" << endl;
        cout << "1.确定" << endl;
        cout << "2.取消" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            ofstream ofs(FILENAME, ios::trunc);
            ofs.close();
            if (this->m_EmpArray != NULL)
                delete []this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true;
            cout << "清空成功" << endl;
            system("pause");
            system("cls");
            Init_Emp();
            return;
        }
    }
}


//析构函数
WorkerManager::~WorkerManager()
{
    if (this->m_EmpArray != NULL)
    {
        delete []this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}
