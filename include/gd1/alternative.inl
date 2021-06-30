//#include "alternative.hpp"

#include <climits>
#include <cstring>

namespace gd{

    //+++++++++++++++++++++//
    //    Group Objects    //
    //+++++++++++++++++++++//
    //(    gd::Alternative Lamination for Lamination    )//
    //+    Static Functions    +//
    template <typename... As>
    inline constexpr uint16_t Alternative<As...>::depth (Empty) noexcept
    {
        return 1;
    }


    template <typename... As>
    inline constexpr size_t Alternative<As...>::size (Empty) noexcept
    {
        return 1;
    }
    
    
    template <typename... As>
    inline constexpr size_t Alternative<As...>::width (Empty) noexcept
    {
        return shadows.width();
    }
    

    
    //+    Member Functions    +//
    // Constructon Functions
    template <typename... As>
    Alternative<As...>::Alternative(void) noexcept
        : _number {0}
    { 
        return;
    }
    
    
    template <typename... As>
    Alternative<As...>::Alternative(const Alternative<As...>& al_) noexcept
    {
        std::memcpy(this, &al_, sizeof *this);
        
        return;
    }
    
    
#ifdef GROUPDATA_ALTERNATIVE_EXCEPTION
    template <typename... As>
    Alternative<As...>::Alternative(uint16_t num_)
    {
        if(!_construct(Rank<0>(), num_)){
            throw exception::unexpected_number_or_type(std::string("[gd::Alternative<As...>::Alternative(uint16_t)]"), num_, "");
        }

        return;
    }
    

    template <typename... As> template <uint16_t R>
    bool Alternative<As...>::_construct(Rank<R>, uint16_t num_) noexcept
    {
        if(R==num_){
            _number=num_;
            return true;
        }

        return _construct(Rank<R+1>(), num_);
    }


    template <typename... As>
    bool Alternative<As...>::_construct(Rank<sizeof...(As)-1>, uint16_t num_) noexcept
    {
        if(sizeof...(As)-1==num_){
            _number=num_;
            return true;
        }

        return false;
    }

#else

    template <typename... As>
    Alternative<As...>::Alternative(uint16_t num_) noexcept
        : _number {num_}
    {
        return;
    }

#endif

#ifdef GROUPDATA_ALTERNATIVE_EXCEPTION
    template <typename... As> template <typename T>
    Alternative<As...>::Alternative(uint16_t num_, const T& t_)
    {
        if(!_construct(Rank<0>(), num_, t_)){
            throw exception::unexpected_number_or_type(std::string("[gd::Alternative<As...>::Alternative(uint16_t)]"), num_, typeid(T).name());
        }

        return;
    }


    template <typename... As> template <uint16_t R, typename T>
    bool Alternative<As...>::_construct(Rank<R>, uint16_t num_, const T& t_) noexcept
    {
        if(R==num_ && typeid(T)==typeid(Type<R>)){
            _number=num_;
            std::memcpy(_element, &t_, sizeof t_);
            return true;
        }else{
            return _construct(Rank<R+1>(), num_, t_);
        }    
    }


    template <typename... As> template <typename T>
    bool Alternative<As...>::_construct(Rank<sizeof...(As)-1>, uint16_t num_, const T& t_) noexcept
    {
        if(sizeof...(As)-1==num_ && typeid(T)==typeid(Type<sizeof...(As)-1>)){
            _number=num_;
            std::memcpy(_element, &t_, sizeof t_);
            return true;
        }else{
            return false;
        }
    }

#else

    template <typename... As> template <typename T>
    Alternative<As...>::Alternative(uint16_t num_, const T& t_) noexcept
        : _number  (num_)
        , _element ( )
    {
        std::memcpy(_element, &t_, sizeof t_);

        return;
    }

#endif

    template <typename... As>
    auto Alternative<As...>::construct(void) noexcept -> Alternative<As...>&
    {
        new(this) Alternative();

        return *this;
    }
    

    template <typename... As>
    auto Alternative<As...>::construct(const Alternative<As...>& al_) noexcept -> Alternative<As...>&
    {
        new(this) Alternative(al_);

        return *this;
    }


    template <typename... As> template <uint16_t R>
    auto Alternative<As...>::construct(void) noexcept -> std::enable_if_t<(R<sizeof...(As)), Alternative<As...>&>
    {
        _number=R;

        return *this;
    }


    template <typename... As> template <uint16_t R, typename U>
    auto Alternative<As...>::construct(const U& u_) noexcept -> std::enable_if_t<std::is_same_v<Type<R>, U>, Alternative<As...>&>
    {
        _number=R;
        std::memcpy(_element, &u_, sizeof u_);

        return *this;
    }
    
    
    template <typename... As>
    Alternative<As...>& Alternative<As...>::construct(uint16_t num_) noexcept(noexcept(Alternative(std::declval<uint16_t>())))
    {
        new(this) Alternative(num_);

        return *this;
    }


    template <typename... As> template <typename T>
    Alternative<As...>& Alternative<As...>::construct(uint16_t num_, const T& t_) noexcept(noexcept(Alternative(std::declval<uint16_t>(), std::declval<T>())))
    {
        new(this) Alternative(num_, t_);

        return *this;
    }
   

    // Destructon Functions
    template <typename... As>
    Alternative<As...>::~Alternative(void) noexcept
    {   
        return;
    }


    template <typename... As> template<uint16_t N>
    Alternative<As...>& Alternative<As...>::destruct(void) noexcept
    {
        ~Alternative();

        return *this;
    }



    // Reference Functions
    template <typename... As>
    uint16_t Alternative<As...>::number(void) const noexcept
    {
        return _number;
    }


    template <typename... As> template <uint16_t R>
    auto Alternative<As...>::path(void) const noexcept -> const decltype(Shadow<As...>::template type<R>())&
    {
        return *reinterpret_cast<const decltype(Shadow<As...>::template type<R>())*>(_element);
    }


    template <typename... As>
    const Alternative<As...>* Alternative<As...>::data(void) const noexcept
    {
        return this;
    }


    template <typename... As>
    const Alternative<As...>& Alternative<As...>::operator[](size_t) const noexcept
    {
        return *this;
    }

    
   
    // Access Functions
    template <typename... As> template <uint16_t R>
    auto Alternative<As...>::path(void) noexcept -> const decltype(Shadow<As...>::template type<R>())&
    {
        return *reinterpret_cast<const decltype(Shadow<As...>::template type<R>())*>(_element);
    }
    
    
    template <typename... As>
    Alternative<As...>* Alternative<As...>::data(void) noexcept
    {
        return this;
    }


    template <typename... As>
    Alternative<As...>& Alternative<As...>::operator[](size_t) noexcept
    {
        return *this;
    }    



    // Ternary Operator
    template <typename... As>
    Alternative<As...>& Alternative<As...>::operator= (const Alternative<As...>& al_) noexcept
    {
        std::memcpy(this, &al_, sizeof *this);
        
        return *this;
    }
    

    template <typename... As>
    Alternative<As...>& Alternative<As...>::operator= (Alternative<As...>&& al_) noexcept
    {
        std::memcpy(this, &al_, sizeof *this);
        
        return *this;
    }
    
    


    //(    gd::ElasticAlternative Lamination for Lamination    )//
    //+    Static Functions    +//
    template <typename... As>
    inline constexpr uint16_t ElasticAlternative<As...>::depth (Empty) noexcept
    {
        return 1;
    }


    template <typename... As>
    inline constexpr size_t ElasticAlternative<As...>::size (Empty) noexcept
    {
        return 1;
    }
    
    
    template <typename... As>
    inline constexpr size_t ElasticAlternative<As...>::width (Empty) noexcept
    {
        return shadows.width();
    }
    

    
    //+    Member Functions    +//
    // Constructon Functions
    template <typename... As>
    ElasticAlternative<As...>::ElasticAlternative(void) noexcept
        : _number (0)
    { 
        _construct<0, Type<0>>();

        return;
    }
    
    
    template <typename... As>
    ElasticAlternative<As...>::ElasticAlternative(const ElasticAlternative<As...>& al_) noexcept
        : _number (al_.number())
    {
        _construct(Rank<sizeof...(As)-1>(), al_);

        return;
    }
    
    
    template <typename... As>
    ElasticAlternative<As...>::ElasticAlternative(ElasticAlternative<As...>&& al_) noexcept
        : _number (al_.number())
    {
        _construct(Rank<sizeof...(As)-1>(), std::move(al_));

        return;
    }
    

#ifdef GROUPDATA_ALTERNATIVE_EXCEPTION
    template <typename... As>
    ElasticAlternative<As...>::ElasticAlternative(uint16_t num_)
    {
        if(!_construct(Rank<sizeof...(As)>(), num_)){
            throw exception::unexpected_number_or_type(std::string("[gd::ElasticAlternative<As...>::ElasticAlternative(uint16_t)]"), num_, "");
        }

        return;
    }

#else

    template <typename... As>
    ElasticAlternative<As...>::ElasticAlternative(uint16_t num_) noexcept
    {
        _construct(Rank<sizeof...(As)>(), num_);

        return;
    }

#endif

    template <typename... As> template <uint16_t R>
    bool ElasticAlternative<As...>::_construct(Rank<R>, uint16_t num_) noexcept
    {
        if(R==num_){
            _number=num_;
            _construct<R-1, Type<R-1>>(); 
            return true;
        }

        return _construct(Rank<R-1>(), num_);
    }
    

    template <typename... As>
    bool ElasticAlternative<As...>::_construct(Rank<0>, uint16_t num_) noexcept
    {
        return false;
    }


#ifdef GROUPDATA_ALTERNATIVE_EXCEPTION
    template <typename... As> template <typename T>
    ElasticAlternative<As...>::ElasticAlternative(uint16_t num_, const T& t_)
    {
        if(!_construct(Rank<sizeof...(As)>(), num_, t_)){
            throw exception::unexpected_number_or_type(std::string("[gd::ElasticAlternative<As...>::ElasticAlternative(uint16_t, const T&)]"), num_, typeid(T).name());
        }

        return;
    }

#else

    template <typename... As> template <typename T>
    ElasticAlternative<As...>::ElasticAlternative(uint16_t num_, const T& t_) noexcept
    {
        _construct(Rank<sizeof...(As)>(), num_, t_);

        return;
    }

#endif

    template <typename... As> template <uint16_t R, typename T>
    bool ElasticAlternative<As...>::_construct(Rank<R>, uint16_t num_, const T& t_) noexcept
    {
        if(R-1==num_){
            construct<R-1, Type<R-1>>(*reinterpret_cast<const Type<R-1>*>(&t_)); 
            return true;
        }

        return _construct(Rank<R-1>(), num_, t_);
    }
    

    template <typename... As> template <typename T>
    bool ElasticAlternative<As...>::_construct(Rank<0>, uint16_t num_, const T& t_) noexcept
    {
        return false;
    }
 

#ifdef GROUPDATA_ALTERNATIVE_EXCEPTION
    template <typename... As> template <typename T>
    ElasticAlternative<As...>::ElasticAlternative(uint16_t num_, T&& t_)
    {
        if(!_construct(Rank<sizeof...(As)>(), num_, std::move(t_))){
            throw exception::unexpected_number_or_type(std::string("[gd::ElasticAlternative<As...>::ElasticAlternative(uint16_t, T&&)]"), num_, typeid(T).name());
        }

        return;
    }

#else

    template <typename... As> template <typename T>
    ElasticAlternative<As...>::ElasticAlternative(uint16_t num_, T&& t_) noexcept
    {
        _construct(Rank<sizeof...(As)>(), num_, std::move(t_));

        return;
    }

#endif

    template <typename... As> template <uint16_t R, typename T>
    bool ElasticAlternative<As...>::_construct(Rank<R>, uint16_t num_, T&& t_) noexcept
    {
        if(R-1==num_){
            _number=num_;
            construct<R-1, Type<R-1>>(std::move(*reinterpret_cast<Type<R-1>*>(&t_))); 
            return true;
        }

        return _construct(Rank<R-1>(), num_, std::move(t_));
    }
    

    template <typename... As> template <typename T>
    bool ElasticAlternative<As...>::_construct(Rank<0>, uint16_t num_, T&& t_) noexcept
    {
        return false;
    } 



    template <typename... As>
    auto ElasticAlternative<As...>::construct(void) noexcept -> ElasticAlternative<As...>&
    {
        _number=0;
        _construct<0, Type<0>>();

        return *this;
    }
    
    
    template <typename... As>
    auto ElasticAlternative<As...>::construct(const ElasticAlternative<As...>& al_) noexcept -> ElasticAlternative<As...>&
    {
        _construct(Rank<sizeof...(As)>(), al_);

        return *this;
    }
    
    
    template <typename... As> template <uint16_t R>
    auto ElasticAlternative<As...>::_construct(Rank<R>, const ElasticAlternative<As...>& al_) noexcept -> void
    {
        if(R-1==al_.number()){
            construct<R-1, Type<R-1>>(*reinterpret_cast<const Type<R-1>*>(&al_.path<R-1>()));
        }
        _construct(Rank<R-1>(), al_);

        return;
    }


    template <typename... As>
    auto ElasticAlternative<As...>::_construct(Rank<0>, const ElasticAlternative<As...>& al_) noexcept -> void
    {
        return;
    }
    
    
    template <typename... As>
    auto ElasticAlternative<As...>::construct(ElasticAlternative<As...>&& al_) noexcept -> ElasticAlternative<As...>&
    {
        _construct(Rank<sizeof...(As)>(), std::move(al_));

        return *this;
    }
    
    
    template <typename... As> template <uint16_t R>
    auto ElasticAlternative<As...>::_construct(Rank<R>, ElasticAlternative<As...>&& al_) noexcept -> void
    {
        if(R-1==al_.number()){
            construct<R-1, Type<R-1>>(std::move(*reinterpret_cast<Type<R-1>*>(al_.path<R-1>())));
        }
        _construct(Rank<R-1>(), std::move(al_));

        return;
    }


    template <typename... As>
    auto ElasticAlternative<As...>::_construct(Rank<0>, ElasticAlternative<As...>&& al_) noexcept -> void
    {
        return;
    }


    template <typename... As> template <uint16_t R>
    auto ElasticAlternative<As...>::construct(void) noexcept -> ElasticAlternative<As...>&
    {
        _number=R;
        _construct<R, Rank<R>>();

        return *this;
    }
    
    
    template <typename... As> template <uint16_t R, typename U>
    auto ElasticAlternative<As...>::_construct(void) noexcept -> void
    {
        new(reinterpret_cast<U*>(_element)) U{ };

        return;
    }
    

    template <typename... As> template <uint16_t R, typename U>
    auto ElasticAlternative<As...>::construct(const U& u_) noexcept -> std::enable_if_t<std::is_same_v<Type<R>, U>, ElasticAlternative<As...>&>
    {
        _number=R;
        new(reinterpret_cast<U*>(_element)) U{u_};

        return *this;
    }
    
    
    template <typename... As> template <uint16_t R, typename U>
    auto ElasticAlternative<As...>::construct(U&& u_) noexcept -> std::enable_if_t<std::is_same_v<Type<R>, U>, ElasticAlternative<As...>&>
    {
        _number=R;
        new(reinterpret_cast<U*>(_element)) U{std::move(u_)};

        return *this;
    }


    template <typename... As>
    ElasticAlternative<As...>& ElasticAlternative<As...>::construct (uint16_t num_) noexcept(noexcept(ElasticAlternative(std::declval<uint16_t>())))
    {
        new(this) ElasticAlternative(num_);

        return *this;
    }


    template <typename... As> template <typename T>
    ElasticAlternative<As...>& ElasticAlternative<As...>::construct (uint16_t num_, const T& t_) noexcept(noexcept(ElasticAlternative(std::declval<uint16_t>(), std::declval<T>())))
    {
        new(this) ElasticAlternative(num_, t_);

        return *this;
    }


    template <typename... As>
    auto ElasticAlternative<As...>::reconstruct(const ElasticAlternative<As...>& al_) noexcept -> ElasticAlternative<As...>&
    {
        destruct();
        _construct(Rank<sizeof...(As)-1>{}, al_);

        return *this;
    }


    template <typename... As>
    auto ElasticAlternative<As...>::reconstruct(ElasticAlternative<As...>&& al_) noexcept -> ElasticAlternative<As...>&
    {
        destruct();
        _construct(Rank<sizeof...(As)-1>{}, std::move(al_));

        return *this;
    }


    template <typename... As> template <uint16_t R>
    auto ElasticAlternative<As...>::reconstruct(void) noexcept -> ElasticAlternative<As...>&
    {
        destruct();
        _number=R;
        _construct<R, decltype(Shadow<As...>::template type<R>())>();

        return *this;
    }


     template <typename... As> template <uint16_t R, typename U>
    auto ElasticAlternative<As...>::reconstruct(const U& u_) noexcept -> std::enable_if_t<std::is_same_v<Type<R>, U>, ElasticAlternative<As...>&>
    {
        destruct();
        _number=R;
        new(reinterpret_cast<U*>(_element)) U{u_};

        return *this;
    }
    
    
    template <typename... As> template <uint16_t R, typename U>
    auto ElasticAlternative<As...>::reconstruct(U&& u_) noexcept -> std::enable_if_t<std::is_same_v<Type<R>, U>, ElasticAlternative<As...>&>
    {
        destruct();
        _number=R;
        new(reinterpret_cast<U*>(_element)) U{std::move(u_)};

        return *this;
    }


    template <typename... As>
    ElasticAlternative<As...>& ElasticAlternative<As...>::reconstruct (uint16_t num_) noexcept(noexcept(ElasticAlternative(std::declval<uint16_t>())))
    {
        destruct();
        new(this) ElasticAlternative(num_);

        return *this;
    }


    template <typename... As> template <typename T>
    ElasticAlternative<As...>& ElasticAlternative<As...>::reconstruct (uint16_t num_, const T& t_) noexcept(noexcept(ElasticAlternative(std::declval<uint16_t>(), std::declval<T>())))
    {
        destruct();
        new(this) ElasticAlternative(num_, t_);

        return *this;
    }


    
    // Destructon Functions
    template <typename... As>
    ElasticAlternative<As...>::~ElasticAlternative(void) noexcept
    {
        destruct();

        return;
    }


    template <typename... As>
    ElasticAlternative<As...>& ElasticAlternative<As...>::destruct(void) noexcept
    {
        _destruct(Rank<sizeof...(As)>{ });

        return *this;
    }
    
    
    template <typename... As> template <uint16_t R>
    void ElasticAlternative<As...>::_destruct(Rank<R>) noexcept
    {
        if(R==_number){
            _destruct<R-1, Type<R-1>>();
        }
            
        _destruct(Rank<R-1>{ });
    
        return;
    }
    
    
    template <typename... As>
    void ElasticAlternative<As...>::_destruct(Rank<0>) noexcept
    {
        return;
    }
    
    
    template <typename... As> template <uint16_t R, typename U>
    void ElasticAlternative<As...>::_destruct(void) noexcept
    {
        reinterpret_cast<U*>(_element)->~U();

        return;
    }



    // Reference Functions
    template <typename... As>
    uint16_t ElasticAlternative<As...>::number(void) const noexcept
    {
        return _number;
    }


    template <typename... As> template <uint16_t R>
    auto ElasticAlternative<As...>::path(void) const noexcept -> const decltype(Shadow<As...>::template type<R>())&
    {
        return *reinterpret_cast<const decltype(Shadow<As...>::template type<R>())*>(_element);
    }


    template <typename... As>
    const ElasticAlternative<As...>* ElasticAlternative<As...>::data(void) const noexcept
    {
        return this;
    }


    template <typename... As>
    const ElasticAlternative<As...>& ElasticAlternative<As...>::operator()(size_t) const noexcept
    {
        return *this;
    }

    
   
    // Access Functions
    template <typename... As> template <uint16_t R>
    auto ElasticAlternative<As...>::path(void) noexcept -> decltype(Shadow<As...>::template type<R>())&
    {
        return *reinterpret_cast<decltype(Shadow<As...>::template type<R>())*>(_element);
    }
    
    
    template <typename... As>
    ElasticAlternative<As...>* ElasticAlternative<As...>::data(void) noexcept
    {
        return this;
    }


    template <typename... As>
    ElasticAlternative<As...>& ElasticAlternative<As...>::operator[](size_t) noexcept
    {
        return *this;
    }
    
    

    // Ternary Operator
    template <typename... As>
    ElasticAlternative<As...>& ElasticAlternative<As...>::operator= (const ElasticAlternative<As...>& al_) noexcept
    {
        _operator_equal(Rank<sizeof...(As)>(), al_);
        
        return *this;
    }
    
    
    template <typename... As> template <uint16_t R>
    void ElasticAlternative<As...>::_operator_equal (Rank<R>, const ElasticAlternative<As...>& al_) noexcept
    {
        
        if(R-1==al_.number()){
            if(_number==al_.number()){
                path<R-1>()=al_.path<R-1>();
            }else{
                reconstruct<R-1>(al_.path<R-1>());
            }
        }else{
            _operator_equal(Rank<R-1>(), al_);
        }

        return;
    }


    template <typename... As>
    void ElasticAlternative<As...>::_operator_equal (Rank<0>, const ElasticAlternative<As...>& al_) noexcept
    {
        return;
    }


    template <typename... As>
    ElasticAlternative<As...>& ElasticAlternative<As...>::operator= (ElasticAlternative<As...>&& al_) noexcept
    {
        _operator_equal(Rank<sizeof...(As)>(), std::move(al_));
        
        return *this;
    }
    
    
    template <typename... As> template <uint16_t R>
    void ElasticAlternative<As...>::_operator_equal (Rank<R>, ElasticAlternative<As...>&& al_) noexcept
    {
        
        if(R-1==al_.number()){
            if(_number==al_.number()){
                path<R-1>()=std::move(al_.path<R-1>());
            }else{
                reconstruct<R-1>(std::move(al_.path<R-1>()));
            }

        }else{
            _operator_equal(Rank<R-1>(), std::move(al_));
        }

        return;
    }


    template <typename... As>
    void ElasticAlternative<As...>::_operator_equal (Rank<0>, ElasticAlternative<As...>&& al_) noexcept
    {
        return;
    }
    


    
    //+++++++++++++++++++++++++++++++++++//
    //    Attached Namespace Function    //
    //+++++++++++++++++++++++++++++++++++//
    template <typename... As>
    std::ostream& operator<<(std::ostream& os_, const gd::Alternative<As...>& al_) noexcept
    {
        _operator_left_shift(Rank<sizeof...(As)>(), os_, al_);

        return os_;    
    }
    
    
    template <uint16_t R, typename... As>
    void _operator_left_shift(Rank<R>, std::ostream& os_, const gd::Alternative<As...>& al_) noexcept
    {
        if(R-1==al_.number()){
            
            gd::ostream(al_.template path<R-1>(), os_);
            os_<<" ";

        }else{
            _operator_left_shift(Rank<uint16_t(R-1)>{ }, os_, al_);
        }

        return;
    }
    
    
    template <typename... As>
    void _operator_left_shift(Rank<0>, std::ostream& os_, const gd::Alternative<As...>& al_) noexcept
    {
        return;
    }


    template <typename... As>
    std::ostream& operator<<(std::ostream& os_, const gd::ElasticAlternative<As...>& al_) noexcept
    {
        _operator_left_shift(Rank<sizeof...(As)>{ }, os_, al_);

        return os_;    
    }
    
    
    template <uint16_t R, typename... As>
    void _operator_left_shift(Rank<R>, std::ostream& os_, const gd::ElasticAlternative<As...>& al_) noexcept
    {
        if(R-1==al_.number()){
            
            gd::ostream(al_.template path<R-1>(), os_);
            os_<<" ";

        }else{
            _operator_left_shift(Rank<uint16_t(R-1)>{ }, os_, al_);
        }

        return;
    }
    
    
    template <typename... As>
    void _operator_left_shift(Rank<0>, std::ostream& os_, const gd::ElasticAlternative<As...>& al_) noexcept
    {
        return;
    }
}
