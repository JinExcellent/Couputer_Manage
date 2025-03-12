#ifndef MANAGER_H_
#define MANAGER_H_

#include "computerRoom.h"
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include <string>
#include <vector>

class Manager: public Identity{
    private:
        std::vector<Student> vStu;
        std::vector<Teacher> vTea;
        std::vector<ComputerRoom> vRom;

    public:
        Manager();
        Manager(string name, string pwd);
        virtual void OpenMenu();
        void AddPerson();
        void ShowPerson();
        void ShowComputer();
        void CleanFile();
        void InitVectorMem();       //初始化成员信息vector
        void InitVectorRom();       //初始化机房信息vector
        bool CheckRepeat(int id, int type);
        friend void PrintStudent(Student & s);
        friend void PrintTeacher(Teacher & t);
};
#endif


