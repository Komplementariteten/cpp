//
// Created by Will nicht on 16.02.20.
//

#ifndef KOMPLEMENTARITELIB_TESTS_H
#define KOMPLEMENTARITELIB_TESTS_H

#include "library.h"
#include <iostream>

namespace Tests {

    struct IntStruct {

    };

    class IntObserver {
    public:
        IntObserver(): m_subscriber(), m_subject() {
        }
    private:
        int m_currentInt = 0;
        Observers::Subscriber<IntStruct> m_subscriber;
        Observers::Subject<IntStruct> m_subject;
    };
}

#endif //KOMPLEMENTARITELIB_TESTS_H
