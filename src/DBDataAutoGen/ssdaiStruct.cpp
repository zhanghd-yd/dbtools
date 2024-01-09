
#include "ssdaiStruct.h"

#define RegisterClassName DBAG::ssdai

std::string& DBAG::ssdaiDBGenDao::getTableName()
{
    static std::string t = "ssdai";
    return t;
}

std::string& DBAG::ssdaiDBGenDao::getPrimarykey()
{
    static std::string t = "md5";
    return t;
}

std::vector<std::string> DBAG::ssdaiDBGenDao::getColumnList()
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
    rttr::registration::class_<RegisterClassName>("DBAG::ssdai")
		.constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
        .property("md5", &RegisterClassName::md5)(rttr::metadata("cn",std::string("编号")))
.property("h2b_l2_nc", &RegisterClassName::h2b_l2_nc)(rttr::metadata("cn",std::string("输入文件名")))
.property("sla_l3_result", &RegisterClassName::sla_l3_result)(rttr::metadata("cn",std::string("输出文件名")))
.property("xml_path", &RegisterClassName::xml_path)(rttr::metadata("cn",std::string("XML文件路径")))
.property("create_time", &RegisterClassName::create_time)(rttr::metadata("cn",std::string("创建时间")))
.property("extend1", &RegisterClassName::extend1)(rttr::metadata("cn",std::string("扩展字段1")))
.property("extend2", &RegisterClassName::extend2)(rttr::metadata("cn",std::string("扩展字段2")))
.property("extend3", &RegisterClassName::extend3)(rttr::metadata("cn",std::string("扩展字段3")))
.property("extend4", &RegisterClassName::extend4)(rttr::metadata("cn",std::string("扩展字段4")))
.property("extend5", &RegisterClassName::extend5)(rttr::metadata("cn",std::string("扩展字段5")))

    ;
}
