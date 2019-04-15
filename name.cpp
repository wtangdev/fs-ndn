#include "NameNode/namenodeserver.hpp"
#include "fs.hpp"
#include "iostream"
#include "logger.hpp"

using namespace std;

const int fsndn::seg_size = 1048576; //

int
main()
{
    cout << "Start NameNode" << endl;
    Log<Output2FILE>::reportingLevel() = LOG_DEBUG;
    Output2FILE::stream() = stdout;
    NameNodeSerImpl service;
    string server_address("hadoop-master:50005");
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
