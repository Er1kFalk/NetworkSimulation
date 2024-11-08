cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(NetworkSimulation VERSION 0.0.1 LANGUAGES CXX)

set(SRCDIR src)
set(PCAPDIR ${CMAKE_CURRENT_SOURCE_DIR}/src/CppToolkit-PCAP)

add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

add_executable(NetworkSimulation
    #${LIBRARIES}
    src/NetworkSimulator.cpp
  
    # ConfigReader
    
    src/ConfigReader/BaseConfigReader/BaseConfigReader.cpp
    src/ConfigReader/BaseConfigReader/BaseConfigReader.h
    
    src/ConfigReader/GeneratorFileConfigReader/GeneratorFileConfigReader.cpp
    src/ConfigReader/GeneratorFileConfigReader/GeneratorFileConfigReader.h
    src/ConfigReader/GeneratorFileConfigReader/GeneratorFileStruct.cpp
    src/ConfigReader/GeneratorFileConfigReader/GeneratorFileStruct.h
    
    src/ConfigReader/SimulatorAppConfigReader/SimulatorAppConfigReader.h
    src/ConfigReader/SimulatorAppConfigReader/SimulatorAppConfigReader.cpp
    src/ConfigReader/SimulatorAppConfigReader/AppConfigFileStruct.h
    
    # HeaderGenerators
    src/HeaderGenerators/CommunicationProtocol/CommunicationProtocol.cpp
    src/HeaderGenerators/CommunicationProtocol/CommunicationProtocol.h
    
    src/HeaderGenerators/Data/Data.cpp src/HeaderGenerators/Data/Data.h
    
    src/HeaderGenerators/EthernetFrame/EthernetFrame.cpp
    src/HeaderGenerators/EthernetFrame/EthernetFrame.h
    src/HeaderGenerators/EthernetFrame/EthernetFrameInterface.h
    
    src/HeaderGenerators/IPv4Packet/IPv4Packet.cpp src/HeaderGenerators/IPv4Packet/IPv4Packet.h src/HeaderGenerators/IPv4Packet/IPv4PacketInterface.h
    
    src/HeaderGenerators/ProtocolConstants/ProtocolConstants.h
    
    src/HeaderGenerators/TCPSegment/TCPSegment.cpp
    src/HeaderGenerators/TCPSegment/TCPSegment.h
    src/HeaderGenerators/TCPSegment/TCPSegmentInterface.h
    
    #PCAPWriter
    src/PCAPWriter/PCAPWriter.cpp src/PCAPWriter/PCAPWriter.h
    
    #Simulator
    src/Simulator/CustomOperators/TupleGreaterThan.h
    
    src/Simulator/NetworkProperties.h
    
    src/Simulator/NetworkNodeSimulator/SimulatorTypeDefs.h 
    src/Simulator/NetworkNodeSimulator/NetworkNodeSimulator.cpp 
    src/Simulator/NetworkNodeSimulator/NetworkNodeSimulator.h
    
    src/Simulator/NetworkNodeSimulator/SimulationModels/BaseScheduler/BaseScheduler.cpp 
    src/Simulator/NetworkNodeSimulator/SimulationModels/BaseScheduler/BaseScheduler.h 
    src/Simulator/NetworkNodeSimulator/SimulationModels/BaseScheduler/Event.h 
    src/Simulator/NetworkNodeSimulator/SimulationModels/BaseScheduler/EventTypeDefs.h
    
    src/Simulator/NetworkNodeSimulator/SimulationModels/EthernetSimulator/EthernetEvent.cpp 
    src/Simulator/NetworkNodeSimulator/SimulationModels/EthernetSimulator/EthernetEvent.h 
    src/Simulator/NetworkNodeSimulator/SimulationModels/EthernetSimulator/EthernetEventRule.cpp 
    src/Simulator/NetworkNodeSimulator/SimulationModels/EthernetSimulator/EthernetEventRule.h
    src/Simulator/NetworkNodeSimulator/SimulationModels/EthernetSimulator/EthernetSimulatorTypeDefs.h
    
    src/Simulator/NetworkNodeSimulator/SimulationModels/IPv4Simulator/IPv4Event.cpp
    src/Simulator/NetworkNodeSimulator/SimulationModels/IPv4Simulator/IPv4Event.h
    src/Simulator/NetworkNodeSimulator/SimulationModels/IPv4Simulator/IPv4EventRule.cpp
    src/Simulator/NetworkNodeSimulator/SimulationModels/IPv4Simulator/IPv4EventRule.h
    src/Simulator/NetworkNodeSimulator/SimulationModels/IPv4Simulator/IPv4SimulatorTypeDefs.h
    
    src/Simulator/NetworkNodeSimulator/SimulationModels/TCPSimulator/TCPEvent.cpp
    src/Simulator/NetworkNodeSimulator/SimulationModels/TCPSimulator/TCPEvent.h
    src/Simulator/NetworkNodeSimulator/SimulationModels/TCPSimulator/TCPEventRules.cpp
    src/Simulator/NetworkNodeSimulator/SimulationModels/TCPSimulator/TCPEventRules.h
    src/Simulator/NetworkNodeSimulator/SimulationModels/TCPSimulator/TCPSimulatorTypeDefs.h
    
    # Utility Library
    src/UtilityLibraries/ArrayUtils/ArrayUtils.cpp
    src/UtilityLibraries/ArrayUtils/ArrayUtils.h
    
    src/UtilityLibraries/BitOperations/BitOperations.cpp
    src/UtilityLibraries/BitOperations/BitOperations.h
    
    src/UtilityLibraries/ProtocolUtils/ProtocolUtils.cpp
    src/UtilityLibraries/ProtocolUtils/ProtocolUtils.h
    
    src/UtilityLibraries/RandomUtils/RandomUtils.cpp
    src/UtilityLibraries/RandomUtils/RandomUtils.h
    
    src/UtilityLibraries/StringUtils/StringUtils.cpp
    src/UtilityLibraries/StringUtils/StringUtils.h
    
    src/UtilityLibraries/WayneUtils/wayneEnums.cpp
    src/UtilityLibraries/WayneUtils/wayneEnums.hpp
    src/UtilityLibraries/WayneUtils/wayneFS.cpp
    src/UtilityLibraries/WayneUtils/wayneFS.hpp
    src/UtilityLibraries/WayneUtils/wayneIO.cpp
    src/UtilityLibraries/WayneUtils/wayneIO.hpp
    src/UtilityLibraries/WayneUtils/wayneStrUtil.cpp
    src/UtilityLibraries/WayneUtils/wayneStrUtil.hpp
)
set_target_properties(
    NetworkSimulation 
    PROPERTIES 
        OUTPUT_NAME "NetworkSimulation"
        SUFFIX ".out"
)

#target_compile_options(NetworkSimulation PRIVATE -Wall -Wextra -Wpedantic -Werror)

target_include_directories(NetworkSimulation PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${PCAPDIR}
)

target_link_libraries(NetworkSimulation -lpcap)
