//
// Created by anson on 19-2-24.
//

#include "fs.hpp"
#include "INode/inodedirectory.hpp"
#include "INode/INodeFile.hpp"
#include "unistd.h"
#include "stdio.h"

using namespace std;

time_t time1;

int fsndn::user_id = 0;
int fsndn::group_id = 0;
INodeDirectory fsndn::root("/", time(&time1), time(&time1), time(&time1));
string fsndn::root_path = "/tmp/fsndn";

int main() {
    cout<< "Hello World!"<< endl;


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

    INodeFile iNodeFile("/c1/c2/file.txt", time(&time1), time(&time1), time(&time1));
    cout<< iNodeFile.getPath()<<" "<< iNodeFile.getNdnName()<< " "<< iNodeFile.getName() <<endl;
    FILE * file = fopen(iNodeFile.getPath().c_str(), "r");
    if(file) {
        fseek(file, 0, SEEK_END);
        cout<< ftell(file)<< endl;
        int len = ftell(file);
        rewind(file);
        char buffer[len];
        fread(buffer, 1, len, file);
        buffer[len] = '\0';
        cout<< buffer<< endl;
    }
    return 0;
}