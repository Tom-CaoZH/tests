#include <string>
#include <iostream>
#include <cassert>
#include "rocksdb/db.h"
#include "rocksdb/options.h"
#include "rocksdb/iterator.h"


void test() {
    //creat primary db (serve as the HDFS to provide data)
    rocksdb::DB *primary_db;
    rocksdb::Options option;

    option.create_if_missing = true;

    rocksdb::Status s = rocksdb::DB::Open(option,"./tmp/primary_db",&primary_db);
    assert(s.ok());

    //put some data and then flush in the primary db
    for(int i = 0; i < 5; i ++) {
        s = primary_db->Put(rocksdb::WriteOptions(), 
                                "hello" + std::to_string(i), std::string(10, 'a' + (i % 26)) );

        assert(s.ok());
    }   

    rocksdb::FlushOptions flush_option;
    s = primary_db->Flush(flush_option);
    assert(s.ok());

    //open secondary db (be used in the prefetch_server)
    rocksdb::DB *secondary_db;
    rocksdb::Options secondary_option;

    secondary_option.create_if_missing = true;
    secondary_option.max_open_files = -1;

    s = rocksdb::DB::Open(secondary_option,"./tmp/secondary_db",&secondary_db);
    assert(s.ok());

    //fetchblock

    //verify 



    s = primary_db->Close();
    assert(s.ok());
    s = secondary_db->Close();
    assert(s.ok());

    delete primary_db;
    delete secondary_db;
}


int main() {
    test();
}
