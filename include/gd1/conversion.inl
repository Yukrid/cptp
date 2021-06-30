namespace gd{
#if defined(GROUPDATA_LIST_HPP) && defined(GROUPDATA_VIEW_HPP)
    
    #ifndef GROUPDATA_CONVERSION_INL_LIST_VIEW_FLAG
    #define GROUPDATA_CONVERSION_INL_LIST_VIEW_FLAG

    //->    list.hpp, consversion.inl    <-//
    #ifdef GROUPDATA_LIST_EXCEPTION
    template <typename T>
    List<T>::List(const View<T>& view_)
        : _size     {view_._size}
        , _capacity {view_._size}
        , _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*_capacity))}
    {
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::List<"}+typeid(T).name()+">::List(const View<T>&)]", _size};
        std::memcpy(_elements, view_.spec(), _size*sizeof(T));
        
        return;
    }

    #else

    template <typename T>
    List<T>::List(const View<T>& view_) noexcept
        : _size     {view_._size}
        , _capacity {view_._size}
        , _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*_capacity))}
    {
        std::memcpy(_elements, view_.spec(), _size*sizeof(T));
        
        return;
    }
    #endif


    #ifdef GROUPDATA_LIST_EXCEPTION
    template <typename T>
    List<T>& List<T>::operator=(const View<T>& view_)
    {
        if(!this->resize(view_._size)) throw exception::failed_to_realloc{std::string{"[gd::List<"}+typeid(T).name()+">::operator=(const View<T>& view_) -> resize(const size_t&)]", _elements, view_.size()};
        std::memcpy(_elements, view_.spec(), _size*sizeof(T));
        
        return *this;
    }
    
    #else
    
    template <typename T>
    List<T>& List<T>::operator=(const View<T>& view_) noexcept
    {
        this->resize(view_._size);
        std::memcpy(_elements, view_._elements, _size*sizeof(T));
        
        return *this;
    }
    #endif


    template <typename T>
    List<T>::operator View<T>() noexcept
    { 
        return View<T>{_size, _capacity, _elements};
    }
    #endif

#endif
}
