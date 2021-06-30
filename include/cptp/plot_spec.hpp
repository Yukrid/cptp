#ifndef CPTP_PLOT_SPEC_HPP
#define CPTP_PLOT_SPEC_HPP

#include "forward.hpp"
#include "color.hpp"
#include "line.hpp"
#include "point.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    cptp::PlotSpec Structure    )//
    //-> forward.hpp plot_spec.hpp plot_spec.cpp
    struct PlotSpec{

        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        std::string tag;
        Color       color;
        Line        line;
        Point       point;
        std::string option;
       

        //+     Member Function    +//
        //_ Constructor
                  PlotSpec    (void)                                                                                                   =default;
                  PlotSpec    (const PlotSpec&)                                                                                        =default;
                  PlotSpec    (PlotSpec&&)                                                                                             =default;
                  PlotSpec    (const std::string&, Color =Color(), const Line& =Line(), const Point& =Point(), const std::string& ="") noexcept;
        PlotSpec& construct   (void)                                                                                                   noexcept;
        PlotSpec& construct   (const std::string&, Color =Color(), const Line& =Line(), const Point& =Point(), const std::string& ="") noexcept;
        PlotSpec& reconstruct (const std::string&, Color =Color(), const Line& =Line(), const Point& =Point(), const std::string& ="") noexcept;

        //_ Destructor
                  ~PlotSpec (void) =default;
        PlotSpec& destruct  (void) noexcept;

        //_ Writer
        void info (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;
        
        //_ Constant Function
        size_t _memory (void) const noexcept;

        //_ Binary Operator
        PlotSpec& operator= (const PlotSpec&) =default;
        PlotSpec& operator= (PlotSpec&&)      =default;
    };


    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    using PlotSpecArray=gd::ElasticList<PlotSpec>;
}
#endif
