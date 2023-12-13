#include "DBDataAutoGen/TestStruct.h"
#include <glog/logging.h>
#include <string>
#include <QDateTime>
#include <iostream>

int main(int argc, char** argv) {

    google::InitGoogleLogging(argv[0]);
    FLAGS_alsologtostderr = 1;
    FLAGS_colorlogtostderr = true;
    LOG(WARNING) << "app start";

    using namespace DBAG;

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
    
    testGen.genSelectSQL(true);

    testGen.genSelectSQL(true,infos);

    testGen.genDeleteSQL<int>(0);

    testGen.genDeleteSQL<std::string>("abc");

    Test testData;
    testData.id = 10;
    testData.name = "abc";
    testData.score = 90.5;
    testData.date = QDate::currentDate().toString("yyyy-MM-dd").toStdString();
    auto list = testGen.getColumnList();
    testGen.genInsertSQL<Test>(list,testData);

    return 0;
}