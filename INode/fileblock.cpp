//
// Created by Anson on 2019-03-09.
//

#include "fileblock.hpp"
#include "../fs.hpp"
#include "../logger.hpp"

// 初始化空闲文件表
vector<SFileTable> FileBlock::space_path;

FileBlock::FileBlock(string name, const char *data, int size, int seg) {
    this->name = name;
    this->size = size;
    this->seg = seg;
    this->offset = 0;
    // 拷贝数据到Block
    this->write(data, size);
}

FileBlock::FileBlock(FileBlock *other) {
    this->size = other->size;
    this->seg = other->seg;
    this->path = other->path;
}

int FileBlock::write(const char *content, int size) {
    bool need_new_file = true;
    int offset = 0;
    // 判断size是否需要新建一个fsndn文件来存储
    if (size < fsndn::seg_size) {
        // 不需要就在空闲文件表中查找最小的合适的空闲文件，
        // TODO: 此处如果用二分查找是会加快还是减慢
        vector<SFileTable> space_set = this->getSpaceTable();
        for (vector<SFileTable>::iterator i = space_set.begin(); i != space_set.end(); i++) {
            if ((*i).getSpace() >= size) {
                // 只有当size与分段的段小并且找到了合适的空文件，才不用新建文件。
                need_new_file = false;
                this->path = (*i).getPath();
                offset = (*i).getOffset();
                break;
            }
        }
    }
    if (need_new_file) {
        // 需要就使用使用节点id与时间戳的组合生成文件唯一id 形如6661552126250.fsndn
//        int fsndnid = fsndn::fsndn_id;
//        time_t time1;
//        int time_stamp = time(&time1);
//        stringstream pathstream1;
//        stringstream pathstream2;
//        pathstream1 << fsndnid;
//        pathstream2 << time_stamp;
        stringstream pathstream;
        pathstream<< "_seg"<< this->seg;
        string root_path = fsndn::root_path;
        string name_path;
        name2path(this->name, name_path);
        this->path = root_path.append(name_path.append(pathstream.str()).append(".fsndn"));
        // 新建文件
        FILE_LOG(LOG_DEBUG)<< "Write: "<< this->path<< endl;
        ofstream creat_file(this->path);
        FILE_LOG(LOG_DEBUG)<< "write : create new file is ok"<< endl;
        creat_file.close();
        // 判断新建的文件是否有剩余空间，有的话则插入空闲文件表
        if (size < fsndn::seg_size) {
            SFileTable newsfiletable(this->path, size+1);
            FileBlock::space_path.push_back(newsfiletable);
        }
    }
    // 注意！ofstream默认打开时就会清空文件内容！所以要使用ios::in
    if (!need_new_file) {
        // 如果写的是查找出来的空闲文件，那么该文件需要被更新
        FileBlock::updateSpaceTable(this->path, size);
    }
    ofstream fout(this->path, ios::binary | ios::in | ios::out);    // 如果该文件实现不存在的话会新建，存在则会覆盖
    // 移动偏移量,如果是新建的文件，偏移量就会是0
    fout.seekp(offset);
    this->offset = offset;
    FILE_LOG(LOG_DEBUG)<< this->path<<"  "<< offset<< endl;
    fout.write(content, sizeof(char) * size);
    fout.close();
    return 0;
}

int FileBlock::read(char *buffer, int size) {
    ifstream fin(this->path, ios::binary);
    if (!fin) {
        FILE_LOG(LOG_DEBUG) << "FileBlock read :File open failed\n";
    } else {
        istream::pos_type current_pos = fin.tellg();    // 记录当前位置
        fin.seekg(0, ios_base::end);    // 移动到末尾
        istream::pos_type file_size = fin.tellg();  // 此时的位置显然就是文件大小
//        fin.seekg(current_pos); //回到初始位置
        fin.seekg(this->offset);
//        char *data = new char(size);
//        memset(data, 0, size);
        fin.read(buffer, sizeof(char) * size);    // 读
        fin.close();
//        cout<< this->path<< " "<< size<<" "<< file_size<< " "<< this->offset<< endl<< buffer<< endl;
    }
    return 0;
}

bool FileBlock::operator<(const FileBlock &otherfile) const {
    return this->seg < otherfile.seg;
}

vector<SFileTable> FileBlock::getSpaceTable() {
    return FileBlock::space_path;
}

void FileBlock::updateSpaceTable(string path, int size) {
    for (vector<SFileTable>::iterator i = FileBlock::space_path.begin(); i != FileBlock::space_path.end(); i++) {
        if ((*i).getPath() == path) {
            (*i).setOffset((*i).getOffset() + size + 1);
            cout<< "   "<< (*i).getSpace()<< endl;
            if ((*i).getSpace() <= 0) {
                // 没有空闲空间了就删掉
                FileBlock::space_path.erase(i);
            }
            break;
        }
    }
    // 重新排序
    sort(FileBlock::space_path.begin(), FileBlock::space_path.end());
}

int FileBlock::getSeg() {
    return this->seg;
}

int FileBlock::getSize() {
    return this->size;
}

SFileTable::SFileTable(string pathstr, int offset) {
    this->path = pathstr;
    this->offset = offset;
    this->space = fsndn::seg_size - this->offset;
}

string SFileTable::getPath() {
    return this->path;
}

int SFileTable::getSpace() {
    return this->space;
}

void SFileTable::setOffset(int ofs) {
    this->offset = ofs;
    this->space = fsndn::seg_size - ofs;
}

int SFileTable::getOffset() {
    return this->offset;
}

bool SFileTable::operator<(const SFileTable &otherfile) const {
    return this->space < otherfile.space;
};

bool SFileTable::operator==(const SFileTable &otherfile) const {
    return this->path == otherfile.path;
}
