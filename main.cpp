#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include "identity.h"
#include "globalfile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"

using std::cout;
using std::cin;
using std::endl;


void TeacherMenu(Identity* teacher){
    while(true){
        teacher -> OpenMenu();

        Teacher *tea = (Teacher*)teacher;
        int select = 0;
        
        cin >> select;

        if(select == 1){
            cout << "显示所有订单" << endl;
            tea -> ShowAllOrder();
        }
        else if(select == 2){
            cout << "审核预约" << endl;
            tea -> VerifyOrder();
        }
        else{
            delete tea;
            cout << "退出登录" << endl;
            return;
        }
    }
}

void StudentMenu(Identity* student){
    while(true){
        student -> OpenMenu();

        Student *stu = (Student*)student;
        int select = 0;
        
        cin >> select;

        if(select == 1){
            cout << "申请预约" << endl;
            stu ->ApplyOrder();
        }
        else if(select == 2){
            cout << "查看我的预约" << endl;
            stu ->ShowMyOrder();
        }
        else if(select == 3){ 
            cout << "查看所有预约" << endl;
            stu -> ShowAllOrder();
        }
        else if(select == 4){
            cout << "取消预约" << endl;
            stu -> CancelOrder();
        }else{
            delete stu;
            cout << "退出登录" << endl;
            return;
        }
    }
}

void ManagerMenu(Identity* manager){        //这里为何要时用基类的指针？ 为何不能改成对象本身的指针？？？？
    while(true){
        manager -> OpenMenu();      //使用虚函数特性

        Manager *man = (Manager*)manager;   //注意此处的类转换
        int select = 0;

        cin >> select;

        if(select == 1){
            cout << "添加账号" << endl;
            man -> AddPerson();
        }
        else if(select == 2){
            cout << "查看账号" << endl;
            man -> ShowPerson();
        }
        else if(select == 3){ 
            cout << "查看机房" << endl;
            man -> ShowComputer();
        }
        else if(select == 4){
            cout << "清空预约" << endl;
            man -> CleanFile();
        }else{
            delete man;
            cout << "注销成功" << endl;
            return;
        }
    }
}


//具有登录功能的全局全局函数
void LogIn(string fileNmae, int type){
    Identity * person = NULL;   //定义抽象基类的指针可以指向具体类 

    std::ifstream ifs;
    ifs.open(fileNmae , std::ios::in);

    if(!ifs.is_open()){
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }

    int id = 0;
    string name;
    string pwd;
    //登录模块 1）学生  2）教师
    if(type == 1){
        cout << "请输入你的学号：" << endl;
        cin >> id;
    }else if(type == 2){
        cout << "请输入你的职工号：" << endl;
        cin >> id;
    }
    /*
     *关于cin的一些细节:
     *cin在输入过程中会忽略空格和换行符，
     *cin每次只读取一个单词，从第一个非空字符起到下一个空字符或换行符
     *cin在读取完一个完整的行后会将换行符留在输入流中
     *基于以上特性，如果连续的使用cin，可以不考虑处理流中的换行符
     */
 /*   while(cin.get() != '\n')*/
        /*continue;*/
    
    cout << "请输入用户名：" << endl;
    cin >> name;
    
    cout << "请输入密码：" << endl;
    cin >> pwd;
    
    //登录验证模块
    if(type == 1){
        int fid;
        string fname;
        string fpwd;

        /*需要改进的地方，登录验证使用循环逐一比对。
         *
         *
         *
         *
         *
         *
         *
         * 设想，如果是百万或千万条数据，该功能如何优化？*/
        while(ifs >> fid && ifs >> fname && ifs >> fpwd){
            if(id == fid && name == fname && pwd == fpwd){
                cout << "学生验证登录成功" << endl;
                person = new Student(id , name , pwd);
                StudentMenu(person);                
                return;
            }
        }
    }
    else if(type == 2){
        int fid;
        string fname;
        string fpwd;

        while(ifs >> fid && ifs >> fname && ifs >> fpwd){
            if(id == fid && name == fname && pwd == fpwd){
                cout << "教师验证登录成功" << endl;
                person = new Teacher(id , name , pwd);
                TeacherMenu(person);
                return;
            }
        }
    }
    else if(type == 3){
        string fname;
        string fpwd;

        while(ifs >> fname && ifs >> fpwd){
            if(name == fname && pwd == fpwd){
                cout << "管理员验证登录成功" << endl;
                person = new Manager(name , pwd);
                ManagerMenu(person);    
                return;
            }

        }
    }

    cout << "登录验证失败" << endl;
    return;
}

int main() {

	cout << "======================  欢迎来到传智播客机房预约系统  =====================" 
         << endl;
	cout << endl << "请输入您的身份" << endl;
	cout << "\t\t -------------------------------\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          1.学生代表           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          2.老    师           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          3.管 理 员           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          0.退    出           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t -------------------------------\n";
	cout << "输入您的选择: ";
   
    int select = 0;

    cin >> select;

    while(cin.get() != '\n')
        continue;

    switch (select) {
        case 1:     //student
            LogIn(STUDENT_FILE, 1);
            break;
        case 2:     //teachure
            LogIn(TEACHER_FILE, 2);
            break;
        case 3:     //root
            LogIn(ADMIN_FILE, 3);
            break;
        case 0:     //exit
            cout << "欢迎下一次使用" << endl;
            break;
        default:
            cout << "your enter error!" << endl;
            break;
    }

	return 0;

}
