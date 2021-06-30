#ifndef GROUPDATA_BANDLE_HPP
#define GROUPDATA_BANDLE_HPP

#include "./groupdata.hpp"
#include "./tuple.hpp"
#include "./vector.hpp"


#ifdef GROUPDATA_BANDLE_EXCEPTION
    #include "./exception/exception.hpp"
#endif

namespace gd{

    //++++++++++++++++++++++//
    //    Bandle Objects    //
    //++++++++++++++++++++++//
    //->    bandle.hpp, bandle.inl    <-//
    //(    gd::Bandle Void    )//
    template <size_t S, typename... As>
    struct Bandle{
       
        //+    Static Functions    +//
        static constexpr uint16_t depth (Empty =_key_) noexcept;


        //+   Member Functions    +//
        // Construction Functions
                          Bandle    (void)                                noexcept;
                          Bandle    (const Bandle<S, As...>&)             noexcept;
                          Bandle    (Bandle<S, As...>&&)                  noexcept;
        template <typename... I>
        Bandle<S, As...>& construct (I...)                                noexcept;
 
        // Destruction Functions
                          ~Bandle  (void) noexcept;
        Bandle<S, As...>& destruct (void) noexcept;
       
        // Access Functions
        void operator= (const Bandle<S, As...>&) const noexcept;
        void operator= (Bandle<S, As...>&&)      const noexcept;

        // Casting Function
        template<size_t R, typename... Bs>
        operator Bandle<R, Bs...> () const noexcept;
    };


    
    //(    gd::Bandle<S, T, As...> Lamination for Lamination    )//
    template <size_t S, typename T, typename... As>
    struct Bandle<S, T, As...>{
        
        //+    Member Variables    +//
        protected :
        Vector<S, T>     _elements;
        Bandle<S, As...> _bandles;
        
        //+    Static Functions    +//
        public :
        template <typename U>
        static constexpr auto   _depth (int32_t, Empty =_key_) noexcept -> typename std::invoke_result_t<decltype(&U::depth), Empty>;
        template <typename U>
        static constexpr auto   _depth (int16_t, Empty =_key_) noexcept -> int16_t;
        static constexpr auto    depth (Empty =_key_)          noexcept -> decltype(_depth<T>(0, _key_));
        static constexpr size_t  size  (Empty =_key_)          noexcept;

        //+    Member Functions    +//
        public :
        
        // Contruction Functions
                              Bandle    (void)                                            noexcept;
                              Bandle    (const Bandle<S, T, As...>&)                      noexcept;
                              Bandle    (Bandle<S, T, As...>&&)                           noexcept;
                              Bandle    (std::initializer_list<Tuple<T, As...>>)          noexcept; 
        template <uint16_t N>
        void                 _construct (Rank<N>, std::initializer_list<Tuple<T, As...>>) noexcept;
        void                 _construct (Rank<0>, std::initializer_list<Tuple<T, As...>>) noexcept;
        Bandle<S, T, As...>&  construct (void)                                            noexcept;
        Bandle<S, T, As...>&  construct (const Bandle&)                                   noexcept;
        Bandle<S, T, As...>&  construct (Bandle&&)                                        noexcept;
        Bandle<S, T, As...>&  construct (std::initializer_list<Tuple<T, As...>>)          noexcept;

        // Destruction Function
                              ~Bandle  (void) noexcept;
        Bandle<S, T, As...>&  destruct (void) noexcept;
        
        
        // Reference functions
        template <uint16_t N>
        const auto&          ref                  (void)                   const noexcept;
        template <uint16_t N>
        const auto&         _ref                  (Rank<N>)                const noexcept;
        const Vector<S, T>& _ref                  (Rank<0>)                const noexcept; 
        template <uint16_t N>
              auto          _spec                 (Rank<N>)                const noexcept -> Tuple<const T*, const As*...>;
              auto          _spec                 (Rank<1>)                const noexcept -> Tuple<const T*>;
              auto           spec                 (void)                   const noexcept -> decltype(_spec(std::declval<Rank<sizeof...(As)+1>>()));
        template <uint16_t N>
              auto          _operator_parentheses (const size_t&, Rank<N>) const noexcept -> ElasticTuple<const T&, const As&...>;
        
              auto          _operator_parentheses (const size_t&, Rank<1>) const noexcept -> ElasticTuple<const T&>;
        #ifdef GROUPDATA_BANDLE_EXCEPTION
              auto           operator()           (const size_t&)          const          -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #else
              auto           operator()           (const size_t&)          const noexcept -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #endif
    
        
        // Access functions
        template <uint16_t N>
        auto&                 path              (void)                       noexcept;
        template <uint16_t N>
        auto&                _path              (Rank<N>)                    noexcept;
        Vector<S, T>&        _path              (Rank<0>)                    noexcept;
        template <uint16_t N>
        auto                 _data              (Rank<N>)                    noexcept -> Tuple<T*, As*...>;
        auto                 _data              (Rank<1>)                    noexcept -> Tuple<T*>;
        auto                  data              (void)                       noexcept -> decltype(_data(std::declval<Rank<sizeof...(As)+1>>()));
        template <uint16_t N>
        auto                 _operator_brackets (const size_t&, Rank<N>)     noexcept -> ElasticTuple<T&, As&...>;
        auto                 _operator_brackets (const size_t&, Rank<1>)     noexcept -> ElasticTuple<T&>;
        #ifdef GROUPDATA_BANDLE_EXCEPTION
        auto                  operator[]        (const size_t&)                       -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #else
        auto                  operator[]        (const size_t&)              noexcept -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #endif
        Bandle<S, T, As...>&  operator=         (const Bandle<S, T, As...>&) noexcept;
        Bandle<S, T, As...>&  operator=         (Bandle<S, T, As...>&&)      noexcept;
        

        // Casting Function
        template <uint16_t N, size_t R, typename U, typename... Bs>
        void _cast_bandle                  (Rank<N>, Bandle<R, U, Bs...>&) const noexcept;
        template <size_t R, typename U, typename... Bs>
        void _cast_bandle                  (Rank<0>, Bandle<R, U, Bs...>&) const noexcept;
        template <size_t R, typename U, typename... Bs>
              operator Bandle<R, U, Bs...> (void)                          const noexcept;
    };
    
    
    
    //(    gd::ElasticBandle Void    )//
    template <size_t S, typename... As>
    struct ElasticBandle{
       
        //+    Static Functions    +//
        static constexpr uint16_t depth (Empty =_key_) noexcept;


        //+   Member Functions    +//
        // Construction Functions
                          ElasticBandle    (void)                                noexcept;
                          ElasticBandle    (const ElasticBandle<S, As...>&)             noexcept;
                          ElasticBandle    (ElasticBandle<S, As...>&&)                  noexcept;
        template <typename... I>
        ElasticBandle<S, As...>& construct (I...)                                noexcept;
 
        // Destruction Functions
                          ~ElasticBandle  (void) noexcept;
        ElasticBandle<S, As...>& destruct (void) noexcept;
       
        // Access Functions
        void operator= (const ElasticBandle<S, As...>&) const noexcept;
        void operator= (ElasticBandle<S, As...>&&)      const noexcept;

        // Casting Function
        template<size_t R, typename... Bs>
        operator ElasticBandle<R, Bs...> () const noexcept;
    };


    
    //(    gd::ElasticBandle<S, T, As...> Lamination for Lamination    )//
    template <size_t S, typename T, typename... As>
    struct ElasticBandle<S, T, As...>{
        
        //+    Member Variables    +//
        protected :
        ElasticVector<S, T>     _elements;
        ElasticBandle<S, As...> _bandles;
        
        //+    Static Functions    +//
        public :
        template <typename U>
        static constexpr auto   _depth (int32_t, Empty =_key_) noexcept -> typename std::invoke_result_t<decltype(&U::depth), Empty>;
        template <typename U>
        static constexpr auto   _depth (int16_t, Empty =_key_) noexcept -> int16_t;
        static constexpr auto    depth (Empty =_key_)          noexcept -> decltype(_depth<T>(0, _key_));
        static constexpr size_t  size  (Empty =_key_)          noexcept;

        //+    Member Functions    +//
        public :
        
        // Contruction Functions
                                     ElasticBandle (void)                                                             noexcept;
                                     ElasticBandle (const ElasticBandle<S, T, As...>&)                                noexcept;
                                     ElasticBandle (ElasticBandle<S, T, As...>&&)                                     noexcept;
                                     ElasticBandle (std::initializer_list<ElasticTuple<T, As...>>)                    noexcept; 
        template <uint16_t N, typename U>
        void                        _construct     (Rank<N>, std::initializer_list<ElasticTuple<T, As...>>, const U&) noexcept;
        template <typename U>
        void                        _construct     (Rank<0>, std::initializer_list<ElasticTuple<T, As...>>, const U&) noexcept;
        ElasticBandle<S, T, As...>&  construct     (void)                                                             noexcept;
        ElasticBandle<S, T, As...>&  construct     (const ElasticBandle&)                                             noexcept;
        ElasticBandle<S, T, As...>&  construct     (ElasticBandle&&)                                                  noexcept;
        ElasticBandle<S, T, As...>&  construct     (std::initializer_list<ElasticTuple<T, As...>>)                    noexcept;

        // Destruction Function
                                    ~ElasticBandle (void) noexcept;
        ElasticBandle<S, T, As...>& destruct       (void) noexcept;
        
        
        // Reference functions
        template <uint16_t N>
        const auto&                 ref                  (void)                   const noexcept;
        template <uint16_t N>
        const auto&                _ref                  (Rank<N>)                const noexcept;
        const ElasticVector<S, T>& _ref                  (Rank<0>)                const noexcept; 
        template <uint16_t N>
              auto                 _spec                 (Rank<N>)                const noexcept -> Tuple<const T*, const As*...>;
              auto                 _spec                 (Rank<1>)                const noexcept -> Tuple<const T*>;
              auto                  spec                 (void)                   const noexcept -> decltype(_spec(std::declval<Rank<sizeof...(As)+1>>()));
        template <uint16_t N>
              auto                 _operator_parentheses (const size_t&, Rank<N>) const noexcept -> ElasticTuple<const T&, const As&...>;
              auto                 _operator_parentheses (const size_t&, Rank<1>) const noexcept -> ElasticTuple<const T&>;
        #ifdef GROUPDATA_BANDLE_EXCEPTION
              auto                  operator()           (const size_t&)          const          -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #else
              auto                  operator()           (const size_t&)          const noexcept -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #endif
    
        
        // Access functions
        template <uint16_t N>
        auto&                        path              (void)                              noexcept;
        template <uint16_t N>
        auto&                       _path              (Rank<N>)                           noexcept;
        ElasticVector<S, T>&        _path              (Rank<0>)                           noexcept;
        template <uint16_t N>
        auto                        _data              (Rank<N>)                           noexcept -> Tuple<T*, As*...>;
        auto                        _data              (Rank<1>)                           noexcept -> Tuple<T*>;
        auto                         data              (void)                              noexcept -> decltype(_data(std::declval<Rank<sizeof...(As)+1>>()));
        template <uint16_t N>
        auto                        _operator_brackets (const size_t&, Rank<N>)            noexcept -> ElasticTuple<T&, As&...>;
        auto                        _operator_brackets (const size_t&, Rank<1>)            noexcept -> ElasticTuple<T&>;
        #ifdef GROUPDATA_BANDLE_EXCEPTION
        auto                         operator[]        (const size_t&)                              -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #else
        auto                         operator[]        (const size_t&)                     noexcept -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #endif
        ElasticBandle<S, T, As...>&  operator=         (const ElasticBandle<S, T, As...>&) noexcept;
        ElasticBandle<S, T, As...>&  operator=         (ElasticBandle<S, T, As...>&&)      noexcept;
        

        // Casting Function
        template <uint16_t N, size_t R, typename U, typename... Bs>
        void _cast_bandle                         (Rank<N>, ElasticBandle<R, U, Bs...>&) const noexcept;
        template <size_t R, typename U, typename... Bs>
        void _cast_bandle                         (Rank<0>, ElasticBandle<R, U, Bs...>&) const noexcept;
        template <size_t R, typename U, typename... Bs>
              operator ElasticBandle<R, U, Bs...> (void)                                 const noexcept;
    };

    

    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <size_t S, typename T, typename... As>
    std::ostream& operator<<(std::ostream&, const gd::Bandle<S, T, As...>&) noexcept;
    template <size_t S, typename T, typename... As>
    std::ostream& operator<<(std::ostream&, const gd::ElasticBandle<S, T, As...>&) noexcept;

}




//++++++++++++++++++++++++++//
//    Inline Definitions    //
//++++++++++++++++++++++++++//
#include "bandle.inl"

#endif
