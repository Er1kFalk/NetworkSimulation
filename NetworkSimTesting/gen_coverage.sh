cd build/
rm -rf out_coverage/*
./NetworkSimTesting
lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info '/usr/*' '*/NetworkSimTesting/*' --output-file coverage_filtered.info
genhtml coverage_filtered.info --output-directory out_coverage
firefox out_coverage/index.html # this is just for convenience (to open coverage when it's done)
# if you don't have firefox, remove it
