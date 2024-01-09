
#ifndef sstf_STRUCT_H
#define sstf_STRUCT_H

#include "DBBaseAutoGen/BaseDBInfo.h"

#include <type_traits>
#include <rttr/registration>

namespace DBAG
{
    
            struct sstf {
                std::string md5;
std::string cfg_dir;
std::string bg_data_type;
std::string bld_resolution;
std::string bld_area_latu;
std::string bld_area_latb;
std::string bld_area_lonl;
std::string bld_area_lonr;
std::string bld_date_start;
std::string bld_date_end;
std::string l4_outdir;
std::string l4_outpattern;
std::string xml_path;
std::string create_time;
std::string extend1;
std::string extend2;
std::string extend3;
std::string extend4;
std::string extend5;

            };

    class sstfDBGenDao : public BaseDBDao {
        public:

        virtual std::string& getTableName() override;

        virtual std::string& getPrimarykey() override;

        virtual std::vector<std::string> getColumnList() override;
    };
} // namespace DBAG

#endif
