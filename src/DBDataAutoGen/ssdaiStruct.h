
#ifndef ssdai_STRUCT_H
#define ssdai_STRUCT_H

#include "DBBaseAutoGen/BaseDBInfo.h"

#include <type_traits>
#include <rttr/registration>

namespace DBAG
{
    
            struct ssdai {
                std::string md5;
std::string h2b_l2_nc;
std::string sla_l3_result;
std::string xml_path;
std::string create_time;
std::string extend1;
std::string extend2;
std::string extend3;
std::string extend4;
std::string extend5;

            };

    class ssdaiDBGenDao : public BaseDBDao {
        public:

        virtual std::string& getTableName() override;

        virtual std::string& getPrimarykey() override;

        virtual std::vector<std::string> getColumnList() override;
    };
} // namespace DBAG

#endif
