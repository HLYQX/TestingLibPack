#ifndef TESTUTILITIES_H
#define TESTUTILITIES_H
#include "stdafx.h"
#include "Utilities.h"

/**
* @brief 测试cout输出浮点数
*/
void test_coutFloat();

/**
* @brief 测试cout输出文本
*/
void test_coutText();

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
* @brief 测试cpp写H5文件
*/
void test_HDF5Write();

/**
* @brief 测试cpp读H5文件
*/
void test_HDF5Read();
#endif