#ifndef CPTP_TITLE_HPP
#define CPTP_TITLE_HPP

#include <limits>
#include <numbers>
#include "forward.hpp"
#include "position.hpp"
#include "vec2.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    cptp::Title Structure    )//
    //-> forward.hpp title.hpp title.cpp
    struct Title{
 

        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        std::string string;
        Position    position;
        Vec2        margin;
        double      point;


        //+     Member Function    +//
        //_ Constructor
               Title (void)          noexcept;
               Title (const Title&) =default;
               Title (Title&&)      =default;
    
        //_ Destructor
        ~Title (void) =default;

        //_ Writer
        void info  (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;
   
        //_ Constant Function
        size_t _memory (void) const noexcept;
   
        //_ Binary Operator
        Title& operator= (const Title&) =default;
        Title& operator= (Title&&)      =default;
        
    };


    //-------------//
    //    Alias    //
    //-------------//
    using TitleSet=gd::ElasticList<Title>;
}

#endif
