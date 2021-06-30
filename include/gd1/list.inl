#ifndef GROUPDATA_LIST_INL
#define GROUPDATA_LIST_INL

#include "list.hpp"

#include <cstring>

namespace gd{

    //++++++++++++++++++++//
    //    List Objects    //
    //++++++++++++++++++++//
    //(    gd::List Structure for Lamination    )//
    //+    Static Functions    +//
    template <typename T>
    constexpr uint16_t List<T>::depth(Empty) noexcept
    {
        return 1;   
    }
        
        

    //+    Member Functions    +//
    // Construcntion Functions
    #ifdef GROUPDATA_LIST_EXCEPTION
    template <typename T>
    List<T>::List(void)
        : _size     {0}
        , _capacity {0}
        , _elements {reinterpret_cast<T*>(std::malloc(0))}
    {
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::List<"}+typeid(T).name()+">::List(void)]", 1};

        return;
    }
    
    
    template <typename T>
    List<T>::List(const size_t& sz_)
        : _size     {0}
        , _capacity {sz_}
        , _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*_capacity))}
    {
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::List<"}+typeid(T).name()+">::List(const size_t&)]", sz_};
        
        return;
    }
    
    
    template <typename T>
    List<T>::List(const List<T>& lst_)
        : _size     {lst_._size}
        , _capacity {lst_._size}
        , _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*_capacity))}
    {
        
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::List<"}+typeid(T).name()+">::List(const List<T>&)]", lst_._size};

        std::memcpy(_elements, lst_._elements, _size*sizeof(T));
        
        return;
    } 
    
   
    template <typename T>
    List<T>::List(std::initializer_list<T> lst_)
        : _size     {lst_.size()}
        , _capacity {lst_.size()}
        , _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*_capacity))}
    {
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::List<"}+typeid(T).name()+">::List(std::initializer_list<T>)]", _capacity};

        std::memcpy(_elements, lst_._begin(), _size*sizeof(T));

        return;
    }


    template <typename T> template <typename... I>
    List<T>& List<T>::construct(I... i_)
    {
        new(this) List(i_...);

        return *this;
    }
        
    #else
    
    template <typename T>
    List<T>::List(void) noexcept
        : _size     {0}
        , _capacity {0}
        , _elements {reinterpret_cast<T*>(std::malloc(0))}
    {
        return;
    }
    
    
    template <typename T>
    List<T>::List(const size_t& sz_) noexcept
        : _size     {0}
        , _capacity {sz_}
        , _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*_capacity))}
    {
        return;
    }
    
    
    template <typename T>
    List<T>::List(const List<T>& lst_) noexcept
        : _size     {lst_._size}
        , _capacity {lst_._size}
        , _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*_capacity))}
    {
        std::memcpy(_elements, lst_._elements, _size*sizeof(T));
        
        return;
    }
    

    template <typename T>
    List<T>::List(std::initializer_list<T> lst_) noexcept
        : _size     {lst_.size()}
        , _capacity {lst_.size()}
        , _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*_capacity))}
    {
        std::memcpy(_elements, lst_.begin(), _size*sizeof(T));

        return;
    }


    template <typename T> template <typename... I>
    List<T>& List<T>::construct(I... i_) noexcept
    {
        new(this) List(i_...);

        return *this;
    }
    #endif


    template <typename T>
    List<T>::List(List<T>&& lst_) noexcept
        : _size     {lst_._size}
        , _capacity {lst_._capacity}
        , _elements {lst_._elements}
    {
        lst_._size=0;
        lst_._capacity=0;
        lst_._elements=nullptr;
        
        return;
    } 

  
    
   
    // Destruction Functions
    template <typename T>
    List<T>::~List(void) noexcept
    {
        #ifdef GROUPDATA_LIST_WARNING
        if(_elements){
            std::free(_elements);
            _elements=nullptr;
        }else{
            warning::double_free{std::string{"[gd::List<"}+typeid(T).name()+">::~List(void)]", "_elements"};
        }
        #else
        if(_elements){
            std::free(_elements);
            _elements=nullptr;
        }
        #endif

        return;
    }




    template <typename T>
    List<T>& List<T>::destruct(void) noexcept
    {
        this->~List<T>();
        
        return *this;
    }
    


   

    // Reference functions
    template <typename T> template<uint16_t N>
    auto List<T>::path(void) const noexcept -> typename std::enable_if_t<(N==0), const T*>
    {
        return _elements;
    }
    
    

    template <typename T>
    const T* List<T>::path(uint16_t) const noexcept
    {
        return _elements;
    }

   
    
    template <typename T>
    const T* List<T>::data(void) const noexcept
    { 
        return _elements;
    }
    
    
    
    #ifdef GROUPDATA_LIST_EXCEPTION
    template <typename T>
    const T& List<T>::operator[](const size_t& s_) const
    { 
        if(s_>=_capacity) throw exception::exceeded_capacity_in_size_direction{std::string{"[gd::List<"}+typeid(T).name()+">::operator()(const size_t&)]", _capacity, s_};
        
        #ifdef GROUPDATA_LIST_WARNING
        if(s_>=_size) warning::exceeded_size{std::string{"[gd::List<"}+typeid(T).name()+">::operator()(const size_t&)]", _size, s_};
        #endif

        return _elements[s_];
    }

    #else

    template <typename T>
    const T& List<T>::operator[](const size_t& s_) const noexcept
    { 
        #ifdef GROUPDATA_LIST_WARNING
        if(s_>=_size) warning::exceeded_size{std::string{"[gd::List<"}+typeid(T).name()+">::operator()(const size_t&)]", _size, s_};
        #endif

        return _elements[s_];
    }
    #endif


    template <typename T>
    Range<const T> List<T>::range(void) const noexcept
    { 
        return Range<const T>{_elements, _elements+size(_key_)};
    }

    
    template <typename T>
    Range<const T> List<T>::range(const size_t& e_) const noexcept
    { 
        return Range<const T>{_elements, _elements+e_};
    }
    
    
    template <typename T>
    Range<const T> List<T>::range(const size_t& b_, const size_t& e_) const noexcept
    { 
        return Range<const T>{_elements+b_, _elements+e_};
    }
    

    template <typename T>
    const size_t& List<T>::size(Empty) const noexcept
    { 
        return _size;    
    }
    
    
    template <typename T>
    const size_t& List<T>::capacity(Empty) const noexcept
    { 
        return _capacity;
    }




    // Access functions
    template <typename T> template<uint16_t N>
    auto List<T>::path(void) noexcept -> typename std::enable_if_t<(N==0), T*>
    {
        return _elements;
    }
    
    
    
    template <typename T>
    T* List<T>::path(uint16_t) noexcept
    {
        return _elements;
    }

    
    
    template <typename T>
    T* List<T>::data(void) noexcept
    { 
        return _elements;
    }

    
    
    #ifdef GROUPDATA_LIST_EXCEPTION
    template <typename T>
    T& List<T>::operator[](const size_t& s_)
    { 
        if(s_>=_capacity) throw exception::exceeded_capacity_in_size_direction{std::string{"[gd::List<"}+typeid(T).name()+">::operator[](const size_t&)]", _capacity, s_};
        
        #ifdef GROUPDATA_LIST_WARNING
        if(s_>=_size) warning::exceeded_size{std::string{"[gd::List<"}+typeid(T).name()+">::operator[](const size_t&)]", _size, s_};
        #endif

        return _elements[s_];
    }

    #else

    template <typename T>
    T& List<T>::operator[](const size_t& s_) noexcept
    { 
        #ifdef GROUPDATA_LIST_WARNING
        if(s_>=_size) warning::exceeded_size{std::string{"[gd::List<"}+typeid(T).name()+">::operator[](const size_t&)]", _size, s_};
        #endif

        return _elements[s_];
    }
    #endif


    #ifdef GROUPDATA_LIST_EXCEPTION
    template <typename T>
    List<T>& List<T>::operator=(const List<T>& lst_)
    {
        if(!this->resize(lst_._size)) throw exception::failed_to_realloc{std::string{"[gd::List<"}+typeid(T).name()+">::operator=(const List<T>&) -> resize(const size_t&)]", _elements, lst_.size()};
        
        std::memcpy(_elements, lst_._elements, _size*sizeof(T));
        
        return *this;
    }
        
    #else
    
    template <typename T>
    List<T>& List<T>::operator=(const List<T>& lst_) noexcept
    {
        this->resize(lst_._size);
        std::memcpy(_elements, lst_._elements, _size*sizeof(T));
        
        return *this;
    }    
    #endif


    template <typename T>
    List<T>& List<T>::operator=(List<T>&& lst_) noexcept
    {
        destruct();
    
        _size    =lst_._size;
        _capacity=lst_._capacity;
        _elements=lst_._elements;

        lst_._size    =0;
        lst_._capacity=0;
        lst_._elements=nullptr;
    
        return *this;
    }


    template <typename T>
    Range<T> List<T>::range(void) noexcept
    { 
        return Range<T>{_elements, _elements+size(_key_)};
    }

    
    template <typename T>
    Range<T> List<T>::range(const size_t& e_) noexcept
    { 
        return Range<T>{_elements, _elements+e_};
    }
    
    
    template <typename T>
    Range<T> List<T>::range(const size_t& b_, const size_t& e_) noexcept
    { 
        return Range<T>{_elements+b_, _elements+e_};
    }



    // Edit Functions
    template <typename T>
    bool List<T>::resize(const size_t& s_) noexcept
    {
        if(_capacity<s_){
            if(void* new_ptr_=std::realloc(_elements, sizeof(T)*s_)){
                _elements=reinterpret_cast<T*>(new_ptr_);
                _capacity=s_;
            }else{
                #ifdef GROUPDATA_LIST_WARNING
                warning::failed_to_realloc{std::string{"[gd::List<"}+typeid(T).name()+">::resize(const size_t&)]", _elements, s_};
                #endif

                return false;
            }
        }
        _size    =s_;

        return true;
    }


    
    template <typename T>
    bool List<T>::reserve(const size_t& s_) noexcept
    {
        if(_capacity<s_){
            if(void* new_ptr_=std::realloc(_elements, sizeof(T)*s_)){
                _elements=reinterpret_cast<T*>(new_ptr_);
                _capacity=s_;
            }else{
                #ifdef GROUPDATA_LIST_WARNING
                warning::failed_to_realloc{std::string{"[gd::List<"}+typeid(T).name()+">::reserve(const size_t&)]", _elements, s_};
                #endif

                return false;
            }
        }

        return true;
    }
    
    
    
    template <typename T>
    bool List<T>::reduce(const size_t& s_) noexcept
    {
        if(_capacity>s_){
            if(void* new_ptr_=std::realloc(_elements, sizeof(T)*s_)){
                _elements=reinterpret_cast<T*>(new_ptr_);
                _capacity=s_;
                _size    = _size>s_ ? s_ : _size;
            }else{
                #ifdef GROUPDATA_LIST_WARNING
                warning::failed_to_realloc{std::string{"[gd::List<"}+typeid(T).name()+">::reduce(const size_t&)]", _elements, s_};
                #endif

                return false;
            }
        }

        return true;
    }


    template <typename T>
    bool List<T>::insert(const size_t & s_, const T& t_) noexcept
    {
        if  (!reserve(_size+1)) return false;
        else{
            std::memmove(_elements+s_+1, _elements+s_, sizeof(T)*(_size-s_));
            std::memcpy(_elements+s_, &t_, sizeof t_);
            _size++;
            
            return true;
        }
    }
         
    
    template <typename T>
    bool List<T>::pushBack(const T& t_) noexcept
    {
        if(_capacity<_size+1){
            size_t s_ = (_size+1)*2;
            if(void* new_ptr_=std::realloc(_elements, sizeof(T)*s_)){
                _elements=reinterpret_cast<T*>(new_ptr_);
                _capacity=s_;
            }else{
                #ifdef GROUPDATA_LIST_WARNING
                warning::failed_to_realloc{std::string{"[gd::List<"}+typeid(T).name()+">::pushBack(const T&)]", _elements, s_};
                #endif

                return false;
            }
        }

        _elements[_size]=t_;
        ++_size;

        return true;
    }



    template <typename T>
    bool List<T>::pushBack(T&& t_) noexcept
    {
        if(_capacity<_size+1){
            size_t s_ = (_size+1)*2;
            if(void* new_ptr_=std::realloc(_elements, sizeof(T)*s_)){
                _elements=reinterpret_cast<T*>(new_ptr_);
                _capacity=s_;
            }else{
                #ifdef GROUPDATA_LIST_WARNING
                warning::failed_to_realloc{std::string{"[gd::List<"}+typeid(T).name()+">::pushBack(T&&)]", _elements, s_};
                #endif

                return false;
            }
        }

        _elements[_size]=t_;
        ++_size;

        return true;
    }


    template <typename T> template <typename... I>
    bool List<T>::emplaceBack(I... i_) noexcept
    {
        if(_capacity<_size+1){
            size_t s_ = (_size+1)*2;
            if(void* new_ptr_=std::realloc(_elements, sizeof(T)*s_)){
                _elements=reinterpret_cast<T*>(new_ptr_);
                _capacity=s_;
            }else{
                #ifdef GROUPDATA_LIST_WARNING
                warning::failed_to_realloc{std::string{"[gd::List<"}+typeid(T).name()+">::pushBack(const T&)]", _elements, s_};
                #endif

                return false;
            }
        }

        new(_elements+_size) T(i_...);
        ++_size;

        return true;
    }

    
    
    template <typename T>
    List<T>& List<T>::memset(int32_t ch_) noexcept
    {
        std::memset(_elements, ch_, sizeof(T)*_capacity);
        
        return *this;
    }
    
    
    
    // Casting Function
    template <typename T> template <typename U>
    List<T>::operator List<U> () const noexcept
    {
        List<U> lst_;
        lst_.resize(_size);
        for(size_t a=0; a<_size; ++a) lst_[a]=static_cast<U>(_elements[a]);
        
        return lst_;
    }
    
    
   

    //(    gd::ElasticList Structure for Lamination    )//
    //+    Static Functions    +//
    template <typename T>
    constexpr uint16_t ElasticList<T>::depth(Empty) noexcept
    {
        return 1;   
    }
        
        

    //+    Member Functions    +//
    // Construcntion Functions
    #ifdef GROUPDATA_LIST_EXCEPTION
    template <typename T>
    ElasticList<T>::ElasticList(void)
        : _size     {0}
        , _capacity {0}
        , _elements {reinterpret_cast<T*>(std::malloc(0))}
    {
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::ElasticList(void)]", 1};
        
        return;
    }

    
    template <typename T>
    ElasticList<T>::ElasticList(const size_t& sz_)
        : _size     {0}
        , _capacity {sz_}
        , _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*_capacity))}
    {
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::ElasticList(const size_t&)]", sz_};
        
        return;
    }
    
    
    template <typename T>
    ElasticList<T>::ElasticList(const ElasticList<T>& lst_)
        : _size     {lst_._size}
        , _capacity {lst_._size}
        , _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*_capacity))}
    {
        
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::ElasticList(const ElasticList<T>&)]", lst_._size};
        
        for(size_t a=0; a<_size; ++a) new(_elements+a) T(lst_(a));
        
        return;
    } 
    
   
    template <typename T>
    ElasticList<T>::ElasticList(std::initializer_list<T> lst_)
        : _size     {lst_.size()}
        , _capacity {lst_.size()}
        , _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*_capacity))}
    {
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::ElasticList(std::initializer_list<T>)]", _capacity};

        for(size_t a=0; a<_size; ++a) new(_elements+a) T(lst_.begin()[a]);

        return;
    }


    template <typename T> template <typename... I>
    ElasticList<T>& ElasticList<T>::construct(I... i_)
    {
        new(this) ElasticList(i_...);

        return *this;
    }
        
    #else
    
    template <typename T>
    ElasticList<T>::ElasticList(void) noexcept
        : _size     {0}
        , _capacity {0}
        , _elements {reinterpret_cast<T*>(std::malloc(0))}
    {
        return;
    }
    
    
    template <typename T>
    ElasticList<T>::ElasticList(const size_t& sz_) noexcept
        : _size     {0}
        , _capacity {sz_}
        , _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*_capacity))}
    {
        return;
    }
    
    
    template <typename T>
    ElasticList<T>::ElasticList(const ElasticList<T>& lst_) noexcept
        : _size     {lst_._size}
        , _capacity {lst_._size}
        , _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*_capacity))}
    {
        for(size_t a=0; a<_size; ++a) new(_elements+a) T(lst_(a));
        
        return;
    }
    

    template <typename T>
    ElasticList<T>::ElasticList(std::initializer_list<T> lst_) noexcept
        : _size     {lst_.size()}
        , _capacity {lst_.size()}
        , _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*_capacity))}
    {
        for(size_t a=0; a<_size; ++a) new(_elements+a) T(std::move(lst_.begin()[a]));

        return;
    }


    template <typename T> template <typename... I>
    ElasticList<T>& ElasticList<T>::construct(I... i_) noexcept
    {
        new(this) ElasticList(i_...);

        return *this;
    }
    #endif


    template <typename T>
    ElasticList<T>::ElasticList(ElasticList<T>&& lst_) noexcept
        : _size     {lst_._size}
        , _capacity {lst_._capacity}
        , _elements {lst_._elements}
    {
        lst_._size=0;
        lst_._capacity=0;
        lst_._elements=nullptr;
        
        return;
    } 
  
    
   
    // Destruction Functions
    template <typename T>
    ElasticList<T>::~ElasticList(void) noexcept
    {
        
        for(size_t a=0; a<_size; ++a) (_elements+a)->~T();
        
        #ifdef GROUPDATA_LIST_WARNING
        if(_elements){
            std::free(_elements);
            _elements=nullptr;
        }else{
            warning::double_free{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::~ElasticList(void)]", "_elements"};
        }
        #else
        if(_elements){
            std::free(_elements);
            _elements=nullptr;
        }
        #endif

        return;
    }


    template <typename T>
    ElasticList<T>& ElasticList<T>::destruct(void) noexcept
    {
        this->~ElasticList<T>();
        
        return *this;
    }
    


   

    // Reference functions
    template <typename T> template<uint16_t N>
    auto ElasticList<T>::path(void) const noexcept -> typename std::enable_if_t<(N==0), const T*>
    {
        return _elements;
    }
    
    

    template <typename T>
    const T* ElasticList<T>::path(uint16_t) const noexcept
    {
        return _elements;
    }

   
    
    template <typename T>
    const T* ElasticList<T>::data(void) const noexcept
    { 
        return _elements;
    }
    
    
    
    #ifdef GROUPDATA_LIST_EXCEPTION
    template <typename T>
    const T& ElasticList<T>::operator[](const size_t& s_) const
    { 
        if(s_>=_capacity) throw exception::exceeded_capacity_in_size_direction{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::operator()(const size_t&)]", _capacity, s_};
        
        #ifdef GROUPDATA_LIST_WARNING
        if(s_>=_size) warning::exceeded_size{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::operator()(const size_t&)]", _size, s_};
        #endif

        return _elements[s_];
    }

    #else

    template <typename T>
    const T& ElasticList<T>::operator[](const size_t& s_) const noexcept
    { 
        #ifdef GROUPDATA_LIST_WARNING
        if(s_>=_size) warning::exceeded_size{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::operator()(const size_t&)]", _size, s_};
        #endif

        return _elements[s_];
    }
    #endif


    template <typename T>
    Range<const T> ElasticList<T>::range(void) const noexcept
    { 
        return Range<const T>{_elements, _elements+size(_key_)};
    }

    
    template <typename T>
    Range<const T> ElasticList<T>::range(const size_t& e_) const noexcept
    { 
        return Range<const T>{_elements, _elements+e_};
    }
    
    
    template <typename T>
    Range<const T> ElasticList<T>::range(const size_t& b_, const size_t& e_) const noexcept
    { 
        return Range<const T>{_elements+b_, _elements+e_};
    }
    

    template <typename T>
    const size_t& ElasticList<T>::size(Empty) const noexcept
    { 
        return _size;    
    }
    
    
    template <typename T>
    const size_t& ElasticList<T>::capacity(Empty) const noexcept
    { 
        return _capacity;
    }




    // Access functions
    template <typename T> template<uint16_t N>
    auto ElasticList<T>::path(void) noexcept -> typename std::enable_if_t<(N==0), T*>
    {
        return _elements;
    }
    
    
    
    template <typename T>
    T* ElasticList<T>::path(uint16_t) noexcept
    {
        return _elements;
    }

    
    
    template <typename T>
    T* ElasticList<T>::data(void) noexcept
    { 
        return _elements;
    }

    
    
    #ifdef GROUPDATA_LIST_EXCEPTION
    template <typename T>
    T& ElasticList<T>::operator[](const size_t& s_)
    { 
        if(s_>=_capacity) throw exception::exceeded_capacity_in_size_direction{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::operator[](const size_t&)]", _capacity, s_};
        
        #ifdef GROUPDATA_LIST_WARNING
        if(s_>=_size) warning::exceeded_size{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::operator[](const size_t&)]", _size, s_};
        #endif

        return _elements[s_];
    }

    #else

    template <typename T>
    T& ElasticList<T>::operator[](const size_t& s_) noexcept
    { 
        #ifdef GROUPDATA_LIST_WARNING
        if(s_>=_size) warning::exceeded_size{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::operator[](const size_t&)]", _size, s_};
        #endif

        return _elements[s_];
    }
    #endif


    #ifdef GROUPDATA_LIST_EXCEPTION
    template <typename T>
    ElasticList<T>& ElasticList<T>::operator=(const ElasticList<T>& lst_)
    {
        
        if(!this->resize(lst_._size)) throw exception::failed_to_realloc{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::operator=(const ElasticList<T>&) -> resize(const size_t&)]", _elements, lst_.size()};

        std::memcpy(_elements, lst_._elements, _size*sizeof(T));
        
        return *this;
    }
        
    #else
    
    template <typename T>
    ElasticList<T>& ElasticList<T>::operator=(const ElasticList<T>& lst_) noexcept
    {
        this->resize(lst_._size);
        for(size_t a=0; a<_size; ++a) _elements[a]=lst_[a];

        return *this;
    }    
    #endif


    template <typename T>
    ElasticList<T>& ElasticList<T>::operator=(ElasticList<T>&& lst_) noexcept
    {
        destruct();
    
        _size    =lst_._size;
        _capacity=lst_._capacity;
        _elements=lst_._elements;

        lst_._size    =0;
        lst_._capacity=0;
        lst_._elements=nullptr;
    
        return *this;
    }


    template <typename T>
    Range<T> ElasticList<T>::range(void) noexcept
    { 
        return Range<T>{_elements, _elements+size(_key_)};
    }

    
    template <typename T>
    Range<T> ElasticList<T>::range(const size_t& e_) noexcept
    { 
        return Range<T>{_elements, _elements+e_};
    }
    
    
    template <typename T>
    Range<T> ElasticList<T>::range(const size_t& b_, const size_t& e_) noexcept
    { 
        return Range<T>{_elements+b_, _elements+e_};
    }



    // Edit Functions
    template <typename T>
    bool ElasticList<T>::resize(const size_t& s_) noexcept
    {   
        if(_size>s_){

            for(size_t a=s_; a<_size; ++a) (_elements+a)->~T();
            _size=s_;    

            return true;
        
        }else if(_capacity<s_){

            if(void* new_ptr_=std::malloc(sizeof(T)*s_)){
                
                T* new_elements=reinterpret_cast<T*>(new_ptr_);
                for(size_t a=0; a<_size; ++a){
                    new(new_elements+a) T(std::move(_elements[a]));
                    _elements[a].~T();
                }
                std::free(_elements);
                
                for(size_t a=_size; a<s_; ++a){
                    new(new_elements+a) T();
                }

                _elements=new_elements;
                
                _capacity=s_;
                _size=s_;

                return true;

            }else{
                #ifdef GROUPDATA_LIST_WARNING
                warning::failed_to_realloc{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::resize(const size_t&)]", _elements, s_};
                #endif

                return false;
            }

        }else if(_size<s_){
            
            for(size_t a=_size; a<s_; ++a){
                new(_elements+a) T();
            }
            _size=s_;

            return true;
        }

        return true;
    }


    template <typename T>
    bool ElasticList<T>::reserve(const size_t& s_) noexcept
    {
         if(_capacity<s_){

            if(void* new_ptr_=std::malloc(sizeof(T)*s_)){
                
                T* new_elements=reinterpret_cast<T*>(new_ptr_);
                for(size_t a=0; a<_size; ++a){
                    new(new_elements+a) T(std::move(_elements[a]));
                    _elements[a].~T();
                }
                std::free(_elements);
                
                _elements=new_elements; 
                _capacity=s_;

                return true;
            }else{
                #ifdef GROUPDATA_LIST_WARNING
                warning::failed_to_realloc{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::reserve(const size_t&)]", _elements, s_};
                #endif

                return false;
            }
        }

        return true;
    }
    
    
   
    template <typename T>
    bool ElasticList<T>::reduce(const size_t& s_) noexcept
    {
        if(_capacity>s_){

            if(_size>s_){
                for(size_t a=s_; a<_size; ++a) (_elements+a)->~T();
            }

            if(void* new_ptr_=std::realloc(_elements, sizeof(T)*s_)){
                
                _elements=reinterpret_cast<T*>(new_ptr_);
                _capacity=s_;
                _size    = _size>s_ ? s_ : _size;

                return true;
            }else{
                #ifdef GROUPDATA_LIST_WARNING
                warning::failed_to_realloc{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::reduce(const size_t&)]", _elements, s_};
                #endif

                return false;
            }
        }
        
        return true;
    }


    template <typename T>
    bool ElasticList<T>::insert(const size_t & s_, const T& t_) noexcept
    {
        if  (!reserve(_size+1)) return false;
        else{
            for(size_t a=_size-1; a>=s_; --a){
                
                new(_elements+a+1) T(std::move(_elements[a]));

                if(a==0) break;
            }

            new(_elements+s_) T(t_);
            _size++;
            
            return true;
        }
    }



    template <typename T>
    bool ElasticList<T>::pushBack(const T& t_) noexcept
    {
        if(_capacity<_size+1){
            
            size_t s_ = (_size+1)*2;
            
            if(void* new_ptr_=std::malloc(sizeof(T)*s_)){
                    
                T* new_elements=reinterpret_cast<T*>(new_ptr_);
                for(size_t a=0; a<_size; ++a){
                    new(new_elements+a) T(std::move(_elements[a]));
                    _elements[a].~T();
                }
                std::free(_elements);
                _elements=new_elements;                 
                    
                new(_elements+_size) T(t_);
                _capacity=s_;
                ++_size;
                    
                return true;

            }else{
                #ifdef GROUPDATA_LIST_WARNING
                warning::failed_to_realloc{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::pushBack(const T&)]", _elements, s_};
                #endif
    
                return false;
            }
    
        }else{
                
            new(_elements+_size) T(t_);
            ++_size;

            return true;
        }
    }
    
    
    template <typename T>
    bool ElasticList<T>::pushBack(T&& t_) noexcept
    {
        if(_capacity<_size+1){
            
            size_t s_ = (_size+1)*2;
            
            if(void* new_ptr_=std::malloc(sizeof(T)*s_)){
                    
                T* new_elements=reinterpret_cast<T*>(new_ptr_);
                for(size_t a=0; a<_size; ++a){
                    new(new_elements+a) T(std::move(_elements[a]));
                    _elements[a].~T();
                }
                std::free(_elements);
                _elements=new_elements;                 
                    
                new(_elements+_size) T(std::move(t_));
                _capacity=s_;
                ++_size;
                    
                return true;

            }else{
                #ifdef GROUPDATA_LIST_WARNING
                warning::failed_to_realloc{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::pushBack(T&&)]", _elements, s_};
                #endif
    
                return false;
            }
    
        }else{
                
            new(_elements+_size) T(std::move(t_));
            ++_size;

            return true;
        }
    }
 

    template <typename T> template <typename... I>
    bool ElasticList<T>::emplaceBack(I... i_) noexcept
    {
        if(_capacity<_size+1){
            
            size_t s_ = (_size+1)*2;
            
            if(void* new_ptr_=std::malloc(sizeof(T)*s_)){
                    
                T* new_elements=reinterpret_cast<T*>(new_ptr_);
                for(size_t a=0; a<_size; ++a){
                    new(new_elements+a) T(std::move(_elements[a]));
                    _elements[a].~T();
                }
                std::free(_elements);
                _elements=new_elements;                 
                    
                new(_elements+_size) T(i_...);
                _capacity=s_;
                ++_size;
                    
                return true;

            }else{
                #ifdef GROUPDATA_LIST_WARNING
                warning::failed_to_realloc{std::string{"[gd::ElasticList<"}+typeid(T).name()+">::moveBack(T&&)]", _elements, s_};
                #endif
    
                return false;
            }
    
        }else{
                
            new(_elements+_size) T(i_...);
            ++_size;

            return true;
        }
    }
    
    
    // Casting Function
    template <typename T> template <typename U>
    ElasticList<T>::operator ElasticList<U> () const noexcept
    {
        ElasticList<U> lst_;
        lst_.resize(_size);
        for(size_t a=0; a<_size; ++a) lst_[a]=static_cast<U>(_elements[a]);
        
        return lst_;
    }

    


    
    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <typename T>
    std::ostream& operator<<(std::ostream& os_, const gd::List<T>& lst_) noexcept
    {
        if(lst_.size()) gd::ostream(lst_[0], os_);
    
        for(size_t a=1; a<lst_.size(); ++a){
            os_<<std::endl;
            gd::ostream(lst_[a], os_);
        }

        return os_;
    }
    
    
    template <typename T>
    std::ostream& operator<<(std::ostream& os_, const gd::ElasticList<T>& lst_) noexcept
    {
        if(lst_.size()) gd::ostream(lst_[0], os_);
        
        for(size_t a=1; a<lst_.size(); ++a){
            os_<<std::endl;
            gd::ostream(lst_[a], os_);
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
        gd::List<double> gr1;
    
        std::cout<<gr1.depth()<<std::endl;
        std::cout<<gr1.size()<<std::endl;
        std::cout<<gr1.capacity()<<std::endl;
    }
    
    {
        std::cout<<"Bravo"<<std::endl;
        gd::List<double> gr1={0, 3, 3, 2, 5};
        gd::List<double> gr2={0, 1};
        gd::List<double> gr3={0, 1, 2, 3, 4, 5, 6};
    
        std::cout<<gr1<<" "<<gr1.size()<<" "<<gr1.capacity()<<std::endl;
        std::cout<<gr2<<" "<<gr2.size()<<" "<<gr2.capacity()<<std::endl;
        std::cout<<gr3<<" "<<gr3.size()<<" "<<gr3.capacity()<<std::endl;
    }
    {
        std::cout<<"Charlie"<<std::endl;
        gd::List<double> gr1={0, 3, 3, 2, 5};
        std::cout<<gr1.path<0>()<<" "<<gr1.path<0>()<<" "<<gr1.data()<<" "<<gr1.data()<<std::endl;
        //gr1.path<0>()[3]=4.5;
        //gr1.path<2>();
        gr1.path<0>()[3]=4.5;
        //gr1.path<2>();
        //gr1.data()[3]=4.5;
        gr1.data()[3]=4.2;
        std::cout<<gr1<<std::endl;
    }
    {
        std::cout<<"Delta"<<std::endl;
        gd::List<double> gr1={0, 3, 3, 2, 5};
        std::cout<<gr1(3)<<std::endl;
        //std::cout<<(gr1(3)=2.3)<<std::endl;
        std::cout<<(gr1[3]=2.3)<<std::endl;
        //std::cout<<gr1(5)<<std::endl;
        //std::cout<<(gr1[5]=2.3)<<std::endl;
    }
    {
        std::cout<<"Echo"<<std::endl;
        gd::List<double> gr1={0, 3, 3, 2, 5};
        gr1.destruct(); 
    }
    {
        std::cout<<std::endl<<"Foxtrot"<<std::endl;
        gd::List<double> gr1={0, 3, 3, 2, 5};
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
        gd::List<std::complex<double>> gr1(1);
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
