#include "datanodeclient.hpp"
#include "../fs.hpp"
#include "../logger.hpp"
#include <iostream>
#include <memory>
#include <string>

int fsndn::user_id;
int fsndn::group_id;
int fsndn::fsndn_id = 666;
string fsndn::root_path = "/tmp/fsndn";
string fsndn::global_prefix = "/ndn/fsndn/prefix";
int fsndn::seg_size = 2048;

DataNodeClient::DataNodeClient(shared_ptr<Channel> channel, int node_id)
  : stub_(DataNodeSer::NewStub(channel))
{
    this->node_id = node_id;
}

long long
DataNodeClient::getFileSize(const string& name)
{
    FileNameRequest request;
    request.set_name(name);
    LongReply reply;
    ClientContext context;
    Status status = stub_->GetFileSize(&context, request, &reply);

    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return -1;
    }
    return reply.result();
}
// 创建空文件
int
DataNodeClient::addEmptyFile(string name,
                             time_t mtime,
                             time_t atime,
                             time_t ctime)
{
    AddEmptyFileRequest request;
    request.set_name(name);
    ;
    request.set_mtime(mtime);
    request.set_atime(atime);
    request.set_ctime(ctime);
    IntReply reply;
    ClientContext context;
    Status status = stub_->AddEmptyFile(&context, request, &reply);

    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return -1;
    }
    return reply.result();
}

// 创建含内容的文件
int
DataNodeClient::addNewFile(string name,
                           const char* content,
                           long long size,
                           time_t mtime,
                           time_t atime,
                           time_t ctime)
{
    AddNewFileRequest request;
    request.set_name(name);
    ;
    request.set_content(content, size);
    request.set_size(size);
    request.set_mtime(mtime);
    request.set_atime(atime);
    request.set_ctime(ctime);
    IntReply reply;
    ClientContext context;
    Status status = stub_->AddNewFile(&context, request, &reply);
    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return -1;
    }
    return reply.result();
}

int
DataNodeClient::delFile(string name)
{
    FileNameRequest request;
    request.set_name(name);
    IntReply reply;
    ClientContext context;
    Status status = stub_->DelFile(&context, request, &reply);

    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return -1;
    }
    return reply.result();
}
int
DataNodeClient::delDir(string prefix)
{
    PrefixRequest request;
    request.set_prefix(prefix);
    IntReply reply;
    ClientContext context;
    Status status = stub_->DelDir(&context, request, &reply);

    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return -1;
    }
    return reply.result();
}

int
DataNodeClient::writeToFile(string name, const char* content, long long size)
{
    WriteRequest request;
    request.set_name(name);
    request.set_content(content, size);
    request.set_size(size);
    IntReply reply;
    ClientContext context;
    Status status = stub_->WriteToFile(&context, request, &reply);

    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return -1;
    }
    return reply.result();
}

int
DataNodeClient::readFromFile(string name, char* buffer, long long size)
{
    ReadRequest request;
    request.set_name(name);
    request.set_size(size);
    ReadReply reply;
    ClientContext context;
    Status status = stub_->ReadFromFile(&context, request, &reply);

    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return -1;
    }
    string buffer_string = reply.buffer();
    // TODO: 内存泄漏风险！
    //    memset(buffer, 0, size);
    memmove(buffer, (char*)buffer_string.c_str(), size);
    return 0;
}

int
DataNodeClient::addFileSeg(string name, const char* content, int size, int seg)
{
    AddFileSegRequest request;
    request.set_name(name);
    request.set_content(content, size);
    request.set_size(size);
    request.set_seg(seg);
    IntReply reply;
    ClientContext context;
    Status status = stub_->AddFileSeg(&context, request, &reply);
    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return -1;
    }
    return reply.result();
}

int
DataNodeClient::getFileSeg(string name, char* buffer, int size, int seg)
{
    GetFileSegRequest request;
    request.set_name(name);
    request.set_size(size);
    request.set_seg(seg);
    ReadReply reply;
    ClientContext context;
    Status status = stub_->GetFileSeg(&context, request, &reply);

    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return -1;
    }
    string buffer_string = reply.buffer();
    // TODO: 内存泄漏风险！
    memset(buffer, 0, size);
    memmove(buffer, (char*)buffer_string.c_str(), size);
    return 0;
}

vector<string>
DataNodeClient::showChildren(string prefix)
{
    PrefixRequest request;
    request.set_prefix(prefix);
    ChildrenReply reply;
    ClientContext context;
    Status status = stub_->GetChildren(&context, request, &reply);
    vector<string> result;
    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return result;
    }
    for (int i = 0; i < reply.children_size(); i++) {
        result.push_back(reply.children(i));
    }
    return result;
}

vector<string>
DataNodeClient::showAllChildren()
{
    EmptyRequest request;
    ChildrenReply reply;
    ClientContext context;
    Status status = stub_->GetAllChildren(&context, request, &reply);
    vector<string> result;
    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return result;
    }
    return result;
}

long long
DataNodeClient::getSpaceSize() const
{
    EmptyRequest request;
    LongReply reply;
    ClientContext context;
    Status status = stub_->GetSpaceSize(&context, request, &reply);
    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return -1;
    }
    return reply.result();
}

int
DataNodeClient::getNodeId()
{
    return node_id;
}

bool
DataNodeClient::operator==(const int& other_node_id) const
{
    return this->node_id == other_node_id;
}

bool
DataNodeClient::operator<(const DataNodeClient& other_node) const
{
    return this->getSpaceSize() < other_node.getSpaceSize();
}
