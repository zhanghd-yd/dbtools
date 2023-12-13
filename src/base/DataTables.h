#ifndef DATA_TABLE_H
#define DATA_TABLE_H

#include "MysqlConnection.h"

namespace eHualu
{

class ConnectionPools
{
public:
	static MysqlConnectionPool& GetEnvPool();
	static MysqlConnectionPool& GetFeaturePool();
	//配置商业卫星数据库连接 lxb 20231207
	static MysqlConnectionPool& GetBizSatPool();
};

//
//class TestTable : public MysqlTableEx
//{
//	/*  使用说明
//		TestTable table;
//		table.Write("123");
//		table.Write("456");
//		table.Write("789");
//
//		std::vector<TestTable::TestRecord> records = table.Read();
//		ForEach(record, records)
//		{
//			record.id = record.id;
//		}
//	*/
//
//public:
//	struct TestRecord
//	{
//		int id;
//		String name;
//	};
//
//	TestTable(MysqlConnectionPool* pool = &ConnectionPools::GetEnvPool()) :MysqlTableEx(pool)
//	{
//
//	}
//
//	bool Write(ConstStringRef name);
//	std::vector<TestRecord> Read();
//};
//
//
//
//class TestSTMTTable : public MysqlSTMTTable
//{
//	/*使用说明
//
//		TestSTMTTable table;
//		String data;
//		data.resize(512, 'a');
//		table.Write("345", data);
//		table.Read();
//	
//	*/
//public:
//	struct TestRecord
//	{
//		int id;
//		String name;
//		String buffer;
//	};
//
//	TestSTMTTable(MysqlConnectionPool* pool = &ConnectionPools::GetEnvPool()) :MysqlSTMTTable(pool)
//	{
//
//	}
//
//	bool Write(ConstStringRef name, ConstStringRef buffer);
//	std::vector<TestRecord> Read();
//};
//
//
//
//void testSTMTTable();
//void testEnvDataTable();
//
//class EnvDataTable : public MysqlTableEx
//{
//
//public:
//	struct Record
//	{
//		Record();
//		String NcFileDataName;
//		String	Name;
//		long long	TimeStamp;
//		double	LonBegin;
//		double	LonEnd;
//		double	LonStep;
//		int	LonCount;
//		double	LatBegin;
//		double	LatEnd;
//		double	LatStep;
//		int	LatCount;
//		double	DepthBegin;
//		double	DepthEnd;
//		double	DepthStep;
//		int	DepthCount;
//		String 	MD5;
//
//		/*
//NcFileDataName
//Name
//TimeStamp
//LonBegin
//LonEnd
//LonStep
//LonCount
//LatBegin
//LatEnd
//LatStep
//LatCount
//DepthBegin
//DepthEnd
//DepthStep
//DepthCount
//MD5		
//		*/
//	};
//
//	EnvDataTable(MysqlConnectionPool* pool = &ConnectionPools::GetEnvPool()) :MysqlTableEx(pool)
//	{
//
//	}
//
//	bool write(Record& record);
//	bool write(std::vector<Record>& records);
//	std::vector<Record> read(const std::string& prop, long long startTime, long long endTime);
//	bool remove(const std::set<std::string>& names);
//};

}

#endif // !DATA_TABLE_H