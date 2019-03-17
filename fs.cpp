//
// Created by anson on 19-2-24.
//

#include "fs.hpp"
#include "DataNode/datanode.hpp"
#include "unistd.h"
#include "stdio.h"
#include "fstream"
#include "ostream"
#include "logger.hpp"

using namespace std;

time_t time1;

int fsndn::user_id ;
int fsndn::group_id;
int fsndn::fsndn_id = 666;
string fsndn::root_path = "/tmp/fsndn";
string fsndn::global_prefix = "/ndn/fsndn/prefix";
const int fsndn::seg_size = 2048;



int main() {
    cout<< "FS-NDN: version 0.1"<< endl;
    fsndn::user_id = getuid();
    fsndn::group_id = getgid();
    cout<< "FS-NDN: prefix " << fsndn::global_prefix<< endl;
    cout<< "FS-NDN: root path "<< fsndn::root_path<< endl;
    Log<Output2FILE>::reportingLevel() = LOG_DEBUG;
    Output2FILE::stream() = stdout;
    DataNode datanode;


    return 0;
}
