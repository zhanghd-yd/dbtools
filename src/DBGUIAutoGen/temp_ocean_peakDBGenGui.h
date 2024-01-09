
#ifndef temp_ocean_peak_DB_GUI_GEN_H
#define temp_ocean_peak_DB_GUI_GEN_H

#include "DBBaseAutoGen/BaseDBInfo.h"
#include "DBBaseAutoGen/BaseDBWidget.h"
#include "DBBaseAutoGen/BaseDBWidgetHelper.h"
#include "DBBaseAutoGen/BaseDBMacro.h"
#include "DBDataAutoGen/temp_ocean_peakStruct.h"

namespace DBAG {
	DataStructDBGuiHelperClassDeclaration(temp_ocean_peakDBGenDao, temp_ocean_peak);

	class temp_ocean_peakDBGenGui : public BaseDBWidget {
		Q_OBJECT
	public:

		temp_ocean_peakDBGenGui(BaseDBWidget* parent = nullptr);

		virtual ~temp_ocean_peakDBGenGui() = default;

		void onSearchBtonClicked() override;

		void onDeleteBtonClicked() override;

		std::optional<temp_ocean_peak> getSelectRowObj(int row);

		std::string getSelectRowColumeText(int row, int column);

	protected:

		void loadDefaultTableHeader() override;

		temp_ocean_peakDBGenGuiHelper _helper;
	};
}

#endif
