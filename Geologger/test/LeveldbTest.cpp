//
// Created by Will nicht on 03.10.18.
//

#include <gtest/gtest.h>
#include <leveldb/db.h>
#include <random>
#include <array>
#include "../storage/dbstorage.h"

const std::string GetKey(const std::string &prefix, const std::string &family, const std::string &value) {
    std:: string t(prefix);
    return t.append(family).append(prefix).append(value);
}

const std::string DB_KEY(std::string key) {
    return GetKey("/", "TestData", key);
}

static std::array<char, 4096> GetRandomString() {
    const int n = 4096;
    const char alphanum[] = "123456789abcdefghijklmnopqrstuvwxyz+*/.,;:_-=?!";
    std::default_random_engine rng;
    std::uniform_int_distribution<> dist(0, sizeof(alphanum) -1);
    std::array<char, n> result;
    for (int i = 0; i < n; i++)
        result[i] = alphanum[dist(rng)];
    //std::shared_ptr<>
    return result;
}


TEST(LeveldbTest, LibaryTest) {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
    ASSERT_TRUE(status.ok());
    delete(db);
}

TEST(LeveldbTest, RWTest) {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
    ASSERT_TRUE(status.ok());
    auto key = DB_KEY("RWTest");
    auto value = GetRandomString();
    std::string value_str(std::begin(value), std::end(value));
    auto datasize = sizeof(value_str);
    ASSERT_GT(datasize, 0);
    db->Put(leveldb::WriteOptions(), key, value_str);
    std::string read_value;
    db->Get(leveldb::ReadOptions(), key, &read_value);
    ASSERT_EQ(datasize, sizeof(read_value));
    ASSERT_EQ(read_value, value_str);
    delete(db);
}

TEST(LeveldbTest, ItteratorTest) {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
    ASSERT_TRUE(status.ok());
    auto key1 = DB_KEY("ItteratorTest1");
    auto value = GetRandomString();
    std::string str_value1(std::begin(value), std::end(value));
    db->Put(leveldb::WriteOptions(), key1, str_value1);
    auto key2 = DB_KEY("ItteratorTest2");
    value = GetRandomString();
    std::string str_value2(std::begin(value), std::end(value));
    db->Put(leveldb::WriteOptions(), key2, str_value2);
    auto key3 = DB_KEY("ItteratorTest3");
    value = GetRandomString();
    std::string str_value3(std::begin(value), std::end(value));
    db->Put(leveldb::WriteOptions(), key3, str_value3);
    auto key4 = DB_KEY("ItteratorTest4");
    value = GetRandomString();
    std::string str_value4(std::begin(value), std::end(value));
    db->Put(leveldb::WriteOptions(), key4, str_value4);
    auto key5 = DB_KEY("ItteratorTest5");
    value = GetRandomString();
    std::string str_value5(std::begin(value), std::end(value));
    db->Put(leveldb::WriteOptions(), key5, str_value5);
    auto key6 = DB_KEY("ItteratorTest6");
    value = GetRandomString();
    std::string str_value6(std::begin(value), std::end(value));
    db->Put(leveldb::WriteOptions(), key6, str_value6);
    auto key7 = DB_KEY("ItteratorTest7");
    value = GetRandomString();
    std::string str_value7(std::begin(value), std::end(value));
    db->Put(leveldb::WriteOptions(), key7, str_value7);
    auto key8 = DB_KEY("ItteratorTest8");
    value = GetRandomString();
    std::string str_value8(std::begin(value), std::end(value));
    db->Put(leveldb::WriteOptions(), key8, str_value8);

    int n = 0;

    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
    for(it->SeekToFirst(); it->Valid(); it->Next()) {
        ++n;
    }
    ASSERT_TRUE(it->status().ok());
    ASSERT_EQ(n, 9);
    delete it;
}

TEST(LeveldbTest, DbSingeltonTest){
    ASSERT_TRUE(GeoLogger::StorageSingelton::getInstance()->IsOpen());
}