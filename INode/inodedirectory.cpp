//
// Created by anson on 19-2-24.
//

#include "inodedirectory.hpp"
#include "../logger.hpp"
#include "sys/stat.h"

list<INode *>::iterator find(list<INode *>::iterator begin, list<INode *>::iterator end, string name) {
    list<INode *>::iterator it;
    for (it = begin; it != end; it++) {
        if ((*it)->getName() == name) {
//            cout<< "找到了\n";
            break;
        }
    }
    return it;
}

inline int split_all_component(const std::string &path, std::vector<std::string> & components) {
    std::string pathcopy = path;
    components.push_back("/");
    size_t first_comp_pos = pathcopy.find('/');
    while(first_comp_pos != std::string::npos) {
        if (first_comp_pos != 0)
            components.push_back(pathcopy.substr(0, first_comp_pos));
        pathcopy = pathcopy.substr(first_comp_pos+1);
        first_comp_pos = pathcopy.find('/');
    }
    components.push_back(pathcopy.substr(0, first_comp_pos));

    return 1;
}

INodeDirectory::INodeDirectory() : INode() {

}

// 按照扁平化和结构化共存的设计理念，用户不会主动去创建目录，所以所有的目录均是由INodeFile类
// 创建的，用户指明路径（名称），系统自动创建相应的路径，方便结构化访问。
INodeDirectory::INodeDirectory(string name, time_t mtime, time_t atime, time_t ctime) : INode(name, mtime, atime, ctime) {
    // 使用mkdir系统调用创建一个真实的文件夹
    // TODO: 研究是否需要创建一个真实的文件夹，直接扁平化的存储是否可行
    // TODO: 用户无需创建真实的目录，读取文件所处的目录只需要使用名称匹配即可
    mkdir(this->getPath().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
//    cout<< this->getPath()<< endl;
}

INodeDirectory::INodeDirectory(INodeDirectory * other) : INode((INode *)other){
    children = other->getChildren();
}

INodeDirectory::~INodeDirectory() {
    list<INode *>::iterator it;
    for (it=children.begin(); it != children.end();) {
//        delete * it;
// TODO: Figure out wether there is a memory leak
        it = children.erase(it);
    }
}

list<INode *> INodeDirectory::getChildren() {
    list<INode *> new_children;
    copy(children.begin(), children.end(), back_inserter(new_children));
    return new_children;
}

bool INodeDirectory::isNULL() {
    return false;
}

bool INodeDirectory::isDirectory() {
    return true;
}

bool INodeDirectory::removeChildLink(INode *node){
    // 此处hadoop实现的是二分查找
    list<INode *>::iterator it = find(children.begin(), children.end(), node->getName());
    if (it == children.end()) {
        FILE_LOG(LOG_ERROR)<< "Remove child error, no such inode"<< endl;
        return false;
    }
    children.remove(node);
    return true;
}

bool INodeDirectory::replaceChildLink(INode *newChild){
    if(children.size() == 0) {
        FILE_LOG(LOG_ERROR)<< "Replace child: The directory is empty"<< endl;
        return false;
    }
    list<INode *>::iterator it;
    it = find(children.begin(), children.end(), newChild->getName());
    if (it == children.end()) {
        FILE_LOG(LOG_ERROR)<< "The directory has no node named "<< newChild->getName()<< endl;
        return false;
    }
    replace(children.begin(), children.end(), *it, newChild);
    return true;
}

INode * INodeDirectory::getChildNodeLink(string name){
    if (children.size() == 0) {
        // TODO: When to release it
        EmptyINode * emptyINode = new EmptyINode;
        FILE_LOG(LOG_DEBUG)<< "The directory is empty "<<name << endl;
        // 无子节点，返回一个空INode
        return emptyINode;
    }
    list<INode *>::iterator it;
    it = find(children.begin(), children.end(), name);
    if (it == children.end()){
        // TODO: When to release it
        EmptyINode * emptyINode = new EmptyINode;
        FILE_LOG(LOG_DEBUG)<< "No such INode"<< endl;
        // 查无此节点，返回空节点
        return emptyINode;
    }
    return (*it);
}

INode * INodeDirectory::getNodeLink(string path){
    vector<string> components;
    split_all_component(path, components);
    INode ** node = new INode*[1];
    node[0] = new EmptyINode;
    getExistingPathINodesLink(components, node, 1-components.size());
    return node[0];
}

INode ** INodeDirectory::getNodesLink(string path){
    vector<string> components;
    split_all_component(path, components);
    INode ** nodes = new INode*[components.size()];
    for(int i = 0; i < components.size(); i++) {
        nodes[i] = new EmptyINode();    // 全部初始化为空对象
    }
    getExistingPathINodesLink(components, nodes, 0);
    return nodes;
}

int INodeDirectory::getExistingPathINodesLink(vector<string> components, INode ** existing, int index) {
    INode * curNode = this;
    int count = 0;
    if (index > 0)
        index = 0;
    while (count < components.size() && !curNode->isNULL()) {
//        cout<<curNode->getName()<< " "<< (void *) curNode<< " ";
        if (index >= 0) {
            delete existing[index];
            existing[index] = curNode;
        }
        if(!curNode->isDirectory() || count == components.size()-1){
            break;
        }
        INodeDirectory * parentDir = (INodeDirectory *) curNode;
        curNode = parentDir->getChildNodeLink(components[count+1]);
        count++;
        index++;
    }
    return count;
}

int INodeDirectory::addChild(INode * node) {
    list<INode *>::iterator it;
    it = find(children.begin(), children.end(), node->getName());
    if (it != children.end()) {
        FILE_LOG(LOG_ERROR)<< "You cannot add a node that the name has alreay exists"<< endl;
        return -1;
    }
    node->parent = this;
    children.push_back(node);
    INode * n1 = children.front();
    setMtime(node->getMtime());
    return 0;
}

void INodeDirectory::showChildrenLink() {
    for (auto item : children) {
        cout<< item->getName()<< " ";
    }
    cout<< endl;
}

INode * INodeDirectory::nextChild(string name) {
    if (name.length() == 0) {
        FILE_LOG(LOG_ERROR)<< "Empty Name"<< endl;
        // TODO: When to release it
        EmptyINode * emptyINode = new EmptyINode;
        return emptyINode;
    }
    list<INode *>::iterator it = find(children.begin(), children.end(), name);
    it++;
    return *it;
}

int INodeDirectory::addNode(string path, INode * newNode) {
    INode * curNode = getNodeLink(path);
    if (curNode->isNULL()) {
        delete(curNode);
        FILE_LOG(LOG_ERROR)<<"No such path!"<< endl;
        return -1;
    }
    INodeDirectory * parentDir =  (INodeDirectory *) curNode;
    parentDir->addChild(newNode);
    return 0;
}

int INodeDirectory::clearAllBlockLink() {
    int total = 1;
    if (children.size() == 0) {
        return total;
    }
    for (INode * child : children) {
        INodeDirectory * childDir = (INodeDirectory *) child;
        total += childDir->clearAllBlockLink();
    }

    delete(parent);
    return total;
}

// 使用
void INodeDirectory::showChildren() {

}
