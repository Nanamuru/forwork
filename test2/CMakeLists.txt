

#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

set(LLVM_DIR "C:\\llvm-project\\llvm-project\\build\\lib\\cmake\\llvm")
set(Clang_DIR "C:\\llvm-project\\llvm-project\\build\\lib\\cmake\\clang")
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
cmake_minimum_required (VERSION 3.8)
set(SOURCES_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test1.cpp)
set(CLANG_LIBS STATIC
    clangAST
    clangAnalysis
    clangBasic
    clangDriver
    clangEdit
    clangFrontend
    clangLex
    clangParse
    clangSema
    clangSerialization
)


#
project ("test1")



# Добавьте источник в исполняемый файл этого проекта.
add_executable (test1 "test1.cpp" )
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
link_directories(${LLVM_LIBRARY_DIRS})

target_include_directories(test1 PUBLIC ${CLANG_INCLUDE_DIRS})

#target_link_libraries(test1 ${CLANG_LIBS} LLVM)
target_link_libraries(test1 STATIC ${CLANG_LIBS} ${CLANG_LINK_FLAGS})