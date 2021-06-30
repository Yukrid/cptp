#ifndef GROUPDATA_LIST_HPP
#define GROUPDATA_LIST_HPP

#include "./groupdata.hpp"

   
#ifdef GROUPDATA_LIST_EXCEPTION
    #include "./exception/exception.hpp"
#endif
#ifdef GROUPDATA_LIST_WARNING
    #include "./warning/warning.hpp"
#endif


namespace gd{

    //++++++++++++++++++++//
    //    List Objects    //
    //++++++++++++++++++++//
    //->    list.hpp, list.inl    <-//
    //(    gd::List Structure for Lamination    )//
    template <typename T>
    struct List{
                
        //+    Member Variables    +//
        protected :
        size_t _size;
        size_t _capacity;
        T*     _elements;
        

        //+    Static Functions    +//
        public :
        static constexpr uint16_t depth (Empty =_key_) noexcept;
        

        //+    Member Functions    +//
        public :
        // Contruction Functions
        #ifdef GROUPDATA_LIST_EXCEPTION
                 List      (void);
                 List      (const size_t&);
                 List      (const List<T>&);
                 List      (const View<T>&); //->    list.hpp, consversion.inl    <-//
                 List      (std::initializer_list<T>);
        template <typename... I>
        List<T>& construct (I...);
        #else
                 List      (void)                     noexcept;
                 List      (const size_t&)            noexcept;
                 List      (const List<T>&)           noexcept;
                 List      (const View<T>&)           noexcept; //->    list.hpp, consversion.inl    <-//
                 List      (std::initializer_list<T>) noexcept;
        template <typename... I>
        List<T>& construct (I...)                     noexcept;
        #endif
                 List      (List<T>&&)                noexcept;

        // Destruction Functions
                 ~List    (void) noexcept;
        List<T>& destruct (void) noexcept;
 
        // Reference functions
        template<uint16_t N>
        auto                path       (void)                         const noexcept -> typename std::enable_if_t<(N==0), const T*>;
        const T*            path       (uint16_t)                     const noexcept;
        const T*            data       (void)                         const noexcept;
        #ifdef GROUPDATA_LIST_EXCEPTION
        const T&            operator[] (const size_t&)                const;
        #else
        const T&            operator[] (const size_t&)                const noexcept;
        #endif
              Range<const T> range     (void)                         const noexcept;
              Range<const T> range     (const size_t&)                const noexcept;
              Range<const T> range     (const size_t&, const size_t&) const noexcept;
        const size_t&        size      (Empty =_key_)                 const noexcept;
        const size_t&        capacity  (Empty =_key_)                 const noexcept;

        // Access Functions
        template<uint16_t N>
        auto     path       (void)                         noexcept -> typename std::enable_if_t<(N==0), T*>;
        T*       path       (uint16_t)                     noexcept; 
        T*       data       (void)                         noexcept;
        #ifdef GROUPDATA_LIST_EXCEPTION
        T&       operator[] (const size_t&);
        #else
        T&       operator[] (const size_t&)                noexcept;
        #endif
        #ifdef GROUPDATA_LIST_EXCEPTION
        List<T>& operator=  (const List<T>&);
        List<T>& operator=  (const View<T>&); //->    list.hpp, consversion.inl    <-//
        #else
        List<T>& operator=  (const List<T>&)               noexcept;
        List<T>& operator=  (const View<T>&)               noexcept; //->    list.hpp, consversion.inl    <-//
        #endif
        List<T>& operator=  (List<T>&&)                    noexcept;
        Range<T> range      (void)                         noexcept;
        Range<T> range      (const size_t&)                noexcept;
        Range<T> range      (const size_t&, const size_t&) noexcept;

        // Edit Functions
        bool     resize      (const size_t &)           noexcept;
        bool     reserve     (const size_t &)           noexcept;
        bool     reduce      (const size_t &)           noexcept;
        bool     insert      (const size_t &, const T&) noexcept;
        bool     pushBack    (const T&)                 noexcept;
        bool     pushBack    (T&&)                      noexcept;
        template <typename... I>
        bool     emplaceBack (I...)                     noexcept;
        List<T>& memset      (int32_t)                  noexcept;
        
        // Casting Function
        template <typename U>
        operator List<U> () const noexcept;
        
        //->    list.hpp, consversion.inl    <-//
        operator View<T> () noexcept;
    };
    
    
    

    //(    gd::ElasticList Class for Class    )//
    template <typename T>
    struct ElasticList{
                
        //+    Member Variables    +//
        protected :
        size_t _size;
        size_t _capacity;
        T*     _elements;
        

        //+    Static Functions    +//
        public :
        static constexpr uint16_t depth (Empty =_key_) noexcept;
        

        //+    Member Functions    +//
        public :
        // Contruction Functions
        #ifdef GROUPDATA_LIST_EXCEPTION
                 ElasticList      (void);
                 ElasticList      (const size_t&);
                 ElasticList      (const ElasticList<T>&);
                 ElasticList      (const View<T>&); //->    list.hpp, consversion.inl    <-//
                 ElasticList      (std::initializer_list<T>);
        template <typename... I>
        ElasticList<T>& construct (I...);
        #else
                 ElasticList      (void)                     noexcept;
                 ElasticList      (const size_t&)            noexcept;
                 ElasticList      (const ElasticList<T>&)    noexcept;
                 ElasticList      (const View<T>&)           noexcept; //->    list.hpp, consversion.inl    <-//
                 ElasticList      (std::initializer_list<T>) noexcept;
        template <typename... I>
        ElasticList<T>& construct (I...)                     noexcept;
        #endif
                 ElasticList      (ElasticList<T>&&)         noexcept;
       
        // Destruction Functions
                        ~ElasticList (void) noexcept;
        ElasticList<T>& destruct     (void) noexcept;
 
        // Reference functions
        template<uint16_t N>
              auto           path       (void)                         const noexcept -> typename std::enable_if_t<(N==0), const T*>;
        const T*             path       (uint16_t)                     const noexcept;
        const T*             data       (void)                         const noexcept;
        #ifdef GROUPDATA_LIST_EXCEPTION
        const T&             operator[] (const size_t&)                const;
        #else
        const T&             operator[] (const size_t&)                const noexcept;
        #endif
              Range<const T> range      (void)                         const noexcept;
              Range<const T> range      (const size_t&)                const noexcept;
              Range<const T> range      (const size_t&, const size_t&) const noexcept;
        const size_t&        size       (Empty =_key_)                 const noexcept;
        const size_t&        capacity   (Empty =_key_)                 const noexcept;

        // Access Functions
        template<uint16_t N>
        auto            path       (void)                         noexcept -> typename std::enable_if_t<(N==0), T*>;
        T*              path       (uint16_t)                     noexcept; 
        T*              data       (void)                         noexcept;
        #ifdef GROUPDATA_LIST_EXCEPTION
        T&              operator[] (const size_t&);
        #else
        T&              operator[] (const size_t&)                noexcept;
        #endif
        #ifdef GROUPDATA_LIST_EXCEPTION
        ElasticList<T>& operator=  (const ElasticList<T>&);
        ElasticList<T>& operator=  (const View<T>&);                        //->    list.hpp, consversion.inl    <-//
        #else
        ElasticList<T>& operator=  (const ElasticList<T>&)        noexcept;
        ElasticList<T>& operator=  (const View<T>&)               noexcept; //->    list.hpp, consversion.inl    <-//
        #endif
        ElasticList<T>& operator=  (ElasticList<T>&&)             noexcept;
        Range<T>        range      (void)                         noexcept;
        Range<T>        range      (const size_t&)                noexcept;
        Range<T>        range      (const size_t&, const size_t&) noexcept;

        // Edit Functions
        bool            resize      (const size_t &)           noexcept;
        bool            reserve     (const size_t &)           noexcept;
        bool            reduce      (const size_t &)           noexcept;
        bool            insert      (const size_t &, const T&) noexcept;
        bool            pushBack    (const T&)                 noexcept;
        bool            pushBack    (T&&)                      noexcept;
        template <typename... I>
        bool            emplaceBack (I...)                     noexcept;
        ElasticList<T>& memset   (int32_t)                     noexcept;
        
        // Casting Function
        template <typename U>
        operator ElasticList<U> () const noexcept;
        
        //->    list.hpp, consversion.inl    <-//
        operator View<T> () noexcept;
    };





    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <typename T>
    std::ostream& operator<<(std::ostream&, const gd::List<T>&) noexcept;
    template <typename T>
    std::ostream& operator<<(std::ostream&, const gd::ElasticList<T>&) noexcept;

}




//++++++++++++++++++++++++++//
//    Inline Definitions    //
//++++++++++++++++++++++++++//
#include "list.inl"
#include "conversion.inl"

#endif
