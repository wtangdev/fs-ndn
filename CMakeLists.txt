project(fsndn)
cmake_minimum_required(VERSION 3.2)

add_compile_options(-std=c++11)

# GRPC and Protocol Buffers libraries location
list(APPEND CMAKE_PREFIX_PATH "/Users/anson/Documents/Lib/grpc" "/Users/anson/Documents/Lib/grp/third_party/cprotobuf")

# Cmake find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)

set(PROTOS
    ${CMAKE_CURRENT_SOURCE_DIR}/protos/fsndn.proto
)

set(PROTO_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto-src)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})
include_directories(${PROTO_SRC_DIR})

# for fsndn
set(DATANODE_SERVER_FILES datanode_server.cpp fs.hpp INode/inode.cpp INode/inode.hpp INode/inodedirectory.cpp INode/inodedirectory.hpp logger.hpp INode/inodefile.cpp INode/inodefile.hpp DataNode/datanode.cpp DataNode/datanode.hpp INode/fileblock.cpp INode/fileblock.hpp )
set(DATANODE_CLIENT_FILES datanode_client.cpp fs.hpp INode/inode.cpp INode/inode.hpp INode/inodedirectory.cpp INode/inodedirectory.hpp logger.hpp INode/inodefile.cpp INode/inodefile.hpp DataNode/datanode.cpp DataNode/datanode.hpp INode/fileblock.cpp INode/fileblock.hpp )
# add_executable(fs ${SOURCE_FILES})

include_directories(/usr/local/include)
# Remember DO NOT USE LINK_DIRECTORIES! JUST USE find_library
find_library(NDN_LIBRARY ndn-cpp /usr/local/lib)


protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTOS})

# Building server
add_executable(datanode_server
    ${CMAKE_CURRENT_SOURCE_DIR}/datanode_server.cpp
    ${PROTO_SRCS}
    ${GRPC_SRCS}
    ${DATANODE_SERVER_FILES}
)
target_link_libraries(datanode_server
    gRPC::grpc++_reflection
    protobuf::libprotobuf
    ${NDN_LIBRARY}
)

# Building client
add_executable(datanode_client
    ${CMAKE_CURRENT_SOURCE_DIR}/datanode_client.cpp
    ${PROTO_SRCS}
    ${GRPC_SRCS}
    ${DATANODE_CLIENT_FILES}
)
target_link_libraries(datanode_client
    gRPC::grpc++_reflection
    protobuf::libprotobuf
    ${NDN_LIBRARY}
)

# Building test

# target_link_libraries(fs PUBLIC ${NDN_LIBRARY})
#target_link_libraries(test PUBLIC ${NDN_LIBRARY})
