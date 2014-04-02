#ifndef PATARAMETER_H
#define PATARAMETER_H

//#include <gl/GL.h>
///////声明全局参数变量////////

//extern double _height;
extern bool ChooseProjection;//选择投影方式
extern bool DrawData;//是否加载指标
extern int IndexStyle;//加载指标类型
extern double ChinaHeight1;//中国DEM高度
extern float C1[], C2[], C3[], C4[], C5[];//设置中国DEM颜色系列
extern int ChartDate[11];//指标数据
extern bool ChinaLadder;//是否画阶梯状图

#endif