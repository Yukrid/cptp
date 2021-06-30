#ifndef CPTP_FUNCTION_HPP
#define CPTP_FUNCTION_HPP

#include "forward.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //----------------------------//
    //    Function Declaration    //
    //----------------------------//
    //(    cptp Space    )//
    //-> function.hpp function.hpp
    inline double   pointToCenti  (double)                       noexcept;
    inline double   centiToPoint  (double)                       noexcept;
    inline uint32_t scaleInterval (uint32_t)                     noexcept;
    inline size_t   mathStrWidth  (const std::string&, size_t=0) noexcept;
    inline size_t   keyWidth      (const std::string&)           noexcept;

}

#include "function.inl"

#endif
