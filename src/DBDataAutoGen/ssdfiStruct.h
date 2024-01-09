
#ifndef ssdfi_STRUCT_H
#define ssdfi_STRUCT_H

#include "DBBaseAutoGen/BaseDBInfo.h"

#include <type_traits>
#include <rttr/registration>

namespace DBAG
{
    
            struct ssdfi {
                std::string md5;
std::string allsat_l3_path;
std::string allsat_l3_nc;
std::string lat_max;
std::string lat_min;
std::string lon_max;
std::string lon_min;
std::string msla_result;
std::string xml_path;
std::string create_time;
std::string extend1;
std::string extend2;
std::string extend3;
std::string extend4;
std::string extend5;

            };

    class ssdfiDBGenDao : public BaseDBDao {
        public:

        virtual std::string& getTableName() override;

        virtual std::string& getPrimarykey() override;

        virtual std::vector<std::string> getColumnList() override;
    };
} // namespace DBAG

#endif
