#ifndef STUDENT_H_
#define STUDENT_H_

#include "computerRoom.h"
#include "identity.h"
#include <fstream>
#include <istream>
#include <string>
#include <vector>


class Student: public Identity{
    private:
        int ID_;
        std::vector<ComputerRoom> vCom;
    public:
        Student();
        Student(int id , string name , string pwd);
        virtual void OpenMenu();
        void ApplyOrder();      //申请
        void ShowMyOrder();     //显示我的预约
        void ShowAllOrder();    //显示所有预约
        void CancelOrder();     //取消预约
        bool SetID_(std::ifstream & is);
        bool SetName_(std::ifstream & is);
        bool SetPwd_(std::ifstream & is);
        void InitVectorCom();   
        inline int GetID_() { return ID_; }
        inline string GetName_() { return Base_GetName_(); }
        inline string GetPwd_() { return Base_GetPwd_(); }
};
#endif
