#include "Client/client.h"
#include "NameNode/namenode.hpp"
#include "fs.hpp"
#include "iostream"
#include "logger.hpp"
#include "unistd.h"

using namespace std;

const int fsndn::seg_size = 1048576; //

int
main(int argc, char **argv) {
    time_t time1;
    //    DataNodeClient client(grpc::CreateChannel(
    //                              "localhost:50051",
    //                              grpc::InsecureChannelCredentials()),
    //                          1001);
    //    NameNode namenode;
    //    namenode.addDataNode("localhost:50051", 1001);
    //    namenode.addDataNode("localhost:50052", 1002);
    Client client;
    client.addNameNode("hadoop-master:50005", 2001);
    client.addDataNode("hadoop-slave1:50051", 1001);
    client.addDataNode("hadoop-slave2:50052", 1002);
    cout << "HelloWorld!\n";

    // 步骤1：发起命名数据写请求
    string ustc_path = "/home/anson/Desktop/USTC.jpg";
    string name_path = "/home/anson/Desktop/names.txt";
    string word_path = "/home/anson/Desktop/test.txt";
    string iso_path = "/home/anson/Desktop/ubuntu.iso";

    string ustc_name = "/a/b/c/USTC.jpg";
    string iso_name = "/a/b/c/ubuntu.iso";

//    client.addNewFile(ustc_name, ustc_path, time(&time1), time(&time1), time(&time1));
//    client.addNewFile(iso_name, iso_path,  time(&time1), time(&time1), time(&time1));

//    client.readFile(ustc_name, ustc_path+"_test.jpg");
    ifstream fin(name_path, ios::binary | ios::in);
    for (int i = 0; i < 100; i++) {
        string name = "/";
        string name1;
        fin >> name1;
        name += name1;
        client.addNewFile(
                name, word_path, time(&time1), time(&time1), time(&time1));
    }
    fin.close();

    // 步骤1：发起命名数据读请求

    /*
//    ifstream fin("/home/anson/Desktop/ustc.jpg", ios::binary | ios::in);
    ifstream fin("/home/anson/Desktop/manjaro.iso", ios::binary | ios::in);
    //    ifstream fin("/Users/anson/Desktop/jpjh原.md", ios::binary | ios::in);
    if (!fin) {
        cout << "File open failed\n";
    } else {
        // 记录当前位置
        long long current_pos = fin.tellg();
        fin.seekg(0, ios_base::end); // 移动到末尾
        //        istream::pos_type file_size = fin.tellg();  //
        // 此时的位置显然就是文件大小
        long long file_size = fin.tellg();
        fin.seekg(current_pos); // 回到初始位置
        FILE_LOG(LOG_DEBUG) << "file_size=" << file_size << endl;
        char* data = new char[file_size];
        fin.read(data, file_size);
        fin.close();
        client.addNewFile(
          "/c1/c2", data, file_size, time(&time1), time(&time1), time(&time1));
        char* buffer = new char[file_size];
        client.readFile("/c1/c2", buffer, file_size);
        ofstream fout("/home/anson/Desktop/newmanjaro.iso", ios::binary);
        fout.write(buffer, file_size);
        fout.close();
    }

     */

    return 0;
}
