cmake_minimum_required(VERSION 2.8)

project(SmppClient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb")

add_executable(
${PROJECT_NAME}
main.cpp
pdu/BindTransceiver.cpp
pdu/BindTransceiver.h
pdu/BindTransceiverResponse.cpp
pdu/BindTransceiverResponse.h
logic/TcpClient.cpp
logic/TcpClient.h
Global.h
Global.cpp
)

target_link_libraries(${PROJECT_NAME} pthread)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
