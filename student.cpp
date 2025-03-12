#include "student.h"
#include "computerRoom.h"
#include "globalfile.h"
#include "identity.h"
#include "orderfile.h"
#include <cstdlib>
#include <fstream>
#include <ostream>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::cin;
Student::Student(){

}

Student::Student(int id , string name , string pwd):ID_(id), Identity(name, pwd){
    InitVectorCom();
}

void Student::OpenMenu(){
    cout << "欢迎学生代表：" << this->GetName_() << "登录！" << endl;
	
    cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          1.申请预约              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          2.查看我的预约          |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          3.查看所有预约          |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          4.取消预约              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

void Student::InitVectorCom(){
    vCom.clear();

    std::ifstream ifs;
    ifs.open(COMPUTER_FILE, std::ios::in);

    if(!ifs.is_open()){
        cout << "打开文件失败" << endl;
        return;
    }

    ComputerRoom c;
    while(c.SetRoomID(ifs) && c.SetMaxNum(ifs)){
       vCom.push_back(c);
    }

    ifs.close();
}

void Student::ApplyOrder(){
    cout << "机房开放时间为周一至周五！" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl; 

    int date = 0;
    int interval = 0;
    int room = 0;

    while(true){
        cin >> date;
        
        if(date >= 1 && date <= 5){
            break;
        }

        cout << "输入有误（1-5）" << endl;
    }	

    cout << "请输入申请预约的时间段：" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;
     
    while(true){
        cin >> interval;
        
        if(interval >= 0 && interval <= 2){
            break;
        }

        cout << "输入有误（1-2）" << endl;
    }	

    cout << "选择机房：" << endl;
    cout << "1号机房：" << vCom[0].GetMaxNum() << endl;
    cout << "2号机房：" << vCom[1].GetMaxNum() << endl;
    cout << "3号机房：" << vCom[2].GetMaxNum() << endl;

    while(true){
        cin >> room;
        
        if(room >= 1 && room <= 3){
            break;
        }

        cout << "输入有误（1-3）" << endl;
    }

    cout << "预约成功,等待审核" << endl;

    std::ofstream ofs(ORDER_FILE, std::ios::out | std::ios::app);
    ofs << "Date:" << date << " ";
    ofs << "Interval:" << interval << " ";
    ofs << "StuID:" << GetID_() << " ";
    ofs << "StuNam:" << GetName_() << " ";
    ofs << "RoomID:" << room << " ";
    ofs << "Status:" << 1 << endl;
    
    ofs.close();
}

void Student::ShowMyOrder(){
    OrderFile of;
    
    if(of.GetSize_() == 0){
        cout << "无预约记录" << endl;
        return;
    }
    
    for(int i = 0; i < of.GetSize_(); i++){
        if(GetID_() == atoi(of.GetMapMem(i, "StuID").c_str())){
            cout << "日期：" << of.GetMapMem(i, "Date") << endl;
            cout << "时间段：" << of.GetMapMem(i, "Interval") << endl;
            cout << "机房号：" << of.GetMapMem(i, "RoomID") << endl;
        
            string status = "状态：";
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
            cout << "=====================" << endl;
        }
    }
    
}

void Student::ShowAllOrder(){
     OrderFile of;
    
    if(of.GetSize_() == 0){
        cout << "无预约记录" << endl;
        return;
    }
    
    for(int i = 0; i < of.GetSize_(); i++){
        cout << "学号：" << of.GetMapMem(i, "StuID") << endl;
        cout << "日期：" << of.GetMapMem(i, "Date") << endl;
        cout << "时间段：" << of.GetMapMem(i, "Interval") << endl;
        cout << "机房号：" << of.GetMapMem(i, "RoomID") << endl;
    
        string status = "状态：";
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
        cout << "=====================" << endl;
    }
    
}

void Student::CancelOrder(){
    OrderFile of;
    
    if(of.GetSize_() == 0){
        cout << "无预约记录" << endl;
        return;
    }
    
    std::vector<int> indx;
    int n = 1;

    for(int i = 0; i < of.GetSize_(); i++){
        if(GetID_() == atoi(of.GetMapMem(i, "StuID").c_str())){
            if(of.GetMapMem(i ,"Status") == "1" || of.GetMapMem(i, "Status") == "2"){
                indx.push_back(i);
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
                cout << "======================================" << endl;
            }
        }
    }

    cout << "选择要取消的预约，(0):quit" << endl;
    int select = 0;
    
    while(true){
        cin >> select;
        if(select <= 0 || select > indx.size()){
            if(select == 0)
                return;
            cout << "范围：1 ~ " << indx.size() << endl; 

        }else{
            cout << of.GetMapMem(indx[select - 1], "Status") << endl;
            of.SetMapMem(indx[select - 1], "Status", "0");
            cout << of.GetMapMem(indx[select - 1], "Status") << endl;
            of.UpdataOrder();
            cout << "取消成功" << endl;
            return;
        }
    }

}

bool Student::SetID_(std::ifstream & is){
    if(is >> (this->ID_))
        return true;
   
    return false;
}

bool Student::SetName_(std::ifstream &is){
    string temp_name;

    if(is >> temp_name){
        Base_SetName_(temp_name);
        return true;
    }
    return false;
}

bool Student::SetPwd_(std::ifstream &is){
    string temp_pwd;

    if(is >> temp_pwd){
        Base_SetPwd_(temp_pwd);
        return true;
    }
    return false;
}






