#include <cptp/title.hpp>

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{
    
    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    cptp::Title Structure    )//
    //+     Member Function    +//
    //_ Constructor
    Title::Title(void) noexcept
        : string   ( )
        , position (Position::AUTO)
        , margin   (0.12, 0.12)
        , point    (9.0)
    {
        return;
    }



    //_ Writer
    void Title::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {    

        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::Title Structure]"<<std::endl;
        os_<<str<<"(size)    : "<<sizeof(Title)<<std::endl;
        os_<<str<<"(name)    : "<<typeid(Title).name()<<std::endl;
        os_<<str<<"(address) : "<<this<<std::endl;
        os_<<str<<"(memory)  : "<<_memory()<<std::endl;
        os_<<str<<"String    : "<<string<<std::endl;
        os_<<str<<"Position  : "<<std::endl;
        position.info(os_, offset_+1);
        os_<<str<<"Margin    : "<<margin<<std::endl;
        os_<<str<<"Point     : "<<point<<std::endl;

        return;
    }



    //_ Constant Function
    size_t Title::_memory(void) const noexcept
    {    
        return string.capacity();
    }

}

