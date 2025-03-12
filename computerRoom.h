#ifndef COMPUTERROOM_H_
#define COMPUTERROOM_H_

#include <fstream>

class ComputerRoom{
    private:
        int RoomID;
        int MaxNum;
    public:
        inline int GetRoomID(){ return RoomID; }
        inline int GetMaxNum() {return MaxNum; }
        inline bool SetRoomID(std::ifstream & is){ return (is >> RoomID)?true:false; }
        inline bool SetMaxNum(std::ifstream & is){ return (is >> MaxNum)?true:false; }
};
#endif
