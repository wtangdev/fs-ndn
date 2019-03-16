//
// Created by anson on 19-2-24.
//

#ifndef FS_NDN_INODE_HPP
#define FS_NDN_INODE_HPP

//#include "../fs.hpp"
#include "ndn-cpp/name.hpp"
//#include "inodedirectory.hpp"

using namespace std;

//class INodeDirectory;



class INode {
public:
    INode * parent;  // 父目录


    string getName();
    string getNdnStringName();
    ndn::Name getNdnName();
    string getNdnPath();
    string getPath();
    time_t getMtime();
    time_t getAtime();
    time_t getCtime();
    int getUserId();
    int getGroupId();
    virtual bool isNULL(){};

    bool isRoot();

    virtual bool isDirectory(){};
    INode();
    INode(string name, time_t mtime, time_t atime, time_t ctime);
    INode(INode * other);
    ~INode(){};

    // 此处我们认为标识两个INode就是name的不同
    bool operator==(const string & otherName) const;
    bool operator==(const INode * & otherNode) const;

    virtual void showChildrenLink(){};

protected:
    string filepath; // 文件在系统中的实际路径
    string name;    //文件或目录名
    ndn::Name ndn_name; // 文件的ndn名称
    time_t mtime;   // 最近一次修改文件内容的时间
    time_t atime;   // 最近访问时间
    time_t ctime;   // inode上一次变动时间

    // 构建新的INode
    // 复制已有的INode
//    ~ INode();




    int setNdnName(string name);
    int setMtime(time_t mtime);
    int setAtime(time_t atime);
    int setCtime(time_t ctime);

private:
    bool is_root = false;
    long long permission;   // 访问权限
    int user_id;
    int group_id;

};

// 设计一个空对象，用于在查询无此节点时返回
// 空对象的设置确实带来了一定的方便，但是会给程序设计时带来严重的内存泄漏风险，所以计划取消使用空对象类。
class EmptyINode:public INode {
public:
    EmptyINode();

    bool isNULL();
};



#endif //FS_NDN_INODE_HPP
