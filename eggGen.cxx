//************************MASS: eggGen*******************
// Monarch Program to convert MASS data files to
// .egg format used by Katydid for analysis
// Author:	Prajwal Mohanmurthy (prajwal@mohanmurthy.com)
//		NuDM Group
//		Laboratory for Nuclear Science, MIT
//
#include<iostream>
#include<fstream>
#include<Monarch.hpp>

using namespace std;
using namespace monarch;

int main()
{
	cout<<"===============eggGen:Begin==============\n";

	const int eggGenRecordSize = 33; // Set the number of entries (rows) in the DASY lab file
	const int eggGenRecordTime = 33000000; //Set this to the entire length in time DASY lab file in ns = 1M X eggGenRecordSize
	fstream eggGenDASY;
	eggGenDASY.open("test.txt", ios::in|ios::out); // Set file name of the DASY Lab file >""

	cout<<"===============eggGen:Init===============\n";

	cout<<"eggGen:Creating eggGen.egg\n";
	Monarch* eggGenInit = monarch::Monarch::OpenForWriting("eggGen.egg");
	MonarchHeader* eggGenHeader= eggGenInit->GetHeader();

	cout<<"eggGen:Setting headers for eggGen.egg\n";
	eggGenHeader->SetFilename("eggGen.egg");
	eggGenHeader->SetFormatMode(sFormatSingle);
	eggGenHeader->SetAcquisitionMode(sOneChannel);
	eggGenHeader->SetAcquisitionRate(.001); //in KHz; DAQ Write Rate (=1KHz for MASS)
	eggGenHeader->SetRunDuration(eggGenRecordTime/1000000);
	eggGenHeader->SetRecordSize(eggGenRecordSize);
	eggGenHeader->SetVoltageMin(-5.0);
	eggGenHeader->SetVoltageRange(10.0);

	cout<<"eggGen:Writing headers for eggGen.egg\n";
	eggGenInit->WriteHeader();

	cout<<"=====eggGen:Reading DASYLab File=========\n";
	uint64_t eggGenDASYData;
	if (eggGenDASY.is_open())
	{
		cout<<"eggGen:Succesfully opened DASY Lab Data file\n";
		int eggGenDASYbeg = eggGenDASY.tellg();
		eggGenDASY.seekg(0, ios::end);
		int eggGenDASYend = eggGenDASY.tellg();
		eggGenDASY.seekg(0, ios::beg);
		cout<<"eggGen:Size of DASY Lab data file (in bytes)= "<<eggGenDASYend - eggGenDASYbeg<<"\n";
	}
	cout<<"=====eggGen:Writing to .egg File=========\n";
	MonarchRecordBytes* eggGenRecord = eggGenInit->GetRecordSeparateOne();
	eggGenRecord->fAcquisitionId = 1;
	eggGenRecord->fRecordId = 1;
	eggGenRecord->fTime = eggGenRecordTime;

	for(int i = 1; i<=eggGenRecordSize; i++)
	{
		eggGenDASY>>eggGenDASYData;
		//cout<<"Test:"<<eggGenDASYData<<"\n";
		eggGenRecord->fData[i-1] = (uint8_t)eggGenDASYData;
	}

	cout<<"eggGen:Finishing writing eggGen.egg\n";
	eggGenInit->WriteRecord();

	cout<<"eggGen:Closing eggGen.egg\n";
	eggGenInit->Close();

	cout<<"===============eggGen:Ending=============\n";
	return 0;
}
