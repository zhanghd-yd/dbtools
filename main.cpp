#include <glog/logging.h>
#include <string>
#include <QDateTime>
#include <iostream>

#include "base/MysqlConnection.h"
#include "base/DataTables.h"

#include "DBDataAutoGen/TestStruct.h"
#include "DBDataAutoGen/env_dataStruct.h"

#include "rttr_serialization/to_json.h"

template<class T>
class TestR {
public:
	inline void print() {
		rttr::type t = rttr::type::get<T>();
		for (auto& prop : t.get_properties()) {
			LOG(INFO) << prop.get_name().to_string();
		}
	}
};

int main(int argc, char** argv) {

	google::InitGoogleLogging(argv[0]);
	FLAGS_alsologtostderr = 1;
	FLAGS_colorlogtostderr = true;
	
	using namespace DBAG;

	TestR<Test> tr;
	tr.print(); //test rttr

	LOG(WARNING) << "============  start gen sql ============ \n";
#if 1 // test ok
	{
		TestDBGenDao testGen;
		std::vector<FieldInfo> infos;
		{
			FieldInfo info;
			info._name = "id";
			info._type = FieldType::INT;
			info._cond = WhereCond::EQUAL;
			info._value = std::any(10);
			infos.emplace_back(info);
		}
		{
			FieldInfo info;
			info._name = "name";
			info._type = FieldType::STRING;
			info._cond = WhereCond::EQUALSTRING;
			info._value = std::make_any<std::string>(u8"abc");
			infos.emplace_back(info);
		}
		{
			FieldInfo info;
			info._name = "score";
			info._type = FieldType::FLOAT;
			info._cond = WhereCond::EQUAL;
			info._value = std::make_any<float>(90.5);
			infos.emplace_back(info);
		}
		{
			FieldInfo info;
			info._name = "date";
			info._type = FieldType::DATE;
			info._cond = WhereCond::DATEMOREEQUAL;
			info._value = std::make_any<std::string>(QDate::currentDate().toString("yyyy-MM-dd").toStdString());
			infos.emplace_back(info);
		}
		{
			FieldInfo info;
			info._name = "date";
			info._type = FieldType::DATE;
			info._cond = WhereCond::DATELESSEQUAL;
			info._value = std::make_any<std::string>(QDate::currentDate().toString("yyyy-MM-dd").toStdString());
			infos.emplace_back(info);
		}

		testGen.genSelectSQL();

		testGen.genSelectSQL(infos);

		testGen.genDeleteSQL(0);
		testGen.genDeleteSQL(std::string("abc"));

		Test testData;
		testData.id = 10;
		testData.name = "abc";
		testData.score = 90.5;
		testData.date = QDate::currentDate().toString("yyyy-MM-dd").toStdString();
		auto list = testGen.getColumnList();
		testGen.genInsertSQL<Test>(list, testData);
	}
#endif


#if 0 // test ok
	LOG(WARNING) << "\n =========== start query db ============\n";

	/////////////////
	{
		MysqlConnectionPool& bizSatPool = eHualu::ConnectionPools::GetBizSatPool();
		bizSatPool.Connect("127.0.0.1", 3306, "root", "root", "hl_earth_eiea");

		env_dataDBGenDao dao;

		env_data dData;
		dData.NcFileDataName = "NcFileDataName";
		dData.Name = "name";
		dData.TimeStamp = "2023-12-01 00:00:00";
		dData.LonBegin = 90.5;
		dData.LonEnd = 90.5;;
		dData.LonStep = 90.5;;
		dData.LonCount = 20;
		dData.LatBegin = 90.5;;
		dData.LatEnd = 90.5;;
		dData.LatStep = 90.5;;
		dData.LatCount = 20;
		dData.DepthBegin = 90.5;;
		dData.DepthEnd = 90.5;;
		dData.DepthStep = 90.5;;
		dData.DepthCount = 20;
		dData.MD5 = "MD5";
		auto list = dao.getColumnList();
		dao.executeDelete<std::string>("NcFileDataName");
		dao.executeInsert<env_data>(list, dData);
		std::vector<env_data> env_dataList = dao.executeSelect<env_data>();
		for (const auto& e : env_dataList) {
			LOG(INFO) << io::to_json(e);
		}
	}
#endif

	return 0;
}