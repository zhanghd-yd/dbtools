
#ifndef iomgff_DB_GUI_GEN_H
#define iomgff_DB_GUI_GEN_H

#include "DBBaseAutoGen/BaseDBInfo.h"
#include "DBBaseAutoGen/BaseDBWidget.h"
#include "DBBaseAutoGen/BaseDBWidgetHelper.h"
#include "DBBaseAutoGen/BaseDBMacro.h"
#include "DBDataAutoGen/iomgffStruct.h"

namespace DBAG {
	DataStructDBGuiHelperClassDeclaration(iomgffDBGenDao, iomgff);

	class iomgffDBGenGui : public BaseDBWidget {
		Q_OBJECT
	public:

		iomgffDBGenGui(BaseDBWidget* parent = nullptr);

		virtual ~iomgffDBGenGui() = default;

		void onSearchBtonClicked() override;

		void onDeleteBtonClicked() override;

		std::optional<iomgff> getSelectRowObj(int row);

		std::string getSelectRowColumeText(int row, int column);

	protected:

		void loadDefaultTableHeader() override;

		iomgffDBGenGuiHelper _helper;
	};
}

#endif
