#ifndef BASE_DB_INFO_H
#define BASE_DB_INFO_H

#include <vector>
#include <any>
#include <functional>
#include "glog/logging.h"
#include "fmt/color.h"

namespace DBAG {
    enum class FieldType : int {
        INT,
        LONGLONG,
        FLOAT,
        DOUBLE,
        STRING,
        DATE,
        DATETIME
    };

    enum class WhereCond : int {
        //only support number !!
        EQUAL,
        LESS,
        LESSEQUAL,
        MORE,
        MOREEQUAL,
        IN,

        //only support string !!
        LIKE,
        EQUALSTRING,

        //only support date(yyyy-MM-dd) !!
        DATEEQUAL,
        DATELESS,
        DATELESSEQUAL,
        DATEMORE,
        DATEMOREEQUAL,

        //only support datetime(yyyy-MM-dd HH:mm:ss) !!
        DATETIMEEQUAL,
        DATETIMELESS,
        DATETIMELESSEQUAL,
        DATETIMEMORE,
        DATETIMEMOREEQUAL
    };

    class FieldInfo {
    public:
        std::string _name;
        std::any _value;

        std::string _conn{"and"};
        WhereCond _cond;
        FieldType _type;

        std::string getSQLCond();
    };

    class BaseDBDao {
    public:
        BaseDBDao() = default;
        virtual ~BaseDBDao() = default;

        virtual std::string& getTableName() = 0;

        virtual std::string& getPrimarykey() = 0;

        virtual std::vector<std::string> getColumnList() = 0;

        /////////////////////// gen SQL
        std::string genSelectSQL(bool addSemicolon,const std::vector<FieldInfo>& infos = std::vector<FieldInfo>());

        template<class T>
        std::string genDeleteSQL(T pKey);

        template<>
        std::string genDeleteSQL<std::string>(std::string pKey);

        template<class T>
        std::string genInsertSQL(std::vector<std::string>& column, T obj);

        template<class T>
        std::string genInsertSQL(std::vector<std::string>& column, std::vector<T> objList);

        ///////////////////// run SQL
        template<class T>
        std::vector<T> executeSelect(const std::vector<FieldInfo>& infos = std::vector<FieldInfo>());

        template<class T>
        int executeDelete(T pKey);

        template<>
        int executeDelete<std::string>(std::string pKey);

        template<class T>
        int executeInsert(std::vector<std::string>& column, T obj);

        template<class T>
        int executeInsert(std::vector<std::string>& column, std::vector<T> objList);

    protected:
        int execute(const std::string& sql);

        template<class T>
        std::vector<T> executeSTMT(const std::string& sql);
    };

    template<class T>
    inline std::string BaseDBDao::genDeleteSQL(T pKey)
    {
        std::string baseSQL = fmt::format("delete from {} where {} = {};", getTableName(), getPrimarykey(), pKey);
        DLOG(INFO) << "Delete SQL: " << baseSQL;
        return move(baseSQL);
    }

    template<>
    inline std::string BaseDBDao::genDeleteSQL(std::string pKey)
    {
        std::string baseSQL = fmt::format("delete from {} where {} = '{}';", getTableName(), getPrimarykey(), pKey);
        DLOG(INFO) << "Delete SQL: " << baseSQL;
        return move(baseSQL);
    }

    template<class T>
    inline std::string BaseDBDao::genInsertSQL(std::vector<std::string>& columnList, T obj)
    {
        using namespace rttr;
        std::string columnStr = "";
        if (!columnList.empty()) {
            for (auto& s : columnList) {
                columnStr += s + ",";
            }
        }
        columnStr = columnStr.substr(0, columnStr.size() - 1);

        std::stringstream valueStream;
        for (auto& columnName : columnList) {
            property prop = type::get(obj).get_property(columnName);
            variant var = prop.get_value(obj);
            std::string typeName = var.get_type().get_name().to_string();
            //DLOG(INFO) << "typeName: " << typeName;
            if (typeName == "std::string") {
                valueStream << "'" << var.to_string() << "'";
            } else if(typeName == "float"){
                valueStream << var.to_float();
            } else if (typeName == "double") {
                valueStream << var.to_double();
            } else if (typeName == "int") {
                valueStream << var.to_int();
            }
            valueStream << ",";
        }
        auto valueStr = valueStream.str();
        valueStr = valueStr.substr(0, valueStr.size() - 1);
        
        std::string insertSQL = fmt::format("insert into {} ({}) value ({});", getTableName(), columnStr, valueStr);
        DLOG(INFO) << "insertSQL SQL: " << insertSQL;

        return move(insertSQL);
    }
    template<class T>
    inline std::string BaseDBDao::genInsertSQL(std::vector<std::string>& column, std::vector<T> objList)
    {
        return std::string();
    }
    template<class T>
    inline std::vector<T> BaseDBDao::executeSelect(const std::vector<FieldInfo>& infos)
    {
        return std::vector<T>();
    }
    template<class T>
    inline int BaseDBDao::executeDelete(T pKey)
    {
        return 0;
    }
    template<>
    inline int BaseDBDao::executeDelete(std::string pKey)
    {
        return 0;
    }
    template<class T>
    inline int BaseDBDao::executeInsert(std::vector<std::string>& column, T obj)
    {
        return 0;
    }
    template<class T>
    inline int BaseDBDao::executeInsert(std::vector<std::string>& column, std::vector<T> objList)
    {
        return 0;
    }
    template<class T>
    inline std::vector<T> BaseDBDao::executeSTMT(const std::string& sql)
    {
        return std::vector<T>();
    }
}
#endif
