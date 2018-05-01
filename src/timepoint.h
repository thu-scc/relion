#pragma once

#include "time.h"
#include "mpi.h"
#include <iostream>
#include <cstdio>

using namespace std;

#define TIME_POINT_INIT(tag) \
    TimeStamp __t##tag; \
    int __rank##tag; \
    MPI_Comm_rank(MPI_COMM_WORLD, &__rank##tag); \
    char __rankstr##tag[100]; \
    sprintf(__rankstr##tag, "%02d", __rank##tag); \
    annotate_time(&__t##tag);

#define TIME_POINT(tag) \
{ \
    /*if (__rank##tag == 0 || __rank##tag == 1)*/ \
    { \
        std::cout << "[TIME" << __rankstr##tag << "] " << elapsed_time(__t##tag) << " " << "t" #tag << " " << __FILE__ << ":" << __LINE__ << std::endl; \
        annotate_time(&__t##tag); \
    } \
}

#define TIME_COUT(tag) (cout << "[COUT" << __rankstr##tag << "]" << __LINE__ << " ")

//#define TIME_POINT_CLOSE { closed_cnt ++; }
//#define TIME_POINT_OPEN { if (closed_cnt) closed_cnt --; }

