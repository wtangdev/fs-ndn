#ifndef DATANODE_CLIENT_HPP
#define DATANODE_CLIENT_HPP

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
using fsndnproto::AddFileSegRequest;
using fsndnproto::GetFileSegRequest;
using fsndnproto::EmptyRequest;
using fsndnproto::IntReply;
using fsndnproto::ReadReply;
using fsndnproto::ChildrenReply;
using fsndnproto::DataNodeSer;
using fsndnproto::LongReply;

struct StoreSeg{
    int seg;
    int size;
};

class DataNodeClient {
public:
    DataNodeClient(shared_ptr<Channel> channel, int node_id);

    long long getFileSize(const string & name);
    // 创建空文件
    int addEmptyFile(string name, time_t mtime, time_t atime, time_t ctime);
    // 创建含内容的文件
    int addNewFile(string name, const char * content, long long size, time_t mtime, time_t atime, time_t ctime);
    int delFile(string name);
    int delDir(string prefix);
    int writeToFile(string name, const char * content, long long size);
    int readFromFile(string name, char * buffer, long long size);

    int addFileSeg(string name, const char * content, int size, int seg);
    int getFileSeg(string name, char * buffer, int size, int seg);
    vector<string> showChildren(string prefix);
    vector<string> showAllChildren();
    long long getSpaceSize() const;
    int getNodeId();

    bool operator== (const int & other_node_id) const;
    bool operator< (const DataNodeClient & other_node) const;

    vector<StoreSeg> store_segs;
private:
    std::shared_ptr<DataNodeSer::Stub> stub_;
    int node_id;
};


#endif // DATANODE_CLIENT_HPP
