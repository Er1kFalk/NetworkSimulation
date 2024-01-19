set(WAYNE_UTILS_SOURCES
    wayneEnums.cpp
    wayneFS.cpp
    wayneIO.cpp
    wayneStrUtil.cpp
)

add_library(wayne_utils_lib STATIC ${WAYNE_UTILS_SOURCES})