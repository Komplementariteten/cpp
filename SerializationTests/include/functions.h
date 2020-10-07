//
// Created by Will nicht on 07.10.20.
//

#ifndef SERIALIZATIONTESTS_FUNCTIONS_H
#define SERIALIZATIONTESTS_FUNCTIONS_H

#include <c++/v1/cstddef>
#include <c++/v1/vector>

namespace serialization_tests{
    uint get_metainfo_size(){
        return sizeof(meta_info);
    }

    uint get_dataitem_size(){
        return sizeof(data_item);
    }

    template<typename T>
    char* as_bytes(T &struct_ref, size_t container_size) {
        char* bytes = new char[container_size];
        memcpy(bytes, &struct_ref, container_size);
        return bytes;
    }

    template<typename T1, typename T2>
    T1* from_bytes(char* bytes, size_t container_size, T2 param){
        auto t1 = new T1(param);
        memcpy(t1, &bytes[0], container_size);
        return t1;
    }
}
#endif //SERIALIZATIONTESTS_FUNCTIONS_H
