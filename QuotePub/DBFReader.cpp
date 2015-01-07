#include "stdafx.h"
#include "DBFReader.h"


DBFReader::DBFReader(void)
{
}


DBFReader::~DBFReader(void)
{
}


bool DBFReader::readDBF(std::string DBFFile)
{
	bool ret = false;
	DWORD fileSize = 0;
	char * buf;
	DWORD numberOfBytesRead = 0;

	HANDLE hFile = ::CreateFile(DBFFile.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return ret;
	}

	
	fileSize = ::GetFileSize(hFile, NULL);
	if (fileSize == 0)
	{
	}
	
	buf = new char[fileSize];
	ret = ReadFile(hFile, buf, fileSize, &numberOfBytesRead, NULL);
	
	CloseHandle(hFile);
	
	

	return ret;
}

bool DBFReader::parseShow2003()
{
	bool ret = false;

	return ret;
}

void DBFReader::parseDBFHeader(char * buf)
{
	int offset = 0;

	byte fileType;
	memcpy(&fileType, buf + offset, 1);
	offset += 1;

	char latestUpdateTime[3];
	memcpy(&latestUpdateTime, buf + offset, sizeof(latestUpdateTime));
	offset += sizeof(latestUpdateTime);

	char records[4];
	memcpy(&records, buf + offset, sizeof(records));
	offset += sizeof(records);

	int n;
	memcpy(&n, records, sizeof(records));

	char firstRecordOffset[2];
	memcpy(&firstRecordOffset, buf + offset, sizeof(firstRecordOffset));
	offset += sizeof(firstRecordOffset);

	short pos;
	int t = sizeof(short);
	memcpy(&pos, firstRecordOffset, sizeof(firstRecordOffset));

	char recordLength[2];
	memcpy(&recordLength, buf + offset, sizeof(recordLength));
	offset += sizeof(recordLength);
	short recordLen;
	
	memcpy(&recordLen, recordLength, sizeof(recordLength));

	dbfHeader.records;
}

void DBFReader::parseFields(char * buf)
{
}
