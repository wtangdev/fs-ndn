#ifndef DATANODE_SERVER_HPP
#define DATANODE_SERVER_HPP

#include "datanode.hpp"
#include <grpcpp/grpcpp.h>

#include "../proto-src/fsndn.grpc.pb.h"

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
using fsndnproto::AddFileSegRequest;
using fsndnproto::GetFileSegRequest;
using fsndnproto::EmptyRequest;
using fsndnproto::IntReply;
using fsndnproto::ReadReply;
using fsndnproto::ChildrenReply;
using fsndnproto::DataNodeSer;
using fsndnproto::LongReply;



class DataNodeSerImpl final : public DataNodeSer::Service {
    Status GetFileSize(ServerContext *context, const FileNameRequest *request,
                       LongReply *response);

    Status AddEmptyFile(ServerContext *context, const AddEmptyFileRequest *request,
                        IntReply *response);

    Status AddNewFile(ServerContext *context, const AddNewFileRequest *request,
                      IntReply *response);

    Status DelFile(ServerContext *context, const FileNameRequest *request,
                   IntReply *response);

    Status DelDir(ServerContext *context, const PrefixRequest *request,
                  IntReply *response);

    Status WriteToFile(ServerContext *context, const WriteRequest *request,
                       IntReply *response);

    Status ReadFromFile(ServerContext *context, const ReadRequest *request,
                        ReadReply *response);

    Status AddFileSeg(ServerContext *context, const AddFileSegRequest *request,
                      IntReply *response);

    Status GetFileSeg(ServerContext *context, const GetFileSegRequest *request,
                      ReadReply *response);

    Status GetChildren(ServerContext *context, const PrefixRequest *request,
                       ChildrenReply *response);

    Status GetAllChildren(ServerContext *context, const EmptyRequest *request,
                          ChildrenReply *response);
    Status GetSpaceSize(ServerContext *context, const EmptyRequest *request,
                        LongReply *response);
private:
    DataNode datanode;
public:
    explicit DataNodeSerImpl(long long node_size);
};


#endif // DATANODE_SERVER_HPP
