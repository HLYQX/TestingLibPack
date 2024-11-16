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
	//test_transformStorageOrder();
	test_HDF5WriteCppArray();
	test_HDF5WriteMatrixXd();
	test_HDF5Read();
	
	

	

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

	//SetConsoleCP(65001);
	qDebug() << QString("给个第三方") << endl;
	qDebug() << QString("给个第三方").toUtf8() << endl;
}

