#ifndef CPTP_SINGLE_PLOTS_HPP
#define CPTP_SINGLE_PLOTS_HPP

#include "forward.hpp"
#include "figure.hpp"
#include "scale.hpp"
#include "title.hpp"
#include "forward.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    cptp::SinglePlots Class    )//
    //-> forward.hpp plots.hpp plots.inl plots.cpp
    struct SinglePlots{
 
        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        Vec2    range;
        double  ratio;
        bool    grid;
        TypeArg arg;


        //+     Member Function    +//
        //_ Constructor
               SinglePlots (void)          noexcept;
               SinglePlots (const SinglePlots&) =default;
               SinglePlots (SinglePlots&&)      =default;
    
        //_ Destructor
        ~SinglePlots (void) =default;

        //_ Writer
        void info  (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;
        void print (std::ostream& =std::cout)                          const noexcept;
   
        //_ Variable Function
        inline void setDecimal   (double =1.)                                                       noexcept;
        inline void setLogarithm (double =10.)                                                      noexcept;
        inline void setAnyParam  (double =std::numbers::pi_v<scalar>, const std::string& ="$\\pi$") noexcept;
     
        //_ Constant Function
        size_t _memory (void) const noexcept;
   
        //_ Binary Operator
        SinglePlots& operator= (const SinglePlots&) =default;
        SinglePlots& operator= (SinglePlots&&)      =default;
        
    };



    //(    cptp::SinglePlots2D Structure    )//
    //-> forward.hpp plots.hpp plots.inl plots.cpp
    struct SinglePlots2D{
    
        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        SinglePlots x;
        SinglePlots y;

        //+     Member Function    +//
        //_ Constructor
        SinglePlots2D (void)           noexcept;
        SinglePlots2D (const SinglePlots2D&) =default;
        SinglePlots2D (SinglePlots2D&&)      =default;

        //_ Destructor
        ~SinglePlots2D (void) =default;

        //_ Writer
        void info  (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;
        void print (std::ostream& =std::cout)                          const noexcept;
        
        //_ Constant Function
        size_t _memory(void) const noexcept;

        //_ Binary Operator
        SinglePlots2D& operator= (const SinglePlots2D&) =default;
        SinglePlots2D& operator= (SinglePlots2D&&)      =default;
        
    };

}

#include "plots.inl"

#endif
