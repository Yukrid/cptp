#ifndef CPTP_POSITION_HPP
#define CPTP_POSITION_HPP

#include "forward.hpp"
#include "vec2.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //------------------------//
    //    Type Declaration    //
    //------------------------//
    ////(    cptp::Position Relocatable Structure   )//
    //-> forward.hpp position.hpp position.cpp
    struct Position{
    
        //+    Member Type    +/
        enum Base : uint8_t{
            AUTO, RIGHT_TOP, LEFT_TOP, RIGHT_BOTTOM, LEFT_BOTTOM
        };


        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        Base base;
        Vec2 disp;   


        //+    Member Function    +//
        //_ Constructor
                  Position  (void)                              noexcept;
                  Position  (const Position&)                   =default;
                  Position  (Position&&)                        =default;
                  Position  (Base, const Vec2& =Vec2(0.2, 0.2)) noexcept;
        Position& construct (Base, const Vec2& =Vec2(0.2, 0.2)) noexcept;
        
        //_ Destructor
                  ~Position (void) =default;
        Position&  destruct (void) noexcept;

        //_ Writer
        void info (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;
   
        //_ Constant Function
        std::string _baseToString (void) const noexcept;

        //_ Binary Operator
        Position& operator= (const Position&) =default;
        Position& operator= (Position&&)      =default;
    };

}
#endif
