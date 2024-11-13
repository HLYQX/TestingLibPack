#ifndef UTILITIES_H
#define UTILITIES_H
#include "stdafx.h"
#include "BaseFunc.h"

/**
* @brief SVD分解求MatrixXd的M-P逆
* @param [A]  待求M-P逆的矩阵
* @param [epsilon]  保留的有效位数
*/
MatrixXd pInv_SVD(const MatrixXd& A, double epsilon = std::numeric_limits<double>::epsilon());

/**
* @brief Greville列递推法求解MatrixXd的M-P逆
* @param [A]  待求M-P逆的矩阵
*/
MatrixXd pInv_Greville(const MatrixXd& A);

/**
* @brief 在控制台中用带颜色的字符显示true和false
* @param [YN]  传入的bool型变量
*/
void printBoolWithColor(bool YN);

/**
* @brief 在控制台中打印带颜色的字符
* @param [Str]  传入的字符串
* @param [ColorForeGround]  字体颜色
* @param [ColorBackGround]  背景颜色
*/
void printStrWithColor(const string& Str, const int& ColorForeGround, const int& ColorBackGround, bool FlagIntensity = true);

/**
* @brief 块信息打印
* @param [YN]  块名
*/
void printBlockInfo(const string& BlockName);

#endif