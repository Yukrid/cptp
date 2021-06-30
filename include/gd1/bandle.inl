#ifndef GROUPDATA_BANDLE_INL
#define GROUPDATA_BANDLE_INL

#include "bandle.hpp"

namespace gd{

    //++++++++++++++++++++++//
    //    Bandle Objects    //
    //++++++++++++++++++++++//
    //(    gd::Bandle Aggregated Void    )//
    //+    Static Functions    +//
    template <size_t S, typename... As>
    constexpr uint16_t Bandle<S, As...>::depth(Empty) noexcept
    {
        return 0;
    }


    //+    Member Functions    +//
    // Construcntion Functions
    template <size_t S, typename... As>
    Bandle<S, As...>::Bandle(void) noexcept
    {
        return;
    }
    
    
    template <size_t S, typename... As>
    Bandle<S, As...>::Bandle(const Bandle<S, As...>&) noexcept
    {
        return;
    }
    
    
    template <size_t S, typename... As>
    Bandle<S, As...>::Bandle(Bandle<S, As...>&&) noexcept
    {
        return;
    }
    
    
    template <size_t S, typename... As> template <typename... I>
    Bandle<S, As...>& Bandle<S, As ...>::construct(I... i_) noexcept
    {
        new(this) Bandle(i_...);

        return *this;
    }



    // Destruction Function
    template <size_t S, typename... As>
    Bandle<S, As...>::~Bandle(void) noexcept
    {
        return;
    }
 
 
    template <size_t S, typename... As>
    Bandle<S, As...>& Bandle<S, As ...>::destruct(void) noexcept
    {
        ~Bandle();

        return *this;
    }



    // Access Functions
    template <size_t S, typename... As>
    void Bandle<S, As ...>::operator=(const Bandle<S, As...>&) const noexcept
    {
        return;
    }
    
    
    template <size_t S, typename... As>
    void Bandle<S, As ...>::operator=(Bandle<S, As...>&&) const noexcept
    {
        return;
    }





    //(    gd::Bandle<S, T, As...> Lamination for Lamination    )//
    // Static Functions
    template <size_t S, typename T, typename... As> template <typename U>
    constexpr auto Bandle<S, T, As...>::_depth(int32_t, Empty) noexcept
    -> typename std::invoke_result_t<decltype(&U::depth), Empty>
    {
        return T::depth(_key_)+Bandle<S, As...>::depth(_key_);
    }        
    
    
    template <size_t S, typename T, typename... As> template <typename U>
    constexpr auto Bandle<S, T, As...>::_depth(int16_t, Empty) noexcept
    -> int16_t
    {
        return 1+Bandle<S, As...>::depth(_key_);
    }
    
    
    template <size_t S, typename T, typename... As>
    constexpr auto Bandle<S, T, As...>::depth(Empty) noexcept
    -> decltype(_depth<T>(0, _key_))
    {
        return _depth<T>(0, _key_);
    }
    
     
    template <size_t S, typename T, typename... As>
    constexpr size_t Bandle<S, T, As...>::size(Empty) noexcept
    {
        return S;   
    }

    
        

    //+    Member Functions    +//
    // Construcntion Functions
    template <size_t S, typename T, typename... As>
    Bandle<S, T, As...>::Bandle(void) noexcept
        : _elements { }
        , _bandles  { }
    {
        return;
    }
    
    
    template <size_t S, typename T, typename... As>
    Bandle<S, T, As...>::Bandle(const Bandle<S, T, As...>& br_) noexcept
        : _elements {br_._elements}
        , _bandles  {br_._bandles}
    {
        return;
    }
    
    
    template <size_t S, typename T, typename... As>
    Bandle<S, T, As...>::Bandle(Bandle<S, T, As...>&& br_) noexcept
        : _elements {br_._elements}
        , _bandles  {br_._bandles}
    {
        return;
    }

    
    template <size_t S, typename T, typename... As>
    Bandle<S, T, As...>::Bandle(std::initializer_list<Tuple<T, As...>> lst_) noexcept
        : _elements { }
        , _bandles  { }
    {
        _construct(Rank<sizeof...(As)>{ }, lst_);

        return;
    }
    

    template <size_t S, typename T, typename... As>
    Bandle<S, T, As...>& Bandle<S, T, As...>::construct(void) noexcept
    {
        new(this) Bandle();

        return *this;
    }
    
    
    template <size_t S, typename T, typename... As> template <uint16_t N>
    void Bandle<S, T, As...>::_construct(Rank<N>, std::initializer_list<Tuple<T, As...>> lst_) noexcept
    {
        for(size_t a=0; a<S && a<lst_.size(); ++a) std::memcpy(&(this->path<N>()[a]), &(lst_.begin()[a].template ref<N>()), sizeof this->path<N>()[a]);
        for(size_t a=lst_.size(); a<S; ++a)        std::memcpy(&(this->path<N>()[a]), &(lst_.end()[-1].template ref<N>()),  sizeof this->path<N>()[a]);
       
        _construct(Rank<N-1>{ }, lst_);
        
        return;
    }    
    
    
    template <size_t S, typename T, typename... As>
    void Bandle<S, T, As...>::_construct(Rank<0>, std::initializer_list<Tuple<T, As...>> lst_) noexcept
    {
        for(size_t a=0; a<S && a<lst_.size(); ++a) std::memcpy(&(this->path<0>()[a]), &(lst_.begin()[a].template ref<0>()), sizeof this->path<0>()[a]);
        for(size_t a=lst_.size(); a<S; ++a)        std::memcpy(&(this->path<0>()[a]), &(lst_.end()[-1].template ref<0>()),  sizeof this->path<0>()[a]);    
    
        return;
    }


    template <size_t S, typename T, typename... As>
    Bandle<S, T, As...>& Bandle<S, T, As...>::construct(const Bandle<S, T, As...>& br_) noexcept
    {
        new(this) Bandle(br_);

        return *this;
    }
    
    
    template <size_t S, typename T, typename... As>
    Bandle<S, T, As...>& Bandle<S, T, As...>::construct(Bandle<S, T, As...>&& br_) noexcept
    {
        new(this) Bandle(br_);

        return *this;
    }
   
    
    template <size_t S, typename T, typename... As>
    Bandle<S, T, As...>& Bandle<S, T, As...>::construct(std::initializer_list<Tuple<T, As...>> lst_) noexcept
    {
        new(this) Bandle(lst_);

        return *this;
    }


    
    // Destruction Functions
    template <size_t S, typename T, typename... As>
    Bandle<S, T, As...>::~Bandle (void) noexcept
    {
        return;
    }

 
    template <size_t S, typename T, typename... As>
    Bandle<S, T, As...>& Bandle<S, T, As...>::destruct (void) noexcept
    {
        return *this; 
    }
   


    // Reference functions
    template <size_t S, typename T, typename... As> template<uint16_t N>
    const auto& Bandle<S, T, As...>::ref(void) const noexcept
    {
        return _ref(Rank<N>{ });
    }
    
    
    
    template <size_t S, typename T, typename... As> template<uint16_t N>
    const auto& Bandle<S, T, As...>::_ref(Rank<N>) const noexcept
    {
        return _bandles._ref(Rank<N-1>{ });
    }
    
    
    
    template <size_t S, typename T, typename... As>
    const Vector<S, T>& Bandle<S, T, As...>::_ref(Rank<0>) const noexcept
    {
        return _elements;
    }

    
    
    template <size_t S, typename T, typename... As> template <uint16_t N>
    auto Bandle<S, T, As...>::_spec(Rank<N>) const noexcept
    -> Tuple<const T*, const As*...>
    {
        return Tuple<const T*, const As*...>{_elements.spec(), _bandles.spec()};
    }
    

    
    template <size_t S, typename T, typename... As>
    auto Bandle<S, T, As...>::_spec(Rank<1>) const noexcept
    -> Tuple<const T*>
    {
        return Tuple<const T*>{_elements.spec()};
    }
    
    

    template <size_t S, typename T, typename... As>
    auto Bandle<S, T, As...>::spec(void) const noexcept
    -> decltype(_spec(std::declval<Rank<sizeof...(As)+1>>()))
    {
        return _spec(Rank<sizeof...(As)+1>{ });
    }
    
    
    
    template <size_t S, typename T, typename... As> template <uint16_t N>
    auto Bandle<S, T, As...>::_operator_parentheses(const size_t& sz_, Rank<N>) const noexcept
    -> ElasticTuple<const T&, const As&...>
    {
        return ElasticTuple<const T&, const As&...>{_elements(sz_), _bandles(sz_)};
    }
    

    
    template <size_t S, typename T, typename... As>
    auto Bandle<S, T, As...>::_operator_parentheses(const size_t& sz_, Rank<1>) const noexcept
    -> ElasticTuple<const T&>
    {
        return ElasticTuple<const T&>{_elements(sz_)};
    }
    
    
    #ifdef GROUPDATA_BANDLE_EXCEPTION
    template <size_t S, typename T, typename... As>
    auto Bandle<S, T, As...>::operator()(const size_t& sz_) const
    -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()))
    {
        if(sz_>=S) throw exception::exceeded_capacity_in_size_direction(std::string{"[gd::Bandle<"}+std::to_string(S)+", "+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::operator()(const size_t&)]", S, sz_);

        return _operator_parentheses(sz_, Rank<sizeof...(As)+1>{ });
    }

    #else
    
    template <size_t S, typename T, typename... As>
    auto Bandle<S, T, As...>::operator()(const size_t& sz_) const noexcept
    -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()))
    {
        return _operator_parentheses(sz_, Rank<sizeof...(As)+1>{ });
    }
    #endif  



    // Access functions
    template <size_t S, typename T, typename... As> template<uint16_t N>
    auto& Bandle<S, T, As...>::path(void) noexcept
    {
        return _path(Rank<N>{ });
    }
    
    
    template <size_t S, typename T, typename... As> template<uint16_t N>
    auto& Bandle<S, T, As...>::_path(Rank<N>) noexcept
    {
        return _bandles._path(Rank<N-1>{ });
    }
    
    
    template <size_t S, typename T, typename... As>
    Vector<S, T>& Bandle<S, T, As...>::_path(Rank<0>) noexcept
    {
        return _elements;
    }
    

    template <size_t S, typename T, typename... As> template <uint16_t N>
    auto Bandle<S, T, As...>::_data(Rank<N>) noexcept
    -> Tuple<T*, As*...>
    {
        return Tuple<T*, As*...>{_elements.data(), _bandles.data()};
    }
    
    
    template <size_t S, typename T, typename... As>
    auto Bandle<S, T, As...>::_data(Rank<1>) noexcept
    -> Tuple<T*>
    {
        return Tuple<T*>{_elements.data()};
    }
    

    template <size_t S, typename T, typename... As>
    auto Bandle<S, T, As...>::data(void) noexcept
    -> decltype(_data(std::declval<Rank<sizeof...(As)+1>>()))
    {
        return _data(Rank<sizeof...(As)+1>{ });
    }
    
    
    template <size_t S, typename T, typename... As> template <uint16_t N>
    auto Bandle<S, T, As...>::_operator_brackets(const size_t& sz_, Rank<N>) noexcept
    -> ElasticTuple<T&, As&...>
    {
        return ElasticTuple<T&, As&...>{_elements[sz_], _bandles[sz_]};
    }
    
    
    template <size_t S, typename T, typename... As>
    auto Bandle<S, T, As...>::_operator_brackets(const size_t& sz_, Rank<1>) noexcept
    -> ElasticTuple<T&>
    {
        return ElasticTuple<T&>{_elements[sz_]};
    }
    
    
    #ifdef GROUPDATA_BANDLE_EXCEPTION
    template <size_t S, typename T, typename... As>
    auto Bandle<S, T, As...>::operator[](const size_t& sz_)
    -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()))
    {
        if(sz_>=S) throw exception::exceeded_capacity_in_size_direction(std::string{"[gd::Bandle<"}+std::to_string(S)+", "+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::operator[](const size_t&)]", S, sz_);

        return _operator_brackets(sz_, Rank<sizeof...(As)+1>{ });
    }

    #else
    
    template <size_t S, typename T, typename... As>
    auto Bandle<S, T, As...>::operator[](const size_t& sz_) noexcept
    -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()))
    {
        return _operator_brackets(sz_, Rank<sizeof...(As)+1>{ });
    }
    #endif


    template <size_t S, typename T, typename... As>
    Bandle<S, T, As...>& Bandle<S, T, As...>::operator=(const Bandle<S, T, As...>& br_) noexcept
    {
        _elements=br_._elements;
        _bandles =br_._bandles;

        return *this;
    }
    
    
    template <size_t S, typename T, typename... As>
    Bandle<S, T, As...>& Bandle<S, T, As...>::operator=(Bandle<S, T, As...>&& br_) noexcept
    {
        _elements=std::move(br_._elements);
        _bandles =std::move(br_._bandles);

        return *this;
    }
    
    
    
    // Casting Functions
    template <size_t S, typename T, typename... As> template <uint16_t N, size_t R, typename U, typename... Bs>
    void Bandle<S, T, As...>::_cast_bandle(Rank<N>, Bandle<R, U, Bs...>& br_) const noexcept
    {
        for(size_t a=0; a<S && a<R; ++a) br_.template path<N>()[a]=this->ref<N>()(a);
        for(size_t a=S; a<R; ++a)        br_.template path<N>()[a]=this->ref<N>()(S-1);
        
        _cast_bandle(Rank<N-1>{ }, br_);

        return;
    }
    
    
    template <size_t S, typename T, typename... As> template <size_t R, typename U, typename... Bs>
    void Bandle<S, T, As...>::_cast_bandle(Rank<0>, Bandle<R, U, Bs...>& br_) const noexcept
    {
        for(size_t a=0; a<S && a<R; ++a) br_.template path<0>()[a]=this->ref<0>()(a);
        for(size_t a=S; a<R; ++a)        br_.template path<0>()[a]=this->ref<0>()(S-1);
        
        return;
    }


    template <size_t S, typename T, typename... As> template <size_t R, typename U, typename... Bs>
    Bandle<S, T, As...>::operator Bandle<R, U, Bs...> () const noexcept
    {
        Bandle<R, U, Bs...> br_;
       
        _cast_bandle(Rank<(sizeof...(As)>sizeof...(Bs) ? sizeof...(Bs) : sizeof...(As))>{ }, br_);

        return br_;
    }
    
    
    
    //(    gd::ElasticBandle Aggregated Void    )//
    //+    Static Functions    +//
    template <size_t S, typename... As>
    constexpr uint16_t ElasticBandle<S, As...>::depth(Empty) noexcept
    {
        return 0;
    }


    //+    Member Functions    +//
    // Construcntion Functions
    template <size_t S, typename... As>
    ElasticBandle<S, As...>::ElasticBandle(void) noexcept
    {
        return;
    }
    
    
    template <size_t S, typename... As>
    ElasticBandle<S, As...>::ElasticBandle(const ElasticBandle<S, As...>&) noexcept
    {
        return;
    }
    
    
    template <size_t S, typename... As>
    ElasticBandle<S, As...>::ElasticBandle(ElasticBandle<S, As...>&&) noexcept
    {
        return;
    }
    
    
    template <size_t S, typename... As> template <typename... I>
    ElasticBandle<S, As...>& ElasticBandle<S, As ...>::construct(I... i_) noexcept
    {
        new(this) ElasticBandle(i_...);

        return *this;
    }



    // Destruction Function
    template <size_t S, typename... As>
    ElasticBandle<S, As...>::~ElasticBandle(void) noexcept
    {
        return;
    }
 
 
    template <size_t S, typename... As>
    ElasticBandle<S, As...>& ElasticBandle<S, As ...>::destruct(void) noexcept
    {
        ~ElasticBandle();

        return *this;
    }



    // Access Functions
    template <size_t S, typename... As>
    void ElasticBandle<S, As ...>::operator=(const ElasticBandle<S, As...>&) const noexcept
    {
        return;
    }
    
    
    template <size_t S, typename... As>
    void ElasticBandle<S, As ...>::operator=(ElasticBandle<S, As...>&&) const noexcept
    {
        return;
    }





    //(    gd::ElasticBandle<S, T, As...> Lamination for Lamination    )//
    // Static Functions
    template <size_t S, typename T, typename... As> template <typename U>
    constexpr auto ElasticBandle<S, T, As...>::_depth(int32_t, Empty) noexcept
    -> typename std::invoke_result_t<decltype(&U::depth), Empty>
    {
        return T::depth(_key_)+ElasticBandle<S, As...>::depth(_key_);
    }        
    
    
    template <size_t S, typename T, typename... As> template <typename U>
    constexpr auto ElasticBandle<S, T, As...>::_depth(int16_t, Empty) noexcept
    -> int16_t
    {
        return 1+ElasticBandle<S, As...>::depth(_key_);
    }
    
    
    template <size_t S, typename T, typename... As>
    constexpr auto ElasticBandle<S, T, As...>::depth(Empty) noexcept
    -> decltype(_depth<T>(0, _key_))
    {
        return _depth<T>(0, _key_);
    }
    
     
    template <size_t S, typename T, typename... As>
    constexpr size_t ElasticBandle<S, T, As...>::size(Empty) noexcept
    {
        return S;   
    }

    
        

    //+    Member Functions    +//
    // Construcntion Functions
    template <size_t S, typename T, typename... As>
    ElasticBandle<S, T, As...>::ElasticBandle(void) noexcept
        : _elements { }
        , _bandles  { }
    {
        return;
    }
    
    
    template <size_t S, typename T, typename... As>
    ElasticBandle<S, T, As...>::ElasticBandle(const ElasticBandle<S, T, As...>& br_) noexcept
        : _elements {br_._elements}
        , _bandles  {br_._bandles}
    {
        return;
    }
    
    
    template <size_t S, typename T, typename... As>
    ElasticBandle<S, T, As...>::ElasticBandle(ElasticBandle<S, T, As...>&& br_) noexcept
        : _elements {br_._elements}
        , _bandles  {br_._bandles}
    {
        return;
    }

    
    template <size_t S, typename T, typename... As>
    ElasticBandle<S, T, As...>::ElasticBandle(std::initializer_list<ElasticTuple<T, As...>> lst_) noexcept
        : _elements { }
        , _bandles  { }
    {        
        _construct(Rank<sizeof...(As)>{ }, lst_, lst_.begin()[0].template ref<sizeof...(As)>());

        return;
    }
    

    template <size_t S, typename T, typename... As>
    ElasticBandle<S, T, As...>& ElasticBandle<S, T, As...>::construct(void) noexcept
    {
        new(this) ElasticBandle();

        return *this;
    }
    
    
    template <size_t S, typename T, typename... As> template <uint16_t N, typename U>
    void ElasticBandle<S, T, As...>::_construct(Rank<N>, std::initializer_list<ElasticTuple<T, As...>> lst_, const U&) noexcept
    {
        for(size_t a=0; a<S && a<lst_.size(); ++a){
            this->path<N>()(a).~U();
            new(&(this->path<N>()[a])) U(lst_.begin()[a].template ref<N>());
        }

        for(size_t a=lst_.size(); a<S; ++a){
            this->path<N>()(a).~U();
            new(&(this->path<N>()[a])) U(lst_.end()[-1].template ref<N>());
        }
        
        _construct(Rank<N-1>{ }, lst_, lst_.begin()[0].template ref<N-1>());
           
        return;
    }    
    
    
    template <size_t S, typename T, typename... As> template <typename U>
    void ElasticBandle<S, T, As...>::_construct(Rank<0>, std::initializer_list<ElasticTuple<T, As...>> lst_, const U&) noexcept
    {
        for(size_t a=0; a<S && a<lst_.size(); ++a){
            this->path<0>()(a).~U();
            new(&(this->path<0>()[a])) U(lst_.begin()[a].template ref<0>());
        }

        for(size_t a=lst_.size(); a<S; ++a){
            this->path<0>()(a).~U();
            new(&(this->path<0>()[a])) U(lst_.end()[-1].template ref<0>());
        }
    
        return;
    }


    template <size_t S, typename T, typename... As>
    ElasticBandle<S, T, As...>& ElasticBandle<S, T, As...>::construct(const ElasticBandle<S, T, As...>& br_) noexcept
    {
        new(this) ElasticBandle(br_);

        return *this;
    }
    
    
    template <size_t S, typename T, typename... As>
    ElasticBandle<S, T, As...>& ElasticBandle<S, T, As...>::construct(ElasticBandle<S, T, As...>&& br_) noexcept
    {
        new(this) ElasticBandle(br_);

        return *this;
    }
   
    
    template <size_t S, typename T, typename... As>
    ElasticBandle<S, T, As...>& ElasticBandle<S, T, As...>::construct(std::initializer_list<ElasticTuple<T, As...>> lst_) noexcept
    {
        new(this) ElasticBandle(lst_);

        return *this;
    }


    
    // Destruction Functions
    template <size_t S, typename T, typename... As>
    ElasticBandle<S, T, As...>::~ElasticBandle (void) noexcept
    {
        return;
    }

 
    template <size_t S, typename T, typename... As>
    ElasticBandle<S, T, As...>& ElasticBandle<S, T, As...>::destruct (void) noexcept
    {
        return *this; 
    }
   


    // Reference functions
    template <size_t S, typename T, typename... As> template<uint16_t N>
    const auto& ElasticBandle<S, T, As...>::ref(void) const noexcept
    {
        return _ref(Rank<N>{ });
    }
    
    
    
    template <size_t S, typename T, typename... As> template<uint16_t N>
    const auto& ElasticBandle<S, T, As...>::_ref(Rank<N>) const noexcept
    {
        return _bandles._ref(Rank<N-1>{ });
    }
    
    
    
    template <size_t S, typename T, typename... As>
    const ElasticVector<S, T>& ElasticBandle<S, T, As...>::_ref(Rank<0>) const noexcept
    {
        return _elements;
    }

    
    
    template <size_t S, typename T, typename... As> template <uint16_t N>
    auto ElasticBandle<S, T, As...>::_spec(Rank<N>) const noexcept
    -> Tuple<const T*, const As*...>
    {
        return Tuple<const T*, const As*...>{_elements.spec(), _bandles.spec()};
    }
    

    
    template <size_t S, typename T, typename... As>
    auto ElasticBandle<S, T, As...>::_spec(Rank<1>) const noexcept
    -> Tuple<const T*>
    {
        return Tuple<const T*>{_elements.spec()};
    }
    
    

    template <size_t S, typename T, typename... As>
    auto ElasticBandle<S, T, As...>::spec(void) const noexcept
    -> decltype(_spec(std::declval<Rank<sizeof...(As)+1>>()))
    {
        return _spec(Rank<sizeof...(As)+1>{ });
    }
    
    
    
    template <size_t S, typename T, typename... As> template <uint16_t N>
    auto ElasticBandle<S, T, As...>::_operator_parentheses(const size_t& sz_, Rank<N>) const noexcept
    -> ElasticTuple<const T&, const As&...>
    {
        return ElasticTuple<const T&, const As&...>{_elements(sz_), _bandles(sz_)};
    }
    

    
    template <size_t S, typename T, typename... As>
    auto ElasticBandle<S, T, As...>::_operator_parentheses(const size_t& sz_, Rank<1>) const noexcept
    -> ElasticTuple<const T&>
    {
        return ElasticTuple<const T&>{_elements(sz_)};
    }
    
    
    #ifdef GROUPDATA_BANDLE_EXCEPTION
    template <size_t S, typename T, typename... As>
    auto ElasticBandle<S, T, As...>::operator()(const size_t& sz_) const
    -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()))
    {
        if(sz_>=S) throw exception::exceeded_capacity_in_size_direction(std::string{"[gd::ElasticBandle<"}+std::to_string(S)+", "+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::operator()(const size_t&)]", S, sz_);

        return _operator_parentheses(sz_, Rank<sizeof...(As)+1>{ });
    }

    #else
    
    template <size_t S, typename T, typename... As>
    auto ElasticBandle<S, T, As...>::operator()(const size_t& sz_) const noexcept
    -> decltype(_operator_parentheses(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()))
    {
        return _operator_parentheses(sz_, Rank<sizeof...(As)+1>{ });
    }
    #endif  



    // Access functions
    template <size_t S, typename T, typename... As> template<uint16_t N>
    auto& ElasticBandle<S, T, As...>::path(void) noexcept
    {
        return _path(Rank<N>{ });
    }
    
    
    template <size_t S, typename T, typename... As> template<uint16_t N>
    auto& ElasticBandle<S, T, As...>::_path(Rank<N>) noexcept
    {
        return _bandles._path(Rank<N-1>{ });
    }
    
    
    template <size_t S, typename T, typename... As>
    ElasticVector<S, T>& ElasticBandle<S, T, As...>::_path(Rank<0>) noexcept
    {
        return _elements;
    }
    

    template <size_t S, typename T, typename... As> template <uint16_t N>
    auto ElasticBandle<S, T, As...>::_data(Rank<N>) noexcept
    -> Tuple<T*, As*...>
    {
        return Tuple<T*, As*...>{_elements.data(), _bandles.data()};
    }
    
    
    template <size_t S, typename T, typename... As>
    auto ElasticBandle<S, T, As...>::_data(Rank<1>) noexcept
    -> Tuple<T*>
    {
        return Tuple<T*>{_elements.data()};
    }
    

    template <size_t S, typename T, typename... As>
    auto ElasticBandle<S, T, As...>::data(void) noexcept
    -> decltype(_data(std::declval<Rank<sizeof...(As)+1>>()))
    {
        return _data(Rank<sizeof...(As)+1>{ });
    }
    
    
    template <size_t S, typename T, typename... As> template <uint16_t N>
    auto ElasticBandle<S, T, As...>::_operator_brackets(const size_t& sz_, Rank<N>) noexcept
    -> ElasticTuple<T&, As&...>
    {
        return ElasticTuple<T&, As&...>{_elements[sz_], _bandles[sz_]};
    }
    
    
    template <size_t S, typename T, typename... As>
    auto ElasticBandle<S, T, As...>::_operator_brackets(const size_t& sz_, Rank<1>) noexcept
    -> ElasticTuple<T&>
    {
        return ElasticTuple<T&>{_elements[sz_]};
    }
    
    
    #ifdef GROUPDATA_BANDLE_EXCEPTION
    template <size_t S, typename T, typename... As>
    auto ElasticBandle<S, T, As...>::operator[](const size_t& sz_)
    -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()))
    {
        if(sz_>=S) throw exception::exceeded_capacity_in_size_direction(std::string{"[gd::ElasticBandle<"}+std::to_string(S)+", "+typeid(T).name()+", {Other "+std::to_string(sizeof...(As))+" types}>::operator[](const size_t&)]", S, sz_);

        return _operator_brackets(sz_, Rank<sizeof...(As)+1>{ });
    }

    #else
    
    template <size_t S, typename T, typename... As>
    auto ElasticBandle<S, T, As...>::operator[](const size_t& sz_) noexcept
    -> decltype(_operator_brackets(std::declval<size_t>(), std::declval<Rank<sizeof...(As)+1>>()))
    {
        return _operator_brackets(sz_, Rank<sizeof...(As)+1>{ });
    }
    #endif


    template <size_t S, typename T, typename... As>
    ElasticBandle<S, T, As...>& ElasticBandle<S, T, As...>::operator=(const ElasticBandle<S, T, As...>& br_) noexcept
    {
        _elements=br_._elements;
        _bandles =br_._bandles;

        return *this;
    }
    
    
    template <size_t S, typename T, typename... As>
    ElasticBandle<S, T, As...>& ElasticBandle<S, T, As...>::operator=(ElasticBandle<S, T, As...>&& br_) noexcept
    {
        _elements=std::move(br_._elements);
        _bandles =std::move(br_._bandles);

        return *this;
    }
    
    
    
    // Casting Functions
    template <size_t S, typename T, typename... As> template <uint16_t N, size_t R, typename U, typename... Bs>
    void ElasticBandle<S, T, As...>::_cast_bandle(Rank<N>, ElasticBandle<R, U, Bs...>& br_) const noexcept
    {
        for(size_t a=0; a<S && a<R; ++a) br_.template path<N>()[a]=this->ref<N>()(a);
        for(size_t a=S; a<R; ++a)        br_.template path<N>()[a]=this->ref<N>()(S-1);
        
        _cast_bandle(Rank<N-1>{ }, br_);

        return;
    }
    
    
    template <size_t S, typename T, typename... As> template <size_t R, typename U, typename... Bs>
    void ElasticBandle<S, T, As...>::_cast_bandle(Rank<0>, ElasticBandle<R, U, Bs...>& br_) const noexcept
    {
        for(size_t a=0; a<S && a<R; ++a) br_.template path<0>()[a]=this->ref<0>()(a);
        for(size_t a=S; a<R; ++a)        br_.template path<0>()[a]=this->ref<0>()(S-1);
        
        return;
    }


    template <size_t S, typename T, typename... As> template <size_t R, typename U, typename... Bs>
    ElasticBandle<S, T, As...>::operator ElasticBandle<R, U, Bs...> () const noexcept
    {
        ElasticBandle<R, U, Bs...> br_;
       
        _cast_bandle(Rank<(sizeof...(As)>sizeof...(Bs) ? sizeof...(Bs) : sizeof...(As))>{ }, br_);

        return br_;
    }

    
 
    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <size_t S, typename T, typename... As>
    std::ostream& operator<<(std::ostream& os_, const gd::Bandle<S, T, As...>& brd_) noexcept
    {
        if(brd_.size()) gd::ostream(brd_(0), os_);
        for(uint16_t a=1; a<S; ++a){
            os_<<std::endl;
            gd::ostream(brd_(a), os_);
        }
    
        return os_;
    }
    
    
    template <size_t S, typename T, typename... As>
    std::ostream& operator<<(std::ostream& os_, const gd::ElasticBandle<S, T, As...>& brd_) noexcept
    {
        if(brd_.size()) gd::ostream(brd_(0), os_);
        for(uint16_t a=1; a<S; ++a){
            os_<<std::endl;
            gd::ostream(brd_(a), os_);
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
        
        //gd::Bandle<2, double, int, char> br1{tp1, tp2, tp3};
        gd::Bandle<3, double, int, char> br1{{1.31, 3, 'a'}, {9.0, 3, 'b'}, {2.0, 4, '\0'}};


        //gd::Tuple<double, int> tp3{-1.0, 9};
        std::cout<<std::endl<<br1<<std::endl;
        std::cout<<br1.spec().path<2>()<<std::endl;
        std::cout<<br1.path<2>().spec()<<std::endl;
        
    }
    {
        std::cout<<"Bravo"<<std::endl;
        gd::Bandle<3, double, int, char> br1{{1.31, 3, 'a'}, {9.0, 3, 'b'}, {2.0, 4, '\0'}}; 
        std::cout<<br1<<std::endl;
        gd::Tuple<double, int, char> tp1{3.33, 1, 'N'};
        br1[0]=tp1; 
        std::cout<<br1[0]<<std::endl;
    }
    */
    //{
        
        /*std::cout<<"Bravo"<<std::endl;
        gd::Bandle<5, int, double> gr1={{0, 3.0}, {3, 4.5}};
        std::cout<<gr1<<std::endl;
        */
   // }
    /*
    {
        std::cout<<"Charlie"<<std::endl;
        gd::Bandle<5, double> gr1={0, 3, 3, 2, 5};
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
        gd::Bandle<5, double> gr1={0, 3, 3, 2, 5};
        std::cout<<gr1(3)<<std::endl;
        //std::cout<<(gr1(3)=2.3)<<std::endl;
        std::cout<<(gr1[3]=2.3)<<std::endl;
        //std::cout<<gr1(5)<<std::endl;
        //std::cout<<(gr1[5]=2.3)<<std::endl;
        
    }
    */

//}

