#ifndef GROUPDATA_TUPLE_INL
#define GROUPDATA_TUPLE_INL

#include "tuple.hpp"
#include <cstring>

namespace gd{

    //+++++++++++++++++++++//
    //    Group Objects    //
    //+++++++++++++++++++++//
    //(    gd::Tuple<As...> Void    )//
    //+    Member Function    +//
    // Constructon Functions
    template <typename... As>
    Tuple<As...>::Tuple(void) noexcept
    {   
        return;
    }
    
    
    template <typename... As>
    Tuple<As...>::Tuple(const Tuple<As...>&) noexcept
    {   
        return;
    }
    
    
    template <typename... As>
    Tuple<As...>::Tuple(Tuple<As...>&&) noexcept
    {   
        return;
    }
    
    
    template <typename... As> template <typename... I>
    Tuple<As...>& Tuple<As...>::construct(I...) noexcept
    {   
        return *this;
    }
   

    
    // Destructon Functions
    template <typename... As>
    Tuple<As...>::~Tuple(void) noexcept
    {
        return;
    }


    template <typename... As>
    Tuple<As...>& Tuple<As...>::destruct(void) noexcept
    {   
        ~Tuple();

        return *this;
    }
    
    
    
    // Access Function
    template <typename... As>
    void Tuple<As ...>::operator= (const Tuple<As...>&) const noexcept
    {
        return;
    }


    // Casting Function
    template <typename... As> template <typename... Bs>
    Tuple<As...>::operator Tuple<Bs...> () const noexcept
    {
        return Tuple<>{ };
    }




    //(    gd::Tuple<T, As...> Aggregated Lamination for Lamination    )//
    //+    Static Functions    +//
    template <typename T, typename... As>
    inline constexpr uint16_t Tuple<T, As...>::depth (Empty) noexcept
    {
        return sizeof...(As)+1;
    }


    template <typename T, typename... As>
    inline constexpr size_t Tuple<T, As...>::size (Empty) noexcept
    {
        return 1;
    }
    
   

    
    //+    Member Functions    +//
    // Constructon Functions
    template <typename T, typename... As>
    Tuple<T, As...>::Tuple(void) noexcept
    {   
        return;
    }
    
    
    template <typename T, typename... As>
    Tuple<T, As...>::Tuple(const Tuple<T, As...>& tp_) noexcept
    {
        std::memcpy(this, &tp_, sizeof *this);
        
        return;
    }
    
    
    template <typename T, typename... As>
    Tuple<T, As...>::Tuple(Tuple<T, As...>&& tp_) noexcept
    {
        std::memcpy(this, &tp_, sizeof *this);
        
        return;
    }
    
    
    template <typename T, typename... As>
    Tuple<T, As...>::Tuple(const T& t_, const As&... as_) noexcept
        : tuples  {as_...}
    {
        std::memcpy(&element, &t_, sizeof t_);
        
        return;
    }
    
    
    template <typename T, typename... As>
    Tuple<T, As...>::Tuple(const T& t_, const Tuple<As ...>& tp_) noexcept
        : tuples  {tp_}
    {
        std::memcpy(&element, &t_, sizeof t_);
        
        return;
    }
    
    
    template <typename T, typename... As> template <typename... I>
    Tuple<T, As...>& Tuple<T, As...>::construct(I... i_) noexcept
    {
        new(this) Tuple(i_...);

        return *this;
    }
    
    

    // Destructon Functions
    template <typename T, typename... As>
    Tuple<T, As...>::~Tuple(void) noexcept
    {   
        return;
    }


    template <typename T, typename... As>
    Tuple<T, As...>& Tuple<T, As...>::destruct(void) noexcept
    {
        ~Tuple();

        return *this;
    }



    // Reference Functions
    template <typename T, typename... As>
    template <uint16_t R>
    const auto& Tuple<T, As...>::path(void) const noexcept
    {
        return _path(Rank<R>{ });
    }
    


    template <typename T, typename... As>
    template <uint16_t R>
    const auto& Tuple<T, As...>::_path(Rank<R>) const noexcept
    {
        return tuples._path(Rank<R-1>{ });
    }
    
    
    
    template <typename T, typename... As>
    const T& Tuple<T, As...>::_path(Rank<0>) const noexcept
    {
        return element;
    }



    template <typename T, typename... As>
    const Tuple<T, As...>* Tuple<T, As...>::data(void) const noexcept
    {
        return this;
    }



    template <typename T, typename... As>
    const Tuple<T, As...>& Tuple<T, As...>::operator[](size_t) const noexcept
    {
        return *this;
    }
    

    
   
    // Access Functions
    template <typename T, typename... As>
    template <uint16_t R>
    auto& Tuple<T, As...>::path(void) noexcept
    {
        return _path(Rank<R>{ });
    }
    


    template <typename T, typename... As>
    template <uint16_t R>
    auto& Tuple<T, As...>::_path(Rank<R>) noexcept
    {
        return tuples._path(Rank<R-1>{ });
    }
    
    
    
    template <typename T, typename... As>
    T& Tuple<T, As...>::_path(Rank<0>) noexcept
    {
        return element;
    }
    
    
    
    template <typename T, typename... As>
    Tuple<T, As...>* Tuple<T, As...>::data(void) noexcept
    {
        return this;
    }



    template <typename T, typename... As>
    Tuple<T, As...>& Tuple<T, As...>::operator[](size_t) noexcept
    {
        return *this;
    }
    

    template <typename T, typename... As>
    Tuple<T, As...>& Tuple<T, As...>::operator= (const Tuple<T, As...>& tp_) noexcept
    {
        element=tp_.element;
        tuples =tp_.tuples;
        
        return *this;
    }
    
    

    template <typename T, typename... As>
    Tuple<T, As...>& Tuple<T, As...>::operator= (Tuple<T, As...>&& tp_) noexcept
    {
        element=std::move(tp_.element);
        tuples =std::move(tp_.tuples);
        
        return *this;
    }
    
    
    
    
    // Casting Functions
    template <typename T, typename... As> template <uint16_t N, typename U, typename... Bs>
    void Tuple<T, As...>::_cast_tuple(Rank<N>, Tuple<U, Bs...>& tp_) const noexcept
    {
        tp_.template path<N>()=this->path<N>();

        _cast_tuple(Rank<N-1>{ }, tp_); 

        return;  
    }


    template <typename T, typename... As> template <typename U, typename... Bs>
    void Tuple<T, As...>::_cast_tuple(Rank<0>, Tuple<U, Bs...>& tp_) const noexcept
    {
        tp_.template path<0>()=this->path<0>();

        return;
    }


    template <typename T, typename... As> template <typename U, typename... Bs>
    Tuple<T, As...>::operator Tuple<U, Bs...> () const noexcept
    {
        Tuple<U, Bs...> tp_;
        _cast_tuple(Rank<(sizeof...(As)>sizeof...(Bs) ? sizeof...(Bs) : sizeof...(As))>{ }, tp_);

        return tp_;
    }
    


    //(    gd::ElasticTuple<As...> Void    )//
    //+    Member Function    +//
    // Constructon Functions
    template <typename... As>
    ElasticTuple<As...>::ElasticTuple(void) noexcept
    {   
        return;
    }
    
    
    template <typename... As>
    ElasticTuple<As...>::ElasticTuple(const ElasticTuple<As...>&) noexcept
    {   
        return;
    }
    
    
    template <typename... As>
    ElasticTuple<As...>::ElasticTuple(ElasticTuple<As...>&&) noexcept
    {   
        return;
    }
    
    
    template <typename... As> template <typename... I>
    ElasticTuple<As...>& ElasticTuple<As...>::construct(I...) noexcept
    {   
        return *this;
    }
   

    
    // Destructon Functions
    template <typename... As>
    ElasticTuple<As...>::~ElasticTuple(void) noexcept
    {
        return;
    }


    template <typename... As>
    ElasticTuple<As...>& ElasticTuple<As...>::destruct(void) noexcept
    {   
        ~ElasticTuple();

        return *this;
    }
    
    
    
    // Access Function
    template <typename... As>
    void ElasticTuple<As ...>::operator= (const ElasticTuple<As...>&) const noexcept
    {
        return;
    }


    // Casting Function
    template <typename... As> template <typename... Bs>
    ElasticTuple<As...>::operator ElasticTuple<Bs...> () const noexcept
    {
        return ElasticTuple<>{ };
    }




    //(    gd::ElasticTuple<T, As...> Aggregated Lamination for Lamination    )//
    //+    Static Functions    +//
    template <typename T, typename... As>
    inline constexpr uint16_t ElasticTuple<T, As...>::depth (Empty) noexcept
    {
        return sizeof...(As)+1;
    }


    template <typename T, typename... As>
    inline constexpr size_t ElasticTuple<T, As...>::size (Empty) noexcept
    {
        return 1;
    }
    
   

    
    //+    Member Functions    +//
    // Constructon Functions
    template <typename T, typename... As>
    ElasticTuple<T, As...>::ElasticTuple(void) noexcept
        : element { }
        , tuples  { }
    {   
        return;
    }
    
    
    template <typename T, typename... As>
    ElasticTuple<T, As...>::ElasticTuple(const ElasticTuple<T, As...>& tp_) noexcept
        : element {tp_.element}
        , tuples  {tp_.tuples}
    {
        return;
    }
    
    
    template <typename T, typename... As>
    ElasticTuple<T, As...>::ElasticTuple(ElasticTuple<T, As...>&& tp_) noexcept
        : element {std::move(tp_.element)}
        , tuples  {std::move(tp_.tuples)}
    {
        return;
    }
    
    
    template <typename T, typename... As>
    ElasticTuple<T, As...>::ElasticTuple(const T& t_, const As&... as_) noexcept
        : element {t_}
        , tuples  {as_...}
    {
        return;
    }
    
    
    template <typename T, typename... As>
    ElasticTuple<T, As...>::ElasticTuple(const T& t_, const ElasticTuple<As ...>& tp_) noexcept
        : element {t_}
        , tuples  {tp_}
    {
        return;
    }
    
    
    template <typename T, typename... As> template <typename... I>
    ElasticTuple<T, As...>& ElasticTuple<T, As...>::construct(I... i_) noexcept
    {
        new(this) ElasticTuple(i_...);

        return *this;
    }
    
    

    // Destructon Functions
    template <typename T, typename... As>
    ElasticTuple<T, As...>::~ElasticTuple(void) noexcept
    {   
        return;
    }


    template <typename T, typename... As>
    ElasticTuple<T, As...>& ElasticTuple<T, As...>::destruct(void) noexcept
    {
        ~ElasticTuple();

        return *this;
    }



    // Reference Functions
    template <typename T, typename... As>
    template <uint16_t R>
    const auto& ElasticTuple<T, As...>::path(void) const noexcept
    {
        return _path(Rank<R>{ });
    }

    

    template <typename T, typename... As>
    template <uint16_t R>
    const auto& ElasticTuple<T, As...>::_path(Rank<R>) const noexcept
    {
        return tuples._path(Rank<R-1>{ });
    }
    
    
    
    template <typename T, typename... As>
    const T& ElasticTuple<T, As...>::_path(Rank<0>) const noexcept
    {
        return element;
    }



    template <typename T, typename... As>
    const ElasticTuple<T, As...>* ElasticTuple<T, As...>::data(void) const noexcept
    {
        return this;
    }



    template <typename T, typename... As>
    const ElasticTuple<T, As...>& ElasticTuple<T, As...>::operator()(size_t) const noexcept
    {
        return *this;
    }


    
   
    // Access Functions
    template <typename T, typename... As>
    template <uint16_t R>
    auto& ElasticTuple<T, As...>::path(void) noexcept
    {
        return _path(Rank<R>{ });
    }
    


    template <typename T, typename... As>
    template <uint16_t R>
    auto& ElasticTuple<T, As...>::_path(Rank<R>) noexcept
    {
        return tuples._path(Rank<R-1>{ });
    }
    
    
    
    template <typename T, typename... As>
    T& ElasticTuple<T, As...>::_path(Rank<0>) noexcept
    {
        return element;
    }
    
    
    
    template <typename T, typename... As>
    ElasticTuple<T, As...>* ElasticTuple<T, As...>::data(void) noexcept
    {
        return this;
    }



    template <typename T, typename... As>
    ElasticTuple<T, As...>& ElasticTuple<T, As...>::operator[](size_t) noexcept
    {
        return *this;
    }
    

    template <typename T, typename... As>
    ElasticTuple<T, As...>& ElasticTuple<T, As...>::operator= (const ElasticTuple<T, As...>& tp_) noexcept
    {
        element=tp_.element;
        tuples =tp_.tuples;
        
        return *this;
    }


    template <typename T, typename... As>
    ElasticTuple<T, As...>& ElasticTuple<T, As...>::operator= (ElasticTuple<T, As...>&& tp_) noexcept
    {
        element=std::move(tp_.element);
        tuples =std::move(tp_.tuples);
        
        return *this;
    }
    

    template <typename T, typename... As> template <typename... Bs>
    ElasticTuple<T, As...>& ElasticTuple<T, As...>::operator= (const ElasticTuple<std::remove_reference_t<T>, Bs...>& tp_) noexcept
    {
        element=tp_.element;
        tuples =tp_.tuples;
        
        return *this;
    }


    template <typename T, typename... As> template <typename... Bs>
    ElasticTuple<T, As...>& ElasticTuple<T, As...>::operator= (ElasticTuple<std::remove_reference_t<T>, Bs...>&& tp_) noexcept
    {
        element=std::move(tp_.element);
        tuples =std::move(tp_.tuples);
        
        return *this;
    }

    
    
    // Casting Functions
    template <typename T, typename... As> template <uint16_t N, typename U, typename... Bs>
    void ElasticTuple<T, As...>::_cast_tuple(Rank<N>, ElasticTuple<U, Bs...>& tp_) const noexcept
    {

        tp_.template path<N>()=this->path<N>();

        _cast_tuple(Rank<N-1>{ }, tp_); 

        return;  
    }


    template <typename T, typename... As> template <typename U, typename... Bs>
    void ElasticTuple<T, As...>::_cast_tuple(Rank<0>, ElasticTuple<U, Bs...>& tp_) const noexcept
    {
        tp_.template path<0>()=this->path<0>();

        return;
    }


    template <typename T, typename... As> template <typename U, typename... Bs>
    ElasticTuple<T, As...>::operator ElasticTuple<U, Bs...> () const noexcept
    {
        ElasticTuple<U, Bs...> tp_;
        
        _cast_tuple(Rank<(sizeof...(As)>sizeof...(Bs) ? sizeof...(Bs) : sizeof...(As))>{ }, tp_);

        return tp_;
    }
            
        
    
    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <typename... As>
    std::ostream& operator<<(std::ostream& os_, const gd::Tuple<As...>& tp_) noexcept
    {
        return os_;
    }


    template <typename T, typename... As>
    std::ostream& operator<<(std::ostream& os_, const gd::Tuple<T, As...>& tp_) noexcept
    {
        gd::ostream(tp_.element, os_);
        os_<<" ";
        gd::ostream(tp_.tuples, os_);

        return os_;
    }
    
    
    template <typename... As>
    std::ostream& operator<<(std::ostream& os_, const gd::ElasticTuple<As...>& tp_) noexcept
    {
        return os_;
    }


    template <typename T, typename... As>
    std::ostream& operator<<(std::ostream& os_, const gd::ElasticTuple<T, As...>& tp_) noexcept
    {
        gd::ostream(tp_.element, os_);
        os_<<" ";
        gd::ostream(tp_.tuples, os_);

        return os_;
    }

}


/*
int main(void){

    {
        gd::Tuple<double, int> tp1= {0.1, 10};
        gd::Tuple<double, float> tp2= {0.1, 30.0};
        tp1=tp2;
        std::cout<<tp1<<" "<<std::endl;
    }
}*/

#endif
