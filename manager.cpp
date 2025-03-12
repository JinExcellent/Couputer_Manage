#include "manager.h"
#include "computerRoom.h"
#include "globalfile.h"
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>


using std::cout;
using std::endl;
using std::cin;
Manager::Manager(){
 
}

Manager::Manager(string name, string pwd):Identity(name, pwd){
    InitVectorMem();
    InitVectorRom();
}

void Manager::OpenMenu(){
//选择菜单
	cout << "欢迎管理员："<< this -> Base_GetName_() << "登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

void Manager::AddPerson(){
    cout << "请输入添加账号的类型:" << endl;
    cout << "1）添加学生" << endl;
    cout << "2) 添加老师" << endl;

    string fileName;
    string tip;
    string repeatTip;
    std::ofstream ofs;

    int select = 0;
    cin >> select;

    if(select == 1){
        fileName = STUDENT_FILE;
        tip = "请输入学号:";
        repeatTip = "学号重复，重新输入";
    }
    else{
        fileName = TEACHER_FILE;
        tip = "请输入职工编号:";
        repeatTip = "职工号重复，重新输入";
    }

    ofs.open(fileName, std::ios::out | std::ios::app);
    int id;
    string name;
    string pwd;
    
    cout << tip << endl;
    
    while(true){
        cin >> id;

        bool ret = this -> CheckRepeat(id, select);     //添加数据时做重复性检测

        if(ret)
            cout << repeatTip << endl;
        else
            break;
    }

    cout << "请输入姓名:" << endl;
    cin >> name;

    cout << "请输入密码:" << endl;
    cin >> pwd;

    ofs << id << " " << name << " " << pwd << endl;
    ofs.close();
    InitVectorMem();   //这语句是解决添加人员后，数据不能及时更新到vector中的bug，但这也带来了另一个问题。效率问题：每次添加成员后都需要将vector中的容器清除后再读取文件并重新写入。
}

void PrintStudent(Student & s){
    cout << "ID：" << s.GetID_() << "\t姓名" << s.GetName_() << "\t密码：" << s.GetPwd_() << endl;
}

void PrintTeacher(Teacher & t){
    cout << "ID：" << t.GetID_() << "\t姓名" << t.GetName_() << "\t密码：" << t.GetPwd_() << endl;
}


void Manager::ShowPerson(){
    cout << "请选择查看的内容：" << endl;     
    cout << "1）查看所有学生" << endl;     
    cout << "2）查看所有老师" << endl;

    int select = 0;

    cin >> select;
    if(select == 1){
        cout << "学生信息：" << endl;
        for_each(vStu.begin(), vStu.end(), PrintStudent);
    }
    else{
        cout << "老师信息：" << endl;
        for_each(vTea.begin(), vTea.end(), PrintTeacher);
    }
}

void Manager::ShowComputer(){
    cout << "机房信息：" << endl;
    for(std::vector<ComputerRoom>::iterator it = vRom.begin(); it != vRom.end(); it++){
        cout << "机房编号：" << it -> GetRoomID() << "机器数：" << it -> GetMaxNum() << endl;
    }
}

void Manager::CleanFile(){
    std::ofstream ofs;
    ofs.open(ORDER_FILE , std::ios::trunc);

    if(!ofs.is_open()){
        cout << "打开文件失败" << endl;
        return;
    }

    cout << "清理成功！" << endl;
    return;
}

void Manager::InitVectorMem(){
    
    vStu.clear();
    vTea.clear();
        cout << "********************" << endl;
    std::ifstream ifs;
    ifs.open(STUDENT_FILE, std::ios::in);
    if(!ifs.is_open()){
        cout << "文件读取错误" << endl;
        return;
    }
    
    Student s;
    
    while(s.SetID_(ifs) && s.SetName_(ifs) && s.SetPwd_(ifs)){
        vStu.push_back(s);
    }
    cout << "当前学生数量为：" << vStu.size() << endl;
    ifs.close();
    
    ifs.open(TEACHER_FILE, std::ios::in);
    if(!ifs.is_open()){
        cout << "文件读取错误" << endl;
        return;
    }
    Teacher t;

    while(t.SetID_(ifs) && t.SetName_(ifs) && t.SetPwd_(ifs)){
        vTea.push_back(t);
    }
    cout << "当前老师数量为：" << vStu.size() << endl;
    ifs.close();

}

bool Manager::CheckRepeat(int id, int type){
    if(type == 1){
        for(std::vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++){
            if(id == it->GetID_())
                return true;
        }
    }
    else{
        for(std::vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++){
            if(id == it->GetID_())
                return true;
        }

    }

    return false;
}

void Manager::InitVectorRom(){
    std::ifstream ifs;

    ifs.open(COMPUTER_FILE, std::ios::in);

    if(!ifs.is_open()){
        cout << "打开文件失败" << endl;
        return;
    }
    
    ComputerRoom r;

    while(r.SetRoomID(ifs) && r.SetMaxNum(ifs)){
        vRom.push_back(r);
    }

    cout << "当前机房数量为：" << vRom.size() << endl;

    ifs.close();
}






























