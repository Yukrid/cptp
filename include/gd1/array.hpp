#ifndef GROUPDATA_ARRAY_HPP
#define GROUPDATA_ARRAY_HPP

#include "./groupdata.hpp"

   
#ifdef GROUPDATA_ARRAY_EXCEPTION
    #include "./exception/exception.hpp"
#endif

namespace gd{
    
    //+++++++++++++++++++++//
    //    Array Objects    //
    //+++++++++++++++++++++//
    //->    array.hpp, array.inl    <-//
    //(    gd::Array Lamination for Lamination    )//
    template <size_t S, typename T>
    struct Array{
        
        //+    Member Variables    +//
        protected :
        T _elements[S];
        

        //+    Static Functions    +//
        public :
        static constexpr uint16_t depth (Empty =_key_) noexcept;
        static constexpr size_t   size  (Empty =_key_) noexcept;
        

        //+    Member Functions    +//
        public :
        // Contruction Functions
                     Array     (void)                     noexcept;
                     Array     (const Array<S, T>&)       noexcept;
                     Array     (Array<S, T>&&)            noexcept;
                     Array     (std::initializer_list<T>) noexcept;

        template <typename... I>
        Array<S, T>& construct (I...) noexcept;
        
        // Destruction Functions
                     ~Array   (void) noexcept;
        Array<S, T>& destruct (void) noexcept;

        // Reference functions
        template<uint16_t N>
              auto           ref        (void)                         const noexcept -> typename std::enable_if_t<(N==0), const T*>;
        const T*             ref        (uint16_t)                     const noexcept;
        const T*             spec       (void)                         const noexcept;
        #ifdef GROUPDATA_ARRAY_EXCEPTION
        const T&             operator() (const size_t&)                const;
        #else
        const T&             operator() (const size_t&)                const noexcept;
        #endif
              Range<const T> range      (const size_t& =S)             const noexcept;
              Range<const T> range      (const size_t&, const size_t&) const noexcept;

        // Access functions
        template<uint16_t N>
        auto         path       (void)                         noexcept -> typename std::enable_if_t<(N==0), T*>;
        T*           path       (uint16_t)                     noexcept; 
        T*           data       (void)                         noexcept;
        #ifdef GROUPDATA_ARRAY_EXCEPTION
        T&           operator[] (const size_t&);
        #else
        T&           operator[] (const size_t&)                noexcept;
        #endif
        Array<S, T>& operator=  (const Array<S, T>&)           noexcept;
        Array<S, T>& operator=  (Array<S, T>&&)                noexcept;
        Range<T>     range      (const size_t& =S)             noexcept;
        Range<T>     range      (const size_t&, const size_t&) noexcept;

        // Casting Functions
        template <size_t R, typename U>
        operator Array<R, U> () const noexcept;
    };
    
    
    
    //(    gd::ElasticArray Lamination for Lamination    )//
    template <size_t S, typename T>
    struct ElasticArray{
        
        //+    Member Variables    +//
        protected :
        T _elements[S];
        

        //+    Static Functions    +//
        public :
        static constexpr uint16_t depth (Empty =_key_) noexcept;
        static constexpr size_t   size  (Empty =_key_) noexcept;
        

        //+    Member Functions    +//
        public :
        // Contruction Functions
                            ElasticArray (void)                      noexcept;
                            ElasticArray (const ElasticArray<S, T>&) noexcept;
                            ElasticArray (ElasticArray<S, T>&&)      noexcept;
                            ElasticArray (std::initializer_list<T>)  noexcept;
        template <typename... I>
        ElasticArray<S, T>& construct    (I...) noexcept;
        
        // Destruction Functions
                            ~ElasticArray (void) noexcept;
        ElasticArray<S, T>& destruct      (void) noexcept;

        // Reference functions
        template<uint16_t N>
              auto          ref        (void)                         const noexcept -> typename std::enable_if_t<(N==0), const T*>;
        const T*            ref        (uint16_t)                     const noexcept;
        const T*            spec       (void)                         const noexcept;
        #ifdef GROUPDATA_ARRAY_EXCEPTION
        const T&            operator() (const size_t&)                const;
        #else
        const T&            operator() (const size_t&)                const noexcept;
        #endif
              Range<const T> range     (const size_t& =S)             const noexcept;
              Range<const T> range     (const size_t&, const size_t&) const noexcept;

        // Access functions
        template<uint16_t N>
        auto                path       (void)                         noexcept -> typename std::enable_if_t<(N==0), T*>;
        T*                  path       (uint16_t)                     noexcept; 
        T*                  data       (void)                         noexcept;
        #ifdef GROUPDATA_ARRAY_EXCEPTION
        T&                  operator[] (const size_t&);
        #else
        T&                  operator[] (const size_t&)                noexcept;
        #endif
        ElasticArray<S, T>& operator=  (const ElasticArray<S, T>&)    noexcept;
        ElasticArray<S, T>& operator=  (ElasticArray<S, T>&&)         noexcept;
        Range<T>            range      (const size_t& =S)             noexcept;
        Range<T>            range      (const size_t&, const size_t&) noexcept;

        // Casting Functions
        template <size_t R, typename U>
        operator ElasticArray<R, U> () const noexcept;
    };

 
 
    
    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <size_t S, typename T>
    std::ostream& operator<<(std::ostream&, const gd::Array<S, T>&) noexcept;
    template <size_t S, typename T>
    std::ostream& operator<<(std::ostream&, const gd::ElasticArray<S, T>&) noexcept;

}




//++++++++++++++++++++++++++//
//    Inline Definitions    //
//++++++++++++++++++++++++++//
#include "array.inl"

#endif
