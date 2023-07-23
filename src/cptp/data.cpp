#include <cptp/data.hpp>

namespace cptp{
    
    //(    cptp::Data2D Relocatable Memory Class    )//
    //-> data.hpp data.inl data.cpp
    //+     Member Function    +//
    //_ Constuctor
    Data2D::Data2D(std::ifstream& ifs_, uint16_t x_, uint16_t y_) noexcept
    {
        std::string str;
        while(std::getline(ifs_, str)){
            scalar x, y, value;
            std::stringstream ss1;
            ss1<<str;
            uint_fast16_t line=(x_<y_ ? y_ : x_)+1;
            for(uint_fast16_t a=0; a<line; ++a){
                ss1>>value;
                if(a==x_) x=value;
                if(a==y_) y=value;
            }
            _datas.pushBack(gd::Tuple<scalar, scalar>(x, y));
        }
    }


    Data2D::Data2D(std::ifstream& ifs_, Index, uint16_t y_) noexcept
    {
        std::string str;
        uint64_t count=0;
        while(std::getline(ifs_, str)){
            scalar y, value;
            std::stringstream ss1;
            ss1<<str;
            for(uint_fast16_t a=0; a<y_+1; ++a){
                ss1>>value;
                if(a==y_) y=value;
            }
            _datas.pushBack(gd::Tuple<scalar, scalar>(count++, y));
        }
    }
 

    Data2D::Data2D(std::ifstream& ifs_, uint16_t x_, Index) noexcept
    {
        std::string str;
        uint64_t count=0;
        while(std::getline(ifs_, str)){
            scalar x, value;
            std::stringstream ss1;
            ss1<<str;
            for(uint_fast16_t a=0; a<x_+1; ++a){
                ss1>>value;
                if(a==x_) x=value;
            }
            _datas.pushBack(gd::Tuple<scalar, scalar>(x, count++));
        }
    }
   


    Data2D& Data2D::construct(void) noexcept
    {
        new(this) Data2D();

        return *this;
    }


   

     
    //_ Destructor
    Data2D& Data2D::destruct(void) noexcept
    {
        this->~Data2D();
        return *this;
    }



    //_ Writer
    void Data2D::info (std::ostream& os_, uint_fast8_t offset_) const noexcept
    {
        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::Data2D Relocatable Memory Class Template]"<<std::endl;
        os_<<str<<"(size)            : "<<sizeof(Data2D)<<std::endl;
        os_<<str<<"(name)            : "<<typeid(Data2D).name()<<std::endl;
        os_<<str<<"(address)         : "<<this<<std::endl;
        os_<<str<<"(memory)          : "<<_memory()<<std::endl;
        os_<<str<<"Data Length       : "<<_datas.size()<<std::endl;
        os_<<str<<"X Address         : "<<_datas.path<0>().data()<<std::endl;
        os_<<str<<"Y Address         : "<<_datas.path<1>().data()<<std::endl;
        if(_datas.size()>0){
                os_<<str<<"First Data        : "<<_datas[0]<<std::endl;
            if(_datas.size()>=2){
                os_<<str<<"Last  Data        : "<<_datas[_datas.size()-1]<<std::endl;
            }
        }

        return;
    }



    //_ Accessor
    Data2D::Series2D& Data2D::datas (void) noexcept
    {
        return _datas;
    }



    //_ Referencer
    const Data2D::Series2D& Data2D::datas (void) const noexcept
    {
        return _datas;
    }


    const size_t& Data2D::length (void) const noexcept
    {
        return _datas.size();
    }


    const Data2D::Separators& Data2D::separator (void) const noexcept
    {
        return _separators;
    }


    const Data2D::Skipper& Data2D::skipper (void) const noexcept
    {
        return _skipper;
    }
    

    void  Data2D::separate (size_t pos_) noexcept
    {
        _separators.insert(pos_);

        return;
    }

    void  Data2D::skip (size_t pos_) noexcept
    {
        if(pos_==0){
            _separators.insert(0);
        }else{
            _separators.insert(pos_-1);
            _separators.insert(pos_);
        }

        _skipper.insert(pos_);

        return;
    }


    //_ Constant Function
    size_t Data2D::_memory(void) const noexcept
    {
        return _datas.path<0>().capacity()+_datas.path<1>().capacity();
    }
    
}
