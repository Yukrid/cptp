#include "vec2.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{
    
    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    cptp::Vec2 Relocatable Strcuture   )//
    //-> cptp.hpp vec2.hpp vec2.cpp
    //_ Constructor
    Vec2::Vec2(scalar s_) noexcept
        : x (s_)
        , y (s_)
    {
        return;
    }
 

    Vec2::Vec2(scalar s1_, scalar s2_) noexcept
        : x (s1_)
        , y (s2_)
    {
        return;
    }
 

    Vec2& Vec2::construct (void) noexcept
    {
        new(this) Vec2();
        
        return *this;
    }


    Vec2& Vec2::construct (const Vec2& v2_) noexcept
    {
        new(this) Vec2(v2_);

        return *this;
    }
 

    Vec2& Vec2::construct (Vec2&& v2_) noexcept
    {
        new(this) Vec2(std::move(v2_));

        return *this;
    }


    Vec2& Vec2::construct (scalar s_) noexcept
    {
        new(this) Vec2(s_);

        return *this;
    }


    Vec2& Vec2::construct (scalar s1_, scalar s2_) noexcept
    {
        new(this) Vec2(s1_, s2_);

        return *this;
    }
    
    

    //_ Destructor
    Vec2& Vec2::destruct (void) noexcept
    {
        this->destruct();

        return *this;
    }


    
    //_ Writer
    void Vec2::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {
        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::Vec2 Relocatable Structure]"<<std::endl;
        os_<<str<<"(size)    : "<<sizeof(Vec2)<<std::endl;
        os_<<str<<"(name)    : "<<typeid(Vec2).name()<<std::endl;
        os_<<str<<"(address) : "<<this<<std::endl;
        os_<<str<<"(memory)  : "<<0<<std::endl;
        os_<<str<<" X        : "<<x<<std::endl;
        os_<<str<<" Y        : "<<y<<std::endl;

        return;
    }
       

    
    //_ Unary Operator
    Vec2 Vec2::operator+(void) const noexcept
    {
        return Vec2(x, y);
    }
    
    
    Vec2 Vec2::operator-(void) const noexcept
    {
        return Vec2(-x, -y);
    } 

    

    //_ Binary Operator
    Vec2& Vec2::operator=(scalar s_) noexcept
    {
        x=s_;  y=s_;
        
        return *this;
    }

    
    Vec2& Vec2::operator+=(const Vec2& v2_) noexcept
    {
        x+=v2_.x;  y+=v2_.y;

        return *this;
    }

    
    Vec2& Vec2::operator+=(scalar s_) noexcept
    {
        x+=s_;  y+=s_;

        return *this;
    }

    
    Vec2& Vec2::operator-=(const Vec2& v2_) noexcept
    {
        x-=v2_.x;  y-=v2_.y;

        return *this;
    }

    
    Vec2& Vec2::operator-=(scalar s_) noexcept
    {
        x-=s_;  y-=s_;

        return *this;
    }

    
    Vec2& Vec2::operator*=(const Vec2& v2_) noexcept
    {
        x*=v2_.x;  y*=v2_.y;

        return *this;
    }

    
    Vec2& Vec2::operator*=(scalar s_) noexcept
    {
        x*=s_;  y*=s_;

        return *this;
    }

    
    Vec2& Vec2::operator/=(const Vec2& v2_) noexcept
    {
        x/=v2_.x;  y/=v2_.y;

        return *this;
    }

    
    Vec2& Vec2::operator/=(scalar s_) noexcept
    {
        x/=s_;  y/=s_;

        return *this;
    }


    Vec2 Vec2::operator+(const Vec2& v2_) const noexcept
    {
        return Vec2(x+v2_.x, y+v2_.y);
    }

    
    Vec2 Vec2::operator+(scalar s_) const noexcept
    {
        return Vec2(x+s_, y+s_);
    }


    Vec2 Vec2::operator-(const Vec2& v2_) const noexcept
    {
        return Vec2(x-v2_.x, y-v2_.y);
    }

    
    Vec2 Vec2::operator-(scalar s_) const noexcept
    {
        return Vec2(x-s_, y-s_);
    }
    
    
    Vec2 Vec2::operator*(const Vec2& v2_) const noexcept
    {
        return Vec2(x*v2_.x, y*v2_.y);
    }

    
    Vec2 Vec2::operator*(scalar s_) const noexcept
    {
        return Vec2(x*s_, y*s_);
    }


    Vec2 Vec2::operator/(const Vec2& v2_) const noexcept
    {
        return Vec2(x/v2_.x, y/v2_.y);
    }

    
    Vec2 Vec2::operator/(scalar s_) const noexcept
    {
        return Vec2(x/s_, y/s_);
    }

    


    //(    md Space    )//
    std::ostream& operator<<(std::ostream& os_, const Vec2& v2_) noexcept
    {
        os_<<v2_.x<<" "<<v2_.y;

        return os_;
    }

}
