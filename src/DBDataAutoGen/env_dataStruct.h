
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
double LonBegin;
double LonEnd;
double LonStep;
int LonCount;
double LatBegin;
double LatEnd;
double LatStep;
int LatCount;
double DepthBegin;
double DepthEnd;
double DepthStep;
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
