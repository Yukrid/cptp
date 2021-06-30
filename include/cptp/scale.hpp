#ifndef CPTP_SCALE_HPP
#define CPTP_SCALE_HPP

#include <limits>
#include <numbers>
#include "forward.hpp"
#include "void.hpp"
#include "vec2.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    cptp::Scale Structure    )//
    //-> forward.hpp scale.hpp scale.cpp
    struct Scale{
 
        //+    Member Type    +//
        enum Type{
            DECIMAL, LOG, ANY
        };
      

        //+    Alias    +//
        using Arg=gd::ElasticAlternative<double, gd::ElasticTuple<double, std::string>, gd::ElasticTuple<double, std::string>>;
        using Decimal=Arg::Type<cptp::Scale::DECIMAL>;
        using Log    =Arg::Type<cptp::Scale::LOG>;
        using Any    =Arg::Type<cptp::Scale::ANY>;


        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        double   point;
        double   length;
        uint16_t interval;
        bool     grid;
        Arg      arg;


        //+     Member Function    +//
        //_ Constructor
               Scale       (void)                                                                                      noexcept;
               Scale       (const Scale&)                                                                              =default;
               Scale       (Scale&&)                                                                                   =default;
               Scale       (const double&, const double& =0.5, uint16_t =0, bool =false, const Arg& =Arg(DECIMAL, 0.)) noexcept;
        Scale& construct   (void)                                                                                      noexcept;
        Scale& construct   (const double&, const double& =0.5, uint16_t =0, bool =false, const Arg& =Arg(DECIMAL, 0.)) noexcept;
        Scale& reconstruct (const double&, const double& =0.5, uint16_t =0, bool =false, const Arg& =Arg(DECIMAL, 0.)) noexcept;
    
        //_ Destructor
                ~Scale  (void) =default;
        Scale& destruct (void) noexcept;

        //_ Writer
        void info  (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;
   
        //_ Constant Function
        size_t _memory (void) const noexcept;
   
        //_ Binary Operator
        Scale& operator= (const Scale&) =default;
        Scale& operator= (Scale&&)      =default;
        
    };



    //(    cptp::Scale2D Structure    )//
    //-> forward.hpp scale.hpp scale.cpp
    struct Scale2D{
    
        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        bool  enable;
        Scale x;
        Scale y;


        //+     Member Function    +//
        //_ Constructor
                 Scale2D     (void)                                               noexcept;
                 Scale2D     (const Scale2D&)                                     =default;
                 Scale2D     (Scale2D&&)                                          =default;
                 Scale2D     (bool, const Scale& =Scale(), const Scale& =Scale()) noexcept;
        Scale2D& construct   (void)                                               noexcept;
        Scale2D& construct   (bool, const Scale& =Scale(), const Scale& =Scale()) noexcept;
        Scale2D& reconstruct (bool, const Scale& =Scale(), const Scale& =Scale()) noexcept;

        //_ Destructor
                 ~Scale2D  (void) =default;
        Scale2D&  destruct (void) noexcept;

        //_ Writer
        void info  (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;
        
        //_ Constant Function
        size_t _memory(void) const noexcept;

        //_ Binary Operator
        Scale2D& operator= (const Scale2D&) =default;
        Scale2D& operator= (Scale2D&&)      =default;
        
    };

}

#endif
