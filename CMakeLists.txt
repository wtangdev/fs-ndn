project(fsndn)
cmake_minimum_required(VERSION 3.2)

add_compile_options(-std=c++11)


# GRPC and Protocol Buffers libraries location
list(APPEND CMAKE_PREFIX_PATH "/home/anson/Documents/Lib/grpc" "/home/anson/Documents/Lib/grp/third_party/cprotobuf")

# Cmake find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)

set(PROTOS
    ${CMAKE_CURRENT_SOURCE_DIR}/protos/fsndn.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/protos/namenode.proto
)

set(PROTO_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/proto-src)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})
include_directories(${PROTO_SRC_DIR})

# for fsndn
set(FS_FILES fs.cpp DataNode/datanodeserver.cpp DataNode/datanodeserver.hpp fs.hpp INode/inode.cpp INode/inode.hpp INode/inodedirectory.cpp INode/inodedirectory.hpp logger.hpp INode/inodefile.cpp INode/inodefile.hpp DataNode/datanode.cpp DataNode/datanode.hpp INode/fileblock.cpp INode/fileblock.hpp )
set(NAMENODE_TEST_FILES namenode_test.cpp Client/client.h Client/client.cpp NameNode/namenodeserver.hpp NameNode/namenodeserver.cpp NameNode/namenodeclient.hpp NameNode/namenodeclient.cpp DataNode/datanodeserver.cpp DataNode/datanodeserver.hpp NameNode/namenode.hpp NameNode/namenode.cpp NameNode/filemeta.hpp NameNode/filemeta.cpp DataNode/datanodeclient.cpp fs.hpp INode/inode.cpp INode/inode.hpp INode/inodedirectory.cpp INode/inodedirectory.hpp logger.hpp INode/inodefile.cpp INode/inodefile.hpp DataNode/datanode.cpp DataNode/datanode.hpp INode/fileblock.cpp INode/fileblock.hpp )
set(NAME_FILES name.cpp Client/client.h Client/client.cpp NameNode/namenodeserver.hpp NameNode/namenodeserver.cpp NameNode/namenodeclient.hpp NameNode/namenodeclient.cpp DataNode/datanodeserver.cpp DataNode/datanodeserver.hpp NameNode/namenode.hpp NameNode/namenode.cpp NameNode/filemeta.hpp NameNode/filemeta.cpp DataNode/datanodeclient.cpp fs.hpp INode/inode.cpp INode/inode.hpp INode/inodedirectory.cpp INode/inodedirectory.hpp logger.hpp INode/inodefile.cpp INode/inodefile.hpp DataNode/datanode.cpp DataNode/datanode.hpp INode/fileblock.cpp INode/fileblock.hpp )
# add_executable(fs ${SOURCE_FILES})

include_directories(/usr/local/include)
# Remember DO NOT USE LINK_DIRECTORIES! JUST USE find_library
find_library(NDN_LIBRARY ndn-cpp /usr/local/lib)

# for libconfig
FIND_PATH(CONFIG++_INCLUDE_DIR libconfig.h++ /usr/include /usr/local/include)

FIND_LIBRARY(CONFIG++_LIBRARY NAMES config++ PATH /usr/lib /usr/local/lib)

IF (CONFIG++_INCLUDE_DIR AND CONFIG++_LIBRARY)
    SET(CONFIG++_FOUND TRUE)
ENDIF ( CONFIG++_INCLUDE_DIR AND CONFIG++_LIBRARY)

IF (CONFIG++_FOUND)
    IF (NOT CONFIG++_FIND_QUIETLY)
        MESSAGE(STATUS "Found Config++: ${CONFIG++_LIBRARY}")
    ENDIF (NOT  CONFIG++_FIND_QUIETLY)
ELSE(CONFIG++_FOUND)
    IF (Config++_FIND_REQUIRED)
        IF(NOT CONFIG++_INCLUDE_DIR)
            MESSAGE(FATAL_ERROR "Could not find LibConfig++ header file!")
        ENDIF(NOT CONFIG++_INCLUDE_DIR)

        IF(NOT CONFIG++_LIBRARY)
            MESSAGE(FATAL_ERROR "Could not find LibConfig++ library file!")
        ENDIF(NOT CONFIG++_LIBRARY)
    ENDIF (Config++_FIND_REQUIRED)
ENDIF (CONFIG++_FOUND)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTOS})

# Building server
add_executable(fs
    ${CMAKE_CURRENT_SOURCE_DIR}/fs.cpp
    ${PROTO_SRCS}
    ${GRPC_SRCS}
    ${FS_FILES}
)
target_link_libraries(fs
    gRPC::grpc++_reflection
    protobuf::libprotobuf
    ${NDN_LIBRARY}
    ${CONFIG++_LIBRARY}
)

# Building client
add_executable(namenode_test
    ${CMAKE_CURRENT_SOURCE_DIR}/namenode_test.cpp
    ${PROTO_SRCS}
    ${GRPC_SRCS}
    ${NAMENODE_TEST_FILES}
)
target_link_libraries(namenode_test
    gRPC::grpc++_reflection
    protobuf::libprotobuf
    ${NDN_LIBRARY}
    ${CONFIG++_LIBRARY}
)

# Building client
add_executable(name
    ${CMAKE_CURRENT_SOURCE_DIR}/name.cpp
    ${PROTO_SRCS}
    ${GRPC_SRCS}
    ${NAME_FILES}
)
target_link_libraries(name
    gRPC::grpc++_reflection
    protobuf::libprotobuf
    ${NDN_LIBRARY}
    ${CONFIG++_LIBRARY}
)

# Building test

# target_link_libraries(fs PUBLIC ${NDN_LIBRARY})
#target_link_libraries(test PUBLIC ${NDN_LIBRARY})
