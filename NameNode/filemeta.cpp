#include "filemeta.hpp"
#include "../logger.hpp"
#include "iostream"
using namespace std;

FileMeta::FileMeta() {}

FileMeta::FileMeta(string name,
                   int segs,
                   long long size,
                   time_t mtime,
                   time_t atime,
                   time_t ctime)
{
    this->name = ndn::Name(name);
    this->segs = segs;
    this->size = size;
    this->read_times = 0;
    this->mtime = mtime;
    this->atime = atime;
    this->ctime = ctime;
}

ndn::Name
  FileMeta::getName()
{
    return this->name;
}

int
  FileMeta::getSegs()
{
    return this->segs;
}

long long
  FileMeta::getSize()
{
    return this->size;
}

int
  FileMeta::getReadTimes()
{
    return read_times;
}

vector<SegIndex>
  FileMeta::getUseNodes()
{
    return this->use_nodes;
}

int
  FileMeta::setSegs(int segs)
{
    this->segs = segs;
    return 0;
}

int
  FileMeta::addReadTimes()
{
    this->read_times++;
    return 0;
}

int
  FileMeta::addUseNodes(int node, int seg, int size)
{
    vector<SegIndex>::iterator it;
    for (it = this->use_nodes.begin(); it != this->use_nodes.end(); it++) {
        if ((*it).node == node) {
            break;
        }
    }
    if (it == this->use_nodes.end()) {
        SegIndex ss;
        ss.node = node;
        SegWithSize segsize;
        segsize.seg = seg;
        segsize.size = size;
        ss.segs.push_back(segsize);
        this->use_nodes.push_back(ss);
    } else {
        SegWithSize segsize;
        segsize.seg = seg;
        segsize.size = size;
        (*it).segs.push_back(segsize);
    }
    return 0;
}

int
  FileMeta::minusReadTimes()
{
    this->read_times--;
    return 0;
}

int
  FileMeta::minusUseNodes(int node)
{
    vector<SegIndex>::iterator it;
    for (it = this->use_nodes.begin(); it != this->use_nodes.end(); it++) {
        if ((*it).node == node) {
            break;
        }
    }
    if (it == use_nodes.end()) {
        FILE_LOG(LOG_ERROR) << "Minus Use Nodes error, " << this->name.toUri()
                            << " has no segment in node " << node << endl;
        return -1;
    }
    this->use_nodes.erase(it);
    return 0;
}

bool
  FileMeta::operator==(const string &other_file_name) const
{
    return this->name.toUri() == other_file_name;
}
