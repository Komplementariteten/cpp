//
// Created by Will nicht on 06.10.18.
//

#ifndef GEOLOGGER_DBSTORAGE_H
#define GEOLOGGER_DBSTORAGE_H

#include <stdexcept>
#include "../util/Singelton.h"
#include <leveldb/db.h>

namespace GeoLogger {
    class DbStorage {
    public:
        DbStorage();
        ~DbStorage();
        bool IsOpen();
        bool Set(const std::string &container, const std::string &key, const std::string &Value);
        std::string Get(const std::string &container, const std::string &key);
    private:
        const leveldb::Options getConfig();
        const std::string& getDbFilePath();
        const leveldb::WriteOptions getWriteOption();
        const leveldb::ReadOptions getReadOption();
        const std::string generateKey(const std::string &container, const std::string &key);
        leveldb::DB* m_pdb;
    };
    typedef Singelton<GeoLogger::DbStorage> StorageSingelton;
}

#endif //GEOLOGGER_DBSTORAGE_H
