CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
PROJECT( my_http )
SET( CMAKE_CXX_COMPILER "g++") #设定编译器
SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 

#INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/include )
#LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/lib)

#ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/Server )
#ADD_SUBDIRECTORY( ${PROJECT_SOURCE_DIR}/Http )

# 增加一个可执行的二进制
ADD_EXECUTABLE(my_http ${PROJECT_SOURCE_DIR}/Server/TCPServer.cpp
                        ${PROJECT_SOURCE_DIR}/Server/TCPServer.h
                        ${PROJECT_SOURCE_DIR}/Server/epoll.cpp
                        ${PROJECT_SOURCE_DIR}/Server/epoll.h
                        ${PROJECT_SOURCE_DIR}/Server/channellists.cpp
                        ${PROJECT_SOURCE_DIR}/Server/channellists.h
		       ${PROJECT_SOURCE_DIR}/Http/Request.cpp
                        ${PROJECT_SOURCE_DIR}/Http/Request.h
	      )
