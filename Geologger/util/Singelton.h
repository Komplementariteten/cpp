//
// Created by Will nicht on 06.10.18.
//

#ifndef GEOLOGGER_SINGELTON_H
#define GEOLOGGER_SINGELTON_H

#include <stddef.h>

template <class T>
class Singelton {
public:
    static T* getInstance() {
        if(!m_pInstance) m_pInstance = new T;
        assert(m_pInstance != NULL);
        return m_pInstance;
    }
protected:
    Singelton();
    ~Singelton();
private:
    Singelton(Singelton const&);
    Singelton &operator=(Singelton const&);
    static T* m_pInstance;
};

template <class T> T* Singelton<T>::m_pInstance = NULL;

#endif //GEOLOGGER_SINGELTON_H
