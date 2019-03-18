// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: fsndn.proto

#include "fsndn.pb.h"
#include "fsndn.grpc.pb.h"

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
namespace fsndnproto {

static const char* DataNodeSer_method_names[] = {
  "/fsndnproto.DataNodeSer/AddEmptyFile",
  "/fsndnproto.DataNodeSer/AddNewFile",
  "/fsndnproto.DataNodeSer/DelFile",
  "/fsndnproto.DataNodeSer/DelDir",
  "/fsndnproto.DataNodeSer/GetFileSize",
  "/fsndnproto.DataNodeSer/WriteToFile",
  "/fsndnproto.DataNodeSer/ReadFromFile",
  "/fsndnproto.DataNodeSer/AddFileSeg",
  "/fsndnproto.DataNodeSer/GetFileSeg",
  "/fsndnproto.DataNodeSer/GetChildren",
  "/fsndnproto.DataNodeSer/GetAllChildren",
  "/fsndnproto.DataNodeSer/GetSpaceSize",
};

std::unique_ptr< DataNodeSer::Stub> DataNodeSer::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< DataNodeSer::Stub> stub(new DataNodeSer::Stub(channel));
  return stub;
}

DataNodeSer::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_AddEmptyFile_(DataNodeSer_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_AddNewFile_(DataNodeSer_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_DelFile_(DataNodeSer_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_DelDir_(DataNodeSer_method_names[3], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetFileSize_(DataNodeSer_method_names[4], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_WriteToFile_(DataNodeSer_method_names[5], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ReadFromFile_(DataNodeSer_method_names[6], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_AddFileSeg_(DataNodeSer_method_names[7], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetFileSeg_(DataNodeSer_method_names[8], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetChildren_(DataNodeSer_method_names[9], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetAllChildren_(DataNodeSer_method_names[10], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetSpaceSize_(DataNodeSer_method_names[11], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status DataNodeSer::Stub::AddEmptyFile(::grpc::ClientContext* context, const ::fsndnproto::AddEmptyFileRequest& request, ::fsndnproto::IntReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_AddEmptyFile_, context, request, response);
}

void DataNodeSer::Stub::experimental_async::AddEmptyFile(::grpc::ClientContext* context, const ::fsndnproto::AddEmptyFileRequest* request, ::fsndnproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_AddEmptyFile_, context, request, response, std::move(f));
}

void DataNodeSer::Stub::experimental_async::AddEmptyFile(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::fsndnproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_AddEmptyFile_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::IntReply>* DataNodeSer::Stub::AsyncAddEmptyFileRaw(::grpc::ClientContext* context, const ::fsndnproto::AddEmptyFileRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::IntReply>::Create(channel_.get(), cq, rpcmethod_AddEmptyFile_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::IntReply>* DataNodeSer::Stub::PrepareAsyncAddEmptyFileRaw(::grpc::ClientContext* context, const ::fsndnproto::AddEmptyFileRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::IntReply>::Create(channel_.get(), cq, rpcmethod_AddEmptyFile_, context, request, false);
}

::grpc::Status DataNodeSer::Stub::AddNewFile(::grpc::ClientContext* context, const ::fsndnproto::AddNewFileRequest& request, ::fsndnproto::IntReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_AddNewFile_, context, request, response);
}

void DataNodeSer::Stub::experimental_async::AddNewFile(::grpc::ClientContext* context, const ::fsndnproto::AddNewFileRequest* request, ::fsndnproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_AddNewFile_, context, request, response, std::move(f));
}

void DataNodeSer::Stub::experimental_async::AddNewFile(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::fsndnproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_AddNewFile_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::IntReply>* DataNodeSer::Stub::AsyncAddNewFileRaw(::grpc::ClientContext* context, const ::fsndnproto::AddNewFileRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::IntReply>::Create(channel_.get(), cq, rpcmethod_AddNewFile_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::IntReply>* DataNodeSer::Stub::PrepareAsyncAddNewFileRaw(::grpc::ClientContext* context, const ::fsndnproto::AddNewFileRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::IntReply>::Create(channel_.get(), cq, rpcmethod_AddNewFile_, context, request, false);
}

::grpc::Status DataNodeSer::Stub::DelFile(::grpc::ClientContext* context, const ::fsndnproto::FileNameRequest& request, ::fsndnproto::IntReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_DelFile_, context, request, response);
}

void DataNodeSer::Stub::experimental_async::DelFile(::grpc::ClientContext* context, const ::fsndnproto::FileNameRequest* request, ::fsndnproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_DelFile_, context, request, response, std::move(f));
}

void DataNodeSer::Stub::experimental_async::DelFile(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::fsndnproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_DelFile_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::IntReply>* DataNodeSer::Stub::AsyncDelFileRaw(::grpc::ClientContext* context, const ::fsndnproto::FileNameRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::IntReply>::Create(channel_.get(), cq, rpcmethod_DelFile_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::IntReply>* DataNodeSer::Stub::PrepareAsyncDelFileRaw(::grpc::ClientContext* context, const ::fsndnproto::FileNameRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::IntReply>::Create(channel_.get(), cq, rpcmethod_DelFile_, context, request, false);
}

::grpc::Status DataNodeSer::Stub::DelDir(::grpc::ClientContext* context, const ::fsndnproto::PrefixRequest& request, ::fsndnproto::IntReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_DelDir_, context, request, response);
}

void DataNodeSer::Stub::experimental_async::DelDir(::grpc::ClientContext* context, const ::fsndnproto::PrefixRequest* request, ::fsndnproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_DelDir_, context, request, response, std::move(f));
}

void DataNodeSer::Stub::experimental_async::DelDir(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::fsndnproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_DelDir_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::IntReply>* DataNodeSer::Stub::AsyncDelDirRaw(::grpc::ClientContext* context, const ::fsndnproto::PrefixRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::IntReply>::Create(channel_.get(), cq, rpcmethod_DelDir_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::IntReply>* DataNodeSer::Stub::PrepareAsyncDelDirRaw(::grpc::ClientContext* context, const ::fsndnproto::PrefixRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::IntReply>::Create(channel_.get(), cq, rpcmethod_DelDir_, context, request, false);
}

::grpc::Status DataNodeSer::Stub::GetFileSize(::grpc::ClientContext* context, const ::fsndnproto::FileNameRequest& request, ::fsndnproto::LongReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GetFileSize_, context, request, response);
}

void DataNodeSer::Stub::experimental_async::GetFileSize(::grpc::ClientContext* context, const ::fsndnproto::FileNameRequest* request, ::fsndnproto::LongReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetFileSize_, context, request, response, std::move(f));
}

void DataNodeSer::Stub::experimental_async::GetFileSize(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::fsndnproto::LongReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetFileSize_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::LongReply>* DataNodeSer::Stub::AsyncGetFileSizeRaw(::grpc::ClientContext* context, const ::fsndnproto::FileNameRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::LongReply>::Create(channel_.get(), cq, rpcmethod_GetFileSize_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::LongReply>* DataNodeSer::Stub::PrepareAsyncGetFileSizeRaw(::grpc::ClientContext* context, const ::fsndnproto::FileNameRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::LongReply>::Create(channel_.get(), cq, rpcmethod_GetFileSize_, context, request, false);
}

::grpc::Status DataNodeSer::Stub::WriteToFile(::grpc::ClientContext* context, const ::fsndnproto::WriteRequest& request, ::fsndnproto::IntReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_WriteToFile_, context, request, response);
}

void DataNodeSer::Stub::experimental_async::WriteToFile(::grpc::ClientContext* context, const ::fsndnproto::WriteRequest* request, ::fsndnproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_WriteToFile_, context, request, response, std::move(f));
}

void DataNodeSer::Stub::experimental_async::WriteToFile(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::fsndnproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_WriteToFile_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::IntReply>* DataNodeSer::Stub::AsyncWriteToFileRaw(::grpc::ClientContext* context, const ::fsndnproto::WriteRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::IntReply>::Create(channel_.get(), cq, rpcmethod_WriteToFile_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::IntReply>* DataNodeSer::Stub::PrepareAsyncWriteToFileRaw(::grpc::ClientContext* context, const ::fsndnproto::WriteRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::IntReply>::Create(channel_.get(), cq, rpcmethod_WriteToFile_, context, request, false);
}

::grpc::Status DataNodeSer::Stub::ReadFromFile(::grpc::ClientContext* context, const ::fsndnproto::ReadRequest& request, ::fsndnproto::ReadReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_ReadFromFile_, context, request, response);
}

void DataNodeSer::Stub::experimental_async::ReadFromFile(::grpc::ClientContext* context, const ::fsndnproto::ReadRequest* request, ::fsndnproto::ReadReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_ReadFromFile_, context, request, response, std::move(f));
}

void DataNodeSer::Stub::experimental_async::ReadFromFile(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::fsndnproto::ReadReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_ReadFromFile_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::ReadReply>* DataNodeSer::Stub::AsyncReadFromFileRaw(::grpc::ClientContext* context, const ::fsndnproto::ReadRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::ReadReply>::Create(channel_.get(), cq, rpcmethod_ReadFromFile_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::ReadReply>* DataNodeSer::Stub::PrepareAsyncReadFromFileRaw(::grpc::ClientContext* context, const ::fsndnproto::ReadRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::ReadReply>::Create(channel_.get(), cq, rpcmethod_ReadFromFile_, context, request, false);
}

::grpc::Status DataNodeSer::Stub::AddFileSeg(::grpc::ClientContext* context, const ::fsndnproto::AddFileSegRequest& request, ::fsndnproto::IntReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_AddFileSeg_, context, request, response);
}

void DataNodeSer::Stub::experimental_async::AddFileSeg(::grpc::ClientContext* context, const ::fsndnproto::AddFileSegRequest* request, ::fsndnproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_AddFileSeg_, context, request, response, std::move(f));
}

void DataNodeSer::Stub::experimental_async::AddFileSeg(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::fsndnproto::IntReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_AddFileSeg_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::IntReply>* DataNodeSer::Stub::AsyncAddFileSegRaw(::grpc::ClientContext* context, const ::fsndnproto::AddFileSegRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::IntReply>::Create(channel_.get(), cq, rpcmethod_AddFileSeg_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::IntReply>* DataNodeSer::Stub::PrepareAsyncAddFileSegRaw(::grpc::ClientContext* context, const ::fsndnproto::AddFileSegRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::IntReply>::Create(channel_.get(), cq, rpcmethod_AddFileSeg_, context, request, false);
}

::grpc::Status DataNodeSer::Stub::GetFileSeg(::grpc::ClientContext* context, const ::fsndnproto::GetFileSegRequest& request, ::fsndnproto::ReadReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GetFileSeg_, context, request, response);
}

void DataNodeSer::Stub::experimental_async::GetFileSeg(::grpc::ClientContext* context, const ::fsndnproto::GetFileSegRequest* request, ::fsndnproto::ReadReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetFileSeg_, context, request, response, std::move(f));
}

void DataNodeSer::Stub::experimental_async::GetFileSeg(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::fsndnproto::ReadReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetFileSeg_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::ReadReply>* DataNodeSer::Stub::AsyncGetFileSegRaw(::grpc::ClientContext* context, const ::fsndnproto::GetFileSegRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::ReadReply>::Create(channel_.get(), cq, rpcmethod_GetFileSeg_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::ReadReply>* DataNodeSer::Stub::PrepareAsyncGetFileSegRaw(::grpc::ClientContext* context, const ::fsndnproto::GetFileSegRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::ReadReply>::Create(channel_.get(), cq, rpcmethod_GetFileSeg_, context, request, false);
}

::grpc::Status DataNodeSer::Stub::GetChildren(::grpc::ClientContext* context, const ::fsndnproto::PrefixRequest& request, ::fsndnproto::ChildrenReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GetChildren_, context, request, response);
}

void DataNodeSer::Stub::experimental_async::GetChildren(::grpc::ClientContext* context, const ::fsndnproto::PrefixRequest* request, ::fsndnproto::ChildrenReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetChildren_, context, request, response, std::move(f));
}

void DataNodeSer::Stub::experimental_async::GetChildren(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::fsndnproto::ChildrenReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetChildren_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::ChildrenReply>* DataNodeSer::Stub::AsyncGetChildrenRaw(::grpc::ClientContext* context, const ::fsndnproto::PrefixRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::ChildrenReply>::Create(channel_.get(), cq, rpcmethod_GetChildren_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::ChildrenReply>* DataNodeSer::Stub::PrepareAsyncGetChildrenRaw(::grpc::ClientContext* context, const ::fsndnproto::PrefixRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::ChildrenReply>::Create(channel_.get(), cq, rpcmethod_GetChildren_, context, request, false);
}

::grpc::Status DataNodeSer::Stub::GetAllChildren(::grpc::ClientContext* context, const ::fsndnproto::EmptyRequest& request, ::fsndnproto::ChildrenReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GetAllChildren_, context, request, response);
}

void DataNodeSer::Stub::experimental_async::GetAllChildren(::grpc::ClientContext* context, const ::fsndnproto::EmptyRequest* request, ::fsndnproto::ChildrenReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetAllChildren_, context, request, response, std::move(f));
}

void DataNodeSer::Stub::experimental_async::GetAllChildren(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::fsndnproto::ChildrenReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetAllChildren_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::ChildrenReply>* DataNodeSer::Stub::AsyncGetAllChildrenRaw(::grpc::ClientContext* context, const ::fsndnproto::EmptyRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::ChildrenReply>::Create(channel_.get(), cq, rpcmethod_GetAllChildren_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::ChildrenReply>* DataNodeSer::Stub::PrepareAsyncGetAllChildrenRaw(::grpc::ClientContext* context, const ::fsndnproto::EmptyRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::ChildrenReply>::Create(channel_.get(), cq, rpcmethod_GetAllChildren_, context, request, false);
}

::grpc::Status DataNodeSer::Stub::GetSpaceSize(::grpc::ClientContext* context, const ::fsndnproto::EmptyRequest& request, ::fsndnproto::LongReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GetSpaceSize_, context, request, response);
}

void DataNodeSer::Stub::experimental_async::GetSpaceSize(::grpc::ClientContext* context, const ::fsndnproto::EmptyRequest* request, ::fsndnproto::LongReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetSpaceSize_, context, request, response, std::move(f));
}

void DataNodeSer::Stub::experimental_async::GetSpaceSize(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::fsndnproto::LongReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetSpaceSize_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::LongReply>* DataNodeSer::Stub::AsyncGetSpaceSizeRaw(::grpc::ClientContext* context, const ::fsndnproto::EmptyRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::LongReply>::Create(channel_.get(), cq, rpcmethod_GetSpaceSize_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::fsndnproto::LongReply>* DataNodeSer::Stub::PrepareAsyncGetSpaceSizeRaw(::grpc::ClientContext* context, const ::fsndnproto::EmptyRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::fsndnproto::LongReply>::Create(channel_.get(), cq, rpcmethod_GetSpaceSize_, context, request, false);
}

DataNodeSer::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataNodeSer_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataNodeSer::Service, ::fsndnproto::AddEmptyFileRequest, ::fsndnproto::IntReply>(
          std::mem_fn(&DataNodeSer::Service::AddEmptyFile), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataNodeSer_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataNodeSer::Service, ::fsndnproto::AddNewFileRequest, ::fsndnproto::IntReply>(
          std::mem_fn(&DataNodeSer::Service::AddNewFile), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataNodeSer_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataNodeSer::Service, ::fsndnproto::FileNameRequest, ::fsndnproto::IntReply>(
          std::mem_fn(&DataNodeSer::Service::DelFile), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataNodeSer_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataNodeSer::Service, ::fsndnproto::PrefixRequest, ::fsndnproto::IntReply>(
          std::mem_fn(&DataNodeSer::Service::DelDir), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataNodeSer_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataNodeSer::Service, ::fsndnproto::FileNameRequest, ::fsndnproto::LongReply>(
          std::mem_fn(&DataNodeSer::Service::GetFileSize), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataNodeSer_method_names[5],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataNodeSer::Service, ::fsndnproto::WriteRequest, ::fsndnproto::IntReply>(
          std::mem_fn(&DataNodeSer::Service::WriteToFile), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataNodeSer_method_names[6],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataNodeSer::Service, ::fsndnproto::ReadRequest, ::fsndnproto::ReadReply>(
          std::mem_fn(&DataNodeSer::Service::ReadFromFile), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataNodeSer_method_names[7],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataNodeSer::Service, ::fsndnproto::AddFileSegRequest, ::fsndnproto::IntReply>(
          std::mem_fn(&DataNodeSer::Service::AddFileSeg), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataNodeSer_method_names[8],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataNodeSer::Service, ::fsndnproto::GetFileSegRequest, ::fsndnproto::ReadReply>(
          std::mem_fn(&DataNodeSer::Service::GetFileSeg), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataNodeSer_method_names[9],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataNodeSer::Service, ::fsndnproto::PrefixRequest, ::fsndnproto::ChildrenReply>(
          std::mem_fn(&DataNodeSer::Service::GetChildren), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataNodeSer_method_names[10],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataNodeSer::Service, ::fsndnproto::EmptyRequest, ::fsndnproto::ChildrenReply>(
          std::mem_fn(&DataNodeSer::Service::GetAllChildren), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataNodeSer_method_names[11],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataNodeSer::Service, ::fsndnproto::EmptyRequest, ::fsndnproto::LongReply>(
          std::mem_fn(&DataNodeSer::Service::GetSpaceSize), this)));
}

DataNodeSer::Service::~Service() {
}

::grpc::Status DataNodeSer::Service::AddEmptyFile(::grpc::ServerContext* context, const ::fsndnproto::AddEmptyFileRequest* request, ::fsndnproto::IntReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataNodeSer::Service::AddNewFile(::grpc::ServerContext* context, const ::fsndnproto::AddNewFileRequest* request, ::fsndnproto::IntReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataNodeSer::Service::DelFile(::grpc::ServerContext* context, const ::fsndnproto::FileNameRequest* request, ::fsndnproto::IntReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataNodeSer::Service::DelDir(::grpc::ServerContext* context, const ::fsndnproto::PrefixRequest* request, ::fsndnproto::IntReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataNodeSer::Service::GetFileSize(::grpc::ServerContext* context, const ::fsndnproto::FileNameRequest* request, ::fsndnproto::LongReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataNodeSer::Service::WriteToFile(::grpc::ServerContext* context, const ::fsndnproto::WriteRequest* request, ::fsndnproto::IntReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataNodeSer::Service::ReadFromFile(::grpc::ServerContext* context, const ::fsndnproto::ReadRequest* request, ::fsndnproto::ReadReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataNodeSer::Service::AddFileSeg(::grpc::ServerContext* context, const ::fsndnproto::AddFileSegRequest* request, ::fsndnproto::IntReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataNodeSer::Service::GetFileSeg(::grpc::ServerContext* context, const ::fsndnproto::GetFileSegRequest* request, ::fsndnproto::ReadReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataNodeSer::Service::GetChildren(::grpc::ServerContext* context, const ::fsndnproto::PrefixRequest* request, ::fsndnproto::ChildrenReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataNodeSer::Service::GetAllChildren(::grpc::ServerContext* context, const ::fsndnproto::EmptyRequest* request, ::fsndnproto::ChildrenReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataNodeSer::Service::GetSpaceSize(::grpc::ServerContext* context, const ::fsndnproto::EmptyRequest* request, ::fsndnproto::LongReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace fsndnproto

