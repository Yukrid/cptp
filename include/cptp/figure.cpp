#include "figure.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{
    
    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    cptp::Figure Relocatable Structure    )//
    //+     Member Function    +//
    //_ Constructor
    Figure::Figure(void) noexcept
        : size   (CAMMPUS, Vec2(11.3, 7.0))
        , margin (0.4, 0.4)
    {
        return;
    }
 

    Figure::Figure(const Size& sz_, const Vec2& mar_) noexcept
        : size   (sz_)
        , margin (mar_)
    { 
        return;
    }


    Figure& Figure::construct(const Size& sz_, const Vec2& mar_) noexcept
    {
        new(this) Figure(sz_, mar_);

        return *this;
    }

    
    //_ Writer
    void Figure::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {    

        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::Figure Relocatable Structure]"<<std::endl;
        os_<<str<<"(size)         : "<<sizeof(Figure)<<std::endl;
        os_<<str<<"(name)         : "<<typeid(Figure).name()<<std::endl;
        os_<<str<<"(address)      : "<<this<<std::endl;
        os_<<str<<"(memory)       : "<<0<<std::endl;
        switch(size.number()){
            case CAMMPUS:
                os_<<str<<"Cammpus Size   : "<<size<<std::endl;
                break;
            case PLOT_AREA:
                os_<<str<<"Plot Area Size : "<<size<<std::endl;
                break;
        }
        os_<<str<<"Margin         : "<<margin<<std::endl;

        return;
    }

}

