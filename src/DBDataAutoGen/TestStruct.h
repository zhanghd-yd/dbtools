#ifndef TEST_STRUCT_H
#define TEST_STRUCT_H

#include "DBBaseAutoGen/BaseDBInfo.h"

#include <type_traits>
#include <rttr/registration>

#define _dbag_type(type,varName)\
	type varName; std::string_view _##varName(){return #varName;}

namespace DBAG
{
	struct Test {
		_dbag_type(int, id);
		_dbag_type(std::string, name);
		_dbag_type(float, score);
		_dbag_type(std::string, date)
	};


	class TestDBGenDao : public BaseDBDao {
	public:

		virtual std::string& getTableName() override;

		virtual std::string& getPrimarykey() override;

		virtual std::vector<std::string> getColumnList() override;
	};
} // namespace DBAG

#endif