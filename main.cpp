#include <glog/logging.h>
#include <string>
#include <QDateTime>
#include <iostream>
#include <QApplication>
#include "rttr_serialization/to_json.h"

#include "base/MysqlConnection.h"
#include "base/DataTables.h"

#include "DBDataAutoGen/TestStruct.h"
#include "DBDataAutoGen/env_dataStruct.h"

#include "DBServer/EnvDataManager.h"

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
	
	QApplication a(argc, argv);

	using namespace DBAG;

#if  0
	TestR<Test> tr;
	tr.print(); //test rttr
#endif //  0

#if 1 // test ok
	LOG(WARNING) << "============  start gen sql ============ \n";
	{
		TestDBGenDao testGen;
		std::vector<FieldSelectedInfo> infos;
		{
			FieldSelectedInfo info;
			info._name = "id";
			info._type = FieldType::INT;
			info._cond = WhereCond::EQUAL;
			info._value = std::to_string(10);
			infos.emplace_back(info);
		}
		{
			FieldSelectedInfo info;
			info._name = "name";
			info._type = FieldType::STRING;
			info._cond = WhereCond::EQUALSTRING;
			info._value = std::string("abc");
			infos.emplace_back(info);
		}
		{
			FieldSelectedInfo info;
			info._name = "score";
			info._type = FieldType::FLOAT;
			info._cond = WhereCond::EQUAL;
			info._value = std::to_string(90.5);;
			infos.emplace_back(info);
		}
		{
			FieldSelectedInfo info;
			info._name = "date";
			info._type = FieldType::DATE;
			info._cond = WhereCond::DATEMOREEQUAL;
			info._value = QDate::currentDate().toString("yyyy-MM-dd").toStdString();
			infos.emplace_back(info);
		}
		{
			FieldSelectedInfo info;
			info._name = "date";
			info._type = FieldType::DATE;
			info._cond = WhereCond::DATELESSEQUAL;
			info._value = QDate::currentDate().toString("yyyy-MM-dd").toStdString();
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
		testData.date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
		auto list = testGen.getColumnList();
		testGen.genInsertSQL<Test>(list, testData);

		testGen.genBatchDeleteSQL<int>({1,2,3,4,5,6});
		testGen.genBatchDeleteSQL<std::string>({ std::string("abc"),std::string("abc"),std::string("abc"),std::string("abc") });
	}
#endif

#if 1
	MysqlConnectionPool& bizSatPool = eHualu::ConnectionPools::GetBizSatPool();
	bizSatPool.Connect("127.0.0.1", 3306, "root", "root", "hl_earth_eiea");
#endif

#if 1 // test ok
	LOG(WARNING) << "\n =========== start query db ============\n";
	/////////////////
	{
		env_dataDBGenDao dao;

		//env_data dData;
		//dData.NcFileDataName = "NcFileDataName_0";
		//dData.Name = "name";
		//dData.TimeStamp = "2023-12-01 00:00:00";
		//dData.LonBegin = 90.5;
		//dData.LonEnd = 90.5;;
		//dData.LonStep = 90.5;;
		//dData.LonCount = 20;
		//dData.LatBegin = 90.5;;
		//dData.LatEnd = 90.5;;
		//dData.LatStep = 90.5;;
		//dData.LatCount = 20;
		//dData.DepthBegin = 90.5;;
		//dData.DepthEnd = 90.5;;
		//dData.DepthStep = 90.5;;
		//dData.DepthCount = 20;
		//dData.MD5 = "MD5";
		//auto list = dao.getColumnList();
		////dao.executeDelete<std::string>("NcFileDataName");
		//dao.executeInsert<env_data>(list, dData);
		//dData.NcFileDataName = "NcFileDataName_1";
		//dao.executeInsert<env_data>(list, dData);
		//dData.NcFileDataName = "NcFileDataName_2";
		//dao.executeInsert<env_data>(list, dData);
		
		std::vector<std::shared_ptr<env_data>> env_dataList = dao.executeSelect<env_data>();
		//for (const auto& e : env_dataList) {
		//	LOG(INFO) << io::to_json(e);
		//}

		//LOG(INFO) << io::to_json(env_dataList);
	}
#endif

	getSupportWhereCond(DBAG::FieldType::LONGLONG);

	BaseDBWidget* gui = new EnvDataManager;
	gui->loadTableHeader("../../config/tableConfig/");
	gui->show();

	return a.exec();
}