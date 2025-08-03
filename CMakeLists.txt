# 设置版本
cmake_minimum_required(VERSION 3.27)
# 设置项目名称
project(LearnC__)
# 设置c++编译标准
set(CMAKE_CXX_STANDARD 20)

# 所有子目录都遵循 exercise* 和 learn_c++* 的模式
file(GLOB subdirs LIST_DIRECTORIES true RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
foreach(subdir ${subdirs})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${subdir} AND
    (subdir MATCHES "^exercise[0-9]+$" OR subdir MATCHES "^learn_c\\+\\+[0-9]+$"))
        add_subdirectory(${subdir})
    endif()
endforeach()
