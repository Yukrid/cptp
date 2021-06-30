#ifndef CPTP_FIGURE_HPP
#define CPTP_FIGURE_HPP

#include "forward.hpp"
#include "vec2.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    cptp::Figure Relocatable Structure    )//
    //-> forward.hpp figure.hpp figure.cpp
    struct Figure{

        //+    Member Type    +//
        //(    cptp::Figure::Size Enumeration    )//
        //-> figure.hpp
        enum SizeDef{
            CAMMPUS, PLOT_AREA
        };


        //+    Alias    +//
        using Size=gd::Alternative<Vec2, Vec2>;


        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        Size size;
        Vec2 margin;
       

        //+     Member Function    +//
        //_ Constructor
                Figure    (void)                                     noexcept;
                Figure    (const Figure&)                            =default;
                Figure    (Figure&&)                                 =default;
                Figure    (const Size&, const Vec2& =Vec2(0.4, 0.4)) noexcept;     
        Figure& construct (const Size&, const Vec2& =Vec2(0.4, 0.4)) noexcept;

        //_ Destructor
        ~Figure (void) =default;

        //_ Writer
        void info  (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;
       
        //_ Binary Operator
        Figure& operator= (const Figure&) =default;
        Figure& operator= (Figure&&)      =default;
        
    };

}

#endif
