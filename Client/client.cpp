#include "client.h"
#include "../NameNode/namenode.hpp"
#include "../fs.hpp"
#include "../logger.hpp"
#include "thread"

void
writeThread(vector<DataNodeClient>::iterator it, string name, const char *content, int size,
            int seg) {
    int seg_size = fsndn::seg_size;
    char *temp_content = new char[size];
    memcpy(temp_content, content + (seg * seg_size), size);
    (*it).addFileSeg(name, temp_content, size, seg);
    delete[] temp_content;
}

void
readThread(vector<DataNodeClient>::iterator it, string name, char *buffer, int get_size,
           int get_seg) {
    int seg_size = fsndn::seg_size;
    char *temp_content = new char[get_size];
    (*it).getFileSeg(name, temp_content, get_size, get_seg);
    memcpy(buffer + (get_seg * seg_size), temp_content, get_size);
    delete[] temp_content;
}

void
writeFileThread(vector<DataNodeClient>::iterator it, string name, string file_path, int size,
                int seg) {
    int seg_size = fsndn::seg_size;
    char *temp_content = new char[size];
    ifstream fin(file_path, ios::binary | ios::in);
    fin.seekg(seg * seg_size);
    fin.read(temp_content, size);
    fin.close();
    (*it).addFileSeg(name, temp_content, size, seg);
    delete[] temp_content;
}

void
readFileThread(vector<DataNodeClient>::iterator it, string name, char *buffer, int get_size,
               int get_seg, int node_seg_count) {
    int seg_size = fsndn::seg_size;
    char *temp_content = new char[get_size];
    (*it).getFileSeg(name, temp_content, get_size, get_seg);
    memcpy(buffer + (node_seg_count * seg_size), temp_content, get_size);
    delete[] temp_content;
}


Client::Client() {}

int
Client::addNameNode(string ip, int node_id) {
    NameNodeClient client(
            grpc::CreateChannel(ip, grpc::InsecureChannelCredentials()), node_id);
    this->name_nodes.push_back(client);
    return 0;
}

int
Client::removeNameNode(int node_id) {
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
Client::addDataNode(string ip, int node_id) {
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
Client::removeDataNode(int node_id) {
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
                   const char *content,
                   long long size,
                   time_t mtime,
                   time_t atime,
                   time_t ctime) {
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
            thread t(writeThread, ref(it), name, content, insert_size, insert_seg);
            t.join();
//            writeThread(it, name, content, insert_size, insert_seg);
        }
    }
    return 0;
}

int
Client::readFile(string name, char *buffer, long long size) {
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
            thread t(readThread, ref(it), name, buffer, get_size, get_seg);
            t.join();
//            readThread(it, name, buffer, get_size, get_seg);
        }
    }
    return 0;
}

void
Client::updateNodes() {
    sort(this->data_nodes.begin(), this->data_nodes.end());
}

int Client::addNewFile(string name, string file_path, time_t mtime, time_t atime, time_t ctime) {
    ifstream fin(file_path, ios::binary | ios::in);

    // 计算文件大小
    // 记录当前位置
    long long current_pos = fin.tellg();
    fin.seekg(0, ios_base::end); // 移动到末尾
    //        istream::pos_type file_size = fin.tellg();  //
    // 此时的位置显然就是文件大小
    long long file_size = fin.tellg();
    fin.seekg(current_pos); // 回到初始位置
    fin.close();

    // 访问名称节点，生成named data元数据信息并获得写入索引
    vector<SegIndex> store_segs;
    store_segs =
            this->name_nodes[0].addNewFile(name, file_size, mtime, atime, ctime);

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
            thread t(writeFileThread, ref(it), name, file_path, insert_size, insert_seg);
            t.join();
//            writeThread(it, name, content, insert_size, insert_seg);
        }
    }

    return 0;
}

int Client::readFile(string name, string file_path) {
    // 计划每次读完一个datanode中所有的段，如果大于500个，就每500个为一次的读，也就是500m,然后开始写入
    int seg_size = fsndn::seg_size;
    long long buffer_size = seg_size * 500;

    long long file_size = this->name_nodes[0].getFileSize(name);

    // 向NameNode发送读请求，获得文件所在位置和分块信息
    vector<SegIndex> store_segs;
    store_segs = this->name_nodes[0].readFile(name);

    // TODO:并行写入
    ofstream fout(file_path, ios::binary);
    char *buffer = new char[buffer_size];
    for (SegIndex si : store_segs) {
        int node_id = si.node;
        vector<DataNodeClient>::iterator it =
                find(this->data_nodes.begin(), this->data_nodes.end(), node_id);
        int node_seg_count = 0;
        long long curr_size = 0; // 当前读了多少字节
        int curr_seg = 0; // 当前应当从哪一个段开始写
        memset(buffer, 0, buffer_size);
        for (SegWithSize ss : si.segs) {
            int get_seg = ss.seg;
            int get_size = ss.size;
            curr_size += get_size;
            // 记录当前节点的第一个段
            if (node_seg_count == 0) {
                curr_seg = get_seg;
            }
            thread t(readFileThread, ref(it), name, buffer, get_size, get_seg, node_seg_count);
            t.join();
            node_seg_count++;
            // 已经读到buffer满了
            if (curr_size + seg_size >= buffer_size) {
                fout.seekp(seg_size * curr_seg);
                FILE_LOG(LOG_DEBUG)<< "seg: "<< seg_size*curr_seg<< endl;
                fout.write(buffer, curr_size);
                fout.flush();
                node_seg_count = 0;
                curr_size = 0;
                memset(buffer, 0, buffer_size);
            }
        }
        // 剩下的写进去
        fout.seekp(seg_size * curr_seg);
        fout.write(buffer, curr_size);
        fout.flush();
    }
    fout.close();
    delete [] buffer;

    return 0;
}


