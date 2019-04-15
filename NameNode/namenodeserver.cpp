#include "namenodeserver.hpp"
#include "../fs.hpp"
#include "../logger.hpp"
#include "namenode.hpp"

grpc::Status
NameNodeSerImpl::AddDataNode(grpc::ServerContext *context,
                             const namenodeproto::AddDataNodeRequst *request,
                             namenodeproto::IntReply *response) {
    string ip = request->ip();
    int node = request->node();
    int result = namenode.addDataNode(ip, node);
    response->set_result(result);
    if (result != 0) {
        FILE_LOG(LOG_ERROR)
            << "Add DataNode Failed, node already exists" << endl;
        return Status::CANCELLED;
    }
    return Status::OK;
}

grpc::Status
NameNodeSerImpl::RemDataNode(grpc::ServerContext *context,
                             const namenodeproto::RemDataNodeRequst *request,
                             namenodeproto::IntReply *response) {
    int node = request->node();
    int result = namenode.removeDataNode(node);
    response->set_result(result);
    if (result != 0) {
        FILE_LOG(LOG_ERROR) << "Remove DataNode Failed, Node not exist";
        return Status::CANCELLED;
    }
    return Status::OK;
}

grpc::Status
NameNodeSerImpl::AddNewFile(grpc::ServerContext *context,
                            const namenodeproto::AddNewFileRequest *request,
                            namenodeproto::SegIndexReply *response) {
    string name = request->name();
    FILE_LOG(LOG_DEBUG) << name << " normal?\n";
    long long size = request->size();
    time_t mtime = request->mtime();
    time_t atime = request->atime();
    time_t ctime = request->ctime();
    vector<SegIndex> seg_index;
    int rt = namenode.addNewFile(name, size, mtime, atime, ctime, seg_index);
    if (rt != 0) {
        return Status::CANCELLED;
    }
    int indexi = 0;
    for (SegIndex item : seg_index) {
        response->add_index();
        namenodeproto::SegIndex *index_temp = response->mutable_index(indexi++);
        index_temp->set_node(item.node);
        int indexj = 0;
        for (SegWithSize ss : item.segs) {
            index_temp->add_segs();
            namenodeproto::SegWithSize *ss_temp =
                    index_temp->mutable_segs(indexj++);
            ss_temp->set_seg(ss.seg);
            ss_temp->set_size(ss.size);
        }
    }
    return Status::OK;
}

grpc::Status
NameNodeSerImpl::ReadFromFile(grpc::ServerContext *context,
                              const namenodeproto::ReadRequest *request,
                              namenodeproto::SegIndexReply *response) {
    string name = request->name();
    vector<SegIndex> seg_index;
    int rt = namenode.readFile(name, seg_index);

    if (rt != 0) {
        return Status::CANCELLED;
    }
    int indexi = 0;
    for (SegIndex item : seg_index) {
        response->add_index();
        namenodeproto::SegIndex *index_temp = response->mutable_index(indexi++);
        index_temp->set_node(item.node);
        int indexj = 0;
        for (SegWithSize ss : item.segs) {
            index_temp->add_segs();
            namenodeproto::SegWithSize *ss_temp =
                    index_temp->mutable_segs(indexj++);
            ss_temp->set_seg(ss.seg);
            ss_temp->set_size(ss.size);
        }
    }
    return Status::OK;
}

grpc::Status
NameNodeSerImpl::DelFile(grpc::ServerContext *context,
                         const namenodeproto::FileNameRequest *request,
                         namenodeproto::IntReply *response) {
    string name = request->name();
    int result = namenode.delFile(name);
    response->set_result(result);
    if (result != 0) {
        FILE_LOG(LOG_ERROR) << "File Remove Failed" << endl;
        return Status::CANCELLED;
    }
    return Status::OK;
}

grpc::Status
NameNodeSerImpl::DelDir(grpc::ServerContext *context,
                        const namenodeproto::PrefixRequest *request,
                        namenodeproto::IntReply *response) {
    string prefix = request->prefix();
    int result = namenode.delDir(prefix);
    response->set_result(result);
    if (result != 0) {
        FILE_LOG(LOG_ERROR) << "File Remove Failed" << endl;
        return Status::CANCELLED;
    }
    return Status::OK;
}

grpc::Status
NameNodeSerImpl::GetFileSize(grpc::ServerContext *context,
                             const namenodeproto::FileNameRequest *request,
                             namenodeproto::LongReply *response) {
    string name = request->name();
    long long size = namenode.getFileSize(name);
    response->set_result(size);
    return Status::OK;
}
