#include "color.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{
    
    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    cptp::Color Relocatable Strcuture   )//
    //-> cptp.hpp color.hpp color.inl color.cpp
    //_ Constructor
    Color::Color(ID id_) noexcept
        : color (1, id_)
    {
        return;
    }


    Color::Color(RGB rgb_) noexcept
        : color (2, rgb_)
    {
        return;
    }


    Color::Color(uint8_t r_, uint8_t g_, uint8_t b_) noexcept
        : color (2, RGB(r_, g_, b_))
    {
        return;
    }

    
    Color& Color::construct(void) noexcept
    {
        new(this) Color();

        return *this;
    }


    Color& Color::construct(ID id_) noexcept
    {
        new(this) Color(id_);

        return *this;
    }


    Color& Color::construct(RGB rgb_) noexcept
    {
        new(this) Color(rgb_);

        return *this;
    }

    
    Color& Color::construct(uint8_t r_, uint8_t g_, uint8_t b_) noexcept
    {
        new(this) Color(r_, g_, b_);

        return *this;
    }



    //_ Destructor
    Color& Color::destruct (void) noexcept
    {
        this->~Color();

        return *this;
    }


    
    //_ Writer
    void Color::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {
        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::Color Relocatable Structure]"<<std::endl;
        os_<<str<<"(size)     : "<<sizeof(Color)<<std::endl;
        os_<<str<<"(name)     : "<<typeid(Color).name()<<std::endl;
        os_<<str<<"(address)  : "<<this<<std::endl;
        os_<<str<<"(memory)   : "<<0<<std::endl;
        switch(color.number()){
            case 0:
                os_<<str<<"Type       : "<<"Null"<<std::endl;
                break;
            case 1:
                os_<<str<<"Type       : "<<"ID"<<std::endl;
                os_<<str<<"String     : "<<_idToString()<<std::endl;
                break;
            case 2:
                os_<<str<<"Type       : "<<"RGB"<<std::endl;
                os_<<str<<"RGB Values : "<<_rgbToString()<<std::endl;
                break;
        }

        return;
    }
 


    //_ Constant Function
    const std::string& Color::_idToString(void) const noexcept
    {
        static std::string str="";

        switch(color.path<1>()){
            case RED      : str="red";       break;
            case GREEN    : str="green";     break;
            case BLUE     : str="blue";      break;
            case VIOLET   : str="violet";    break;
            case OLIVE    : str="olive";     break;
            case ORANGE   : str="orange";    break;
            case TEAL     : str="teal";      break;
            case BROWN    : str="brown";     break;
            case PURPLE   : str="purple";    break;
            case DARKGRAY : str="darkgray";  break;
            case MAGENTA  : str="magenta";   break;
            case GRAY     : str="gray";      break;
            case PINK     : str="pink";      break;
            case LIME     : str="lime";      break;
            case BLACK    : str="black";     break;
            case YELLOW   : str="yellow";    break;
            case CYAN     : str="cyan";      break;
            case LIGHTGRAY: str="lightgray"; break;
            default       : str="black";     break;
        }

        return str;
    }


    const std::string& Color::_rgbToString(void) const noexcept
    {
        static std::string str="red!"+std::to_string(100*int((+color.path<2>().r)/255))+"!green!"+std::to_string(100*int((+color.path<2>().g)/255))+"!blue";

        return str;
    }


    //_ Unary Operator
    const gd::Alternative<Void,Color::ID,RGB>& Color::operator() (void) const noexcept
    {
        return color;
    }




    //(    md Space    )//
    std::ostream& operator<<(std::ostream& os_, const Color& color_) noexcept
    {
        os_<<color_();

        return os_;
    }
}
