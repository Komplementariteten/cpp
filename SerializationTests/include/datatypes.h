//
// Created by Will nicht on 17.08.20.
//

#ifndef SERIALIZATIONTESTS_DATATYPES_H
#define SERIALIZATIONTESTS_DATATYPES_H

#include <iostream>
#include <vector>
namespace serialization_tests {

    const u_long SEPERATOR_VALUES = ULONG_MAX;

    struct meta_info {
        long x = 0;
        long Y = 0;
        long Z = 0;
        int tags;
        int flag;
        meta_info() {

        }
    };

    struct data_item {
        long M1;
        long M2;
        long M3;
        data_item(){
            M1 = 1;
            M2 = 2;
            M3 = 3;
        }
    };

    template<typename T1, typename T2>
    struct Container {
    public:
        Container<T1, T2>(): meta_info(new T1()), item_count_(0) {
            size = get_size();
        };

        Container<T1, T2>(int item_count): meta_info(new T1()), item_count_(item_count) {
            for (auto i = 0; i < item_count; ++i) {
                items.push_back(new T2());
            }
            size = get_size();
        };
        size_t size;
        T1* meta_info;
        std::vector<T2*> items;
    private:
        size_t get_size(){
            return sizeof(T1) + (this->item_count_ * sizeof(T2));
        }
        int item_count_;
    };

}

#endif //SERIALIZATIONTESTS_DATATYPES_H


