#ifndef CPTP_RANGE_HPP
#define CPTP_RANGE_HPP

#include "forward.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //------------------------//
    //    Type Declaration    //
    //------------------------//
    //(    cptp::Range Relocatable Strcuture   )//
    //-> forward.hpp range.hpp range.cpp
    struct Range{
        
        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        scalar min;
		scalar max;


        //+    Member Function    +//
        //_ Constructor
               Range     (void)                             noexcept;
               Range     (const Range&)                     =default;
               Range     (Range&&)                          =default;
               Range     (const scalar&, const scalar& max) noexcept;
        Range& construct (const scalar&, const scalar& max) noexcept;

        //_ Destructor
                ~Range  (void) =default;
        Range& destruct (void) noexcept;

        //_ Writer
        void info (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;        

        //_ Binary Operator
        Range& operator= (const Range&) =default;
        Range& operator= (Range&&)      =default;

    };



    //(    cptp::Range2D Relocatable Strcuture   )//
    //-> forward.hpp range.hpp range.cpp
    struct Range2D{
        
        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        Range x;
		Range y;


        //+    Member Function    +//
        //_ Constructor
                 Range2D   (void)                       =default;
                 Range2D   (const Range2D&)             =default;
                 Range2D   (Range2D&&)                  =default;
                 Range2D   (const Range&, const Range&) noexcept;
        Range2D& construct (const Range&, const Range&) noexcept;

        //_ Destructor
                ~Range2D  (void) =default;
        Range2D& destruct (void) noexcept;

        //_ Writer
        void info (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;        

        //_ Binary Operator
        Range2D& operator= (const Range2D&) =default;
        Range2D& operator= (Range2D&&)      =default;

    };

}
#endif
