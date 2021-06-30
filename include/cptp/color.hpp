#ifndef CPTP_COLOR_HPP
#define CPTP_COLOR_HPP

#include "forward.hpp"
#include "void.hpp"
#include "rgb.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //------------------------//
    //    Type Declaration    //
    //------------------------//
    ////(    cptp::Color Relocatable Strcuture   )//
    //-> forward.hpp color.hpp color.inl color.cpp
    struct Color{

        //+    Member Type    +/
        enum ID : uint8_t{
            RED, GREEN, BLUE, VIOLET, OLIVE, ORANGE, TEAL, BROWN, PURPLE, DARKGRAY, 
            MAGENTA, GRAY, PINK, LIME, BLACK, YELLOW, CYAN, LIGHTGRAY
        };
        

        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        gd::Alternative<Void, ID, RGB> color;


        //+    Member Function    +//
        //_ Constructor
               Color     (void)                      =default;
               Color     (const Color&)              =default;
               Color     (Color&&)                   =default;
               Color     (ID)                        noexcept;
               Color     (RGB)                       noexcept;
               Color     (uint8_t, uint8_t, uint8_t) noexcept;
        Color& construct (void)                      noexcept;
        Color& construct (ID)                        noexcept;
        Color& construct (RGB)                       noexcept;
        Color& construct (uint8_t, uint8_t, uint8_t) noexcept;
        
        //_ Destructor
               ~Color   (void) =default;
        Color& destruct (void) noexcept;

        //_ Writer
        void info (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;        
 
        //_ Constant Function
        const std::string& _idToString  (void) const noexcept;
        const std::string& _rgbToString (void) const noexcept;
      
        //_ Unary Operator
        const gd::Alternative<Void,ID,RGB>& operator() (void) const noexcept;
   
        //_ Binary Operator
        Color& operator= (const Color&) =default;
        Color& operator= (Color&&)      =default;

    };
    


    //----------------------------//
    //    Function Declaration    //
    //----------------------------//
    //(    cptp Space    )//
    std::ostream& operator<< (std::ostream&, const Color&) noexcept; 

}
#endif
