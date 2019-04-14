#include "Client/client.h"
#include "NameNode/namenode.hpp"
#include "fs.hpp"
#include "iostream"
#include "logger.hpp"
#include "unistd.h"

using namespace std;

const int fsndn::seg_size = 1048576; //

int
  main(int argc, char **argv)
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
    cout << "HelloWorld!\n";

    string file_path = "/home/anson/Desktop/USTC.jpg";
    string pict_path = "/home/anson/Desktop/pict.jpg";
    string word_path = "/home/anson/Desktop/names_copy.txt";
    int ret = 0;
    // 步骤1：发起命名数据写请求
    /*
    client.addNewFile("/c1/c2/c3/c4/c5/USTC.jpeg",
                                file_path,
                                time(&time1),
                                time(&time1),
                                time(&time1));
    client.addNewFile("/c1/c2/c3/c4/c6/c5/USTC.jpeg",
                      file_path,
                      time(&time1),
                      time(&time1),
                      time(&time1));
    */
    ret = client.addNewFile(
      "/a/b/c", word_path, time(&time1), time(&time1), time(&time1));
    /*
    client.addNewFile("/a/b/c/d/e/f/g/USTC.jpeg",
                      pict_path,
                      time(&time1),
                      time(&time1),
                      time(&time1));
    string name_path = "/home/anson/Desktop/names.txt";
    ifstream fin(name_path, ios::binary | ios::in);
    const char *str = "NEW STR";
    for (int i = 0; i < 16; i++) {
        string name = "/";
        string name1;
        fin >> name1;
        name += name1;
        client.addNewFile(
          name, word_path, time(&time1), time(&time1), time(&time1));
    }

    fin.close();

    */
    if (ret != -1) {
        // 步骤1：发起命名数据读请求
        client.readFile("/c1/c2/c3/c4/c5/USTC.jpeg",
                        "/home/anson/Desktop/newUSTC.jpg");
        string test = "/a/b/c";
        string test1 =
          "/linkinghub.elsevier.com/retrieve/pii/S1050464810002901";
        string test2 = "/openurl.ingenta.com/content/"
                       "xref?genreequalsarticle&issnequals1357-1559&"
                       "volumeequals16&issueequals1&spageequals24";
        cout << client.readFile(test, "/home/anson/Desktop/test.txt") << endl;
        //        cout << client.readFile(test1,
        //        "/home/anson/Desktop/test1.txt") << endl; cout <<
        //        client.readFile(test2, "/home/anson/Desktop/test2.txt") <<
        //        endl;
    }
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
