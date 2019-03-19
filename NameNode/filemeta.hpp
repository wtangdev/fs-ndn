#ifndef FILEMETA_HPP
#define FILEMETA_HPP

#include "ndn-cpp/name.hpp"
#include "set"
#include "vector"

using namespace std;

struct SegSize
    {
        int seg;
        int size;
    };

struct StoreSeg {
    int node;
    vector<SegSize> segs;
    bool operator ==(const int & other_seg) const {
        return node == other_seg;
    }
};

class FileMeta {
public:
    FileMeta(string name, int segs, int size);
    ndn::Name getName();
    int getSegs();
    long long getSize();
    int getReadTimes();
    vector<StoreSeg> getUseNodes();

    int setSegs(int segs);
    int addReadTimes();
    int addUseNodes(int node, int seg, int size);
    int minusReadTimes();
    int minusUseNodes(int node);

    bool operator ==(const string & other_file_name) const;
private:
    ndn::Name name;
    vector<StoreSeg> use_nodes;
    int segs;
    long long size;
    int read_times;
};



#endif // FILEMETA_HPP
