g++ -std=c++17 server_prefetch_test.cc -o server_prefetch_test -lrocksdb -Wl,-rpath=/usr/local/lib
./server_prefetch_test