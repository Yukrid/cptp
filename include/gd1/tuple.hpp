#ifndef GROUPDATA_TUPLE_HPP
#define GROUPDATA_TUPLE_HPP

#include "./groupdata.hpp"

namespace gd{

    //+++++++++++++++++++++//
    //    Tuple Objects    //
    //+++++++++++++++++++++//
    //(    gd::Tuple<As...> Void    )//
    template <typename... As>
    struct Tuple{
        
        //+    Member Functions    +//
        // Construction Function
                      Tuple     (void)                noexcept;
                      Tuple     (const Tuple<As...>&) noexcept;
                      Tuple     (Tuple<As...>&&)      noexcept;
        template <typename... I>
        Tuple<As...>& construct (I...)                noexcept;
        
        // Destruction Functions
                      ~Tuple   (void) noexcept;
        Tuple<As...>& destruct (void) noexcept;

        // Access Function
        void operator= (const Tuple<As...>&) const noexcept;
        
        // Casting Function
        template <typename... Bs>
        operator Tuple<Bs...> () const noexcept;
    
    };


    //(    gd::Tuple<T, As...> Lamination for Lamination    )//
    template <typename T, typename... As>
    struct Tuple<T, As...>{
        
        //+    Member Variables    +//
        T            element;
        Tuple<As...> tuples;

       
        //+    Static Functions    +//
        public : 
        static constexpr uint16_t depth (Empty =_key_) noexcept;
        static constexpr size_t   size  (Empty =_key_) noexcept;


        //+    Member Functions    +//
        public :
        // Construction Function
                         Tuple     (void)                          noexcept;
                         Tuple     (const Tuple<T, As...>&)        noexcept;
                         Tuple     (Tuple<T, As...>&&)             noexcept;
                         Tuple     (const T&, const As&...)        noexcept;
                         Tuple     (const T&, const Tuple<As...>&) noexcept;
        template <typename... I>
        Tuple<T, As...>& construct (I...) noexcept;

        // Destruction Function
                         ~Tuple   (void) noexcept;
        Tuple<T, As...>& destruct (void) noexcept;


        // Reference Functions
        template<uint16_t R>
        const auto&             path       (void)    const noexcept;
        template<uint16_t R>
        const auto&            _path       (Rank<R>) const noexcept;
        const T&               _path       (Rank<0>) const noexcept; 
        const Tuple<T, As...>*  data       (void)    const noexcept;
        const Tuple<T, As...>&  operator[] (size_t)  const noexcept;

        
        // Access Functions
        template<uint16_t R>
        auto&             path       (void)                   noexcept; 
        template<uint16_t R>
        auto&            _path       (Rank<R>)                noexcept; 
        T&               _path       (Rank<0>)                noexcept;
        Tuple<T, As...>*  data       (void)                   noexcept;
        Tuple<T, As...>&  operator[] (size_t)                 noexcept;
        Tuple<T, As...>&  operator=  (const Tuple<T, As...>&) noexcept;
        Tuple<T, As...>&  operator=  (Tuple<T, As...>&&)      noexcept;

        // Casting Functions
        template <uint16_t N, typename U, typename... Bs>
        void _cast_tuple(Rank<N>, Tuple<U, Bs...>&) const noexcept;
        template <typename U, typename... Bs>
        void _cast_tuple(Rank<0>, Tuple<U, Bs...>&) const noexcept;
        template <typename U, typename... Bs>
        operator Tuple<U, Bs...> () const noexcept;
    
    };
    
    
    
    //(    gd::ElasticTuple<As...> Void    )//
    template <typename... As>
    struct ElasticTuple{
        
        //+    Member Functions    +//
        // Construction Function
                             ElasticTuple (void)                       noexcept;
                             ElasticTuple (const ElasticTuple<As...>&) noexcept;
                             ElasticTuple (ElasticTuple<As...>&&)      noexcept;
        template <typename... I>
        ElasticTuple<As...>& construct    (I...)                       noexcept;
        
        // Destruction Functions
                      ~ElasticTuple   (void) noexcept;
        ElasticTuple<As...>& destruct (void) noexcept;

        // Access Function
        void operator= (const ElasticTuple<As...>&) const noexcept;
        
        // Casting Function
        template <typename... Bs>
        operator ElasticTuple<Bs...> () const noexcept;
    
    };


    //(    gd::ElasticTuple<T, As...> Aggregated Lamination for Lamination    )//
    template <typename T, typename... As>
    struct ElasticTuple<T, As...>{
        
        //+    Member Variables    +//
        T            element;
        ElasticTuple<As...> tuples;

       
        //+    Static Functions    +//
        public : 
        static constexpr uint16_t depth (Empty =_key_) noexcept;
        static constexpr size_t   size  (Empty =_key_) noexcept;


        //+    Member Functions    +//
        public :
        // Construction Function
                         ElasticTuple     (void)                                 noexcept;
                         ElasticTuple     (const ElasticTuple<T, As...>&)        noexcept;
                         ElasticTuple     (ElasticTuple<T, As...>&&)             noexcept;
                         ElasticTuple     (const T&, const As&...)               noexcept;
                         ElasticTuple     (const T&, const ElasticTuple<As...>&) noexcept;
        template <typename... I>
        ElasticTuple<T, As...>& construct (I...) noexcept;

        // Destruction Function
                         ~ElasticTuple   (void) noexcept;
        ElasticTuple<T, As...>& destruct (void) noexcept;


        // Reference Functions
        template<uint16_t R>
        const auto&             path        (void)          const noexcept;
        template<uint16_t R>
        const auto&            _path        (Rank<R>)       const noexcept;
        const T&               _path        (Rank<0>)       const noexcept; 
        const ElasticTuple<T, As...>*  data       (void)   const noexcept;
        const ElasticTuple<T, As...>&  operator() (size_t) const noexcept;

        
        // Access Functions
        template<uint16_t R>
        auto&             path       (void)                                 noexcept; 
        template<uint16_t R>
        auto&            _path       (Rank<R>)                              noexcept; 
        T&               _path       (Rank<0>)                              noexcept;
        ElasticTuple<T, As...>*  data       (void)                          noexcept;
        ElasticTuple<T, As...>& operator[] (size_t)                        noexcept;
        ElasticTuple<T, As...>& operator=       (const ElasticTuple<T, As...>&)                          noexcept;
        ElasticTuple<T, As...>& operator=       (ElasticTuple<T, As...>&&)                               noexcept; 
        template <typename... Bs>
        ElasticTuple<T, As...>& operator=       (const ElasticTuple<std::remove_reference_t<T>, Bs...>&) noexcept;
        template <typename... Bs>
        ElasticTuple<T, As...>& operator=       (ElasticTuple<std::remove_reference_t<T>, Bs...>&&)      noexcept;


        // Casting Functions
        template <uint16_t N, typename U, typename... Bs>
        void _cast_tuple(Rank<N>, ElasticTuple<U, Bs...>&) const noexcept;
        template <typename U, typename... Bs>
        void _cast_tuple(Rank<0>, ElasticTuple<U, Bs...>&) const noexcept;
        template <typename U, typename... Bs>
        operator ElasticTuple<U, Bs...> ()                 const noexcept;
        operator ElasticTuple<std::remove_reference<T>, As...> () const noexcept;
    };
    

    
    
    
    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <typename... As>
    std::ostream& operator<<(std::ostream&, const gd::Tuple<As...>&)           noexcept;
    template <typename T, typename... As>
    std::ostream& operator<<(std::ostream&, const gd::Tuple<T, As...>&)        noexcept;
    template <typename... As>
    std::ostream& operator<<(std::ostream&, const gd::ElasticTuple<As...>&)    noexcept;
    template <typename T, typename... As>
    std::ostream& operator<<(std::ostream&, const gd::ElasticTuple<T, As...>&) noexcept;

}



//++++++++++++++++++++++++++//
//    Inline Definitions    //
//++++++++++++++++++++++++++//
#include "tuple.inl"

#endif
