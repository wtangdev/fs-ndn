#ifndef NAMENODECLIENT_H
#define NAMENODECLIENT_H

#include "../proto-src/namenode.grpc.pb.h"
#include "namenode.hpp"
#include <grpcpp/grpcpp.h>

using namespace std;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namenodeproto::NameNodeSer;

class NameNodeClient {
public:
    NameNodeClient(shared_ptr<Channel> Channel, int node_id);

    int addDataNode(const string &ip, int node_id);

    int removeDataNode(int node_id);

    int addNewFile(const string &name,
                   long long size,
                   time_t mtime,
                   time_t atime,
                   time_t ctime,
                   vector<SegIndex> & seg_index);

    int readFile(string name, vector<SegIndex> & seg_index);

    int delFile(const string &name);

    int delDir(const string &prefix);

    void updateNode(int status);

    long long getFileSize(const string &name);

    void quit();

    bool operator==(const int &other_node_id) const;

private:
    std::shared_ptr<NameNodeSer::Stub> stub_;
    int node_id;

    void printSegIndex(vector<SegIndex>);
};

#endif // NAMENODECLIENT_H
