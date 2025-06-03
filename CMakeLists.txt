cmake_minimum_required(VERSION 3.16)

# 项目配置
project(ZTS_OS_Design 
    VERSION 1.0.0
    DESCRIPTION "ZTS Operating System Design & Simulation Platform"
    LANGUAGES CXX
)

# C++标准设置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译器配置
if(MSVC)
    # Windows/MSVC特定配置
    add_compile_options(/utf-8)  # 支持UTF-8编码
    add_compile_options(/W4)     # 警告级别
    add_definitions(-DUNICODE -D_UNICODE)
    # 禁用一些MSVC的安全警告
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # GCC/Clang配置
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 包含目录
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/core)
include_directories(${CMAKE_SOURCE_DIR}/include/algorithms)
include_directories(${CMAKE_SOURCE_DIR}/include/utils)

# 定义源文件组
set(CORE_SOURCES
    src/process/Process.cpp
)

set(SCHEDULER_SOURCES
    src/scheduler/Scheduler.cpp
    src/scheduler/FCFSScheduler.cpp
    src/scheduler/RoundRobinScheduler.cpp
    src/scheduler/SJFScheduler.cpp
    src/scheduler/PriorityScheduler.cpp
)

set(MEMORY_SOURCES
    src/memory/MemoryManager.cpp
    src/memory/ContiguousAllocator.cpp
    # src/memory/PagingManager.cpp
)

set(UI_SOURCES
    src/ui/boot_animation.cpp
    src/ui/scheduler_demo.cpp
    src/ui/memory_demo.cpp
)

# 暂时注释掉未实现的模块
# set(FILESYSTEM_SOURCES
#     src/filesystem/file_system.cpp
#     src/filesystem/directory.cpp
#     src/filesystem/file.cpp
# )

# set(SYNC_SOURCES
#     src/synchronization/semaphore.cpp
#     src/synchronization/mutex.cpp
#     src/synchronization/condition_variable.cpp
# )

# 所有源文件
set(ALL_SOURCES
    ${CORE_SOURCES}
    ${SCHEDULER_SOURCES}
    ${MEMORY_SOURCES}
    ${UI_SOURCES}
    # ${FILESYSTEM_SOURCES}
    # ${SYNC_SOURCES}
)

# 主可执行文件
add_executable(${PROJECT_NAME} 
    main.cpp
    ${ALL_SOURCES}
)

# Windows特定链接库
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE kernel32 user32)
endif()

# 启用测试
enable_testing()

# 添加测试可执行文件
if(EXISTS ${CMAKE_SOURCE_DIR}/tests)
    # add_subdirectory(tests)
endif()

# 编译后事件 - 复制资源文件
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    COMMENT "Copying resources to output directory"
)

# 安装配置
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY resources/
    DESTINATION bin/resources
)

# 打包配置
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "ZIP")
include(CPack) 