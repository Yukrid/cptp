#ifndef CPTP_KEY_HPP
#define CPTP_KEY_HPP
#include "forward.hpp"
#include "position.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    cptp::Key Relocatable Structure    )//
    //-> forward.hpp key.hpp key.cpp
    struct Key{
    
        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        bool     enable;
        Position position;
        float    point;
        float    margin;
        float    interval;
        float    str_scale;


        //+     Member Function    +//
        //_ Constructor
             Key         (void)                                                                  noexcept;
             Key         (const Key&)                                                            =default;
             Key         (Key&&)                                                                 =default;
             Key         (bool, const Position& =Position(), float =5.0, float =0.15, float =0.05, float =0.5) noexcept;
        Key& construct   (bool, const Position& =Position(), float =5.0, float =0.15, float =0.05, float =0.5) noexcept;
        

        //_ Destructor
             ~Key     (void) =default;
        Key& destruct (void) noexcept;

        //_ Writer
        void info  (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;
        
        //_ Binary Operator
        Key& operator= (const Key&) =default;
        Key& operator= (Key&&)      =default;
        
    };
}

#endif
