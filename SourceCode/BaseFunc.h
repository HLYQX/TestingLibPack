#ifndef BASEFUNC_LIBRARY_H
#define BASEFUNC_LIBRARY_H
#include "stdafx.h"

using namespace std;
using namespace Eigen;
using namespace H5;

/**
* @brief MatrixXd 转化为 QString
* @param [M]  MatrixXd 类型数据
* @param [prec]  保留的有效位数
*/
QString		ToQString(const MatrixXd& M, int prec = 6);

/**
* @brief vector<int> 转化为 QString
* @param [V]  vector<int> 类型数据
*/
QString		ToQString(const vector<int>& V);

/**
* @brief 以文本文档形式保存列阵
* @param [Path]  文件路径
* @param [V]  列阵
*/
bool    saveVectorFile(QString Path, Eigen::VectorXd V);

/**
* @brief 从文本文件中加载列阵
* @param [Path]  文件路径
* @param [V]  列阵
*/
bool	loadVectorFile(QString Path, Eigen::VectorXd& V);

/**
* @brief 从文本文件中加载矩阵
* @param [Path]  文件路径
* @param [M]  列阵
* @param [S]  分割符
*/
bool	loadMatrixFile(QString Path, MatrixXd& M, QString S = QLatin1String(" "));

#endif