
#include "temp_ocean_peakStruct.h"

#define RegisterClassName DBAG::temp_ocean_peak

std::string& DBAG::temp_ocean_peakDBGenDao::getTableName()
{
    static std::string t = "temp_ocean_peak";
    return t;
}

std::string& DBAG::temp_ocean_peakDBGenDao::getPrimarykey()
{
    static std::string t = "";
    return t;
}

std::vector<std::string> DBAG::temp_ocean_peakDBGenDao::getColumnList()
{
    std::vector<std::string> list;
    rttr::type t = rttr::type::get<RegisterClassName>();
    for (auto& prop : t.get_properties()){
        list.emplace_back(prop.get_name().to_string());
    }

    return move(list);
}

RTTR_REGISTRATION
{
    rttr::registration::class_<RegisterClassName>("DBAG::temp_ocean_peak")
		.constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
        .property("id", &RegisterClassName::id)(rttr::metadata("cn",std::string("")))
.property("lat_min", &RegisterClassName::lat_min)(rttr::metadata("cn",std::string("")))
.property("lat_max", &RegisterClassName::lat_max)(rttr::metadata("cn",std::string("")))
.property("lon_min", &RegisterClassName::lon_min)(rttr::metadata("cn",std::string("")))
.property("lon_max", &RegisterClassName::lon_max)(rttr::metadata("cn",std::string("")))
.property("date_start", &RegisterClassName::date_start)(rttr::metadata("cn",std::string("")))
.property("date_end", &RegisterClassName::date_end)(rttr::metadata("cn",std::string("")))
.property("data_type", &RegisterClassName::data_type)(rttr::metadata("cn",std::string("")))
.property("in_dir", &RegisterClassName::in_dir)(rttr::metadata("cn",std::string("")))
.property("out_dir", &RegisterClassName::out_dir)(rttr::metadata("cn",std::string("")))
.property("temp_throd", &RegisterClassName::temp_throd)(rttr::metadata("cn",std::string("")))
.property("bwareaopen_num", &RegisterClassName::bwareaopen_num)(rttr::metadata("cn",std::string("")))
.property("imdilate_num", &RegisterClassName::imdilate_num)(rttr::metadata("cn",std::string("")))
.property("imerode_num", &RegisterClassName::imerode_num)(rttr::metadata("cn",std::string("")))
.property("bwmorph_num", &RegisterClassName::bwmorph_num)(rttr::metadata("cn",std::string("")))
.property("create_time", &RegisterClassName::create_time)(rttr::metadata("cn",std::string("")))
.property("extend1", &RegisterClassName::extend1)(rttr::metadata("cn",std::string("")))
.property("extend2", &RegisterClassName::extend2)(rttr::metadata("cn",std::string("")))
.property("extend3", &RegisterClassName::extend3)(rttr::metadata("cn",std::string("")))
.property("extend4", &RegisterClassName::extend4)(rttr::metadata("cn",std::string("")))
.property("extend5", &RegisterClassName::extend5)(rttr::metadata("cn",std::string("")))

    ;
}
