
#ifndef sstr_STRUCT_H
#define sstr_STRUCT_H

#include "DBBaseAutoGen/BaseDBInfo.h"

#include <type_traits>
#include <rttr/registration>

namespace DBAG
{
    
            struct sstr {
                std::string md5;
std::string dir_install;
std::string dir_input;
std::string dir_output;
std::string dir_parameter;
std::string source_l1b;
std::string source_refsst;
std::string outfile_name;
std::string time_start;
std::string time_end;
std::string lon_start;
std::string lon_end;
std::string lat_start;
std::string lat_end;
std::string region_name;
std::string bias_region;
std::string xml_path;
std::string create_time;
std::string extend1;
std::string extend2;
std::string extend3;
std::string extend4;
std::string extend5;

            };

    class sstrDBGenDao : public BaseDBDao {
        public:

        virtual std::string& getTableName() override;

        virtual std::string& getPrimarykey() override;

        virtual std::vector<std::string> getColumnList() override;
    };
} // namespace DBAG

#endif
