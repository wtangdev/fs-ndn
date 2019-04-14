#ifndef NAMENODE_HPP
#define NAMENODE_HPP

#include "../DataNode/datanodeclient.hpp"
#include "filemeta.hpp"
#include "namehashtable.hpp"

// 前缀和其属性
class Prefix
{
  public:
    Prefix(string prefix, bool leaf);
    ndn::Name prefix; // 前缀
    bool leaf;        // 是否是叶子前缀
    std::size_t operator()(const Prefix &p) const;
    bool operator==(const Prefix &other_prefix) const;
};

class NameNode
{
  public:
    NameNode();

    int addDataNode(string ip, int node_id);
    int removeDataNode(int node_id);

    // 为文件生成命名数据数据信息，并建立写入位置索引,然后返回写入位置索引个客户端
    int addNewFile(string name,
                   long long size,
                   time_t mtime,
                   time_t atime,
                   time_t ctime,
                   vector<SegIndex> &store_segs);
    int readFile(string name, vector<SegIndex> &seg_segs);
    int delFile(string name);
    int delDir(string name);

    int addNewFileToNode(string name,
                         const char *content,
                         long long size,
                         int node_id);

    long long getFileSize(string name);

  private:
    // 当前管理的所有的DataNode
    vector<DataNodeClient> data_nodes;
    // 所有的文件的元数据信息
    vector<FileMeta> files;
    // 用来快速查找文件数据的哈希表
    // TODO:使用自己实现的哈希表以减小内存占用
    unordered_map<string, FileMeta> name_index;

    void updateNodes();
    bool spaceEnough(long long size);
    //
    int findFile(string name, FileMeta &file_meta);

    // 下面是快速名称查找算法实现所需要的函数
    // 前缀表
    vector<Prefix> prefixs;
    // 构建 Next 和 Back 数组
    void buildArrays(vector<int> next, vector<int> back);
    // 打印目前构建的哈希表用于调试
    void printHashTable();
};

#endif // NAMENODE_HPP
