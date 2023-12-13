#ifndef TEST_STRUCT_H
#define TEST_STRUCT_H

#include "DBBaseAutoGen/BaseDBInfo.h"

#include <type_traits>
#include <rttr/registration>

namespace DBAG
{
	struct Test {
		int id;
		std::string name;
		float score;
		std::string date;
	};


	class TestDBGenDao : public BaseDBDao {
	public:

		virtual std::string& getTableName() override;

		virtual std::string& getPrimarykey() override;

		virtual std::vector<std::string> getColumnList() override;
	};
} // namespace DBAG

#endif