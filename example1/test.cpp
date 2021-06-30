#include "../include/cptp/table_parallel_plots.hpp"

int main(void){
    
    // セル(0,0)の入力データ
    cptp::Data2DArray data_array00;
    {
        // データ配列（yのみ）
        double ydata1[]={1, 2, 4, 8, 16, 32};
        double ydata2[]={1, 3, 5, 7, 9, 11, 13, 15, 17};
        
        // x軸の値にインデックスを指定
        cptp::Data2D data1(cptp::Data2D::INDEX, cptp::Data<double>(ydata1, 6));
        cptp::Data2D data2(cptp::Data2D::INDEX, cptp::Data<double>(ydata2, 9));

        // (0,0)のData2DArrayにpushBackで追加
        data_array00.pushBack(data1);
        data_array00.pushBack(data2);
    }

    // セル(0,1)の入力データ
    cptp::Data2DArray data_array01;
    {
        // データ配列（x,y 両方）
        uint32_t xdata1[]={4, 5, 6, 7, 8, 9};
        double   ydata1[]={2, 1, 0.5, 0.25, 0.125, 0.0625};
        uint32_t xdata2[]={1, 2, 3, 4, 5, 6, 7, 8, 9};
        double   ydata2[]={0.0625, 0.125, 0.25, 0.5, 1, 2};
        
        // x軸にxdataをy軸にydataをそれぞれ指定
        cptp::Data2D data1(cptp::Data<uint32_t>(xdata1, 6), cptp::Data<double>(ydata1, 6));
        cptp::Data2D data2(cptp::Data<uint32_t>(xdata2, 9), cptp::Data<double>(ydata2, 6));

        // (0,1)のData2DArrayにpushBackで追加
        data_array01.pushBack(data1);
        data_array01.pushBack(data2);
    }


    // 1x2テーブルで各セルに最大2個のプロットテーブルを作成
    cptp::TabParPlots tpp(1, 2, 2);
    
    // (0,0)にdata_array00、(0,1)にdata_array01を割り振り
    tpp.setDatas(0, 0, data_array00);
    tpp.setDatas(0, 1, data_array01);
    

    // プロットの点を有効にし、設定を反映
    cptp::PlotSpec ps;
    ps.point.enable=true;
    tpp.setPlotSpec(0, ps);
    tpp.setPlotSpec(1, ps);
    
    // x軸のラベル、y軸のラベルを設定
    tpp.label.x.string="$r$ [nm]";
    tpp.label.y.string="$\\rho$ [g/$\\mathrm{cm}^3$]";
    
    // figureサイズを縦長に変更
    tpp.figure.size.construct(cptp::Figure::CAMMPUS, cptp::Vec2(5.5, 8.));

    // tex/example1.texとしてtexファイルを作成
    tpp.outputPlot("tex/example1.tex");
}
