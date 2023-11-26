# NetworkSimulation
A program for simulation of network traffic. Given the characteristics of network sessions (defined by generator configs), a network trace mimicing these characteristics will be output to .pcap file, which can be read by Wireshark.
PCAPNG is currently not supported.

# Structure
- Unit tests are located in the NetworkSimTesting folder.
- The code base is located in the NetworkSimulation folder.

# Dependencies
The project depends on the following libraries:
- libpcap: In order to write .pcap files. See https://www.tcpdump.org/.
Ubuntu install: `apt install libpcap-dev`
- BOOST: For reading JSON configuration files.
Ubuntu install: apt install libboost-all-dev

# Testing dependencies
- Google Test: Used for unit testing. See https://github.com/google/googletest.git.
Ubuntu install:
cd /usr/src
git clone https://github.com/google/googletest.git
mkdir build && cd build
cmake ..
make
copy lib files to /usr/local/lib
copy header files to /usr/local/include

- LCOV: Used for generating code coverage documentation. 
Ubuntu install: sudo apt install lcov

# Building
## Building the network simulator
1. Go to the _NetworkSimulation_ folder
2. `mkdir build && cd build`

Then build by:

3. `cmake ..`

4. `make`

**Note**: Currently the compilation process is (very) slow. This is due to the CMAKE file using glob. A better compilation process will have to be developed in the future.

## Building the tests
1. Go to the _NetworkSimTesting_ folder
2. mkdir build && cd build

Then build by:
3. cmake ..
4. make ..

If you want to also generate code coverage, run ./gen_coverage.sh.
It will not work for all systems, since it is platform dependent.

# Running the network simulator
In order to run the network simulator, you have to specify the folders where your generator configs are located as run argument. All generator files in that folder will then be used to generate traffic.
You can specify multiple generator files. For example:

```
./NetworkSimulation.out ../SimulatorConfig/
```

Will use all the generator files located in ../SimulatorConfig/ (relative path to the executable). More folders can be added if needed. A folder generator files should be seen as a "category" of configurations of traces, that specifies some application. E.g., you may have a folder called Windows 10, with configuration files that specify the traces for that operating system. If you do:

```
./NetworkSimulation.out Windows10
```

Then Windows 10 will be simulated. More applications can be added on top, if wanted.
Currently, only a single node can be simulated.

After running `./NetworkSimulation.out` you will be prompted for a output filename, the average RTT and the standard deviation of the RTT in the network you want to simulate. In addition, you will be told to specify the simulation time, in seconds. After that it runs, and an output PCAP file with the simulated traces is generated.

# Specifying generator configs
Generator configs are specified in .json. Such a file looks like this:

```json
{
    "PROTOCOL_STACK" : ["TCP", "IPv4", "Ethernet"],
    "CONNECTION_OFFSET_SEC" : 10,
    "CONNECTION_OFFSET_USEC" : 213,
    "CONNECTION_END" : 110,
    "REPEATS_AFTER" : 150,
    "APPLICATION_DATA" : "../ApplicationDataConfigs/applicationdata.json",
    "CLIENT" : {
        "INIT_CONNECTION" : true,
        "END_CONNECTION" : true,
        "IP_INFO" : {
            "IP_ADDRESS" : "192.168.0.1",
            "TTL" : 128
        },
        "TCP_INFO" : {
            "SOURCE_PORT" : "application set",
            "MSS" : 1460,
            "PACKETS_SENT" : 8,
            "WINDOW_SIZES" : [4535, 5435, 5435]
        }
    },
    "SERVER" : {
        "INIT_CONNECTION" : false,
        "END_CONNECTION" : false,
        "IP_INFO" : {
            "IP_ADDRESS" : "40.113.10.67",
            "TTL" : 64
        },
        "TCP_INFO" : {
            "SOURCE_PORT" : 443,
            "MSS" : 1440,
            "PACKETS_SENT" : 10,
            "WINDOW_SIZES" : [4535, 5435, 5435]
        }
    }
}
```

* The _PROTOCOL_STACK_ defines which protocols are used, from the transport layer and all the way down to the link layer. Currently only TCP, IPv4 and Ethernet are supported, but it is planned to add more protocols in the future.
* _CONNECTION_OFFSET_ defines when the first packet is transmitted. (_CONNECTION_OFFSET_SEC_ is in seconds and _USEC_ is in micro seconds).
* _CONNECTION_END_ defines when the connection is terminated. In TCP, this means a RST or when the 4-way close will occur. If _CONNECTION_END_ < _CONNECTION_OFFSET_, it will result in weird behavior (i.e. you will first get a close dialog, then a 3-way handshake opening the connection, and then the data exchange).
* _REPEATS_AFTER_ means that this session will be repeated after the time specified, in minutes.
* _APPLICATION_DATA_ points to an application data configuration file that defines how data should be exchanged (by defining the data contained in the packets for both client and server, the delay between sending the packets, and the send pattern between client and server).
* _CLIENT_ and _SERVER _defines the configuration of the client (the one initiating a connection) and the server. _INIT_CONNECTION_ and _END_CONNECTION_ is not used to do anything currently. However, the parser still needs them. _END_CONNECTION_ will be used in the future to determine _which_ of the client and server that initiates the closing of a connection. Note that currently connections are closed using RST (a very rude close), which is not very realistic.
* _IP_INFO_ defines the configuration for the IPv4 protocol. Currently, this is only the IPv4 address and time to live. Since TTL values almost never change during a session, only one value can be chosen.
* _TCP_INFO_ defines the configuration for the TCP protocol. Right now only _SOURCE_PORT_, _MSS_ and _WINDOW_SIZES_ have an effect (_PACKETS SENT_ is a left over that is not really used anymore). _WINDOW SIZES_ is a list of window sizes. When simulating, TCP will choose one of these window sizes, at random, for every segment.


