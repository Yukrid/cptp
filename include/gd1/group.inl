#ifndef GROUPDATA_GROUP_INL
#define GROUPDATA_GROUP_INL

#include "group.hpp"
#include <cstring>

namespace gd{

    //+++++++++++++++++++++//
    //    Group Objects    //
    //+++++++++++++++++++++//
    //(    gd::Group<T, D> Lamination Tempalte for Lamination    )//
    //+    Static Functions    +//
    template <typename T, uint16_t D>
    constexpr uint16_t Group<T, D>::depth(Empty) noexcept
    {
        return D;   
    }
    
    
    template <typename T, uint16_t D>
    constexpr size_t Group<T, D>::size(Empty) noexcept
    {
        return 1;   
    }

    
        
    //+    Member Functions    +//
    // Construcntion Functions
    template <typename T, uint16_t D>
    Group<T, D>::Group(void) noexcept
    {
        return;
    }
    
    
    template <typename T, uint16_t D>
    Group<T, D>::Group(const Group<T, D>& gr_) noexcept
    {
        std::memcpy(_elements, gr_._elements, sizeof(T)*D);
        
        return;
    }


    template <typename T, uint16_t D>
    Group<T, D>::Group(Group<T, D>&& gr_) noexcept
    {
        std::memcpy(_elements, gr_._elements, sizeof(T)*D);
        
        return;
    }
    
    
    template <typename T, uint16_t D>
    Group<T, D>::Group(std::initializer_list<T> lst_) noexcept
    {
        std::memcpy(_elements, lst_.begin(), sizeof(T)*(D>lst_.size() ? lst_.size() : D));
        for(size_t a=lst_.size(); a<D; ++a){
            std::memcpy(_elements+a, lst_.end()-1, sizeof(T));
        }
        
        return;
    }


    template <typename T, uint16_t D> template <typename... I>
    Group<T, D>& Group<T, D>::construct(I... i_) noexcept
    {
        new(this) Group(i_...);

        return *this;
    }



    // Destruction Functions
    template <typename T, uint16_t D>
    Group<T, D>::~Group(void) noexcept
    {
        return;
    }
    
    
    template <typename T, uint16_t D>
    Group<T, D>& Group<T, D>::destruct(void) noexcept
    {
        ~Group();

        return *this;
    }



    // Reference functions
    template <typename T, uint16_t D> template<uint16_t N>
    auto Group<T, D>::path(void) const noexcept
     -> typename std::enable_if_t<(N<D), const T&>
    {
        return _elements[N];
    }

    
    #ifdef GROUPDATA_GROUP_EXCEPTION
    template <typename T, uint16_t D>
    const T& Group<T, D>::path(uint16_t id_) const
    {
        if(id_>=D) throw exception::exceeded_capacity_in_depth_direction(std::string{"[gd::Group<"}+typeid(T).name()+", "+std::to_string(D)+">::path(uint16_t)]", D, id_);
        
        return _elements[id_];
    }

    #else

    template <typename T, uint16_t D>
    const T& Group<T, D>::path(uint16_t id_) const noexcept
    { 
        return _elements[id_];
    }
    #endif
   
    
    template <typename T, uint16_t D> template<uint16_t N>
    auto Group<T, D>::data(void) const noexcept
     -> typename std::enable_if_t<(N<D), const T*>
    { 
        return _elements+N;
    }
    
    
    template <typename T, uint16_t D>
    const Group<T, D>& Group<T, D>::operator[](const size_t&) const noexcept
    { 
        return *this;
    }

    

    // Access functions
    template <typename T, uint16_t D> template<uint16_t N>
    auto Group<T, D>::path(void) noexcept
     -> typename std::enable_if_t<(N<D), T&>
    {
        return _elements[N];
    }
    
        
    #ifdef GROUPDATA_GROUP_EXCEPTION
    template <typename T, uint16_t D>
    T& Group<T, D>::path(uint16_t id_)
    {
        if(id_>=D) throw exception::exceeded_capacity_in_depth_direction(std::string{"[gd::Group<"}+typeid(T).name()+", "+std::to_string(D)+">::path(uint16_t)]", D, id_);
        
        return _elements[id_];
    }

    #else

    template <typename T, uint16_t D>
    T& Group<T, D>::path(uint16_t id_) noexcept
    { 
        return _elements[id_];
    }
    #endif
    
    
    template <typename T, uint16_t D> template<uint16_t N>
    auto Group<T, D>::data(void) noexcept
     -> typename std::enable_if_t<(N<D), T*>
    { 
        return _elements+N;
    }
    

    template <typename T, uint16_t D>
    Group<T, D>& Group<T, D>::operator[](const size_t&) noexcept
    {
        return *this;
    }
    
    
    template <typename T, uint16_t D>
    Group<T, D>& Group<T, D>::operator=(const Group<T, D>& gr_) noexcept
    {
        std::memcpy(_elements, gr_._elements, sizeof(T)*D);

        return *this;
    }
    
    
    template <typename T, uint16_t D>
    Group<T, D>& Group<T, D>::operator=(Group<T, D>&& gr_) noexcept
    {
        std::memcpy(_elements, gr_._elements, sizeof(T)*D);

        return *this;
    }



    // Casting Function
    template <typename T, uint16_t D> template <typename U, uint16_t E>
    Group<T, D>::operator Group<U, E>() const noexcept
    {
        Group<U, E> gr;
        std::memcpy(_elements, gr._elements, sizeof(T)*(D>E ? E : D));
        for(size_t a=E; a<D; ++a){
            std::memcpy(_elements+a, gr._elements+E-1, sizeof(T));
        }

        return gr;
    }





    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <typename T, uint16_t D>
    std::ostream& operator<<(std::ostream& os_, const gd::Group<T, D>& gr_) noexcept
    {
        for(uint_fast16_t a=0; a<gr_.depth(); ++a){
            gd::ostream(gr_.path(a), os_);
            os_<<" ";
        }

        return os_;
    }
    
    
    template <typename T, uint16_t D>
    std::ostream& operator<<(std::ostream& os_, const gd::ElasticGroup<T, D>& gr_) noexcept
    {
        for(uint_fast16_t a=0; a<gr_.depth(); ++a){
            gd::ostream(gr_.path(a), os_);
            os_<<" ";
        }
        
        return os_;
    }
}

#endif
