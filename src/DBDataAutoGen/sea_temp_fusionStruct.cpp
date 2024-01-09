
#include "sea_temp_fusionStruct.h"

#define RegisterClassName DBAG::sea_temp_fusion

std::string& DBAG::sea_temp_fusionDBGenDao::getTableName()
{
    static std::string t = "sea_temp_fusion";
    return t;
}

std::string& DBAG::sea_temp_fusionDBGenDao::getPrimarykey()
{
    static std::string t = "";
    return t;
}

std::vector<std::string> DBAG::sea_temp_fusionDBGenDao::getColumnList()
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
    rttr::registration::class_<RegisterClassName>("DBAG::sea_temp_fusion")
		.constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
        .property("id", &RegisterClassName::id)(rttr::metadata("cn",std::string("")))
.property("cfg_dir", &RegisterClassName::cfg_dir)(rttr::metadata("cn",std::string("")))
.property("bg_data_type", &RegisterClassName::bg_data_type)(rttr::metadata("cn",std::string("")))
.property("bld_resolution", &RegisterClassName::bld_resolution)(rttr::metadata("cn",std::string("")))
.property("bld_area_latu", &RegisterClassName::bld_area_latu)(rttr::metadata("cn",std::string("")))
.property("bld_area_latb", &RegisterClassName::bld_area_latb)(rttr::metadata("cn",std::string("")))
.property("bld_area_lonl", &RegisterClassName::bld_area_lonl)(rttr::metadata("cn",std::string("")))
.property("bld_area_lonr", &RegisterClassName::bld_area_lonr)(rttr::metadata("cn",std::string("")))
.property("bld_date_start", &RegisterClassName::bld_date_start)(rttr::metadata("cn",std::string("")))
.property("bld_date_end", &RegisterClassName::bld_date_end)(rttr::metadata("cn",std::string("")))
.property("l4_outdir", &RegisterClassName::l4_outdir)(rttr::metadata("cn",std::string("")))
.property("l4_outpattern", &RegisterClassName::l4_outpattern)(rttr::metadata("cn",std::string("")))
.property("datapath", &RegisterClassName::datapath)(rttr::metadata("cn",std::string("")))
.property("create_time", &RegisterClassName::create_time)(rttr::metadata("cn",std::string("")))
.property("extend1", &RegisterClassName::extend1)(rttr::metadata("cn",std::string("")))
.property("extend2", &RegisterClassName::extend2)(rttr::metadata("cn",std::string("")))
.property("extend3", &RegisterClassName::extend3)(rttr::metadata("cn",std::string("")))
.property("extend4", &RegisterClassName::extend4)(rttr::metadata("cn",std::string("")))
.property("extend5", &RegisterClassName::extend5)(rttr::metadata("cn",std::string("")))

    ;
}
