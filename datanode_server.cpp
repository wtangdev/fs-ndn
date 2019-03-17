//
// Created by anson on 19-2-24.
//

#include "fs.hpp"
#include "DataNode/datanode.hpp"
#include "unistd.h"
#include "stdio.h"
#include "fstream"
#include "ostream"
#include "logger.hpp"

#include <grpcpp/grpcpp.h>

#include "fsndn.grpc.pb.h"

using namespace std;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using fsndnproto::AddEmptyFileRequest;
using fsndnproto::AddNewFileRequest;
using fsndnproto::FileNameRequest;
using fsndnproto::PrefixRequest;
using fsndnproto::ReadRequest;
using fsndnproto::WriteRequest;
using fsndnproto::EmptyRequest;
using fsndnproto::IntReply;
using fsndnproto::ReadReply;
using fsndnproto::ChildrenReply;
using fsndnproto::DataNodeSer;

time_t time1;

int fsndn::user_id ;
int fsndn::group_id;
int fsndn::fsndn_id = 666;
string fsndn::root_path = "/tmp/fsndn";
string fsndn::global_prefix = "/ndn/fsndn/prefix";
const int fsndn::seg_size = 2048;

class DataNodeSerImpl final : public DataNodeSer::Service {
    Status GetFileSize(ServerContext *context, const FileNameRequest *request,
                       IntReply *response) {
        string name = request->name();
        int size = datanode.getFileSize(name);
        response->set_result(size);
        return Status::OK;
    }

    Status AddEmptyFile(ServerContext *context, const AddEmptyFileRequest *request,
                        IntReply *response) {
        string name = request->name();
        time_t mtime = request->mtime();
        time_t atime = request->atime();
        time_t ctime = request->ctime();
        datanode.addEmptyFile(name, mtime, atime, ctime);
        response->set_result(0);
        return Status::OK;
    }

    Status AddNewFile(ServerContext *context, const AddNewFileRequest *request,
                      IntReply *response) {
        string name = request->name();
        string content_string = request->content();
        int size = request->size();
        if (size != content_string.length()) {
            response->set_result(-1);
            FILE_LOG(LOG_ERROR)<< "Add new file failed, 接收文件大小与要求大小不匹配"<< endl;
            return Status::CANCELLED;
        }
        // TODO: 内存泄漏风险！
        const unsigned char * content = reinterpret_cast<const unsigned char *> (content_string.c_str());
        time_t mtime = request->mtime();
        time_t atime = request->atime();
        time_t ctime = request->ctime();
        datanode.addNewFile(name, content, size, mtime, atime, ctime);
        response->set_result(0);
        return Status::OK;
    }

    Status DelFile(ServerContext *context, const FileNameRequest *request,
                   IntReply *response) {
        string name = request->name();
        int result = datanode.delFile(name);
        response->set_result(result);
        if (result != 0) {
            return Status::CANCELLED;
        }
        return Status::OK;
    }

    Status DelDir(ServerContext *context, const PrefixRequest *request,
                  IntReply *response) {
        string prefix = request->prefix();
        int result = datanode.delDir(prefix);
        response->set_result(result);
        if (result != 0) {
            return Status::CANCELLED;
        }
        return Status::OK;
    }

    Status WriteToFile(ServerContext *context, const WriteRequest *request,
                       IntReply *response) {
        string name = request->name();
        string content_string = request->content();
        int size = request->size();
        if (size != content_string.length()) {
            response->set_result(-1);
            FILE_LOG(LOG_ERROR)<< "Write to"<< name<<" failed, 接收文件大小与要求大小不匹配"<< endl;
            return Status::CANCELLED;
        }
        // TODO: 内存泄漏风险！
        const unsigned char * content = reinterpret_cast<const unsigned char *> (content_string.c_str());
        int result = datanode.writeToFile(name, content, size);
        if (result != 0) {
            return Status::CANCELLED;
        }
        return Status::OK;
    }

    Status ReadFromFile(ServerContext *context, const ReadRequest *request,
                        ReadReply *response) {
        string name = request->name();
        int size = request->size();
        unsigned char buffer[size];
        int result = datanode.readFromFile(name, buffer, size);
        if (result != 0) {
            unsigned char result[13] = "No Such File";
            response->set_buffer(result, 13);
            return Status::CANCELLED;
        }
        response->set_buffer(buffer, size);
        return Status::OK;
    }

    Status GetChildren(ServerContext *context, const PrefixRequest *request,
                       ChildrenReply *response) {
        string prefix = request->prefix();
        vector<string> children = datanode.showChildren(prefix);
        for (int i = 0; i < children.size(); i++) {
            response->add_children(children[i]);
        }
        return Status::OK;
    }

    Status GetAllChildren(ServerContext *context, const EmptyRequest *request,
                          ChildrenReply *response) {
        vector<string> children = datanode.showAllChildren();
        for (int i = 0; i < children.size(); i++) {
            response->add_children(children[i]);
            cout<< response->children(i)<< endl;
        }
        return Status::OK;
    }

public:
    DataNode datanode;
};

void test(DataNode & datanode) {
    ifstream fin("/Users/anson/Desktop/psb.jpeg", ios::binary | ios::in);
    //    ifstream fin("/Users/anson/Desktop/jpjh.md", ios::binary | ios::in);
    if (!fin) {
        cout<< "File open failed\n";
    } else {
        //        istream::pos_type current_pos = fin.tellg();    // 记录当前位置
        int current_pos = fin.tellg();
        fin.seekg(0, ios_base::end);    // 移动到末尾
        //        istream::pos_type file_size = fin.tellg();  // 此时的位置显然就是文件大小
        int file_size = fin.tellg();
        fin.seekg(current_pos); //回到初始位置
        FILE_LOG(LOG_DEBUG)<< "file_size="<<file_size<< endl;
        unsigned char data[file_size];
        //        memset(data, 0, file_size);
        fin.read(reinterpret_cast<char *>(data), sizeof(unsigned char) * file_size);    // 读
        fin.close();
        datanode.addNewFile("/c1/c2", data, file_size, time(&time1), time(&time1), time(&time1));
        unsigned char read_data[file_size];
        datanode.readFromFile("/c1/c2", read_data, file_size);
        ofstream fout("/Users/anson/Desktop/newpsb.jpeg", ios::binary);
        //        ofstream fout("/Users/anson/Desktop/newjpjh.md", ios::binary);
        fout.write(reinterpret_cast<char *>(read_data), sizeof(unsigned char) * file_size);
        fout.close();
    }
}

int main() {
    cout<< "FS-NDN: version 0.1"<< endl;
    fsndn::user_id = getuid();
    fsndn::group_id = getgid();
    cout<< "FS-NDN: prefix " << fsndn::global_prefix<< endl;
    cout<< "FS-NDN: root path "<< fsndn::root_path<< endl;
    Log<Output2FILE>::reportingLevel() = LOG_DEBUG;
    Output2FILE::stream() = stdout;
    DataNode datanode;
    test(datanode);

    DataNodeSerImpl service;
    service.datanode = datanode;
    string server_address("127.0.0.1:50051");
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();

    return 0;
}
