//
// Created by anson on 19-2-24.
//

#include "datanodeserver.hpp"
#include "../fs.hpp"
#include "../logger.hpp"
#include "datanode.hpp"
#include "fstream"
#include "ostream"
#include "stdio.h"
#include "unistd.h"

DataNodeSerImpl::DataNodeSerImpl(long long node_size)
  : datanode(node_size)
{}

Status
  DataNodeSerImpl::GetFileSize(ServerContext *context,
                               const FileNameRequest *request,
                               LongReply *response)
{
    string name = request->name();
    long long size = datanode.getFileSize(name);
    response->set_result(size);
    return Status::OK;
}

Status
  DataNodeSerImpl::AddEmptyFile(ServerContext *context,
                                const AddEmptyFileRequest *request,
                                IntReply *response)
{
    string name = request->name();
    time_t mtime = request->mtime();
    time_t atime = request->atime();
    time_t ctime = request->ctime();
    datanode.addEmptyFile(name, mtime, atime, ctime);
    response->set_result(0);
    return Status::OK;
}

Status
  DataNodeSerImpl::AddNewFile(ServerContext *context,
                              const AddNewFileRequest *request,
                              IntReply *response)
{
    string name = request->name();
    string content_string = request->content();
    long long size = request->size();
    if (size != content_string.length()) {
        response->set_result(-1);
        FILE_LOG(LOG_ERROR)
          << "Add new file failed, 接收文件大小与要求大小不匹配" << endl;
        return Status::CANCELLED;
    }
    // TODO: 内存泄漏风险！
    //        const char * content = reinterpret_cast<const char *>
    //        (content_string.c_str());
    char content[size];
    memset(content, 0, size);
    memmove(content, (char *) content_string.c_str(), size);
    time_t mtime = request->mtime();
    time_t atime = request->atime();
    time_t ctime = request->ctime();
    datanode.addNewFile(name, content, size, mtime, atime, ctime);
    response->set_result(0);
    return Status::OK;
}

Status
  DataNodeSerImpl::DelFile(ServerContext *context,
                           const FileNameRequest *request,
                           IntReply *response)
{
    string name = request->name();
    int result = datanode.delFile(name);
    response->set_result(result);
    if (result != 0) {
        return Status::CANCELLED;
    }
    return Status::OK;
}

Status
  DataNodeSerImpl::DelDir(ServerContext *context,
                          const PrefixRequest *request,
                          IntReply *response)
{
    string prefix = request->prefix();
    int result = datanode.delDir(prefix);
    response->set_result(result);
    if (result != 0) {
        return Status::CANCELLED;
    }
    return Status::OK;
}

Status
  DataNodeSerImpl::WriteToFile(ServerContext *context,
                               const WriteRequest *request,
                               IntReply *response)
{
    string name = request->name();
    string content_string = request->content();
    long long size = request->size();
    if (size != content_string.length()) {
        response->set_result(-1);
        FILE_LOG(LOG_ERROR) << "Write to" << name
                            << " failed, 接收文件大小与要求大小不匹配" << endl;
        return Status::CANCELLED;
    }
    // TODO: 内存泄漏风险！
    char content[size];
    memset(content, 0, size);
    memmove(content, (char *) content_string.c_str(), size);
    int result = datanode.writeToFile(name, content, size);
    if (result != 0) {
        return Status::CANCELLED;
    }
    return Status::OK;
}

Status
  DataNodeSerImpl::ReadFromFile(ServerContext *context,
                                const ReadRequest *request,
                                ReadReply *response)
{
    string name = request->name();
    long long size = request->size();
    char *buffer = new char[size];
    int result = datanode.readFromFile(name, buffer, size);
    //    cout << result << endl;
    if (result != 0) {
        char result[13] = "No Such File";
        response->set_buffer(result, 13);
        return Status::CANCELLED;
    }
    response->set_buffer(buffer, size);
    // TODO: 空指针预警！！！
    delete[] buffer;
    return Status::OK;
}

Status
  DataNodeSerImpl::AddFileSeg(ServerContext *context,
                              const AddFileSegRequest *request,
                              IntReply *response)
{
    string name = request->name();
    string content_string = request->content();
    int size = request->size();
    if (size != content_string.length()) {
        response->set_result(-1);
        FILE_LOG(LOG_ERROR) << "Write seg to" << name
                            << " failed, 接收文件大小与要求大小不匹配" << endl;
        return Status::CANCELLED;
    }
    char content[size];
    memset(content, 0, size);
    memmove(content, (char *) content_string.c_str(), size);
    int seg = request->seg();
    int result = datanode.addFileSeg(name, content, size, seg);
    if (result != 0) {
        return Status::CANCELLED;
    }
    return Status::OK;
}

Status
  DataNodeSerImpl::GetFileSeg(ServerContext *context,
                              const GetFileSegRequest *request,
                              ReadReply *response)
{
    string name = request->name();
    int size = request->size();
    int seg = request->seg();
    char *buffer = new char[size];
    //    cout << "   " << (void*)buffer << endl;
    int result = datanode.getFileSeg(name, buffer, size, seg);
    if (result != 0) {
        char result[13] = "No Such File";
        response->set_buffer(result, 13);
        return Status::CANCELLED;
    }
    response->set_buffer(buffer, size);
    // 空指针预警
    delete[] buffer;
    return Status::OK;
}

Status
  DataNodeSerImpl::GetChildren(ServerContext *context,
                               const PrefixRequest *request,
                               ChildrenReply *response)
{
    string prefix = request->prefix();
    vector<string> children = datanode.showChildren(prefix);
    for (int i = 0; i < children.size(); i++) {
        response->add_children(children[i]);
    }
    return Status::OK;
}

Status
  DataNodeSerImpl::GetAllChildren(ServerContext *context,
                                  const EmptyRequest *request,
                                  ChildrenReply *response)
{
    vector<string> children = datanode.showAllChildren();
    for (int i = 0; i < children.size(); i++) {
        response->add_children(children[i]);
        //        cout << response->children(i) << endl;
    }
    return Status::OK;
}

grpc::Status
  DataNodeSerImpl::GetSpaceSize(grpc::ServerContext *context,
                                const fsndnproto::EmptyRequest *request,
                                fsndnproto::LongReply *response)
{
    long long space_size = datanode.getSpaceSize();
    response->set_result(space_size);
    return Status::OK;
}
