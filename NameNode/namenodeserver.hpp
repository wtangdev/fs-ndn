#ifndef NAMENODESERVER_H
#define NAMENODESERVER_H

#include "namenode.hpp"
#include <grpcpp/grpcpp.h>

#include "../proto-src/namenode.grpc.pb.h"

using namespace std;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namenodeproto::NameNodeSer;

class NameNodeSerImpl final : public NameNodeSer::Service {

    Status AddDataNode(grpc::ServerContext *context,
                       const namenodeproto::AddDataNodeRequst *request,
                       namenodeproto::IntReply *response);

    Status RemDataNode(grpc::ServerContext *context,
                       const namenodeproto::RemDataNodeRequst *request,
                       namenodeproto::IntReply *response);

    Status AddNewFile(ServerContext *context,
                      const namenodeproto::AddNewFileRequest *request,
                      namenodeproto::SegIndexReply *response);

    Status ReadFromFile(ServerContext *context,
                        const namenodeproto::ReadRequest *request,
                        namenodeproto::SegIndexReply *response);

    Status DelFile(ServerContext *context,
                   const namenodeproto::FileNameRequest *request,
                   namenodeproto::IntReply *response);

    Status DelDir(grpc::ServerContext *context,
                  const namenodeproto::PrefixRequest *request,
                  namenodeproto::IntReply *response);

    Status GetFileSize(grpc::ServerContext *context,
                       const namenodeproto::FileNameRequest *request,
                       namenodeproto::LongReply *response);

    Status Quit(grpc::ServerContext *context,
                const namenodeproto::EmptyRequest *request,
                namenodeproto::IntReply *respone);

private:
    NameNode namenode;
public:
};

#endif // NAMENODESERVER_H
