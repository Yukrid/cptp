#ifndef GROUPDATA_VECTOR_HPP
#define GROUPDATA_VECTOR_HPP

#include "./groupdata.hpp"

   
#ifdef GROUPDATA_VECTOR_EXCEPTION
    #include "./exception/exception.hpp"
#endif
#ifdef GROUPDATA_VECTOR_WARNING
    #include "./warning/warning.hpp"
#endif


namespace gd{

    //++++++++++++++++++++++//
    //    Vector Objects    //
    //++++++++++++++++++++++//
    //->    vector.hpp, vector.inl    <-//
    //(    gd::Vector Structure for Lamination    )//
    template <size_t S, typename T>
    struct Vector{
                
        //+    Member Variables    +//
        protected :
        T* _elements;
        

        //+    Static Functions    +//
        public :
        static constexpr uint16_t depth (Empty =_key_) noexcept;
        static constexpr size_t   size  (Empty =_key_) noexcept;
        

        //+    Member Functions    +//
        public :
        // Contruction Functions
                      Vector    (void)                     noexcept;
                      Vector    (const Vector<S, T>&)      noexcept;
                      Vector    (Vector<S, T>&&)           noexcept;
                      Vector    (std::initializer_list<T>) noexcept;
        template <typename... I>
        Vector<S, T>& construct (I...) noexcept;
        
        // Destruction Functions
                      ~Vector  (void) noexcept;
        Vector<S, T>& destruct (void) noexcept;

        
        // Reference functions
        template<uint16_t N>
              auto           ref        (void)                         const noexcept -> typename std::enable_if_t<(N==0), const T*>;
        const T*             ref        (uint16_t)                     const noexcept;
        const T*             spec       (void)                         const noexcept;
        #ifdef GROUPDATA_VECTOR_EXCEPTION
        const T&             operator() (const size_t&)                const;
        #else
        const T&             operator() (const size_t&)                const noexcept;
        #endif
              Range<const T> range      (const size_t& =S)             const noexcept;
              Range<const T> range      (const size_t&, const size_t&) const noexcept;


        // Access functions
        template<uint16_t N>
        auto          path       (void)                         noexcept -> typename std::enable_if_t<(N==0), T*>;
        T*            path       (uint16_t)                     noexcept; 
        T*            data       (void)                         noexcept;
        #ifdef GROUPDATA_VECTOR_EXCEPTION
        T&            operator[] (const size_t&);
        #else
        T&            operator[] (const size_t&)                noexcept;
        #endif
        Vector<S, T>& operator=  (const Vector<S, T>&)          noexcept;
        Vector<S, T>& operator=  (Vector<S, T>&&)               noexcept;
        Range<T>      range      (const size_t& =S)             noexcept;
        Range<T>      range      (const size_t&, const size_t&) noexcept;

        // Casting Functions
        template <size_t R, typename U>
        operator Vector<R, U> () const noexcept;
    };
    
    
    
    //(    gd::ElasticVector Structure for Lamination    )//
    template <size_t S, typename T>
    struct ElasticVector{
                
        //+    Member Variables    +//
        protected :
        T* _elements;
        

        //+    Static Functions    +//
        public :
        static constexpr uint16_t depth (Empty =_key_) noexcept;
        static constexpr size_t   size  (Empty =_key_) noexcept;
        

        //+    Member Functions    +//
        public :
        // Contruction Functions
                             ElasticVector (void)                       noexcept;
                             ElasticVector (const ElasticVector<S, T>&) noexcept;
                             ElasticVector (ElasticVector<S, T>&&)      noexcept;
                             ElasticVector (std::initializer_list<T>)   noexcept;
        template <typename... I>
        ElasticVector<S, T>& construct     (I...)                       noexcept;
        
        // Destruction Functions
                             ~ElasticVector (void) noexcept;
        ElasticVector<S, T>& destruct       (void) noexcept;

        
        // Reference functions
        template<uint16_t N>
              auto           ref        (void)                         const noexcept -> typename std::enable_if_t<(N==0), const T*>;
        const T*             ref        (uint16_t)                     const noexcept;
        const T*             spec       (void)                         const noexcept;
        #ifdef GROUPDATA_VECTOR_EXCEPTION
        const T&             operator() (const size_t&)                const;
        #else
        const T&             operator() (const size_t&)                const noexcept;
        #endif
              Range<const T> range      (const size_t& =S)             const noexcept;
              Range<const T> range      (const size_t&, const size_t&) const noexcept;


        // Access functions
        template<uint16_t N>
        auto                 path       (void)                         noexcept -> typename std::enable_if_t<(N==0), T*>;
        T*                   path       (uint16_t)                     noexcept; 
        T*                   data       (void)                         noexcept;
        #ifdef GROUPDATA_VECTOR_EXCEPTION
        T&                   operator[] (const size_t&);
        #else
        T&                   operator[] (const size_t&)                noexcept;
        #endif 
        ElasticVector<S, T>& operator=  (const ElasticVector<S, T>&)   noexcept;
        ElasticVector<S, T>& operator=  (ElasticVector<S, T>&&)        noexcept;
        Range<T>             range      (const size_t& =S)             noexcept;
        Range<T>             range      (const size_t&, const size_t&) noexcept;

        // Casting Functions
        template <size_t R, typename U>
        operator ElasticVector<R, U> () const noexcept;

    };




    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <size_t S, typename T>
    std::ostream& operator<<(std::ostream&, const gd::Vector<S, T>&) noexcept;
    template <size_t S, typename T>
    std::ostream& operator<<(std::ostream&, const gd::ElasticVector<S, T>&) noexcept;

}




//++++++++++++++++++++++++++//
//    Inline Definitions    //
//++++++++++++++++++++++++++//
#include "vector.inl"

#endif
