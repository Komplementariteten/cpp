//
// Created by Will nicht on 2019-01-26.
//

#ifndef KOMPLEMENTLIB_TYPE_TOOLS_H
#define KOMPLEMENTLIB_TYPE_TOOLS_H
#include <type_traits>

namespace komplement {
    namespace type {

        template<typename T, template<typename> class TT>
        struct is_instantiation_of : std::false_type { };

        template<typename T, template<typename> class TT>
        struct is_instantiation_of<TT<T>, TT> : std::true_type { };
    }
}
#endif //KOMPLEMENTLIB_TYPE_TOOLS_H
