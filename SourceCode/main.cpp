#include "stdafx.h"
#include "TestUtilities.h"





int main(int argc, char* argv[])
{
	//test_argInMain(argc, argv);
	//test_coutFloat();
	//test_coutText();
	//test_QtReadWrite();
	//test_clock();
	//test_pInV();
	//test_map();
	//test_Eigen340();
	//test_transformStorageOrder();
	//test_HDF5WriteCppArray();
	//test_HDF5WriteMatrixXd();
	//test_HDF5ReadCppArray();
	//test_HDF5ReadEigen();
	//test_QtXmlWrite();
	//test_QtXmlRead();
	//test_QtXmlModify();


	/// 打印块信息
	printBlockInfo("main()");

	/// 中文输出测试
	cout << "中文输出测试" << endl;
	qDebug() << "中文输出测试" << endl;
	qDebug() << QString("中文输出测试") << endl;
	cout << QString("中文输出测试").toStdString() << endl;

	return 0;
}

