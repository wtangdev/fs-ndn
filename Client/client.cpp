#include "client.h"
#include "../NameNode/namenode.hpp"
#include "../fs.hpp"
#include "../logger.hpp"
#include "thread"

// 不建议使用
void
writeThread(vector<DataNodeClient>::iterator it,
            string name,
            const char *content,
            int size,
            int seg)
{
    int seg_size = fsndn::seg_size;
    char *temp_content = new char[size];
    memcpy(temp_content, content + (seg * seg_size), size);
    (*it).addFileSeg(name, temp_content, size, seg);
    delete[] temp_content;
}

// 不建议使用
void
readThread(vector<DataNodeClient>::iterator it,
           string name,
           char *buffer,
           int get_size,
           int get_seg)
{
    int seg_size = fsndn::seg_size;
    char *temp_content = new char[get_size];
    (*it).getFileSeg(name, temp_content, get_size, get_seg);
    memcpy(buffer + (get_seg * seg_size), temp_content, get_size);
    delete[] temp_content;
}

void
writeFileThread(vector<DataNodeClient>::iterator it,
                string name,
                string file_path,
                int size,
                int seg)
{
    int seg_size = fsndn::seg_size;
    // TODO: 此处 size 会有几率出现负数！！！
    FILE_LOG(LOG_DEBUG) << size << " !!!!!!!!!!!!!!!!!!!!!! \n";
    char *temp_content = new char[size];
    ifstream fin(file_path, ios::binary | ios::in);
    fin.seekg(seg * seg_size);
    fin.read(temp_content, size);
    fin.close();
    // TODO: 如果传输过程发生错误，此处如何进行处理？出错重传等
    // 步骤5:写入应答
    (*it).addFileSeg(name, temp_content, size, seg);
    delete[] temp_content;
}

void
readFileThread(vector<DataNodeClient>::iterator it,
               string name,
               char *buffer,
               int get_size,
               int get_seg,
               int node_seg_count)
{
    int seg_size = fsndn::seg_size;
    char *temp_content = new char[get_size];
    // TODO: 如果传输过程发生错误，此处如何进行处理？出错重传等
    (*it).getFileSeg(name, temp_content, get_size, get_seg);
    memcpy(buffer + (node_seg_count * seg_size), temp_content, get_size);
    delete[] temp_content;
}

mutex mutex_write;

void
highWriteFileThread(const vector<DataNodeClient>::iterator it,
                    const string name,
                    ifstream * fin,
                    const vector<SegWithSize> ss)
{
    int seg_size = fsndn::seg_size;
    char *temp_content = new char[seg_size];
    // TODO: 如果传输过程发生错误，此处如何进行处理？出错重传等
    // 步骤5:写入应答
    for (auto item : ss) {
        mutex_write.try_lock();
        fin->seekg(item.seg * seg_size);
        fin->read(temp_content, item.size);
        mutex_write.unlock();
        (*it).addFileSeg(name, temp_content, item.size, item.seg);
    }
    delete[] temp_content;
}

mutex mutex_read;

void
highReadFileThread(const vector<DataNodeClient>::iterator it,
                   const string name,
                   ofstream * fout,
                   const vector<SegWithSize> ss)
{
    int seg_size = fsndn::seg_size;
    char *temp_content = new char[seg_size];
    for (auto item : ss) {
        (*it).getFileSeg(name, temp_content, item.size, item.seg);
        // 准备写
        mutex_read.try_lock();
        fout->seekp(seg_size * item.seg);
        fout->write(temp_content, item.size);
        // 释放
        mutex_read.unlock();
    }
    delete[] temp_content;
}
/*
void
highWriteFileSignThread(const vector<DataNodeClient>::iterator it,
                        const string name,
                        const string file_path,
                        const vector<SegWithSize> ss)
{
    FILE_LOG(LOG_DEBUG)<< "I am waiting for something then write!!!!"<< endl;
    int seg_size = fsndn::seg_size;
    ifstream fin(file_path, ios::binary | ios::in);
    char *content_sign = new char[seg_size];
    // TODO: 如果传输过程发生错误，此处如何进行处理？出错重传等
    // 步骤5:写入应答
    for (auto item : ss) {
        FILE_LOG(LOG_DEBUG)<< item.seg<< endl;
        fin.seekg(item.seg * (seg_size - 256));
        fin.read(content_sign + 256, item.size - 256);
        ndn::Data data;
        data.setName(name);
        data.setContent((const uint8_t *) content_sign + 256, item.size - 256);
        fsndn::keyChain->sign(data, fsndn::certificateName);
        memcpy(content_sign,
               data.getSignature()->getSignature().toRawStr().c_str(),
               256);
        (*it).addFileSeg(name, content_sign, item.size, item.seg);
    }
    fin.close();
    delete[] content_sign;
}
*/

mutex mutex_write_sign;
void
highWriteFileSignThread(const vector<DataNodeClient>::iterator it,
                        const string name,
                        ifstream * fin,
                        const vector<SegWithSize> ss)
{
    FILE_LOG(LOG_DEBUG)<< "I am waiting for something then write!!!!"<< endl;
    int seg_size = fsndn::seg_size;
    char *content_sign = new char[seg_size];
    // TODO: 如果传输过程发生错误，此处如何进行处理？出错重传等
    // 步骤5:写入应答
    for (auto item : ss) {
        FILE_LOG(LOG_DEBUG)<< item.seg<< endl;
        mutex_write_sign.try_lock();
        fin->seekg(item.seg * (seg_size - 256));
        fin->read(content_sign + 256, item.size - 256);
        mutex_write_sign.unlock();
        ndn::Data data;
        data.setName(name);
        data.setContent((const uint8_t *) content_sign + 256, item.size - 256);
        fsndn::keyChain->sign(data, fsndn::certificateName);
        memcpy(content_sign,
               data.getSignature()->getSignature().toRawStr().c_str(),
               256);
        (*it).addFileSeg(name, content_sign, item.size, item.seg);
    }
    delete[] content_sign;
}

// 用来解决写冲突的互斥量
mutex mutex_read_sign;

void
highReadFileSignThread(const vector<DataNodeClient>::iterator it,
                       const string name,
                       ofstream * fout,
                       const vector<SegWithSize> ss)
{
    FILE_LOG(LOG_DEBUG)<< "I am waiting for something then read!!!!"<< endl;
    int seg_size = fsndn::seg_size;
    char *content_sign = new char[seg_size];
    for (auto item : ss) {
        FILE_LOG(LOG_DEBUG)<< item.seg<< endl;
        (*it).getFileSeg(name, content_sign, item.size, item.seg);
        // 准备写了，加锁
        mutex_read_sign.try_lock();
        fout->seekp((seg_size - 256) * item.seg);
        fout->write(content_sign + 256, item.size - 256);
        // 写完了，释放
        mutex_read_sign.unlock();
        FILE_LOG(LOG_DEBUG) << Client::checkSignautre(
                  name, content_sign + 256, item.size - 256, content_sign)
             << endl;
    }
    delete[] content_sign;
}

/*
void
highReadFileSignThread(vector<DataNodeClient>::iterator it,
                       string name,
                       string file_path,
                       vector<SegWithSize> ss)
{
    FILE_LOG(LOG_DEBUG)<< "I am waiting for something then read!!!!"<< endl;
    int seg_size = fsndn::seg_size;
    char *content_sign = new char[seg_size];
    ofstream fout(file_path, ios::binary | ios::in);
    for (auto item : ss) {
        FILE_LOG(LOG_DEBUG)<< item.seg<< endl;
        (*it).getFileSeg(name, content_sign, item.size, item.seg);
        fout.seekp((seg_size - 256) * item.seg);
        fout.write(content_sign + 256, item.size - 256);
        cout << Client::checkSignautre(
                  name, content_sign + 256, item.size - 256, content_sign)
             << endl;
    }
    fout.close();
    delete[] content_sign;
}
*/

bool
Client::checkSignautre(string name,
                       const char *context,
                       int size,
                       const char *signature)
{
    ndn::Data data;
    data.setName(name);
    data.setContent((const uint8_t *) context, size);
    fsndn::keyChain->sign(data, fsndn::certificateName);
    char *orign_sign = new char[256];
    memcpy(
      orign_sign, data.getSignature()->getSignature().toRawStr().c_str(), 256);
    return (memcmp(orign_sign, signature, 256) == 0);
}

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

// 不建议使用,因为很难能把一个大文件完整的存放到内存里面去
int
Client::addNewFile(string name,
                   const char *content,
                   long long size,
                   time_t mtime,
                   time_t atime,
                   time_t ctime)
{
    // 访问名称节点，生成named data元数据信息并获得写入索引
    vector<SegIndex> store_segs;
    this->name_nodes[0].addNewFile(name, size, mtime, atime, ctime, store_segs);
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
            thread t(
              writeThread, ref(it), name, content, insert_size, insert_seg);
            t.join();
            //            writeThread(it, name, content, insert_size,
            //            insert_seg);
        }
    }

    return 0;
}

// 不建议使用,因为很难能把一个大文件完整的存放到内存里面去
int
Client::readFile(string name, char *buffer, long long size)
{
    // TODO:检索本地缓存
    // 向NameNode发送读请求，获得文件所在位置和分块信息
    vector<SegIndex> store_segs;
    this->name_nodes[0].readFile(name, store_segs);
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
Client::updateNodes()
{
    sort(this->data_nodes.begin(), this->data_nodes.end());
}

/*
 *
分配方式为从一个节点开始分配足够的段，再往下一个分配，这样的方式不利于通过并行来提高读写速度
int
Client::addNewFile(string name,
                   string file_path,
                   time_t mtime,
                   time_t atime,
                   time_t ctime) {
    ifstream fin(file_path, ios::binary | ios::in);
    // 检测文件打开成功与否，打开失败返回-1
    if (!fin) {
        FILE_LOG(LOG_ERROR) << "File open failed!" << endl;
        return -1;
    }
    // 计算文件大小
    // 记录当前位置
    long long current_pos = fin.tellg();
    fin.seekg(0, ios_base::end); // 移动到末尾
    //        istream::pos_type file_size = fin.tellg();  //
    // 此时的位置显然就是文件大小
    long long file_size = fin.tellg();
    fin.seekg(current_pos); // 回到初始位置
    fin.close();

    // 步骤2：访问名称节点，生成named data元数据信息并获得写入索引
    vector<SegIndex> store_segs;
    this->name_nodes[0].addNewFile(name, file_size, mtime, atime, ctime,
store_segs);

    // 步骤3：文件分段信息已由NameNode生成，写入DataNode
    int seg_size = fsndn::seg_size;
    // TODO: 并行写入
    for (SegIndex si : store_segs) {
        int node_id = si.node;
        vector<DataNodeClient>::iterator it =
                find(this->data_nodes.begin(), this->data_nodes.end(), node_id);
        for (SegWithSize ss : si.segs) {
            int insert_seg = ss.seg;
            int insert_size = ss.size;
            if (insert_size < 0) {
                return -1;
            }
            // 步骤4：分块写入
            thread t(writeFileThread,
                     ref(it),
                     name,
                     file_path,
                     insert_size,
                     insert_seg);
            t.join();
            //            writeThread(it, name, content, insert_size,
            //            insert_seg);
        }
    }

    // TODO: 步骤6关闭？
    // TODO:
    //
告诉NameNode写入完成！NameNode应该根据写入完成与否来更新DataNode节点的的信息！
    int status = 0;
    // 对 Status 进行处理，从而告诉NameNode是成功了还是失败了
    this->name_nodes[0].updateNode(status);

    return 0;
}

 int
Client::readFile(string name, string file_path) {
    // TODO: 检索本地缓存，如果存在本地缓存，则直接返回本地的缓存给用户

    // ******************************************************************

    // 步骤2：本地缓存不存在该文件的情况下，询问NameNode以进行并行读取，
    //
计划每次读完一个datanode中所有的段，如果大于500个，就每500个为一次的读，也就是500m,然后开始写入
    int seg_size = fsndn::seg_size;
    long long buffer_size = seg_size * 500;

    // 判断该文件在系统中是否存在
    long long file_size = this->name_nodes[0].getFileSize(name);
    if (file_size == -1) {
        FILE_LOG(LOG_ERROR) << "File named " << name << " is not exist" << endl;
        return -1;
    }

    // 步骤3：向NameNode发送读请求，获得文件所在位置和分块信息
    vector<SegIndex> store_segs;
    this->name_nodes[0].readFile(name, store_segs);
    for (auto item: store_segs) {
        for (auto ss : item.segs) {
            cout << " client :" << item.node << " Seg=" << ss.seg << " Size=" <<
ss.size << endl;
        }
    }

    // 步骤4:并行读取
    ofstream fout(file_path, ios::binary);
    char *buffer = new char[buffer_size];
    for (SegIndex si : store_segs) {
        int node_id = si.node;
        vector<DataNodeClient>::iterator it =
                find(this->data_nodes.begin(), this->data_nodes.end(), node_id);
        int node_seg_count = 0;
        long long curr_size = 0; // 当前读了多少字节
        int curr_seg = 0;        // 当前应当从哪一个段开始写
        memset(buffer, 0, buffer_size);
        for (SegWithSize ss : si.segs) {
            int get_seg = ss.seg;
            int get_size = ss.size;
            curr_size += get_size;
            // 记录当前节点的第一个段
            if (node_seg_count == 0) {
                curr_seg = get_seg;
            }
            // 步骤5：数每一个据段的读取
            thread t(readFileThread,
                     ref(it),
                     name,
                     buffer,
                     get_size,
                     get_seg,
                     node_seg_count);
            t.join();
            node_seg_count++;
            // 已经读到buffer满了
            if (curr_size + seg_size >= buffer_size) {
                fout.seekp(seg_size * curr_seg);
                FILE_LOG(LOG_DEBUG) << "seg: " << seg_size * curr_seg << endl;
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
    delete[] buffer;

    // 步骤6： 关闭
    return 0;
}

*/

// 改进的分配方式，将段以适合并行读写的方式均匀的分配到不同的节点上,此处实现的是并行读写
// TODO: 负载均衡！
int
Client::addNewFile(
  string name, string file_path, time_t mtime, time_t atime, time_t ctime)
{
    ifstream fin(file_path, ios::binary | ios::in);
    // 检测文件打开成功与否，打开失败返回-1
    if (!fin) {
        FILE_LOG(LOG_ERROR) << "File open failed!" << endl;
        return -1;
    }
    // 计算文件大小
    // 记录当前位置
    long long current_pos = fin.tellg();
    fin.seekg(0, ios_base::end); // 移动到末尾
    //        istream::pos_type file_size = fin.tellg();  //
    // 此时的位置显然就是文件大小
    long long file_size = fin.tellg();
    fin.seekg(current_pos); // 回到初始位置
    fin.close();

    // 步骤2：访问名称节点，生成named data元数据信息并获得写入索引
    vector<SegIndex> store_segs;
    int write_namenode_ok = this->name_nodes[0].addNewFile(
      name, file_size, mtime, atime, ctime, store_segs);
    
    if (write_namenode_ok == -1) {
        FILE_LOG(LOG_DEBUG) << name<< " is already exists"<< endl;
        return -2;
    }

    // 步骤3：文件分段信息已由NameNode生成，写入DataNode
    int seg_size = fsndn::seg_size;
    // TODO: 并行写入
    vector<thread *> threads;
    ifstream * fin_point = new ifstream(file_path, ios::binary | ios::in);
    for (SegIndex si : store_segs) {
        int node_id = si.node;
        vector<DataNodeClient>::iterator it =
          find(this->data_nodes.begin(), this->data_nodes.end(), node_id);
        thread *t = new thread(highWriteFileThread, it, name, fin_point, si.segs);
        threads.push_back(t);
    }
    for (int i = 0; i < threads.size(); i++) {
        threads[i]->join();
    }
    for (int i = 0; i < threads.size(); i++) {
        delete threads[i];
    }
    fin_point->close();
    delete fin_point;
    /*
        for (SegIndex si : store_segs) {
            int node_id = si.node;
            vector<DataNodeClient>::iterator it =
                    find(this->data_nodes.begin(), this->data_nodes.end(),
       node_id); for (SegWithSize ss : si.segs) { int insert_seg = ss.seg; int
       insert_size = ss.size; if (insert_size < 0) { return -1;
                }
                // 步骤4：分块写入
                thread t(writeFileThread,
                         ref(it),
                         name,
                         file_path,
                         insert_size,
                         insert_seg);
                t.join();
                //            writeThread(it, name, content, insert_size,
                //            insert_seg);
            }
        }
    */
    // TODO: 步骤6关闭？
    // TODO:
    // 告诉NameNode写入完成！NameNode应该根据写入完成与否来更新DataNode节点的的信息！
    int status = 0;
    // 对 Status 进行处理，从而告诉NameNode是成功了还是失败了
    this->name_nodes[0].updateNode(status);

    return 0;
}

// 改进的分配方式，向不同的节点
// 0 读取成功, -1 name 不存在
int
Client::readFile(string name, string file_path)
{
    // TODO: 检索本地缓存，如果存在本地缓存，则直接返回本地的缓存给用户

    //******************************************************************

    // 步骤2：本地缓存不存在该文件的情况下，询问NameNode以进行并行读取，
    // 计划每次读完一个datanode中所有的段，如果大于500个，就每500个为一次的读，也就是500m,然后开始写入
    int seg_size = fsndn::seg_size;
    long long buffer_size = seg_size * 500;

    // 判断该文件在系统中是否存在
    long long file_size = this->name_nodes[0].getFileSize(name);
    if (file_size == -1) {
        FILE_LOG(LOG_ERROR) << "File named " << name << " is not exist" << endl;
        return -1;
    }

    // 防止文件不存在目录中导致的文件出错，所以此处以覆盖的方式打开一下该文件，实际上就是新建了
    ofstream creat_file(file_path);
    creat_file.close();

    // 步骤3：向NameNode发送读请求，获得文件所在位置和分块信息
    vector<SegIndex> store_segs;
    this->name_nodes[0].readFile(name, store_segs);
    for (auto item : store_segs) {
        for (auto ss : item.segs) {
            FILE_LOG(LOG_DEBUG) << " client :" << item.node << " Seg=" << ss.seg
                                << " Size=" << ss.size << endl;
        }
    }

    // 步骤4:并行读取
    vector<thread *> threads;
    ofstream * fout_point = new ofstream(file_path, ios::binary | ios::in);
    for (SegIndex si : store_segs) {
        int node_id = si.node;
        vector<DataNodeClient>::iterator it =
          find(this->data_nodes.begin(), this->data_nodes.end(), node_id);
        thread * t = new thread(highReadFileThread, it, name, fout_point, si.segs);
        threads.push_back(t);
    }
    for (int i = 0; i < threads.size(); i++) {
        threads[i]->join();
    }
    for (int i = 0; i < threads.size(); i++) {
        delete threads[i];
    }
    fout_point->close();
    delete fout_point;
 
    /*
    char *buffer = new char[buffer_size];
    for (SegIndex si : store_segs) {
        int node_id = si.node;
        vector<DataNodeClient>::iterator it =
                find(this->data_nodes.begin(), this->data_nodes.end(), node_id);
        int node_seg_count = 0;
        long long curr_size = 0; // 当前读了多少字节
        int curr_seg = 0;        // 当前应当从哪一个段开始写
        memset(buffer, 0, buffer_size);
        for (SegWithSize ss : si.segs) {
            int get_seg = ss.seg;
            int get_size = ss.size;
            curr_size += get_size;
            // 记录当前节点的第一个段
            if (node_seg_count == 0) {
                curr_seg = get_seg;
            }
            // 步骤5：数每一个据段的读取
            thread t(readFileThread,
                     ref(it),
                     name,
                     buffer,
                     get_size,
                     get_seg,
                     node_seg_count);
            t.join();
            node_seg_count++;
            // 已经读到buffer满了
            if (curr_size + seg_size >= buffer_size) {
                fout.seekp(seg_size * curr_seg);
                FILE_LOG(LOG_DEBUG) << "seg: " << seg_size * curr_seg << endl;
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
    delete[] buffer;
    */

    // 步骤6： 关闭
    return 0;
}

// 写入的时候加入签名
// TODO: 负载均衡！
// 0 写入成功 -1 文件打开失败, -2 name 已存在
int
Client::addNewFileSign(
  string name, string file_path, time_t mtime, time_t atime, time_t ctime)
{
    int seg_size = fsndn::seg_size;
    ifstream fin(file_path, ios::binary | ios::in);
    // 检测文件打开成功与否，打开失败返回-1
    if (!fin) {
        FILE_LOG(LOG_ERROR) << "File open failed!" << endl;
        return -1;
    }
    // 计算文件大小
    // 记录当前位置
    long long current_pos = fin.tellg();
    fin.seekg(0, ios_base::end); // 移动到末尾
    //        istream::pos_type file_size = fin.tellg();  //
    // 此时的位置显然就是文件大小
    long long file_size = fin.tellg();
    fin.seekg(current_pos); // 回到初始位置
    fin.close();

    // 步骤2：访问名称节点，生成named data元数据信息并获得写入索引
    // 针对需要签名的情况，我们把签名信息存在每个段的头256个字节，所以每个段要多加入256字节
    int need_seg = file_size / seg_size;
    if (need_seg * seg_size < file_size) {
        need_seg++;
    }
    // 每一段多256字节
    file_size += need_seg * 256;
    vector<SegIndex> store_segs;
    int write_namenode_ok = this->name_nodes[0].addNewFile(
      name, file_size, mtime, atime, ctime, store_segs);
    if (write_namenode_ok == -1) {
        FILE_LOG(LOG_DEBUG)<< name << " is already exists in NameNode"<< endl;
        return -2;
    }

    // 步骤3：文件分段信息已由NameNode生成，写入DataNode
    // TODO: 并行写入
    ifstream * fin_point = new ifstream(file_path, ios::binary | ios::in);
    vector<thread *> threads;
    for (SegIndex si : store_segs) {
        int node_id = si.node;
        vector<DataNodeClient>::iterator it =
          find(this->data_nodes.begin(), this->data_nodes.end(), node_id);
        // thread * t = new thread(highWriteFileSignThread, it, name, file_path, si.segs);
        thread * t = new thread(highWriteFileSignThread, it, name, fin_point, si.segs);
        threads.push_back(t);
    }
    for (int i = 0; i < threads.size(); i++) {
        threads[i]->join();
    }
    for (int i = 0; i < threads.size(); i++) {
        delete threads[i];
    }
    fin_point->close();
    delete fin_point;
    // TODO: 步骤6关闭？
    // TODO:
    //
    // 告诉NameNode写入完成！NameNode应该根据写入完成与否来更新DataNode节点的的信息！
    // int status = 0;
    // 对 Status 进行处理，从而告诉NameNode是成功了还是失败了
    // this->name_nodes[0].updateNode(status);
    return 0;
}

// 针对需要为
int
Client::readFileSign(string name, string file_path)
{
    // TODO: 检索本地缓存，如果存在本地缓存，则直接返回本地的缓存给用户

    //******************************************************************

    // 步骤2：本地缓存不存在该文件的情况下，询问NameNode以进行并行读取，
    // 计划每次读完一个datanode中所有的段，如果大于500个，就每500个为一次的读，也就是500m,然后开始写入
    int seg_size = fsndn::seg_size;
    long long buffer_size = seg_size * 500;

    // 判断该文件在系统中是否存在
    long long file_size = this->name_nodes[0].getFileSize(name);
    if (file_size == -1) {
        FILE_LOG(LOG_ERROR) << "File named " << name << " is not exist" << endl;
        return -1;
    }

    // 防止文件不存在目录中导致的文件出错，所以此处以覆盖的方式打开一下该文件，实际上就是新建了
    ofstream creat_file(file_path);
    creat_file.close();

    // 步骤3：向NameNode发送读请求，获得文件所在位置和分块信息
    vector<SegIndex> store_segs;
    this->name_nodes[0].readFile(name, store_segs);
    for (auto item : store_segs) {
        for (auto ss : item.segs) {
            FILE_LOG(LOG_DEBUG) << " client :" << item.node << " Seg=" << ss.seg
                                << " Size=" << ss.size << endl;
        }
    }

    // 步骤4:并行读取
    vector<thread *> threads;
    ofstream * fout_point = new ofstream(file_path, ios::binary | ios::in);
    for (SegIndex si : store_segs) {
        int node_id = si.node;
        vector<DataNodeClient>::iterator it =
          find(this->data_nodes.begin(), this->data_nodes.end(), node_id);
        thread * t = new thread(highReadFileSignThread, it, name, fout_point, si.segs);
        threads.push_back(t);
    }
    for (int i = 0; i < threads.size(); i++) {
        threads[i]->join();
    }
    for (int i = 0; i < threads.size(); i++) {
        delete threads[i];
    }
    fout_point->close();
    delete fout_point;
    // 步骤6： 关闭
    return 0;
}

void
Client::quitDatanode()
{
    for (auto item : this->data_nodes) {
        item.quit();
    }
    return;
}

void
Client::quitNamenode()
{

    for (auto item : this->name_nodes) {
        item.quit();
    }
}
