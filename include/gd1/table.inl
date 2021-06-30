
#ifndef GROUPDATA_TABLE_INL
#define GROUPDATA_TABLE_INL

#include "table.hpp"

namespace gd{

    //+++++++++++++++++++++//
    //    Table Objects    //
    //+++++++++++++++++++++//
    //(    gd::Table Lamination for Lamination    )//
    //+    Static Functions    +//
    template <typename... As>
    constexpr uint16_t Table<As...>::depth(Empty) noexcept
    {
        return 0;
    }


    //+    Member Functions    +//
    // Construcntion Functions
    template <typename... As>
    Table<As...>::Table(void) noexcept
        : _size     {0}
        , _capacity {0}
    {
        return;
    }


    template <typename... As>
    Table<As...>::Table(const size_t& s_) noexcept
        : _size     {s_}
        , _capacity {s_}
    {
        return;
    }
    
    
    template <typename... As>
    Table<As...>::Table(const Table<As...>& tb_) noexcept
        : _size     {tb_._size}
        , _capacity {tb_._size}
    {
        return;
    }
    
    
    template <typename... As>
    Table<As...>::Table(Table<As...>&& tb_) noexcept
        : _size     {tb_._size}
        , _capacity {tb_._capacity}
    {
        return;
    }
    

    template <typename... As> template <typename... I>
    Table<As...>& Table<As ...>::construct(I... i_) noexcept
    {
        new(this) Table(i_...);

        return *this;
    }


    
    // Destruction Functions
    template <typename... As>
    Table<As...>::~Table(void) noexcept
    {
        _size     = 0;
        _capacity = 0;

        return;
    }
    

    template <typename... As>
    Table<As...>& Table<As ...>::destruct(void) noexcept
    {
        ~Table();

        return *this;
    }


    
    // Reference Functions
    template <typename... As>
    const size_t& Table<As ...>::size(void) const noexcept
    {
        return _size;
    }
    
    
    template <typename... As>
    const size_t& Table<As ...>::capacity(void) const noexcept
    {
        return _capacity;
    }



    // Access Functions
    template <typename... As>
    void Table<As...>::_operator_equal(const Table<As...>& tb_) noexcept
    {
        _size    =tb_._size;
        _capacity=tb_._size;

        return;
    }
   

    template <typename... As>
    void Table<As...>::_operator_equal(Table<As...>&& tb_) noexcept
    {
        _size    =tb_._size;
        _capacity=tb_._capacity;

        return;
    }

    
    template <typename... As>
    size_t& Table<As...>::_protSize(void) noexcept
    {
        return _size;
    }

 
    template <typename... As>
    size_t& Table<As...>::_protCapacity(void) noexcept
    {
        return _capacity;
    }
    

    // Edit Functions
    template <typename... As>
    bool Table<As...>::_resize(const size_t& s_) noexcept
    {
        _size     = s_;
        _capacity = _capacity>s_ ? _capacity : s_;
    
        return true;
    }
    
    
    template <typename... As>
    bool Table<As...>::_reserve(const size_t& s_) noexcept
    {
        _capacity = _capacity>s_ ? _capacity : s_;
    
        return true;
    }
    
    

    template <typename... As>
    bool Table<As...>::_reduce(const size_t& s_) noexcept
    {
        _size     = _size>s_ ? s_ : _size;
        _capacity = s_;
    
        return true;
    }
    

    template <typename... As>
    bool Table<As...>::_insert(const size_t&, const Tuple<As...>&) noexcept
    {
        ++_size;
    
        return true;
    }

    
    template <typename... As>
    bool Table<As...>::_pushBack(const Tuple<As...>&) noexcept
    {
        ++_size;
    
        return true;
    }
    
    
    template <typename... As>
    bool Table<As...>::_moveBack(Tuple<As...>&&) noexcept
    {
        ++_size;
    
        return true;
    }


    template <typename... As>
    Table<As...>& Table<As...>::memset(int32_t) noexcept
    {
        return *this;
    }



    //(    gd::Table<T, As...> Lamination for Lamination    )//
    // Static Functions
    template <typename T, typename... As> template <typename U>
    constexpr auto Table<T, As...>::_depth(int32_t, Empty) noexcept
    -> typename std::invoke_result_t<decltype(&U::depth), Empty>
    {
        return T::depth(_key_)+Table<As...>::depth(_key_);
    }        
    
    
    template <typename T, typename... As> template <typename U>
    constexpr auto Table<T, As...>::_depth(int16_t, Empty) noexcept
    -> int16_t
    {
        return 1+Table<As...>::depth(_key_);
    }
    
    
    template <typename T, typename... As>
    constexpr auto Table<T, As...>::depth(Empty) noexcept
    -> decltype(_depth<T>(0, _key_))
    {
        return _depth<T>(0, _key_);
    }
    
     
            
    
    //+    Member Functions    +//
    // Construcntion Functions
    #ifdef GROUPDATA_TABLE_EXCEPTION
    template <typename T, typename... As>
    Table<T, As...>::Table(void)
        : _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)))}
        , _tables   { }
    {
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::Table<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::Table(void)]", 1};
        
        return;
    }
    
    
    template <typename T, typename... As>
    Table<T, As...>::Table(const size_t& sz_)
        : _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*sz_))}
        , _tables   (sz_)
    {
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::Table<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::Table(const size_t&)]", sz_};
        
        return;
    }
    
    
    template <typename T, typename... As>
    Table<T, As...>::Table(const Table<T, As...>& tb_)
        : _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*tb_.size()))}
        , _tables   {tb_._tables}
    {
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::Table<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::Table(const Table<T, As...>&]", tb_.size()};
        std::memcpy(_elements, tb_._elements, tb_.size()*sizeof(T));

        /*for(size_t a=0; a<tb_.size(); ++a){
            new(_elements+a) T(tb_._elements(a));
        }*/
        
        return;
    }
    

    template <typename T, typename... As>
    Table<T, As...>::Table(std::initializer_list<Tuple<T, As...>> lst_)
        : _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*lst_.size()))}
        , _tables   (lst_.size())
    {
        std::cout<<"In"<<std::endl;
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::Table<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::Table(std::initializer_list<Tuple<T, As...>>)]", lst_.size()};
        
        _construct(Rank<sizeof...(As)>{ }, lst_);
    
        return;
    }
    
    
    template <typename T, typename... As> template <typename... I>
    Table<T, As...>& Table<T, As...>::construct(I... i_)
    {
        new(this) Table(i_...);

        return *this;
    }

    #else
    
    template <typename T, typename... As>
    Table<T, As...>::Table(void) noexcept
        : _elements {reinterpret_cast<T*>(std::malloc(0))}
        , _tables   { }
    {
        return;
    }
    
    
    template <typename T, typename... As>
    Table<T, As...>::Table(const size_t& sz_) noexcept
        : _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*sz_))}
        , _tables   (sz_)
    {
        return;
    }

    
    
    template <typename T, typename... As>
    Table<T, As...>::Table(const Table<T, As...>& tb_) noexcept
        : _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*tb_.size()))}
        , _tables   {tb_._tables}
    {
        std::memcpy(_elements, tb_._elements, tb_.size()*sizeof(T));
        
        return;
    }
       

    
    template <typename T, typename... As>
    Table<T, As...>::Table(std::initializer_list<Tuple<T, As...>> lst_) noexcept
        : _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*lst_.size()))}
        , _tables   (lst_.size())
    {
        _construct(Rank<sizeof...(As)>{ }, lst_);
    
        return;
    }
    

    template <typename T, typename... As> template <typename... I>
    Table<T, As...>& Table<T, As...>::construct(I... i_) noexcept
    {
        new(this) Table(i_...);

        return *this;
    }
    #endif


    template <typename T, typename... As> template <uint16_t N>
    void Table<T, As...>::_construct(Rank<N>, std::initializer_list<Tuple<T, As...>> lst_) noexcept
    {
        for(size_t a=0; a<lst_.size(); ++a) std::memcpy(&(this->path<N>()[a]), &(lst_.begin()[a].template ref<N>()), sizeof this->path<N>()[a]);
        
        _construct(Rank<N-1>{ }, lst_);
        
        return;
    }    
    
    
    template <typename T, typename... As>
    void Table<T, As...>::_construct(Rank<0>, std::initializer_list<Tuple<T, As...>> lst_) noexcept
    {
        for(size_t a=0; a<lst_.size(); ++a) std::memcpy(&(this->path<0>()[a]), &(lst_.begin()[a].template ref<0>()), sizeof this->path<0>()[a]);
        
        _protSize()    =lst_.size();
        _protCapacity()=lst_.size();
        
        return;
    }


    template <typename T, typename... As>
    Table<T, As...>::Table(Table<T, As...>&& tb_) noexcept
        : _elements {tb_._elements}
        , _tables   {std::move(tb_._tables)}
    {
        tb_._protSize()     =0;
        tb_._protCapacity() =0;
        tb_._elements       =nullptr;

        return;
    }


    // Destruction Functions
    template <typename T, typename... As>
    Table<T, As...>::~Table (void) noexcept
    {
        #ifdef GROUPDATA_TABLE_WARNING
        if(_elements){
            std::free(_elements);
            _elements=nullptr;
        }else{
            warning::double_free{std::string{"[gd::Table<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::~Table(void)]", "_elements"};
        }
        #else
        if(_elements){
            std::free(_elements);
            _elements=nullptr;
        }
        #endif

        return;
    }

 
    template <typename T, typename... As>
    Table<T, As...>& Table<T, As...>::destruct (void) noexcept
    {
        ~Table();

        return *this; 
    }



    // Reference functions
    template <typename T, typename... As> template<uint16_t N>
    const auto Table<T, As...>::path(void) const noexcept
    {
        return _path(Rank<N>{ });
    }
    
    
    
    template <typename T, typename... As> template<uint16_t N>
    const auto Table<T, As...>::_path(Rank<N>) const noexcept
    {
        return _tables._path(Rank<N-1>{ });
    }
    
    
    
    template <typename T, typename... As>
    const View<T> Table<T, As...>::_path(Rank<0>) const noexcept
    {
        return View<T>{size(), capacity(), _elements};
    }

    
    
    template <typename T, typename... As> template <uint16_t N>
    auto Table<T, As...>::_cdata(Rank<N>) const noexcept
    -> Tuple<const T*, const As*...>
    {
        return Tuple<const T*, const As*...>{_elements, _tables.data()};
    }
    

    
    template <typename T, typename... As>
    auto Table<T, As...>::_cdata(Rank<1>) const noexcept
    -> Tuple<const T*>
    {
        return Tuple<const T*>{_elements};
    }
    
    
    template <typename T, typename... As>
    auto Table<T, As...>::data(void) const noexcept
    -> decltype(_cdata(std::declval<Rank<sizeof...(As)+1>>()))
    {
        return _cdata(Rank<sizeof...(As)+1>{ });
    }
    
        
    template <typename T, typename... As> template <uint16_t N>
    auto Table<T, As...>::_operator_parentheses(const size_t& sz_, Rank<N>) const noexcept
    -> ElasticTuple<const T&, const As&...>
    {
        return ElasticTuple<const T&, const As&...>{_elements[sz_], _tables[sz_]};
    }
    

    template <typename T, typename... As>
    auto Table<T, As...>::_operator_parentheses(const size_t& sz_, Rank<1>) const noexcept
    -> ElasticTuple<const T&>
    {
        return ElasticTuple<const T&>{_elements[sz_]};
    }

    
    #ifdef GROUPDATA_TABLE_EXCEPTION
    template <typename T, typename... As>
    auto Table<T, As...>::operator[](const size_t& sz_) const
    -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()))
    {
        if(sz_>=capacity()) throw exception::exceeded_capacity_in_size_direction(std::string{"[gd::Table<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::operator()(const size_t&)]", capacity(), sz_);
        
        #ifdef GROUPDATA_TABLE_WARNING
        if(sz_>=size()) warning::exceeded_size(std::string{"[gd::Table<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::operator()(const size_t&)]", size(), sz_);
        #endif

        return _operator_parentheses(sz_, Rank<sizeof...(As)+1>{ });
    }

    #else
    
    template <typename T, typename... As>
    auto Table<T, As...>::operator[](const size_t& sz_) const noexcept
    -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()))
    {
        #ifdef GROUPDATA_TABLE_WARNING
        if(sz_>=size()) warning::exceeded_size(std::string{"[gd::Table<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::operator()(const size_t&)]", size(), sz_);
        #endif

        return _operator_parentheses(sz_, Rank<sizeof...(As)+1>{ });
    }
    #endif  
     
 
    template <typename T, typename... As>
    const size_t& Table<T, As...>::size(void) const noexcept
    {
        return _tables.size();
    }
    
    
    template <typename T, typename... As>
    const size_t& Table<T, As...>::capacity(void) const noexcept
    {
        return _tables.capacity();
    }




    // Access functions
    template <typename T, typename... As> template<uint16_t N>
    auto Table<T, As...>::path(void) noexcept
    {
        return _path(Rank<N>{ });
    }
    
    
    template <typename T, typename... As> template<uint16_t N>
    auto Table<T, As...>::_path(Rank<N>) noexcept
    {
        return _tables._path(Rank<N-1>{ });
    }
    
    
    template <typename T, typename... As>
    View<T> Table<T, As...>::_path(Rank<0>) noexcept
    {
        return View<T>{size(), capacity(), _elements};
    }
    

    template <typename T, typename... As> template <uint16_t N>
    auto Table<T, As...>::_data(Rank<N>) noexcept
    -> Tuple<T*, As*...>
    {
        return Tuple<T*, As*...>{_elements, _tables.data()};
    }
    
    
    template <typename T, typename... As>
    auto Table<T, As...>::_data(Rank<1>) noexcept
    -> Tuple<T*>
    {
        return Tuple<T*>{_elements};
    }
    

    template <typename T, typename... As>
    auto Table<T, As...>::data(void) noexcept
    -> decltype(_data(std::declval<Rank<sizeof...(As)+1>>()))
    {
        return _data(Rank<sizeof...(As)+1>{ });
    }
    
    
    template <typename T, typename... As> template <uint16_t N>
    auto Table<T, As...>::_operator_brackets(const size_t& sz_, Rank<N>) noexcept
    -> ElasticTuple<T&, As&...>
    {
        return ElasticTuple<T&, As&...>{_elements[sz_], _tables[sz_]};
    }
    
    
    template <typename T, typename... As>
    auto Table<T, As...>::_operator_brackets(const size_t& sz_, Rank<1>) noexcept
    -> ElasticTuple<T&>
    {
        return ElasticTuple<T&>{_elements[sz_]};
    }
    
    
    #ifdef GROUPDATA_TABLE_EXCEPTION
    template <typename T, typename... As>
    auto Table<T, As...>::operator[](const size_t& sz_)
    -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()))
    {
        if(sz_>=capacity()) throw exception::exceeded_capacity_in_size_direction(std::string{"[gd::Table<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::operator[](const size_t&)]", capacity(), sz_);

        #ifdef GROUPDATA_TABLE_WARNING
        if(sz_>=size()) warning::exceeded_size(std::string{"[gd::Table<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::operator[](const size_t&)]", size(), sz_);
        #endif

        return _operator_brackets(sz_, Rank<sizeof...(As)+1>{ });
    }

    #else
    
    template <typename T, typename... As>
    auto Table<T, As...>::operator[](const size_t& sz_) noexcept
    -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()))
    {
        #ifdef GROUPDATA_TABLE_WARNING
        if(sz_>=size()) warning::exceeded_size(std::string{"[gd::Table<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::operator[](const size_t&)]", size(), sz_);
        #endif

        return _operator_brackets(sz_, Rank<sizeof...(As)+1>{ });
    }
    #endif


    template <typename T, typename... As>
    void Table<T, As...>::_operator_equal(const Table<T, As...>& tb_) noexcept
    {
        std::memcpy(_elements, tb_._elements, tb_.size()*sizeof(T));
        
        _tables._operator_equal(tb_._tables);

        return;
    }
    
    
    template <typename T, typename... As>
    void Table<T, As...>::_operator_equal(Table<T, As...>&& tb_) noexcept
    {
        _elements=tb_._elements;
        tb_._elements=nullptr;

        _tables._operator_equal(std::move(tb_._tables));

        return;
    }



    template <typename T, typename... As>
    Table<T, As...>& Table<T, As...>::operator=(const Table<T, As...>& tb_) noexcept
    {
        if(!resize(tb_.size())) return *this;
        
        _operator_equal(tb_);

        return *this;
    }
    
    

    template <typename T, typename... As>
    Table<T, As...>& Table<T, As...>::operator=(Table<T, As...>&& tb_) noexcept
    {
        _operator_equal(std::move(tb_));

        return *this;
    }



    template <typename T, typename... As>
    size_t& Table<T, As...>::_protSize(void) noexcept
    {
        return _tables._protSize();
    }
    
    
    template <typename T, typename... As>
    size_t& Table<T, As...>::_protCapacity(void) noexcept
    {
        return _tables._protCapacity();
    }



    // Edit Functions
    template <typename T, typename... As>
    bool Table<T, As...>::resize(const size_t& s_) noexcept
    {
        bool ot_;
        if(capacity()<s_){
            ot_=_resize(s_);    
        }else{
            _protSize()=s_;
            return true;
        }
        
        return ot_;
    }
    

    template <typename T, typename... As>
    bool Table<T, As...>::_resize(const size_t& s_) noexcept
    {
        if(void* new_ptr_=std::realloc(_elements, sizeof(T)*s_)){
            _elements=reinterpret_cast<T*>(new_ptr_);
        }else{
            #ifdef GROUPDATA_TABLE_WARNING
            warning::failed_to_realloc{std::string{"[gd::Table<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::resize(const size_t&)]", _elements, s_};
            #endif

            return false;
        }

        return _tables._resize(s_);
    }
    
    
    template <typename T, typename... As>
    bool Table<T, As...>::reserve(const size_t& s_) noexcept
    {
        bool ot_;
        if(capacity()<s_){
            ot_=_reserve(s_);    
        }else{
            return true;
        }
        
        return ot_;
    }
    

    template <typename T, typename... As>
    bool Table<T, As...>::_reserve(const size_t& s_) noexcept
    {
        if(void* new_ptr_=std::realloc(_elements, sizeof(T)*s_)){
            _elements=reinterpret_cast<T*>(new_ptr_);
        }else{
            #ifdef GROUPDATA_TABLE_WARNING
            warning::failed_to_realloc{std::string{"[gd::Table<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::reserve(const size_t&)]", _elements, s_};
            #endif

            return false;
        }

        return _tables._reserve(s_);
    }
    
    
    template <typename T, typename... As>
    bool Table<T, As...>::reduce(const size_t& s_) noexcept
    {
        bool ot_;
        if(capacity()>s_){
            ot_=_reduce(s_);    
        }else{
            return true;
        }
        
        return ot_;
    }
    

    template <typename T, typename... As>
    bool Table<T, As...>::_reduce(const size_t& s_) noexcept
    {
        if(void* new_ptr_=std::realloc(_elements, sizeof(T)*s_)){
            _elements=reinterpret_cast<T*>(new_ptr_);
        }else{
            #ifdef GROUPDATA_TABLE_WARNING
            warning::failed_to_realloc{std::string{"[gd::Table<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::reduce(const size_t&)]", _elements, s_};
            #endif

            return false;
        }

        return _tables._reduce(s_);
    }


    template <typename T, typename... As>
    bool Table<T, As...>::insert(const size_t& s_, const Tuple<T, As...>& tp_) noexcept
    {
        if(!reserve(size()+1)) return false;
        
        return _insert(s_, tp_);
    }
    

    template <typename T, typename... As>
    bool Table<T, As...>::_insert(const size_t& s_, const Tuple<T, As...>& tp_) noexcept
    {
        std::memmove(_elements+s_+1, _elements+s_, sizeof(T)*(size()-s_));
        std::memcpy (_elements+s_, &tp_.element, sizeof tp_.element);

        return _tables._insert(s_, tp_.tuples);
    }



    template <typename T, typename... As>
    bool Table<T, As...>::pushBack(const Tuple<T, As...>& tp_) noexcept
    {
        size_t s_ = (size()+1)*2;
        if(!reserve(s_)) return false;
        
        return _pushBack(tp_);
    }


    template <typename T, typename... As>
    bool Table<T, As...>::_pushBack(const Tuple<T, As...>& tp_) noexcept
    {
        std::memcpy(_elements+size(), &tp_.element, sizeof(T));
        
        return _tables._pushBack(tp_.tuples);
    }
    
    
    template <typename T, typename... As>
    bool Table<T, As...>::moveBack(Tuple<T, As...>&& tp_) noexcept
    {
        size_t s_ = (size()+1)*2;
        if(!reserve(s_)) return false;
        
        return _moveBack(std::move(tp_));
    }


    template <typename T, typename... As>
    bool Table<T, As...>::_moveBack(Tuple<T, As ...>&& tp_) noexcept
    {
        std::memcpy(_elements+size(), &tp_.element, sizeof(T));
        
        return _tables._moveBack(std::move(tp_.tuples));
    }
    
    
    template <typename T, typename... As> 
    Table<As...>& Table<T, As...>::memset(int32_t ch_) noexcept
    {
        std::memset(_elements, ch_, sizeof(T)*capacity());
        _tables.memset(ch_);
        
        return *this;
    }

    
    
    
    // Casting Functions
    template <typename T, typename... As> template <uint16_t N, typename U, typename... Bs>
    void Table<T, As...>::_cast_table(Rank<N>, Table<U, Bs...>& tb_) const noexcept
    {
        for(size_t a=0; a<size(); ++a) tb_.template path<N>()[a]=this->path<N>()(a);
        
        _cast_table(Rank<N-1>{ }, tb_);

        return;
    }
    
    
    template <typename T, typename... As> template <typename U, typename... Bs>
    void Table<T, As...>::_cast_table(Rank<0>, Table<U, Bs...>& tb_) const noexcept
    {
        for(size_t a=0; a<size(); ++a) tb_.template path<0>()[a]=this->path<0>()(a);
        
        return;
    }


    template <typename T, typename... As> template <typename U, typename... Bs>
    Table<T, As...>::operator Table<U, Bs...> () const noexcept
    {
        Table<U, Bs...> tb_;
        if(!tb_.resize(size())) return tb_;
       
        _cast_table(Rank<(sizeof...(As)>sizeof...(Bs) ? sizeof...(Bs) : sizeof...(As))>{ }, tb_);

        return tb_;
    }
 
 
 
    //(    gd::ElasticTable Lamination for Lamination    )//
    //+    Static Functions    +//
    template <typename... As>
    constexpr uint16_t ElasticTable<As...>::depth(Empty) noexcept
    {
        return 0;
    }


    //+    Member Functions    +//
    // Construcntion Functions
    template <typename... As>
    ElasticTable<As...>::ElasticTable(void) noexcept
        : _size     {0}
        , _capacity {0}
    {
        return;
    }


    template <typename... As>
    ElasticTable<As...>::ElasticTable(const size_t& s_) noexcept
        : _size     {s_}
        , _capacity {s_}
    {
        return;
    }
    
    
    template <typename... As>
    ElasticTable<As...>::ElasticTable(const ElasticTable<As...>& tb_) noexcept
        : _size     {tb_._size}
        , _capacity {tb_._size}
    {
        return;
    }
    
    
    template <typename... As>
    ElasticTable<As...>::ElasticTable(ElasticTable<As...>&& tb_) noexcept
        : _size     {tb_._size}
        , _capacity {tb_._capacity}
    {
        return;
    }
    

    template <typename... As> template <typename... I>
    ElasticTable<As...>& ElasticTable<As ...>::construct(I... i_) noexcept
    {
        new(this) ElasticTable(i_...);

        return *this;
    }


    
    // Destruction Functions
    template <typename... As>
    ElasticTable<As...>::~ElasticTable(void) noexcept
    {
        _size     = 0;
        _capacity = 0;

        return;
    }
    

    template <typename... As>
    ElasticTable<As...>& ElasticTable<As ...>::destruct(void) noexcept
    {
        ~ElasticTable();

        return *this;
    }


    
    // Reference Functions
    template <typename... As>
    const size_t& ElasticTable<As ...>::size(void) const noexcept
    {
        return _size;
    }
    
    
    template <typename... As>
    const size_t& ElasticTable<As ...>::capacity(void) const noexcept
    {
        return _capacity;
    }



    // Access Functions
    template <typename... As>
    void ElasticTable<As...>::_operator_equal(const ElasticTable<As...>& tb_) const noexcept
    {
        _size    =tb_._size;
        _capacity=tb_._size;

        return;
    }
   

    template <typename... As>
    void ElasticTable<As...>::_operator_equal(ElasticTable<As...>&& tb_) const noexcept
    {
        _size    =tb_._size;
        _capacity=tb_._capacity;

        return;
    }

    
    template <typename... As>
    size_t& ElasticTable<As...>::_protSize(void) noexcept
    {
        return _size;
    }

 
    template <typename... As>
    size_t& ElasticTable<As...>::_protCapacity(void) noexcept
    {
        return _capacity;
    }
    

    // Edit Functions
    template <typename... As>
    bool ElasticTable<As...>::resize(const size_t& s_) noexcept
    {
        _size     = s_;
        _capacity = _capacity>s_ ? _capacity : s_;
    
        return true;
    }
    
    
    template <typename... As>
    bool ElasticTable<As...>::reserve(const size_t& s_) noexcept
    {
        _capacity = _capacity>s_ ? _capacity : s_;
    
        return true;
    }
    
    

    template <typename... As>
    bool ElasticTable<As...>::reduce(const size_t& s_) noexcept
    {
        _size     = _size>s_ ? s_ : _size;
        _capacity = s_;
    
        return true;
    }
    

    template <typename... As>
    bool ElasticTable<As...>::_insert(const size_t&, const ElasticTuple<As...>&) noexcept
    {
        ++_size;
    
        return true;
    }


    template <typename... As>
    bool ElasticTable<As...>::_pushBack(const ElasticTuple<As...>&) noexcept
    {
        ++_size;
    
        return true;
    }
    
    
    template <typename... As>
    bool ElasticTable<As...>::_moveBack(ElasticTuple<As...>&&) noexcept
    {
        ++_size;
    
        return true;
    }


    template <typename... As>
    ElasticTable<As...>& ElasticTable<As...>::memset(int32_t) noexcept
    {
        return *this;
    }



    //(    gd::ElasticTable<T, As...> Lamination for Lamination    )//
    // Static Functions
    template <typename T, typename... As> template <typename U>
    constexpr auto ElasticTable<T, As...>::_depth(int32_t, Empty) noexcept
    -> typename std::invoke_result_t<decltype(&U::depth), Empty>
    {
        return T::depth(_key_)+ElasticTable<As...>::depth(_key_);
    }        
    
    
    template <typename T, typename... As> template <typename U>
    constexpr auto ElasticTable<T, As...>::_depth(int16_t, Empty) noexcept
    -> int16_t
    {
        return 1+ElasticTable<As...>::depth(_key_);
    }
    
    
    template <typename T, typename... As>
    constexpr auto ElasticTable<T, As...>::depth(Empty) noexcept
    -> decltype(_depth<T>(0, _key_))
    {
        return _depth<T>(0, _key_);
    }
    
     
            
    
    //+    Member Functions    +//
    // Construcntion Functions
    #ifdef GROUPDATA_TABLE_EXCEPTION
    template <typename T, typename... As>
    ElasticTable<T, As...>::ElasticTable(void)
        : _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)))}
        , _tables   { }
    {
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::ElasticTable<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::ElasticTable(void)]", 1};
        
        return;
    }
    
    
    template <typename T, typename... As>
    ElasticTable<T, As...>::ElasticTable(const size_t& sz_)
        : _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*sz_))}
        , _tables   (sz_)
    {
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::ElasticTable<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::ElasticTable(const size_t&)]", sz_};
        
        return;
    }
    
    
    template <typename T, typename... As>
    ElasticTable<T, As...>::ElasticTable(const ElasticTable<T, As...>& tb_)
        : _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*tb_.size()))}
        , _tables   {tb_._tables}
    {
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::ElasticTable<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::ElasticTable(const ElasticTable<T, As...>&]", tb_.size()};

        for(size_t a=0; a<tb_.size(); ++a){
            new(_elements+a) T(tb_._elements[a]);
        }
        
        return;
    }
    

    template <typename T, typename... As>
    ElasticTable<T, As...>::ElasticTable(std::initializer_list<ElasticTuple<T, As...>> lst_)
        : _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*lst_.size()))}
        , _tables   (lst_.size())
    {
        if(!_elements) throw exception::failed_to_malloc{std::string{"[gd::ElasticTable<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::ElasticTable(std::initializer_list<ElasticTuple<T, As...>>)]", lst_.size()};
        
        _construct(Rank<sizeof...(As)>{ }, lst_, lst_.begin()[0].template ref<sizeof...(As)>());
    
        return;
    }
    
    template <typename T, typename... As> template <typename... I>
    ElasticTable<T, As...>& ElasticTable<T, As...>::construct(I... i_)
    {
        new(this) ElasticTable(i_...);

        return *this;
    }

    #else
    
    template <typename T, typename... As>
    ElasticTable<T, As...>::ElasticTable(void) noexcept
        : _elements {reinterpret_cast<T*>(std::malloc(0))}
        , _tables   { }
    {
        return;
    }
    
    
    template <typename T, typename... As>
    ElasticTable<T, As...>::ElasticTable(const size_t& sz_) noexcept
        : _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*sz_))}
        , _tables   (sz_)
    {
        return;
    }

    
    
    template <typename T, typename... As>
    ElasticTable<T, As...>::ElasticTable(const ElasticTable<T, As...>& tb_) noexcept
        : _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*tb_.size()))}
        , _tables   {tb_._tables}
    {
        for(size_t a=0; a<tb_.size(); ++a){
            new(_elements+a) T(tb_._elements[a]);
        }
        
        return;
    }
       

    
    template <typename T, typename... As>
    ElasticTable<T, As...>::ElasticTable(std::initializer_list<ElasticTuple<T, As...>> lst_) noexcept
        : _elements {reinterpret_cast<T*>(std::malloc(sizeof(T)*lst_.size()))}
        , _tables   (lst_.size())
    {
        _construct(Rank<sizeof...(As)>{ }, lst_, lst_.begin()[0].template ref<sizeof...(As)>());
    
        return;
    }
    

    template <typename T, typename... As> template <typename... I>
    ElasticTable<T, As...>& ElasticTable<T, As...>::construct(I... i_) noexcept
    {
        new(this) ElasticTable(i_...);

        return *this;
    }
    #endif


    template <typename T, typename... As> template <uint16_t N, typename U>
    void ElasticTable<T, As...>::_construct(Rank<N>, std::initializer_list<ElasticTuple<T, As...>> lst_, const U&) noexcept
    { 
        for(size_t a=0; a<lst_.size(); ++a){
            new(&(this->path<N>()[a])) U(lst_.begin()[a].template ref<N>());
        }
        
        _construct(Rank<N-1>{ }, lst_, lst_.begin()[0].template ref<N-1>());
        
        return; 
    }    
    
    
    template <typename T, typename... As> template <typename U>
    void ElasticTable<T, As...>::_construct(Rank<0>, std::initializer_list<ElasticTuple<T, As...>> lst_, const U&) noexcept
    {
        for(size_t a=0; a<lst_.size(); ++a){
            new(&(this->path<0>()[a])) U(lst_.begin()[a].template ref<0>());
        }

        _protSize()    =lst_.size();
        _protCapacity()=lst_.size();
        
        return;
    }


    template <typename T, typename... As>
    ElasticTable<T, As...>::ElasticTable(ElasticTable<T, As...>&& tb_) noexcept
        : _elements {tb_._elements}
        , _tables   {std::move(tb_._tables)}
    {
        tb_._protSize()     =0;
        tb_._protCapacity() =0;
        tb_._elements       =nullptr;

        return;
    }


    // Destruction Functions
    template <typename T, typename... As>
    ElasticTable<T, As...>::~ElasticTable (void) noexcept
    {
        for(size_t a=0; a<size(); ++a){
            (_elements+a)->~T();
        }

        #ifdef GROUPDATA_TABLE_WARNING
        if(_elements){
            std::free(_elements);
            _elements=nullptr;
        }else{
            warning::double_free{std::string{"[gd::ElasticTable<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::~ElasticTable(void)]", "_elements"};
        }
        #else
        if(_elements){
            std::free(_elements);
            _elements=nullptr;
        }
        #endif
        
        return;
    }

 
    template <typename T, typename... As>
    ElasticTable<T, As...>& ElasticTable<T, As...>::destruct (void) noexcept
    {
        ~ElasticTable();

        return *this; 
    }



    // Reference functions
    template <typename T, typename... As> template<uint16_t N>
    const auto ElasticTable<T, As...>::path(void) const noexcept
    {
        return _path(Rank<N>{ });
    }
    
    
    
    template <typename T, typename... As> template<uint16_t N>
    const auto ElasticTable<T, As...>::_path(Rank<N>) const noexcept
    {
        return _tables._path(Rank<N-1>{ });
    }
    
    
    
    template <typename T, typename... As>
    const ElasticView<T> ElasticTable<T, As...>::_path(Rank<0>) const noexcept
    {
        return ElasticView<T>{size(), capacity(), _elements};
    }

    
    
    template <typename T, typename... As> template <uint16_t N>
    auto ElasticTable<T, As...>::_cdata(Rank<N>) const noexcept
    -> Tuple<const T*, const As*...>
    {
        return Tuple<const T*, const As*...>{_elements, _tables.data()};
    }
    

    
    template <typename T, typename... As>
    auto ElasticTable<T, As...>::_cdata(Rank<1>) const noexcept
    -> Tuple<const T*>
    {
        return Tuple<const T*>{_elements};
    }
    
    
    template <typename T, typename... As>
    auto ElasticTable<T, As...>::data(void) const noexcept
    -> decltype(_cdata(std::declval<Rank<sizeof...(As)+1>>()))
    {
        return _cdata(Rank<sizeof...(As)+1>{ });
    }
    
        
    template <typename T, typename... As> template <uint16_t N>
    auto ElasticTable<T, As...>::_operator_parentheses(const size_t& sz_, Rank<N>) const noexcept
    -> ElasticTuple<const T&, const As&...>
    {
        return ElasticTuple<const T&, const As&...>{_elements[sz_], _tables[sz_]};
    }
    

    template <typename T, typename... As>
    auto ElasticTable<T, As...>::_operator_parentheses(const size_t& sz_, Rank<1>) const noexcept
    -> ElasticTuple<const T&>
    {
        return ElasticTuple<const T&>{_elements[sz_]};
    }

    
    #ifdef GROUPDATA_TABLE_EXCEPTION
    template <typename T, typename... As>
    auto ElasticTable<T, As...>::operator[](const size_t& sz_) const
    -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()))
    {
        if(sz_>=capacity()) throw exception::exceeded_capacity_in_size_direction(std::string{"[gd::ElasticTable<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::operator()(const size_t&)]", capacity(), sz_);
        
        #ifdef GROUPDATA_TABLE_WARNING
        if(sz_>=size()) warning::exceeded_size(std::string{"[gd::ElasticTable<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::operator()(const size_t&)]", size(), sz_);
        #endif

        return _operator_parentheses(sz_, Rank<sizeof...(As)+1>{ });
    }

    #else
    
    template <typename T, typename... As>
    auto ElasticTable<T, As...>::operator[](const size_t& sz_) const noexcept
    -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()))
    {
        #ifdef GROUPDATA_TABLE_WARNING
        if(sz_>=size()) warning::exceeded_size(std::string{"[gd::ElasticTable<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::operator()(const size_t&)]", size(), sz_);
        #endif

        return _operator_parentheses(sz_, Rank<sizeof...(As)+1>{ });
    }
    #endif  
     
 
    template <typename T, typename... As>
    const size_t& ElasticTable<T, As...>::size(void) const noexcept
    {
        return _tables.size();
    }
    
    
    template <typename T, typename... As>
    const size_t& ElasticTable<T, As...>::capacity(void) const noexcept
    {
        return _tables.capacity();
    }




    // Access functions
    template <typename T, typename... As> template<uint16_t N>
    auto ElasticTable<T, As...>::path(void) noexcept
    {
        return _path(Rank<N>{ });
    }
    
    
    template <typename T, typename... As> template<uint16_t N>
    auto ElasticTable<T, As...>::_path(Rank<N>) noexcept
    {
        return _tables._path(Rank<N-1>{ });
    }
    
    
    template <typename T, typename... As>
    ElasticView<T> ElasticTable<T, As...>::_path(Rank<0>) noexcept
    {
        return ElasticView<T>{size(), capacity(), _elements};
    }


    template <typename T, typename... As> template <uint16_t N>
    auto ElasticTable<T, As...>::_data(Rank<N>) noexcept
    -> Tuple<T*, As*...>
    {
        return Tuple<T*, As*...>{_elements, _tables.data()};
    }
    
    
    template <typename T, typename... As>
    auto ElasticTable<T, As...>::_data(Rank<1>) noexcept
    -> Tuple<T*>
    {
        return Tuple<T*>{_elements};
    }
    

    template <typename T, typename... As>
    auto ElasticTable<T, As...>::data(void) noexcept
    -> decltype(_data(std::declval<Rank<sizeof...(As)+1>>()))
    {
        return _data(Rank<sizeof...(As)+1>{ });
    }
    
    
    template <typename T, typename... As> template <uint16_t N>
    auto ElasticTable<T, As...>::_operator_brackets(const size_t& sz_, Rank<N>) noexcept
    -> ElasticTuple<T&, As&...>
    {
        return ElasticTuple<T&, As&...>{_elements[sz_], _tables[sz_]};
    }
    
    
    template <typename T, typename... As>
    auto ElasticTable<T, As...>::_operator_brackets(const size_t& sz_, Rank<1>) noexcept
    -> ElasticTuple<T&>
    {
        return ElasticTuple<T&>{_elements[sz_]};
    }
    
    
    #ifdef GROUPDATA_TABLE_EXCEPTION
    template <typename T, typename... As>
    auto ElasticTable<T, As...>::operator[](const size_t& sz_)
    -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()))
    {
        if(sz_>=capacity()) throw exception::exceeded_capacity_in_size_direction(std::string{"[gd::ElasticTable<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::operator[](const size_t&)]", capacity(), sz_);

        #ifdef GROUPDATA_TABLE_WARNING
        if(sz_>=size()) warning::exceeded_size(std::string{"[gd::ElasticTable<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::operator[](const size_t&)]", size(), sz_);
        #endif

        return _operator_brackets(sz_, Rank<sizeof...(As)+1>{ });
    }

    #else
    
    template <typename T, typename... As>
    auto ElasticTable<T, As...>::operator[](const size_t& sz_) noexcept
    -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()))
    {
        #ifdef GROUPDATA_TABLE_WARNING
        if(sz_>=size()) warning::exceeded_size(std::string{"[gd::ElasticTable<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::operator[](const size_t&)]", size(), sz_);
        #endif

        return _operator_brackets(sz_, Rank<sizeof...(As)+1>{ });
    }
    #endif


    template <typename T, typename... As>
    ElasticTable<T, As...>& ElasticTable<T, As...>::_operator_equal(const ElasticTable<T, As...>& tb_) noexcept
    {
        for(size_t a=0; a<size(); ++a){
            _elements[a]=tb_._elements[a];
        }
        
        _tables._operator_equal(tb_._tables);

        return *this;
    }
    
    
    template <typename T, typename... As>
    ElasticTable<T, As...>& ElasticTable<T, As...>::_operator_equal(ElasticTable<T, As...>&& tb_) noexcept
    {
        _elements=tb_._elements;
        tb_._elements=nullptr;

        _tables._operator_equal(std::move(tb_._tables));

        return *this;
    }



    template <typename T, typename... As>
    ElasticTable<T, As...>& ElasticTable<T, As...>::operator=(const ElasticTable<T, As...>& tb_) noexcept
    {
        if(!resize(tb_.size())) return *this;
        
        _operator_equal(tb_);

        return *this;
    }
    
    

    template <typename T, typename... As>
    ElasticTable<T, As...>& ElasticTable<T, As...>::operator=(ElasticTable<T, As...>&& tb_) noexcept
    {
        _operator_equal(std::move(tb_));

        return *this;
    }



    template <typename T, typename... As>
    size_t& ElasticTable<T, As...>::_protSize(void) noexcept
    {   
        size_t& tt=_tables._protSize();
        
        return tt;
    }
    
    
    template <typename T, typename... As>
    size_t& ElasticTable<T, As...>::_protCapacity(void) noexcept
    {
        size_t& tt=_tables._protCapacity();
        
        return tt;
    }



    // Edit Functions
    template <typename T, typename... As>
    bool ElasticTable<T, As...>::resize(const size_t& s_) noexcept
    {
        if(size()>s_){
            
            for(size_t a=s_; a<size(); ++a) (_elements+a)->~T();
            
            return _tables.resize(s_);

        }else if(capacity()<s_){
            
            if(void* new_ptr_=std::malloc(sizeof(T)*s_)){
                
                T* new_elements=reinterpret_cast<T*>(new_ptr_);
                for(size_t a=0; a<size(); ++a){
                    new(new_elements+a) T(std::move(_elements[a]));
                    _elements[a].~T();
                }
                std::free(_elements);

                for(size_t a=size(); a<s_; ++a){
                    new(new_elements+a) T();
                }

                _elements=new_elements;

                return _tables.resize(s_);
            
            }else{
                
                #ifdef GROUPDATA_TABLE_WARNING
                warning::failed_to_malloc{std::string{"[gd::ElasticTable<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::resize(const size_t&)]", s_};
                #endif

                return false;
            }

        }else if(size()<s_){
            
            for(size_t a=size(); a<s_; ++a){
                new(_elements+a) T();
            }
            
            return _tables.resize(s_);
        }
        
        return true;
    }
    

    
    template <typename T, typename... As>
    bool ElasticTable<T, As...>::reserve(const size_t& s_) noexcept
    {
        if(capacity()<s_){
            
            if(void* new_ptr_=std::malloc(sizeof(T)*s_)){
                
                T* new_elements=reinterpret_cast<T*>(new_ptr_);
                for(size_t a=0; a<size(); ++a){
                    new(new_elements+a) T(std::move(_elements[a]));
                    _elements[a].~T();
                }
                std::free(_elements);

                _elements=new_elements;

                return _tables.reserve(s_);
            
            }else{

                #ifdef GROUPDATA_TABLE_WARNING
                warning::failed_to_malloc{std::string{"[gd::ElasticTable<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::reserve(const size_t&)]", s_};
                #endif

                return false;
            }
        }
        
        return true;
    }
    
    
    template <typename T, typename... As>
    bool ElasticTable<T, As...>::reduce(const size_t& s_) noexcept
    {
        if(capacity()>s_){
            
            if(size()>s_){
                for(size_t a=s_; a<size(); ++a) (_elements+a)->~T();
            }
            
            if(void* new_ptr_=std::realloc(_elements, sizeof(T)*s_)){
                
                _elements=reinterpret_cast<T*>(new_ptr_);

                return _tables.reduce(s_);
                
            }else{
                
                #ifdef GROUPDATA_TABLE_WARNING
                warning::failed_to_realloc{std::string{"[gd::ElasticTable<"}+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::reduce(const size_t&)]", _elements, s_};
                #endif
            
                return false;
            }
        }

        return true;
    }
 

    template <typename T, typename... As>
    bool ElasticTable<T, As...>::insert(const size_t& s_, const ElasticTuple<T, As...>& tp_) noexcept
    {
        
        if(!reserve(s_)) return false;
        
        return _insert(s_, tp_);
    }

    
    template <typename T, typename... As>
    bool ElasticTable<T, As...>::_insert(const size_t& s_, const ElasticTuple<T, As...>& tp_) noexcept
    {
        
        size_t sz=size();
        int count=0;
        for(size_t a=sz-1; a>=s_; --a){
            new(_elements+a+1) T(std::move(_elements[a]));
            if(a==0) break;
        }

        new(_elements+s_) T(tp_.element);
        
        return _tables._insert(s_, tp_.tuples);
    }

    template <typename T, typename... As>
    bool ElasticTable<T, As...>::pushBack(const ElasticTuple<T, As...>& tp_) noexcept
    {
        
        size_t s_ = (size()+1)*2;
        if(!reserve(s_)) return false;
        
        return _pushBack(tp_);
    }


    template <typename T, typename... As>
    bool ElasticTable<T, As...>::_pushBack(const ElasticTuple<T, As...>& tp_) noexcept
    {
        new(_elements+size()) T{tp_.element};

        return _tables._pushBack(tp_.tuples);
    }
    
    
    template <typename T, typename... As>
    bool ElasticTable<T, As...>::moveBack(ElasticTuple<T, As...>&& tp_) noexcept
    {
        size_t s_ = (size()+1)*2;
        if(!reserve(s_)) return false;
        
        return _moveBack(std::move(tp_));
    }


    template <typename T, typename... As>
    bool ElasticTable<T, As...>::_moveBack(ElasticTuple<T, As...>&& tp_) noexcept
    {
        new(_elements+size()) T{std::move(tp_.element)};
        
        return _tables._moveBack(std::move(tp_.tuples));
    }
    
    
    
    // Casting Functions
    template <typename T, typename... As> template <uint16_t N, typename U, typename... Bs>
    void ElasticTable<T, As...>::_cast_table(Rank<N>, ElasticTable<U, Bs...>& tb_) const noexcept
    {
        for(size_t a=0; a<size(); ++a) tb_.template path<N>()[a]=this->path<N>()(a);
        
        _cast_table(Rank<N-1>{ }, tb_);

        return;
    }
    
    
    template <typename T, typename... As> template <typename U, typename... Bs>
    void ElasticTable<T, As...>::_cast_table(Rank<0>, ElasticTable<U, Bs...>& tb_) const noexcept
    {
        for(size_t a=0; a<size(); ++a) tb_.template path<0>()[a]=this->path<0>()(a);
        
        return;
    }


    template <typename T, typename... As> template <typename U, typename... Bs>
    ElasticTable<T, As...>::operator ElasticTable<U, Bs...> () const noexcept
    {
        ElasticTable<U, Bs...> tb_;
        if(!tb_.resize(size())) return tb_;
       
        _cast_table(Rank<(sizeof...(As)>sizeof...(Bs) ? sizeof...(Bs) : sizeof...(As))>{ }, tb_);

        return tb_;
    }
   
     
 
    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <typename T, typename... As>
    std::ostream& operator<<(std::ostream& os_, const gd::Table<T, As...>& tb_) noexcept
    {
        if(tb_.size()) gd::ostream(tb_[0], os_);
        for(uint16_t a=1; a<tb_.size(); ++a){
            os_<<std::endl;
            gd::ostream(tb_[a], os_);
        }
    
        return os_;
    }
    
    
    template <typename T, typename... As>
    std::ostream& operator<<(std::ostream& os_, const gd::ElasticTable<T, As...>& tb_) noexcept
    {
        if(tb_.size()) gd::ostream(tb_[0], os_);
        for(uint16_t a=1; a<tb_.size(); ++a){
            os_<<std::endl;
            gd::ostream(tb_[a], os_);
        }
    
        return os_;
    }
}
#endif


/*
int main(void){
    
    {
        //{gd::Tuple<double, int>{3.0, 1}};
        gd::Tuple<double, int, char> tp1{1.31, 3, 'a'};
        gd::Tuple<double, int, char> tp2{3.5, 2, 'b'};
        gd::Tuple<double, int, char> tp3{2.14, 9, 'c'};
        
        //gd::Table<2, double, int, char> br1{tp1, tp2, tp3};
        gd::Table<3, double, int, char> br1{{1.31, 3, 'a'}, {9.0, 3, 'b'}, {2.0, 4, '\0'}};


        //gd::Tuple<double, int> tp3{-1.0, 9};
        std::cout<<std::endl<<br1<<std::endl;
        std::cout<<br1.spec().path<2>()<<std::endl;
        std::cout<<br1.path<2>().spec()<<std::endl;
        
    }
    {
        std::cout<<"Bravo"<<std::endl;
        gd::Table<3, double, int, char> br1{{1.31, 3, 'a'}, {9.0, 3, 'b'}, {2.0, 4, '\0'}}; 
        std::cout<<br1<<std::endl;
        gd::Tuple<double, int, char> tp1{3.33, 1, 'N'};
        br1[0]=tp1; 
        std::cout<<br1[0]<<std::endl;
    }
    */
    //{
        
        /*std::cout<<"Bravo"<<std::endl;
        gd::Table<5, int, double> gr1={{0, 3.0}, {3, 4.5}};
        std::cout<<gr1<<std::endl;
        */
   // }
    /*
    {
        std::cout<<"Charlie"<<std::endl;
        gd::Table<5, double> gr1={0, 3, 3, 2, 5};
        std::cout<<gr1.ref<0>()<<" "<<gr1.path<0>()<<" "<<gr1.spec()<<" "<<gr1.data()<<std::endl;
        //gr1.ref<0>()[3]=4.5;
        //gr1.ref<2>();
        gr1.path<0>()[3]=4.5;
        //gr1.path<2>();
        //gr1.spec()[3]=4.5;
        gr1.data()[3]=1.0;
        std::cout<<gr1<<std::endl;
    }
    {
        std::cout<<"Delta"<<std::endl;
        gd::Table<5, double> gr1={0, 3, 3, 2, 5};
        std::cout<<gr1(3)<<std::endl;
        //std::cout<<(gr1(3)=2.3)<<std::endl;
        std::cout<<(gr1[3]=2.3)<<std::endl;
        //std::cout<<gr1(5)<<std::endl;
        //std::cout<<(gr1[5]=2.3)<<std::endl;
        
    }
    */

//}

