#ifndef NAMEHASHTABLE_HPP
#define NAMEHASHTABLE_HPP
#include "../fs.hpp"
#include "vector"

// 小的哈希表的完美哈希表
class PerfectHashTable
{
  public:
    PerfectHashTable();
    // BKDR Hash Function
    unsigned int BKDRHash(char *str);

  private:
    std::vector<int> data;
};

// 管理所有小的哈希表的基础哈希表
class BasicHashTable
{
  public:
    BasicHashTable();
};

#endif // NAMEHASHTABLE_HPP
