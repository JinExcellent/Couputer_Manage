#include "orderfile.h"
#include "globalfile.h"
#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include <utility>

using std::cout;
using std::endl;
using std::string;

OrderFile::OrderFile(){
    std::ifstream ifs;

    ifs.open(ORDER_FILE, std::ios::in);

    string date;
    string interval;
    string stuid;
    string stuname;
    string roomid;
    string status;

    Size_ = 0;
    while(ifs >> date && ifs >> interval && ifs >> stuid && ifs >> stuname && ifs >> roomid && ifs >> status){
        //cout << date << interval << stuid << stuname << roomid << status << endl;
    
    
        string key;
        string value;
        std::map<string, string> m;
        //这是使用到了字符串处理技术和嵌套容器技术，需要深刻体会，融汇贯通 
        int pos = date.find(":");
        if(pos != -1){
            key = date.substr(0, pos);
            value = date.substr(pos + 1, date.size() - pos - 1);
            m.insert(std::make_pair(key, value));
        }

        pos = interval.find(":");
        if(pos != -1){
            key = interval.substr(0, pos);
            value = interval.substr(pos + 1, interval.size() - pos - 1);
            m.insert(std::make_pair(key, value));
        }

        pos = stuid.find(":");
        if(pos != -1){
            key = stuid.substr(0, pos);
            value = stuid.substr(pos + 1, stuid.size() - pos - 1);
            m.insert(std::make_pair(key, value));
        }

        pos = stuname.find(":");
        if(pos != -1){
            key = stuname.substr(0, pos);
            value = stuname.substr(pos + 1, stuname.size() - pos - 1);
            m.insert(std::make_pair(key, value));
        }

        pos = roomid.find(":");
        if(pos != -1){
            key = roomid.substr(0, pos);
            value = roomid.substr(pos + 1, roomid.size() - pos - 1);
            m.insert(std::make_pair(key, value));
        }

        pos = status.find(":");
        if(pos != -1){
            key = status.substr(0, pos);
            value = status.substr(pos + 1, status.size() - pos - 1);
            m.insert(std::make_pair(key, value));
        }
        
        OrderDate_.insert(std::make_pair(Size_, m));
        Size_++;
    }

    ifs.close();

    //test***********************************

    /*for(std::map<int,std::map<string,string>>::iterator it = OrderDate_.begin(); it != OrderDate_.end(); it++){*/
        /*cout << "No." << it->first << endl;*/
        /*for(std::map<string,string>::iterator mit = (*it).second.begin(); mit != (it->second).end(); mit++){*/
            /*cout << (*mit).first << ":" << mit->second << endl;*/
        /*}*/
    /*}*/

}


//更新预约，重写ORDER_FILE文件
//
/*需要改进的地方：
 *
 *
 * 当数据达到千万级规模时
 * ，该功能该如何优化？
 *
 *
 * */

void OrderFile::UpdataOrder(){
    if(Size_ == 0)
        return;

    std::ofstream ofs(ORDER_FILE, std::ios::out | std::ios::trunc);
    for(int i = 0; i < Size_; i++){
        ofs << "Date:" << OrderDate_[i]["Date"] << " ";
        ofs << "Interval:" << OrderDate_[i]["Interval"] << " ";
        ofs << "StuID:" << OrderDate_[i]["StuID"] << " ";
        ofs << "StuNam:" << OrderDate_[i]["StuNam"] << " ";
        ofs << "RoomID:" << OrderDate_[i]["RoomID"] << " ";
        ofs << "Status:" << OrderDate_[i]["Status"] << endl;
    }
    ofs.close();

}





















