#include "../include/cptp/table_parallel_plots.hpp"

int main(void){
    
    // セル(0,0)の入力データ
    cptp::Data2DArray data_array00;
    {
        // ファイルストリームを利用
        std::ifstream ifs1("ydata00_1.txt");
        std::ifstream ifs2("ydata00_2.txt");
        
        // x軸の値にインデックスを指定し、0ラインの値を利用
        cptp::Data2D data1(ifs1, cptp::Data2D::INDEX, 0);
        cptp::Data2D data2(ifs2, cptp::Data2D::INDEX, 0);

        // (0,0)のData2DArrayにpushBackで追加
        data_array00.pushBack(data1);
        data_array00.pushBack(data2);
    }

    // セル(0,1)の入力データ
    cptp::Data2DArray data_array01;
    {
        {
            // ファイルストリームを利用
            std::ifstream ifs1("ydata01.txt"); 
            
            // x軸に0ラインの値を利用し、y軸に1ラインの値を利用
            cptp::Data2D data1(ifs1, 0, 1);
            
            // (0,1)のData2DArrayにpushBackで追加
            data_array01.pushBack(data1);
        }
        {
            // ファイルストリームを利用
            std::ifstream ifs1("ydata01.txt"); 
            
            // x軸に2ラインの値を利用し、y軸に3ラインの値を利用
            cptp::Data2D data2(ifs1, 2, 3);
            
            // (0,1)のData2DArrayにpushBackで追加
            data_array01.pushBack(data2);
        }
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
    tpp.outputPlot("tex/example2.tex");
}
