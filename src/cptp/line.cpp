#include <cptp/line.hpp>

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{
    
    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    cptp::Line Strcuture   )//
    //-> forward.hpp line.hpp line.cpp
    //_ Constructor
    Line::Line(void) noexcept
        : enable (true)
        , color  ( )
        , width  ( )
        , dot    ( )
        , option ( )
    {
        return;
    }


    Line::Line(bool e_, const Color& c_, Width w_, Dot d_, const std::string& str_) noexcept
        : enable (e_)
        , color  (c_)
        , width  (w_)
        , dot    (d_)
        , option (str_)
    {
        return;
    }


    Line& Line::construct(void) noexcept
    {
        new(this) Line();

        return *this;
    }


    Line& Line::construct(bool e_, const Color& c_, Width w_, Dot d_, const std::string& str_) noexcept
    {
        new(this) Line(e_, c_, w_, d_, str_);

        return *this;
    }


    Line& Line::set(bool e_, const Color& c_, Width w_, Dot d_, const std::string& str_) noexcept
    {
        this->~Line();
        new(this) Line(e_, c_, w_, d_, str_);

        return *this;
    }



    //_ Destructor
    Line& Line::destruct (void) noexcept
    {
        this->~Line();

        return *this;
    }


    
    //_ Writer
    void Line::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {
        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::Line Structure]"<<std::endl;
        os_<<str<<"(size)     : "<<sizeof(Line)<<std::endl;
        os_<<str<<"(name)     : "<<typeid(Line).name()<<std::endl;
        os_<<str<<"(address)  : "<<this<<std::endl;
        os_<<str<<"(memory)   : "<<0<<std::endl;
        os_<<str<<"Enable     : "<<(enable ? "true" : "false")<<std::endl;
        os_<<str<<"Color      : "<<std::endl;
        color.info(os_, offset_+1);
        os_<<str<<"Width      : "<<_widthToString()<<std::endl;
        os_<<str<<"Dot        : "<<_dotToString()<<std::endl;
        os_<<str<<"Option     : "<<option<<std::endl;

        return;
    }



    //_ Constant Function
    size_t Line::_memory(void) const noexcept
    {
        return option.capacity();
    }


    const std::string& Line::_widthToString(void) const noexcept
    {
        static std::string str="";

        switch(width){
            case ULTRA_THIN : str="ultra thin";  break;
            case VERY_THIN  : str="very thin";   break;
            case THIN       : str="thin";        break;
            case THICK      : str="thick";       break;
            case VERY_THICK : str="very thick";  break;
            case ULTRA_THICK: str="ultra thick"; break;
            default         : str="semithick";   break;
        }

        return str;
    }


    const std::string& Line::_dotToString(void) const noexcept
    {
        static std::string str="";

        switch(dot){
            case LOOSELY_DOTTED       : str="loosely dotted";        break;
            case DOTTED               : str="dotted";                break;
            case DENSELY_DOTTED       : str="densely dotted";        break;
            case LOOSELY_DASHED       : str="loosely dashed";        break;
            case DASHED               : str="dashed";                break;
            case DENSELY_DASHED       : str="densely dashed";        break;
            case LOOSELY_DASH_DOT     : str="loosely dash dot";      break;
            case DASH_DOT             : str="dash dot";              break;
            case DENSELY_DASH_DOT     : str="densely dash dot";      break;
            case LOOSELY_DASH_DOT_DOT : str="loosely dash dot dot";  break;
            case DASH_DOT_DOT         : str="dash dot dot";          break;
            case DENSELY_DASH_DOT_DOT : str="densely dash dot dot";  break;
            default                   : str="solid";                 break;
        }

        return str;
    }

}
