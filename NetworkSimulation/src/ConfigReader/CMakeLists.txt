set(CONFIG_READER_SOURCES
    ConfigReader.cpp
    GeneratorFileStruct.cpp
)

add_library(config_reader_lib STATIC ${CONFIG_READER_SOURCES})