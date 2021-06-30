#ifndef GROUPDATA_ALTERNATIVE_HPP
#define GROUPDATA_ALTERNATIVE_HPP

#include "./groupdata.hpp"
#ifdef GROUPDATA_ALTERNATIVE_EXCEPTION
    #include "./exception/exception.hpp"
#endif

namespace gd{

    //+++++++++++++++++++++++++++//
    //    Alternative Objects    //
    //+++++++++++++++++++++++++++//    
    //(    gd::Alternative Lamination for Lamination    )//
    template <typename... As>
    struct Alternative{
        
        //+    Static Value    +//
        public : 
        static constexpr Shadow<As...> shadows{ };
       

        //+    Static Functions    +//
        public : 
        static constexpr uint16_t depth (Empty =_key_) noexcept;
        static constexpr size_t   size  (Empty =_key_) noexcept;
        static constexpr size_t   width (Empty =_key_) noexcept;
        
        
        //+    Alias    +//
        template <uint16_t R>
        using Type = decltype(Shadow<As...>::template type<R>());

 
        //+    Member Variables    +//
        protected : 
        uint16_t _number;
        uint8_t  _element[width(_key_)];
        
       
        //+    Member Functions    +//
        public :
        // Construction Function
        Alternative (void)                      noexcept;
        Alternative (const Alternative<As...>&) noexcept;

#ifdef GROUPDATA_ALTERNATIVE_EXCEPTION
              Alternative (uint16_t);
        template <uint16_t R>
        bool _construct   (Rank<R>, uint16_t)               noexcept;
        bool _construct   (Rank<sizeof...(As)-1>, uint16_t) noexcept;
#else
              Alternative (uint16_t) noexcept;
#endif
#ifdef GROUPDATA_ALTERNATIVE_EXCEPTION
        template <typename T>
              Alternative (uint16_t, const T&);
        template <uint16_t R, typename T>
        bool _construct   (Rank<R>, uint16_t, const T&)               noexcept;
        template <typename T>
        bool _construct   (Rank<sizeof...(As)-1>, uint16_t, const T&) noexcept;
#else
        template <typename T>
        Alternative (uint16_t, const T&) noexcept;
#endif
        auto construct   (void)                      noexcept -> Alternative<As...>&;
        auto construct   (const Alternative<As...>&) noexcept -> Alternative<As...>&;
        
        template <uint16_t R>
        auto construct   (void)                      noexcept -> std::enable_if_t<(R<sizeof...(As)), Alternative<As...>&>;
        template <uint16_t R, typename U>
        auto construct   (const U&)                  noexcept -> std::enable_if_t<std::is_same_v<Type<R>, U>, Alternative<As...>&>;
       
        Alternative<As...>& construct (uint16_t) noexcept(noexcept(Alternative(std::declval<uint16_t>())));
        
        template <typename T>
        Alternative<As...>& construct (uint16_t, const T&) noexcept(noexcept(Alternative(std::declval<uint16_t>(), std::declval<T>())));
        

        // Destruction Function
                            ~Alternative (void)    noexcept;
        template <uint16_t R>
        Alternative<As...>&  destruct    (void)    noexcept;
       

        // Reference Functions
        uint16_t                   number     (void)   const noexcept;
        template <uint16_t R>
              auto                 path       (void)   const noexcept -> const Type<R>&;
        const Alternative<As...>*  data       (void)   const noexcept;
        const Alternative<As...>&  operator[] (size_t) const noexcept;

        // Access Functions
        template <uint16_t R>
        auto                 path       (void)   noexcept  -> const Type<R>&;
        Alternative<As...>*  data       (void)   noexcept;
        Alternative<As...>&  operator[] (size_t) noexcept;
        

        // Ternary Operator
        Alternative<As...>& operator= (const Alternative<As...>&) noexcept;
        Alternative<As...>& operator= (Alternative<As...>&&)      noexcept;

    };
    
    
    
    //(    gd::ElasticAlternative Lamination for Lamination    )//
    template <typename... As>
    struct ElasticAlternative{
         
        //+    Static Value    +//
        public : 
        static constexpr Shadow<As...> shadows{ };
       

        //+    Static Functions    +//
        public : 
        static constexpr uint16_t depth (Empty =_key_) noexcept;
        static constexpr size_t   size  (Empty =_key_) noexcept;
        static constexpr size_t   width (Empty =_key_) noexcept;
        
        
        //+    Alias    +//
        template <uint16_t R>
        using Type = decltype(Shadow<As...>::template type<R>());

 
        //+    Member Variables    +//
        protected : 
        uint16_t _number;
        uint8_t  _element[width(_key_)];

       
        //+    Member Functions    +//
        public :
        // Construction Function
              ElasticAlternative (void)                                      noexcept;
              ElasticAlternative (const ElasticAlternative<As...>&)          noexcept;
              ElasticAlternative (ElasticAlternative<As...>&&)               noexcept;
        
#ifdef GROUPDATA_ALTERNATIVE_EXCEPTION
              ElasticAlternative (uint16_t);
#else
              ElasticAlternative (uint16_t) noexcept;
#endif
        template <uint16_t R>
        bool _construct   (Rank<R>, uint16_t) noexcept;
        bool _construct   (Rank<0>, uint16_t) noexcept;

#ifdef GROUPDATA_ALTERNATIVE_EXCEPTION
        template <typename T>
              ElasticAlternative (uint16_t, const T&);
#else
        template <typename T>
              ElasticAlternative (uint16_t, const T&) noexcept;
#endif
        template <uint16_t R, typename T>
        bool _construct   (Rank<R>, uint16_t, const T&) noexcept;
        template <typename T>
        bool _construct   (Rank<0>, uint16_t, const T&) noexcept;             

#ifdef GROUPDATA_ALTERNATIVE_EXCEPTION
        template <typename T>
              ElasticAlternative (uint16_t, T&&);
#else
        template <typename T>
              ElasticAlternative (uint16_t, T&&) noexcept;
#endif
        template <uint16_t R, typename T>
        bool _construct   (Rank<R>, uint16_t, T&&)               noexcept;
        template <typename T>
        bool _construct   (Rank<0>, uint16_t, T&&) noexcept;             


        auto  construct          (void)                                      noexcept -> ElasticAlternative<As...>&;
        
        auto  construct          (const ElasticAlternative<As...>&)          noexcept -> ElasticAlternative<As...>&;
        template <uint16_t R>
        auto _construct          (Rank<R>, const ElasticAlternative<As...>&) noexcept -> void;
        auto _construct          (Rank<0>, const ElasticAlternative<As...>&) noexcept -> void;
        
        auto  construct          (ElasticAlternative<As...>&&)               noexcept -> ElasticAlternative<As...>&;
        template <uint16_t R>
        auto _construct          (Rank<R>, ElasticAlternative<As...>&&)      noexcept -> void;
        auto _construct          (Rank<0>, ElasticAlternative<As...>&&)      noexcept -> void;
        
        template <uint16_t R>
        auto  construct          (void)                                      noexcept -> ElasticAlternative<As...>&;
        template <uint16_t R, typename U>
        auto _construct          (void)                                      noexcept -> void;
        
        template <uint16_t R, typename U>
        auto  construct          (const U&)                                  noexcept -> std::enable_if_t<std::is_same_v<Type<R>, U>, ElasticAlternative<As...>&>;
        
        template <uint16_t R, typename U>
        auto  construct          (U&&)                                       noexcept -> std::enable_if_t<std::is_same_v<Type<R>, U>, ElasticAlternative<As...>&>;
        
        ElasticAlternative<As...>& construct (uint16_t)           noexcept(noexcept(ElasticAlternative(std::declval<uint16_t>())));
        
        template <typename T>
        ElasticAlternative<As...>& construct (uint16_t, const T&) noexcept(noexcept(ElasticAlternative(std::declval<uint16_t>(), std::declval<T>())));

        auto  reconstruct (const ElasticAlternative<As...>&) noexcept -> ElasticAlternative<As...>&;
        auto  reconstruct (ElasticAlternative<As...>&&)      noexcept -> ElasticAlternative<As...>&;
        template <uint16_t R>
        auto  reconstruct (void)                             noexcept -> ElasticAlternative<As...>&;
        template <uint16_t R, typename U>
        auto  reconstruct (const U&)                         noexcept -> std::enable_if_t<std::is_same_v<Type<R>, U>, ElasticAlternative<As...>&>;
        template <uint16_t R, typename U>
        auto  reconstruct (U&&)                              noexcept -> std::enable_if_t<std::is_same_v<Type<R>, U>, ElasticAlternative<As...>&>;
        
        ElasticAlternative<As...>& reconstruct (uint16_t)           noexcept(noexcept(ElasticAlternative(std::declval<uint16_t>())));
        template <typename T>
        ElasticAlternative<As...>& reconstruct (uint16_t, const T&) noexcept(noexcept(ElasticAlternative(std::declval<uint16_t>(), std::declval<T>())));
       

        // Destruction Function
                                   ~ElasticAlternative (void)    noexcept;
        ElasticAlternative<As...>&  destruct           (void)    noexcept;
        template <uint16_t R>
        void                       _destruct           (Rank<R>) noexcept;
        void                       _destruct           (Rank<0>) noexcept;
        template <uint16_t R, typename U>
        void                       _destruct           (void)    noexcept;
       

        // Reference Functions
        uint16_t                          number     (void)   const noexcept;
        template<uint16_t R>
              auto                        path       (void)   const noexcept -> const decltype(Shadow<As...>::template type<R>())&;
        const ElasticAlternative<As...>*  data       (void)   const noexcept;
        const ElasticAlternative<As...>&  operator() (size_t) const noexcept;

        // Access Functions
        template<uint16_t R>
        auto                        path       (void)   noexcept -> decltype(Shadow<As...>::template type<R>())&;
        ElasticAlternative<As...>*  data       (void)   noexcept;
        ElasticAlternative<As...>&  operator[] (size_t) noexcept;

        // Ternary Operator
        ElasticAlternative<As...>&  operator=      (const ElasticAlternative<As...>&)          noexcept;
        template <uint16_t R>
        void                       _operator_equal (Rank<R>, const ElasticAlternative<As...>&) noexcept;
        void                       _operator_equal (Rank<0>, const ElasticAlternative<As...>&) noexcept;
        ElasticAlternative<As...>&  operator=      (ElasticAlternative<As...>&&)               noexcept;
        template <uint16_t R>
        void                       _operator_equal (Rank<R>, ElasticAlternative<As...>&&)      noexcept;
        void                       _operator_equal (Rank<0>, ElasticAlternative<As...>&&)      noexcept;

    };

    
    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <typename... As>
    std::ostream&  operator<<          (std::ostream&, const gd::Alternative<As...>&)                 noexcept;
    template <uint16_t R, typename... As>
    void          _operator_left_shift (Rank<R>, std::ostream&, const gd::Alternative<As...>&)        noexcept;
    template <typename... As>
    void          _operator_left_shift (Rank<0>, std::ostream&, const gd::Alternative<As...>&)        noexcept;
    template <typename... As>
    std::ostream&  operator<<          (std::ostream&, const gd::ElasticAlternative<As...>&)          noexcept;
    template <uint16_t R, typename... As>
    void          _operator_left_shift (Rank<R>, std::ostream&, const gd::ElasticAlternative<As...>&) noexcept;
    template <typename... As>
    void          _operator_left_shift (Rank<0>, std::ostream&, const gd::ElasticAlternative<As...>&) noexcept;

    
}



//++++++++++++++++++++++++++//
//    Inline Definitions    //
//++++++++++++++++++++++++++//
#include "alternative.inl"

#endif
