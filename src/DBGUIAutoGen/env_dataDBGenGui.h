#ifndef env_data_DB_GUI_GEN_H
#define env_data_DB_GUI_GEN_H

#include "DBBaseAutoGen/BaseDBInfo.h"
#include "DBBaseAutoGen/BaseDBWidget.h"
#include "DBBaseAutoGen/BaseDBWidgetHelper.h"
#include "DBBaseAutoGen/BaseDBMacro.h"
#include "DBDataAutoGen/env_dataStruct.h"

namespace DBAG {
	DataStructDBGuiHelperClassDeclaration(env_dataDBGenDao, env_data);

	class env_dataDBGenGui : public BaseDBWidget {
		Q_OBJECT
	public:

		env_dataDBGenGui(BaseDBWidget* parent = nullptr);

		virtual ~env_dataDBGenGui() = default;

		void onSearchBtonClicked() override;

		void onDeleteBtonClicked() override;

		std::optional<env_data> getSelectRowObj(int row);

		std::string getSelectRowColumeText(int row, int column);

	protected:

		void loadDefaultTableHeader() override;

		env_dataDBGenGuiHelper _helper;
	};
}

#endif