//
// Created by anson on 19-2-24.
//
//

#ifndef FS_NDN_FS_HPP
#define FS_NDN_FS_HPP

#include "iostream"
#include "bits/stdc++.h"
#include <ndn-cpp/security/key-chain.hpp>
#include <ndn-cpp/security/identity/memory-identity-storage.hpp>
#include <ndn-cpp/security/identity/memory-private-key-storage.hpp>
#include <ndn-cpp/security/policy/no-verify-policy-manager.hpp>
#include <ndn-cpp/name.hpp>
#include "logger.hpp"
#include "INode/inodedirectory.hpp"

namespace fsndn {
    extern int user_id;
    extern int group_id;

    extern ndn::Name certificateName;
    extern ndn::ptr_lib::shared_ptr<ndn::KeyChain> keyChain;
    extern std::string global_prefix;
    extern std::string root_path;
    extern std::string logging_path;

    extern const int version_type;
    extern const int segment_type;
    extern const int seg_size;
    extern const int seg_size_shift;
    extern const int default_files_per_directory;

    // 根节点
    extern INodeDirectory root;

}

inline int split_last_component(const std::string &path, std::string &prefix, std::string &name)
{
    size_t last_comp_pos = path.rfind('/');
    if (last_comp_pos == std::string::npos)
        return -1;

    prefix = path.substr(0, last_comp_pos);
    if (prefix.empty())
        prefix = "/";
    name = path.substr(last_comp_pos + 1);

    return 0;
}

inline int split_all_component(const std::string &path, std::vector<std::string> & components) {
    std::string pathcopy = path;
    components.push_back("/");
    size_t first_comp_pos = pathcopy.find('/');
    while(first_comp_pos != std::string::npos) {
        if (first_comp_pos != 0)
            components.push_back(pathcopy.substr(0, first_comp_pos));
        pathcopy = pathcopy.substr(first_comp_pos+1);
        first_comp_pos = pathcopy.find('/');
    }
    components.push_back(pathcopy.substr(0, first_comp_pos));

    return 1;
}

#endif //FS_NDN_FS_HPP
