#include "stdafx.h"
#include "TestUtilities.h"





void main()
{
	test_coutFloat();
	test_coutText();
	test_clock();
	test_pInV();
	
	//C++map
	cout << "C++map" << endl;
	map <int, char> Alphabet;
	int Key[26] = {};
	char Value[26] = {};
	for (int i = 0; i < 26; i++)
	{
		Key[i] = i;
		Value[i] = 65 + i;
		//cout << Key[i] << '\t' << Value[i] << endl;
		Alphabet.insert(pair<int, char>(Key[i], Value[i]));
	}
	for (auto& it : Alphabet)
	{
		cout << it.first << ' ' << it.second << endl;
	}

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


	//Eigen 3.40
	MatrixXd Aa = MatrixXd::Zero(20, 20);
	Aa.diagonal().setLinSpaced(0, 20 - 1);
	Aa(0, all).setLinSpaced(0, 20 - 1);
	Aa(all, 0).setLinSpaced(0, 20 - 1);
	cout << "Aa\n" << Aa << endl;
	cout << "Aa(seqN(1, 5), {1,2,3,4,5})\n" << Aa(seqN(1, 5), { 1,2,3,4,5 }) << endl;
	cout << "Aa(seq(1, 5), {1,2,3,4,5})\n" << Aa(seq(1, 5), { 1,2,3,4,5 }) << endl;
	cout << "Aa(seq(5, 1, -1), { 5,4,3,2,1 })\n" << Aa(seq(5, 1, -1), { 5,4,3,2,1 }) << endl;
	cout << "Aa(seq(5, 1, -1), seq(5, 1, -1))\n" << Aa(seq(5, 1, -1), seq(5, 1, -1)) << endl;
	cout << "Aa(seq(5, 1, -1).reverse(), seq(5, 1, -1).reverse())\n" << Aa(seq(5, 1, -1).reverse(), seq(5, 1, -1).reverse()) << endl;
	cout << "Aa({ 5,4,3,2,1 }, { 5,4,3,2,1 })\n" << Aa({ 5,4,3,2,1 }, { 5,4,3,2,1 }) << endl;
	cout << "Aa(seqN(1, 3, 2), { 1,3,5 })\n" << Aa(seqN(1, 3, 2), { 1,3,5 }) << endl;
	cout << "Aa(seq(1, 5, 2), { 1,3,5 })\n" << Aa(seq(1, 5, 2), { 1,3,5 }) << endl;
	cout << "Aa(all, last/2)\n" << Aa(all, last / 2) << endl;
	cout << "Aa(all, lastN(2))\n" << Aa(all, lastN(2)) << endl;
	cout << "Aa(all, lastN(5,2))\n" << Aa(all, lastN(5,2)) << endl;
	cout << "VectorXd::Unit(20, 5)\n" << VectorXd::Unit(20, 5) << endl;

	MatrixXd A(10, 5);               //  10x5  matrix.
	A.setConstant(NoChange, 10, 2);  //  10x10 matrix of 2s.
	cout << A << endl;
	A.setConstant(5, NoChange, 3);   //  5x10 matrix of 3s.
	A.setZero(NoChange, 20);         //  5x20 matrix of 0s.
	A.setZero(20, NoChange);         //  20x20 matrix of 0s.
	A.setOnes(NoChange, 5);          //  20x5  matrix of 1s.
	A.setOnes(5, NoChange);          //  5x5  matrix of 1s.
	A.setRandom(NoChange, 10);       //  5x10 random matrix.
	A.setRandom(10, NoChange);       //  10x10 random matrix.
	cout << A << endl;
	for (auto& x : A.rowwise()) { 
		int IndexMax;
		x.maxCoeff(&IndexMax);
		x = x.sum() * VectorXd::Unit(10, IndexMax);
	}
	cout << A << endl;

	for (auto x : VectorXd::Unit(20, 5)) {
		cout << x << " ";
	}
	cout << endl;
	//SetConsoleCP(65001);
	qDebug() << QString("给个第三方") << endl;
	qDebug() << QString("给个第三方").toUtf8() << endl;
}

