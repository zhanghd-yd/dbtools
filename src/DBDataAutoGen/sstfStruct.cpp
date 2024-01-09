
#include "sstfStruct.h"

#define RegisterClassName DBAG::sstf

std::string& DBAG::sstfDBGenDao::getTableName()
{
    static std::string t = "sstf";
    return t;
}

std::string& DBAG::sstfDBGenDao::getPrimarykey()
{
    static std::string t = "md5";
    return t;
}

std::vector<std::string> DBAG::sstfDBGenDao::getColumnList()
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
    rttr::registration::class_<RegisterClassName>("DBAG::sstf")
		.constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
        .property("md5", &RegisterClassName::md5)(rttr::metadata("cn",std::string("编号")))
.property("cfg_dir", &RegisterClassName::cfg_dir)(rttr::metadata("cn",std::string("说明文件路径")))
.property("bg_data_type", &RegisterClassName::bg_data_type)(rttr::metadata("cn",std::string("背景场类型")))
.property("bld_resolution", &RegisterClassName::bld_resolution)(rttr::metadata("cn",std::string("融合精度")))
.property("bld_area_latu", &RegisterClassName::bld_area_latu)(rttr::metadata("cn",std::string("最大纬度")))
.property("bld_area_latb", &RegisterClassName::bld_area_latb)(rttr::metadata("cn",std::string("最小纬度")))
.property("bld_area_lonl", &RegisterClassName::bld_area_lonl)(rttr::metadata("cn",std::string("最小经度")))
.property("bld_area_lonr", &RegisterClassName::bld_area_lonr)(rttr::metadata("cn",std::string("最大经度")))
.property("bld_date_start", &RegisterClassName::bld_date_start)(rttr::metadata("cn",std::string("起始日期")))
.property("bld_date_end", &RegisterClassName::bld_date_end)(rttr::metadata("cn",std::string("终止日期")))
.property("l4_outdir", &RegisterClassName::l4_outdir)(rttr::metadata("cn",std::string("输出路径")))
.property("l4_outpattern", &RegisterClassName::l4_outpattern)(rttr::metadata("cn",std::string("输出路径")))
.property("xml_path", &RegisterClassName::xml_path)(rttr::metadata("cn",std::string("XML文件路径")))
.property("create_time", &RegisterClassName::create_time)(rttr::metadata("cn",std::string("创建时间")))
.property("extend1", &RegisterClassName::extend1)(rttr::metadata("cn",std::string("扩展字段1")))
.property("extend2", &RegisterClassName::extend2)(rttr::metadata("cn",std::string("扩展字段2")))
.property("extend3", &RegisterClassName::extend3)(rttr::metadata("cn",std::string("扩展字段3")))
.property("extend4", &RegisterClassName::extend4)(rttr::metadata("cn",std::string("扩展字段4")))
.property("extend5", &RegisterClassName::extend5)(rttr::metadata("cn",std::string("扩展字段5")))

    ;
}
