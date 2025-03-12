#ifndef TEACHER_H_
#define TEACHER_H_

#include "identity.h"
#include <string>

class Teacher: public Identity{
    private:
        int ID_;
    public:
        Teacher();
        Teacher(int id, string name , string pwd);
        virtual void OpenMenu();
        void ShowAllOrder();
        void VerifyOrder();
        bool SetID_(std::ifstream & is);
        bool SetName_(std::ifstream & is);
        bool SetPwd_(std::ifstream & is);
        inline int GetID_() { return ID_; }
        inline string GetName_() { return Base_GetName_(); }
        inline string GetPwd_() { return Base_GetPwd_(); }
};
#endif
