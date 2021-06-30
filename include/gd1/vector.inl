#ifndef GROUPDATA_VECTOR_INL
#define GROUPDATA_VECTOR_INL

#include "vector.hpp"

#include <cstring>

namespace gd{

    //+++++++++++++++++++++++++++++++++++++++++++//
    //    gd::Vector Structure for Lamination    //
    //+++++++++++++++++++++++++++++++++++++++++++//
    //+    Static Functions    +//
    template <size_t S, typename T>
    constexpr uint16_t Vector<S, T>::depth(Empty) noexcept
    {
        return 1;   
    }
    
    
    
    template <size_t S, typename T>
    constexpr size_t Vector<S, T>::size(Empty) noexcept
    {
        return S; 
    }

    
        

    //+    Member Functions    +//
    // Construcntion Functions
    template <size_t S, typename T>
    Vector<S, T>::Vector(void) noexcept
        : _elements {new T[S]}
    {
        return;
    }
    

    template <size_t S, typename T>
    Vector<S, T>::Vector(const Vector<S, T>& vec_) noexcept
        : _elements {new T[vec_.size()]}
    {
        std::memcpy(_elements, vec_._elements, S*sizeof(T));
        return;
    }
    
        
    template <size_t S, typename T>
    Vector<S, T>::Vector(Vector<S, T>&& vec_) noexcept
        : _elements {vec_._elements}
    {
        vec_._elements=nullptr;
        return;
    }
    

    template <size_t S, typename T>
    Vector<S, T>::Vector(std::initializer_list<T> lst_) noexcept
        : _elements {new T[S]}
    {
        std::memcpy(_elements, lst_.begin(), sizeof(T)*(S>lst_.size() ? lst_.size() : S));
        for(size_t a=lst_.size(); a<S; ++a){
            std::memcpy(_elements+a, lst_.end()-1, sizeof(T));
        }

        return;
    }


    template <size_t S, typename T> template <typename... I>
    Vector<S, T>& Vector<S, T>::construct(I... i_) noexcept
    {
        new(this) Vector(i_...);

        return *this;
    }
    
    

    // Destruction Functions
    template <size_t S, typename T>
    Vector<S, T>::~Vector(void) noexcept
    {
        #ifdef GROUPDATA_VECTOR_WARNING
        if(_elements){
            delete[] _elements;
            _elements=nullptr;
        }else{
            warning::double_delete{std::string{"[gd::Vector<"}+std::to_string(S)+", "+typeid(T).name()+">::~Vector(void)]", "_elements"};
        }
        #else
        if(_elements){
            delete[] _elements;
            _elements=nullptr;
        }
        #endif

        return;
    }


    template <size_t S, typename T>
    Vector<S, T>& Vector<S, T>::destruct(void) noexcept
    {
        this->~Vector<S, T>();
               
        return *this;
    }


   
    // Reference functions
    template <size_t S, typename T> template<uint16_t N>
    auto Vector<S, T>::ref(void) const noexcept -> typename std::enable_if_t<(N==0), const T*>
    {
        return _elements;
    }
    
    

    template <size_t S, typename T>
    const T* Vector<S, T>::ref(uint16_t) const noexcept
    {
        return _elements;
    }

   
    
    template <size_t S, typename T>
    const T* Vector<S, T>::spec(void) const noexcept
    { 
        return _elements;
    }
    
    
    
    #ifdef GROUPDATA_VECTOR_EXCEPTION
    template <size_t S, typename T>
    const T& Vector<S, T>::operator()(const size_t& s_) const
    { 
        if(s_>=S) throw exception::exceeded_capacity_in_size_direction(std::string{"[gd::Vector<"}+std::to_string(S)+", "+typeid(T).name()+">::operator()(const size_t&)]", S, s_);
        return _elements[s_];
    }

    #else

    template <size_t S, typename T>
    const T& Vector<S, T>::operator()(const size_t& s_) const noexcept
    { 
        return _elements[s_];
    }

    #endif
    
    
    template <size_t S, typename T>
    Range<const T> Vector<S, T>::range(const size_t& e_) const noexcept
    { 
        return Range<const T>{_elements, _elements+e_};
    }
    
    
    template <size_t S, typename T>
    Range<const T> Vector<S, T>::range(const size_t& b_, const size_t& e_) const noexcept
    { 
        return Range<const T>{_elements+b_, _elements+e_};
    }

    

    // Access functions
    template <size_t S, typename T> template<uint16_t N>
    auto Vector<S, T>::path(void) noexcept -> typename std::enable_if_t<(N==0), T*>
    {
        return _elements;
    }
     
    
    template <size_t S, typename T>
    T* Vector<S, T>::path(uint16_t) noexcept
    {
        return _elements;
    }
    
    
    template <size_t S, typename T>
    T* Vector<S, T>::data(void) noexcept
    { 
        return _elements;
    }
    
    
    #ifdef GROUPDATA_VECTOR_EXCEPTION
    template <size_t S, typename T>
    T& Vector<S, T>::operator[](const size_t& s_)
    { 
        if(s_>=S) throw exception::exceeded_capacity_in_size_direction(std::string{"[gd::Vector<"}+std::to_string(S)+", "+typeid(T).name()+">::operator[](const size_t&)]", S, s_);
        return _elements[s_];
    }

    #else

    template <size_t S, typename T>
    T& Vector<S, T>::operator[](const size_t& s_) noexcept
    { 
        return _elements[s_];
    }
    #endif
    

    template <size_t S, typename T>
    Vector<S, T>& Vector<S, T>::operator=(const Vector<S, T>& vec_) noexcept
    {
        std::memcpy(_elements, vec_._elements, S*sizeof(T));
        
        return *this;
    }
    
    
    template <size_t S, typename T>
    Vector<S, T>& Vector<S, T>::operator=(Vector<S, T>&& vec_) noexcept
    {
        std::memcpy(_elements, vec_._elements, S*sizeof(T));
        
        return *this;
    }
    
    
    template <size_t S, typename T>
    Range<T> Vector<S, T>::range(const size_t& e_) noexcept
    { 
        return Range<T>{_elements, _elements+e_};
    }
    
    
    template <size_t S, typename T>
    Range<T> Vector<S, T>::range(const size_t& b_, const size_t& e_) noexcept
    { 
        return Range<T>{_elements+b_, _elements+e_};
    }


    
    // Casting Functions
    template <size_t S, typename T> template <size_t R, typename U>
    Vector<S, T>::operator Vector<R, U> () const noexcept
    {
        Vector<R, U> vec;
        std::memcpy(_elements, vec._elements, sizeof(T)*(S>R ? R : S));
        for(size_t a=R; a<S; ++a){
            std::memcpy(_elements+a, vec._elements+R-1, sizeof(T));
        }

        return vec;
    }
 
 
 

    //+++++++++++++++++++++++++++++++++++++++++++//
    //    gd::ElasticVector Structure for Lamination    //
    //+++++++++++++++++++++++++++++++++++++++++++//
    //+    Static Functions    +//
    template <size_t S, typename T>
    constexpr uint16_t ElasticVector<S, T>::depth(Empty) noexcept
    {
        return 1;   
    }
    
    
    
    template <size_t S, typename T>
    constexpr size_t ElasticVector<S, T>::size(Empty) noexcept
    {
        return S; 
    }

    
        

    //+    Member Functions    +//
    // Construcntion Functions
    template <size_t S, typename T>
    ElasticVector<S, T>::ElasticVector(void) noexcept
        : _elements {new T[S]}
    {
        return;
    }
    

    template <size_t S, typename T>
    ElasticVector<S, T>::ElasticVector(const ElasticVector<S, T>& vec_) noexcept
        : _elements {new T[vec_.size()]}
    {
        for(uint16_t a=0; a<S; ++a){
            (_elements+a)->~T();
            new (_elements+a) T{vec_(a)};
        }

        return;
    }
    
        
    template <size_t S, typename T>
    ElasticVector<S, T>::ElasticVector(ElasticVector<S, T>&& vec_) noexcept
        : _elements {vec_._elements}
    {
        vec_._elements=nullptr;
        return;
    }
    

    template <size_t S, typename T>
    ElasticVector<S, T>::ElasticVector(std::initializer_list<T> lst_) noexcept
        : _elements {new T[S]}
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
    ElasticVector<S, T>& ElasticVector<S, T>::construct(I... i_) noexcept
    {
        new(this) ElasticVector(i_...);

        return *this;
    }
    
    

    // Destruction Functions
    template <size_t S, typename T>
    ElasticVector<S, T>::~ElasticVector(void) noexcept
    {
        #ifdef GROUPDATA_VECTOR_WARNING
        if(_elements){
            delete[] _elements;
            _elements=nullptr;
        }else{
            warning::double_delete{std::string{"[gd::ElasticVector<"}+std::to_string(S)+", "+typeid(T).name()+">::~ElasticVector(void)]", "_elements"};
        }
        #else
        if(_elements){
            delete[] _elements;
            _elements=nullptr;
        }
        #endif

        return;
    }


    template <size_t S, typename T>
    ElasticVector<S, T>& ElasticVector<S, T>::destruct(void) noexcept
    {
        this->~ElasticVector<S, T>();
               
        return *this;
    }


   
    // Reference functions
    template <size_t S, typename T> template<uint16_t N>
    auto ElasticVector<S, T>::ref(void) const noexcept -> typename std::enable_if_t<(N==0), const T*>
    {
        return _elements;
    }
    
    

    template <size_t S, typename T>
    const T* ElasticVector<S, T>::ref(uint16_t) const noexcept
    {
        return _elements;
    }

   
    
    template <size_t S, typename T>
    const T* ElasticVector<S, T>::spec(void) const noexcept
    { 
        return _elements;
    }
    
    
    
    #ifdef GROUPDATA_VECTOR_EXCEPTION
    template <size_t S, typename T>
    const T& ElasticVector<S, T>::operator()(const size_t& s_) const
    { 
        if(s_>=S) throw exception::exceeded_capacity_in_size_direction(std::string{"[gd::ElasticVector<"}+std::to_string(S)+", "+typeid(T).name()+">::operator()(const size_t&)]", S, s_);
        return _elements[s_];
    }

    #else

    template <size_t S, typename T>
    const T& ElasticVector<S, T>::operator()(const size_t& s_) const noexcept
    { 
        return _elements[s_];
    }

    #endif
    
    
    template <size_t S, typename T>
    Range<const T> ElasticVector<S, T>::range(const size_t& e_) const noexcept
    { 
        return Range<const T>{_elements, _elements+e_};
    }
    
    
    template <size_t S, typename T>
    Range<const T> ElasticVector<S, T>::range(const size_t& b_, const size_t& e_) const noexcept
    { 
        return Range<const T>{_elements+b_, _elements+e_};
    }

    

    // Access functions
    template <size_t S, typename T> template<uint16_t N>
    auto ElasticVector<S, T>::path(void) noexcept -> typename std::enable_if_t<(N==0), T*>
    {
        return _elements;
    }
     
    
    template <size_t S, typename T>
    T* ElasticVector<S, T>::path(uint16_t) noexcept
    {
        return _elements;
    }
    
    
    template <size_t S, typename T>
    T* ElasticVector<S, T>::data(void) noexcept
    { 
        return _elements;
    }
    
    
    #ifdef GROUPDATA_VECTOR_EXCEPTION
    template <size_t S, typename T>
    T& ElasticVector<S, T>::operator[](const size_t& s_)
    { 
        if(s_>=S) throw exception::exceeded_capacity_in_size_direction(std::string{"[gd::ElasticVector<"}+std::to_string(S)+", "+typeid(T).name()+">::operator[](const size_t&)]", S, s_);
        return _elements[s_];
    }

    #else

    template <size_t S, typename T>
    T& ElasticVector<S, T>::operator[](const size_t& s_) noexcept
    { 
        return _elements[s_];
    }
    #endif
    

    template <size_t S, typename T>
    ElasticVector<S, T>& ElasticVector<S, T>::operator=(const ElasticVector<S, T>& vec_) noexcept
    {
        for(uint16_t a=0; a<S; ++a){
            _elements[a]=vec_(a);
        }
        
        return *this;
    }
    
    
    template <size_t S, typename T>
    ElasticVector<S, T>& ElasticVector<S, T>::operator=(ElasticVector<S, T>&& vec_) noexcept
    {
        _elements=vec_._elements;
        vec_._elements=nullptr;
        
        return *this;
    }
    
    
    template <size_t S, typename T>
    Range<T> ElasticVector<S, T>::range(const size_t& e_) noexcept
    { 
        return Range<T>{_elements, _elements+e_};
    }
    
    
    template <size_t S, typename T>
    Range<T> ElasticVector<S, T>::range(const size_t& b_, const size_t& e_) noexcept
    { 
        return Range<T>{_elements+b_, _elements+e_};
    }


    
    // Casting Functions
    template <size_t S, typename T> template <size_t R, typename U>
    ElasticVector<S, T>::operator ElasticVector<R, U> () const noexcept
    {
        ElasticVector<R, U> vec;
          for(size_t a=0; a<R && a<S; ++a){
            vec[a]=_elements(a);
        }
        for(size_t a=S; a<R; ++a){
            vec[a]=_elements(S-1);
        }

        return vec;
    }
   



    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <size_t S, typename T>
    std::ostream& operator<<(std::ostream& os_, const gd::Vector<S, T>& vec_) noexcept
    {
        if(vec_.size()) gd::ostream(vec_(0), os_);
        
        for(const T& v : vec_.crange(1, S)){
            os_<<std::endl;
            gd::ostream(v, os_);
        }
    
        return os_;
    }
    
    
    
    template <size_t S, typename T>
    std::ostream& operator<<(std::ostream& os_, const gd::ElasticVector<S, T>& vec_) noexcept
    {
        if(vec_.size()) gd::ostream(vec_(0), os_);
        
        for(const T& v : vec_.crange(1, S)){
            os_<<std::endl;
            gd::ostream(v, os_);
        }
    
        return os_;
    }

}
#endif

/*
int main(void){
    
    {
        std::cout<<"Alpha"<<std::endl;
        gd::Vector<5, double> gr1;
    
        std::cout<<gr1.depth()<<std::endl;
        std::cout<<gr1.size()<<std::endl;
    }
    
    {
        std::cout<<"Bravo"<<std::endl;
        gd::Vector<5, double> gr1={0, 3, 3, 2, 5};
        gd::Vector<5, double> gr2={0, 1};
        gd::Vector<5, double> gr3={0, 1, 2, 3, 4, 5, 6};
    
        std::cout<<gr1<<std::endl;
        std::cout<<gr2<<std::endl;
        std::cout<<gr3<<std::endl;
    }
    {
        std::cout<<"Charlie"<<std::endl;
        gd::Vector<5, double> gr1={0, 3, 3, 2, 5};
        std::cout<<gr1.ref<0>()<<" "<<gr1.path<0>()<<" "<<gr1.spec()<<" "<<gr1.data()<<std::endl;
        //gr1.ref<0>()[3]=4.5;
        //gr1.ref<2>();
        gr1.path<0>()[3]=4.5;
        //gr1.path<2>();
        //gr1.spec()[3]=4.5;
        gr1.data()[3]=4.2;
        std::cout<<gr1<<std::endl;
    }
    {
        std::cout<<"Delta"<<std::endl;
        gd::Vector<5, double> gr1={0, 3, 3, 2, 5};
        std::cout<<gr1(3)<<std::endl;
        //std::cout<<(gr1(3)=2.3)<<std::endl;
        std::cout<<(gr1[3]=2.3)<<std::endl;
        //std::cout<<gr1(5)<<std::endl;
        //std::cout<<(gr1[5]=2.3)<<std::endl;
    }
    {
        std::cout<<"Echo"<<std::endl;
        gd::Vector<5, double> gr1={0, 3, 3, 2, 5};
        gr1.destruct(); 
    }
    

}
*/
