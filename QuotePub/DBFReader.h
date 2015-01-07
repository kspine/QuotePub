#ifndef DBF_READER_H
#define DBF_READER_H

#include <vector>
#include <string>

//http://wenku.baidu.com/link?url=Ey8JKiQv58J7NQ9XVI9Hi4xRMkTFK4PS2ZKQ7hQgjRE9L2dLcD88JyjBzkhCR6c-0MiqWaByqEyyJmsXFBLig5lpsxVIgHpUZYOuq8yQNba
//http://blog.sina.com.cn/s/blog_627e00500100gpmp.html

typedef struct DBF_Header
{
	byte fileType;  // �ļ�����
	char latestUpdateTime[3]; // ���һ�θ���ʱ��YYMMDD

	int records; //��¼��
	short firstRecordOffset; //�ļ��е�һ�����ݼ�¼��λ��
	short recordLength; // ��¼�ĳ���
	char reserved[20]; // ����
}DBF_HEADER;

#define DBF_HEADER_SIZE 32

typedef struct field
{
	char name[11]; // �ֶ���,���10���ַ�
	char type; // �ֶ�����
	int offset; //�ֶ��ڼ�¼�е�ƫ����
	byte length; // �ֶγ���
	byte decimal; // С��λ��
	char reserved[14]; // ����
}FIELD;
#define FIELD_DEFINE_SIZE 32

typedef struct record
{
	char name[11];
}RECORD;

/*
0.�����ļ��䶯
1.���ļ�
2.�������
3.���߳̽���
4.��������

�ļ�ͷ32 + �ֶζ���32*�ֶ��� + 0x0D + ���ݼ�¼*��¼��
ÿ����¼�ĵ�һ���ֽ����Ϊ�Ǻ�(0x2A)����ɾ����¼���ո�(0x20)����������¼
*/

class DBFReader
{
public:
	DBFReader(void);
	~DBFReader(void);

	
	

	bool readDBF(std::string DBFFile);
	bool parseShow2003();
	bool parseSjshq();

	DBF_HEADER dbfHeader;
	std::vector<FIELD> fields;
	std::vector<RECORD> records;

	void parseDBFHeader(char * buf);
	void parseFields(char * buf);
};

#endif
