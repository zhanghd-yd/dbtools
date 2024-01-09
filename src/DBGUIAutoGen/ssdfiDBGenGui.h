
#ifndef ssdfi_DB_GUI_GEN_H
#define ssdfi_DB_GUI_GEN_H

#include "DBBaseAutoGen/BaseDBInfo.h"
#include "DBBaseAutoGen/BaseDBWidget.h"
#include "DBBaseAutoGen/BaseDBWidgetHelper.h"
#include "DBBaseAutoGen/BaseDBMacro.h"
#include "DBDataAutoGen/ssdfiStruct.h"

namespace DBAG {
	DataStructDBGuiHelperClassDeclaration(ssdfiDBGenDao, ssdfi);

	class ssdfiDBGenGui : public BaseDBWidget {
		Q_OBJECT
	public:

		ssdfiDBGenGui(BaseDBWidget* parent = nullptr);

		virtual ~ssdfiDBGenGui() = default;

		void onSearchBtonClicked() override;

		void onDeleteBtonClicked() override;

		std::optional<ssdfi> getSelectRowObj(int row);

		std::string getSelectRowColumeText(int row, int column);

	protected:

		void loadDefaultTableHeader() override;

		ssdfiDBGenGuiHelper _helper;
	};
}

#endif
