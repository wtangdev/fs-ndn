#include "Client/client.h"
#include "NameNode/namenode.hpp"
#include "fs.hpp"
#include "iostream"
#include "logger.hpp"

using namespace std;

int
main(int argc, char** argv)
{
    time_t time1;
    //    DataNodeClient client(grpc::CreateChannel(
    //                              "localhost:50051",
    //                              grpc::InsecureChannelCredentials()),
    //                          1001);
    //    NameNode namenode;
    //    namenode.addDataNode("localhost:50051", 1001);
    //    namenode.addDataNode("localhost:50052", 1002);
    Client client;
    client.addNameNode("127.0.0.1:50005", 2001);
    client.addDataNode("localhost:50051", 1001);
    client.addDataNode("localhost:50052", 1002);
    cout << "HelloWorld!";
    ifstream fin("/Users/anson/Desktop/psb.jpeg", ios::binary | ios::in);
    //    ifstream fin("/Users/anson/Desktop/jpjh原.md", ios::binary | ios::in);
    if (!fin) {
        cout << "File open failed\n";
    } else {
        //            记录当前位置
        long long current_pos = fin.tellg();
        fin.seekg(0, ios_base::end); // 移动到末尾
        //        istream::pos_type file_size = fin.tellg();  //
        //此时的位置显然就是文件大小
        long long file_size = fin.tellg();
        fin.seekg(current_pos); //回到初始位置
        FILE_LOG(LOG_DEBUG) << "file_size=" << file_size << endl;
        char* data = new char[file_size];
        fin.read(data, file_size);
        fin.close();
        client.addNewFile(
          "/c1/c2", data, file_size, time(&time1), time(&time1), time(&time1));
        char* buffer = new char[file_size];
        client.readFile("/c1/c2", buffer, file_size);
        ofstream fout("/Users/anson/Desktop/new.jpeg", ios::binary);
        fout.write(buffer, file_size);
        fout.close();
    }
    return 0;
}
