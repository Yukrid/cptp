#include <cptp/position.hpp>

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{
    
    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    cptp::Position Relocatable Strcuture   )//
    //-> cptp.hpp position.hpp position.cpp
    //_ Constructor
    Position::Position(void) noexcept
        : base (Base::AUTO)
        , disp (0.2, 0.2)
    {
        return;
    }

    Position::Position(Base b_, const Vec2& v2_) noexcept
        : base (b_)
        , disp (v2_)
    {
        return;
    }
 

    Position& Position::construct (Base b_, const Vec2& v2_) noexcept
    {
        new(this) Position(b_, v2_);
        
        return *this;
    }



    //_ Destructor
    Position& Position::destruct (void) noexcept
    {
        return *this;
    }


    
    //_ Writer
    void Position::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {
        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::Position Relocatable Structure]"<<std::endl;
        os_<<str<<"(size)       : "<<sizeof(Position)<<std::endl;
        os_<<str<<"(name)       : "<<typeid(Position).name()<<std::endl;
        os_<<str<<"(address)    : "<<this<<std::endl;
        os_<<str<<"(memory)     : "<<0<<std::endl;
        os_<<str<<"Base         : "<<_baseToString()<<std::endl;
        os_<<str<<"Displacement : "<<disp<<std::endl;

        return;
    }
    

    //_ Constant Function
    std::string Position::_baseToString(void) const noexcept
    {
        std::string str;
        switch(base){
            case AUTO         : str="auto";         break;
            case RIGHT_TOP    : str="right top";    break;
            case LEFT_TOP     : str="left top";     break;
            case RIGHT_BOTTOM : str="right bottom"; break;
            case LEFT_BOTTOM  : str="left bottom";  break;
            default           : str="(null)";       break;
        }

        return str;
    }
}
