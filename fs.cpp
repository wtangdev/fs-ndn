//
// Created by anson on 19-2-24.
//

#include "fs.hpp"
#include "INode/inodedirectory.hpp"
#include "INode/inodefile.hpp"
#include "INode/fileblock.hpp"
#include "unistd.h"
#include "stdio.h"
#include "fstream"
#include "ostream"

using namespace std;

time_t time1;

int fsndn::user_id = 1;
int fsndn::group_id = 2;
int fsndn::fsndn_id = 666;
string fsndn::root_path = "/tmp/fsndn";
string fsndn::global_prefix = "/ndn/fsndn/prefix";
const int fsndn::seg_size = 2048;


INodeDirectory fsndn::root("/", time(&time1), time(&time1), time(&time1));

int main() {
//    cout<< "Hello World!"<< endl;


//    list<INode> list1;
//    INodeDirectory iNodeDirectory1("wq", time(&time1), time(&time1), time(&time1));
//    INodeDirectory iNodeDirectory2("qw", time(&time1), time(&time1), time(&time1));
//    list1.push_back(iNodeDirectory1);
//    list1.push_back(iNodeDirectory2);
//    for (auto i : list1) {
//        cout<< i.getName()<<" "<< i.getMtime()<< endl;
//    }
//    sleep(1);
//    INodeDirectory newChild("wq", time(&time1+1), time(&time1), time(&time1));
//    list<INode>::iterator it = find(list1.begin(), list1.end(), newChild.getName());
//    replace(list1.begin(), list1.end(), *it,(INode) newChild);
//    for (auto i : list1) {
//        cout<< i.getName()<<" "<< i.getAtime()<< endl;
//    }
//    cout<< it->getName()<< "  "<< newChild.getName();

//    string prefix, last;
//    split_last_component("/c1/c2/c3", prefix, last);
//    cout<< prefix<<"  " << last<< endl;
//    vector<string> vector1;
//    split_all_component("/c1/c2/c3", vector1);
//    for (auto item : vector1) {
//        cout<< item<< endl;
//    }

//    INodeDirectory iNodeDirectory("/", time(&time1), time(&time1), time(&time1));
//    INodeDirectory iNodeDirectory1("c1", time(&time1), time(&time1), time(&time1));
//    INodeDirectory iNodeDirectory2("c2", time(&time1), time(&time1), time(&time1));
//    INode iNode("i1", time(&time1), time(&time1), time(&time1));
//    iNodeDirectory1.addChild(& iNodeDirectory2);
//    iNodeDirectory.addChild(& iNodeDirectory1);
//
//
////    iNodeDirectory.addChild(iNode);
////    iNodeDirectory.removeChild()
////    INode ** node;
//    INode * node;
////    iNodeDirectory.removeChild(& iNodeDirectory1);
//    node = iNodeDirectory.getNodeLink("/c1");
////    cout<< node[0]->getName()<< "  "<< node[2]->getName()<<  endl;
//    cout<< node->getName()<< endl;


//    INodeDirectory iNodeDirectory("/c1/c2/c3", time(&time1), time(&time1), time(&time1));
//    INodeDirectory iNodeDirectory1("/c1/c2/c3/c4", time(&time1), time(&time1), time(&time1));
//    cout<< iNodeDirectory.getNdnName().getPrefix(-1)<< endl;
//    cout<< iNodeDirectory.getNdnName().match(iNodeDirectory1.getNdnName());

//    fsndn::root;
//    inodefile iNodeFile("/c1/c2/file.txt", time(&time1), time(&time1), time(&time1));
//    cout<< fsndn::root.getNdnName()<< endl;
//    cout<< iNodeFile.getPath()<<" "<< iNodeFile.getNdnName()<< " "<< iNodeFile.getName() <<endl;
//    cout<< iNodeFile.getNdnPath()<< endl;
//    FILE * file = fopen(iNodeFile.getPath().c_str(), "r");
////    fsndn::root.showChildrenLink();
//    for (auto item : fsndn::root.getChildren()) {
//         INodeDirectory * temp = (INodeDirectory *) item;
//         cout<< item->getName()<< " ";
//        for (auto item1 : temp->getChildren()) {
//            INodeDirectory * temp1 = (INodeDirectory *) item1;
//            cout<< item1->getName()<< " ";
//         for (auto item2 : temp1->getChildren()) {
//             INodeDirectory *temp2 = (INodeDirectory *) item2;
//             cout << item2->getName() << " ";
//         }
//        }
//    }
//    cout<< fsndn::root.getName()<< endl;
//    if(file) {
//        fseek(file, 0, SEEK_END);
//        cout<< ftell(file)<< endl;
//        int len = ftell(file);
//        rewind(file);
//        char buffer[len];
//        fread(buffer, 1, len, file);
//        buffer[len] = '\0';
//        cout<< buffer<< endl;
//    }
//    ifstream fin("/Users/anson/Desktop/jpjh.md", ios::binary);
//    if (!fin) {
//        cout<< "File open failed\n";
//    } else {
//        istream::pos_type current_pos = fin.tellg();    // 记录当前位置
//        fin.seekg(0, ios_base::end);    // 移动到末尾
//        istream::pos_type file_size = fin.tellg();  // 此时的位置显然就是文件大小
//        fin.seekg(current_pos); //回到初始位置
//        unsigned char * data = new unsigned char(file_size);
//        memset(data, 0, file_size);
//        fin.read(reinterpret_cast<char*>(data), sizeof(unsigned char)*file_size);    // 读
//        cout<< data<< endl;
//        fin.seekg(8);
//        int size1 = file_size;
//        size1 -= 8;
//        memset(data, 0, file_size);
//        fin.read(reinterpret_cast<char*>(data), sizeof(unsigned char)*(size1));    // 读
//        cout<< endl;
//        cout<< data<< endl;
//        ofstream fout("/Users/anson/Desktop/newnewpsb.jpeg", ios::binary);    // 如果该文件实现不存在的话会新建，存在则会覆盖
//        fout.write(reinterpret_cast<char*>(data), sizeof(unsigned char)*file_size);  // 写
        // 下面是二进制数据拷贝
//        unsigned char * newdata = new unsigned char(file_size);
//        memmove(newdata, data, file_size);
//        delete data;
//        ofstream fout2("/Users/anson/Desktop/newnew2psb.jpeg", ios::binary);
//        fout2.write(reinterpret_cast<char*>(newdata), sizeof(unsigned char)*file_size);
//        fout2.close();
//        fout.close();
//    }
//    fin.close();

// 测试 fileblock
     ifstream fin("/Users/anson/Desktop/jpjh8k.md", ios::binary | ios::in);
    if (!fin) {
        cout<< "File open failed\n";
    } else {
//        istream::pos_type current_pos = fin.tellg();    // 记录当前位置
        int current_pos = fin.tellg();
        fin.seekg(0, ios_base::end);    // 移动到末尾
//        istream::pos_type file_size = fin.tellg();  // 此时的位置显然就是文件大小
        int file_size = fin.tellg();
        fin.seekg(current_pos); //回到初始位置
        FILE_LOG(LOG_DEBUG)<< "file_size="<<file_size<< endl;
        unsigned char data[file_size];
//        memset(data, 0, file_size);
        fin.read(reinterpret_cast<char *>(data), sizeof(unsigned char) * file_size);    // 读
        fin.close();
        INodeFile iNodeFile("/ndn/c1/c2/data1", time(&time1), time(&time1), time(&time1));
        iNodeFile.write(data, file_size);
        unsigned char content[iNodeFile.getSize()];
        iNodeFile.read(content, iNodeFile.getSize());
        FILE_LOG(LOG_DEBUG)<< content<< endl;
    }
    return 0;
}