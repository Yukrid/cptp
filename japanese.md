# 注意事項

- 未実装の機能あり
- c++20 が必要
- 内輪向け

# 例１- 配列からのプロット
```c++
#incldue <table_parallel_plots.hpp>

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
```
# 例２- ファイルからのプロット
```c++
#include <table_parallel_plots.hpp>

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
```


# 設定

## figure

### size（型：``cptp::Figure::Size`` ）

図全体のサイズを 11.3 cm x 7.0 cm に設定。

```c++
tpp.figure.size.construct(cptp::Figure::CAMMPUS, cptp::Vec2(11.3, 7.0));
```

図のプロット領域のサイズを 8.0 cm x 12.0 cm に設定。

```c++
tpp.figure.size.construct(cptp::Figure::PLOT_AREA, cptp::Vec2(8., 12.0));
```

図全体のサイズとプロット領域のサイズは択一的です。デフォルトは図全体のサイズが 11.3 cm x 7.0 cm に設定になるように設定されています。``construct``関数で変更して下さい。

### margin（型：``cptp::Vec2``）
x,y のマージンをそれぞれ 0.4 cmに設定。マージンは、ラベルまたはプロット領域の右上の角から図の末端までの距離を表します。

```c++
tpp.figure.margin=cptp::Vec2(0.4, 0.4);
```

``tpp.figure.margin.x`` などを変更することで、$x$ 軸のマージンのみ変更なども可能です。

## label

### enable（型：``bool``）

ラベルを表示するかどうかのフラグです。true で有効、false で無効です。

```c++
表示するかどうかのフラグです。true で有効、false で無効です。

￼
tpp.label.enable=true;
[x or y].string（型：std::string）
tpp.label.enable=true;
```

### [x or y].string（型：``std::string``）

ラベル名は x,y で別個に設定できます。Latexの数式が仕様できます。

```cpp
tpp.label.x.string="$x$";
```

### [x or y].point（型：``double``）

ラベルの文字のサイズです。x,y で別個に設定できます。

```cpp
tpp.label.x.point=10.0;
```

### margin（型：``cptp::Vec2``）

ラベルとスケールの文字の間の空白(cm)です。

```cpp
tpp.label.margin=cptp::Vec2(0.2, 0.2);
```

``tpp.label.margin.x`` などを変更することで、x 軸のマージンのみ変更なども可能です。

## scale

### enable（型：``bool``）

スケールを表示するかどうかのフラグです。true で有効、false で無効です。

```c++
tpp.scale.enable=true;
```

### [x or y].point（型：``double``）

スケールの文字のサイズ。x,y で別個に設定可。

```cpp
tpp.scale.x.point=8.0;
```

### [x or y].length（型：``double``）

スケールバーの長さ(cm)。x,y で別個に設定可。サブのスケールバーはこの長さの半分になる。

```cpp
tpp.scale.x.length=0.1;
```

### [x or y].interval（型：``uint16_t``）

スケールのバーの間隔を調整できるが値だが、ちょっと調整が難しいかもしれない（バーの本数を表す値ではないのでは注意）。$0$ は自動を意味する。x,y で別個に設定可。

```cpp
tpp.scale.x.interval=0;
```

### [x or y].grid（型：``bool``）

未実装。

### [x or y].arg（型：``cptp::Scale::Arg``）

スケールの取り方を調整値。現在は通常のスケールと、対数スケールが実装されている。x,y で別個に設定可。デフォルトは ``cptp::Scale::DECIMAL`` で値は 0. が設定。

通常の場合は ``cptp::DECIMAL`` を用いれば良く、double型の値はスケールが刻む時に通って欲しい値となる（例えば、スケールが 1.0 間隔で、-0.5, 0.5を通っている時、値に 0.0 を指定すると -1.0, 0.0, 1.0を通る様にすることができる）。若干バグるかも...

```c++
tpp.x.arg.construct(cptp::Scale::DECIMAL, 0.);
```

対数スケールの場合は ``cptp::LOG`` を用い、底の値と底の変数名を指定できる。底の変数名が空文字列（``""``）である場合は、数字を底の名前として出力する。

```c++
tpp.x.arg.construct(cptp::Scale::LOG, cptp::Scale::Log(2, ""));
```

この例のようにすると2を底とする対数グラフとなり、スケールの値が 2ⁿ の様に変更される。``construct`` 関数を呼び出し、第１引数を ``cptp::Scale::LOG`` （列挙体整数値）、第２引数に ``cptp::Scale::Log`` 型（``double``型と ``std::string`` 型の組、実体は ``gd::ElasticTuple<double, std::string>`` ）の値を入れる必要があることに注意。

## key

凡例全体の設定です。個別のプロットの名前に関しては、``ProtSpec``型の ``tag`` を変更して下さい。 

### enable（型：``bool``）

凡例を表示するかどうかのフラグです。true で有効、false で無効です。

```c++
tpp.key.enable=true;
```

### position（型：``cptp::Position``）

凡例の出力位置を調整する値だが、NxM のプロットのどこに出力するかは選べず、全てのプロットの内、一番スペースが空いてそうな所に出力される（いつか改善されるかも）。プロットのどの角に寄せるかという指定と、プロットの角から凡例の矩形の角までのオフセット(cm)を設定できる。プロットの４つ角は ``cptp::Position::Base`` 型の列挙体値で表され、

- ``cptp::Position::AUTO``
- ``cptp::Position::RIGHT_TOP``
- ``cptp::Position::LEFT_TOP``
- ``cptp::Position::RIGHT_BOTTOM``
- ``cptp::Position::LEFT_BOTTOM``

から選択可能。 

```c++
tpp.key.position(cptp::Position::AUTO, cptp::Vec2(0.2, 0.2));
```

4つ角の指定は自動で、角から 0.2 の間を開ける場合の設定。``tpp.key.postion.base`` と ``tpp.key.position.disp`` でそれぞれ個別に設定可。プロットと重なったりして気に食わない場合、Latexファイルを直接編集してkeyを動かす方が楽かも知れません。

### point（型：``float``）

凡例で表示する名前の文字のポイントサイズ(pt)です。

```c++
tpp.key.point=5.0;
```

### margin（型：``float``）

凡例の矩形と凡例のプロット線や文字の間のマージン(cm)です。

```c++
tpp.key.point=0.15;
```

### interval（型：``float``）

n 個目の凡例と n+1 個目の凡例の間の縦方向の隙間の大きさ(cm)です。

```c++
tpp.key.point=0.05;
```

## range

### min（型：``scalar``）

プロットする最小値を表します。x,y で別個に設定可能。デフォルトは``std::numeric_limits<scale>::max()`` です。この値の場合はプロット作成時の全てデータの点の内で最も小さい値が最小値になります。

```c++
tpp.range.x.min=0.;
```

### max（型：``scalar``）

プロットする最大値を表します。x,y で別個に設定可能。デフォルトは``-std::numeric_limits<scale>::max()`` です。この値の場合はプロット作成時の全てデータの点の内で最も大きい値が最大値になります。

```c++
tpp.range.x.max=0.;
```

## plot_spec

プロットに関する設定の為の値です。``TabParPlots``型 は NxM のテーブルがあり、それぞれ各セルに P 個（以下）のプロットがある時に、各プロットに対応する P 個の ``PlotSpec``型の値を持ちます。アクセスは ``plot_spec``関数で行うか、``setPlotSpec``関数で``PlotSpec``型の値を直接代入できます。

### tag（型：``std::string``）

凡例に表示するプロット名です。デフォルト（空文字列）の場合は 0 から順に数字が入ります。

```c++
tpp.plot_spec(p).tag="";
```

### color（型：``cptp::Color``）

プロットの色です。自動、IDから指定、RGBから指定の三種類の設定方法があります。デフォルトは自動です。変更は ``construct`` 関数を用います。線（``line``）や点（``point``）の方で自動以外に色が設定されている場合はそちらが優先されます。

自動に設定。

```c++
tpp.plot_spec(p).color.construct();
```

IDから設定。

```c++
tpp.plot_spec(p).color.construct(cptp::Color::RED);
```

IDは``cptp::Color::ID``型の列挙体で、``RED, GREEN, BLUE, VIOLET, OLIVE, ORANGE, TEAL, BROWN, PURPLE, DARKGRAY, MAGENTA, GRAY, PINK, LIME, BLACK, YELLOW, CYAN, LIGHTGRAY`` から選択できます。自動の場合も順に先頭からこの色を使います。

RGBから色を (255,0,0) に設定。

```c++
tpp.plot_spec(p).color.construct(255, 0, 0);
```

または、

```c++
tpp.plot_spec(p).color.construct(cptp::RGB(255, 0, 0));
```

（RGBテストした覚えがないのが、これちゃんと動くんかな....）

### line（型：``cptp::Line``）

プロットの線の設定です。さらに細かい設定があります。

#### enable（型：``bool``）

プロットに線を利用するかどうかのフラグです。``true``で有効、``false`` で無効で、デフォルトは ``true`` です。点だけを打ちたい場合は線を ``false`` にして、点を ``true`` にします。

```c++
tpp.plot_spec(p).line.enable=true;
```

#### color（型：``cptp::Color``）

``plot_spec`` の``color`` と同様なので割愛。

#### width（型：``cptp::Width``）

プロットの線の太さの設定値です。tikzの線の太さの設定に準拠します。``cptp::Line::Width``型の列挙体で表現され、``SEMI_THICK, ULTRA_THIN, VERY_THIN, THIN, THICK, VERY_THICK, ULTRA_THICK`` から選択できます。デフォルトは ``SEMI_THICK`` です。

```c++
tpp.plot_spec(p).line.width=cptp::Line::SEMI_THICK;
```

#### dot（型：``cptp::Dot``）

プロットの線の破線などの設定値です。tikzの線の破線などの設定に準拠します。``cptp::Line::Dot``型の列挙体で、``SOLID, LOOSELY_DOTTED, DOTTED, DENSELY_DOTTED, LOOSELY_DASHED, DASHED, DENSELY_DASHED, 
            LOOSELY_DASH_DOT, DASH_DOT, DENSELY_DASH_DOT, LOOSELY_DASH_DOT_DOT, DASH_DOT_DOT, DENSELY_DASH_DOT_DOT`` から選択できます。デフォルトは ``SOLID`` です。

```c++
tpp.plot_spec(p).line.dot=cptp::Line::SOLID;
```

（線の引き方の都合で、点線などはきれいに表記されない可能性が高いです。治そうと思ってます）

#### option（型：``std::string``）

プロットの線の追加設定で、文字列で取り扱います。デフォルトは空文字列です。tikzの線の``[]`` 内に ``option`` の内容がそのまま貼付されます。例えば、線の透明度を0.5にしたい場合は次のようにします。

```c++
tpp.plot_spec(p).line.option="opacity=0.5";
```

### point（型：``cptp::Point``）

プロットの点の設定です。さらに細かい設定があります。

#### enable（型：``bool``）

プロットに点を利用するかどうかのフラグです。``true``で有効、``false`` で無効で、デフォルトは ``false`` です。

```c++
tpp.plot_spec(p).point.enable=false;
```

#### color（型：``cptp::Color``）

``plot_spec`` の``color`` と同様なので割愛。

#### size（型：``double``）

プロットの点の大きさ(pt)です。点には文字がそのまま利用されるため、単位はptです。デフォルトは 8.0 pt です。

```c++
tpp.plot_spec(p).point.size=8.0;
```

#### shape（型：``std::string``）

プロットの点の形です。Latexで使える文字をそのまま用いることができます。デフォルトは ``"$\\bullet$"`` で、塗りつぶされた丸い点です。例えば、バツ印にしたければ、``"$\\times$"`` などを用います。（あくまで文字なので、内部で多少位置を補正している場合があります。よく使いそうもないやつは試してないので少しずれるかも...）

```c++
tpp.plot_spec(p).point.shape="$\\bullet$";
```

#### option（型：``std::string``）

プロットの点の追加設定です。tikzの点に用いる文字付きノートの``[]`` 内に ``option`` の内容がそのまま貼付されます。デフォルトは空文字列です。

```c++
tpp.plot_spec(p).point.option="";
```

## title

プロットテーブルの各セルに設置する副題の設定の為の値です。``TabParPlots``型 は NxM のテーブルがあり、それぞれ各セルに P 個（以下）のプロットがある時に、各セルに対応する NxM の ``Title``型の値を持ちます。``title``関数でアクセスを行うか、``setDatas`` 関数の第４引数に``cptp::Title``型の値を直接代入することができます。

### string（型：``std::string``）

テーブルの各セルにつく副題の文字列です。デフォルト（空文字列）の場合は (n,m) の様にセルIDが振られます。

```c++
tpp.title(n, m).string="";
```

### position（型：``cptp::Position``）

テーブルの各セルにつく副題の位置です。デフォルト（空文字列）の場合は (n,m) の様にセルIDが振られます。

```c++
tpp.title(n, m).position="";
```

プロットのどの角に寄せるかという指定と、プロットの角から凡例の矩形の角までのオフセット(cm)を設定できる。プロットの４つ角は ``cptp::Position::Base`` 型の列挙体値で表され、``AUTO, RIGHT_TOP, LEFT_TOP, RIGHT_BOTTOM, LEFT_BOTTOM`` 


（力尽きた...）
