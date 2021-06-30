#ifndef CPTP_RGB_HPP
#define CPTP_RGB_HPP

#include "forward.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //------------------------//
    //    Type Declaration    //
    //------------------------//
    ////(    cptp::RGB Relocatable Strcuture   )//
    //-> forward.hpp rgb.hpp rgb.cpp
    struct RGB{
        
        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        uint8_t r;
		uint8_t g;
		uint8_t b;



        //+    Member Function    +//
        //_ Constructor
             RGB       (void)                      =default;
             RGB       (const RGB&)                =default;
             RGB       (RGB&&)                     =default;
             RGB       (uint8_t, uint8_t, uint8_t) noexcept;
        RGB& construct (void)                      noexcept;
        RGB& construct (uint8_t, uint8_t, uint8_t) noexcept;
        

        //_ Destructor
                ~RGB  (void) =default;
        RGB& destruct (void) noexcept;


        //_ Writer
        void info (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;        
       

        //_ Binary Operator
        RGB& operator= (const RGB&) =default;
        RGB& operator= (RGB&&)      =default;

    };



    //----------------------------//
    //    Function Declaration    //
    //----------------------------//
    //(    cptp Space    )//
    std::ostream& operator<< (std::ostream&, const RGB&) noexcept; 

}
#endif
