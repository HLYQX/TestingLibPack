#include "stdafx.h"
#include "TestUtilities.h"





void main()
{
	//test_coutFloat();
	//test_coutText();
	//test_clock();
	//test_pInV();
	//test_map();
	//test_Eigen340();
	
	// C++写HDF5
	cout << "C++写 HDF5" << endl;
	MatrixXi TestEigenRand(2, 3);
	//TestEigenRand.setRandom();
	TestEigenRand << 50, 40, 30,
		25, 26, 24;
	ofstream a("TestEigenRand.txt");
	a << TestEigenRand << endl;
	a.close();

	const int NumRow = TestEigenRand.rows();
	const int Numcol = TestEigenRand.cols();

	int data[2][3];
	int(*pdata)[3] = data;
	for (int i = 0; i < NumRow; i++)
	{
		for (int j = 0; j < Numcol; j++)
		{
			data[i][j] = TestEigenRand(i, j);
			cout << data[i][j] << '\t';
		}
		cout << endl;
	}

	H5File TestCppH5Write("Test.h5", H5F_ACC_TRUNC);

	IntType TestCppH5DataType(PredType::NATIVE_INT);
	TestCppH5DataType.setOrder(H5T_ORDER_LE);
	//TestCppH5DataType.setOrder(H5T_ORDER_BE);

	hsize_t TestCppH5Dims[2];
	TestCppH5Dims[0] = 2;
	TestCppH5Dims[1] = 3;
	DataSpace DataSpaceTestCppH5Write(2, TestCppH5Dims);

	Group TestCppH5Group = TestCppH5Write.createGroup("GroupRand");
	TestCppH5Group = TestCppH5Group.createGroup("GroupRand2");
	//加上“/”会使得DataSet创建在根目录下
	DataSet* dset = new DataSet(TestCppH5Group.createDataSet("RandData3", TestCppH5DataType, DataSpaceTestCppH5Write));
	DataSet TestCppH5DataSet1 = (&TestCppH5Group)->createDataSet("/RandData1", TestCppH5DataType, DataSpaceTestCppH5Write);
	DataSet TestCppH5DataSet2 = TestCppH5Group.createDataSet("RandData2", TestCppH5DataType, DataSpaceTestCppH5Write);
	TestCppH5DataSet1.write(pdata, PredType::NATIVE_INT);
	TestCppH5DataSet2.write(pdata, PredType::NATIVE_INT);
	dset->write(pdata, PredType::NATIVE_INT);
	TestCppH5Write.close();

	// C++读HDF5
	cout << "C++读 HDF5" << endl;
	H5File TestCppH5Read("Test.h5", H5F_ACC_RDONLY);
	TestCppH5DataSet1 = TestCppH5Read.openDataSet("/RandData1");
	TestCppH5DataSet1.read(pdata, TestCppH5DataType);
	for (int i = 0; i < NumRow; i++)
	{
		for (int j = 0; j < Numcol; j++)
		{
			cout << pdata[i][j] << '\t';
		}
		cout << endl;
	}
	TestCppH5Read.close();

	//Test QString W
	cout << "Test QString W" << endl;
	QString QStrWrite = "QStrWrite";
	cout << QStrWrite.toStdString() << endl;

	QFile QFileWrite("QFileWrite.txt");
	QFileWrite.open(QFile::WriteOnly | QFile::Truncate);
	//QFileWrite.write(QStrWrite.toLatin1());


	QTextStream QTextStreamWrite(&QFileWrite);
	QTextStreamWrite << QStrWrite + "20231023" << endl;
	QTextStreamWrite << ToQString(Matrix3d::Random()) << endl;
	//for (int i = 0; i < TestEigenRand.rows(); i++)
	//{
	//	for (int j = 0; j < TestEigenRand.cols(); j++)
	//	{
	//		QTextStreamWrite << TestEigenRand(i, j) << "\t";
	//	}
	//	QTextStreamWrite << endl;
	//}
	QFileWrite.close();

	//Test QString R
	cout << "Test QString R" << endl;
	QFile QFileRead("QFileWrite.txt");
	QFileRead.open(QFile::ReadOnly);
	QTextStream QTextStreamRead(&QFileRead);
	QString QStrRead;
	//QTextStreamRead >> QStrRead;
	//QStrRead = QTextStreamRead.readLine();
	QStrRead = QTextStreamRead.readAll();
	cout << QStrRead.toStdString();
	QFileRead.close();

	//Test pInv
	//Matlab Reference Result:
	Matrix<char, 4, 3>TestpInv;
	TestpInv << 1, 0, 0,
		5, 1, -1,
		1, 0, 0,
		2, 1, -1;
	//TestpInv.setZero();
	//cout << pInv(TestEigenRand) << endl;
	cout << TestpInv << endl;
	Matrix<double, Dynamic, Dynamic>TestpInvd;
	TestpInvd.resize(TestpInv.rows(), TestpInv.cols());
	TestpInvd.setZero();
	


	/*
	//system("pause");
	*/


	
	//SetConsoleCP(65001);
	qDebug() << QString("给个第三方") << endl;
	qDebug() << QString("给个第三方").toUtf8() << endl;
}

