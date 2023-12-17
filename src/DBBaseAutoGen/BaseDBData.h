#ifndef BASE_DB_DATA_H
#define BASE_DB_DATA_H

#include <any>
#include <map>
#include <type_traits>
#include <rttr/registration>

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
		EQUAL = 0,
		LESS,
		LESSEQUAL,
		MORE,
		MOREEQUAL,
		IN,

		//only support string !!
		EQUALSTRING = 100,
		LIKE,

		//only support date(yyyy-MM-dd) !!
		DATEEQUAL = 200,
		DATELESS,
		DATELESSEQUAL,
		DATEMORE,
		DATEMOREEQUAL,

		//only support datetime(yyyy-MM-dd HH:mm:ss) !!
		DATETIMEEQUAL = 300,
		DATETIMELESS,
		DATETIMELESSEQUAL,
		DATETIMEMORE,
		DATETIMEMOREEQUAL
	};

	
	FieldType getFieldType(std::string_view fieldTypeName);
	std::string getWhereCondWidgetText(DBAG::WhereCond cond);
	std::pair<int, int> getSupportWhereCondRange(std::string_view fieldTypeName);
	std::pair<int, int> getSupportWhereCondRange(FieldType type);
	std::vector<WhereCond> getSupportWhereCond(std::string_view fieldTypeName);
	std::vector<WhereCond> getSupportWhereCond(FieldType type);
	bool checkSupportWhereCond(FieldType type, WhereCond cond);

	class FieldSelectedInfo {
	public:

		std::string _name;
		//std::any _value;
		std::string _value;

		std::string _conn{ "and" };
		WhereCond _cond;
		FieldType _type;
		bool _enable{ true };

		std::string getSQLCond();
	};


	///////////////////////////////// tableConfig
	struct FieldSelected {
		FieldSelected() {}
		FieldSelected(std::string value, int cond, int tablerow,bool enable) 
			:_value(value), _cond(cond), _tablerow(tablerow), _enable(enable){}
		
		std::string _value;
		int _cond;//WhereCond
		int _tablerow;
		bool _enable{ true };
	};

	struct FieldInfo {
		std::string _field;
		std::string _type;
		int _length;
		int _precision;
		int _scale;
		double _max_value{ 9999.0 };
		double _min_value{ 0.0 };
		bool _nullable;
		std::string _comment;
		std::vector<FieldSelected> _selecteds;
	};
	struct TableKey {
		std::string _column{};
		bool _increment{ false };
	};
	struct TableConfig {
		int _query_table_rowcount{ 0 };
		std::string _table;
		TableKey _key;
		std::vector<FieldInfo> _fields;
	};
	/////////////////////////////////
}

#endif // !BASE_DB_DATA_H
