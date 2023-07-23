#include <cptp/forward.hpp>

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{



    //------------------------//
    //    Function Definition    //
    //------------------------//
    double pointToCenti(const double point_){
    
        return point_*0.03528;   
    }

    double CentiToPoint(const double centi_){

        return centi_*28.3;
    }

}

