#include <cptp/scale.hpp>

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{
    
    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    cptp::Scale Structure    )//
    //-> forward.hpp scale.hpp scale.cpp
    //+     Member Function    +//
    //_ Constructor
    Scale::Scale(void) noexcept
        : point    (8.0)
        , length   (0.1)
        , interval (0)
        , grid     (false)
        , arg      (DECIMAL, 0.)
    {
        return;
    }
 
 
    Scale::Scale(const double& pt_, const double& len_, uint16_t in_, bool grid_, const Arg& arg_) noexcept
        : point    (pt_)
        , length   (len_)
        , interval (in_)
        , grid     (grid_)
        , arg      (arg_)
    {
        return;
    }


    Scale& Scale::construct(void) noexcept
    {
        new(this) Scale();

        return *this;
    }


    Scale& Scale::construct(const double& pt_, const double& len_, uint16_t in_, bool grid_, const Arg& arg_) noexcept
    {
        new(this) Scale(pt_, len_, in_, grid_, arg_);

        return *this;
    }


    Scale& Scale::reconstruct(const double& pt_, const double& len_, uint16_t in_, bool grid_, const Arg& arg_) noexcept
    {
        this->~Scale();
        new(this) Scale(pt_, len_, in_, grid_, arg_);

        return *this;
    }



    //_ Destructor
    Scale& Scale::destruct(void) noexcept
    {
        this->~Scale();

        return *this;;
    }   



    //_ Writer
    void Scale::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {    

        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::Scale Structure]"<<std::endl;
        os_<<str<<"(size)         : "<<sizeof(Scale)<<std::endl;
        os_<<str<<"(name)         : "<<typeid(Scale).name()<<std::endl;
        os_<<str<<"(address)      : "<<this<<std::endl;
        os_<<str<<"(memory)       : "<<_memory()<<std::endl;
        os_<<str<<"Point          : "<<point<<std::endl;
        os_<<str<<"Length         : "<<length<<std::endl;
        os_<<str<<"Interval       : "<<interval<<std::endl;
        os_<<str<<"Grid           : "<<(grid ? "True" : "False")<<std::endl;
        switch(arg.number()){
            case DECIMAL:
                os_<<str<<"Type           : "<<"Decimal"<<std::endl;
                os_<<str<<"Scale Ratio    : "<<arg.path<DECIMAL>()<<std::endl;
                break;    
            case LOG:
                os_<<str<<"Type           : "<<"Logarithm"<<std::endl;
                os_<<str<<"Logarithm Base : "<<arg.path<LOG>().path<0>()<<std::endl;
                os_<<str<<"Base String    : "<<arg.path<LOG>().path<1>()<<std::endl;
                break;
            case ANY:
                os_<<str<<"Type           : "<<"Any Value"<<std::endl;
                os_<<str<<"Scale Ratio    : "<<arg.path<ANY>().path<0>()<<std::endl;
                os_<<str<<"Scale String   : "<<arg.path<ANY>().path<1>()<<std::endl;
                break;
        }
        
        return;
    }

    

    //_ Constant Function
    size_t Scale::_memory(void) const noexcept
    {
        size_t mem=0;
        switch(arg.number()){
            case LOG:
                mem=arg.path<LOG>().path<1>().capacity();
                break;
            case ANY:
                mem=arg.path<ANY>().path<1>().capacity();
                break;
            default:
                mem=0;
                break;
        }

        return mem;
    }




    //(    cptp::Scale2D Structure    )//
    //+     Member Function    +//
    //_ Constructor    
    Scale2D::Scale2D(void) noexcept
        : enable (true)
        , x      ( )
        , y      ( )
    {
        return;
    }
 

    Scale2D::Scale2D(bool e_, const Scale& x_, const Scale& y_) noexcept
        : enable (true)
        , x      (x_)
        , y      (y_)
    {
        return;
    }
 

    Scale2D& Scale2D::construct(void) noexcept
    {
        new(this) Scale2D();

        return *this;
    }


    Scale2D& Scale2D::construct(bool e_, const Scale& x_, const Scale& y_) noexcept
    {
        new(this) Scale2D(e_, x_, y_);

        return *this;
    }
    
 
    Scale2D& Scale2D::reconstruct(bool e_, const Scale& x_, const Scale& y_) noexcept
    {
        this->~Scale2D();
        new(this) Scale2D(e_, x_, y_);

        return *this;
    }
   
    

    //_ Destructor
    Scale2D& Scale2D::destruct(void) noexcept
    {
        this->~Scale2D();

        return *this;
    }

    

    //_ Writer
    void Scale2D::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {    

        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::Scale2D Structure]"<<std::endl;
        os_<<str<<"(size)    : "<<sizeof(Scale2D)<<std::endl;
        os_<<str<<"(name)    : "<<typeid(Scale2D).name()<<std::endl;
        os_<<str<<"(address) : "<<this<<std::endl;
        os_<<str<<"(memory)  : "<<_memory()<<std::endl;
        os_<<str<<"Enable    : "<<(enable ? "true" : "false")<<std::endl;
        os_<<str<<"X         : "<<std::endl;
        x.info(os_, offset_+1);
        os_<<str<<"Y         : "<<std::endl;
        y.info(os_, offset_+1);

        return;
    }



    //_ Constant Function
    size_t Scale2D::_memory(void) const noexcept
    {    
        return x._memory()+y._memory();
    }
}
