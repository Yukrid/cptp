#ifndef GROUPDATA_TAG_HPP
#define GROUPDATA_TAG_HPP

#include "./groupdata.hpp"

#ifdef GROUPATA_TAG_EXCEPTION
    #include "./exception/exception.hpp"
#endif

namespace gd{

    //+++++++++++++++++++++//
    //    Tag Objects    //
    //+++++++++++++++++++++//
    //->    tag.hpp, tag.inl    <-//
    //(    gd::Tag<D> Lamination Template for Lamination    )//
    template <uint16_t D>
    struct Tag{
                
        //+    Member Variables    +//
        protected :
        char _elements[D];
        

        //+    Static Functions    +//
        public :
        static constexpr uint16_t depth (Empty =_key_) noexcept;
        static constexpr size_t   size  (Empty =_key_) noexcept;
        

        //+    Member Functions    +//
        public :
        // Contruction Functions
                   Tag    (void)               noexcept;
                   Tag    (const Tag<D>&)      noexcept;
                   Tag    (Tag<D>&&)           noexcept;
                   Tag    (const char[D])      noexcept;
                   Tag    (const std::string&) noexcept;
        template <typename... I>
        Tag<D>& construct (I...)               noexcept;
     
        // Destruction Functions
                   ~Tag  (void) noexcept;
        Tag<D>& destruct (void) noexcept;    

        // Reference Functions
        template<uint16_t N>
              auto              ref        (void)               const noexcept -> typename std::enable_if_t<(N<D), const char&>;
        #ifdef GROUPDATA_TAG_EXCEPTION
        const char&             ref        (uint16_t)           const;
        #else
        const char&             ref        (uint16_t)           const noexcept;
        #endif
        const char*             spec       (void)               const noexcept;
        const Tag<D>&           operator() (size_t)             const noexcept;
              Range<const char> range      (uint16_t =D)        const noexcept;
              Range<const char> range      (uint16_t, uint16_t) const noexcept;

        // Access Functions
        template<uint16_t N>
        auto        path       (void)               noexcept -> typename std::enable_if_t<(N<D), char&>; 
        #ifdef GROUPDATA_TAG_EXCEPTION
        char&       path       (uint16_t);
        #else
        char&       path       (uint16_t)           noexcept;
        #endif     
        char*       data       (void)               noexcept;
        Tag<D>&     operator[] (size_t)             noexcept;
        Tag<D>&     operator=  (const Tag<D>&)      noexcept;
        Tag<D>&     operator=  (Tag<D>&&)           noexcept;
        Range<char> range      (uint16_t =D)        noexcept;
        Range<char> range      (uint16_t, uint16_t) noexcept;

        // Casting Functions
        template <uint16_t E>
        operator Tag<E>      () const noexcept;
        operator std::string () const noexcept;
    };




    //++++++++++++++++++++++++++++++++//
    //    Attached Global Function    //
    //++++++++++++++++++++++++++++++++//
    template <uint16_t D>
    std::ostream& operator<<(std::ostream&, const gd::Tag<D>&) noexcept;

}



//++++++++++++++++++++++++++//
//    Inline Definitions    //
//++++++++++++++++++++++++++//
#include "tag.inl"

#endif
