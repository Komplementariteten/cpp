//
// Created by Will nicht on 16.02.20.
//

#ifndef KOMPLEMENTARITELIB_OBSERVERS_H
#define KOMPLEMENTARITELIB_OBSERVERS_H

#include <list>
#include <algorithm>

namespace Observers {
    template <typename TState>
    class Observer {
    public:
        virtual ~Observer();
        virtual void Update(TState state);
    };

    template <typename TState>
    class Subject{
    public:
        void Attach(const Observer<TState>& observer) {
            auto it = std::find(m_observers.begin(), m_observers.end(), observer);
            if (it != m_observers.end()) {
                m_observers.push_back(observer);
            }
        };
        void Detach(const Observer<TState>& observer) {
            m_observers.remove(observer);
        }
        void Notify() {
            for(Observer<TState> o : m_observers)
                o.Update(this->m_state);
        }
        Subject(std::initializer_list<Observer<TState *>> l): m_state(0), m_observers(l){

        };
    private:
        TState m_state;
        std::list<Observer<TState>> m_observers;
    };

    template <typename TState>
    class Subscriber {
    public:
        /* void Subscribe(Subject<TState>& subject){
            if (this->m_isSubscribed) {
                m_subscribtion.Detach(this->m_observer);
            }
            subject.Attach(this->m_observer);
            m_subscribtion = subject;
            m_isSubscribed = true;
        } */
        Subscriber() : m_isSubscribed(false), /* m_subscribtion() */, m_observer() {
        };
    private:
        bool m_isSubscribed;
        // Subject<TState> m_subscribtion;
        Observer<TState> m_observer;
    };
}


#endif //KOMPLEMENTARITELIB_OBSERVERS_H
