#ifndef DATANODE_CLIENT_HPP
#define DATANODE_CLIENT_HPP

#include <grpcpp/grpcpp.h>

#include "../proto-src/fsndn.grpc.pb.h"

using namespace std;
using fsndnproto::AddEmptyFileRequest;
using fsndnproto::AddFileSegRequest;
using fsndnproto::AddNewFileRequest;
using fsndnproto::ChildrenReply;
using fsndnproto::DataNodeSer;
using fsndnproto::EmptyRequest;
using fsndnproto::FileNameRequest;
using fsndnproto::GetFileSegRequest;
using fsndnproto::IntReply;
using fsndnproto::LongReply;
using fsndnproto::PrefixRequest;
using fsndnproto::ReadReply;
using fsndnproto::ReadRequest;
using fsndnproto::WriteRequest;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class DataNodeClient
{
  public:
    DataNodeClient(shared_ptr<Channel> channel, int node_id);

    long long getFileSize(const string& name);
    // 创建空文件
    int addEmptyFile(string name, time_t mtime, time_t atime, time_t ctime);
    // 创建含内容的文件
    int addNewFile(string name,
                   const char* content,
                   long long size,
                   time_t mtime,
                   time_t atime,
                   time_t ctime);
    int delFile(string name);
    int delDir(string prefix);
    int writeToFile(string name, const char* content, long long size);
    int readFromFile(string name, char* buffer, long long size);

    int addFileSeg(string name, const char* content, int size, int seg);
    int getFileSeg(string name, char* buffer, int size, int seg);
    vector<string> showChildren(string prefix);
    vector<string> showAllChildren();
    long long getSpaceSize() const;
    int getNodeId();
    int quit();

    bool operator==(const int& other_node_id) const;
    bool operator<(const DataNodeClient& other_node) const;

  private:
    std::shared_ptr<DataNodeSer::Stub> stub_;
    int node_id;
};

#endif // DATANODE_CLIENT_HPP
