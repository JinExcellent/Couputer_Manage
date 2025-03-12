#include "teacher.h"
#include "identity.h"
#include "orderfile.h"
#include <string>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::cin;


Teacher::Teacher(){
    ID_ = 0;
}

Teacher::Teacher(int id, string name, string pwd):ID_(id) , Identity(name, pwd){

}

void Teacher::OpenMenu(){
    cout << "欢迎教师：" << GetName_() << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.审核预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

void Teacher::ShowAllOrder(){
    OrderFile of;
    
    if(of.GetSize_() == 0){
        cout << "无预约记录" << endl;
        return;
    }
    
    int n = 1;

    for(int i = 0; i < of.GetSize_(); i++){
        cout << "学号" << of.GetMapMem(i, "StuID");
        cout << "(" << n++ << "):"; 
        cout << "日期：" << of.GetMapMem(i, "Date");
        cout << " 时间段：" << of.GetMapMem(i, "Interval");
        cout << " 机房号：" << of.GetMapMem(i, "RoomID");

        string status = " 状态：";
        if(of.GetMapMem(i, "Status") == "1"){
            status += "审核中";
        }
        else if(of.GetMapMem(i, "Status") == "2"){
            status += "已预约";
        }
        else if(of.GetMapMem(i, "Status") == "-1"){
            status += "预约失败";
        }
        else{
            status += "预约已取消";
        }

        cout << status << endl;
        cout << "========================================================" << endl;
        }
}

void Teacher::VerifyOrder(){
    OrderFile of;
    
    if(of.GetSize_() == 0){
        cout << "无预约记录" << endl;
        return;
    }
    
    std::vector<int> indx;
    int n = 1;

    for(int i = 0; i < of.GetSize_(); i++){
        if(of.GetMapMem(i ,"Status") == "1" || of.GetMapMem(i, "Status") == "2"){
            indx.push_back(i);
            cout << "(" << n++ << "):"; 
            cout << "学号" << of.GetMapMem(i, "StuID");
            cout << " 日期：" << of.GetMapMem(i, "Date");
            cout << " 时间段：" << of.GetMapMem(i, "Interval");
            cout << " 机房号：" << of.GetMapMem(i, "RoomID");

            string status = " 状态：";
            if(of.GetMapMem(i, "Status") == "1"){
                status += "审核中";
            }
            else if(of.GetMapMem(i, "Status") == "2"){
                status += "审核通过";
            }
            else if(of.GetMapMem(i, "Status") == "-1"){
                status += "审核不通过";
            }
            else{
                status += "预约已取消";
            }

            cout << status << endl;
            cout << "==================================================================" << endl;
        }
    }

    cout << "选择要审核的预约，(0):quit" << endl;
    int select = 0;
    
    while(true){
        cin >> select;
        if(select <= 0 || select > indx.size()){
            if(select == 0)
                return;
            cout << "范围：1 ~ " << indx.size() << endl; 

        }else{
            cout << "输入审核结果："<< endl;
            cout << "1) 通过" << endl;
            cout << "2) 不通过" << endl;
            cout << "0) 退出" << endl;
            int n = 0;
            
            cin >> n;
            if(n <= 0 && select > 2){
                if(select == 0)
                    return;
                cout << "范围：1 ~ 2"<< endl; 
            }else if(n == 1){
                of.SetMapMem(indx[select - 1], "Status", "2");
                of.UpdataOrder();
                cout << "审核成功" << endl;
                return;
            }else if(n == 2){
                of.SetMapMem(indx[select - 1], "Status", "-1");
                of.UpdataOrder();
                cout << "审核成功" << endl;
                return;
            }
        }
    } 
};

bool Teacher::SetID_(std::ifstream & is){
    if(is >> (this->ID_))
        return true;
   
    return false;
}

bool Teacher::SetName_(std::ifstream &is){
    string temp_name;

    if(is >> temp_name){
        Base_SetName_(temp_name);
        return true;
    }
    return false;
}

bool Teacher::SetPwd_(std::ifstream &is){
    string temp_pwd;

    if(is >> temp_pwd){
        Base_SetPwd_(temp_pwd);
        return true;
    }
    return false;
}


