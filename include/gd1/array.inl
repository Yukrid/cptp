#ifndef GROUPDATA_ARRAY_INL
#define GROUPDATA_ARRAY_INL

#include "array.hpp"

#include <cstring>

namespace gd{

    //+++++++++++++++++++++//
    //    Array Objects    //
    //+++++++++++++++++++++/
    //(    gd::Array Lamination for Lamination    )//
    //+    Static Functions    +//
    template <size_t S, typename T>
    constexpr uint16_t Array<S, T>::depth(Empty) noexcept
    {
        return 1;   
    }
    
    
    template <size_t S, typename T>
    constexpr size_t Array<S, T>::size(Empty) noexcept
    {
        return S;   
    }

    
        
    //+    Member Functions    +//
    // Construcntion Functions
    template <size_t S, typename T>
    Array<S, T>::Array(void) noexcept
    {
        return;
    }


    template <size_t S, typename T>
    Array<S, T>::Array(const Array<S, T>& ar_) noexcept
    {
        std::memcpy(_elements, ar_._elements, S*sizeof(T));
        
        return;
    }
    
    
    template <size_t S, typename T>
    Array<S, T>::Array(Array<S, T>&& ar_) noexcept
    {
        std::memcpy(_elements, ar_._elements, S*sizeof(T));
        
        return;
    }
    
        
    template <size_t S, typename T>
    Array<S, T>::Array(std::initializer_list<T> lst_) noexcept
    {
        std::memcpy(_elements, lst_.begin(), sizeof(T)*(S>lst_.size() ? lst_.size() : S));
        for(size_t a=lst_.size(); a<S; ++a){
            std::memcpy(_elements+a, lst_.end()-1, sizeof(T));
        }

        return;
    }


    template <size_t S, typename T> template <typename... I>
    Array<S, T>& Array<S, T>::construct(I... i_) noexcept
    {
        new(this) Array(i_...);

        return *this;
    }

    

    // Destruction Functions
    template <size_t S, typename T>
    Array<S, T>::~Array(void) noexcept
    {
        return;
    }
    
    
    template <size_t S, typename T>
    Array<S, T>& Array<S, T>::destruct(void) noexcept
    {
        return *this;
    }

    

    // Reference Functions
    template <size_t S, typename T> template<uint16_t N>
    auto Array<S, T>::ref(void) const noexcept -> typename std::enable_if_t<(N==0), const T*>
    {
        return _elements;
    }
    
    
    template <size_t S, typename T>
    const T* Array<S, T>::ref(uint16_t) const noexcept
    {
        return _elements;
    }

   
    template <size_t S, typename T>
    const T* Array<S, T>::spec(void) const noexcept
    { 
        return _elements;
    }
    
     
    #ifdef GROUPDATA_ARRAY_EXCEPTION
    template <size_t S, typename T>
    const T& Array<S, T>::operator()(const size_t& s_) const
    { 
        if(s_>=S) throw exception::exceeded_capacity_in_size_direction(std::string{"[gd::Array<"}+std::to_string(S)+", "+typeid(T).name()+">::operator()(const size_t&)]", S, s_);
        return _elements[s_];
    }

    #else

    template <size_t S, typename T>
    const T& Array<S, T>::operator()(const size_t& s_) const noexcept
    { 
        return _elements[s_];
    }
    #endif


    template <size_t S, typename T>
    Range<const T> Array<S, T>::range(const size_t& e_) const noexcept
    { 
        return Range<const T>{_elements, _elements+e_};
    }
    
    
    template <size_t S, typename T>
    Range<const T> Array<S, T>::range(const size_t& b_, const size_t& e_) const noexcept
    { 
        return Range<const T>{_elements+b_, _elements+e_};
    }



    // Access functions
    template <size_t S, typename T> template<uint16_t N>
    auto Array<S, T>::path(void) noexcept -> typename std::enable_if_t<(N==0), T*>
    {
        return _elements;
    }
    
    
    template <size_t S, typename T>
    T* Array<S, T>::path(uint16_t) noexcept
    {
        return _elements;
    }
    
    
    template <size_t S, typename T>
    T* Array<S, T>::data(void) noexcept
    { 
        return _elements;
    }
    
    
    #ifdef GROUPDATA_ARRAY_EXCEPTION
    template <size_t S, typename T>
    T& Array<S, T>::operator[](const size_t& s_)
    { 
        if(s_>=S) throw exception::exceeded_capacity_in_size_direction(std::string{"[gd::Array<"}+std::to_string(S)+", "+typeid(T).name()+">::operator[](const size_t&)]", S, s_);
        return _elements[s_];
    }

    #else

    template <size_t S, typename T>
    T& Array<S, T>::operator[](const size_t& s_) noexcept
    { 
        return _elements[s_];
    }
    #endif
    
    template <size_t S, typename T>
    Array<S, T>& Array<S, T>::operator=(const Array<S, T>& ar_) noexcept
    { 
        std::memcpy(_elements, ar_._elements, S*sizeof(T));
        
        return *this;
    }
   
   
    template <size_t S, typename T>
    Array<S, T>& Array<S, T>::operator=(Array<S, T>&& ar_) noexcept
    { 
        std::memcpy(_elements, ar_._elements, S*sizeof(T));
        
        return *this;
    }
 
    
    template <size_t S, typename T>
    Range<T> Array<S, T>::range(const size_t& e_) noexcept
    { 
        return Range<T>{_elements, _elements+e_};
    }
    
    
    template <size_t S, typename T>
    Range<T> Array<S, T>::range(const size_t& b_, const size_t& e_) noexcept
    { 
        return Range<T>{_elements+b_, _elements+e_};
    }

    

    // Casting Functions
    template <size_t S, typename T> template <size_t R, typename U>
    Array<S, T>::operator Array<R, U> () const noexcept
    {
        Array<R, U> ar;
        std::memcpy(_elements, ar._elements, sizeof(T)*(S>R ? R : S));
        for(size_t a=R; a<S; ++a){
            std::memcpy(_elements+a, ar._elements+R-1, sizeof(T));
        }
    
        return ar;
    }
    
    

    
    //(    gd::ElasticArray Lamination for Lamination    )//
    //+    Static Functions    +//
    template <size_t S, typename T>
    constexpr uint16_t ElasticArray<S, T>::depth(Empty) noexcept
    {
        return 1;   
    }
    
    
    template <size_t S, typename T>
    constexpr size_t ElasticArray<S, T>::size(Empty) noexcept
    {
        return S;   
    }

    
        
    //+    Member Functions    +//
    // Construcntion Functions
    template <size_t S, typename T>
    ElasticArray<S, T>::ElasticArray(void) noexcept
        : _elements { }
    {
        return;
    }


    template <size_t S, typename T>
    ElasticArray<S, T>::ElasticArray(const ElasticArray<S, T>& ar_) noexcept
        : _elements { }
    {
        for(uint16_t a=0; a<S; ++a){
            (_elements+a)->~T();
            new (_elements+a) T{ar_(a)};
        }
        
        return;
    }
    
    
    template <size_t S, typename T>
    ElasticArray<S, T>::ElasticArray(ElasticArray<S, T>&& ar_) noexcept
        : _elements { }
    {
        for(uint16_t a=0; a<S; ++a){
            (_elements+a)->~T();
            new (_elements+a) T{std::move(ar_[a])};
        }
        
        return;
    }
    
        
    template <size_t S, typename T>
    ElasticArray<S, T>::ElasticArray(std::initializer_list<T> lst_) noexcept
        : _elements { }
    {
        for(uint16_t a=0; a<S && a<lst_.size(); ++a){
            (_elements+a)->~T();
            new (_elements+a) T{lst_.begin()[a]};
        }
        for(uint16_t a=lst_.size(); a<S; ++a){
            (_elements+a)->~T();
            new (_elements+a) T{lst_.end()[-1]};
        }

        return;
    }


    template <size_t S, typename T> template <typename... I>
    ElasticArray<S, T>& ElasticArray<S, T>::construct(I... i_) noexcept
    {
        new(this) ElasticArray(i_...);

        return *this;
    }

    

    // Destruction Functions
    template <size_t S, typename T>
    ElasticArray<S, T>::~ElasticArray(void) noexcept
    {
        return;
    }
    
    
    template <size_t S, typename T>
    ElasticArray<S, T>& ElasticArray<S, T>::destruct(void) noexcept
    {
        return *this;
    }

    

    // Reference Functions
    template <size_t S, typename T> template<uint16_t N>
    auto ElasticArray<S, T>::ref(void) const noexcept -> typename std::enable_if_t<(N==0), const T*>
    {
        return _elements;
    }
    
    
    template <size_t S, typename T>
    const T* ElasticArray<S, T>::ref(uint16_t) const noexcept
    {
        return _elements;
    }

   
    template <size_t S, typename T>
    const T* ElasticArray<S, T>::spec(void) const noexcept
    { 
        return _elements;
    }
    
     
    #ifdef GROUPDATA_ARRAY_EXCEPTION
    template <size_t S, typename T>
    const T& ElasticArray<S, T>::operator()(const size_t& s_) const
    { 
        if(s_>=S) throw exception::exceeded_capacity_in_size_direction(std::string{"[gd::ElasticArray<"}+std::to_string(S)+", "+typeid(T).name()+">::operator()(const size_t&)]", S, s_);
        return _elements[s_];
    }

    #else

    template <size_t S, typename T>
    const T& ElasticArray<S, T>::operator()(const size_t& s_) const noexcept
    { 
        return _elements[s_];
    }
    #endif


    template <size_t S, typename T>
    Range<const T> ElasticArray<S, T>::range(const size_t& e_) const noexcept
    { 
        return Range<const T>{_elements, _elements+e_};
    }
    
    
    template <size_t S, typename T>
    Range<const T> ElasticArray<S, T>::range(const size_t& b_, const size_t& e_) const noexcept
    { 
        return Range<const T>{_elements+b_, _elements+e_};
    }



    // Access functions
    template <size_t S, typename T> template<uint16_t N>
    auto ElasticArray<S, T>::path(void) noexcept -> typename std::enable_if_t<(N==0), T*>
    {
        return _elements;
    }
    
    
    template <size_t S, typename T>
    T* ElasticArray<S, T>::path(uint16_t) noexcept
    {
        return _elements;
    }
    
    
    template <size_t S, typename T>
    T* ElasticArray<S, T>::data(void) noexcept
    { 
        return _elements;
    }
    
    
    #ifdef GROUPDATA_ARRAY_EXCEPTION
    template <size_t S, typename T>
    T& ElasticArray<S, T>::operator[](const size_t& s_)
    { 
        if(s_>=S) throw exception::exceeded_capacity_in_size_direction(std::string{"[gd::ElasticArray<"}+std::to_string(S)+", "+typeid(T).name()+">::operator[](const size_t&)]", S, s_);
        return _elements[s_];
    }

    #else

    template <size_t S, typename T>
    T& ElasticArray<S, T>::operator[](const size_t& s_) noexcept
    { 
        return _elements[s_];
    }
    #endif
    
    template <size_t S, typename T>
    ElasticArray<S, T>& ElasticArray<S, T>::operator=(const ElasticArray<S, T>& ar_) noexcept
    { 
        for(uint16_t a=0; a<S; ++a){
            _elements[a]=ar_(a);
        }

        return *this;
    }

   
    template <size_t S, typename T>
    ElasticArray<S, T>& ElasticArray<S, T>::operator=(ElasticArray<S, T>&& ar_) noexcept
    { 
        std::memcpy(_elements, ar_._elements, S*sizeof(T));
        
        return *this;
    }
 
    
    template <size_t S, typename T>
    Range<T> ElasticArray<S, T>::range(const size_t& e_) noexcept
    { 
        return Range<T>{_elements, _elements+e_};
    }
    
    
    template <size_t S, typename T>
    Range<T> ElasticArray<S, T>::range(const size_t& b_, const size_t& e_) noexcept
    { 
        return Range<T>{_elements+b_, _elements+e_};
    }

    

    // Casting Functions
    template <size_t S, typename T> template <size_t R, typename U>
    ElasticArray<S, T>::operator ElasticArray<R, U> () const noexcept
    {
        ElasticArray<R, U> ar;
        for(size_t a=0; a<R && a<S; ++a){
            ar[a]=_elements(a);
        }
        for(size_t a=S; a<R; ++a){
            ar[a]=_elements(S-1);
        }
    
        return ar;
    }

   

    
    
    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <size_t S, typename T>
    std::ostream& operator<<(std::ostream& os_, const gd::Array<S, T>& arr_) noexcept
    {
        if(arr_.size()) gd::ostream(arr_(0), os_);
        for(const T& a : arr_.range(1, S)){
            os_<<std::endl;
            gd::ostream(a, os_);
        }
          
        return os_;
    }
}

#endif

