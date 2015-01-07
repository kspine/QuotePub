#ifndef DBF_READER_H
#define DBF_READER_H

#include <vector>
#include <string>

//http://wenku.baidu.com/link?url=Ey8JKiQv58J7NQ9XVI9Hi4xRMkTFK4PS2ZKQ7hQgjRE9L2dLcD88JyjBzkhCR6c-0MiqWaByqEyyJmsXFBLig5lpsxVIgHpUZYOuq8yQNba
//http://blog.sina.com.cn/s/blog_627e00500100gpmp.html

typedef struct DBF_Header
{
	byte fileType;  // 文件类型
	char latestUpdateTime[3]; // 最近一次更新时间YYMMDD

	int records; //记录数
	short firstRecordOffset; //文件中第一条数据记录的位置
	short recordLength; // 记录的长度
	char reserved[20]; // 保留
}DBF_HEADER;

#define DBF_HEADER_SIZE 32

typedef struct field
{
	char name[11]; // 字段名,最多10个字符
	char type; // 字段类型
	int offset; //字段在记录中的偏移量
	byte length; // 字段长度
	byte decimal; // 小数位数
	char reserved[14]; // 保留
}FIELD;
#define FIELD_DEFINE_SIZE 32

typedef struct record
{
	char name[11];
}RECORD;

/*
0.监听文件变动
1.读文件
2.放入队列
3.单线程解析
4.推送数据

文件头32 + 字段定义32*字段数 + 0x0D + 数据记录*记录数
每条记录的第一个字节如果为星号(0x2A)代表删除记录，空格(0x20)代表正常记录
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
