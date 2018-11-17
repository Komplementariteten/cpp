//
// Created by Will nicht on 06.10.18.
//

#include "dbstorage.h"

namespace GeoLogger {
    DbStorage::DbStorage() {
        auto path = getDbFilePath();
        leveldb::Status status = leveldb::DB::Open(getConfig(), path, &m_pdb);
        if (!status.ok()) throw std::logic_error("Failed to initialize LevelDb");
    }
    bool DbStorage::IsOpen() {
        return true;
    }

    bool DbStorage::Set(const std::string &Container,const std::string &Key,const std::string &Value) {
        auto t_key = this->generateKey(Container, Key);
        leveldb::Status status = this->m_pdb->Put(getWriteOption(), t_key, Value);
        return status.ok();
    }

    std::string DbStorage::Get(const std::string &container, const std::string &key) {
        auto read = getReadOption();
        auto t_key = this->generateKey(container, key);
        std::string read_value;
        leveldb::Status status = this->m_pdb->Get(read, t_key, &read_value);
        if (!status.ok()) throw std::logic_error("Key not found");
        return read_value;
    }

    const leveldb::ReadOptions DbStorage::getReadOption() {
        auto options = leveldb::ReadOptions();
        return options;
    }

    const leveldb::WriteOptions DbStorage::getWriteOption() {
        auto options = leveldb::WriteOptions();
        return options;
    }

    const std::string generateKey(const std::string &container, const std::string &key) {
        std::string t(container);
        return t.append(".").append(key);
    }

    const leveldb::Options DbStorage::getConfig() {
        auto options = leveldb::Options();
        options.create_if_missing = true;
        return options;
    }

    const std::string& DbStorage::getDbFilePath() {
        std::string t_str = "/tmp/dev.leveldb";
        return t_str;
    }
}