#ifndef CPTP_POINT_HPP
#define CPTP_POINT_HPP

#include "forward.hpp"
#include "color.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    cptp::Point Structure    )//
    //-> forward.hpp point.hpp point.cpp
    struct Point{

        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        bool        enable;
        Color       color;
        double      size;
        std::string shape;
        std::string option;
       

        //+     Member Function    +//
        //_ Constructor
               Point     (void)                                                                                              noexcept;
               Point     (const Point&)                                                                                      =default;
               Point     (Point&&)                                                                                           =default;
               Point     (bool, Color=Color(), const double& =8.0, const std::string& ="$\\bullet$", const std::string& ="") noexcept;
        Point& construct (void)                                                                                              noexcept;
        Point& construct (bool, Color=Color(), const double& =8.0, const std::string& ="$\\bullet$", const std::string& ="") noexcept;
        Point& set       (bool, Color=Color(), const double& =8.0, const std::string& ="$\\bullet$", const std::string& ="") noexcept;

        //_ Destructor
              ~Point    (void) =default;
        Point& destruct (void) noexcept;

        //_ Writer
        void info (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;
        
        //_ Constant Function
        size_t _memory (void) const noexcept;

        //_ Binary Operator
        Point& operator= (const Point&) =default;
        Point& operator= (Point&&)      =default;
    };
     
}
#endif
