#include <cptp/table_parallel_plots.hpp>

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{
    
    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    cptp::TabParPlots Strcuture   )//
    //-> forward.hpp table_parallel_plots.hpp plot_spec.cpp
    //_ Constructor
    TabParPlots::TabParPlots(uint16_t n_, uint16_t m_, uint16_t p_) noexcept
        :  figure          ( )
        ,  label           ( )
        ,  scale           ( )
        ,  key             ( )
        ,  range           ( )
        , _plot_spec_array ( )
        , _n               (n_)
        , _m               (m_)
        , _p               (p_)
        , _title_set       ( )
        , _data_set        ( )
    {
        _plot_spec_array.resize(p_);
        _title_set.resize(n_*m_);
        _data_set.resize(n_*m_);
    
        return;
    }


    TabParPlots& TabParPlots::construct(uint16_t n_, uint16_t m_, uint16_t p_) noexcept
    {
        new(this) TabParPlots(n_, m_, p_);
        
        return *this;
    }
 

    TabParPlots& TabParPlots::reconstruct(uint16_t n_, uint16_t m_, uint16_t p_) noexcept
    {
        this->~TabParPlots();
        new(this) TabParPlots(n_, m_, p_);
        
        return *this;
    }



    //_ Destructor
    TabParPlots& TabParPlots::destruct (void) noexcept
    {
        this->~TabParPlots();

        return *this;
    }



    //_ Accessor
    Title& TabParPlots::title(uint16_t n_, uint16_t m_) noexcept
    {
        return _title_set[n_*_m+m_];
    }



    Data2DArray& TabParPlots::data(uint16_t n_, uint16_t m_) noexcept
    {
        return _data_set[n_*_m+m_];
    }



    PlotSpec& TabParPlots::plot_spec(uint16_t p_) noexcept
    {
        return _plot_spec_array[p_];
    }


    
    //_ Writer
    void TabParPlots::info(std::ostream& os_, uint_fast8_t offset_) const noexcept
    {
        std::string str;
        for(uint_fast8_t a=0; a<offset_; ++a) str+="  ";
        
        os_<<str<<"[cptp::TabParPlots Class Template]"<<std::endl;
        os_<<str<<"(size)                   : "<<sizeof(TabParPlots)<<std::endl;
        os_<<str<<"(name)                   : "<<typeid(TabParPlots).name()<<std::endl;
        os_<<str<<"(address)                : "<<this<<std::endl;
        os_<<str<<"(memory)                 : "<<_memory()<<std::endl;
        os_<<str<<"Figure                   : "<<std::endl;
        figure.info(os_, offset_+1);
        os_<<str<<"Label                    : "<<std::endl;
        label.info(os_, offset_+1);
        os_<<str<<"Scale                    : "<<std::endl;
        scale.info(os_, offset_+1);
        os_<<str<<"Key                      : "<<std::endl;
        key.info(os_, offset_+1);
        os_<<str<<"Range                    : "<<std::endl;
        range.info(os_, offset_+1);
        os_<<str<<"Plot Specification Array : "<<std::endl;
        if(_plot_spec_array.size()>0){
            os_<<str<<"First Plot Specification : "<<std::endl;
            _plot_spec_array[0].info(os_, offset_+1);
            if(_plot_spec_array.size()>=2){
                os_<<str<<"Last Plot Specification  : "<<std::endl;
                _plot_spec_array[_plot_spec_array.size()-1].info(os_, offset_+1);
            }
        }
        os_<<str<<"N                        : "<<_n<<std::endl;
        os_<<str<<"M                        : "<<_m<<std::endl;
        os_<<str<<"P                        : "<<_p<<std::endl;
        os_<<str<<"Title Set                : "<<std::endl;
        if(_title_set.size()>0){
            os_<<str<<"First Title              : "<<std::endl;
            _title_set[0].info(os_, offset_+1);
            if(_title_set.size()>=2){
        os_<<str<<"Last Title               : "<<std::endl;
                _title_set[_title_set.size()-1].info(os_, offset_+1);
            }
        }
        os_<<str<<"Data Set                 : "<<std::endl;

        return;
    }
     


    //_ Variable Function
    void TabParPlots::setPlotSpec(uint16_t p_, const PlotSpec& ps_) noexcept
    {   
        _plot_spec_array[p_]=ps_;
        
        return;
    }
 
    
    void TabParPlots::setDatas(uint16_t n_, uint16_t m_, const Data2DArray& ds_, const Title& tit_) noexcept
    {
        _title_set[n_*_m+m_]=tit_;
        _data_set [n_*_m+m_]=ds_;

        return;
    }
     

    void TabParPlots::outputPlot(const std::string& str_) noexcept
    {
        std::ofstream ofs(str_);
        Vec2 figure;
        Vec2 cammpus;
        Vec2 scaler;
        uint32_t key_nmpos[2];
        Range2D r2d;
        gd::List<gd::Group<uint32_t, 4>> cofs;

        cofs.resize(_n*_m);
        cofs.memset(0);
        
        _writeInitialCode(ofs, figure, cammpus);
        if(_decideRange()){
            std::cerr<<"Range error"<<std::endl;
            return;
        }
        _drawBox(figure, ofs, scaler);
        r2d=range;
        _drawScale(ofs, scaler, r2d);
        if(label.enable) _drawLabel(ofs);
        _drawPlot(scaler, r2d, ofs, cofs);
        if(key.enable) _drawKey(cofs, ofs, key_nmpos);
        _drawTitle(cofs, key_nmpos, ofs);
        _writeFinalCode(ofs);

        return;
    }

    
    void TabParPlots::_writeInitialCode(std::ofstream& output_, Vec2& fig, Vec2& camp) noexcept
    {
        switch(figure.size.number()){
            case Figure::CAMMPUS:
                camp=figure.size.path<Figure::CAMMPUS>();
                break;
            case Figure::PLOT_AREA:
                camp.x=figure.size.path<Figure::PLOT_AREA>().x*_n+pointToCenti(label.y.point+scale.y.point*3.)*1.1+label.margin.x+figure.margin.x*2.+0.2;
                camp.y=figure.size.path<Figure::PLOT_AREA>().y*_m+pointToCenti(label.x.point+label.x.point   )*1.1+label.margin.y+figure.margin.y*2.+0.2;
                break;
        } 
        fig=camp-0.1;
 
        output_<<"\\documentclass[dvipdfmx, 10pt]{beamer}"<<std::endl;
        output_<<"\\usefonttheme{serif}"<<std::endl;
        output_<<"\\setbeamertemplate{navigation symbols}{}"<<std::endl;
        output_<<std::endl;
        output_<<"\\setlength{\\paperwidth}{"<<camp.x<<"cm}"<<std::endl;
        output_<<"\\setlength{\\paperheight}{"<<camp.y<<"cm}"<<std::endl;
            output_<<"\\setlength{\\topmargin}{0cm}"<<std::endl;
        output_<<"\\setlength{\\oddsidemargin}{0cm}"<<std::endl;
        output_<<"\\setlength{\\hoffset}{-2.5cm}"<<std::endl;
        output_<<"\\setlength{\\voffset}{-2.5cm}"<<std::endl;
        output_<<"\\setlength{\\textwidth}{"<<fig.x<<"cm}"<<std::endl;
        output_<<"\\setlength{\\textheight}{"<<fig.y<<"cm}"<<std::endl;
        output_<<"\\setlength{\\headsep}{0cm}"<<std::endl;
        output_<<"\\setlength{\\headheight}{0cm}"<<std::endl;
        output_<<"\\setlength{\\marginparsep}{0cm}"<<std::endl;
        output_<<"\\setlength{\\marginparwidth}{0cm}"<<std::endl;
        output_<<"\\setlength{\\footskip}{0cm}"<<std::endl;
        output_<<"\\setlength{\\footheight}{0cm}"<<std::endl;
        output_<<std::endl;
        output_<<"\\usepackage{graphicx}"<<std::endl;
        output_<<"\\usepackage{tikz}"<<std::endl;
        output_<<"\\usetikzlibrary{calc}"<<std::endl;
        output_<<"\\usepackage{here}"<<std::endl;
        output_<<std::endl;
        output_<<"\\begin{document}"<<std::endl;
        output_<<"\\begin{figure}[H]"<<std::endl;
        output_<<"\\centering"<<std::endl;
        output_<<"\\begin{tikzpicture}"<<std::endl;
    
        return;
    }


    int TabParPlots::_decideRange(void) noexcept
    {
        scalar f_max=+std::numeric_limits<scalar>::max();
        scalar f_min=-std::numeric_limits<scalar>::max();
        
        scalar xmin = range.x.min;
        scalar xmax = range.x.max;
        scalar ymin = range.y.min;
        scalar ymax = range.y.max;

        if((range.x.min==f_max || range.x.max==f_min) or (ymin!=f_max || ymax!=f_min)){

            scalar tx_min=f_max;
            scalar tx_max=f_min;
            if(ymin==f_max) ymin=f_min;
            if(ymax==f_min) ymax=f_max;
            for(auto& data_array : _data_set.range()){
                for(auto& d2 : data_array.range()){
                    for(size_t a=0; a<d2.datas().path<0>().size(); ++a){
                        if(d2.skipper().find(a)==d2.skipper().end()){
                            auto& x = d2.datas().path<0>()[a];
                            auto& y = d2.datas().path<1>()[a];
                            if(tx_min>x and ymin <= y and y <= ymax) tx_min=x;
                            if(tx_max<x and ymin <= y and y <= ymax) tx_max=x;
                        }
                    }
                }
            }
            if(range.x.min==f_max) range.x.min=tx_min;
            if(range.x.max==f_min) range.x.max=tx_max;
        }

        if((range.y.min==f_max || range.y.max==f_min) or (xmin!=f_max || xmax!=f_min)){

            scalar ty_min=f_max;
            scalar ty_max=f_min;
            if(xmin==f_max) xmin=f_min;
            if(xmax==f_min) xmax=f_max;
            for(auto& data_array : _data_set.range()){
                for(auto& d2 : data_array.range()){
                    for(size_t a=0; a<d2.datas().path<1>().size(); ++a){
                        if(d2.skipper().find(a)==d2.skipper().end()){
                            auto& x = d2.datas().path<0>()[a];
                            auto& y = d2.datas().path<1>()[a];
                            if(ty_min>y and xmin <= x and x <= xmax) ty_min=y;
                            if(ty_max<y and xmin <= x and x <= xmax) ty_max=y;
                        }
                    }
                }
            }
            if(range.y.min==f_max) range.y.min=ty_min;
            if(range.y.max==f_min) range.y.max=ty_max;
        }
        
        if(range.x.min < range.x.max and range.x.min < range.x.max) return 0;
        else                                                        return -1;
    }


    void TabParPlots::_drawBox(const Vec2& fig_, std::ofstream& output_, Vec2& scaler_) noexcept
    {
        Vec2 region, base;
        region.x=fig_.x-pointToCenti(label.y.point+scale.y.point*3.)*1.1-label.margin.x-figure.margin.x*2.-0.1;
        region.y=fig_.y-pointToCenti(label.x.point+scale.x.point+label.y.point)*1.1-label.margin.y-figure.margin.y*2.-0.1;
        region.x/=static_cast<scalar>(_n);
        region.y/=static_cast<scalar>(_m);
        base.x=pointToCenti(label.y.point+scale.y.point*3.)*1.1+label.margin.x+figure.margin.x+0.05;
        base.y=pointToCenti(label.x.point+scale.x.point   )*1.1+label.margin.y+figure.margin.y+0.05;
        
        output_<<std::endl<<"% Box"<<std::endl;
        output_<<"\\coordinate (BOX_REGION) at ("<<region.x<<","<<region.y<<");"<<std::endl;
        output_<<"\\coordinate (BOX_REGION_X) at ("<<region.x<<","<<0<<");"<<std::endl;
        output_<<"\\coordinate (BOX_REGION_Y) at ("<<0<<","<<region.y<<");"<<std::endl;
        for(uint_fast16_t n=0; n<_n; ++n){
            for(uint_fast16_t m=0; m<_m; ++m){
                if(n==0 && m==0){
                    output_<<"\\coordinate (BOX_LB_"<<n<<"_"<<m<<") at ("<<base.x<<","<<base.y<<");"<<std::endl;
                    output_<<"\\coordinate (BOX_RT_"<<n<<"_"<<m<<") at ($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION)$);"<<std::endl;
                    output_<<"\\draw[very thick] (BOX_LB_"<<n<<"_"<<m<<") rectangle (BOX_RT_"<<n<<"_"<<m<<");"<<std::endl;
                }
                output_<<"\\coordinate (BOX_LB_"<<n<<"_"<<m<<") at ($(BOX_LB_"<<0<<"_"<<0<<")+"<<n<<"*(BOX_REGION_X)+"<<m<<"*(BOX_REGION_Y)$);"<<std::endl;
                output_<<"\\coordinate (BOX_RT_"<<n<<"_"<<m<<") at ($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION)$);"<<std::endl;
                output_<<"\\draw[very thick] (BOX_LB_"<<n<<"_"<<m<<") rectangle (BOX_RT_"<<n<<"_"<<m<<");"<<std::endl;
            }
        }

        output_<<"\\fill[opacity=0] (0.05,0.05) rectangle ("<<figure.margin.x<<","<<figure.margin.y<<");"<<std::endl;
        output_<<"\\fill[opacity=0] (BOX_RT_"<<_n-1<<"_"<<_m-1<<") rectangle ("<<fig_.x-0.05<<","<<fig_.y-0.05<<");"<<std::endl;
        
        scaler_.x=region.x/(range.x.max-range.x.min);
        scaler_.y=region.y/(range.y.max-range.y.min);

        return;
    }


    void TabParPlots::_drawScale(std::ofstream& output_, Vec2& sca_, Range2D& r2d_) noexcept
    {
        switch(scale.x.arg.number()){
            
            case Scale::DECIMAL:
            {
                gd::List<scalar>             scale_values;
                gd::ElasticList<std::string> scale_strs;
                gd::List<bool>               scale_bar_flag;

                scalar width=range.x.max-range.x.min;
                scalar  exp  =1;
                int32_t count=0;
                if(width<=3.0) while(width<=3.0){ width*=10.;  exp*=10.;  --count; }
                if(width>29.0) while(width>29.0){ width*=0.1;  exp*=0.1;  ++count; }
                int32_t min_i=static_cast<int32_t>(range.x.min*exp);
                int32_t max_i=static_cast<int32_t>(range.x.max*exp);
                scalar arg  =scale.x.arg.path<Scale::DECIMAL>();
                if(arg<range.x.min || range.x.max<arg){
                    arg=(static_cast<scalar>(min_i)+1)/exp;
                }
                uint32_t interval=scale.x.interval==0 ? scaleInterval(max_i-min_i) : scale.x.interval*exp;
                if(interval == 0){
                    std::cerr<<"error: invalid scale interval"<<std::endl;
                    std::exit(EXIT_FAILURE);
                }
                gd::List<scalar> rev_sv;
                for(scalar a=arg-interval/exp; a>=range.x.min; a-=interval/exp){
                    rev_sv.pushBack(static_cast<scalar>(a));
                }
                for(size_t a=rev_sv.size(); a>0; --a){
                    scale_values.pushBack(rev_sv[a-1]);
                }

                for(scalar a=arg; a<=range.x.max; a+=interval/exp){
                    scale_values.pushBack(static_cast<scalar>(a));
                }
                
                if(0.0005<exp && exp<5000.){
                    for(const scalar& sv : scale_values.range()){
                        std::stringstream ss1;
                        std::string       str1;
                        ss1<<sv;
                        ss1>>str1;
                        if(str1.length()>5){
                           str1=str1.substr(0,5); 
                        }
                        scale_strs.pushBack(std::move(str1));
                    }
                }else{
                    for(const scalar& sv : scale_values.range()){
                        std::stringstream ss1;
                        std::string       str1;
                        ss1<<sv*exp;
                        ss1>>str1;
                        if(str1.length()>5){
                           str1=str1.substr(0,5); 
                        }
                        scale_strs.pushBack(std::move(str1));
                    }
                    output_<<"\\draw ($(BOX_LB_"<<_n-1<<"_"<<0<<")+(BOX_REGION_X)-(0,"<<pointToCenti(scale.x.point)*1.5<<")$) node[below] {\\fontsize{"<<scale.x.point<<"pt}{0pt}\\selectfont $\\times 10^{"<<count<<"}$};"<<std::endl;
                }
                {
                    output_<<std::endl<<"% X Scale"<<std::endl;
                    output_<<"\\coordinate (X_SCALE_LENGTH) at (0,"<<scale.x.length<<");"<<std::endl;
                    for(size_t a=0; a<scale_values.size(); ++a){
                        scale_values[a]=sca_.x*(scale_values[a]-range.x.min);
                        output_<<"\\coordinate (X_SCALE_"<<a<<") at ("<<scale_values[a]<<","<<0<<");"<<std::endl;
                    }
        
                    size_t max_leng=0;
                    for(const std::string& ss : scale_strs.range()){
                        size_t sz=ss.length();
                        if(sz>max_leng) max_leng=sz;
                    }
                    
                    size_t period=0;
                    scalar zero=scale_values[0];
                    for(const scalar& sv : scale_values.range(1)){
                        scalar deff=(sv-pointToCenti(scale.x.point*(static_cast<float>(max_leng)*0.5)))-(zero+pointToCenti(scale.x.point*(static_cast<float>(max_leng)*0.5)));
                        ++period;
                        if(deff>=pointToCenti(scale.x.point)) break;
                    }
    
                    for(uint_fast16_t n=0; n<_n; ++n){
                        for(size_t a=0; a<scale_strs.size(); ++a){
                            if(a%period){
                                scale_bar_flag.pushBack(false);
                            }else{
                                if(a==scale_strs.size()-1 && n!=_n-1){
                                    float right=scale_values[a-period]+pointToCenti(scale.x.point*(static_cast<float>(max_leng)*0.5));
                                    float left =sca_.x*(range.x.max-range.x.min)+scale_values[0]-pointToCenti(scale.x.point*(static_cast<float>(max_leng)*0.5));
                                    if(left-right>=pointToCenti(scale.x.point*0.5)){
                                        output_<<"\\draw ($(BOX_LB_"<<n<<"_"<<0<<")+(X_SCALE_"<<a<<")$) node[below] {\\fontsize{"<<scale.x.point<<"pt}{0pt}\\selectfont "<<scale_strs[a]<<"};"<<std::endl;
                                    }
                                }else{
                                    output_<<"\\draw ($(BOX_LB_"<<n<<"_"<<0<<")+(X_SCALE_"<<a<<")$) node[below] {\\fontsize{"<<scale.x.point<<"pt}{0pt}\\selectfont "<<scale_strs[a]<<"};"<<std::endl;
                                }
                                scale_bar_flag.pushBack(true);
                            }
                        }
                        for(uint_fast16_t m=0; m<_m; ++m){
                            for(size_t a=0; a<scale_values.size(); ++a){
                                if(scale_bar_flag[a]){
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(X_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(X_SCALE_"<<a<<")+(X_SCALE_LENGTH)$);"<<std::endl;
                                }else{
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(X_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(X_SCALE_"<<a<<")+0.5*(X_SCALE_LENGTH)$);"<<std::endl;
                                }
                            }
                            for(size_t a=0; a<scale_values.size(); ++a){
                                if(scale_bar_flag[a]){
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_Y)+(X_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_Y)+(X_SCALE_"<<a<<")-(X_SCALE_LENGTH)$);"<<std::endl;
                                }else{
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_Y)+(X_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_Y)+(X_SCALE_"<<a<<")-0.5*(X_SCALE_LENGTH)$);"<<std::endl;
                                }
                            }
                        }
                    }
                }
                break;
            }
            case Scale::LOG:
            {
                /*
                bool negative_enable=false;
                if(r2d_.x.max<0.){
                    negative_enable=true;
                    r2d_.x.min=-range.x.max;
                    r2d_.x.max=-range.x.min;
                }else if(r2d_.x.min<=0 or r2d_.x.max==0.){
                    std::cout<<range.x.min<<" "<<range.x.max<<std::endl;
                    scale.x.arg.construct(Scale::DECIMAL, 0.);
                    goto INVARID_LOG_SCALE;
                }*/
                if(range.x.min<=0){
                    std::cerr<<"Invarid range at log scale."<<std::endl;
                    std::exit(EXIT_FAILURE);
                }


                gd::List<scalar>             scale_values;
                gd::ElasticList<std::string> scale_strs;
                gd::List<bool>               scale_bar_flag;
                scalar arg  =scale.x.arg.path<Scale::LOG>().path<0>();
                
                int32_t min_e=0;
                int32_t max_e=0;
                while(r2d_.x.min< std::pow(arg, min_e)){ --min_e; };
                while(r2d_.x.min> std::pow(arg, min_e)){ ++min_e; };
                while(r2d_.x.max< std::pow(arg, max_e)){ --max_e; };
                while(r2d_.x.max> std::pow(arg, max_e)){ ++max_e; };
                uint32_t interval=scale.x.interval==0 ? scaleInterval(max_e-min_e) : scale.x.interval;
                
                r2d_.x.min=std::log(r2d_.x.min)/std::log(arg);
                r2d_.x.max=std::log(r2d_.x.max)/std::log(arg);
                sca_.x=sca_.x*(range.x.max-range.x.min)/(r2d_.x.max-r2d_.x.min);
                for(int32_t a=min_e; a<max_e; a+=interval){
                    scale_values.pushBack(a);
                }


                std::string base;
                if(scale.x.arg.path<Scale::LOG>().path<1>()==""){
                    std::stringstream ss1;
                    ss1<<arg;
                    ss1>>base;
                }else{
                    base=scale.x.arg.path<Scale::LOG>().path<1>();
                }
                
                for(const scalar& sv : scale_values.range()){
                    std::string expo;
                    std::stringstream ss1;
                    ss1<<sv;
                    ss1>>expo;
                    scale_strs.pushBack(std::string("$")+base+"^{"+expo+"}$");
                }
                
                {
                    output_<<std::endl<<"% X Scale"<<std::endl;
                    output_<<"\\coordinate (X_SCALE_LENGTH) at (0,"<<scale.x.length<<");"<<std::endl;
                    for(size_t a=0; a<scale_values.size(); ++a){
                        scale_values[a]=sca_.x*(scale_values[a]-r2d_.x.min);
                        output_<<"\\coordinate (X_SCALE_"<<a<<") at ("<<scale_values[a]<<","<<0<<");"<<std::endl;
                    }
        
                    size_t max_leng=0;
                    for(const std::string& ss : scale_strs.range()){
                        size_t sz=mathStrWidth(ss)/2;
                        if(sz>max_leng) max_leng=sz;
                    }
                    
                    size_t period=0;
                    scalar zero=scale_values[0];
                    for(const scalar& sv : scale_values.range(1)){
                        scalar deff=(sv-pointToCenti(scale.x.point*(static_cast<float>(max_leng)*0.5)))-(zero+pointToCenti(scale.x.point*(static_cast<float>(max_leng)*0.5)));
                        ++period;
                        if(deff>=pointToCenti(scale.x.point)) break;
                    }
    
                    for(uint_fast16_t n=0; n<_n; ++n){
                        for(size_t a=0; a<scale_strs.size(); ++a){
                            if(a%period){
                                scale_bar_flag.pushBack(false);
                            }else{
                                if(a==scale_strs.size()-1 && n!=_n-1){
                                    float right=scale_values[a-period]+pointToCenti(scale.x.point*(static_cast<float>(max_leng)*0.5));
                                    float left =sca_.x*(r2d_.x.max-r2d_.x.min)+scale_values[0]-pointToCenti(scale.x.point*(static_cast<float>(max_leng)*0.5));
                                    if(left-right>=pointToCenti(scale.x.point*0.5)){
                                        output_<<"\\draw ($(BOX_LB_"<<n<<"_"<<0<<")+(X_SCALE_"<<a<<")$) node[below] {\\fontsize{"<<scale.x.point<<"pt}{0pt}\\selectfont "<<scale_strs[a]<<"};"<<std::endl;
                                    }
                                }else{
                                    output_<<"\\draw ($(BOX_LB_"<<n<<"_"<<0<<")+(X_SCALE_"<<a<<")$) node[below] {\\fontsize{"<<scale.x.point<<"pt}{0pt}\\selectfont "<<scale_strs[a]<<"};"<<std::endl;
                                }
                                scale_bar_flag.pushBack(true);
                            }
                        }
                        for(uint_fast16_t m=0; m<_m; ++m){
                            for(size_t a=0; a<scale_values.size(); ++a){
                                if(scale_bar_flag[a]){
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(X_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(X_SCALE_"<<a<<")+(X_SCALE_LENGTH)$);"<<std::endl;
                                }else{
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(X_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(X_SCALE_"<<a<<")+0.5*(X_SCALE_LENGTH)$);"<<std::endl;
                                }
                            }
                            for(size_t a=0; a<scale_values.size(); ++a){
                                if(scale_bar_flag[a]){
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_Y)+(X_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_Y)+(X_SCALE_"<<a<<")-(X_SCALE_LENGTH)$);"<<std::endl;
                                }else{
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_Y)+(X_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_Y)+(X_SCALE_"<<a<<")-0.5*(X_SCALE_LENGTH)$);"<<std::endl;
                                }
                            }
                        }
                    }
                }
                break;
            }
            case Scale::ANY:
            {
                gd::List<scalar>             scale_values;
                gd::ElasticList<std::string> scale_strs;
                gd::List<bool>               scale_bar_flag;
                std::cerr<<"Any scale is no yet been implemented."<<std::endl;
                /*scalar arg   =scale.x.arg.path<Scale::ANY>();
                scalar width=(range.x.max-range.x.min)/arg;
                int32_t denom=1;
                if(width<=3.0){
                    while(width<=3.0){
                        width/=denom;
                        ++denom;
                    }
                }else{
                    while(width>10.0){
                        width*=denom;
                        ++denom;
                    }
                    denom=-denom;
                }*/
                /*
                int32_t min_i=static_cast<int32_t>(range.x.min*exp);
                int32_t max_i=static_cast<int32_t>(range.x.max*exp);
                if(arg<range.x.min || range.x.max<arg){
                    arg=(static_cast<scalar>(min_i)+1)/exp;
                }
                uint32_t interval=scale.x.interval==0 ? scaleInterval(max_i-min_i) : scale.x.interval;
                gd::List<scalar> rev_sv;
                for(scalar a=arg-interval/exp; a>=range.x.min; a-=interval/exp){
                    rev_sv.pushBack(static_cast<scalar>(a));
                }
                for(size_t a=rev_sv.size(); a>0; --a){
                    scale_values.pushBack(rev_sv[a-1]);
                }

                for(scalar a=arg; a<=range.x.max; a+=interval/exp){
                    scale_values.pushBack(static_cast<scalar>(a));
                }
                std::cout<<"SV:"<<scale_values<<" "<<min_i<<" "<<exp<<std::endl;
                
                if(0.0005<exp && exp<5000.){
                    for(const scalar& sv : scale_values.range()){
                        std::stringstream ss1;
                        std::string       str1;
                        ss1<<sv;
                        ss1>>str1;
                        if(str1.length()>4){
                           str1=str1.substr(0,4); 
                        }
                        scale_strs.pushBack(std::move(str1));
                    }
                }else{
                    for(const scalar& sv : scale_values.range()){
                        std::stringstream ss1;
                        std::string       str1;
                        ss1<<sv*exp;
                        ss1>>str1;
                        if(str1.length()>4){
                           str1=str1.substr(0,4); 
                        }
                        scale_strs.pushBack(std::move(str1));
                    }
                }
                {
                    output_<<std::endl<<"% X Scale"<<std::endl;
                    output_<<"\\coordinate (X_SCALE_LENGTH) at (0,"<<scale.x.length<<");"<<std::endl;
                    for(size_t a=0; a<scale_values.size(); ++a){
                        scale_values[a]=sca_.x*(scale_values[a]-range.x.min);
                        output_<<"\\coordinate (X_SCALE_"<<a<<") at ("<<scale_values[a]<<","<<0<<");"<<std::endl;
                    }
        
                    size_t max_leng=0;
                    for(const std::string& ss : scale_strs.range()){
                        size_t sz=ss.length();
                        if(sz>max_leng) max_leng=sz;
                    }
                    
                    size_t period=0;
                    scalar zero=scale_values[0];
                    for(const scalar& sv : scale_values.range(1)){
                        scalar deff=(sv-pointToCenti(scale.x.point*(static_cast<float>(max_leng)*0.5)))-(zero+pointToCenti(scale.x.point*(static_cast<float>(max_leng)*0.5)));
                        std::cout<<"D:"<<deff<<std::endl;
                        ++period;
                        if(deff>=pointToCenti(scale.x.point)) break;
                    }
    
                    for(uint_fast16_t n=0; n<_n; ++n){
                        for(size_t a=0; a<scale_strs.size(); ++a){
                            if(a%period){
                                scale_bar_flag.pushBack(false);
                            }else{
                                if(a==scale_strs.size()-1 && n!=_n-1){
                                    float right=scale_values[a-period]+pointToCenti(scale.x.point*(static_cast<float>(max_leng)*0.5));
                                    float left =sca_.x*(range.x.max-range.x.min)+scale_values[0]-pointToCenti(scale.x.point*(static_cast<float>(max_leng)*0.5));
                                    if(left-right>=pointToCenti(scale.x.point*0.5)){
                                        output_<<"\\draw ($(BOX_LB_"<<n<<"_"<<0<<")+(X_SCALE_"<<a<<")$) node[below] {\\fontsize{"<<scale.x.point<<"pt}{0pt}\\selectfont "<<scale_strs[a]<<"};"<<std::endl;
                                    }
                                }else{
                                    output_<<"\\draw ($(BOX_LB_"<<n<<"_"<<0<<")+(X_SCALE_"<<a<<")$) node[below] {\\fontsize{"<<scale.x.point<<"pt}{0pt}\\selectfont "<<scale_strs[a]<<"};"<<std::endl;
                                }
                                scale_bar_flag.pushBack(true);
                            }
                        }
                        for(uint_fast16_t m=0; m<_m; ++m){
                            for(size_t a=0; a<scale_values.size(); ++a){
                                if(scale_bar_flag[a]){
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(X_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(X_SCALE_"<<a<<")+(X_SCALE_LENGTH)$);"<<std::endl;
                                }else{
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(X_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(X_SCALE_"<<a<<")+0.5*(X_SCALE_LENGTH)$);"<<std::endl;
                                }
                            }
                            for(size_t a=0; a<scale_values.size(); ++a){
                                if(scale_bar_flag[a]){
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_Y)+(X_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_Y)+(X_SCALE_"<<a<<")-(X_SCALE_LENGTH)$);"<<std::endl;
                                }else{
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_Y)+(X_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_Y)+(X_SCALE_"<<a<<")-0.5*(X_SCALE_LENGTH)$);"<<std::endl;
                                }
                            }
                        }
                    }
                }
                break;
                */
                break;
            }
        }


        switch(scale.y.arg.number()){
            case Scale::DECIMAL:
            {
                gd::List<scalar>             scale_values;
                gd::ElasticList<std::string> scale_strs;
                gd::List<bool>               scale_bar_flag;

                scalar width=range.y.max-range.y.min;
                scalar  exp  =1;
                int32_t count=0;
                if(width<=3.0) while(width<=3.0){ width*=10.;  exp*=10.;  --count; }
                if(width>29.0) while(width>29.0){ width*=0.1;  exp*=0.1;  ++count; }
            
                int32_t min_i=static_cast<int32_t>(range.y.min*exp);
                int32_t max_i=static_cast<int32_t>(range.y.max*exp);
                scalar arg  =scale.y.arg.path<Scale::DECIMAL>();
                if(arg<range.y.min || range.y.max<arg){
                    arg=(static_cast<scalar>(min_i)+1)/exp;
                }
                uint32_t interval=scale.y.interval==0 ? scaleInterval(max_i-min_i) : scale.y.interval;
                gd::List<scalar> rev_sv;
                for(scalar a=arg-interval/exp; a>=range.y.min; a-=interval/exp){
                    rev_sv.pushBack(static_cast<scalar>(a));
                }
                for(size_t a=rev_sv.size(); a>0; --a){
                    scale_values.pushBack(rev_sv[a-1]);
                }

                for(scalar a=arg; a<=range.y.max; a+=interval/exp){
                    scale_values.pushBack(static_cast<scalar>(a));
                }
                
                if(0.0005<exp && exp<5000.){
                    for(const scalar& sv : scale_values.range()){
                        std::stringstream ss1;
                        std::string       str1;
                        ss1<<sv;
                        ss1>>str1;
                        if(str1.length()>5){
                           str1=str1.substr(0,5); 
                        }
                        scale_strs.pushBack(std::move(str1));
                    }
                }else{
                    for(const scalar& sv : scale_values.range()){
                        std::stringstream ss1;
                        std::string       str1;
                        ss1<<sv*exp;
                        ss1>>str1;
                        if(str1.length()>5){
                           str1=str1.substr(0,5); 
                        }
                        scale_strs.pushBack(std::move(str1));
                    }
                    output_<<"\\draw ($(BOX_LB_"<<0<<"_"<<_m-1<<")+(BOX_REGION_Y)+(0, "<<pointToCenti(scale.y.point)*0.5<<")$) node[above] {\\fontsize{"<<scale.x.point<<"pt}{0pt}\\selectfont $\\times 10^{"<<count<<"}$};"<<std::endl;
                }
 
                {
                    output_<<std::endl<<"% Y Scale"<<std::endl;
                    output_<<"\\coordinate (Y_SCALE_LENGTH) at ("<<scale.y.length<<", 0);"<<std::endl;
                    for(size_t a=0; a<scale_values.size(); ++a){
                        scale_values[a]=sca_.y*(scale_values[a]-range.y.min);
                        output_<<"\\coordinate (Y_SCALE_"<<a<<") at ("<<0<<","<<scale_values[a]<<");"<<std::endl;
                    }
    
                    size_t max_leng=1;
                    size_t period=0;
                    scalar zero=scale_values[0];
                    for(const scalar& sv : scale_values.range(1, scale_values.size())){
                        scalar deff=(sv-pointToCenti(scale.y.point*(static_cast<float>(max_leng)*0.25)))-(zero+pointToCenti(scale.y.point*(static_cast<float>(max_leng)*0.25)));
                        ++period;
                        if(deff>=pointToCenti(scale.y.point)) break;
                    }
    
                    for(uint_fast16_t m=0; m<_m; ++m){
                        for(size_t a=0; a<scale_strs.size(); ++a){
                            if(a%period){
                                scale_bar_flag.pushBack(false);
                            }else{
                                if(a==scale_strs.size()-1 && m!=_m-1){
                                    
                                    float top   =scale_values[a]+pointToCenti(scale.y.point*(static_cast<float>(max_leng)*0.25));
                                    float bottom=sca_.y*(range.y.max-range.y.min)+scale_values[0]-pointToCenti(scale.y.point*(static_cast<float>(max_leng)*0.25));
                                    if(bottom-top>=pointToCenti(scale.y.point)){
                                        output_<<"\\draw ($(BOX_LB_"<<0<<"_"<<m<<")+(Y_SCALE_"<<a<<")$) node[left] {\\fontsize{"<<scale.y.point<<"pt}{0pt}\\selectfont "<<scale_strs[a]<<"};"<<std::endl;
                                    }
                                }else{
                                    output_<<"\\draw ($(BOX_LB_"<<0<<"_"<<m<<")+(Y_SCALE_"<<a<<")$) node[left] {\\fontsize{"<<scale.y.point<<"pt}{0pt}\\selectfont "<<scale_strs[a]<<"};"<<std::endl;
                                }
                                scale_bar_flag.pushBack(true);
                            }
                        }
                        for(uint_fast16_t n=0; n<_n; ++n){
                            for(size_t a=0; a<scale_values.size(); ++a){
                                if(scale_bar_flag[a]){
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(Y_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(Y_SCALE_"<<a<<")+(Y_SCALE_LENGTH)$);"<<std::endl;
                                }else{
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(Y_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(Y_SCALE_"<<a<<")+0.5*(Y_SCALE_LENGTH)$);"<<std::endl;
                                }
                            }
                            for(size_t a=0; a<scale_values.size(); ++a){
                                if(scale_bar_flag[a]){
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_X)+(Y_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_X)+(Y_SCALE_"<<a<<")-(Y_SCALE_LENGTH)$);"<<std::endl;
                                }else{
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_X)+(Y_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_X)+(Y_SCALE_"<<a<<")-0.5*(Y_SCALE_LENGTH)$);"<<std::endl;
                                }
                            }
                        }
                    }
                }

                break;
            }
            case Scale::LOG:
            {
                
                
                if(range.y.min<=0){
                    std::cerr<<"Invarid range at log scale."<<std::endl;
                    std::exit(EXIT_FAILURE);
                }

                gd::List<scalar>             scale_values;
                gd::ElasticList<std::string> scale_strs;
                gd::List<bool>               scale_bar_flag;
                scalar arg  =scale.y.arg.path<Scale::LOG>().path<0>();
                
                int32_t min_e=0;
                int32_t max_e=0;
                while(r2d_.y.min< std::pow(arg, min_e)){ --min_e; };
                while(r2d_.y.min> std::pow(arg, min_e)){ ++min_e; };
                while(r2d_.y.max< std::pow(arg, max_e)){ --max_e; };
                while(r2d_.y.max> std::pow(arg, max_e)){ ++max_e; };
                uint32_t interval=scale.y.interval==0 ? scaleInterval(max_e-min_e) : scale.y.interval;
                
                r2d_.y.min=std::log(r2d_.y.min)/std::log(arg);
                r2d_.y.max=std::log(r2d_.y.max)/std::log(arg);
                sca_.y=sca_.y*(range.y.max-range.y.min)/(r2d_.y.max-r2d_.y.min);
                for(int32_t a=min_e; a<max_e; a+=interval){
                    scale_values.pushBack(a);
                }


                std::string base;
                if(scale.y.arg.path<Scale::LOG>().path<1>()==""){
                    std::stringstream ss1;
                    ss1<<arg;
                    ss1>>base;
                }else{
                    base=scale.y.arg.path<Scale::LOG>().path<1>();
                }
                
                for(const scalar& sv : scale_values.range()){
                    std::string expo;
                    std::stringstream ss1;
                    ss1<<sv;
                    ss1>>expo;
                    scale_strs.pushBack(std::string("$")+base+"^{"+expo+"}$");
                }
                
                {
                    output_<<std::endl<<"% Y Scale"<<std::endl;
                    output_<<"\\coordinate (Y_SCALE_LENGTH) at ("<<scale.y.length<<",0);"<<std::endl;
                    for(size_t a=0; a<scale_values.size(); ++a){
                        scale_values[a]=sca_.y*(scale_values[a]-r2d_.y.min);
                        output_<<"\\coordinate (Y_SCALE_"<<a<<") at (0,"<<scale_values[a]<<");"<<std::endl;
                    }
        
                    size_t max_leng=3;
                    
                    size_t period=0;
                    scalar zero=scale_values[0];
                    for(const scalar& sv : scale_values.range(1)){
                        scalar deff=(sv-pointToCenti(scale.y.point*(static_cast<float>(max_leng)*0.5)))-(zero+pointToCenti(scale.y.point*(static_cast<float>(max_leng)*0.5)));
                        ++period;
                        if(deff>=pointToCenti(scale.y.point)) break;
                    }
    
                    for(uint_fast16_t m=0; m<_m; ++m){
                        for(size_t a=0; a<scale_strs.size(); ++a){
                            if(a%period){
                                scale_bar_flag.pushBack(false);
                            }else{
                                if(a==scale_strs.size()-1 && m!=_m-1){
                                    float top    =scale_values[a-period]+pointToCenti(scale.y.point*(static_cast<float>(max_leng)*0.5));
                                    float bottom =sca_.y*(r2d_.y.max-r2d_.y.min)+scale_values[0]-pointToCenti(scale.y.point*(static_cast<float>(max_leng)*0.5));
                                    if(bottom-top>=pointToCenti(scale.y.point*0.5)){
                                        output_<<"\\draw ($(BOX_LB_"<<0<<"_"<<m<<")+(Y_SCALE_"<<a<<")$) node[left] {\\fontsize{"<<scale.y.point<<"pt}{0pt}\\selectfont "<<scale_strs[a]<<"};"<<std::endl;
                                    }
                                }else{
                                    output_<<"\\draw ($(BOX_LB_"<<0<<"_"<<m<<")+(Y_SCALE_"<<a<<")$) node[left] {\\fontsize{"<<scale.y.point<<"pt}{0pt}\\selectfont "<<scale_strs[a]<<"};"<<std::endl;
                                }
                                scale_bar_flag.pushBack(true);
                            }
                        }
                        for(uint_fast16_t n=0; n<_n; ++n){
                            for(size_t a=0; a<scale_values.size(); ++a){
                                if(scale_bar_flag[a]){
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(Y_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(Y_SCALE_"<<a<<")+(Y_SCALE_LENGTH)$);"<<std::endl;
                                }else{
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(Y_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(Y_SCALE_"<<a<<")+0.5*(Y_SCALE_LENGTH)$);"<<std::endl;
                                }
                            }
                            for(size_t a=0; a<scale_values.size(); ++a){
                                if(scale_bar_flag[a]){
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_X)+(Y_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_X)+(Y_SCALE_"<<a<<")-(Y_SCALE_LENGTH)$);"<<std::endl;
                                }else{
                                    output_<<"\\draw[thin] ($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_X)+(Y_SCALE_"<<a<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+(BOX_REGION_X)+(Y_SCALE_"<<a<<")-0.5*(Y_SCALE_LENGTH)$);"<<std::endl;
                                }
                            }
                        }
                    }
                }
                break;
            }
            case Scale::ANY:
            {
                break;
            }
        }
    }


    void TabParPlots::_drawLabel(std::ofstream& output_) noexcept
    {
        output_<<std::endl<<"% X Label"<<std::endl;
        output_<<"\\coordinate (X_LABEL_DEFF) at (0,"<<label.margin.y+pointToCenti(label.x.point*0.5+scale.x.point)*1.1<<");"<<std::endl;
        output_<<"\\coordinate (X_LABEL) at ($0.5*(BOX_LB_"<<0<<"_"<<0<<")+0.5*(BOX_RT_"<<_n-1<<"_"<<0<<")-0.5*(BOX_REGION_Y)-(X_LABEL_DEFF)$);"<<std::endl;
        output_<<"\\draw (X_LABEL) node {\\fontsize{"<<label.x.point<<"pt}{0pt}\\selectfont "<<label.x.string<<"};"<<std::endl;
        
        output_<<std::endl<<"% Y Label"<<std::endl;
        output_<<"\\coordinate (Y_LABEL_DEFF) at ("<<label.margin.x+pointToCenti(label.y.point*0.5+scale.y.point*3)*1.1<<",0);"<<std::endl;
        output_<<"\\coordinate (Y_LABEL) at ($0.5*(BOX_LB_"<<0<<"_"<<0<<")+0.5*(BOX_RT_"<<0<<"_"<<_m-1<<")-0.5*(BOX_REGION_X)-(Y_LABEL_DEFF)$);"<<std::endl;
        output_<<"\\draw (Y_LABEL) node {\\rotatebox[origin=c]{90}{\\fontsize{"<<label.y.point<<"pt}{0pt}\\selectfont "<<label.y.string<<"}};"<<std::endl;

        return;
    }


    void TabParPlots::_drawPlot(const Vec2& sca_, const Range2D& r2d_, std::ofstream& output_, gd::List<gd::Group<uint32_t, 4>>& cofs_) noexcept
    {
        for(size_t p=0; p<_p; ++p){
            PlotSpec& ps=_plot_spec_array[p];
            if(!ps.line.color().number()){
                if(!ps.color().number()){
                    ps.line.color.construct(static_cast<Color::ID>(p%18));
                }else{
                    ps.line.color=ps.color;
                }
            }
            if(!ps.point.color().number()){
                if(!ps.color().number()){
                    ps.point.color.construct(static_cast<Color::ID>(p%18));
                }else{
                    ps.point.color=ps.color;
                }
            }
        }

                    
        float xmax, ymax;
        xmax=sca_.x*(r2d_.x.max-r2d_.x.min);
        ymax=sca_.y*(r2d_.y.max-r2d_.y.min);

        for(uint_fast16_t n=0; n<_n; ++n){
            for(uint_fast16_t m=0; m<_m; ++m){
                for(uint_fast16_t p=0; p<_p && p<_data_set[n*_m+m].size(); ++p){
                    const PlotSpec& ps =_plot_spec_array[p];
                    const Data2D&   d2d=_data_set[n*_m+m][p];

                    for(size_t a=0; a<d2d.datas().size(); ++a){
                        Vec2 p1(d2d.datas()[a  ].path<0>(), d2d.datas()[a  ].path<1>());
                        switch(scale.x.arg.number()){
                            case Scale::DECIMAL:
                                p1.x=sca_.x*(p1.x-range.x.min);
                                break;
                            case Scale::LOG:
                                p1.x=sca_.x*(std::log(p1.x)/std::log(scale.x.arg.path<Scale::LOG>().path<0>())-r2d_.x.min);
                                break;
                        }
                        switch(scale.y.arg.number()){
                            case Scale::DECIMAL:
                                p1.y=sca_.y*(p1.y-range.y.min);
                                break;
                            case Scale::LOG:
                                p1.y=sca_.y*(std::log(p1.y)/std::log(scale.y.arg.path<Scale::LOG>().path<0>())-r2d_.y.min);
                                break;
                        }


                        if(0.<=p1.x && p1.x<=xmax && 0.<=p1.y && p1.y<=ymax){
                            if(p1.x<xmax*0.5){

                                if  (p1.y<ymax*0.5) ++cofs_[n*_m+m].path(0);
                                else                ++cofs_[n*_m+m].path(1);
                            
                            }else{
                                
                                if  (p1.y<ymax*0.5) ++cofs_[n*_m+m].path(2);
                                else                ++cofs_[n*_m+m].path(3);

                            }
                        }
                    }

                    if(ps.line.enable){
                        output_<<std::endl<<"% ("<<n<<","<<m<<","<<p<<") Plot Line"<<std::endl;
                        const Data2D& d2d=_data_set[n*_m+m][p];
                        std::string color;
                        switch(ps.line.color().number()){
                            case 1:
                                color=ps.line.color._idToString();
                                break;
                            case 2:
                                color=ps.line.color._rgbToString();
                                break;
                        }

                        std::string width=ps.line._widthToString();
                        std::string dot  =ps.line._dotToString();
                        if(dot=="solid") dot="";
                        bool initial_data=true;
                        for(size_t a=0; a<d2d.datas().size()-1; ++a){
                            Vec2 p1(d2d.datas()[a  ].path<0>(), d2d.datas()[a  ].path<1>());
                            Vec2 p2(d2d.datas()[a+1].path<0>(), d2d.datas()[a+1].path<1>());
                            bool p1_in=(range.x.min<=p1.x && p1.x<=range.x.max && range.y.min<=p1.y && p1.y<=range.y.max);
                            bool p2_in=(range.x.min<=p2.x && p2.x<=range.x.max && range.y.min<=p2.y && p2.y<=range.y.max);
                            if(p1_in && p2_in){
                                scalar x1,x2,y1,y2;
                                switch(scale.x.arg.number()){
                                    case Scale::DECIMAL:
                                        x1=sca_.x*(p1.x-range.x.min);
                                        x2=sca_.x*(p2.x-range.x.min);
                                        break;
                                    case Scale::LOG:
                                        x1=sca_.x*(std::log(p1.x)/std::log(scale.x.arg.path<Scale::LOG>().path<0>())-r2d_.x.min);
                                        x2=sca_.x*(std::log(p2.x)/std::log(scale.x.arg.path<Scale::LOG>().path<0>())-r2d_.x.min);
                                        break;

                                }
                                switch(scale.y.arg.number()){
                                    case Scale::DECIMAL:
                                        y1=sca_.y*(p1.y-range.y.min);
                                        y2=sca_.y*(p2.y-range.y.min);
                                        break;
                                    case Scale::LOG:
                                        y1=sca_.y*(std::log(p1.y)/std::log(scale.y.arg.path<Scale::LOG>().path<0>())-r2d_.y.min);
                                        y2=sca_.y*(std::log(p2.y)/std::log(scale.y.arg.path<Scale::LOG>().path<0>())-r2d_.y.min);
                                        break;
                                } 
                                if(d2d.separator().find(a)!=d2d.separator().end()){
                                    if(!initial_data) output_<<";"<<std::endl;
                                    initial_data = true;
                                }else{
                                    if(initial_data){
                                        output_<<"\\draw["<<color<<","<<width<<","<<dot<<","<<ps.line.option<<"] ($(BOX_LB_"<<n<<"_"<<m<<")+("<<x1<<","<<y1<<")$)--($(BOX_LB_"<<n<<"_"<<m<<")+("<<x2<<","<<y2<<")$)";
                                        initial_data=false;
                                    }else{
                                        output_<<std::endl<<"--($(BOX_LB_"<<n<<"_"<<m<<")+("<<x2<<","<<y2<<")$)";
                                    }
                                }
                            }else if(p1_in){
                                if(!initial_data) output_<<";"<<std::endl;
                                initial_data=true;
                            }
                            if(a==d2d.datas().size()-2){
                                if(!initial_data) output_<<";"<<std::endl;
                            }
                        }
                    }
                    if(ps.point.enable){
                        output_<<std::endl<<"% ("<<n<<","<<m<<","<<p<<") Plot Point"<<std::endl;
                        const Data2D& d2d=_data_set[n*_m+m][p];
                        std::string color;
                        switch(ps.point.color().number()){
                            case 1:
                                color=ps.point.color._idToString();
                                break;
                            case 2:
                                color=ps.point.color._rgbToString();
                                break;
                        }
                        float offset=0.;
                        if(ps.point.shape=="$\\circ$" || ps.point.shape=="$\\bullet$" || ps.point.shape=="\\textbullet") offset=pointToCenti(ps.point.size)*0.025;

                        for(size_t a=0; a<d2d.datas().size(); ++a){
                            Vec2 p1(d2d.datas()[a  ].path<0>(), d2d.datas()[a  ].path<1>());
                            if(range.x.min<=p1.x && p1.x<=range.x.max && range.y.min<=p1.y && p1.y<=range.y.max){
                                scalar x1,y1;
                                switch(scale.x.arg.number()){
                                    case Scale::DECIMAL:
                                        x1=sca_.x*(p1.x-range.x.min);
                                        break;
                                    case Scale::LOG:
                                        x1=sca_.x*(std::log(p1.x)/std::log(scale.x.arg.path<Scale::LOG>().path<0>())-r2d_.x.min);
                                        break;

                                }
                                switch(scale.y.arg.number()){
                                    case Scale::DECIMAL:
                                        y1=sca_.y*(p1.y-range.y.min);
                                        break;
                                    case Scale::LOG:
                                        y1=sca_.y*(std::log(p1.y)/std::log(scale.y.arg.path<Scale::LOG>().path<0>())-r2d_.y.min);
                                        break;
                                }
                                if(d2d.skipper().find(a)==d2d.skipper().end()){
                                    output_<<"\\draw["<<color<<","<<ps.point.option<<"] ($(BOX_LB_"<<n<<"_"<<m<<")+("<<x1<<","<<y1-offset<<")$) node{\\fontsize{"<<ps.point.size<<"pt}{0pt}\\selectfont "<<ps.point.shape<<"};"<<std::endl;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        return;
    }



    void TabParPlots::_drawKey(const gd::List<gd::Group<uint32_t, 4>>& cofs_, std::ofstream& output_, uint32_t key_nmpos_[2]) noexcept
    {
        size_t   index=0;
        uint32_t min_count=~0U;
        Position::Base pos_base=Position::LEFT_TOP;
        for(size_t a=0; a<cofs_.size(); ++a){
            const gd::Group<uint32_t, 4>& gr=cofs_[a];
            switch(key.position.base){
                case Position::AUTO:
                    if(gr.path(0)<=min_count){
                        min_count=gr.path(0);
                        index=a;
                        pos_base=Position::LEFT_BOTTOM;
                    }
                    if(gr.path(2)<=min_count){
                        min_count=gr.path(2);
                        index=a;
                        pos_base=Position::RIGHT_BOTTOM;
                    }
                    if(gr.path(1)<=min_count){
                        min_count=gr.path(1);
                        index=a;
                        pos_base=Position::LEFT_TOP;
                    }
                    if(gr.path(3)<=min_count){
                        min_count=gr.path(3);
                        index=a;
                        pos_base=Position::RIGHT_TOP;
                    }
                    break;

                case Position::RIGHT_TOP:
                    if(gr.path(3)<=min_count){
                        min_count=gr.path(3);
                        index=a;
                        pos_base=Position::RIGHT_TOP;
                    }
                    break;

                case Position::LEFT_TOP:
                    if(gr.path(1)<=min_count){
                        min_count=gr.path(1);
                        index=a;
                        pos_base=Position::LEFT_TOP;
                    }
                    break;

                case Position::RIGHT_BOTTOM:
                    if(gr.path(2)<=min_count){
                        min_count=gr.path(2);
                        index=a;
                        pos_base=Position::RIGHT_BOTTOM;
                    }
                    break;

                case Position::LEFT_BOTTOM:
                    if(gr.path(0)<=min_count){
                        min_count=gr.path(0);
                        index=a;
                        pos_base=Position::LEFT_BOTTOM;
                    }
                    break;
            }
        }

        key.position.base=pos_base;
        key_nmpos_[0]=index;
        key_nmpos_[1]=pos_base;
        
        float key_str_width=0;
        for(size_t a=0; a<_plot_spec_array.size(); ++a){
            PlotSpec& ps=_plot_spec_array[a];
            if(ps.tag=="") ps.tag=std::to_string(a);
            float width=key.str_scale*keyWidth(ps.tag)*pointToCenti(key.point);
            if(width>key_str_width) key_str_width=width; 
        }
        float key_space_width=pointToCenti(key.point)*3+key_str_width+key.margin*2;
        float key_space_height=(key.interval+pointToCenti(key.point))*_plot_spec_array.size()-key.interval+key.margin*2;

        output_<<std::endl<<"% KEY"<<std::endl;
        output_<<"\\coordinate (KEY_REGION_X) at ("<<key_space_width<<",0);"<<std::endl;
        output_<<"\\coordinate (KEY_REGION_Y) at (0,"<<key_space_height<<");"<<std::endl;
        switch(key.position.base){

            case Position::LEFT_BOTTOM:
                output_<<"\\coordinate (KEY_LB) at ($(BOX_LB_"<<index/_m<<"_"<<index%_m<<")+("<<key.position.disp.x<<","<<key.position.disp.y<<")$);"<<std::endl;
                output_<<"\\coordinate (KEY_RT) at ($(KEY_LB)+(KEY_REGION_X)+(KEY_REGION_Y)$);"<<std::endl;
                output_<<"\\draw[semithick, fill=white] (KEY_LB) rectangle (KEY_RT);"<<std::endl;
                break;

            case Position::RIGHT_BOTTOM:
                output_<<"\\coordinate (KEY_LB) at ($(BOX_LB_"<<index/_m<<"_"<<index%_m<<")+(BOX_REGION_X)-(KEY_REGION_X)+("<<-key.position.disp.x<<","<<key.position.disp.y<<")$);"<<std::endl;
                output_<<"\\coordinate (KEY_RT) at ($(KEY_LB)+(KEY_REGION_X)+(KEY_REGION_Y)$);"<<std::endl;
                output_<<"\\draw[semithick, fill=white] (KEY_LB) rectangle (KEY_RT);"<<std::endl;
                break;

            case Position::LEFT_TOP:
                output_<<"\\coordinate (KEY_LB) at ($(BOX_LB_"<<index/_m<<"_"<<index%_m<<")+(BOX_REGION_Y)-(KEY_REGION_Y)+("<<key.position.disp.x<<","<<-key.position.disp.y<<")$);"<<std::endl;
                output_<<"\\coordinate (KEY_RT) at ($(KEY_LB)+(KEY_REGION_X)+(KEY_REGION_Y)$);"<<std::endl;
                output_<<"\\draw[semithick, fill=white] (KEY_LB) rectangle (KEY_RT);"<<std::endl;
                break;

            case Position::RIGHT_TOP:
                output_<<"\\coordinate (KEY_RT) at ($(BOX_RT_"<<index/_m<<"_"<<index%_m<<")-("<<key.position.disp.x<<","<<key.position.disp.y<<")$);"<<std::endl;
                output_<<"\\coordinate (KEY_LB) at ($(KEY_RT)-(KEY_REGION_X)-(KEY_REGION_Y)$);"<<std::endl;
                output_<<"\\draw[semithick, fill=white] (KEY_LB) rectangle (KEY_RT);"<<std::endl;
                break;

            default:
                break;
        }

        float line_left =key.margin;
        float line_right=key.margin+pointToCenti(key.point)*2;
        float str_center=key.margin+pointToCenti(key.point)*3+key_str_width*0.5;
        output_<<"\\coordinate (KEY_INTERVAL) at (0,"<<key.interval<<");"<<std::endl;
        output_<<"\\coordinate (KEY_STRING_HEIGHT) at (0,"<<pointToCenti(key.point)<<");"<<std::endl;
        output_<<"\\coordinate (KEY_LINE_DECENT) at (0,"<<pointToCenti(key.point)*0.5<<");"<<std::endl;
        for(size_t a=0; a<_plot_spec_array.size(); ++a){
            const PlotSpec& ps =_plot_spec_array[a];
            if(ps.line.enable){
                std::string color;
                switch(ps.line.color().number()){
                    case 1:
                        color=ps.line.color._idToString();
                        break;
                    case 2:
                        color=ps.line.color._rgbToString();
                        break;
                }
                std::string width=ps.line._widthToString();
                std::string dot  =ps.line._dotToString();
                if(dot=="solid") dot="";
                output_<<"\\draw["<<color<<","<<width<<","<<dot<<","<<ps.line.option<<"] ($(KEY_LB)+(KEY_REGION_Y)-"<<a<<"*(KEY_STRING_HEIGHT)-"<<a<<"*(KEY_INTERVAL)-(KEY_LINE_DECENT)+("<<line_left<<","<<-key.margin<<")$)-"
                                                                                    << "-($(KEY_LB)+(KEY_REGION_Y)-"<<a<<"*(KEY_STRING_HEIGHT)-"<<a<<"*(KEY_INTERVAL)-(KEY_LINE_DECENT)+("<<line_right<<","<<-key.margin<<")$);"<<std::endl;
            }
            if(ps.point.enable){
                std::string color;
                switch(ps.point.color().number()){
                    case 1:
                        color=ps.point.color._idToString();
                        break;
                    case 2:
                        color=ps.point.color._rgbToString();
                        break;
                }
                float offset=0.;
                if(ps.point.shape=="$\\circ$" || ps.point.shape=="$\\bullet$" || ps.point.shape=="\\textbullet") offset=pointToCenti(ps.point.size)*0.025;
                output_<<"\\draw["<<color<<","<<ps.point.option<<"] ($(KEY_LB)+(KEY_REGION_Y)-"<<a<<"*(KEY_STRING_HEIGHT)-"<<a<<"*(KEY_INTERVAL)-(KEY_LINE_DECENT)+("<<(line_left+line_right)*0.5<<","<<-key.margin-offset<<")$) node{\\fontsize{"<<ps.point.size<<"pt}{0pt}\\selectfont "<<ps.point.shape<<"};"<<std::endl;
            }
            
            output_<<"\\draw ($(KEY_LB)+(KEY_REGION_Y)-"<<a<<"*(KEY_STRING_HEIGHT)-"<<a<<"*(KEY_INTERVAL)-(KEY_LINE_DECENT)+("<<str_center<<","<<-key.margin<<")$) node{\\fontsize{"<<key.point<<"pt}{0pt}\\selectfont "<<ps.tag<<"};"<<std::endl;
        }
        //float key_space_width=pointToCenti(key.point)*4+key_str_width+key.margin*2;
        //float key_space_height=(key.interval+pointToCenti(key.point))*_plot_spec_array.size()-key.interval+key.margin*2;


        return;
    }



    void TabParPlots::_drawTitle(const gd::List<gd::Group<uint32_t, 4>>& cofs_, const uint32_t key_nmpos_[2], std::ofstream& output_) noexcept
    {
        for(size_t a=0; a<_title_set.size(); ++a){
            const gd::Group<uint32_t, 4>& gr=cofs_[a];
            uint32_t min_count=~0U;
            Position::Base pos_base=Position::RIGHT_TOP;
            switch(_title_set[a].position.base){
                case Position::AUTO:
                    if(a==key_nmpos_[0]){
                        if(key_nmpos_[1]!=Position::LEFT_BOTTOM && gr.path(0)<=min_count){
                            min_count=gr.path(0);
                            pos_base=Position::LEFT_BOTTOM;
                        }
                        if(key_nmpos_[1]!=Position::RIGHT_BOTTOM && gr.path(2)<=min_count){
                            min_count=gr.path(2);
                            pos_base=Position::RIGHT_BOTTOM;
                        }
                        if(key_nmpos_[1]!=Position::LEFT_TOP && gr.path(1)<=min_count){
                            min_count=gr.path(1);
                            pos_base=Position::LEFT_TOP;
                        }
                        if(key_nmpos_[1]!=Position::RIGHT_TOP && gr.path(3)<=min_count){
                            min_count=gr.path(3);
                            pos_base=Position::RIGHT_TOP;
                        }
                    }else{
                        if(gr.path(0)<min_count){
                            min_count=gr.path(0);
                            pos_base=Position::LEFT_BOTTOM;
                        }
                        if(gr.path(2)<min_count){
                            min_count=gr.path(2);
                            pos_base=Position::RIGHT_BOTTOM;
                        }
                        if(gr.path(1)<min_count){
                            min_count=gr.path(1);
                            pos_base=Position::LEFT_TOP;
                        }
                        if(gr.path(3)<min_count){
                            min_count=gr.path(3);
                            pos_base=Position::RIGHT_TOP;
                        }
                    }
                    break;

                case Position::RIGHT_TOP:
                    pos_base=Position::RIGHT_TOP;
                    break;

                case Position::LEFT_TOP:
                    pos_base=Position::LEFT_TOP;
                    break;

                case Position::RIGHT_BOTTOM:
                    pos_base=Position::RIGHT_BOTTOM;
                    break;

                case Position::LEFT_BOTTOM:
                    pos_base=Position::LEFT_BOTTOM;
                    break;
            }

            std::string tit=_title_set[a].string;
            if(tit=="\t") tit=std::string("(")+std::to_string(a/_m)+","+std::to_string(a%_m)+")";
            float x=0.5*static_cast<float>(mathStrWidth(tit))*0.25*pointToCenti(_title_set[a].point);
            float y=0.5*pointToCenti(_title_set[a].point);
            //float x_margin=_title_set[a].margin.x;
            //float y_margin=_title_set[a].margin.y;
            output_<<"\\coordinate (TITLE_POS_DISP_X) at ("<<_title_set[a].position.disp.x<<",0);"<<std::endl;
            output_<<"\\coordinate (TITLE_POS_DISP_Y) at (0,"<<_title_set[a].position.disp.y<<");"<<std::endl;
            switch(pos_base){
                case Position::LEFT_BOTTOM  :
                    output_<<"\\draw ($(BOX_LB_"<<a/_m<<"_"<<a%_m<<")+(TITLE_POS_DISP_X)+(TITLE_POS_DISP_Y)+("<<x<<","<<y<<")$) node{\\fontsize{"<<_title_set[a].point<<"pt}{0pt}\\selectfont "<<tit<<"};"<<std::endl;
                    break;
                case Position::RIGHT_BOTTOM :
                    output_<<"\\draw ($(BOX_LB_"<<a/_m<<"_"<<a%_m<<")+(BOX_REGION_X)-(TITLE_POS_DISP_X)+(TITLE_POS_DISP_Y)+("<<-x<<","<<y<<")$) node{\\fontsize{"<<_title_set[a].point<<"pt}{0pt}\\selectfont "<<tit<<"};"<<std::endl;
                    break;
                case Position::LEFT_TOP     :
                    output_<<"\\draw ($(BOX_LB_"<<a/_m<<"_"<<a%_m<<")+(BOX_REGION_Y)+(TITLE_POS_DISP_X)-(TITLE_POS_DISP_Y)+("<<x<<","<<-y<<")$) node{\\fontsize{"<<_title_set[a].point<<"pt}{0pt}\\selectfont "<<tit<<"};"<<std::endl;
                    break;
                case Position::RIGHT_TOP    :
                    output_<<"\\draw ($(BOX_RT_"<<a/_m<<"_"<<a%_m<<")-(TITLE_POS_DISP_X)-(TITLE_POS_DISP_Y)-("<<x<<","<<y<<")$) node{\\fontsize{"<<_title_set[a].point<<"pt}{0pt}\\selectfont "<<tit<<"};"<<std::endl;
                    break;
            }
        }
    }


    void TabParPlots::_writeFinalCode(std::ofstream& output_) noexcept
    {
        output_<<"\\end{tikzpicture}"<<std::endl;
        output_<<"\\end{figure}"<<std::endl;
        output_<<"\\end{document}"<<std::endl;
    
        return;
    }



    //_ Constant Function
    size_t TabParPlots::_memory(void) const noexcept
    {
        return 0;
    }


}
