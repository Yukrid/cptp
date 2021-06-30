#ifndef CPTP_LABEL_HPP
#define CPTP_LABEL_HPP

#include "forward.hpp"
#include "vec2.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    cptp::Label Structure    )//
    //-> forward.hpp label.hpp label.cpp
    struct Label{
    
        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        std::string string;
        double      point;
       

        //+     Member Function    +//
        //_ Constructor
               Label       (void)                             noexcept;
               Label       (const Label&)                     =default;
               Label       (Label&&)                          =default;
               Label       (const std::string&, double =10.0) noexcept;
        Label& construct   (void)                             noexcept;
        Label& construct   (const std::string&, double =10.0) noexcept;
        Label& reconstruct (const std::string&, double =10.0) noexcept;

        //_ Destructor
               ~Label   (void) =default;
        Label& destruct (void) noexcept;

        //_ Writer
        void info  (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;
        
        //_ Constant Function
        size_t _memory(void) const noexcept;

        //_ Binary Operator
        Label& operator= (const Label&) =default;
        Label& operator= (Label&&)      =default;
        
    };
 


    //(    cptp::Label2D Structure    )//
    //-> forward.hpp label.hpp label.cpp
    struct Label2D{
    
        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        bool  enable;
        Label x;
        Label y;
        Vec2  margin;

        //+     Member Function    +//
        //_ Constructor
                 Label2D     (void)                                                                                      noexcept;
                 Label2D     (const Label2D&)                                                                            =default;
                 Label2D     (Label2D&&)                                                                                 =default;
                 Label2D     (bool, const Label& =Label("$x$"), const Label& =Label("$y$"), const Vec2& =Vec2(0.2, 0.2)) noexcept;
        Label2D& construct   (void)                                                                                      noexcept;
        Label2D& construct   (bool, const Label& =Label("$x$"), const Label& =Label("$y$"), const Vec2& =Vec2(0.2, 0.2)) noexcept;
        Label2D& reconstruct (bool, const Label& =Label("$x$"), const Label& =Label("$y$"), const Vec2& =Vec2(0.2, 0.2)) noexcept;
        

        //_ Destructor
                 ~Label2D (void) =default;
        Label2D& destruct (void) noexcept;

        //_ Writer
        void info  (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;
        
        //_ Constant Function
        size_t _memory(void) const noexcept;

        //_ Binary Operator
        Label2D& operator= (const Label2D&) =default;
        Label2D& operator= (Label2D&&)      =default;
        
    };
   
}

#endif
