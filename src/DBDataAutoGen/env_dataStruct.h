
#ifndef env_data_STRUCT_H
#define env_data_STRUCT_H

#include "DBBaseAutoGen/BaseDBInfo.h"

#include <type_traits>
#include <rttr/registration>

namespace DBAG
{
	struct env_data {
		std::string NcFileDataName;
		std::string Name;
		std::string TimeStamp;
		float LonBegin;
		float LonEnd;
		float LonStep;
		int LonCount;
		float LatBegin;
		float LatEnd;
		float LatStep;
		int LatCount;
		float DepthBegin;
		float DepthEnd;
		float DepthStep;
		int DepthCount;
		std::string MD5;

	};

	class env_dataDBGenDao : public BaseDBDao {
	public:

		virtual std::string& getTableName() override;

		virtual std::string& getPrimarykey() override;

		virtual std::vector<std::string> getColumnList() override;
	};
} // namespace DBAG

#endif
