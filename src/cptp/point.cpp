#include <cptp/point.hpp>

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{
    
    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    cptp::Point Strcuture   )//
    //-> forward.hpp point.hpp point.cpp
    //_ Constructor
    Point::Point(void) noexcept
        : enable (false)
        , color  ( )
        , size   (8.0)
        , shape  ("$\\bullet$")
        , option ( )
    {
        return;
    }


    Point::Point(bool e_, Color c_, const double& sz_, const std::string& shp_, const std::string& opt_) noexcept
        : enable (e_)
        , color  (c_)
        , size   (sz_)
        , shape  (shp_)
        , option (opt_)
    {
        return;
    }


    Point& Point::construct(void) noexcept
    {
        new(this) Point();

        return *this;
    }


    Point& Point::construct(bool e_, Color c_, const double& sz_, const std::string& shp_, const std::string& opt_) noexcept
    {
        new(this) Point(e_, c_, sz_, shp_, opt_);

        return *this;
    }


    Point& Point::set(bool e_, Color c_, const double& sz_, const std::string& shp_, const std::string& opt_) noexcept
    {
        this->~Point();
        new(this) Point(e_, c_, sz_, shp_, opt_);

        return *this;
    }



    //_ Destructor
    Point& Point::destruct (void) noexcept
    {
        this->~Point();

        return *this;
    }


    
    //_ Writer
    void Point::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {
        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::Point Structure]"<<std::endl;
        os_<<str<<"(size)     : "<<sizeof(Point)<<std::endl;
        os_<<str<<"(name)     : "<<typeid(Point).name()<<std::endl;
        os_<<str<<"(address)  : "<<this<<std::endl;
        os_<<str<<"(memory)   : "<<_memory()<<std::endl;
        os_<<str<<"Enable     : "<<(enable ? "true" : "false")<<std::endl;
        os_<<str<<"Color      : "<<std::endl;
        color.info(os_, offset_+1);
        os_<<str<<"Size       : "<<size<<std::endl;
        os_<<str<<"Shape      : "<<shape<<std::endl;
        os_<<str<<"Option     : "<<option<<std::endl;

        return;
    }



    //_ Constant Function
    size_t Point::_memory(void) const noexcept
    {
        return shape.capacity()+option.capacity();
    }

}
