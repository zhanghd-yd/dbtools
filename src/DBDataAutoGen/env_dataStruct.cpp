#include "env_dataStruct.h"

#define RegisterClassName DBAG::env_data

std::string& DBAG::env_dataDBGenDao::getTableName()
{
	static std::string t = "env_data";
	return t;
}

std::string& DBAG::env_dataDBGenDao::getPrimarykey()
{
	static std::string t = "NcFileDataName";
	return t;
}

std::vector<std::string> DBAG::env_dataDBGenDao::getColumnList()
{
	std::vector<std::string> list;
	rttr::type t = rttr::type::get<RegisterClassName>();
	for (auto& prop : t.get_properties()) {
		list.emplace_back(prop.get_name().to_string());
	}

	return move(list);
}

RTTR_REGISTRATION
{
	rttr::registration::class_<RegisterClassName>("DBAG::env_data")
		.property("NcFileDataName", &RegisterClassName::NcFileDataName)(rttr::metadata("cn",std::string("处理后的数据文件名")))
		.property("Name", &RegisterClassName::Name)(rttr::metadata("cn",u8"环境数据属性名"))
		.property("TimeStamp", &RegisterClassName::TimeStamp)(rttr::metadata("cn",u8"试验时间"))
		.property("LonBegin", &RegisterClassName::LonBegin)(rttr::metadata("cn",u8"起始经度"))
		.property("LonEnd", &RegisterClassName::LonEnd)(rttr::metadata("cn",u8"终止经度"))
		.property("LonStep", &RegisterClassName::LonStep)(rttr::metadata("cn",u8"经度跨度"))
		.property("LonCount", &RegisterClassName::LonCount)(rttr::metadata("cn",u8"经度数量"))
		.property("LatBegin", &RegisterClassName::LatBegin)(rttr::metadata("cn",u8"起始纬度"))
		.property("LatEnd", &RegisterClassName::LatEnd)(rttr::metadata("cn",u8"终止纬度"))
		.property("LatStep", &RegisterClassName::LatStep)(rttr::metadata("cn",u8"纬度跨步"))
		.property("LatCount", &RegisterClassName::LatCount)(rttr::metadata("cn",u8"纬度数量"))
		.property("DepthBegin", &RegisterClassName::DepthBegin)(rttr::metadata("cn",u8"起始深度"))
		.property("DepthEnd", &RegisterClassName::DepthEnd)(rttr::metadata("cn",u8"终止深度"))
		.property("DepthStep", &RegisterClassName::DepthStep)(rttr::metadata("cn",u8"深度跨度"))
		.property("DepthCount", &RegisterClassName::DepthCount)(rttr::metadata("cn",u8"深度数量"))
		.property("MD5", &RegisterClassName::MD5)(rttr::metadata("cn",u8"nc文件md5验证码"))
		;
}
