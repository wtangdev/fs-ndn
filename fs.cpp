//
// Created by anson on 19-2-24.
//

#include "fs.hpp"
#include "DataNode/datanode.hpp"
#include "DataNode/datanodeserver.hpp"
#include "unistd.h"
#include "stdio.h"
#include "fstream"
#include "ostream"
#include "logger.hpp"
#include "libconfig.h++"

using namespace std;
using namespace libconfig;

time_t time1;

int fsndn::user_id ;
int fsndn::group_id;
int fsndn::fsndn_id = 666;
string fsndn::root_path;
string fsndn::global_prefix;
int fsndn::seg_size = seg_size;

int main() {
    cout<< "FS-NDN: version 0.1"<< endl;
    fsndn::user_id = getuid();
    fsndn::group_id = getgid();
    Config cfg;
    cfg.readFile("./fsndn.conf");
    string addr = cfg.lookup("server.addr");
    cfg.lookupValue("server.root_path", fsndn::root_path);
    cfg.lookupValue("server.global_prefix", fsndn::global_prefix);
    cfg.lookupValue("server.seg_size", fsndn::seg_size);

    cout<< "FS-NDN: prefix " << fsndn::global_prefix<< endl;
    cout<< "FS-NDN: root path "<< fsndn::root_path<< endl;
    Log<Output2FILE>::reportingLevel() = LOG_DEBUG;
    Output2FILE::stream() = stdout;

    DataNodeSerImpl service(1024*1024*1024);
    string server_address(addr);
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();

    return 0;
}
