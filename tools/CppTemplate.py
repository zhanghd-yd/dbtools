# -*- coding:utf-8 -*-


cfile = """
#ifndef %s_STRUCT_H
#define %s_STRUCT_H

#include "DBBaseAutoGen/BaseDBInfo.h"

#include <type_traits>
#include <rttr/registration>

namespace DBAG
{
    %s

    class %sDBGenDao : public BaseDBDao {
        public:

        virtual std::string& getTableName() override;

        virtual std::string& getPrimarykey() override;

        virtual std::vector<std::string> getColumnList() override;
    };
} // namespace DBAG

#endif
"""

cppFile = """
#include "%sStruct.h"

#define RegisterClassName DBAG::%s

std::string& DBAG::%sDBGenDao::getTableName()
{
    static std::string t = "%s";
    return t;
}

std::string& DBAG::%sDBGenDao::getPrimarykey()
{
    static std::string t = "%s";
    return t;
}

std::vector<std::string> DBAG::%sDBGenDao::getColumnList()
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
    rttr::registration::class_<RegisterClassName>("DBAG::%s")
		.constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
        %s
    ;
}
"""

guihFile = """
#ifndef %s_DB_GUI_GEN_H
#define %s_DB_GUI_GEN_H

#include "DBBaseAutoGen/BaseDBInfo.h"
#include "DBBaseAutoGen/BaseDBWidget.h"
#include "DBBaseAutoGen/BaseDBWidgetHelper.h"
#include "DBBaseAutoGen/BaseDBMacro.h"
#include "DBDataAutoGen/%sStruct.h"

namespace DBAG {
	DataStructDBGuiHelperClassDeclaration(%sDBGenDao, %s);

	class %sDBGenGui : public BaseDBWidget {
		Q_OBJECT
	public:

		%sDBGenGui(BaseDBWidget* parent = nullptr);

		virtual ~%sDBGenGui() = default;

		void onSearchBtonClicked() override;

		void onDeleteBtonClicked() override;

		std::optional<%s> getSelectRowObj(int row);

		std::string getSelectRowColumeText(int row, int column);

	protected:

		void loadDefaultTableHeader() override;

		%sDBGenGuiHelper _helper;
	};
}

#endif
"""

guicppFile = """
#include "%sDBGenGui.h"

DataStructDBGuiClassDefinition(%s);
"""
