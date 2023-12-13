#include "TestStruct.h"

#define RegisterClassName DBAG::Test

std::string& DBAG::TestDBGenDao::getTableName()
{
	static std::string t = "Test";
	return t;
}

std::string& DBAG::TestDBGenDao::getPrimarykey()
{
	static std::string t = "id";
	return t;
}

std::vector<std::string> DBAG::TestDBGenDao::getColumnList()
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
	rttr::registration::class_<RegisterClassName>("DBAG::Test")
		.constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
		.property("id", &RegisterClassName::id)
		.property("name", &RegisterClassName::name)
		.property("score", &RegisterClassName::score)
		.property("date", &RegisterClassName::date)
	;
}