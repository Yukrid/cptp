#ifndef CPTP_DATA_HPP
#define CPTP_DATA_HPP

#include "forward.hpp"
#include <fstream>
#include <sstream>

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    cptp::Data<T> Relocatable Class Template    )//
    //-> forward.hpp data.hpp data.inl
    template <typename T>
    struct Data{

        //+    Member Variables    +//
        private:
        //->    Data Family    <-//
        const T*         _begin;
        const T*         _end;
        size_t           _length;

        //+     Member Function    +//
        public:
        //_ Constructor
              Data      (void)                    noexcept;
              Data      (const Data&)             =default;
              Data      (Data&&)                  =default;
              Data      (const T*, const T*)      noexcept;
              Data      (const T*, const size_t&) noexcept;
        Data& construct (const T*, const T*)      noexcept;
        Data& construct (const T*, const size_t&) noexcept;

        //_ Destructor
              ~Data    (void) noexcept;
        Data& destruct (void) noexcept;

        //_ Writer
        void info (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;

        //_ Referencer
        const T*      begin  (void) const noexcept;
        const T*      end    (void) const noexcept;
        const size_t& length (void) const noexcept;

        //_ Ternary Operator
        Data& operator= (const Data&) =default;
        Data& operator= (Data&&)      =default;
        
    };
    
    


    //(    cptp::Data2D<T,U> Relocatable Memory    )//
    //-> forward.hpp data.hpp data.cpp
    struct Data2D{

        //+   Alias   +//
        using Series2D  =gd::Table<scalar, scalar>;
        using Separators=gd::List<size_t>;

        //+    Member Type    +//
        //(    cptp::Data2D::Index Enumeration    )//
        //-> forward.hpp data.hpp data.inl data.cpp
        enum Index : bool{
            INDEX   
        };

        //+    Member Variable    +//
        private:
        //->    Data2D Family    <-//
        Series2D   _datas;
        Separators _separators;

        //+     Member Function    +//
        public:
        //_ Constructor
                       Data2D      (void)                                                            =default;
                       Data2D      (const Data2D&)                                                   =default;
                       Data2D      (Data2D&&)                                                        =default;
                       Data2D      (std::ifstream&, uint16_t =0, uint16_t =1)                        noexcept;
                       Data2D      (std::ifstream&, Index, uint16_t)                                 noexcept;
                       Data2D      (std::ifstream&, uint16_t, Index)                                 noexcept;
        template <typename T, typename U>
        inline         Data2D      (const Data<T>&, const Data<U>&, const Separators& =Separators()) noexcept;
        template <typename U>
        inline         Data2D      (Index, const Data<U>&, const Separators& =Separators())          noexcept;
        template <typename T>
        inline         Data2D      (const Data<T>&, Index, const Separators& =Separators())          noexcept;
               Data2D& construct   (void)                                                            noexcept;
        template <typename T, typename U>
        inline Data2D& construct   (const Data<T>&, const Data<U>&, const Separators& =Separators()) noexcept;
        template <typename U>
        inline Data2D& construct   (Index, const Data<U>&, const Separators& =Separators())          noexcept;
        template <typename T>
        inline Data2D& construct   (const Data<T>&, Index, const Separators& =Separators())          noexcept;
        template <typename T, typename U>
        inline Data2D& reconstruct (const Data<T>&, const Data<U>&, const Separators& =Separators()) noexcept;
        template <typename U>
        inline Data2D& reconstruct (Index, const Data<U>&, const Separators& =Separators())          noexcept;
        template <typename T>
        inline Data2D& reconstruct (const Data<T>&, Index, const Separators& =Separators())          noexcept;
        

        //_ Destructor
                ~Data2D   (void) =default;
        Data2D&  destruct (void) noexcept;

        //_ Writer
        void info (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;
        
        //_ Accessor
        Series2D& datas (void) noexcept;

        //_ Referencer
        const Series2D&   datas     (void) const noexcept;
        const size_t&     length    (void) const noexcept;
        const Separators& separator (void) const noexcept;

        //_ Constant Function
        size_t _memory (void) const noexcept;
        
        //_ Ternary Operator
        Data2D& operator= (const Data2D&) =default;
        Data2D& operator= (Data2D&&)      =default;
    };



    //-------------//
    //    Alias    //
    //-------------//
    using Data2DArray=gd::ElasticList<Data2D>;
    using DataSet    =gd::ElasticList<Data2DArray>;
}

#include "data.inl"

#endif
