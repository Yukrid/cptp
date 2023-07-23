#include <cptp/label.hpp>

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{
    
    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    cptp::Label Structure    )//
    //+     Member Function    +//
    //_ Constructor
    Label::Label(void) noexcept
        : string ( )
        , point  (10.0)
    {
        return;
    }
 

    Label::Label(const std::string& str_, double pt_) noexcept
        : string (str_)
        , point  (pt_)
    {
        return;
    }
 

    Label& Label::construct(void) noexcept
    {
        new(this) Label();

        return *this;
    } 


    Label& Label::construct(const std::string& str_, double pt_) noexcept
    {
        new(this) Label(str_, pt_);

        return *this;
    } 


    Label& Label::reconstruct(const std::string& str_, double pt_) noexcept
    {
        this->~Label();
        new(this) Label(str_, pt_);

        return *this;
    } 

    

    //_ Destructor
    Label& Label::destruct(void) noexcept
    {
        this->~Label();

        return *this;
    } 



    //_ Writer
    void Label::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {    

        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::Label Structure]"<<std::endl;
        os_<<str<<"(size)    : "<<sizeof(Label)<<std::endl;
        os_<<str<<"(name)    : "<<typeid(Label).name()<<std::endl;
        os_<<str<<"(address) : "<<this<<std::endl;
        os_<<str<<"(memory)  : "<<_memory()<<std::endl;
        os_<<str<<"String    : "<<string<<std::endl;
        os_<<str<<"Point     : "<<point<<std::endl;

        return;
    }



    //_ Constant Function
    size_t Label::_memory(void) const noexcept
    {    
        return string.capacity();
    }



    //(    cptp::Label2D Structure    )//
    //+     Member Function    +//
    //_ Constructor    
    Label2D::Label2D(void) noexcept
        : enable (true)
        , x      ("$x$")
        , y      ("$y$")
        , margin (0.2, 0.2)
    {
        return;
    }
 

    Label2D::Label2D(bool f_, const Label& x_, const Label& y_, const Vec2& v2_) noexcept
        : enable (f_)
        , x      (x_)
        , y      (y_)
        , margin (v2_)
    {
        return;
    }
 

    Label2D& Label2D::construct(void) noexcept
    {
        new(this) Label2D();
        
        return *this;
    }


    Label2D& Label2D::construct(bool f_, const Label& x_, const Label& y_, const Vec2& v2_) noexcept
    {
        new(this) Label2D(f_, x_, y_, v2_);
        
        return *this;
    }
  

    Label2D& Label2D::reconstruct(bool f_, const Label& x_, const Label& y_, const Vec2& v2_) noexcept
    {
        this->~Label2D();
        new(this) Label2D(f_, x_, y_, v2_);
        
        return *this;
    }
    


    //_ Destructor
    Label2D& Label2D::destruct(void) noexcept
    {
        this->~Label2D();

        return *this;
    } 
    
    

    //_ Writer
    void Label2D::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {    

        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::Label2D Structure]"<<std::endl;
        os_<<str<<"(size)    : "<<sizeof(Label2D)<<std::endl;
        os_<<str<<"(name)    : "<<typeid(Label2D).name()<<std::endl;
        os_<<str<<"(address) : "<<this<<std::endl;
        os_<<str<<"(memory)  : "<<_memory()<<std::endl;
        os_<<str<<"Enable    : "<<(enable ? "true" : "false")<<std::endl;
        os_<<str<<"X         : "<<std::endl;
        x.info(os_, offset_+1);
        os_<<str<<"Y         : "<<std::endl;
        y.info(os_, offset_+1);
        os_<<str<<"Margin    : "<<margin<<std::endl;

        return;
    }



    //_ Constant Function
    size_t Label2D::_memory(void) const noexcept
    {    
        return x._memory()+y._memory();
    }

}

