#ifndef GROUPDATA_HPP
#define GROUPDATA_HPP

#include <iostream>

#ifdef GROUPDATA_EXCEPTION
    #define GROUPDATA_GROUP_EXCEPTION
    #define GROUPDATA_TUPLE_EXCEPTION
    #define GROUPDATA_ARRAY_EXCEPTION
    #define GROUPDATA_VECTOR_EXCEPTION
    #define GROUPDATA_LIST_EXCEPTION
    #define GROUPDATA_VIEW_EXCEPTION
    #define GROUPDATA_BRIDGE_EXCEPTION
    #define GROUPDATA_BANDLE_EXCEPTION
    #define GROUPDATA_TABLE_EXCEPTION
#endif

#ifdef GROUPDATA_WARNING
    #define GROUPDATA_GROUP_WARNING
    #define GROUPDATA_TUPLE_WARNING
    #define GROUPDATA_ARRAY_WARNING
    #define GROUPDATA_VECTOR_WARNING
    #define GROUPDATA_LIST_WARNING
    #define GROUPDATA_VIEW_WARNING
    #define GROUPDATA_BRIDGE_WARNING
    #define GROUPDATA_BANDLE_WARNING
    #define GROUPDATA_TABLE_WARNING
#endif

//#include "./function.hpp"


namespace gd{

    //+    Namespace Variable    +//
    // groupdata.hpp groupdata.cpp
    extern size_t _format_length_;

    
}
    
#include "gd1/groupdata.hpp"
#include "gd1/group.hpp"
#include "gd1/tag.hpp"
#include "gd1/tuple.hpp"
#include "gd1/alternative.hpp"
#include "gd1/array.hpp"
#include "gd1/vector.hpp"
#include "gd1/list.hpp"
#include "gd1/view.hpp"
#include "gd1/bridge.hpp"
#include "gd1/bandle.hpp"
#include "gd1/table.hpp"

#endif
