#ifndef GROUPDATA_VIEW_HPP
#define GROUPDATA_VIEW_HPP

#include "./groupdata.hpp"

   
#ifdef GROUPDATA_VIEW_EXCEPTION
    #include "./exception/exception.hpp"
#endif
#ifdef GROUPDATA_VIEW_WARNING
    #include "./warning/warning.hpp"
#endif


namespace gd{

    //++++++++++++++++++++//
    //    View Objects    //
    //++++++++++++++++++++//
    //->    view.hpp, view.inl    <-//
    //(    gd::View Structure for Lamination    )//
    template <typename T>
    struct View{
                
        //+    Member Variables    +//
        protected :
        const size_t&       _size;
        const size_t&       _capacity;
              T*      const _elements;
        

        //+    Static Functions    +//
        public :
        static constexpr uint16_t depth (Empty =_key_) noexcept;
        

        //+    Member Functions    +//
        public :
        // Contruction Functions
                 View      (const size_t&, const size_t&, T*) noexcept;
                 View      (const View<T>&)    noexcept;
                 View      (View<T>&&)=delete;
        template <typename... I>
        View<T>& construct (I...)              noexcept;

        // Destruction Functions
                 ~View    (void) noexcept;
        View<T>& destruct (void) noexcept;
 
        // Reference functions
        template<uint16_t N>
        auto           path       (void)                         const noexcept -> typename std::enable_if_t<(N==0), const T*>;
        const T*       path       (uint16_t)                     const noexcept;       
        const T*       data       (void)                         const noexcept;
        #ifdef GROUPDATA_VIEW_EXCEPTION
        const T&       operator[] (const size_t&)                const;
        #else
        const T&       operator[] (const size_t&)                const noexcept;
        #endif
        const size_t&  size       (Empty =_key_)                 const noexcept;
        const size_t&  capacity   (Empty =_key_)                 const noexcept;
        Range<const T> range      (void)                         const noexcept;
        Range<const T> range      (const size_t&)                const noexcept;
        Range<const T> range      (const size_t&, const size_t&) const noexcept;

        // Access Functions
        template<uint16_t N>
        auto path       (void)               noexcept -> typename std::enable_if_t<(N==0), T*>;
        T*   path       (uint16_t)           noexcept; 
        T*   data       (void)               noexcept;
        #ifdef GROUPDATA_VIEW_EXCEPTION
        T&       operator[] (const size_t&);
        #else
        T&       operator[] (const size_t&)  noexcept;
        #endif
        Range<T> range      (void)                         noexcept;
        Range<T> range      (const size_t&)                noexcept;
        Range<T> range      (const size_t&, const size_t&) noexcept;

        // Edit Functions
        View<T>& memset (uint32_t)      noexcept;
    };
    
    
    
    //(    gd::ElasticView Structure for Lamination    )//
    template <typename T>
    struct ElasticView{
                
        //+    Member Variables    +//
        protected :
        const size_t&       _size;
        const size_t&       _capacity;
              T*      const _elements;
        

        //+    Static Functions    +//
        public :
        static constexpr uint16_t depth (Empty =_key_) noexcept;
        

        //+    Member Functions    +//
        public :
        // Contruction Functions
                        ElasticView (const size_t&, const size_t&, T*) noexcept;
                        ElasticView (const ElasticView<T>&)            noexcept;
                        ElasticView (ElasticView<T>&&)=delete;
        template <typename... I>
        ElasticView<T>& construct   (I...)                             noexcept;

        // Destruction Functions
                 ~ElasticView    (void) noexcept;
        ElasticView<T>& destruct (void) noexcept;
 
        // Reference functions
        template<uint16_t N>
              auto    path        (void)                         const noexcept -> typename std::enable_if_t<(N==0), const T*>;
        const T*      path        (uint16_t)                     const noexcept;
        const T*      data        (void)                         const noexcept;
        #ifdef GROUPDATA_VIEW_EXCEPTION
        const T&       operator[] (const size_t&)                const;
        #else
        const T&       operator[] (const size_t&)                const noexcept;
        #endif
        const size_t&  size       (Empty =_key_)                 const noexcept;
        const size_t&  capacity   (Empty =_key_)                 const noexcept;
        Range<const T> range      (void)                         const noexcept;
        Range<const T> range      (const size_t&)                const noexcept;
        Range<const T> range      (const size_t&, const size_t&) const noexcept;

        // Access Functions
        template<uint16_t N>
        auto     path       (void)           noexcept -> typename std::enable_if_t<(N==0), T*>;
        T*       path       (uint16_t)       noexcept; 
        T*       data       (void)           noexcept;
        #ifdef GROUPDATA_VIEW_EXCEPTION
        T&       operator[] (const size_t&);
        #else
        T&       operator[] (const size_t&)  noexcept;
        #endif
        Range<T> range      (void)                         noexcept;
        Range<T> range      (const size_t&)                noexcept;
        Range<T> range      (const size_t&, const size_t&) noexcept;
   
    };




    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <typename T>
    std::ostream& operator<<(std::ostream&, const gd::View<T>&) noexcept;
    template <typename T>
    std::ostream& operator<<(std::ostream&, const gd::ElasticView<T>&) noexcept;
}




//++++++++++++++++++++++++++//
//    Inline Definitions    //
//++++++++++++++++++++++++++//
#include "view.inl"
#include "conversion.inl"

#endif
