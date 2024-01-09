
#ifndef sea_temp_fusion_DB_GUI_GEN_H
#define sea_temp_fusion_DB_GUI_GEN_H

#include "DBBaseAutoGen/BaseDBInfo.h"
#include "DBBaseAutoGen/BaseDBWidget.h"
#include "DBBaseAutoGen/BaseDBWidgetHelper.h"
#include "DBBaseAutoGen/BaseDBMacro.h"
#include "DBDataAutoGen/sea_temp_fusionStruct.h"

namespace DBAG {
	DataStructDBGuiHelperClassDeclaration(sea_temp_fusionDBGenDao, sea_temp_fusion);

	class sea_temp_fusionDBGenGui : public BaseDBWidget {
		Q_OBJECT
	public:

		sea_temp_fusionDBGenGui(BaseDBWidget* parent = nullptr);

		virtual ~sea_temp_fusionDBGenGui() = default;

		void onSearchBtonClicked() override;

		void onDeleteBtonClicked() override;

		std::optional<sea_temp_fusion> getSelectRowObj(int row);

		std::string getSelectRowColumeText(int row, int column);

	protected:

		void loadDefaultTableHeader() override;

		sea_temp_fusionDBGenGuiHelper _helper;
	};
}

#endif
