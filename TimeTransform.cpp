#include <time.h>

#include "Functions.h"
//将烹饪所需时间转化为烹饪完成所在的时刻
void TimeTransform(int* plushour,int* plusminute,int Time) {
    time_t t;
    time(&t); // 获取当前的时间戳
    tm *localTime = localtime(&t);// 将时间戳转换为本地时间
        if(localTime->tm_min + Time >= 60) {
            *plushour = (localTime->tm_min + Time) / 60;
            *plusminute =  Time - *plushour * 60;

        }else {
            *plusminute = Time;

        }

}