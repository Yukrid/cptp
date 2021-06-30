#ifndef CPTP_FORWARD_HPP
#define CPTP_FORWARD_HPP

#include <gd1.hpp>

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //-------------//
    //    Alias    //
    //-------------//
    using scalar=double;    

    //------------------------//
    //    Type Declaration    //
    //------------------------//
    //(    cptp::Void Void Structure    )//
    //-> forward.hpp void.hpp
    struct Void;

    //(    cptp::Vec2 Relocatable Structure    )//
    //-> forward.hpp vec2.hpp vec2.cpp
    struct Vec2;

    //(    cptp::RGB Relocatable Structure    )//
    //-> forward.hpp rgb.hpp rgb.cpp
    struct RGB;

    //(    cptp::Figure Relocatable Structure    )//
    //-> forward.hpp figure.hpp figure.cpp
    struct Figure;
    
    //(    cptp::Label Structure    )//
    //-> forward.hpp label.hpp label.cpp
    struct Label;

    //(    cptp::Scale Structure    )//
    //-> forward.hpp scale.hpp scale.inl scale.cpp
    struct Scale;


}

#endif
