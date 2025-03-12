#ifndef IDENTITY_H_
#define IDENTITY_H_

#include <fstream>
#include <string>

using std::string;

//abstract base class

class Identity{
    private:
        string  Name_;
        string  Pwd_;
    protected:
        inline string Base_GetName_(){ return Name_; }
        inline string Base_GetPwd_(){ return Pwd_; }
        inline void Base_SetName_(string name) { Name_ = name; }
        inline void Base_SetPwd_(string pwd) {Pwd_ = pwd; }

    public:
        virtual void OpenMenu() = 0;
        Identity(){};
        Identity(string name, string pwd):Name_(name), Pwd_(pwd) { }
};


#endif
