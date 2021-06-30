#ifndef GROUPDATA_TAG_INL
#define GROUPDATA_TAG_INL

#include "tag.hpp"
#include <cstring>

namespace gd{

    //+++++++++++++++++++//
    //    Tag Objects    //
    //+++++++++++++++++++//
    //(    gd::Tag<D> Lamination Tempalte for Lamination    )//
    //+    Static Functions    +//
    template <uint16_t D>
    constexpr uint16_t Tag<D>::depth(Empty) noexcept
    {
        return D;   
    }
    
    
    template <uint16_t D>
    constexpr size_t Tag<D>::size(Empty) noexcept
    {
        return 1;   
    }

    
        
    //+    Member Functions    +//
    // Construcntion Functions
    template <uint16_t D>
    Tag<D>::Tag(void) noexcept
    {
        return;
    }
    
    
    template <uint16_t D>
    Tag<D>::Tag(const Tag<D>& gr_) noexcept
    {
        std::memcpy(_elements, gr_._elements, sizeof(char)*D);
        
        return;
    }


    template <uint16_t D>
    Tag<D>::Tag(Tag<D>&& gr_) noexcept
    {
        std::memcpy(_elements, gr_._elements, sizeof(char)*D);
        
        return;
    }

    
    template <uint16_t D>
    Tag<D>::Tag(const char ch_[D]) noexcept
    {
        std::strncpy(_elements, ch_, D);
     
        return;
    }
    
    
    template <uint16_t D>
    Tag<D>::Tag(const std::string& str_) noexcept
    {
        std::strncpy(_elements, str_.c_str(), D);
     
        return;
    }


    template <uint16_t D> template <typename... I>
    Tag<D>& Tag<D>::construct(I... i_) noexcept
    {
        new(this) Tag(i_...);

        return *this;
    }



    // Destruction Functions
    template <uint16_t D>
    Tag<D>::~Tag(void) noexcept
    {
        return;
    }
    
    
    template <uint16_t D>
    Tag<D>& Tag<D>::destruct(void) noexcept
    {
        ~Tag();

        return *this;
    }



    // Reference functions
    template <uint16_t D> template<uint16_t N>
    auto Tag<D>::ref(void) const noexcept -> typename std::enable_if_t<(N<D), const char&>
    {
        return _elements[N];
    }

    
    #ifdef GROUPDATA_TAG_EXCEPTION
    template <uint16_t D>
    const T& Tag<D>::ref(uint16_t id_) const
    {
        if(id_>=D) throw exception::exceeded_capacity_in_depth_direction(std::string{"[gd::Tag<"}+typeid(char).name()+", "+std::to_string(D)+">::ref(uint16_t)]", D, id_);
        
        return _elements[id_];
    }

    #else

    template <uint16_t D>
    const char& Tag<D>::ref(uint16_t id_) const noexcept
    { 
        return _elements[id_];
    }
    #endif
   
    
    template <uint16_t D>
    const char* Tag<D>::spec(void) const noexcept
    { 
        return _elements;
    }

    
    template <uint16_t D>
    const Tag<D>& Tag<D>::operator()(size_t) const noexcept
    { 
        return *this;
    }
    
    
    template <uint16_t D>
    Range<const char> Tag<D>::range(uint16_t e_) const noexcept
    {
        return Range<const char>{_elements, _elements+e_};
    }
  
        
    template <uint16_t D>
    Range<const char> Tag<D>::range(uint16_t b_, uint16_t e_) const noexcept
    {
        return Range<const char>{_elements+b_, _elements+e_};
    }



    // Access functions
    template <uint16_t D> template<uint16_t N>
    auto Tag<D>::path(void) noexcept -> typename std::enable_if_t<(N<D), char&>
    {
        return _elements[N];
    }
    
        
    #ifdef GROUPDATA_TAG_EXCEPTION
    template <uint16_t D>
    char& Tag<D>::path(uint16_t id_)
    {
        if(id_>=D) throw exception::exceeded_capacity_in_depth_direction(std::string{"[gd::Tag<"}+typeid(char).name()+", "+std::to_string(D)+">::path(uint16_t)]", D, id_);
        
        return _elements[id_];
    }

    #else

    template <uint16_t D>
    char& Tag<D>::path(uint16_t id_) noexcept
    { 
        return _elements[id_];
    }
    #endif
    
    
    template <uint16_t D>
    char* Tag<D>::data(void) noexcept
    { 
        return _elements;
    }
    

    template <uint16_t D>
    Tag<D>& Tag<D>::operator[](size_t) noexcept
    {
        return *this;
    }
    
    
    template <uint16_t D>
    Tag<D>& Tag<D>::operator=(const Tag<D>& gr_) noexcept
    {
        std::memcpy(_elements, gr_._elements, sizeof(char)*D);

        return *this;
    }
    
    
    template <uint16_t D>
    Tag<D>& Tag<D>::operator=(Tag<D>&& gr_) noexcept
    {
        std::memcpy(_elements, gr_._elements, sizeof(char)*D);

        return *this;
    }
    
    
    template <uint16_t D>
    Range<char> Tag<D>::range(uint16_t e_) noexcept
    {
        return Range<char>{_elements, _elements+e_};
    }


    template <uint16_t D>
    Range<char> Tag<D>::range(uint16_t b_, uint16_t e_) noexcept
    {
        return Range<char>{_elements+b_, _elements+e_};
    }



    // Casting Function
    template <uint16_t D> template <uint16_t E>
    Tag<D>::operator Tag<E>() const noexcept
    {
        Tag<E> gr;
        std::strncpy(_elements, gr._elements, (D>E ? E : D));

        return gr;
    }




    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <uint16_t D>
    std::ostream& operator<<(std::ostream& os_, const gd::Tag<D>& gr_) noexcept
    {
        os_<<gr_.spec();

        return os_;
    }    
}
#endif
