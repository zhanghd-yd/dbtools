#include "BaseDBData.h"
#include "glog/logging.h"
#include <assert.h>

DBAG::FieldType DBAG::getFieldType(std::string_view fieldTypeName)
{
	using namespace rttr;
	enumeration enum_align = type::get_by_name("DBAG::FieldType").get_enumeration();
	variant var = enum_align.name_to_value(fieldTypeName.data());

	DLOG(INFO) << "getSupportWhereCond: " << fieldTypeName.data();
	assert(var.is_valid());

	FieldType enum_value = var.get_value<DBAG::FieldType>();
	return enum_value;
}

std::string DBAG::getWhereCondWidgetText(DBAG::WhereCond cond)
{
	static std::map<DBAG::WhereCond, std::string> map = {
		{DBAG::WhereCond::EQUAL,"="},
		{DBAG::WhereCond::LESS,"<" },
		{DBAG::WhereCond::LESSEQUAL,"<="},
		{DBAG::WhereCond::MORE, ">"},
		{DBAG::WhereCond::MOREEQUAL, ">="},
		{DBAG::WhereCond::IN, "in"},

		{DBAG::WhereCond::EQUALSTRING, "="},
		{DBAG::WhereCond::LIKE, "like"},

		{ DBAG::WhereCond::DATEEQUAL, "=" },
		{ DBAG::WhereCond::DATELESS, "<" },
		{ DBAG::WhereCond::DATELESSEQUAL, "<=" },
		{ DBAG::WhereCond::DATEMORE, ">" },
		{ DBAG::WhereCond::DATEMOREEQUAL, ">="},

		{ DBAG::WhereCond::DATETIMEEQUAL, "=" },
		{ DBAG::WhereCond::DATETIMELESS, "<" },
		{ DBAG::WhereCond::DATETIMELESSEQUAL, "<=" },
		{ DBAG::WhereCond::DATETIMEMORE, ">" },
		{ DBAG::WhereCond::DATETIMEMOREEQUAL,">="}
	};

	auto it = map.find(cond);
	if (it == map.end()) {
		LOG(WARNING) << "getWhereCondWidgetText";
		assert(false);
	}

	return it->second;
}

std::pair<int, int> DBAG::getSupportWhereCondRange(std::string_view fieldTypeName)
{
	return getSupportWhereCondRange(getFieldType(fieldTypeName));
}

std::pair<int, int> DBAG::getSupportWhereCondRange(FieldType type)
{
	int startPos = 0;
	int endPos = 0;
	switch (type)
	{
	case DBAG::FieldType::INT:
	case DBAG::FieldType::LONGLONG:
	case DBAG::FieldType::FLOAT:
	case DBAG::FieldType::DOUBLE: {
		startPos = 0;
		endPos = 99;
		break;
	}
	case DBAG::FieldType::STRING: {
		startPos = 100;
		endPos = 199;
		break;
	}
	case DBAG::FieldType::DATE: {
		startPos = 200;
		endPos = 299;
		break;
	}
	case DBAG::FieldType::DATETIME: {
		startPos = 300;
		endPos = 399;
		break;
	}
	default: {
		assert(false);
		break;
	}
	}
	return { startPos ,endPos };
}

std::vector<DBAG::WhereCond> DBAG::getSupportWhereCond(std::string_view fieldTypeName)
{
	using namespace rttr;
	enumeration enum_align = type::get_by_name("DBAG::FieldType").get_enumeration();
	variant var = enum_align.name_to_value(fieldTypeName.data());

	DLOG(INFO) << "getSupportWhereCond: " << fieldTypeName.data() << "  " << var.is_valid();
	assert(var.is_valid());

	FieldType enum_value = var.get_value<DBAG::FieldType>();
	return getSupportWhereCond(enum_value);
}

std::vector<DBAG::WhereCond> DBAG::getSupportWhereCond(FieldType type) {
	std::vector<DBAG::WhereCond> list;
	using namespace rttr;
	enumeration enum_align = type::get_by_name("DBAG::WhereCond").get_enumeration();

	auto range = getSupportWhereCondRange(type);

	//const auto& names = enum_align.get_names();
	const auto& values = enum_align.get_values();
	for (auto it = values.begin(); it != values.end(); it++) {
		auto v = it->to_int();
		if (v >= range.first && v <= range.second) {
			//auto name = enum_align.value_to_name(static_cast<WhereCond>(v));
			list.emplace_back(static_cast<WhereCond>(v));
		}
	}

	return move(list);
}

bool DBAG::checkSupportWhereCond(FieldType type, WhereCond cond)
{
	auto range = getSupportWhereCondRange(type);

	int v = static_cast<int>(cond);
	return v >= range.first && v <= range.second;
}

RTTR_REGISTRATION
{
	using namespace rttr;
	registration::enumeration<DBAG::FieldType>("DBAG::FieldType")(
		value("INT",		DBAG::FieldType::INT),
		value("LONGLONG",	DBAG::FieldType::LONGLONG),
		value("FLOAT",      DBAG::FieldType::FLOAT),
		value("DOUBLE",     DBAG::FieldType::DOUBLE),
		value("STRING",     DBAG::FieldType::STRING),
		value("DATE",		DBAG::FieldType::DATE),
		value("DATETIME",   DBAG::FieldType::DATETIME)
	);

	registration::enumeration<DBAG::WhereCond>("DBAG::WhereCond")(
		value("EQUAL",			DBAG::WhereCond::EQUAL),
		value("LESS",			DBAG::WhereCond::LESS),
		value("LESSEQUAL",		DBAG::WhereCond::LESSEQUAL),
		value("MORE",			DBAG::WhereCond::MORE),
		value("MOREEQUAL",		DBAG::WhereCond::MOREEQUAL),
		value("IN",				DBAG::WhereCond::IN),

		value("STRINGEQUAL",	DBAG::WhereCond::EQUALSTRING),
		value("LIKE",			DBAG::WhereCond::LIKE),

		value("DATEEQUAL",		DBAG::WhereCond::DATEEQUAL),
		value("DATELESS",		DBAG::WhereCond::DATELESS),
		value("DATELESSEQUAL",	DBAG::WhereCond::DATELESSEQUAL),
		value("DATEMORE",		DBAG::WhereCond::DATEMORE),
		value("DATEMOREEQUAL", DBAG::WhereCond::DATEMORE),

		value("DATEMOREEQUAL",		DBAG::WhereCond::DATEMOREEQUAL),
		value("DATETIMEEQUAL",		DBAG::WhereCond::DATETIMEEQUAL),
		value("DATETIMELESS",		DBAG::WhereCond::DATETIMELESS),
		value("DATETIMELESSEQUAL",	DBAG::WhereCond::DATETIMELESSEQUAL),
		value("DATETIMEMORE",		DBAG::WhereCond::DATETIMEMORE),
		value("DATETIMEMOREEQUA",	DBAG::WhereCond::DATETIMEMOREEQUAL)
	);

	rttr::registration::class_<DBAG::FieldSelected>("DBAG::FieldSelected")
		.property("Value", &DBAG::FieldSelected::_value)
		.property("Cond", &DBAG::FieldSelected::_cond)
		.property("TableRow", &DBAG::FieldSelected::_tablerow)
		.property("Enable", &DBAG::FieldSelected::_enable)
		;

	rttr::registration::class_<DBAG::FieldInfo>("DBAG::FieldInfo")
		.property("Field", &DBAG::FieldInfo::_field)
		.property("Type", &DBAG::FieldInfo::_type)
		.property("Length", &DBAG::FieldInfo::_length)
		.property("Precision", &DBAG::FieldInfo::_precision)
		.property("Scale", &DBAG::FieldInfo::_scale)
		.property("Nullable", &DBAG::FieldInfo::_nullable)
		.property("Comment", &DBAG::FieldInfo::_comment)
		.property("Selected", &DBAG::FieldInfo::_selecteds)
		.property("MaxNumber", &DBAG::FieldInfo::_max_value)
		.property("MinNumber", &DBAG::FieldInfo::_min_value)
		;

	rttr::registration::class_<DBAG::TableKey>("DBAG::TableKey")
		.property("Column", &DBAG::TableKey::_column)
		.property("Increment", &DBAG::TableKey::_increment)
		;

	rttr::registration::class_<DBAG::TableConfig>("DBAG::TableConfig")
		.constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
		.property("Table", &DBAG::TableConfig::_table)
		.property("Key", &DBAG::TableConfig::_key)
		.property("Column", &DBAG::TableConfig::_fields)
		.property("QueryCount", &DBAG::TableConfig::_query_table_rowcount)
		;

}