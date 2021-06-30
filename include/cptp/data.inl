//#include "data.hpp"

namespace cptp{
    
    //(    cptp::Data<T> Relocatable Structure    )//
    //+     Member Function    +//
    //_ Constructor
    template <typename T>
    Data<T>::Data(void) noexcept
        : _begin  {nullptr}
        , _end    {nullptr}
        , _length { }
    {
        return;
    }

    
    template <typename T>
    Data<T>::Data(const T* begin_, const T* end_) noexcept
        : _begin  {begin_}
        , _end    {end_}
        , _length {static_cast<size_t>(end_-begin_)}
    {
        return;
    }
    
    
    template <typename T>
    Data<T>::Data(const T* begin_, const size_t& size_) noexcept
        : _begin  {begin_}
        , _end    {begin_+size_}
        , _length {size_}
    {
        return;
    }
 

    template <typename T>
    Data<T>& Data<T>::construct(const T* begin_, const T* end_) noexcept
    {
        new(this) Data(begin_, end_);

        return *this;
    }


    template <typename T>
    Data<T>& Data<T>::construct(const T* begin_, const size_t& sz_) noexcept
    {
        new(this) Data(begin_, sz_);

        return *this;
    }
    


    //_ Destructor
    template <typename T>
    Data<T>::~Data(void) noexcept
    {
        _begin =nullptr;
        _end   =nullptr;
        _length=0;

        return;
    }
 

    template <typename T>
    Data<T>& Data<T>::destruct(void) noexcept
    {
        this->~Data();
        
        return *this;
    }
        


    //_ Writer
    template <typename T>
    void Data<T>::info (std::ostream& os_, uint_fast8_t offset_) const noexcept
    {
        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::Data<T> Relocatable Class Template]"<<std::endl;
        os_<<str<<"(size)         : "<<sizeof(Data)<<std::endl;
        os_<<str<<"(name)         : "<<typeid(Data).name()<<std::endl;
        os_<<str<<"(address)      : "<<this<<std::endl;
        os_<<str<<"(memory)       : "<<0<<std::endl;
        os_<<str<<"(template)     : "<<"<"<<typeid(T).name()<<">"<<std::endl;
        os_<<str<<"Begin Pointer  : "<<_begin<<std::endl;
        os_<<str<<"End Pointer    : "<<_end<<std::endl;
        os_<<str<<"Length         : "<<_length<<std::endl;

        return;
    }
    


    //_ Referencer
    template <typename T>
    const T* Data<T>::begin(void) const noexcept
    {   
        return _begin;
    }
    
    
    template <typename T>
    const T* Data<T>::end(void) const noexcept
    {   
        return _end;
    }
    
    
    template <typename T>
    const size_t& Data<T>::length(void) const noexcept
    {   
        return _length;
    }
    


    //(    cptp::Data2D Relocatable Memory Class    )//
    //-> data.hpp data.inl data.cpp
    //+     Member Function    +//
    //_ Constuctor
    template <typename T, typename U>
    Data2D::Data2D(const Data<T>& x_, const Data<U>& y_, const Separators& sep_) noexcept
        : _datas        ( )
        , _separators (sep_)
    {
        _datas.resize(x_.length()<y_.length() ? x_.length() : y_.length());
        
        scalar* xs=_datas.path<0>().data();
        for(size_t a=0; a<_datas.size(); ++a){
            xs[a]=static_cast<scalar>(x_.begin()[a]);
        }

        scalar* ys=_datas.path<1>().data();
        for(size_t a=0; a<_datas.size(); ++a){
            ys[a]=static_cast<scalar>(y_.begin()[a]);
        }

        return;
    }

     
    template <typename U>
    Data2D::Data2D(Index, const Data<U>& y_, const Separators& sep_) noexcept
        : _datas        ( )
        , _separators (sep_)
    {
        _datas.resize(y_.length());
        
        scalar* xs=_datas.path<0>().data();
        for(size_t a=0; a<_datas.size(); ++a){
            xs[a]=static_cast<scalar>(a+1);
        }

        scalar* ys=_datas.path<1>().data();
        for(size_t a=0; a<_datas.size(); ++a){
            ys[a]=static_cast<scalar>(y_.begin()[a]);
        }

        return;
    }
    
    
    template <typename T>
    Data2D::Data2D(const Data<T>& x_, Index, const Separators& sep_) noexcept
        : _datas     ( )
        , _separators (sep_)
    {
        _datas.resize(x_.length());
        
        scalar* xs=_datas.path<0>().data();
        for(size_t a=0; a<_datas.size(); ++a){
            xs[a]=static_cast<scalar>(x_.begin()[a]);
        }

        scalar* ys=_datas.path<1>().data();
        for(size_t a=0; a<_datas.size(); ++a){
            ys[a]=static_cast<scalar>(a+1);
        }

        return;
    }
     
    
    template <typename T, typename U>
    Data2D& Data2D::construct(const Data<T>& x_, const Data<U>& y_, const Separators& sep_) noexcept
    {
        new(this) Data2D(x_, y_, sep_);

        return *this;
    }


    template <typename U>
    Data2D& Data2D::construct(Index i_, const Data<U>& y_, const Separators& sep_) noexcept
    {
        new(this) Data2D(i_, y_, sep_);

        return *this;
    }


    template <typename T>
    Data2D& Data2D::construct(const Data<T>& x_, Index i_, const Separators& sep_) noexcept
    {
        new(this) Data2D(x_, i_, sep_);

        return *this;
    }
 

    template <typename T, typename U>
    Data2D& Data2D::reconstruct(const Data<T>& x_, const Data<U>& y_, const Separators& sep_) noexcept
    {
        this->~Data2D();
        new(this) Data2D(x_, y_, sep_);

        return *this;
    }
    

    template <typename U>
    Data2D& Data2D::reconstruct(Index i_, const Data<U>& y_, const Separators& sep_) noexcept
    {
        this->~Data2D();
        new(this) Data2D(i_, y_, sep_);

        return *this;
    }


    template <typename T>
    Data2D& Data2D::reconstruct(const Data<T>& x_, Index i_, const Separators& sep_) noexcept
    {
        this->~Data2D();
        new(this) Data2D(x_, i_, sep_);

        return *this;
    }
 
}
