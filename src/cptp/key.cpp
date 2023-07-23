#include <cptp/key.hpp>

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{
    
    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    cptp::Key Relocatable Structure    )//
    //+     Member Function    +//
    //_ Constructor
    Key::Key(void) noexcept
        : enable   (true)
        , position ( )
        , point    (8.0)
        , margin   (0.10)
        , interval (0.05)
    {
        return;
    }


    Key::Key(bool e_, const Position& pos_, float pt_, float mar_, float in_) noexcept
        : enable   (e_)
        , position (pos_)
        , point    (pt_)
        , margin   (mar_)
        , interval (in_)
    {
        return;
    }


    Key& Key::construct(bool e_, const Position& pos_, float pt_, float mar_, float in_) noexcept
    {
        new(this) Key(e_, pos_, pt_, mar_, in_);

        return *this;
    }



    //_ Writer
    void Key::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {    

        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
    
        os_<<str<<"[cptp::Key Relocatable Structure]"<<std::endl;
        os_<<str<<"(size)    : "<<sizeof(Key)<<std::endl;
        os_<<str<<"(name)    : "<<typeid(Key).name()<<std::endl;
        os_<<str<<"(address) : "<<this<<std::endl;
        os_<<str<<"(memory)  : "<<0<<std::endl;
        os_<<str<<"Enable    : "<<(enable ? "true" : "false")<<std::endl;
        os_<<str<<"Position  : "<<std::endl;
        position.info(os_, offset_+1);
        os_<<str<<"Point     : "<<point<<std::endl;
        os_<<str<<"Margin    : "<<margin<<std::endl;
        os_<<str<<"Interval  : "<<interval<<std::endl;

        return;
    }

}
