#ifndef __MAKE_H__
#define __MAKE_H__

#include <memory>

template<typename Container, typename ... Args>
auto make( Args&& ... args ) {

    if constexpr ( sizeof...(Args) == 0 )
       return Container();

    Container container;
    ( container.emplace_front( std::forward<Args>(args) ), ... );
    return container;

}

#endif /* __MAKE_H__ */
