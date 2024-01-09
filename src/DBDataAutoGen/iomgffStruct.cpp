
#include "iomgffStruct.h"

#define RegisterClassName DBAG::iomgff

std::string& DBAG::iomgffDBGenDao::getTableName()
{
    static std::string t = "iomgff";
    return t;
}

std::string& DBAG::iomgffDBGenDao::getPrimarykey()
{
    static std::string t = "md5";
    return t;
}

std::vector<std::string> DBAG::iomgffDBGenDao::getColumnList()
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
    rttr::registration::class_<RegisterClassName>("DBAG::iomgff")
		.constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
        .property("md5", &RegisterClassName::md5)(rttr::metadata("cn",std::string("编号")))
.property("allsat_l4_nc", &RegisterClassName::allsat_l4_nc)(rttr::metadata("cn",std::string("输入文件")))
.property("lat_max", &RegisterClassName::lat_max)(rttr::metadata("cn",std::string("最大纬度")))
.property("lat_min", &RegisterClassName::lat_min)(rttr::metadata("cn",std::string("最小纬度")))
.property("lon_max", &RegisterClassName::lon_max)(rttr::metadata("cn",std::string("最大经度")))
.property("lon_min", &RegisterClassName::lon_min)(rttr::metadata("cn",std::string("最小经度")))
.property("csv_result", &RegisterClassName::csv_result)(rttr::metadata("cn",std::string("输出文件")))
.property("xml_path", &RegisterClassName::xml_path)(rttr::metadata("cn",std::string("XML文件路径")))
.property("create_time", &RegisterClassName::create_time)(rttr::metadata("cn",std::string("创建时间")))
.property("extend1", &RegisterClassName::extend1)(rttr::metadata("cn",std::string("扩展字段1")))
.property("extend2", &RegisterClassName::extend2)(rttr::metadata("cn",std::string("扩展字段2")))
.property("extend3", &RegisterClassName::extend3)(rttr::metadata("cn",std::string("扩展字段3")))
.property("extend4", &RegisterClassName::extend4)(rttr::metadata("cn",std::string("扩展字段4")))
.property("extend5", &RegisterClassName::extend5)(rttr::metadata("cn",std::string("扩展字段5")))

    ;
}
