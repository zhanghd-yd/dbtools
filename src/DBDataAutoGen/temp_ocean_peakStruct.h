
#ifndef temp_ocean_peak_STRUCT_H
#define temp_ocean_peak_STRUCT_H

#include "DBBaseAutoGen/BaseDBInfo.h"

#include <type_traits>
#include <rttr/registration>

namespace DBAG
{
    
            struct temp_ocean_peak {
                int id;
std::string lat_min;
std::string lat_max;
std::string lon_min;
std::string lon_max;
std::string date_start;
std::string date_end;
std::string data_type;
std::string in_dir;
std::string out_dir;
std::string temp_throd;
std::string bwareaopen_num;
std::string imdilate_num;
std::string imerode_num;
std::string bwmorph_num;
std::string create_time;
std::string extend1;
std::string extend2;
std::string extend3;
std::string extend4;
std::string extend5;

            };

    class temp_ocean_peakDBGenDao : public BaseDBDao {
        public:

        virtual std::string& getTableName() override;

        virtual std::string& getPrimarykey() override;

        virtual std::vector<std::string> getColumnList() override;
    };
} // namespace DBAG

#endif
