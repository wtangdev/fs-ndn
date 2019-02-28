cmake_minimum_required(VERSION 3.12)
project(fs-ndn)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES fs.cpp fs.hpp filestore.cpp filestore.hpp INode/inode.cpp INode/inode.hpp INode/inodedirectory.cpp INode/inodedirectory.hpp logger.hpp INode/INodeFile.cpp INode/INodeFile.hpp)

add_executable(fs ${SOURCE_FILES})

include_directories(/usr/include)
link_directories(/usr/lib)

target_link_libraries(fs jsoncpp ndn-cpp)
