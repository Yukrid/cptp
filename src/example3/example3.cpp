#include <cptp.hpp>
#include <filesystem>

int main(void){
    
    // セル(0,0)の入力データ
    cptp::Data2DArray data_array;
    {
        // データ配列（yのみ）
        double* ydata1 = new double[1000];
        for(size_t a = 0; a < 1000; ++a){
            double x = a*20/1000.;
            ydata1[a] = std::sin(std::exp(x-5.))/std::pow(x-5., 2) + 1;
        }
        
        // x軸の値にインデックスを指定
        cptp::Data2D data1(cptp::Data2D::INDEX, cptp::Data<double>(ydata1, 1000));
        
        // yが大きすぎるプロット点のスキップ
        for(size_t a = 0; a < 1000; ++a) if(data1.datas().path<1>()[a] > 5.) data1.skip(a);

        // Data2DArrayにpushBackで追加
        data_array.pushBack(data1);
    }
    
    // 1系列のプロットを作成
    cptp::SinglePlots tpp(1);
    
    // data_arrayを割り振り
    tpp.setDatas(data_array);
    
    // x軸のラベル、y軸のラベル、xの最大値を450に設定
    tpp.label.x.string="$\\omega$ [1/sec]";
    tpp.label.y.string="$A$ [m]";
    tpp.range.x.max = 450; 

    // tex/example1.texとしてtexファイルを作成
    std::filesystem::create_directory("example3_tex");
    tpp.outputPlot("example3_tex/example3.tex");
}
