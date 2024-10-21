# 查找 MySQL 库
find_library(MYSQL_LIB mysqlclient HINTS /usr/lib64/mysql /usr/lib/mysql)
if (NOT MYSQL_LIB)
    message(FATAL_ERROR "MySQL client library not found")
endif()

# 定义源文件列表
aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_LIST)
aux_source_directory(./model MODEL_LIST)
aux_source_directory(./redis REDIS_LIST)
# 创建可执行文件
add_executable(ChatServer ${SRC_LIST} ${DB_LIST} ${MODEL_LIST} ${REDIS_LIST})

# 指定链接的库
target_link_libraries(ChatServer muduo_net muduo_base ${MYSQL_LIB} hiredis pthread)
