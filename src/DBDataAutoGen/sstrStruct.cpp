
#include "sstrStruct.h"

#define RegisterClassName DBAG::sstr

std::string& DBAG::sstrDBGenDao::getTableName()
{
    static std::string t = "sstr";
    return t;
}

std::string& DBAG::sstrDBGenDao::getPrimarykey()
{
    static std::string t = "md5";
    return t;
}

std::vector<std::string> DBAG::sstrDBGenDao::getColumnList()
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
    rttr::registration::class_<RegisterClassName>("DBAG::sstr")
		.constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
        .property("md5", &RegisterClassName::md5)(rttr::metadata("cn",std::string("编号")))
.property("dir_install", &RegisterClassName::dir_install)(rttr::metadata("cn",std::string("可执行程序路径")))
.property("dir_input", &RegisterClassName::dir_input)(rttr::metadata("cn",std::string("文件输入路径")))
.property("dir_output", &RegisterClassName::dir_output)(rttr::metadata("cn",std::string("文件输出路径")))
.property("dir_parameter", &RegisterClassName::dir_parameter)(rttr::metadata("cn",std::string("参数配置路径")))
.property("source_l1b", &RegisterClassName::source_l1b)(rttr::metadata("cn",std::string("L1B数据源类型")))
.property("source_refsst", &RegisterClassName::source_refsst)(rttr::metadata("cn",std::string("背景场数据源类型")))
.property("outfile_name", &RegisterClassName::outfile_name)(rttr::metadata("cn",std::string("输出文件命名格式")))
.property("time_start", &RegisterClassName::time_start)(rttr::metadata("cn",std::string("起始日期")))
.property("time_end", &RegisterClassName::time_end)(rttr::metadata("cn",std::string("终止日期")))
.property("lon_start", &RegisterClassName::lon_start)(rttr::metadata("cn",std::string("起始经度")))
.property("lon_end", &RegisterClassName::lon_end)(rttr::metadata("cn",std::string("结束经度")))
.property("lat_start", &RegisterClassName::lat_start)(rttr::metadata("cn",std::string("起始纬度")))
.property("lat_end", &RegisterClassName::lat_end)(rttr::metadata("cn",std::string("结束纬度")))
.property("region_name", &RegisterClassName::region_name)(rttr::metadata("cn",std::string("区域名称")))
.property("bias_region", &RegisterClassName::bias_region)(rttr::metadata("cn",std::string("空间误差")))
.property("xml_path", &RegisterClassName::xml_path)(rttr::metadata("cn",std::string("XML文件路径")))
.property("create_time", &RegisterClassName::create_time)(rttr::metadata("cn",std::string("创建时间")))
.property("extend1", &RegisterClassName::extend1)(rttr::metadata("cn",std::string("扩展字段1")))
.property("extend2", &RegisterClassName::extend2)(rttr::metadata("cn",std::string("扩展字段2")))
.property("extend3", &RegisterClassName::extend3)(rttr::metadata("cn",std::string("扩展字段3")))
.property("extend4", &RegisterClassName::extend4)(rttr::metadata("cn",std::string("扩展字段4")))
.property("extend5", &RegisterClassName::extend5)(rttr::metadata("cn",std::string("扩展字段5")))

    ;
}
