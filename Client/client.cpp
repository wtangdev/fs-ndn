#include "client.h"
#include "../NameNode/namenode.hpp"
#include "../fs.hpp"
#include "../logger.hpp"

Client::Client() {}

int
Client::addNameNode(string ip, int node_id)
{
    NameNodeClient client(
      grpc::CreateChannel(ip, grpc::InsecureChannelCredentials()), node_id);
    this->name_nodes.push_back(client);
    return 0;
}

int
Client::removeNameNode(int node_id)
{
    vector<NameNodeClient>::iterator it =
      find(name_nodes.begin(), name_nodes.end(), node_id);
    if (it == name_nodes.end()) {
        FILE_LOG(LOG_ERROR)
          << "Remove NameNode failed, No NameNode named " << node_id << endl;
        return -1;
    }
    this->name_nodes.erase(it);
    return 0;
}

int
Client::addDataNode(string ip, int node_id)
{
    // TODO: 目前考虑的是单个namenode的情况。
    DataNodeClient client(
      grpc::CreateChannel(ip, grpc::InsecureChannelCredentials()), node_id);
    this->data_nodes.push_back(client);
    this->updateNodes();
    // 给NameNode添加该DataNode,目前认为只有一个NamenNode，所以直接选择0
    this->name_nodes[0].addDataNode(ip, node_id);
    return 0;
}

int
Client::removeDataNode(int node_id)
{
    vector<DataNodeClient>::iterator it =
      find(data_nodes.begin(), data_nodes.end(), node_id);
    if (it == data_nodes.end()) {
        FILE_LOG(LOG_ERROR)
          << "Remove DataNode failed, No DataNode named " << node_id << endl;
        return -1;
    }
    this->data_nodes.erase(it);
    this->name_nodes[0].removeDataNode(node_id);
    return 0;
}

int
Client::addNewFile(string name,
                   const char* content,
                   long long size,
                   time_t mtime,
                   time_t atime,
                   time_t ctime)
{
    // 访问名称节点，生成named data元数据信息并获得写入索引
    vector<SegIndex> store_segs;
    store_segs =
      this->name_nodes[0].addNewFile(name, size, mtime, atime, ctime);
    // 文件分段信息已由NameNode生成，写入DataNode
    int seg_size = fsndn::seg_size;
    // TODO: 并行写入
    for (SegIndex si : store_segs) {
        int node_id = si.node;
        vector<DataNodeClient>::iterator it =
          find(this->data_nodes.begin(), this->data_nodes.end(), node_id);
        for (SegWithSize ss : si.segs) {
            int insert_seg = ss.seg;
            int insert_size = ss.size;
            char* temp_content = new char[insert_size];
            memcpy(
              temp_content, content + (insert_seg * seg_size), insert_size);
            (*it).addFileSeg(name, temp_content, insert_size, insert_seg);
            delete[] temp_content;
        }
    }
    return 0;
}

int
Client::readFile(string name, char* buffer, long long size)
{
    // TODO:检索本地缓存
    // 向NameNode发送读请求，获得文件所在位置和分块信息
    vector<SegIndex> store_segs;
    store_segs = this->name_nodes[0].readFile(name);
    // TODO:并行读取
    int seg_size = fsndn::seg_size;
    for (SegIndex si : store_segs) {
        int node_id = si.node;
        vector<DataNodeClient>::iterator it =
          find(this->data_nodes.begin(), this->data_nodes.end(), node_id);
        for (SegWithSize ss : si.segs) {
            int get_seg = ss.seg;
            int get_size = ss.size;
            char* temp_content = new char[get_size];
            (*it).getFileSeg(name, temp_content, get_size, get_seg);
            memcpy(buffer + (get_seg * seg_size), temp_content, get_size);
            delete[] temp_content;
        }
    }
    return 0;
}

void
Client::updateNodes()
{
    sort(this->data_nodes.begin(), this->data_nodes.end());
}
