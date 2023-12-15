#ifndef BASE_DB_DATA_H
#define BASE_DB_DATA_H

#include <any>

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

		std::string _conn{ "and" };
		WhereCond _cond;
		FieldType _type;

		std::string getSQLCond();
	};

}
#endif // !BASE_DB_DATA_H
