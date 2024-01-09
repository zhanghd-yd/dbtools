#ifndef BASE_DB_INFO_H
#define BASE_DB_INFO_H

#include <vector>
#include <any>
#include <functional>
#include "glog/logging.h"
#include "fmt/color.h"

#include <type_traits>
#include <rttr/registration>
#include "rttr_serialization/to_json.h"

//////////////
#include "base/MysqlConnection.h"
#include "base/DataTables.h"
#include "mysql/mysql.h"

#include "BaseDBData.h"

namespace DBAG {
	
	class BaseDBDao {
	public:
		BaseDBDao() = default;
		virtual ~BaseDBDao() = default;

		virtual std::string& getTableName() = 0;

		virtual std::string& getPrimarykey() = 0;

		virtual std::vector<std::string> getColumnList() = 0;

		/////////////////////// gen SQL
		std::string genSelectSQL(const std::vector<FieldSelectedInfo>& infos = std::vector<FieldSelectedInfo>());

		template<class T>
		std::string genDeleteSQL(T pKey);

		template<>
		std::string genDeleteSQL<std::string>(std::string pKey);

		template<class T>
		std::string genBatchDeleteSQL(const std::vector<T>& pKey);

		template<>
		std::string genBatchDeleteSQL<std::string>(const std::vector<std::string>& pKey);

		template<class T>
		std::string genInsertSQL(std::vector<std::string>& column, T obj);

		template<class T>
		std::string genInsertSQL(std::vector<std::string>& column, std::vector<T> objList);

		///////////////////// run SQL
		template<class T>
		std::vector<std::shared_ptr<T>> executeSelect(const std::vector<FieldSelectedInfo>& infos = std::vector<FieldSelectedInfo>());

		template<class T>
		int executeDelete(T pKey);

		template<>
		int executeDelete<std::string>(std::string pKey);

		template<class T>
		int executeBitchDelete(const std::vector<T>& pKeyList);

		template<>
		int executeBitchDelete<std::string>(const std::vector<std::string>& pKeyList);

		template<class T>
		int executeInsert(std::vector<std::string>& column, T obj);

		template<class T>
		int executeInsert(std::vector<std::string>& column, std::vector<T> objList);

	protected:
		int execute(const std::string& sql);

		template<class T>
		std::vector<std::shared_ptr<T>> executeSTMT(const std::string& sql);
	};

	template<class T>
	inline std::string BaseDBDao::genDeleteSQL(T pKey)
	{
		std::string baseSQL = fmt::format("delete from {} where {} = {}", getTableName(), getPrimarykey(), pKey);
		DLOG(INFO) << "Delete SQL: " << baseSQL;
		return move(baseSQL);
	}

	template<>
	inline std::string BaseDBDao::genDeleteSQL(std::string pKey)
	{
		std::string baseSQL = fmt::format("delete from {} where {} = '{}'", getTableName(), getPrimarykey(), pKey);
		DLOG(INFO) << "Delete SQL: " << baseSQL;
		return move(baseSQL);
	}

	template<class T>
	inline std::string BaseDBDao::genBatchDeleteSQL(const std::vector<T>& pKeyList)
	{
		std::stringstream ss{};
		for (const auto& s : pKeyList) {
			ss << s << ",";
		}
		std::string sp = ss.str();
		sp = sp.substr(0, sp.size() - 1);
		
		std::string baseSQL = fmt::format("delete from {} where {} in ({})", getTableName(), getPrimarykey(), sp);
		DLOG(INFO) << "Batch Delete SQL: " << baseSQL;
		return move(baseSQL);
	}

	template<>
	inline std::string BaseDBDao::genBatchDeleteSQL<std::string>(const std::vector<std::string>& pKeyList){
		std::stringstream ss{};
		for (const auto& s : pKeyList) {
			ss << "'" << s + "',";
		}
		std::string sp = ss.str();
		sp = sp.substr(0, sp.size() - 1);

		std::string baseSQL = fmt::format("delete from {} where {} in ({})", getTableName(), getPrimarykey(), sp);
		DLOG(INFO) << "Batch Delete SQL: " << baseSQL;
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
			} else if (typeName == "float") {
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

		std::string insertSQL = fmt::format("insert into {} ({}) value ({})", getTableName(), columnStr, valueStr);
		DLOG(INFO) << "insertSQL SQL: " << insertSQL;

		return move(insertSQL);
	}
	template<class T>
	inline std::string BaseDBDao::genInsertSQL(std::vector<std::string>& column, std::vector<T> objList)
	{
		return std::string();
	}

	//////////////////////////////////////

	template<class T>
	inline std::vector<std::shared_ptr<T>> BaseDBDao::executeSelect(const std::vector<FieldSelectedInfo>& infos)
	{
		using namespace rttr;
		std::string sql = genSelectSQL(infos);
		
		std::vector<std::shared_ptr<T>> resuls{};

		MysqlConnectionPool& connectPool = eHualu::ConnectionPools::GetBizSatPool();
		MYSQL_RES* res_set = connectPool.GetMysqlConnection()->QuerySQL(sql);
		if (res_set == NULL || res_set->row_count == 0)
		{
			if (res_set)
			{
				connectPool.GetMysqlConnection()->ReleaseResultSet(res_set);
			}
		} else {
			std::vector<std::pair<std::string, int>> dbColumnInfo;
			unsigned int fieldNum = mysql_num_fields(res_set);
			MYSQL_FIELD* fields = mysql_fetch_fields(res_set);
			std::string tmpName;
			for (int i = 0; i < fieldNum; i++) {
				std::pair<std::string, int> p = { std::string(fields[i].name), static_cast<int>(fields[i].type) };
				dbColumnInfo.emplace_back(p);

				DLOG(INFO) << "Get Field Type Value:" << p.first << " " << p.second;
			}

			MYSQL_ROW row;
			while ((row = mysql_fetch_row(res_set)) != NULL)
			{
				/*
				enum enum_field_types { MYSQL_TYPE_DECIMAL, MYSQL_TYPE_TINY,
                    MYSQL_TYPE_SHORT,  MYSQL_TYPE_LONG,
                    MYSQL_TYPE_FLOAT,  MYSQL_TYPE_DOUBLE,
                    MYSQL_TYPE_NULL,   MYSQL_TYPE_TIMESTAMP,
                    MYSQL_TYPE_LONGLONG,MYSQL_TYPE_INT24,
                    MYSQL_TYPE_DATE,   MYSQL_TYPE_TIME,
                    MYSQL_TYPE_DATETIME, MYSQL_TYPE_YEAR,
                    MYSQL_TYPE_NEWDATE, MYSQL_TYPE_VARCHAR,
                    MYSQL_TYPE_BIT,
                        
                    //the following types are not used by client,
                    //only for mysqlbinlog!!
					MYSQL_TYPE_TIMESTAMP2,
					MYSQL_TYPE_DATETIME2,
					MYSQL_TYPE_TIME2,
					
					MYSQL_TYPE_JSON = 245,
					MYSQL_TYPE_NEWDECIMAL = 246,
					MYSQL_TYPE_ENUM = 247,
					MYSQL_TYPE_SET = 248,
					MYSQL_TYPE_TINY_BLOB = 249,
					MYSQL_TYPE_MEDIUM_BLOB = 250,
					MYSQL_TYPE_LONG_BLOB = 251,
					MYSQL_TYPE_BLOB = 252,
					MYSQL_TYPE_VAR_STRING = 253,
					MYSQL_TYPE_STRING = 254,
					MYSQL_TYPE_GEOMETRY = 255,
				}
				*/
				rttr::variant obj_var = rttr::type::get<T>().create();
				std::shared_ptr<T> t = obj_var.get_value<std::shared_ptr<T>>();
				for (int index = 0; index < dbColumnInfo.size(); index++) {
					char* d = row[index];
					if (d == nullptr) {
						continue;
					}

					const auto& p = dbColumnInfo[index];
					property prop = type::get(t.get()).get_property(p.first);
					switch (p.second)
					{
						//case enum_field_types::MYSQL_TYPE_SHORT:
						//case enum_field_types::MYSQL_TYPE_LONGLONG:
						case enum_field_types::MYSQL_TYPE_LONG: {
							int var = std::stoi(std::string(d));
							prop.set_value(t, var);
							break;
						}
						case enum_field_types::MYSQL_TYPE_DATE:
						case enum_field_types::MYSQL_TYPE_DATETIME: {
							prop.set_value(t, std::string(d));
							break;
						}
						/*case enum_field_types::MYSQL_TYPE_FLOAT: {
							float var = std::stof(std::string(d));
							prop.set_value(t, var);
							break;
						}*/
						case enum_field_types::MYSQL_TYPE_DOUBLE: {
							//double var = std::stod(std::string(d));
							float var = std::stof(std::string(d));
							prop.set_value(t, var);
							break;
						}
						case enum_field_types::MYSQL_TYPE_VAR_STRING: {
							prop.set_value(t, std::string(d));
							break;
						}
						default: {
							DLOG(INFO) << "error: " << p.first << " " << p.second << " " << std::string(d);
							assert(false);
							break;
						}
					}
				}
				resuls.emplace_back(t);
			}
			connectPool.GetMysqlConnection()->ReleaseResultSet(res_set);
		}

		return resuls;
	}
	template<class T>
	inline int BaseDBDao::executeDelete(T pKey)
	{
		std::string sql = genDeleteSQL<T>(pKey);
		MysqlConnectionPool& connectPool = eHualu::ConnectionPools::GetBizSatPool();
		bool b = connectPool.GetMysqlConnection()->ExecuteSQL(sql);
		b ? DLOG(INFO) << "executeDelete success" : DLOG(WARNING) << "executeDelete failed";
		return b;
	}
	template<>
	inline int BaseDBDao::executeDelete(std::string pKey)
	{
		std::string sql = genDeleteSQL<std::string>(pKey);
		MysqlConnectionPool& connectPool = eHualu::ConnectionPools::GetBizSatPool();
		bool b = connectPool.GetMysqlConnection()->ExecuteSQL(sql);
		b ? DLOG(INFO) << "executeDelete success" : DLOG(WARNING) << "executeDelete failed";
		return b;
	}
	template<class T>
	inline int BaseDBDao::executeBitchDelete(const std::vector<T>& pKeyList)
	{
		std::string sql = genBatchDeleteSQL<T>(pKeyList);
		MysqlConnectionPool& connectPool = eHualu::ConnectionPools::GetBizSatPool();
		bool b = connectPool.GetMysqlConnection()->ExecuteSQL(sql);
		b ? DLOG(INFO) << "executeDelete success" : DLOG(WARNING) << "executeDelete failed";
		return b;
	}

	template<>
	inline int BaseDBDao::executeBitchDelete<std::string>(const std::vector<std::string>& pKeyList) {
		std::string sql = genBatchDeleteSQL<std::string>(pKeyList);
		MysqlConnectionPool& connectPool = eHualu::ConnectionPools::GetBizSatPool();
		bool b = connectPool.GetMysqlConnection()->ExecuteSQL(sql);
		b ? DLOG(INFO) << "executeDelete success" : DLOG(WARNING) << "executeDelete failed";
		return b;
	}

	template<class T>
	inline int BaseDBDao::executeInsert(std::vector<std::string>& column, T obj)
	{
		std::string sql = genInsertSQL(column, obj);
		MysqlConnectionPool& connectPool = eHualu::ConnectionPools::GetBizSatPool();
		bool b = connectPool.GetMysqlConnection()->ExecuteSQL(sql);
		b ? DLOG(INFO) << "executeInsert success" : DLOG(WARNING) << "executeInsert failed";
		return b;
	}
	template<class T>
	inline int BaseDBDao::executeInsert(std::vector<std::string>& column, std::vector<T> objList)
	{
		//TODO
		return 0;
	}
	template<class T>
	inline std::vector<std::shared_ptr<T>> BaseDBDao::executeSTMT(const std::string& sql)
	{
		//TODO
		return std::vector<T>();
	}
}
#endif
