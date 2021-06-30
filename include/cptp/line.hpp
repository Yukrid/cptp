#ifndef CPTP_LINE_HPP
#define CPTP_LINE_HPP

#include "forward.hpp"
#include "color.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    cptp::Line Structure    )//
    //-> forward.hpp line.hpp line.cpp
    struct Line{
    
        //+    Member Type    +//
        //(    cptp::Line::Width Enumeration    )//
        //-> line.hpp
        enum Width : uint8_t {
            SEMI_THICK, ULTRA_THIN, VERY_THIN, THIN, THICK, VERY_THICK, ULTRA_THICK
        };


        //(    cptp::Line::Width Enumeration    )//
        //-> dot.hpp
        enum Dot : uint8_t {
            SOLID, LOOSELY_DOTTED, DOTTED, DENSELY_DOTTED, LOOSELY_DASHED, DASHED, DENSELY_DASHED, 
            LOOSELY_DASH_DOT, DASH_DOT, DENSELY_DASH_DOT, LOOSELY_DASH_DOT_DOT, DASH_DOT_DOT, DENSELY_DASH_DOT_DOT
        };


        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        bool        enable;
        Color       color;
        Width       width;
        Dot         dot;
        std::string option;
       

        //+     Member Function    +//
        //_ Constructor
              Line      (void)                                                                               noexcept;
              Line      (const Line&)                                                                        =default;
              Line      (Line&&)                                                                             =default;
              Line      (bool, const Color& =Color(), Width =SEMI_THICK, Dot =SOLID, const std::string& ="") noexcept;
        Line& construct (void)                                                                               noexcept;
        Line& construct (bool, const Color& =Color(), Width =SEMI_THICK, Dot =SOLID, const std::string& ="") noexcept;
        Line& set       (bool, const Color& =Color(), Width =SEMI_THICK, Dot =SOLID, const std::string& ="") noexcept;

        //_ Destructor
              ~Line    (void) =default;
        Line& destruct (void) noexcept;

        //_ Writer
        void info  (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;
        
        //_ Constant Function
              size_t       _memory        (void) const noexcept;
        const std::string& _widthToString (void) const noexcept;
        const std::string& _dotToString   (void) const noexcept;

        //_ Binary Operator
        Line& operator= (const Line&) =default;
        Line& operator= (Line&&)      =default;
    
    };
   
}

#endif
