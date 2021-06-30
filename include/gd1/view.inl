#ifndef GROUPDATA_VIEW_INL
#define GROUPDATA_VIEW_INL

#include "view.hpp"

#include <cstring>

namespace gd{

    //++++++++++++++++++++//
    //    View Objects    //
    //++++++++++++++++++++//
    //(    gd::View Structure for Lamination    )//
    //+    Static Functions    +//
    template <typename T>
    constexpr uint16_t View<T>::depth(Empty) noexcept
    {
        return 1;   
    }
        
        

    //+    Member Functions    +//
    // Construcntion Functions
    template <typename T>
    View<T>::View(const size_t& sz_, const size_t& cap_, T* ptr_) noexcept
        : _size     {sz_}
        , _capacity {cap_}
        , _elements {ptr_}
    {
        return;
    }
    
    
    template <typename T>
    View<T>::View(const View<T>& view_) noexcept
        : _size     {view_._size}
        , _capacity {view_._capacity}
        , _elements {view_._elements}
    {
        return;
    }    


    template <typename T> template <typename... I>
    View<T>& View<T>::construct(I... i_) noexcept
    {
        new(this) View(i_...);

        return *this;
    }

  

    // Destruction Functions
    template <typename T>
    View<T>::~View(void) noexcept
    {
        return;
    }




    template <typename T>
    View<T>& View<T>::destruct(void) noexcept
    {
        ~View();
        
        return *this;
    }
    

   

    // Reference functions
    template <typename T> template<uint16_t N>
    auto View<T>::path(void) const noexcept -> typename std::enable_if_t<(N==0), const T*>
    {
        return _elements;
    }
    
    

    template <typename T>
    const T* View<T>::path(uint16_t) const noexcept
    {
        return _elements;
    }

   
    
    template <typename T>
    const T* View<T>::data(void) const noexcept
    { 
        return _elements;
    }
    
    
    
    #ifdef GROUPDATA_VIEW_EXCEPTION
    template <typename T>
    const T& View<T>::operator[](const size_t& s_) const
    { 
        if(s_>=_capacity) throw exception::exceeded_capacity_in_size_direction{std::string{"[gd::View<"}+typeid(T).name()+">::operator()(const size_t&)]", _capacity, s_};
        
        #ifdef GROUPDATA_VIEW_WARNING
        if(s_>=_size) warning::exceeded_size{std::string{"[gd::View<"}+typeid(T).name()+">::operator()(const size_t&)]", _size, s_};
        #endif

        return _elements[s_];
    }

    #else

    template <typename T>
    const T& View<T>::operator[](const size_t& s_) const noexcept
    { 
        #ifdef GROUPDATA_VIEW_WARNING
        if(s_>=_size) warning::exceeded_size{std::string{"[gd::View<"}+typeid(T).name()+">::operator()(const size_t&)]", _size, s_};
        #endif

        return _elements[s_];
    }

    #endif
        
    

    template <typename T>
    const size_t& View<T>::size(Empty) const noexcept
    { 
        return _size;
    }
    
    
    
    template <typename T>
    const size_t& View<T>::capacity(Empty) const noexcept
    { 
        return _capacity;
    }


    template <typename T>
    Range<const T> View<T>::range(void) const noexcept
    { 
        return Range<const T>{_elements, _elements+size(_key_)};
    }

    
    template <typename T>
    Range<const T> View<T>::range(const size_t& e_) const noexcept
    { 
        return Range<const T>{_elements, _elements+e_};
    }
    
    
    template <typename T>
    Range<const T> View<T>::range(const size_t& b_, const size_t& e_) const noexcept
    { 
        return Range<const T>{_elements+b_, _elements+e_};
    }




    // Access functions
    template <typename T> template<uint16_t N>
    auto View<T>::path(void) noexcept -> typename std::enable_if_t<(N==0), T*>
    {
        return _elements;
    }
    
    
    
    template <typename T>
    T* View<T>::path(uint16_t) noexcept
    {
        return _elements;
    }

    
    
    template <typename T>
    T* View<T>::data(void) noexcept
    { 
        return _elements;
    }


    template <typename T>
    Range<T> View<T>::range(void) noexcept
    { 
        return Range<T>{_elements, _elements+size(_key_)};
    }

    
    template <typename T>
    Range<T> View<T>::range(const size_t& e_) noexcept
    { 
        return Range<T>{_elements, _elements+e_};
    }
    
    
    template <typename T>
    Range<T> View<T>::range(const size_t& b_, const size_t& e_) noexcept
    { 
        return Range<T>{_elements+b_, _elements+e_};
    }

    
    
    #ifdef GROUPDATA_VIEW_EXCEPTION
    template <typename T>
    T& View<T>::operator[](const size_t& s_)
    {
        if(s_>=_capacity) throw exception::exceeded_capacity_in_size_direction{std::string{"[gd::View<"}+typeid(T).name()+">::operator[](const size_t&)]", _capacity, s_};
        
        #ifdef GROUPDATA_VIEW_WARNING
        if(s_>=_size) warning::exceeded_size{std::string{"[gd::View<"}+typeid(T).name()+">::operator[](const size_t&)]", _size, s_};
        #endif

        return _elements[s_];
    }

    #else

    template <typename T>
    T& View<T>::operator[](const size_t& s_) noexcept
    { 
        #ifdef GROUPDATA_VIEW_WARNING
        if(s_>=_size) warning::exceeded_size{std::string{"[gd::View<"}+typeid(T).name()+">::operator[](const size_t&)]", _size, s_};
        #endif

        return _elements[s_];
    }
    #endif


    template <typename T>
    View<T>& View<T>::memset(uint32_t ch_) noexcept
    {
        std::memset(_elements, ch_, sizeof(T)*_capacity);
        
        return *this;
    }
    
    
    
   
    //(    gd::ElasticView Structure for Lamination    )//
    //+    Static Functions    +//
    template <typename T>
    constexpr uint16_t ElasticView<T>::depth(Empty) noexcept
    {
        return 1;   
    }
        
        

    //+    Member Functions    +//
    // Construcntion Functions
    template <typename T>
    ElasticView<T>::ElasticView(const size_t& sz_, const size_t& cap_, T* ptr_) noexcept
        : _size     {sz_}
        , _capacity {cap_}
        , _elements {ptr_}
    {
        return;
    }
    
    
    template <typename T>
    ElasticView<T>::ElasticView(const ElasticView<T>& view_) noexcept
        : _size     {view_._size}
        , _capacity {view_._capacity}
        , _elements {view_._elements}
    {
        return;
    }


    template <typename T> template <typename... I>
    ElasticView<T>& ElasticView<T>::construct(I... i_) noexcept
    {
        new(this) ElasticView(i_...);

        return *this;
    }

  

    // Destruction Functions
    template <typename T>
    ElasticView<T>::~ElasticView(void) noexcept
    {
        return;
    }




    template <typename T>
    ElasticView<T>& ElasticView<T>::destruct(void) noexcept
    {
        ~ElasticView();
        
        return *this;
    }
    

   

    // Reference functions
    template <typename T> template<uint16_t N>
    auto ElasticView<T>::path(void) const noexcept -> typename std::enable_if_t<(N==0), const T*>
    {
        return _elements;
    }
    
    

    template <typename T>
    const T* ElasticView<T>::path(uint16_t) const noexcept
    {
        return _elements;
    }

   
    
    template <typename T>
    const T* ElasticView<T>::data(void) const noexcept
    { 
        return _elements;
    }
    
    
    
    #ifdef GROUPDATA_VIEW_EXCEPTION
    template <typename T>
    const T& ElasticView<T>::operator[](const size_t& s_) const
    { 
        if(s_>=_capacity) throw exception::exceeded_capacity_in_size_direction{std::string{"[gd::ElasticView<"}+typeid(T).name()+">::operator()(const size_t&)]", _capacity, s_};
        
        #ifdef GROUPDATA_VIEW_WARNING
        if(s_>=_size) warning::exceeded_size{std::string{"[gd::ElasticView<"}+typeid(T).name()+">::operator()(const size_t&)]", _size, s_};
        #endif

        return _elements[s_];
    }

    #else

    template <typename T>
    const T& ElasticView<T>::operator[](const size_t& s_) const noexcept
    { 
        #ifdef GROUPDATA_VIEW_WARNING
        if(s_>=_size) warning::exceeded_size{std::string{"[gd::ElasticView<"}+typeid(T).name()+">::operator()(const size_t&)]", _size, s_};
        #endif

        return _elements[s_];
    }

    #endif
        
    

    template <typename T>
    const size_t& ElasticView<T>::size(Empty) const noexcept
    { 
        return _size;
    }
        
    
    template <typename T>
    const size_t& ElasticView<T>::capacity(Empty) const noexcept
    { 
        return _capacity;
    }


    template <typename T>
    Range<const T> ElasticView<T>::range(void) const noexcept
    { 
        return Range<const T>{_elements, _elements+size(_key_)};
    }

    
    template <typename T>
    Range<const T> ElasticView<T>::range(const size_t& e_) const noexcept
    { 
        return Range<const T>{_elements, _elements+e_};
    }
    
    
    template <typename T>
    Range<const T> ElasticView<T>::range(const size_t& b_, const size_t& e_) const noexcept
    { 
        return Range<const T>{_elements+b_, _elements+e_};
    }



    // Access functions
    template <typename T> template<uint16_t N>
    auto ElasticView<T>::path(void) noexcept -> typename std::enable_if_t<(N==0), T*>
    {
        return _elements;
    }
    
    
    
    template <typename T>
    T* ElasticView<T>::path(uint16_t) noexcept
    {
        return _elements;
    }

    
    
    template <typename T>
    T* ElasticView<T>::data(void) noexcept
    { 
        return _elements;
    }


    template <typename T>
    Range<T> ElasticView<T>::range(void) noexcept
    { 
        return Range<T>{_elements, _elements+size(_key_)};
    }

    
    template <typename T>
    Range<T> ElasticView<T>::range(const size_t& e_) noexcept
    { 
        return Range<T>{_elements, _elements+e_};
    }
    
    
    template <typename T>
    Range<T> ElasticView<T>::range(const size_t& b_, const size_t& e_) noexcept
    { 
        return Range<T>{_elements+b_, _elements+e_};
    }

    
    
    #ifdef GROUPDATA_VIEW_EXCEPTION
    template <typename T>
    T& ElasticView<T>::operator[](const size_t& s_)
    { 
        if(s_>=_capacity) throw exception::exceeded_capacity_in_size_direction{std::string{"[gd::ElasticView<"}+typeid(T).name()+">::operator[](const size_t&)]", _capacity, s_};
        
        #ifdef GROUPDATA_VIEW_WARNING
        if(s_>=_size) warning::exceeded_size{std::string{"[gd::ElasticView<"}+typeid(T).name()+">::operator[](const size_t&)]", _size, s_};
        #endif

        return _elements[s_];
    }

    #else

    template <typename T>
    T& ElasticView<T>::operator[](const size_t& s_) noexcept
    { 
        #ifdef GROUPDATA_VIEW_WARNING
        if(s_>=_size) warning::exceeded_size{std::string{"[gd::ElasticView<"}+typeid(T).name()+">::operator[](const size_t&)]", _size, s_};
        #endif

        return _elements[s_];
    }
    #endif


   

    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <typename T>
    std::ostream& operator<<(std::ostream& os_, const gd::View<T>& lst_) noexcept
    {
        if(lst_.size()) gd::ostream(lst_(0), os_);
        for(uint16_t a=1; a<lst_.size(); ++a){
            os_<<std::endl;
            gd::ostream(lst_(a), os_);
        }
    
        return os_;
    } 

    
    template <typename T>
    std::ostream& operator<<(std::ostream& os_, const gd::ElasticView<T>& lst_) noexcept
    {
        if(lst_.size()) gd::ostream(lst_(0), os_);
        for(uint16_t a=1; a<lst_.size(); ++a){
            os_<<std::endl;
            gd::ostream(lst_(a), os_);
        }
    
        return os_;
    }
    
    
  

}
#endif

/*
#include <complex>
int main(void){
    
    {
        std::cout<<"Alpha"<<std::endl;
        gd::View<double> gr1;
    
        std::cout<<gr1.depth()<<std::endl;
        std::cout<<gr1.size()<<std::endl;
        std::cout<<gr1.capacity()<<std::endl;
    }
    
    {
        std::cout<<"Bravo"<<std::endl;
        gd::View<double> gr1={0, 3, 3, 2, 5};
        gd::View<double> gr2={0, 1};
        gd::View<double> gr3={0, 1, 2, 3, 4, 5, 6};
    
        std::cout<<gr1<<" "<<gr1.size()<<" "<<gr1.capacity()<<std::endl;
        std::cout<<gr2<<" "<<gr2.size()<<" "<<gr2.capacity()<<std::endl;
        std::cout<<gr3<<" "<<gr3.size()<<" "<<gr3.capacity()<<std::endl;
    }
    {
        std::cout<<"Charlie"<<std::endl;
        gd::View<double> gr1={0, 3, 3, 2, 5};
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
        gd::View<double> gr1={0, 3, 3, 2, 5};
        std::cout<<gr1(3)<<std::endl;
        //std::cout<<(gr1(3)=2.3)<<std::endl;
        std::cout<<(gr1[3]=2.3)<<std::endl;
        //std::cout<<gr1(5)<<std::endl;
        //std::cout<<(gr1[5]=2.3)<<std::endl;
    }
    {
        std::cout<<"Echo"<<std::endl;
        gd::View<double> gr1={0, 3, 3, 2, 5};
        gr1.destruct(); 
    }
    {
        std::cout<<std::endl<<"Foxtrot"<<std::endl;
        gd::View<double> gr1={0, 3, 3, 2, 5};
        if(!gr1.reserve(100)){
            std::cout<<"Err"<<std::endl;
        }else{
            std::cout<<gr1<<std::endl;
            std::cout<<gr1.size()<<" "<<gr1.capacity()<<std::endl;
            gr1.resize(100);
            std::cout<<gr1<<std::endl;
            std::cout<<gr1.size()<<" "<<gr1.capacity()<<std::endl;
            gr1.resize(0);
            std::cout<<gr1<<std::endl;
            std::cout<<gr1.size()<<" "<<gr1.capacity()<<std::endl;
        }
    }
    {
        std::cout<<std::endl<<"Foxtrot"<<std::endl;
        gd::View<std::complex<double>> gr1(1);
        std::cout<<gr1.size()<<" "<<gr1.capacity()<<std::endl;
        gr1.pushBack(std::complex<double>{3, 2});
        std::cout<<gr1<<std::endl;
        std::cout<<gr1.size()<<" "<<gr1.capacity()<<std::endl;
        gr1.emplaceBack(2.0, 4.0);
        std::cout<<gr1<<std::endl;
        std::cout<<gr1.size()<<" "<<gr1.capacity()<<std::endl;
        gr1.pushBack(std::complex<double>{3, 2});
        gr1.pushBack(std::complex<double>{3, 2});
        gr1.emplaceBack(2.0, 4.0);
        std::cout<<gr1<<std::endl;
        std::cout<<gr1.size()<<" "<<gr1.capacity()<<std::endl;
    }
}
*/
