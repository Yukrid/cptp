
//#define GROUPDATA_TABLE_EXCEPTION
//#define GROUPDATA_TABLE_WARNING

#ifndef GROUPDATA_TABLE_HPP
#define GROUPDATA_TABLE_HPP

#include "./groupdata.hpp"
#include "./tuple.hpp"
#include "./view.hpp"


#ifdef GROUPDATA_TABLE_EXCEPTION
    #include "./exception/exception.hpp"
#endif
#ifdef GROUPDATA_TABLE_EXCEPTION
    #include "./warning/warning.hpp"
#endif

namespace gd{

    //++++++++++++++++++++++//
    //    Table Objects    //
    //++++++++++++++++++++++//
    //->    table.hpp, table.inl    <-//
    //(    gd::Table Lamination for Lamination    )//
    template <typename... As>
    struct Table{

        //+    Member Variables    +//
        protected :
        size_t _size;
        size_t _capacity;


        //+    Static Functions    +//
        public :
        static constexpr uint16_t depth (Empty =_key_) noexcept;


        //+   Member Functions    +//
        // Construction Functions
        public :
                      Table     (void)                noexcept;
                      Table     (const size_t&)       noexcept;
                      Table     (const Table<As...>&) noexcept;
                      Table     (Table<As...>&&)      noexcept;
        template <typename... I>
        Table<As...>& construct (I...)                noexcept;
        
        // Destruction Functions
        public :
                       ~Table   (void) noexcept;
        Table<As ...>& destruct (void) noexcept;

        // Reference Functions
        public :
        const size_t& size      (void) const noexcept;
        const size_t& capacity  (void) const noexcept;

        // Access Functions
        public :
        void _operator_equal (const Table<As...>&) noexcept;
        void _operator_equal (Table<As...>&&)      noexcept;
        
        public :
        size_t& _protSize     (void) noexcept;
        size_t& _protCapacity (void) noexcept;

        // Edit Functions
        public : 
        bool          _resize   (const size_t&)                      noexcept;
        bool          _reserve  (const size_t&)                      noexcept;
        bool          _reduce   (const size_t&)                      noexcept;
        bool          _insert   (const size_t&, const Tuple<As...>&) noexcept;
        bool          _pushBack (const Tuple<As...>&)                noexcept;
        bool          _moveBack (Tuple<As...>&&)                     noexcept;
        Table<As...>&  memset   (int32_t)                            noexcept;
    };
    

    
    //(    gd::Table<T, As...> Lamination for Lamination    )//
    template <typename T, typename... As>
    struct Table<T, As...>{
        
        //+    Member Variables    +//
        protected :
        T*           _elements;
        Table<As...> _tables;
        
        //+    Static Functions    +//
        public :
        template <typename U>
        static constexpr auto   _depth (int32_t, Empty =_key_) noexcept -> typename std::invoke_result_t<decltype(&U::depth), Empty>;
        template <typename U>
        static constexpr auto   _depth (int16_t, Empty =_key_) noexcept -> int16_t;
        static constexpr auto    depth (Empty =_key_)          noexcept -> decltype(_depth<T>(0, _key_));

        //+    Member Functions    +//
        // Contruction Functions
        public :
        #ifdef GROUPDATA_TABLE_EXCEPTION
                          Table     (void);
                          Table     (const size_t&);
                          Table     (const Table<T, As...>&);
                          Table     (std::initializer_list<Tuple<T, As...>>); 
        template <typename... I>
        Table<T, As...>&  construct (I...);
        #else
                          Table      (void)                                           noexcept;
                          Table      (const size_t&)                                  noexcept;
                          Table      (const Table<T, As...>&)                         noexcept;
                          Table      (std::initializer_list<Tuple<T, As...>>)         noexcept; 
                template <typename... I>
        Table<T, As...>&  construct (I...)                                            noexcept;
        #endif
        template <uint16_t N>
        void             _construct (Rank<N>, std::initializer_list<Tuple<T, As...>>) noexcept;
        void             _construct (Rank<0>, std::initializer_list<Tuple<T, As...>>) noexcept;
                          Table     (Table<T, As...>&&)                               noexcept;

        // Destruction Function
        public :
                         ~Table   (void) noexcept;
        Table<T, As...>& destruct (void) noexcept;
        
        // Reference functions
        public :
        template <uint16_t N>
        const auto     path                 (void)                   const noexcept;
        template <uint16_t N>
        const auto    _path                 (Rank<N>)                const noexcept;
        const View<T> _path                 (Rank<0>)                const noexcept;
        template <uint16_t N>
              auto    _cdata                (Rank<N>)                const noexcept -> Tuple<const T*, const As*...>;
              auto    _cdata                (Rank<1>)                const noexcept -> Tuple<const T*>;
              auto     data                 (void)                   const noexcept -> decltype(_cdata(std::declval<Rank<sizeof...(As)+1>>()));
        template <uint16_t N>
              auto    _operator_parentheses (const size_t&, Rank<N>) const noexcept -> ElasticTuple<const T&, const As&...>;
              auto    _operator_parentheses (const size_t&, Rank<1>) const noexcept -> ElasticTuple<const T&>; 
        #ifdef GROUPDATA_TABLE_EXCEPTION
              auto     operator[]           (const size_t&)          const          -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #else
              auto     operator[]           (const size_t&)          const noexcept -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #endif
        const size_t&  size                 (void)                   const noexcept;
        const size_t&  capacity             (void)                   const noexcept;
       
        
        // Access functions
        public :
        template <uint16_t N>
        auto              path              (void)                   noexcept;
        template <uint16_t N>
        auto             _path              (Rank<N>)                noexcept;
        View <T>         _path              (Rank<0>)                noexcept;
        template <uint16_t N>
        auto             _data              (Rank<N>)                noexcept -> Tuple<T*, As*...>;
        auto             _data              (Rank<1>)                noexcept -> Tuple<T*>;
        auto              data              (void)                   noexcept -> decltype(_data(std::declval<Rank<sizeof...(As)+1>>()));
        template <uint16_t N>
        auto             _operator_brackets (const size_t&, Rank<N>) noexcept -> ElasticTuple<T&, As&...>;
        auto             _operator_brackets (const size_t&, Rank<1>) noexcept -> ElasticTuple<T&>;
        #ifdef GROUPDATA_TABLE_EXCEPTION
        auto              operator[]        (const size_t&)                   -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #else
        auto              operator[]        (const size_t&)          noexcept -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #endif
        void             _operator_equal    (const Table<T, As...>&) noexcept;
        void             _operator_equal    (Table<T, As...>&&)      noexcept;
        Table<T, As...>&  operator=         (const Table<T, As...>&) noexcept;
        Table<T, As...>&  operator=         (Table<T, As...>&&)      noexcept;

        public :
        size_t&          _protSize          (void)                   noexcept;
        size_t&          _protCapacity      (void)                   noexcept;


        // Edit Functions
        public :
        bool           resize      (const size_t&)                         noexcept;
        bool          _resize      (const size_t&)                         noexcept;
        bool           reserve     (const size_t&)                         noexcept;
        bool          _reserve     (const size_t&)                         noexcept;
        bool           reduce      (const size_t&)                         noexcept;
        bool          _reduce      (const size_t&)                         noexcept;
        bool           insert      (const size_t&, const Tuple<T, As...>&) noexcept;
        bool          _insert      (const size_t&, const Tuple<T, As...>&) noexcept;
        bool           pushBack    (const Tuple<T, As...>&)                noexcept;
        bool          _pushBack    (const Tuple<T, As...>&)                noexcept;
        bool           moveBack    (Tuple<T, As...>&&)                     noexcept;
        bool          _moveBack    (Tuple<T, As...>&&)                     noexcept;
        Table<As...>&  memset      (int32_t)                               noexcept;
    
        // Casting Function
        public :
        template <uint16_t N, typename U, typename... Bs>
        void _cast_table               (Rank<N>, Table<U, Bs...>&) const noexcept;
        template <typename U, typename... Bs>
        void _cast_table               (Rank<0>, Table<U, Bs...>&) const noexcept;
        template <typename U, typename... Bs>
              operator Table<U, Bs...> (void)                      const noexcept;
    
    };
    
    
    
    //(    gd::ElasticTable Lamination for Lamination    )//
    template <typename... As>
    struct ElasticTable{

        //+    Member Variables    +//
        protected :
        size_t _size;
        size_t _capacity;


        //+    Static Functions    +//
        public :
        static constexpr uint16_t depth (Empty =_key_) noexcept;


        //+   Member Functions    +//
        // Construction Functions
        public :
                             ElasticTable (void)                       noexcept;
                             ElasticTable (const size_t&)              noexcept;
                             ElasticTable (const ElasticTable<As...>&) noexcept;
                             ElasticTable (ElasticTable<As...>&&)      noexcept;
        template <typename... I>
        ElasticTable<As...>& construct    (I...)                       noexcept;
        
        // Destruction Functions
        public :
                              ~ElasticTable (void) noexcept;
        ElasticTable<As ...>& destruct      (void) noexcept;

        // Reference Functions
        public :
        const size_t& size     (void) const noexcept;
        const size_t& capacity (void) const noexcept;

        // Access Functions
        public :
        void _operator_equal (const ElasticTable<As...>&) const noexcept;
        void _operator_equal (ElasticTable<As...>&&)      const noexcept;
        
        public :
        size_t& _protSize     (void) noexcept;
        size_t& _protCapacity (void) noexcept;

        // Edit Functions
        public : 
        bool                   resize   (const size_t&)                             noexcept;
        bool                   reserve  (const size_t&)                             noexcept;
        bool                   reduce   (const size_t&)                             noexcept;
        bool                  _insert   (const size_t&, const ElasticTuple<As...>&) noexcept;
        bool                  _pushBack (const ElasticTuple<As...>&)                noexcept;
        bool                  _moveBack (ElasticTuple<As...>&&)                     noexcept;
        ElasticTable<As...>&   memset   (int32_t)                                   noexcept;
    };
    

    
    //(    gd::ElasticTable<T, As...> Lamination for Lamination    )//
    template <typename T, typename... As>
    struct ElasticTable<T, As...>{
        
        //+    Member Variables    +//
        protected :
        T*                  _elements;
        ElasticTable<As...> _tables;
        
        //+    Static Functions    +//
        public :
        template <typename U>
        static constexpr auto   _depth (int32_t, Empty =_key_) noexcept -> typename std::invoke_result_t<decltype(&U::depth), Empty>;
        template <typename U>
        static constexpr auto   _depth (int16_t, Empty =_key_) noexcept -> int16_t;
        static constexpr auto    depth (Empty =_key_)          noexcept -> decltype(_depth<T>(0, _key_));

        //+    Member Functions    +//
        // Contruction Functions
        public :
        #ifdef GROUPDATA_TABLE_EXCEPTION
                                 ElasticTable (void);
                                 ElasticTable (const size_t&);
                                 ElasticTable (const ElasticTable<T, As...>&);
                                 ElasticTable (std::initializer_list<ElasticTuple<T, As...>>); 
        template <typename... I>
        ElasticTable<T, As...>&  construct    (I...);
        #else
                                 ElasticTable (void)                                                   noexcept;
                                 ElasticTable (const size_t&)                                          noexcept;
                                 ElasticTable (const ElasticTable<T, As...>&)                          noexcept;
                                 ElasticTable (std::initializer_list<ElasticTuple<T, As...>>)          noexcept; 
                template <typename... I>
        ElasticTable<T, As...>&  construct    (I...)                                                   noexcept;
        #endif
        template <uint16_t N, typename U>
        void                    _construct    (Rank<N>, std::initializer_list<ElasticTuple<T, As...>>, const U&) noexcept;
        template <typename U>
        void                    _construct    (Rank<0>, std::initializer_list<ElasticTuple<T, As...>>, const U&) noexcept;
                                ElasticTable  (ElasticTable<T, As...>&&)                               noexcept;

        // Destruction Function
        public :
                                ~ElasticTable (void) noexcept;
        ElasticTable<T, As...>& destruct      (void) noexcept;
        
        // Reference functions
        public :
        template <uint16_t N>
        const auto            path                  (void)                   const noexcept;
        template <uint16_t N>
        const auto           _path                  (Rank<N>)                const noexcept;
        const ElasticView<T> _path                  (Rank<0>)                const noexcept;
        template <uint16_t N>
              auto           _cdata                 (Rank<N>)                const noexcept -> Tuple<const T*, const As*...>;
              auto           _cdata                 (Rank<1>)                const noexcept -> Tuple<const T*>;
              auto            data                 (void)                   const noexcept -> decltype(_cdata(std::declval<Rank<sizeof...(As)+1>>()));
        template <uint16_t N>
              auto           _operator_parentheses (const size_t&, Rank<N>) const noexcept -> ElasticTuple<const T&, const As&...>;
              auto           _operator_parentheses (const size_t&, Rank<1>) const noexcept -> ElasticTuple<const T&>; 
        #ifdef GROUPDATA_TABLE_EXCEPTION
              auto            operator[]           (const size_t&)          const          -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #else
              auto            operator[]           (const size_t&)          const noexcept -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #endif
        const size_t&         size                 (void)                   const noexcept;
        const size_t&         capacity             (void)                   const noexcept;
       
        
        // Access functions
        public :
        template <uint16_t N>
        auto                     path              (void)                          noexcept;
        template <uint16_t N>
        auto                    _path              (Rank<N>)                       noexcept;
        ElasticView <T>         _path              (Rank<0>)                       noexcept;
        template <uint16_t N>
        auto                    _data              (Rank<N>)                       noexcept -> Tuple<T*, As*...>;
        auto                    _data              (Rank<1>)                       noexcept -> Tuple<T*>;
        auto                     data              (void)                          noexcept -> decltype(_data(std::declval<Rank<sizeof...(As)+1>>()));
        template <uint16_t N>
        auto                    _operator_brackets (const size_t&, Rank<N>)        noexcept -> ElasticTuple<T&, As&...>;
        auto                    _operator_brackets (const size_t&, Rank<1>)        noexcept -> ElasticTuple<T&>;
        #ifdef GROUPDATA_TABLE_EXCEPTION
        auto                     operator[]        (const size_t&)                   -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #else
        auto                     operator[]        (const size_t&)                 noexcept -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()));
        #endif
        ElasticTable<T, As...>& _operator_equal    (const ElasticTable<T, As...>&) noexcept;
        ElasticTable<T, As...>& _operator_equal    (ElasticTable<T, As...>&&)      noexcept;
        ElasticTable<T, As...>&  operator=         (const ElasticTable<T, As...>&) noexcept;
        ElasticTable<T, As...>&  operator=         (ElasticTable<T, As...>&&)      noexcept;

        public :
        size_t& _protSize     (void) noexcept;
        size_t& _protCapacity (void) noexcept;


        // Edit Functions
        public :
        bool  resize   (const size_t&)                                noexcept;
        bool _resize   (const size_t&)                                noexcept;
        bool  reserve  (const size_t&)                                noexcept;
        bool _reserve  (const size_t&)                                noexcept;
        bool  reduce   (const size_t&)                                noexcept;
        bool _reduce   (const size_t&)                                noexcept;
        bool  insert   (const size_t&, const ElasticTuple<T, As...>&) noexcept;
        bool _insert   (const size_t&, const ElasticTuple<T, As...>&) noexcept;
        bool  pushBack (const ElasticTuple<T, As...>&)                noexcept;
        bool _pushBack (const ElasticTuple<T, As...>&)                noexcept;
        bool  moveBack (ElasticTuple<T, As...>&&)                     noexcept;
        bool _moveBack (ElasticTuple<T, As...>&&)                     noexcept;
    

        // Casting Function
        public :
        template <uint16_t N, typename U, typename... Bs>
        void _cast_table                      (Rank<N>, ElasticTable<U, Bs...>&) const noexcept;
        template <typename U, typename... Bs>
        void _cast_table                      (Rank<0>, ElasticTable<U, Bs...>&) const noexcept;
        template <typename U, typename... Bs>
              operator ElasticTable<U, Bs...> (void)                             const noexcept;
    };

    
    
    

    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <typename T, typename... As>
    std::ostream& operator<<(std::ostream&, const gd::Table<T, As...>&)        noexcept;
    template <typename T, typename... As>
    std::ostream& operator<<(std::ostream&, const gd::ElasticTable<T, As...>&) noexcept;
}




//++++++++++++++++++++++++++//
//    Inline Definitions    //
//++++++++++++++++++++++++++//
#include "table.inl"

#endif
