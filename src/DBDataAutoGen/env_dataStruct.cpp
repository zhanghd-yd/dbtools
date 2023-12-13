
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
		.property("NcFileDataName", &RegisterClassName::NcFileDataName)
		.property("Name", &RegisterClassName::Name)
		.property("TimeStamp", &RegisterClassName::TimeStamp)
		.property("LonBegin", &RegisterClassName::LonBegin)
		.property("LonEnd", &RegisterClassName::LonEnd)
		.property("LonStep", &RegisterClassName::LonStep)
		.property("LonCount", &RegisterClassName::LonCount)
		.property("LatBegin", &RegisterClassName::LatBegin)
		.property("LatEnd", &RegisterClassName::LatEnd)
		.property("LatStep", &RegisterClassName::LatStep)
		.property("LatCount", &RegisterClassName::LatCount)
		.property("DepthBegin", &RegisterClassName::DepthBegin)
		.property("DepthEnd", &RegisterClassName::DepthEnd)
		.property("DepthStep", &RegisterClassName::DepthStep)
		.property("DepthCount", &RegisterClassName::DepthCount)
		.property("MD5", &RegisterClassName::MD5)
		;
}
