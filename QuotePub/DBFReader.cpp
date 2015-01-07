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
	
	parseDBFHeader(buf);

	parseFields(buf);

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
	memset(&dbfHeader, 0x00, sizeof(dbfHeader));

	
	memcpy(&dbfHeader.fileType, buf + offset, 1);
	offset += 1;

	
	memcpy(dbfHeader.latestUpdateTime, buf + offset, sizeof(dbfHeader.latestUpdateTime));
	offset += sizeof(dbfHeader.latestUpdateTime);

	
	memcpy(&dbfHeader.records, buf + offset, sizeof(dbfHeader.records));
	offset += sizeof(dbfHeader.records);

	

	
	memcpy(&dbfHeader.firstRecordOffset, buf + offset, sizeof(dbfHeader.firstRecordOffset));
	offset += sizeof(dbfHeader.firstRecordOffset);

	

	
	memcpy(&dbfHeader.recordLength, buf + offset, sizeof(dbfHeader.recordLength));
	offset += sizeof(dbfHeader.recordLength);
	
	
	
}

void DBFReader::parseFields(char * buf)
{
	int fieldTotalLen = dbfHeader.firstRecordOffset - DBF_HEADER_SIZE - 1; // 最后一个1代表0x0D
	int fieldCount = fieldTotalLen / FIELD_DEFINE_SIZE;
	int offset = DBF_HEADER_SIZE;

	for (int i=0; i<fieldCount; i++)
	{
		FIELD field;

		memcpy(field.name, buf + offset, sizeof(field.name));
		offset += sizeof(field.name);

		memcpy(&field.type, buf + offset, sizeof(field.type));
		offset += sizeof(field.type);

		memcpy(&field.offset, buf + offset, sizeof(field.offset));
		offset += sizeof(field.offset);

		memcpy(&field.length, buf + offset, sizeof(field.length));
		offset += sizeof(field.length);

		memcpy(&field.decimal, buf + offset, sizeof(field.decimal));
		offset += sizeof(field.decimal);

		memcpy(&field.reserved, buf + offset, sizeof(field.reserved));
		offset += sizeof(field.reserved);

		fields.push_back(field);
	}

	for (auto field : fields)
	{
		TRACE("字段名字%s", field.name);
		TRACE("\t字段类型%c", field.type);
		TRACE("\t字段长度%d", field.length);
		TRACE("\t字段小数位数%d", field.decimal);
		TRACE("\n");
	}	
}
