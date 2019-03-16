//
// Created by anson on 19-2-24.
//

#include "fs.hpp"
//#include "INode/inodedirectory.hpp"
//#include "INode/inodefile.hpp"
//#include "INode/fileblock.hpp"
#include "DataNode/datanode.hpp"
#include "unistd.h"
#include "stdio.h"
#include "fstream"
#include "ostream"
#include "logger.hpp"

using namespace std;

time_t time1;

int fsndn::user_id = 1;
int fsndn::group_id = 2;
int fsndn::fsndn_id = 666;
string fsndn::root_path = "/tmp/fsndn";
string fsndn::global_prefix = "/ndn/fsndn/prefix";
const int fsndn::seg_size = 2048;


//INodeDirectory fsndn::root("/", time(&time1), time(&time1), time(&time1));

int main() {
        return 0;
}
