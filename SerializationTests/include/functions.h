//
// Created by Will nicht on 07.10.20.
//

#ifndef SERIALIZATIONTESTS_FUNCTIONS_H
#define SERIALIZATIONTESTS_FUNCTIONS_H

#include <vector>
#include "datatypes.h"

namespace serialization_tests{
    uint get_metainfo_size(){
        return sizeof(meta_info);
    }

    uint get_dataitem_size(){
        return sizeof(data_item);
    }

    template<typename T>
    std::vector<std::byte> as_bytes(T* struct_ref, size_t container_size) {
        auto bytes = std::vector<std::byte>(container_size);
        memcpy(&bytes[0], struct_ref, container_size);
        return bytes;
    }
    template<typename T>
    std::vector<std::byte> as_bytes(T &&rvalue) {
        auto s = sizeof(rvalue);
        auto bytes = std::vector<std::byte>(s);
        memcpy(&bytes[0], &rvalue, s);
        return bytes;
    }
    template<typename T1>
    T1* from_bytes(std::byte *bytes, size_t container_size){
        auto t1 = new T1();
        memcpy(t1, &bytes[0], container_size);
        return t1;
    }
}
#endif //SERIALIZATIONTESTS_FUNCTIONS_H
