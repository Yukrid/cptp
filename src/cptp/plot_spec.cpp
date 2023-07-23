#include <cptp/plot_spec.hpp>

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{
    
    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    cptp::PlotSpec Strcuture   )//
    //-> forward.hpp plot_spec.hpp plot_spec.cpp
    //_ Constructor
    PlotSpec::PlotSpec(const std::string& t_, Color c_, const Line& l_, const Point& p_, const std::string& opt_) noexcept
        : tag    (t_)
        , color  (c_)
        , line   (l_)
        , point  (p_)
        , option (opt_)
    {
        return;
    }


    PlotSpec& PlotSpec::construct(void) noexcept
    {
        new(this) PlotSpec();

        return *this;
    }


    PlotSpec& PlotSpec::construct(const std::string& t_, Color c_, const Line& l_, const Point& p_, const std::string& opt_) noexcept
    {
        new(this) PlotSpec(t_, c_, l_, p_, opt_);

        return *this;
    }


    PlotSpec& PlotSpec::reconstruct(const std::string& t_, Color c_, const Line& l_, const Point& p_, const std::string& opt_) noexcept
    {
        this->~PlotSpec();
        new(this) PlotSpec(t_, c_, l_, p_, opt_);

        return *this;
    }



    //_ Destructor
    PlotSpec& PlotSpec::destruct (void) noexcept
    {
        this->~PlotSpec();

        return *this;
    }


    
    //_ Writer
    void PlotSpec::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {
        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::PlotSpec Structure]"<<std::endl;
        os_<<str<<"(size)     : "<<sizeof(PlotSpec)<<std::endl;
        os_<<str<<"(name)     : "<<typeid(PlotSpec).name()<<std::endl;
        os_<<str<<"(address)  : "<<this<<std::endl;
        os_<<str<<"(memory)   : "<<_memory()<<std::endl;
        os_<<str<<"Color      : "<<std::endl;
        color.info(os_, offset_+1);
        os_<<str<<"Line       : "<<std::endl;
        line.info(os_, offset_+1);
        os_<<str<<"Point      : "<<std::endl;
        point.info(os_, offset_+1);
        os_<<str<<"Option     : "<<option<<std::endl;

        return;
    }



    //_ Constant Function
    size_t PlotSpec::_memory(void) const noexcept
    {
        return line._memory()+point._memory()+option.capacity();
    }
    
}
