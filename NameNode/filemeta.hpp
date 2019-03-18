#ifndef FILEMETA_HPP
#define FILEMETA_HPP

#include "ndn-cpp/name.hpp"
#include "set"

using namespace std;

class FileMeta {
public:
    FileMeta(string name, int segs, int size);
    ndn::Name getName();
    int getSegs();
    long long getSize();
    int getReadTimes();
    set<int> getUseNodes();

    int setSegs(int segs);
    int addReadTimes();
    int addUseNodes(int node);
    int minusReadTimes();
    int minusUseNodes(int node);

    bool operator ==(const string & other_file_name) const;
private:
    ndn::Name name;
    set<int> use_nodes;
    int segs;
    long long size;
    int read_times;
};



#endif // FILEMETA_HPP
