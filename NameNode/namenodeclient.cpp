#include "namenodeclient.hpp"
#include "../logger.hpp"

NameNodeClient::NameNodeClient(shared_ptr<grpc::Channel> Channel, int node_id)
  : stub_(NameNodeSer::NewStub(Channel))
{
    this->node_id = node_id;
}

int
  NameNodeClient::addDataNode(const string &ip, int node_id)
{
    namenodeproto::AddDataNodeRequst request;
    request.set_ip(ip);
    request.set_node(node_id);
    namenodeproto::IntReply response;
    ClientContext context;
    Status status = stub_->AddDataNode(&context, request, &response);
    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return -1;
    }
    return response.result();
}

int
  NameNodeClient::removeDataNode(int node_id)
{
    namenodeproto::RemDataNodeRequst request;
    request.set_node(node_id);
    namenodeproto::IntReply response;
    ClientContext context;
    Status status = stub_->RemDataNode(&context, request, &response);
    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return -1;
    }
    return response.result();
}

vector<SegIndex>
  NameNodeClient::addNewFile(const string &name,
                             long long size,
                             time_t mtime,
                             time_t atime,
                             time_t ctime)
{
    namenodeproto::AddNewFileRequest request;
    request.set_name(name);
    request.set_size(size);
    request.set_mtime(mtime);
    request.set_atime(atime);
    request.set_ctime(ctime);
    namenodeproto::SegIndexReply response;
    ClientContext context;
    Status status = stub_->AddNewFile(&context, request, &response);
    vector<SegIndex> seg_index;
    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_message() << " " << status.error_code()
          << " Add New File Error : " << name << endl;
        return seg_index;
    }
    for (namenodeproto::SegIndex si : response.index()) {
        SegIndex seg;
        seg.node = si.node();
        for (namenodeproto::SegWithSize item : si.segs()) {
            SegWithSize ss;
            ss.seg = item.seg();
            ss.size = item.size();
            seg.segs.push_back(ss);
        }
        seg_index.push_back(seg);
    }
    return seg_index;
}

vector<SegIndex>
  NameNodeClient::readFile(string name)
{
    namenodeproto::ReadRequest request;
    request.set_name(name);
    namenodeproto::SegIndexReply response;
    ClientContext context;
    Status status = stub_->ReadFromFile(&context, request, &response);
    vector<SegIndex> seg_index;
    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return seg_index;
    }
    for (namenodeproto::SegIndex si : response.index()) {
        SegIndex seg;
        seg.node = si.node();
        for (namenodeproto::SegWithSize item : si.segs()) {
            SegWithSize ss;
            ss.seg = item.seg();
            ss.size = item.size();
            seg.segs.push_back(ss);
        }
        seg_index.push_back(seg);
    }
    return seg_index;
}

int
  NameNodeClient::delFile(const string &name)
{
    namenodeproto::FileNameRequest request;
    request.set_name(name);
    namenodeproto::IntReply response;
    ClientContext context;
    Status status = stub_->DelFile(&context, request, &response);
    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return -1;
    }
    return response.result();
}

int
  NameNodeClient::delDir(const string &prefix)
{
    namenodeproto::PrefixRequest request;
    request.set_prefix(prefix);
    namenodeproto::IntReply response;
    ClientContext context;
    Status status = stub_->DelDir(&context, request, &response);
    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return -1;
    }
    return response.result();
}

void
  NameNodeClient::updateNode(int status)
{
    // Update NameNode need to be implement
    return;
}

long long
  NameNodeClient::getFileSize(const string &name)
{
    namenodeproto::FileNameRequest request;
    request.set_name(name);
    namenodeproto::LongReply response;
    ClientContext context;
    Status status = stub_->GetFileSize(&context, request, &response);
    if (!status.ok()) {
        FILE_LOG(LOG_ERROR)
          << status.error_code() << " : " << status.error_message() << endl;
        return -1;
    }
    return response.result();
}

bool
  NameNodeClient::operator==(const int &other_node_id) const
{
    return this->node_id == other_node_id;
}
