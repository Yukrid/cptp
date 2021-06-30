#include "rgb.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{
    
    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    cptp::RGB Relocatable Strcuture   )//
    //-> cptp.hpp rgb.hpp rgb.cpp
    //_ Constructor
    RGB::RGB(uint8_t s1_, uint8_t s2_, uint8_t s3_) noexcept
        : r (s1_)
        , g (s2_)
        , b (s3_)
    {
        return;
    }
 

    RGB& RGB::construct (void) noexcept
    {
        new(this) RGB();
        
        return *this;
    }


    RGB& RGB::construct (uint8_t s1_, uint8_t s2_, uint8_t s3_) noexcept
    {
        new(this) RGB(s1_, s2_, s3_);
        
        return *this;
    }



    //_ Destructor
    RGB& RGB::destruct (void) noexcept
    {
        this->~RGB();

        return *this;
    }


    
    //_ Writer
    void RGB::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {
        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::RGB Relocatable Structure]"<<std::endl;
        os_<<str<<"(size)    : "<<sizeof(RGB)<<std::endl;
        os_<<str<<"(name)    : "<<typeid(RGB).name()<<std::endl;
        os_<<str<<"(address) : "<<this<<std::endl;
        os_<<str<<"(memory)  : "<<0<<std::endl;
        os_<<str<<"R         : "<<+r<<std::endl;
        os_<<str<<"G         : "<<+g<<std::endl;
        os_<<str<<"B         : "<<+b<<std::endl;

        return;
    }
    



    //(    md Space    )//
    std::ostream& operator<<(std::ostream& os_, const RGB& rgb_) noexcept
    {
        os_<<+rgb_.r<<" "<<+rgb_.g<<" "<<+rgb_.b;

        return os_;
    }

}
