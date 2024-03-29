// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: namenode.proto

#include "namenode.pb.h"
#include "namenode.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace namenodeproto {

static const char* NameNodeSer_method_names[] = {
  "/namenodeproto.NameNodeSer/AddNewFile",
  "/namenodeproto.NameNodeSer/DelFile",
  "/namenodeproto.NameNodeSer/DelDir",
  "/namenodeproto.NameNodeSer/GetFileSize",
  "/namenodeproto.NameNodeSer/ReadFromFile",
  "/namenodeproto.NameNodeSer/AddDataNode",
  "/namenodeproto.NameNodeSer/RemDataNode",
  "/namenodeproto.NameNodeSer/Quit",
};

std::unique_ptr< NameNodeSer::Stub> NameNodeSer::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< NameNodeSer::Stub> stub(new NameNodeSer::Stub(channel));
  return stub;
}

NameNodeSer::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_AddNewFile_(NameNodeSer_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_DelFile_(NameNodeSer_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_DelDir_(NameNodeSer_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetFileSize_(NameNodeSer_method_names[3], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ReadFromFile_(NameNodeSer_method_names[4], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_AddDataNode_(NameNodeSer_method_names[5], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_RemDataNode_(NameNodeSer_method_names[6], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Quit_(NameNodeSer_method_names[7], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status NameNodeSer::Stub::AddNewFile(::grpc::ClientContext* context, const ::namenodeproto::AddNewFileRequest& request, ::namenodeproto::SegIndexReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_AddNewFile_, context, request, response);
}

void NameNodeSer::Stub::experimental_async::AddNewFile(::grpc::ClientContext* context, const ::namenodeproto::AddNewFileRequest* request, ::namenodeproto::SegIndexReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_AddNewFile_, context, request, response, std::move(f));
}

void NameNodeSer::Stub::experimental_async::AddNewFile(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::namenodeproto::SegIndexReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_AddNewFile_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::namenodeproto::SegIndexReply>* NameNodeSer::Stub::AsyncAddNewFileRaw(::grpc::ClientContext* context, const ::namenodeproto::AddNewFileRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::namenodeproto::SegIndexReply>::Create(channel_.get(), cq, rpcmethod_AddNewFile_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::namenodeproto::SegIndexReply>* NameNodeSer::Stub::PrepareAsyncAddNewFileRaw(::grpc::ClientContext* context, const ::namenodeproto::AddNewFileRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::namenodeproto::SegIndexReply>::Create(channel_.get(), cq, rpcmethod_AddNewFile_, context, request, false);
}

::grpc::Status NameNodeSer::Stub::DelFile(::grpc::ClientContext* context, const ::namenodeproto::FileNameRequest& request, ::namenodeproto::IntReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_DelFile_, context, request, response);
}

void NameNodeSer::Stub::experimental_async::DelFile(::grpc::ClientContext* context, const ::namenodeproto::FileNameRequest* request, ::namenodeproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_DelFile_, context, request, response, std::move(f));
}

void NameNodeSer::Stub::experimental_async::DelFile(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::namenodeproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_DelFile_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::namenodeproto::IntReply>* NameNodeSer::Stub::AsyncDelFileRaw(::grpc::ClientContext* context, const ::namenodeproto::FileNameRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::namenodeproto::IntReply>::Create(channel_.get(), cq, rpcmethod_DelFile_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::namenodeproto::IntReply>* NameNodeSer::Stub::PrepareAsyncDelFileRaw(::grpc::ClientContext* context, const ::namenodeproto::FileNameRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::namenodeproto::IntReply>::Create(channel_.get(), cq, rpcmethod_DelFile_, context, request, false);
}

::grpc::Status NameNodeSer::Stub::DelDir(::grpc::ClientContext* context, const ::namenodeproto::PrefixRequest& request, ::namenodeproto::IntReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_DelDir_, context, request, response);
}

void NameNodeSer::Stub::experimental_async::DelDir(::grpc::ClientContext* context, const ::namenodeproto::PrefixRequest* request, ::namenodeproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_DelDir_, context, request, response, std::move(f));
}

void NameNodeSer::Stub::experimental_async::DelDir(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::namenodeproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_DelDir_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::namenodeproto::IntReply>* NameNodeSer::Stub::AsyncDelDirRaw(::grpc::ClientContext* context, const ::namenodeproto::PrefixRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::namenodeproto::IntReply>::Create(channel_.get(), cq, rpcmethod_DelDir_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::namenodeproto::IntReply>* NameNodeSer::Stub::PrepareAsyncDelDirRaw(::grpc::ClientContext* context, const ::namenodeproto::PrefixRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::namenodeproto::IntReply>::Create(channel_.get(), cq, rpcmethod_DelDir_, context, request, false);
}

::grpc::Status NameNodeSer::Stub::GetFileSize(::grpc::ClientContext* context, const ::namenodeproto::FileNameRequest& request, ::namenodeproto::LongReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GetFileSize_, context, request, response);
}

void NameNodeSer::Stub::experimental_async::GetFileSize(::grpc::ClientContext* context, const ::namenodeproto::FileNameRequest* request, ::namenodeproto::LongReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetFileSize_, context, request, response, std::move(f));
}

void NameNodeSer::Stub::experimental_async::GetFileSize(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::namenodeproto::LongReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetFileSize_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::namenodeproto::LongReply>* NameNodeSer::Stub::AsyncGetFileSizeRaw(::grpc::ClientContext* context, const ::namenodeproto::FileNameRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::namenodeproto::LongReply>::Create(channel_.get(), cq, rpcmethod_GetFileSize_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::namenodeproto::LongReply>* NameNodeSer::Stub::PrepareAsyncGetFileSizeRaw(::grpc::ClientContext* context, const ::namenodeproto::FileNameRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::namenodeproto::LongReply>::Create(channel_.get(), cq, rpcmethod_GetFileSize_, context, request, false);
}

::grpc::Status NameNodeSer::Stub::ReadFromFile(::grpc::ClientContext* context, const ::namenodeproto::ReadRequest& request, ::namenodeproto::SegIndexReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_ReadFromFile_, context, request, response);
}

void NameNodeSer::Stub::experimental_async::ReadFromFile(::grpc::ClientContext* context, const ::namenodeproto::ReadRequest* request, ::namenodeproto::SegIndexReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_ReadFromFile_, context, request, response, std::move(f));
}

void NameNodeSer::Stub::experimental_async::ReadFromFile(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::namenodeproto::SegIndexReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_ReadFromFile_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::namenodeproto::SegIndexReply>* NameNodeSer::Stub::AsyncReadFromFileRaw(::grpc::ClientContext* context, const ::namenodeproto::ReadRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::namenodeproto::SegIndexReply>::Create(channel_.get(), cq, rpcmethod_ReadFromFile_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::namenodeproto::SegIndexReply>* NameNodeSer::Stub::PrepareAsyncReadFromFileRaw(::grpc::ClientContext* context, const ::namenodeproto::ReadRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::namenodeproto::SegIndexReply>::Create(channel_.get(), cq, rpcmethod_ReadFromFile_, context, request, false);
}

::grpc::Status NameNodeSer::Stub::AddDataNode(::grpc::ClientContext* context, const ::namenodeproto::AddDataNodeRequst& request, ::namenodeproto::IntReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_AddDataNode_, context, request, response);
}

void NameNodeSer::Stub::experimental_async::AddDataNode(::grpc::ClientContext* context, const ::namenodeproto::AddDataNodeRequst* request, ::namenodeproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_AddDataNode_, context, request, response, std::move(f));
}

void NameNodeSer::Stub::experimental_async::AddDataNode(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::namenodeproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_AddDataNode_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::namenodeproto::IntReply>* NameNodeSer::Stub::AsyncAddDataNodeRaw(::grpc::ClientContext* context, const ::namenodeproto::AddDataNodeRequst& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::namenodeproto::IntReply>::Create(channel_.get(), cq, rpcmethod_AddDataNode_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::namenodeproto::IntReply>* NameNodeSer::Stub::PrepareAsyncAddDataNodeRaw(::grpc::ClientContext* context, const ::namenodeproto::AddDataNodeRequst& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::namenodeproto::IntReply>::Create(channel_.get(), cq, rpcmethod_AddDataNode_, context, request, false);
}

::grpc::Status NameNodeSer::Stub::RemDataNode(::grpc::ClientContext* context, const ::namenodeproto::RemDataNodeRequst& request, ::namenodeproto::IntReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_RemDataNode_, context, request, response);
}

void NameNodeSer::Stub::experimental_async::RemDataNode(::grpc::ClientContext* context, const ::namenodeproto::RemDataNodeRequst* request, ::namenodeproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_RemDataNode_, context, request, response, std::move(f));
}

void NameNodeSer::Stub::experimental_async::RemDataNode(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::namenodeproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_RemDataNode_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::namenodeproto::IntReply>* NameNodeSer::Stub::AsyncRemDataNodeRaw(::grpc::ClientContext* context, const ::namenodeproto::RemDataNodeRequst& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::namenodeproto::IntReply>::Create(channel_.get(), cq, rpcmethod_RemDataNode_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::namenodeproto::IntReply>* NameNodeSer::Stub::PrepareAsyncRemDataNodeRaw(::grpc::ClientContext* context, const ::namenodeproto::RemDataNodeRequst& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::namenodeproto::IntReply>::Create(channel_.get(), cq, rpcmethod_RemDataNode_, context, request, false);
}

::grpc::Status NameNodeSer::Stub::Quit(::grpc::ClientContext* context, const ::namenodeproto::EmptyRequest& request, ::namenodeproto::IntReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Quit_, context, request, response);
}

void NameNodeSer::Stub::experimental_async::Quit(::grpc::ClientContext* context, const ::namenodeproto::EmptyRequest* request, ::namenodeproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Quit_, context, request, response, std::move(f));
}

void NameNodeSer::Stub::experimental_async::Quit(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::namenodeproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Quit_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::namenodeproto::IntReply>* NameNodeSer::Stub::AsyncQuitRaw(::grpc::ClientContext* context, const ::namenodeproto::EmptyRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::namenodeproto::IntReply>::Create(channel_.get(), cq, rpcmethod_Quit_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::namenodeproto::IntReply>* NameNodeSer::Stub::PrepareAsyncQuitRaw(::grpc::ClientContext* context, const ::namenodeproto::EmptyRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::namenodeproto::IntReply>::Create(channel_.get(), cq, rpcmethod_Quit_, context, request, false);
}

NameNodeSer::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NameNodeSer_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NameNodeSer::Service, ::namenodeproto::AddNewFileRequest, ::namenodeproto::SegIndexReply>(
          std::mem_fn(&NameNodeSer::Service::AddNewFile), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NameNodeSer_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NameNodeSer::Service, ::namenodeproto::FileNameRequest, ::namenodeproto::IntReply>(
          std::mem_fn(&NameNodeSer::Service::DelFile), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NameNodeSer_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NameNodeSer::Service, ::namenodeproto::PrefixRequest, ::namenodeproto::IntReply>(
          std::mem_fn(&NameNodeSer::Service::DelDir), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NameNodeSer_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NameNodeSer::Service, ::namenodeproto::FileNameRequest, ::namenodeproto::LongReply>(
          std::mem_fn(&NameNodeSer::Service::GetFileSize), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NameNodeSer_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NameNodeSer::Service, ::namenodeproto::ReadRequest, ::namenodeproto::SegIndexReply>(
          std::mem_fn(&NameNodeSer::Service::ReadFromFile), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NameNodeSer_method_names[5],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NameNodeSer::Service, ::namenodeproto::AddDataNodeRequst, ::namenodeproto::IntReply>(
          std::mem_fn(&NameNodeSer::Service::AddDataNode), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NameNodeSer_method_names[6],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NameNodeSer::Service, ::namenodeproto::RemDataNodeRequst, ::namenodeproto::IntReply>(
          std::mem_fn(&NameNodeSer::Service::RemDataNode), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      NameNodeSer_method_names[7],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< NameNodeSer::Service, ::namenodeproto::EmptyRequest, ::namenodeproto::IntReply>(
          std::mem_fn(&NameNodeSer::Service::Quit), this)));
}

NameNodeSer::Service::~Service() {
}

::grpc::Status NameNodeSer::Service::AddNewFile(::grpc::ServerContext* context, const ::namenodeproto::AddNewFileRequest* request, ::namenodeproto::SegIndexReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status NameNodeSer::Service::DelFile(::grpc::ServerContext* context, const ::namenodeproto::FileNameRequest* request, ::namenodeproto::IntReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status NameNodeSer::Service::DelDir(::grpc::ServerContext* context, const ::namenodeproto::PrefixRequest* request, ::namenodeproto::IntReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status NameNodeSer::Service::GetFileSize(::grpc::ServerContext* context, const ::namenodeproto::FileNameRequest* request, ::namenodeproto::LongReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status NameNodeSer::Service::ReadFromFile(::grpc::ServerContext* context, const ::namenodeproto::ReadRequest* request, ::namenodeproto::SegIndexReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status NameNodeSer::Service::AddDataNode(::grpc::ServerContext* context, const ::namenodeproto::AddDataNodeRequst* request, ::namenodeproto::IntReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status NameNodeSer::Service::RemDataNode(::grpc::ServerContext* context, const ::namenodeproto::RemDataNodeRequst* request, ::namenodeproto::IntReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status NameNodeSer::Service::Quit(::grpc::ServerContext* context, const ::namenodeproto::EmptyRequest* request, ::namenodeproto::IntReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace namenodeproto

