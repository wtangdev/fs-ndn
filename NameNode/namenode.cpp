#include "namenode.hpp"
#include "../logger.hpp"
#include "../fs.hpp"
#include "set"

time_t time1;

NameNode::NameNode()
{
}

void NameNode::updateNodes() {
    sort(this->nodes.begin(), this->nodes.end());
}

bool NameNode::spaceEnough(long long size) {
    long long all_space = 0;
    for (DataNodeClient item : this->nodes) {
        all_space += item.getSpaceSize();
    }
    FILE_LOG(LOG_DEBUG)<< " space size = " << all_space;
    return all_space > size;
}

vector<FileMeta>::iterator NameNode::findFile(string name)
{
    FILE_LOG(LOG_DEBUG)<< "Find File Need To be Implemented!!!"<< endl;
    return find(this->files.begin(), this->files.end(), name);
}

int NameNode::addDataNode(string ip, int node_id)
{
    DataNodeClient client(grpc::CreateChannel(
                              ip, grpc::InsecureChannelCredentials()),
                          node_id);
    this->nodes.push_back(client);
    this->updateNodes();
    return 0;
}

int NameNode::removeDataNode(int node_id)
{
    vector<DataNodeClient>::iterator it = find(this->nodes.begin(), this->nodes.end(), node_id);
    if (it == this->nodes.end()) {
        FILE_LOG(LOG_ERROR)<< "Remove DataNode error, No DataNode named "<< node_id<< " exits"<< endl;
        return -1;
    }
    this->nodes.erase(it);
    return 0;
}

int NameNode::addNewFile(string name, const char *content, long long size)
{
    // TODO: 目前简单实现了平均分配个不同的DataNodes，实际上应该动态有策略的去存储，具体的存储方式需要研究
    if (this->findFile(name) != this->files.end()) {
        FILE_LOG(LOG_ERROR) << "Add New File Error, "<< name<< " is already exists"<< endl;
        return -1;
    }
    if (!this->spaceEnough(size)) {
        FILE_LOG(LOG_ERROR)<<"FSNDN IS FULL!!!"<< endl;
        return -1;
    }
    int seg_size = fsndn::seg_size;
    if (size < seg_size) {
        // 意味着随便找个空间大的节点存一下就可以了
        if (this->nodes.back().getSpaceSize() < size) {
            // TODO: 考虑将文件分段存储
            FILE_LOG(LOG_ERROR)<<"FSNDN IS FULL!!!"<< endl;
            return -1;
        }
        this->nodes.back().addNewFile(name, content, size, time(&time1), time(&time1), time(&time1));
        FileMeta new_file(name, 1, size);
        int seg_insert = 0;
        int nodeid_insert = this->nodes.back().getNodeId();
        for (; (seg_insert+1)*seg_size <= size; seg_insert++) {
            new_file.addUseNodes(nodeid_insert, seg_insert, seg_size);
        }
        new_file.addUseNodes(nodeid_insert, seg_insert, size - (seg_insert*seg_size));
        this->files.push_back(new_file);
        this->updateNodes();
        return 0;
    }
    char temp_content[seg_size];
    int seg = 0;
    int nodes_count = this->nodes.size();
    FileMeta new_file(name, 0, size);
    while ((seg+1) * seg_size < size) {
        memset(temp_content, 0, seg_size);
        memmove(temp_content, content+(seg*seg_size), seg_size);
        if (seg < nodes_count) {
            this->nodes[seg].addEmptyFile(name, time(&time1), time(&time1), time(&time1));
        }
        this->nodes[seg%nodes_count].addFileSeg(name, temp_content, seg_size, seg);
        new_file.addUseNodes(this->nodes[seg%nodes_count].getNodeId(), seg, seg_size);
        seg++;
    }
    // 把最后一点放进去
    memset(temp_content, 0, seg_size);
    memmove(temp_content, content+(seg*seg_size), size-(seg*seg_size));
    this->nodes[seg%nodes_count].addFileSeg(name, temp_content, size - (seg*seg_size), seg);
    new_file.addUseNodes(this->nodes[seg%nodes_count].getNodeId(), seg, size - (seg *seg_size));
    new_file.setSegs(seg);
    this->files.push_back(new_file);
    this->updateNodes();
    return 0;
}

int NameNode::readFile(string name, char * buffer, long long size)
{
    int seg_size = fsndn::seg_size;
    vector<FileMeta>::iterator it = this->findFile(name);
    if (it == this->files.end()) {
        FILE_LOG(LOG_ERROR)<< "Read File Error, "<< name<< " is not exists!"<< endl;
        return -1;
    }
    if (size < (*it).getSize()) {
        FILE_LOG(LOG_ERROR)<< "Read File Error, size is smaller than file size"<< endl;
        return -1;
    }
    int segs = (*it).getSegs();
    //    for (auto node : this->nodes) {
    //        if ((*it).getUseNodes().find(node.getNodeId()) != (*it).getUseNodes().end()) {
    ////                node.readFromFile(name, buffer, size);
    //                for (auto file_seg : node.store_segs) {
    //                    int temp_seg = file_seg.seg;
    //                    int temp_size = file_seg.size;
    //                    char * temp_content = new char[temp_size];
    //                    node.getFileSeg(name, temp_content, temp_size, temp_seg);
    //                    memcpy(buffer+seg_size * temp_seg, temp_content, temp_size);
    //                    delete [] temp_content;
    //                }
    //            }
    //        }
    //    }
    // TODO: 优化！！！！
    for (auto ss : (*it).getUseNodes()) {
        int nodeid = ss.node;
        vector<DataNodeClient>::iterator node = find(this->nodes.begin(), this->nodes.end(), nodeid);
        for (auto segs : ss.segs) {
            int seg_read = segs.seg;
            int size_read = segs.size;
            char * temp_content = new char[size_read];
            (*node).getFileSeg(name, temp_content, size_read, seg_read);
            memcpy(buffer+seg_size * seg_read, temp_content, size_read);
            delete [] temp_content;
        }
    }
    cout<< (void *)buffer<< endl;
    return 0;
}

long long NameNode::getFileSize(string name)
{
    vector<FileMeta>::iterator it = this->findFile(name);
    if (it == this->files.end()) {
        FILE_LOG(LOG_ERROR)<< "Get File Size Error, "<< name<< " is not exists!"<< endl;
        return -1;
    }
    return (*it).getSize();
}
