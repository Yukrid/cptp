#ifndef GROUPDATA_GROUP_HPP
#define GROUPDATA_GROUP_HPP

#include "./groupdata.hpp"

#ifdef GROUPDATA_GROUP_EXCEPTION
    #include "./exception/exception.hpp"
#endif

namespace gd{

    //+++++++++++++++++++//
    //    Group Types    //
    //+++++++++++++++++++//
    //->    group.hpp, group.inl    <-//
    //(    gd::Group<T, D> Structure Template for Structure    )//
    template <typename T, uint16_t D>
    struct Group{
                
        //+    Member Variables    +//
        protected :
        T _elements[D];
        

        //+    Static Functions    +//
        public :
        static constexpr uint16_t depth (Empty =_key_) noexcept;
        static constexpr size_t   size  (Empty =_key_) noexcept;
        

        //+    Member Functions    +//
        public :
        // Contruction Functions
                     Group     (void)                     noexcept;
                     Group     (const Group<T, D>&)       noexcept;
                     Group     (Group<T, D>&&)            noexcept;
                     Group     (std::initializer_list<T>) noexcept;
        template <typename... I>
        Group<T, D>& construct (I...)                     noexcept;
     
        // Destruction Functions
                     ~Group   (void) noexcept;
        Group<T, D>& destruct (void) noexcept;    

        // Reference Functions
        template<uint16_t N>
              auto           path       (void)               const noexcept -> typename std::enable_if_t<(N<D), const T&>;
        #ifdef GROUPDATA_GROUP_EXCEPTION
        const T&             path       (uint16_t)           const;
        #else
        const T&             path       (uint16_t)           const noexcept;
        #endif
        template<uint16_t N>
              auto           data       (void)               const noexcept -> typename std::enable_if_t<(N<D), const T*>;
        const Group<T, D>&   operator[] (const size_t&)      const noexcept;

        // Access Functions
        template<uint16_t N>
        auto         path (void)     noexcept -> typename std::enable_if_t<(N<D), T&>; 
        #ifdef GROUPDATA_GROUP_EXCEPTION
        T&           path       (uint16_t);
        #else
        T&           path       (uint16_t)           noexcept;
        #endif     
        template<uint16_t N>
        auto         data       (void)               noexcept -> typename std::enable_if_t<(N<D), T*>;
        Group<T, D>& operator[] (const size_t&)      noexcept;
        Group<T, D>& operator=  (const Group<T, D>&) noexcept;
        Group<T, D>& operator=  (Group<T, D>&&)      noexcept;

        // Casting Functions
        template <typename U, uint16_t E>
        operator Group<U, E> () const noexcept;
    };



    //(    gd::ElasticGroup<T, D> Lamination Template for Class    )//
    template <typename T, uint16_t D>
    struct ElasticGroup{
                
        //+    Member Variables    +//
        protected :
        T _elements[D];
        

        //+    Static Functions    +//
        public :
        static constexpr uint16_t depth (Empty =_key_) noexcept;
        static constexpr size_t   size  (Empty =_key_) noexcept;
        

        //+    Member Functions    +//
        public :
        // Contruction Functions
                            ElasticGroup (void)                      noexcept;
                            ElasticGroup (const ElasticGroup<T, D>&) noexcept;
                            ElasticGroup (ElasticGroup<T, D>&&)      noexcept;
                            ElasticGroup (std::initializer_list<T>)  noexcept;
        template <typename... I>
        ElasticGroup<T, D>& construct    (I...)                      noexcept;
     
        // Destruction Functions
                     ~ElasticGroup   (void) noexcept;
        ElasticGroup<T, D>& destruct (void) noexcept;    

        // Reference Functions
        template<uint16_t N>
              auto                path       (void)                     const noexcept -> typename std::enable_if_t<(N<D), const T&>;
        #ifdef GROUPDATA_GROUP_EXCEPTION
        const T&                  path       (uint16_t)                 const;
        #else
        const T&                  path       (uint16_t)                 const noexcept;
        #endif
        template<uint16_t N>
              auto                data       (void)                     const noexcept -> typename std::enable_if_t<(N<D), const T*>;
        const ElasticGroup<T, D>& operator[] (const size_t&)            const noexcept;

        // Access Functions
        template<uint16_t N>
        auto                path       (void)                     noexcept -> typename std::enable_if_t<(N<D), T&>; 
        #ifdef GROUPDATA_GROUP_EXCEPTION
        T&                  path       (uint16_t);
        #else
        T&                  path       (uint16_t)                  noexcept;
        #endif     
        template<uint16_t N>
        auto                data       (void)                      noexcept -> typename std::enable_if_t<(N<D), T*>;
        ElasticGroup<T, D>& operator[] (const size_t&)             noexcept;
        ElasticGroup<T, D>& operator=  (const ElasticGroup<T, D>&) noexcept;
        ElasticGroup<T, D>& operator=  (ElasticGroup<T, D>&&)      noexcept;

        // Casting Functions
        template <typename U, uint16_t E>
        operator ElasticGroup<U, E> () const noexcept;
    };



    //++++++++++++++++++++++++++++++++//
    //    Attached Global Function    //
    //++++++++++++++++++++++++++++++++//
    template <typename T, uint16_t D>
    std::ostream& operator<<(std::ostream&, const gd::Group<T, D>&) noexcept;
    template <typename T, uint16_t D>
    std::ostream& operator<<(std::ostream&, const gd::ElasticGroup<T, D>&) noexcept;

}



//++++++++++++++++++++++++++//
//    Inline Definitions    //
//++++++++++++++++++++++++++//
#include "group.inl"

#endif
