#include "NameNode/namenode.hpp"
#include "logger.hpp"
#include "iostream"
#include "fs.hpp"

using namespace std;

int main(int argc, char ** argv) {
    time_t time1;
    //    DataNodeClient client(grpc::CreateChannel(
    //                              "localhost:50051", grpc::InsecureChannelCredentials()),
    //                          1001);
    NameNode namenode;
    namenode.addDataNode("localhost:50051", 1001);
    namenode.addDataNode("localhost:50052", 1002);
    string filename = "/c1/c2.jpeg";
    cout<< "getfilesize : "<< filename<< endl;
    int reply = namenode.getFileSize(filename);
    cout<< "Client recieved: " << reply<< endl;

        ifstream fin("/Users/anson/Desktop/psb.jpeg", ios::binary | ios::in);
//    ifstream fin("/Users/anson/Desktop/jpjh.md", ios::binary | ios::in);
    if (!fin) {
        cout<< "File open failed\n";
    } else {
        //        istream::pos_type current_pos = fin.tellg();    // 记录当前位置
        long long current_pos = fin.tellg();
        fin.seekg(0, ios_base::end);    // 移动到末尾
        //        istream::pos_type file_size = fin.tellg();  // 此时的位置显然就是文件大小
        long long file_size = fin.tellg();
        fin.seekg(current_pos); //回到初始位置
        FILE_LOG(LOG_DEBUG)<< "file_size="<<file_size<< endl;
        char data[file_size];
        //        memset(data, 0, file_size);
        fin.read(reinterpret_cast<char *>(data), sizeof(char) * file_size);    // 读
        fin.close();
        //        cout<< "addNewFile /c1/new.jpeg"<< endl;
        cout<< "addNewFile /c1/newmd.md"<< endl;
        //        int reply = namenode.addNewFile("/c1/new.jpeg", data, file_size);
        int reply = namenode.addNewFile("/c1/newmd.md", data, file_size);
        cout<< "Client recieved: " << reply<< endl;
    }
    //    vector<string> children = client.showAllChildren();
    //    for (auto str : children) {
    //        cout<< str<< endl;
    //    }
    //    long long md_size = namenode.getFileSize("/c1/new.jpeg");
    long long md_size = namenode.getFileSize("/c1/newmd.md");
    char * md_content;
    try {
        md_content = new char[md_size];

        memset(md_content, 0, md_size);
        cout<< "  "<< (void*)md_content<< endl;
        namenode.readFile("/c1/newmd.md", md_content, md_size);
        cout<< "  "<< (void*)md_content<< endl;
        ofstream fout("/Users/anson/Desktop/newjpeg.jpeg", ios::binary);
//        ofstream fout("/Users/anson/Desktop/newmd.md", ios::binary);
        fout.write(md_content, md_size*sizeof(char));
        fout.flush();
        fout.close();
        delete[] md_content;
        cout<< 1<< endl;
    } catch (std::exception& e) {
        cout<< e.what()<< endl;
    }
    return 0;
}
