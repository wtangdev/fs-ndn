//
// Created by anson on 19-2-24.
//

#ifndef FS_NDN_INODEDRIECTORY_HPP
#define FS_NDN_INODEDRIECTORY_HPP

#include "inode.hpp"
#include "bits/stdc++.h"

class INodeDirectory: public INode {
public:
    INodeDirectory();
    // 建造初始目录，所以没有子目录
    INodeDirectory(string name,time_t mtime,time_t atime,time_t ctime);
    // 从已有的目录中复制
    INodeDirectory(INodeDirectory * other);
    ~INodeDirectory();

    /* 计划采用两种方式组织目录的孩子节点，一种就是按照传统的模式，每个节点有一个父亲节点，
     * 每一个节点同时也有一个孩子链表，这个链表里面存有孩子节点的指针，据此提供相关操作；
     * 第二种即采用NDN的思想，扁平化存储所有的文件，以名字来区分节点所处的层级，根据哈希算法
     * 查找孩子节点、父节点等操作。
     */

    void showChildrenLink();
    void showChildren();


    // 是目录吗
    bool isDirectory();
    // 重载null
    bool isNULL();
    // 移除节点
    bool removeChildLink(INode * node);
    bool removeChild(INode * node);
    // 用newChild替换与newChild同名的子节点
    bool replaceChildLink(INode * newChild);
    bool replaceChild(INode * newChild);
    // 获得孩子节点
    INode * getChildNodeLink(string name);
    INode * getChildNode(string name);
    // 获取给定路径上的INode
    INode * getNodeLink(string path);
//    int getNodeLink(string path, INode * );
    INode * getNode(string path);
    // 获取指定路径上的所有INode
    INode ** getNodesLink(string path);
//    int getNodesLink(string path, INode ** );
    INode ** getNodes(string path);
    // 获取指定路径上的所有节点
    int getExistingPathINodesLink(vector<string> components, INode ** existing, int index);
    int getExistingPathINodes(vector<string> components, INode ** existing, int index);
    // 在目录中添加子节点, NDN方法无需添加孩子节点
    int addChild(INode * node);
    // 根据一个子节点的名称查找下一个子节点的index
    INode * nextChildLink(string name);
    INode * nextChild(string name);
    // 给指定的目录添加子节点,NDN方法无需添加节点
    int addNode(string path, INode * newNode);
    // 递归删除当前目录下的所有block
    int clearAllBlockLink();
    int clearAllBlock();

    // 修改为通过饮用返回参数，而不是使用返回值，从而减小内存泄漏的风险
    int getChildren(list<INode *> & new_children);





private:
    list<INode *> children; // 子目录或文件
};


#endif //FS_NDN_INODEDRIECTORY_HPP
