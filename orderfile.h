#ifndef ORDERFILE_H_
#define ORDERFILE_H_

#include <string>
#include <map>

class OrderFile{
    private:
        std::map<int, std::map<std::string, std::string>> OrderDate_;
        int Size_;      //记录容器中的元素个数,并作为内部容器的key值
    public:
        OrderFile();
        ~OrderFile() {};
        void UpdataOrder();
        inline std::string GetMapMem(const int indx , const char * ch){
            return OrderDate_[indx][ch];
        }
        inline void SetMapMem(const int indx, const char* ch , const std::string val){
            OrderDate_[indx][ch] = val;
        }
        inline int GetSize_(){ return Size_; }
};

#endif
