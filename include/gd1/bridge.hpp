#ifndef GROUPDATA_BRIDGE_HPP
#define GROUPDATA_BRIDGE_HPP

#include "./groupdata.hpp"
#include "./tuple.hpp"
#include "./array.hpp"


#ifdef GROUPDATA_BRIDGE_EXCEPTION
    #include "./exception/exception.hpp"
#endif

namespace gd{

    //++++++++++++++++++++++//
    //    Bridge Objects    //
    //++++++++++++++++++++++//
    //->    bridge.hpp, bridge.inl    <-//
    //(    gd::Bridge Void    )//
    template <size_t S, typename... As>
    struct Bridge{
       
        //+    Static Functions    +//
        static constexpr uint16_t depth (Empty =_key_) noexcept;


        //+   Member Functions    +//
        // Construction Functions
                          Bridge    (void)                    noexcept;
                          Bridge    (const Bridge<S, As...>&) noexcept;
                          Bridge    (Bridge<S, As...>&&)      noexcept;
        template <typename... I>
        Bridge<S, As...>& construct (I...)                    noexcept;
        
        // Destruction Functions
                          ~Bridge  (void) noexcept;
        Bridge<S, As...>& destruct (void) noexcept;
        
        // Access Function
        void operator= (const Bridge<S, As...>&) const noexcept;
        void operator= (Bridge<S, As...>&&)      const noexcept;
       
        // Casting Function
        template<size_t R, typename... Bs>
        operator Bridge<R, Bs...> () const noexcept;
    };


    
    //(    gd::Bridge<S, T, As...> Lamination for Lamination    )//
    template <size_t S, typename T, typename... As>
    struct Bridge<S, T, As...>{
        
        //+    Member Variables    +//
        public :
        Array<S, T>      _elements;
        Bridge<S, As...> _bridges;
        
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
                              Bridge    (void)                                            noexcept;
                              Bridge    (const Bridge<S, T, As...>&)                      noexcept;
                              Bridge    (Bridge<S, T, As...>&&)                           noexcept;
                              Bridge    (std::initializer_list<Tuple<T, As...>>)          noexcept; 
        template <uint16_t N>
        void                 _construct (Rank<N>, std::initializer_list<Tuple<T, As...>>) noexcept;
        void                 _construct (Rank<0>, std::initializer_list<Tuple<T, As...>>) noexcept;
        Bridge<S, T, As...>&  construct (void)                                            noexcept;
        Bridge<S, T, As...>&  construct (const Bridge&)                                   noexcept;
        Bridge<S, T, As...>&  construct (Bridge&&)                                        noexcept;
        Bridge<S, T, As...>&  construct (std::initializer_list<Tuple<T, As...>>)          noexcept;

        // Destruction Function
                              ~Bridge  (void) noexcept;
        Bridge<S, T, As...>&  destruct (void) noexcept;
        
        
        // Reference functions
        template <uint16_t N>
        const auto&         ref                  (void)                   const noexcept;
        template <uint16_t N>
        const auto&        _ref                  (Rank<N>)                const noexcept;
        const Array<S, T>& _ref                  (Rank<0>)                const noexcept; 
        template <uint16_t N>
              auto         _spec                 (Rank<N>)                const noexcept -> Tuple<const T*, const As*...>;
              auto         _spec                 (Rank<1>)                const noexcept -> Tuple<const T*>;
              auto          spec                 (void)                   const noexcept -> decltype(_spec(std::declval<Rank<sizeof...(As)+1>>()));
        template <uint16_t N>
              auto         _operator_parentheses (const size_t&, Rank<N>) const noexcept -> ElasticTuple<const T&, const As&...>;
              auto         _operator_parentheses (const size_t&, Rank<1>) const noexcept -> ElasticTuple<const T&>;
        #ifdef GROUPDATA_BRIDGE_EXCEPTION
              auto          operator()           (const size_t&)          const          -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #else
              auto          operator()           (const size_t&)          const noexcept -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #endif
        
        // Access functions
        template <uint16_t N>
        auto&                 path              (void)                       noexcept;
        template <uint16_t N>
        auto&                _path              (Rank<N>)                    noexcept;
        Array<S, T>&         _path              (Rank<0>)                    noexcept;
        template <uint16_t N>
        auto                 _data              (Rank<N>)                    noexcept -> Tuple<T*, As*...>;
        auto                 _data              (Rank<1>)                    noexcept -> Tuple<T*>;
        auto                  data              (void)                       noexcept -> decltype(_data(std::declval<Rank<sizeof...(As)+1>>()));
        template <uint16_t N>
        auto                 _operator_brackets (const size_t&, Rank<N>)     noexcept -> ElasticTuple<T&, As&...>;
        auto                 _operator_brackets (const size_t&, Rank<1>)     noexcept -> ElasticTuple<T&>;
        #ifdef GROUPDATA_BRIDGE_EXCEPTION
        auto                  operator[]        (const size_t&)                       -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #else 
        auto                  operator[]        (const size_t&)              noexcept -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #endif
        Bridge<S, T, As...>&  operator=         (const Bridge<S, T, As...>&) noexcept;
        Bridge<S, T, As...>&  operator=         (Bridge<S, T, As...>&&)      noexcept;

        // Casting Function
        template <uint16_t N, size_t R, typename U, typename... Bs>
        void _cast_bridge(Rank<N>, Bridge<R, U, Bs...>&) const noexcept;
        template <size_t R, typename U, typename... Bs>
        void _cast_bridge(Rank<0>, Bridge<R, U, Bs...>&) const noexcept;
        template <size_t R, typename U, typename... Bs>
        operator Bridge<R, U, Bs...> () const noexcept;
    };
    
    



    //(    gd::ElasticBridge Void    )//
    template <size_t S, typename... As>
    struct ElasticBridge{
       
        //+    Static Functions    +//
        static constexpr uint16_t depth (Empty =_key_) noexcept;


        //+   Member Functions    +//
        // Construction Functions
                                 ElasticBridge (void)                           noexcept;
                                 ElasticBridge (const ElasticBridge<S, As...>&) noexcept;
                                 ElasticBridge (ElasticBridge<S, As...>&&)      noexcept;
        template <typename... I>
        ElasticBridge<S, As...>& construct     (I...)                           noexcept;
        
        // Destruction Functions
                                 ~ElasticBridge (void) noexcept;
        ElasticBridge<S, As...>& destruct       (void) noexcept;
        
        // Access Function
        void operator= (const ElasticBridge<S, As...>&) const noexcept;
        void operator= (ElasticBridge<S, As...>&&)      const noexcept;
        
        template<size_t R, typename... Bs>
        operator ElasticBridge<R, Bs...> () const noexcept;
    };


    
    //(    gd::ElasticBridge<S, T, As...> Lamination for Lamination    )//
    template <size_t S, typename T, typename... As>
    struct ElasticBridge<S, T, As...>{
        
        //+    Member Variables    +//
        public :
        ElasticArray<S, T>      _elements;
        ElasticBridge<S, As...> _bridges;
        
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
                                     ElasticBridge (void)                                                             noexcept;
                                     ElasticBridge (const ElasticBridge<S, T, As...>&)                                noexcept;
                                     ElasticBridge (ElasticBridge<S, T, As...>&&)                                     noexcept;
                                     ElasticBridge (std::initializer_list<ElasticTuple<T, As...>>)                    noexcept; 
        template <typename U, uint16_t N>
        void                        _construct     (Rank<N>, std::initializer_list<ElasticTuple<T, As...>>, const U&) noexcept;
        template <typename U>
        void                        _construct     (Rank<0>, std::initializer_list<ElasticTuple<T, As...>>, const U&) noexcept;
        ElasticBridge<S, T, As...>&  construct     (void)                                                             noexcept;
        ElasticBridge<S, T, As...>&  construct     (const ElasticBridge&)                                             noexcept;
        ElasticBridge<S, T, As...>&  construct     (ElasticBridge&&)                                                  noexcept;
        ElasticBridge<S, T, As...>&  construct     (std::initializer_list<ElasticTuple<T, As...>>)                    noexcept;

        // Destruction Function
                              ~ElasticBridge  (void) noexcept;
        ElasticBridge<S, T, As...>&  destruct (void) noexcept;
        
        
        // Reference functions
        template <uint16_t N>
        const auto&                ref                  (void)                   const noexcept;
        template <uint16_t N>
        const auto&               _ref                  (Rank<N>)                const noexcept;
        const ElasticArray<S, T>& _ref                  (Rank<0>)                const noexcept; 
        template <uint16_t N>
              auto                _spec                 (Rank<N>)                const noexcept -> Tuple<const T*, const As*...>;
              auto                _spec                 (Rank<1>)                const noexcept -> Tuple<const T*>;
              auto                 spec                 (void)                   const noexcept -> decltype(_spec(std::declval<Rank<sizeof...(As)+1>>()));
        template <uint16_t N>
              auto                _operator_parentheses (const size_t&, Rank<N>) const noexcept -> ElasticTuple<const T&, const As&...>;
              auto                _operator_parentheses (const size_t&, Rank<1>) const noexcept -> ElasticTuple<const T&>;
        #ifdef GROUPDATA_BRIDGE_EXCEPTION
              auto                 operator()           (const size_t&)          const          -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #else
              auto                 operator()           (const size_t&)          const noexcept -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #endif
        
        // Access functions
        template <uint16_t N>
        auto&                        path              (void)                              noexcept;
        template <uint16_t N>
        auto&                       _path              (Rank<N>)                           noexcept;
        ElasticArray<S, T>&         _path              (Rank<0>)                           noexcept;
        template <uint16_t N>
        auto                        _data              (Rank<N>)                           noexcept -> Tuple<T*, As*...>;
        auto                        _data              (Rank<1>)                           noexcept -> Tuple<T*>;
        auto                         data              (void)                              noexcept -> decltype(_data(std::declval<Rank<sizeof...(As)+1>>()));
        template <uint16_t N>
        auto                        _operator_brackets (const size_t&, Rank<N>)            noexcept -> ElasticTuple<T&, As&...>;
        auto                        _operator_brackets (const size_t&, Rank<1>)            noexcept -> ElasticTuple<T&>;
        #ifdef GROUPDATA_BRIDGE_EXCEPTION
        auto                         operator[]        (const size_t&)                              -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #else 
        auto                         operator[]        (const size_t&)                     noexcept -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #endif
        ElasticBridge<S, T, As...>&  operator=         (const ElasticBridge<S, T, As...>&) noexcept;
        ElasticBridge<S, T, As...>&  operator=         (ElasticBridge<S, T, As...>&&)      noexcept;

        // Casting Function
        template <uint16_t N, size_t R, typename U, typename... Bs>
        void _cast_bridge(Rank<N>, ElasticBridge<R, U, Bs...>&) const noexcept;
        template <size_t R, typename U, typename... Bs>
        void _cast_bridge(Rank<0>, ElasticBridge<R, U, Bs...>&) const noexcept;
        template <size_t R, typename U, typename... Bs>
              operator ElasticBridge<R, U, Bs...> ()            const noexcept;
    };
    
    
    

    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <size_t S, typename T, typename... As>
    std::ostream& operator<<(std::ostream&, const gd::Bridge<S, T, As...>&) noexcept;
    template <size_t S, typename T, typename... As>
    std::ostream& operator<<(std::ostream&, const gd::ElasticBridge<S, T, As...>&) noexcept;
}




//++++++++++++++++++++++++++//
//    Inline Definitions    //
//++++++++++++++++++++++++++//
#include "bridge.inl"

#endif
