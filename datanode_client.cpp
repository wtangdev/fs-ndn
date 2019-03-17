#include <iostream>
#include <memory>
#include <string>
#include "fs.hpp"
#include "logger.hpp"
#include <grpcpp/grpcpp.h>

#include "fsndn.grpc.pb.h"

using namespace std;
using grpc::Channel;
using grpc::ClientContext;
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

int fsndn::user_id ;
int fsndn::group_id;
int fsndn::fsndn_id = 666;
string fsndn::root_path = "/tmp/fsndn";
string fsndn::global_prefix = "/ndn/fsndn/prefix";
const int fsndn::seg_size = 2048;

class NameNodeClinet {
public:
    NameNodeClinet(shared_ptr<Channel> channel) : stub_(DataNodeSer::NewStub(channel)){}
    int getFileSize(const string & name) {
        FileNameRequest request;
        request.set_name(name);
        IntReply reply;
        ClientContext context;
        Status status = stub_->GetFileSize(&context, request, & reply);

        if (!status.ok()) {
            FILE_LOG(LOG_ERROR) << status.error_code()<< " : "<< status.error_message()<< endl;
            return -1;
        }
        return reply.result();
    }
    // 创建空文件
    int addEmptyFile(string name, time_t mtime, time_t atime, time_t ctime) {
        AddEmptyFileRequest request;
        request.set_name(name);;
        request.set_mtime(mtime);
        request.set_atime(atime);
        request.set_ctime(ctime);
        IntReply reply;
        ClientContext context;
        Status status = stub_->AddEmptyFile(&context, request, & reply);

        if (!status.ok()) {
            FILE_LOG(LOG_ERROR) << status.error_code()<< " : "<< status.error_message()<< endl;
            return -1;
        }
        return reply.result();
    }

    // 创建含内容的文件
    int addNewFile(string name, const unsigned char * content, int size, time_t mtime, time_t atime, time_t ctime) {
        AddNewFileRequest request;
        request.set_name(name);;
        request.set_content(content, size);
        request.set_size(size);
        request.set_mtime(mtime);
        request.set_atime(atime);
        request.set_ctime(ctime);
        IntReply reply;
        ClientContext context;
        Status status = stub_->AddNewFile(&context, request, & reply);

        if (!status.ok()) {
            FILE_LOG(LOG_ERROR) << status.error_code()<< " : "<< status.error_message()<< endl;
            return -1;
        }
        return reply.result();
    }

    int delFile(string name) {
        FileNameRequest request;
        request.set_name(name);
        IntReply reply;
        ClientContext context;
        Status status = stub_->DelFile(&context, request, & reply);

        if (!status.ok()) {
            FILE_LOG(LOG_ERROR) << status.error_code()<< " : "<< status.error_message()<< endl;
            return -1;
        }
        return reply.result();

    }
    int delDir(string prefix) {
        PrefixRequest request;
        request.set_prefix(prefix);
        IntReply reply;
        ClientContext context;
        Status status = stub_->DelDir(&context, request, & reply);

        if (!status.ok()) {
            FILE_LOG(LOG_ERROR) << status.error_code()<< " : "<< status.error_message()<< endl;
            return -1;
        }
        return reply.result();

    }

    int writeToFile(string name, const unsigned char * content, int size) {
        WriteRequest request;
        request.set_name(name);
        request.set_content(content, size);
        request.set_size(size);
        IntReply reply;
        ClientContext context;
        Status status = stub_->WriteToFile(&context, request, & reply);

        if (!status.ok()) {
            FILE_LOG(LOG_ERROR) << status.error_code()<< " : "<< status.error_message()<< endl;
            return -1;
        }
        return reply.result();

    }

    int readFromFile(string name, unsigned char * buffer, int size) {
        ReadRequest request;
        request.set_name(name);
        request.set_size(size);
        ReadReply reply;
        ClientContext context;
        Status status = stub_->ReadFromFile(&context, request, & reply);

        if (!status.ok()) {
            FILE_LOG(LOG_ERROR) << status.error_code()<< " : "<< status.error_message()<< endl;
            return -1;
        }
        string buffer_string = reply.buffer();
        // TODO: 内存泄漏风险！
        memset(buffer, 0, size);
        memmove(buffer, (unsigned char *)buffer_string.c_str(), size);
        return 0;
    }

    vector<string> showChildren(string prefix) {
        PrefixRequest request;
        request.set_prefix(prefix);
        ChildrenReply reply;
        ClientContext context;
        Status status = stub_->GetChildren(&context, request, & reply);
        vector<string> result;
        if (!status.ok()) {
            FILE_LOG(LOG_ERROR) << status.error_code()<< " : "<< status.error_message()<< endl;
            return result;
        }
        for (int i = 0; i < reply.children_size(); i++) {
            result.push_back(reply.children(i));
        }
        return result;
    }

    vector<string> showAllChildren() {
        EmptyRequest request;
        ChildrenReply reply;
        ClientContext context;
        Status status = stub_->GetAllChildren(&context, request, & reply);
        vector<string> result;
        if (!status.ok()) {
            FILE_LOG(LOG_ERROR) << status.error_code()<< " : "<< status.error_message()<< endl;
            return result;
        }
        for (int i = 0; i < reply.children_size(); i++) {
            result.push_back(reply.children(i));
        }
        return result;
    }


private:
    std::unique_ptr<DataNodeSer::Stub> stub_;
};

int main(int argc, char ** argv) {
    time_t time1;
    NameNodeClinet client(grpc::CreateChannel(
                              "localhost:50051", grpc::InsecureChannelCredentials()));
    string filename = "/c1/c2.jpeg";
    cout<< "getfilesize : "<< filename<< endl;
    int reply = client.getFileSize(filename);
    cout<< "Client recieved: " << reply<< endl;

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
        cout<< "addNewFile /c1/new.jpeg"<< endl;
//        cout<< "addNewFile /c1/newmd.md"<< endl;
        int reply = client.addNewFile("/c1/new.jpeg", data, file_size, time(&time1), time(&time1), time(&time1));
//        int reply = client.addNewFile("/c1/newmd.md", data, file_size, time(&time1), time(&time1), time(&time1));
        cout<< "Client recieved: " << reply<< endl;
    }
    vector<string> children = client.showAllChildren();
    for (auto str : children) {
        cout<< str<< endl;
    }
    int md_size = client.getFileSize("/c1/new.jpeg");
    unsigned char md_content[md_size];
    client.readFromFile("/c1/new.jpeg", md_content, md_size);
    ofstream fout("/Users/anson/Desktop/new111.jpeg", ios::binary);
    fout.write(reinterpret_cast<char *>(md_content), md_size*sizeof(unsigned char));

    return 0;
}
