#include <cptp.hpp>
#include <filesystem>

int main(void){
    
    // セル(0,0)の入力データ
    cptp::Data2DArray data_array;
    {
        // データ配列（yのみ）
        double   ydata1[]={1, 2, 4, 8, 16, 32};
        uint32_t xdata2[]={1, 2, 3, 4, 5, 6, 7};
        double   ydata2[]={1, 3, 5, 7, 9, 11, 13};
        
        // x軸の値にインデックスを指定
        cptp::Data2D data1(cptp::Data2D::INDEX, cptp::Data<double>(ydata1, 6));
        
        // x軸にxdataをy軸にydataをそれぞれ指定
        cptp::Data2D data2(cptp::Data<uint32_t>(xdata2, 7), cptp::Data<double>(ydata2, 7));
        data2.skip(3);

        // Data2DArrayにpushBackで追加
        data_array.pushBack(data1);
        data_array.pushBack(data2);
    }
    
    // 最大2個のプロットテーブルを作成
    cptp::SinglePlots tpp(2);
    
    // (data_arrayを割り振り
    tpp.setDatas(data_array);
    

    // プロットの点を有効にし、設定を反映
    cptp::PlotSpec ps;
    ps.point.enable=true;
    tpp.setPlotSpec(0, ps);
    tpp.setPlotSpec(1, ps);
    
    // x軸のラベル、y軸のラベルを設定
    tpp.label.x.string="$r$ [nm]";
    tpp.label.y.string="$\\rho$ [g/$\\mathrm{cm}^3$]";

    // figureサイズを縦長に変更
//    tpp.figure.size.construct(cptp::Figure::CAMMPUS, cptp::Vec2(8., 8.));
    
    // tex/example1.texとしてtexファイルを作成
    std::filesystem::create_directory("example1_tex");
    tpp.outputPlot("example1_tex/example1.tex");
}
