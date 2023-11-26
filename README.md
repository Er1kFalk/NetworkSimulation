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
2. mkdir build && cd build

Then build by:
3. cmake ..
4. make

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
In order to run the network simulator, you have to specify the folders where your generator files are located as run argument. All generator files in that folder will then be used to generate traffic.
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









