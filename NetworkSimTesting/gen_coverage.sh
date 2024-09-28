#./build.sh
cd build/
rm -rf out_coverage/*
./C_runner-Debug/NetworkSimTesting
lcov --capture --directory ./C_runner-Debug/CMakeFiles/NetworkSimulationLibrary.dir --output-file coverage.info
lcov --remove coverage.info '/usr/*' '*/NetworkSimTesting/*' --output-file coverage_filtered.info
genhtml coverage_filtered.info --output-directory out_coverage
firefox out_coverage/index.html # this is just for convenience (to open coverage when it's done)
# if you don't have firefox, remove it
