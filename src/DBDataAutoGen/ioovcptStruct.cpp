
#include "ioovcptStruct.h"

#define RegisterClassName DBAG::ioovcpt

std::string& DBAG::ioovcptDBGenDao::getTableName()
{
    static std::string t = "ioovcpt";
    return t;
}

std::string& DBAG::ioovcptDBGenDao::getPrimarykey()
{
    static std::string t = "md5";
    return t;
}

std::vector<std::string> DBAG::ioovcptDBGenDao::getColumnList()
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
    rttr::registration::class_<RegisterClassName>("DBAG::ioovcpt")
		.constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
        .property("md5", &RegisterClassName::md5)(rttr::metadata("cn",std::string("编号")))
.property("lat_min", &RegisterClassName::lat_min)(rttr::metadata("cn",std::string("最小纬度")))
.property("lat_max", &RegisterClassName::lat_max)(rttr::metadata("cn",std::string("最大纬度")))
.property("lon_min", &RegisterClassName::lon_min)(rttr::metadata("cn",std::string("最小经度")))
.property("lon_max", &RegisterClassName::lon_max)(rttr::metadata("cn",std::string("最大经度")))
.property("date_start", &RegisterClassName::date_start)(rttr::metadata("cn",std::string("起始日期")))
.property("date_end", &RegisterClassName::date_end)(rttr::metadata("cn",std::string("终止日期")))
.property("date_type", &RegisterClassName::date_type)(rttr::metadata("cn",std::string("日期类型 1： yyyy-MM-dd 2：yyyy-MM")))
.property("amplitude_threshold", &RegisterClassName::amplitude_threshold)(rttr::metadata("cn",std::string("涡旋振幅阈值 cm")))
.property("radius_threshold", &RegisterClassName::radius_threshold)(rttr::metadata("cn",std::string("涡旋半径阈值 km")))
.property("in_dir", &RegisterClassName::in_dir)(rttr::metadata("cn",std::string("输入路径")))
.property("out_dir", &RegisterClassName::out_dir)(rttr::metadata("cn",std::string("输出路径")))
.property("xml_path", &RegisterClassName::xml_path)(rttr::metadata("cn",std::string("XML文件路径")))
.property("create_time", &RegisterClassName::create_time)(rttr::metadata("cn",std::string("创建时间")))
.property("extend1", &RegisterClassName::extend1)(rttr::metadata("cn",std::string("扩展字段1")))
.property("extend2", &RegisterClassName::extend2)(rttr::metadata("cn",std::string("扩展字段2")))
.property("extend3", &RegisterClassName::extend3)(rttr::metadata("cn",std::string("扩展字段3")))
.property("extend4", &RegisterClassName::extend4)(rttr::metadata("cn",std::string("扩展字段4")))
.property("extend5", &RegisterClassName::extend5)(rttr::metadata("cn",std::string("扩展字段5")))

    ;
}
