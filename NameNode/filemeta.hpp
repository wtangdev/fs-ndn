#ifndef FILEMETA_HPP
#define FILEMETA_HPP

#include "ndn-cpp/name.hpp"
#include "set"
#include "vector"

using namespace std;

// 每一段的文件的大小
struct SegWithSize
{
    int seg;
    int size;
};

// DataNode 里面存储的段
struct SegIndex
{
    int node;
    vector<SegWithSize> segs;
    bool operator==(const int &other_seg) const { return node == other_seg; }
};

// 文件元数据
class FileMeta
{
  public:
    FileMeta();
    FileMeta(string name,
             int segs,
             long long size,
             time_t mtime,
             time_t atime,
             time_t ctime);
    ndn::Name getName();
    int getSegs();
    long long getSize();
    int getReadTimes();
    vector<SegIndex> getUseNodes();

    int setSegs(int segs);
    int addReadTimes();
    int addUseNodes(int node, int seg, int size);
    int minusReadTimes();
    int minusUseNodes(int node);

    bool operator==(const string &other_file_name) const;

  private:
    ndn::Name name;
    vector<SegIndex> use_nodes;
    int segs;
    long long size;
    int read_times;
    time_t mtime;
    time_t atime;
    time_t ctime;
};

#endif // FILEMETA_HPP
