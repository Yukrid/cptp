#ifndef GROUPDATA_GROUPDATA_INL
#define GROUPDATA_GROUPDATA_INL

#include "groupdata.hpp"

namespace gd{
    
    //+++++++++++++++++++//
    //    Common Type    //
    //+++++++++++++++++++//
    //(    gd::Range Lamination Template    +//
    // Construction Function
    template <typename T>
    Range<T>::Range(T* b_, T* e_) noexcept
        : _begin {b_}
        , _end   {e_}
    {
        return;
    }



    // Access Function
    template <typename T>
    T* Range<T>::begin(void) noexcept
    {
        return _begin;
    }
    
    
    template <typename T>
    T* Range<T>::end (void) noexcept
    {
        return _end;
    }


/*
    //(    gd::ConstRange Lamination Template    +//
    // Construction Function
    template <typename T>
    ConstRange<T>::ConstRange(const T* b_, const T* e_) noexcept
        : _begin {b_}
        , _end   {e_}
    {
        return;
    }



    // Access Function
    template <typename T>
    const T* ConstRange<T>::begin(void) noexcept
    {
        return _begin;
    }
    
    
    template <typename T>
    const T* ConstRange<T>::end (void) noexcept
    {
        return _end;
    }
    */
    
    //(    gd::Shadow Lamination Template    )//
    template <typename... As>
    constexpr size_t Shadow<As...>::width(void)
    {
        return 0;
    }

    
    //(    gd::Shadow<T, As...> Lamination Template    )//
    // Static Functions
    template <typename T, typename... As>
    constexpr size_t Shadow<T, As...>::width(void)
    {
        constexpr size_t max_size=shadows.width();
        
        return sizeof(T)>max_size ? sizeof(T) : max_size;
    }

    

    //++++++++++++++++++++++++//
    //    Common Functions    //
    //++++++++++++++++++++++++//
    //+    std::ostream.operator    +//
    template <typename T>
    auto _ostream(const T& t_, std::ostream& os_, int32_t) noexcept -> decltype(void(std::declval<std::ostream&>()<<std::declval<T>()))
    { 
        os_<<t_;

        return;
    }



    template <typename T>
    auto _ostream(const T& t_, std::ostream& os_, int16_t) noexcept -> void
    { 
        os_<<"?";

        return;
    }



    template <typename T>
    auto ostream(const T& t_, std::ostream& os_) noexcept -> decltype(void(_ostream(std::declval<T>(), std::declval<std::ostream&>(), 0)))
    {
        _ostream(t_, os_, 0);

        return;
    }




    //+    gd::[object].depth    +// 
    template <typename T>
    constexpr auto _depth(const T& t_, uint16_t d_, int32_t) noexcept -> decltype(std::declval<T>().depth(_key_))
    {    
        return d_+t_.depth();
    }



    template <typename T>
    constexpr auto _depth(const T&, uint16_t d_, int16_t) noexcept -> int16_t
    {    
        return d_+1;
    }
    


    template <typename T>
    constexpr auto depth(const T& t_, uint16_t d_) noexcept -> decltype(_depth(std::declval<T>(), std::declval<uint16_t>(), 0))
    {
        return _depth(t_, d_, 0);
    }
}
#endif
