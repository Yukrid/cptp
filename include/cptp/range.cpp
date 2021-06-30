#include <limits>
#include "range.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{
    
    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    cptp::Range Relocatable Strcuture   )//
    //-> cptp.hpp range.hpp range.cpp
    //_ Constructor
    Range::Range(void) noexcept
        : min (+std::numeric_limits<scalar>::max())
        , max (-std::numeric_limits<scalar>::max())
    {
        return;
    }


    Range::Range(const scalar& min_, const scalar& max_) noexcept
        : min (min_)
        , max (max_)
    {
        return;
    }
 

    Range& Range::construct(const scalar& min_, const scalar& max_) noexcept
    {
        new(this) Range(min_, max_);
        
        return *this;
    }



    //_ Destructor
    Range& Range::destruct (void) noexcept
    {
        this->~Range();

        return *this;
    }


    
    //_ Writer
    void Range::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {
        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::Range Relocatable Structure]"<<std::endl;
        os_<<str<<"(size)    : "<<sizeof(Range)<<std::endl;
        os_<<str<<"(name)    : "<<typeid(Range).name()<<std::endl;
        os_<<str<<"(address) : "<<this<<std::endl;
        os_<<str<<"(memory)  : "<<0<<std::endl;
        os_<<str<<"Min Value : "<<min<<std::endl;
        os_<<str<<"Max Value : "<<max<<std::endl;

        return;
    }
    



    //(    cptp::Range Relocatable Strcuture   )//
    //-> cptp.hpp range.hpp range.cpp
    //_ Constructor
    Range2D::Range2D(const Range& x_, const Range& y_) noexcept
        : x (x_)
        , y (y_)
    {
        return;
    }
    

    Range2D& Range2D::construct(const Range& x_, const Range& y_) noexcept
    {
        new(this) Range2D(x_, y_);

        return *this;
    }
    


    //_ Destructor
    Range2D& Range2D::destruct(void) noexcept
    {
        this->~Range2D();

        return *this;
    }
    


    //_ Writer
    void Range2D::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {
        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::Range2D Relocatable Structure]"<<std::endl;
        os_<<str<<"(size)    : "<<sizeof(Range2D)<<std::endl;
        os_<<str<<"(name)    : "<<typeid(Range2D).name()<<std::endl;
        os_<<str<<"(address) : "<<this<<std::endl;
        os_<<str<<"(memory)  : "<<0<<std::endl;
        os_<<str<<"X         : "<<std::endl;
        x.info(os_, offset_+1);
        os_<<str<<"Y         : "<<std::endl;
        y.info(os_, offset_+1);

        return;
    }

}
