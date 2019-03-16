//#include <utility>

//
// Created by anson on 19-2-24.
//

#include "inode.hpp"
#include "../fs.hpp"
#include "../logger.hpp"

INode::INode() {
    ndn_name = "";
    mtime = 0;
    atime = 0;
    ctime = 0;
    user_id = fsndn::user_id;
    group_id =fsndn::group_id;
}

INode::INode(string node_name, time_t mtime, time_t atime, time_t ctime) {
    // 获取文件路径
    if (node_name == "/") {
        this->is_root = true;
    }
    string pathname = fsndn::root_path;
    pathname.append(node_name);
    this->filepath = pathname;
    string prefix = fsndn::global_prefix;
    prefix.append(node_name);
    ndn::Name ndn_name(prefix);
    this->ndn_name = ndn_name;
    this->name = ndn_name.getSubName(-1).toUri().substr(1);
    this->mtime = mtime;
    this->atime = atime;
    this->ctime = ctime;
    user_id = fsndn::user_id;
    group_id = fsndn::group_id;
//    cout<< " XX "<< node_name<< " ndn_name: "<< ndn_name<< " name: "<< name<< " file_path: "<< filepath<< endl;
}

INode::INode(INode * other) {
    ndn_name = other->ndn_name;
    name = other->name;
    mtime = other->mtime;
    atime = other->atime;
    ctime = other->ctime;
    user_id = other->getUserId();
    group_id = other->getGroupId();
    this->filepath = other->filepath;
}

bool INode::operator==(const string & otherName) const {
    return name == otherName;
}

bool INode::operator==(const INode * & otherNode) const {
    return name == otherNode->name;
}

string INode::getPath() {
    return this->filepath;
}

time_t INode::getAtime() {
    return this->atime;
}

time_t INode::getMtime() {
    return this->mtime;
}

time_t INode::getCtime() {
    return this->ctime;
}

int INode::getGroupId() {
    return this->group_id;
}

int INode::getUserId() {
    return this->user_id;
}

string INode::getNdnStringName() {
    return this->ndn_name.toUri();
}

ndn::Name INode::getNdnName() {
    return ndn_name;
}

string INode::getNdnPath() {
    ndn::Name root_prefix(fsndn::global_prefix);
    return ndn_name.getSubName(root_prefix.getComponentCount()).toUri();
}

string INode::getName() {
    return this->name;
}

int INode::setNdnName(string name) {
    this->ndn_name = name;
}

int INode::setAtime(time_t atime) {
    this->atime = atime;
}

int INode::setCtime(time_t ctime) {
    this->ctime = ctime;
}

int INode::setMtime(time_t mtime) {
    this->mtime = mtime;
}

bool INode::isRoot() {
    return is_root;
}

EmptyINode::EmptyINode(){
    name = "EmptyINode";
    mtime = -1;
    atime = -1;
    ctime = -1;
}

bool EmptyINode::isNULL() {
    return true;
}


