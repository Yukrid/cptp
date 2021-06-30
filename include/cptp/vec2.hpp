#ifndef CPTP_VEC2_HPP
#define CPTP_VEC2_HPP

#include "forward.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //------------------------//
    //    Type Declaration    //
    //------------------------//
    ////(    cptp::Vec2 Relocatable Strcuture   )//
    //-> forward.hpp vec2.hpp vec2.cpp
    struct Vec2{
        
        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        scalar x;
		scalar y;



        //+    Member Function    +//
        //_ Constructor
                       Vec2      (void)           =default;
                       Vec2      (const Vec2&)    =default;
                       Vec2      (Vec2&&)         =default;
        explicit       Vec2      (scalar)         noexcept;
                       Vec2      (scalar, scalar) noexcept;
                 Vec2& construct (void)           noexcept;
                 Vec2& construct (const Vec2&)    noexcept;
                 Vec2& construct (Vec2&&)         noexcept;
                 Vec2& construct (scalar)         noexcept;
                 Vec2& construct (scalar, scalar) noexcept;


        //_ Destructor
              ~Vec2    (void) =default;
        Vec2& destruct (void) noexcept;


        //_ Writer
        void info (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;        
        
        //_ Unary Operator
        Vec2 operator+ (void) const noexcept;
        Vec2 operator- (void) const noexcept;


        //_ Binary Operator
        Vec2& operator=  (const Vec2&) =default;
        Vec2& operator=  (Vec2&&)      =default;
        Vec2& operator=  (scalar)      noexcept;
        Vec2& operator+= (const Vec2&) noexcept;
        Vec2& operator+= (scalar)      noexcept;
        Vec2& operator-= (const Vec2&) noexcept;
        Vec2& operator-= (scalar)      noexcept;
        Vec2& operator*= (const Vec2&) noexcept;
        Vec2& operator*= (scalar)      noexcept;
        Vec2& operator/= (const Vec2&) noexcept;
        Vec2& operator/= (scalar)      noexcept;

        Vec2 operator+ (const Vec2&) const noexcept;
        Vec2 operator+ (scalar)      const noexcept;
        Vec2 operator- (const Vec2&) const noexcept;
        Vec2 operator- (scalar)      const noexcept;
        Vec2 operator* (const Vec2&) const noexcept;
        Vec2 operator* (scalar)      const noexcept;
        Vec2 operator/ (const Vec2&) const noexcept;
        Vec2 operator/ (scalar)      const noexcept;
    
    };


    //----------------------------//
    //    Function Declaration    //
    //----------------------------//
    //(    cptp Space    )//
    std::ostream& operator<< (std::ostream&, const Vec2&) noexcept; 

}

#endif
