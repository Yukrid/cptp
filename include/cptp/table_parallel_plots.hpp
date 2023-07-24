#ifndef CPTP_TABLE_PARALLEL_PLOTS_HPP
#define CPTP_TABLE_PARALLEL_PLOTS_HPP

#include <cmath>
#include <fstream>
#include "forward.hpp"
#include "figure.hpp"
#include "scale.hpp"
#include "key.hpp"
#include "label.hpp"
#include "range.hpp"
#include "title.hpp"
#include "data.hpp"
#include "plot_spec.hpp"
#include "function.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    cptp::TabParPlots Class Template    )//
    //-> forward.hpp table_parallel_plots.hpp table_parallel_plots.inl
    struct TabParPlots{

        //+    Member Variable    +//
        //->    Isolated Variable    <-//
        public:
        Figure         figure;
        Label2D        label;
        Scale2D        scale;
        Key            key;
        Range2D        range;
        private:
        public:
        PlotSpecArray _plot_spec_array;
        //->    PlotSet Family    <-//
        private:
        public:
        uint16_t      _n;
        uint16_t      _m;
        uint16_t      _p;
        TitleSet      _title_set;
        DataSet       _data_set;
        

        //+     Member Function    +//
        public:
        //_ Constructor
                     TabParPlots (const TabParPlots&)           =default;
                     TabParPlots (TabParPlots&&)                =default;
                     TabParPlots (uint16_t, uint16_t, uint16_t) noexcept;
        TabParPlots& construct   (uint16_t, uint16_t, uint16_t) noexcept;
        TabParPlots& reconstruct (uint16_t, uint16_t, uint16_t) noexcept;

        //_ Destructor
                     ~TabParPlots (void) =default;
        TabParPlots&  destruct    (void) noexcept;

        //_ Accessor
        Title&       title     (uint16_t, uint16_t) noexcept;
        Data2DArray& data      (uint16_t, uint16_t) noexcept;
        PlotSpec&    plot_spec (uint16_t)           noexcept;

        //_ Writer
        void info (std::ostream& =std::cout, uint_fast8_t offset_ =0) const noexcept;

        //_ Variable Function
        void setPlotSpec       (uint16_t, const PlotSpec&)                                                      noexcept;
        void setDatas          (uint16_t, uint16_t, const Data2DArray&, const Title& =Title())                  noexcept;
        void outputPlot        (const std::string&)                                                             noexcept;
        void _writeInitialCode (std::ofstream&, Vec2&, Vec2&)                                                   noexcept;
        int  _decideRange      (void)                                                                           noexcept;
        void _drawBox          (const Vec2&, std::ofstream&, Vec2&)                                             noexcept;
        void _drawScale        (std::ofstream&, Vec2&, Range2D&)                                                noexcept;
        void _drawLabel        (std::ofstream&)                                                                 noexcept;
        void _drawPlot         (const Vec2&, const Range2D&, std::ofstream&, gd::List<gd::Group<uint32_t, 4>>&) noexcept;
        void _drawKey          (const gd::List<gd::Group<uint32_t, 4>>&, std::ofstream&, uint32_t[2])           noexcept;
        void _drawTitle        (const gd::List<gd::Group<uint32_t, 4>>&, const uint32_t[2], std::ofstream&)     noexcept;
        void _writeFinalCode   (std::ofstream&)                                                                 noexcept;

        //_ Constant Function
        size_t _memory (void) const noexcept;

        //_ Binary Operator
        TabParPlots& operator= (const TabParPlots&) =default;
        TabParPlots& operator= (TabParPlots&&)      =default;
    };

}

#endif
