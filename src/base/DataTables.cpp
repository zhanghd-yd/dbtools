#include "DataTables.h"

namespace eHualu
{
	MysqlConnectionPool& ConnectionPools::GetEnvPool()
	{
		static MysqlConnectionPool s_pool;
		return s_pool;
	}

	MysqlConnectionPool& ConnectionPools::GetFeaturePool()
	{
		static MysqlConnectionPool s_pool;
		return s_pool;
	}

	//配置商业卫星数据库连接 lxb 20231207
	MysqlConnectionPool& ConnectionPools::GetBizSatPool()
	{
		static MysqlConnectionPool s_pool;
		return s_pool;
	}


	//bool TestTable::Write(ConstStringRef name)
	//{
	//	String sql;
	//	sql.Format("replace `test` set `name` =  '%s'", name.data());

	//	if (!ExecuteSQL(sql))
	//	{
	//		return false;
	//	}
	//	return true;
	//}


	//std::vector<TestTable::TestRecord> TestTable::Read()
	//{
	//	std::vector<TestRecord> records;

	//	String sql;
	//	sql.Format("select id, name from  `test` where id > %d", 1);


	//	MYSQL_RES* res_set = QuerySQL(sql);
	//	if (res_set == NULL || res_set->row_count == 0)
	//	{
	//		if (res_set)
	//		{
	//			ReleaseResultSet(res_set);
	//		}
	//	}
	//	else
	//	{
	//		TestRecord record;
	//		MYSQL_ROW row;
	//		while ((row = mysql_fetch_row(res_set)) != NULL)
	//		{
	//			record.id = readi(row[0]);
	//			record.name = String::UTF8ToGB(row[0]);
	//			records.emplace_back(record);
	//		}
	//		ReleaseResultSet(res_set);
	//	}

	//	return std::move(records);
	//}


	//bool TestSTMTTable::Write(ConstStringRef name, ConstStringRef buffer)
	//{
	//	m_params.clear();
	//	m_results.clear();
	//	String sql = "replace into `test` set `name` =  ? , `data` = ?";

	//	m_params.resize(2);
	//	memset(&m_params[0], 0, sizeof(MYSQL_BIND) * m_results.size());

	//	String n = name;
	//	String data = buffer;

	//	BindStringParam(m_params[0], n);
	//	BindLongBlobParam(m_params[1], data);


	//	bool flag = Prepare(sql);
	//	flag = ExecuteSTMT();
	//	return flag;
	//}

	//std::vector<TestSTMTTable::TestRecord> TestSTMTTable::Read()
	//{
	//	m_params.clear();
	//	m_results.clear();
	//	std::vector<TestRecord> records;
	//	String sql;

	//	sql.Format("select id, name,data from  `test` where name = '%s'", "345");

	//	m_results.resize(3);
	//	memset(&m_results[0], 0, sizeof(MYSQL_BIND) * m_results.size());
	//	TestRecord record;
	//	record.name.resize(255);
	//	record.buffer.resize(1024);
	//	BindIntParam(m_results[0], record.id);
	//	BindStringParam(m_results[1], record.name);
	//	BindLongBlobParam(m_results[2], record.buffer);

	//	bool flag = Prepare(sql);
	//	flag = ExecuteSTMT();
	//	while (FetchResult())
	//	{
	//		records.push_back(record);
	//	}


	//	return std::move(records);

	//}

	//////////////////////////////////////////////////////////////////////////////

	//void testSTMTTable()
	//{

	//	TestSTMTTable table;
	//	String data;
	//	data.resize(512, '\0');
	//	data[8] = 'a';
	//	table.Write("345", data);
	//	table.Read();

	//}

	//void testEnvDataTable()
	//{
	//	EnvDataTable table;
	//	EnvDataTable::Record record;
	//	record.NcFileDataName = "temp.nc";
	//	record.Name = "temperature";
	//	record.TimeStamp = 1670800000;
	//	record.LonBegin = 110;
	//	record.LonEnd = 130;
	//	record.LonStep = 1;
	//	record.LonCount = 100;
	//	record.LatBegin = 60;
	//	record.LatEnd = 70;
	//	record.LatStep = 1;
	//	record.LatCount = 100;
	//	record.DepthBegin = 1;
	//	record.DepthEnd = 100;
	//	record.DepthStep = 1;
	//	record.DepthCount = 100;
	//	record.MD5 = "hfipaohfaods";

	//	table.write(record);
	//	std::vector<EnvDataTable::Record> records;
	//	records.push_back(record);
	//	record.NcFileDataName = "temp2.nc";
	//	records.push_back(record);

	//	table.write(records);

	//}


	//EnvDataTable::Record::Record()
	//{
	//	NcFileDataName = "";
	//	Name = "";
	//	TimeStamp = 0;
	//	LatBegin = 0;
	//	LatEnd = 0;
	//	LatCount = 0;
	//	LatStep = 0;
	//	LonBegin = 0;
	//	LonEnd = 0;
	//	LonCount = 0;
	//	LonStep = 0;
	//	DepthBegin = 0;
	//	DepthEnd = 0;
	//	DepthCount = 0;
	//	DepthStep = 0;
	//	MD5 = "";
	//}


	//bool EnvDataTable::write(Record& record)
	//{
	//	String sql = fmt::format("replace into `env_data` values ('{}','{}',{},{},{},{},{},{},{},{},{},{},{},{},{},'{}')",
	//			record.NcFileDataName,
	//			record.Name,
	//			record.TimeStamp,
	//			record.LonBegin,
	//			record.LonEnd,
	//			record.LonStep,
	//			record.LonCount,
	//			record.LatBegin,
	//			record.LatEnd,
	//			record.LatStep,
	//			record.LatCount,
	//			record.DepthBegin,
	//			record.DepthEnd,
	//			record.DepthStep,
	//			record.DepthCount,
	//			record.MD5
	//	);


	//	if (!ExecuteSQL(sql))
	//	{
	//		return false;
	//	}
	//	return true;
	//}

	//bool EnvDataTable::write(std::vector<Record>& records)
	//{
	//	int count = records.size();
	//	if (count == 0)
	//	{
	//		return true;
	//	}
	//	if (count == 1)
	//	{
	//		return write(records[0]);
	//	}
	//	std::stringstream ss;
	//	ss << "replace into `env_data` values ";
	//	String format = "('{}','{}',{},{},{},{},{},{},{},{},{},{},{},{},{},'{}'),";
	//	For(i, count)
	//	{
	//		Record& record = records[i];
	//		if (i == count - 1)
	//		{
	//			format = "('{}','{}',{},{},{},{},{},{},{},{},{},{},{},{},{},'{}')";
	//		}


	//		ss << fmt::format(format,
	//				record.NcFileDataName,
	//				record.Name,
	//				record.TimeStamp,
	//				record.LonBegin,
	//				record.LonEnd,
	//				record.LonStep,
	//				record.LonCount,
	//				record.LatBegin,
	//				record.LatEnd,
	//				record.LatStep,
	//				record.LatCount,
	//				record.DepthBegin,
	//				record.DepthEnd,
	//				record.DepthStep,
	//				record.DepthCount,
	//				record.MD5
	//		);
	//	}

	//	if (!ExecuteSQL(ss.str()))
	//	{
	//		return false;
	//	}
	//	return true;
	//}

	//std::vector<EnvDataTable::Record> EnvDataTable::read(const std::string& prop, long long startTime, long long endTime)
	//{
	//	std::vector<Record> records;

	//	String sql;
	//	sql.Format("select NcFileDataName,Name,	TimeStamp,LonBegin,	LonEnd,LonStep,LonCount,LatBegin,LatEnd,	LatStep,LatCount,DepthBegin,DepthEnd,DepthStep,DepthCount,MD5 from  `env_data` where Name ='%s' and TimeStamp >= %lld and TimeStamp <= %lld", prop.data(), startTime, endTime);


	//	MYSQL_RES* res_set = QuerySQL(sql);
	//	if (res_set == NULL || res_set->row_count == 0)
	//	{
	//		if (res_set)
	//		{
	//			ReleaseResultSet(res_set);
	//		}
	//	}
	//	else
	//	{
	//		Record record;
	//		MYSQL_ROW row;
	//		while ((row = mysql_fetch_row(res_set)) != NULL)
	//		{
	//			record.NcFileDataName = row[0];
	//			record.Name = row[1];
	//			record.TimeStamp = readi64(row[2]);
	//			record.LonBegin = readf(row[3]);
	//			record.LonEnd = readf(row[4]);
	//			record.LonStep = readf(row[5]);
	//			record.LonCount = readi(row[6]);
	//			record.LatBegin = readf(row[7]);
	//			record.LatEnd = readf(row[8]);
	//			record.LatStep = readf(row[9]);
	//			record.LatCount = readi(row[10]);
	//			record.DepthBegin = readf(row[11]);
	//			record.DepthEnd = readf(row[12]);
	//			record.DepthStep = readf(row[13]);
	//			record.DepthCount = readi(row[14]);
	//			record.MD5 = row[15];

	//			records.emplace_back(record);
	//		}
	//		ReleaseResultSet(res_set);
	//	}

	//	return std::move(records);

	//}

	//bool EnvDataTable::remove(const std::set<std::string>& names)
	//{
	//	std::stringstream ss;
	//	int i = 0;
	//	ForEach(name, names)
	//	{
	//		ss << '"' << name << '"';
	//		if (i < names.size() - 1)
	//		{
	//			ss << ',';
	//		}
	//		i++;
	//	}

	//	String sql;
	//	sql.Format("delete from `env_data` where  `NcFileDataName` in  (%s)", ss.str().data());

	//	if (!ExecuteSQL(sql))
	//	{
	//		return false;
	//	}
	//	return true;
	//}


}