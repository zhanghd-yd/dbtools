
#include "ioofcptStruct.h"

#define RegisterClassName DBAG::ioofcpt

std::string& DBAG::ioofcptDBGenDao::getTableName()
{
    static std::string t = "ioofcpt";
    return t;
}

std::string& DBAG::ioofcptDBGenDao::getPrimarykey()
{
    static std::string t = "md5";
    return t;
}

std::vector<std::string> DBAG::ioofcptDBGenDao::getColumnList()
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
    rttr::registration::class_<RegisterClassName>("DBAG::ioofcpt")
		.constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
        .property("md5", &RegisterClassName::md5)(rttr::metadata("cn",std::string("编号")))
.property("lat_min", &RegisterClassName::lat_min)(rttr::metadata("cn",std::string("最小纬度")))
.property("lat_max", &RegisterClassName::lat_max)(rttr::metadata("cn",std::string("最大纬度")))
.property("lon_min", &RegisterClassName::lon_min)(rttr::metadata("cn",std::string("最小经度")))
.property("lon_max", &RegisterClassName::lon_max)(rttr::metadata("cn",std::string("最大经度")))
.property("date_start", &RegisterClassName::date_start)(rttr::metadata("cn",std::string("起始日期")))
.property("date_end", &RegisterClassName::date_end)(rttr::metadata("cn",std::string("终止日期")))
.property("date_type", &RegisterClassName::date_type)(rttr::metadata("cn",std::string("日期类型 1.yyyy-MM-dd 2.yyyy-MM")))
.property("in_dir", &RegisterClassName::in_dir)(rttr::metadata("cn",std::string("输入路径")))
.property("out_dir", &RegisterClassName::out_dir)(rttr::metadata("cn",std::string("输出路径")))
.property("temp_throd", &RegisterClassName::temp_throd)(rttr::metadata("cn",std::string("温度梯度阈值")))
.property("bwareaopen_num", &RegisterClassName::bwareaopen_num)(rttr::metadata("cn",std::string("小面积参数")))
.property("imdilate_num", &RegisterClassName::imdilate_num)(rttr::metadata("cn",std::string("膨胀参数")))
.property("imerode_num", &RegisterClassName::imerode_num)(rttr::metadata("cn",std::string("腐蚀参数")))
.property("bwmorph_num", &RegisterClassName::bwmorph_num)(rttr::metadata("cn",std::string("毛刺参数")))
.property("xml_path", &RegisterClassName::xml_path)(rttr::metadata("cn",std::string("XML文件路径")))
.property("create_time", &RegisterClassName::create_time)(rttr::metadata("cn",std::string("创建时间")))
.property("extend1", &RegisterClassName::extend1)(rttr::metadata("cn",std::string("扩展字段1")))
.property("extend2", &RegisterClassName::extend2)(rttr::metadata("cn",std::string("扩展字段2")))
.property("extend3", &RegisterClassName::extend3)(rttr::metadata("cn",std::string("扩展字段3")))
.property("extend4", &RegisterClassName::extend4)(rttr::metadata("cn",std::string("扩展字段4")))
.property("extend5", &RegisterClassName::extend5)(rttr::metadata("cn",std::string("扩展字段5")))

    ;
}
