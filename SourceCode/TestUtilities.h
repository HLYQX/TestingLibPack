#ifndef TESTUTILITIES_H
#define TESTUTILITIES_H
#include "stdafx.h"
#include "Utilities.h"

/**
* @brief 测试main函数（主程序）入参
*/
void test_argInMain(int argc, char* argv[]);

/**
* @brief 测试cout输出浮点数
*/
void test_coutFloat();

/**
* @brief 测试cout输出文本
*/
void test_coutText();

/**
* @brief 测试Qt读写文本
*/
void test_QtReadWrite();

/**
* @brief 测试clock_t计时
*/
void test_clock();

/**
* @brief 测试pInv
*/
void test_pInV();

/**
* @brief 测试map容器
*/
void test_map();

/**
* @brief 测试Eigen3.4.0
*/
void test_Eigen340();

/**
* @brief 测试transformStorageOrder函数
*/
void test_transformStorageOrder();

/**
* @brief 测试cpp写H5文件(用c++多维数组)
*/
void test_HDF5WriteCppArray();

/**
* @brief 测试cpp写H5文件(用Eigen)
*/
void test_HDF5WriteMatrixXd();

/**
* @brief 测试cpp读H5文件(用c++多维数组)
*/
void test_HDF5ReadCppArray();

/**
* @brief 测试cpp读H5文件(用Eigen)
*/
void test_HDF5ReadEigen();

/**
* @brief 测试Qt写xml文件
*/
void test_QtXmlWrite();

/**
* @brief 测试Qt读xml文件
*/
void test_QtXmlRead();

/**
* @brief 测试Qt修改xml文件
*/
void test_QtXmlModify();

#endif