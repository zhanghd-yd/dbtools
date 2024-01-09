
#ifndef ioovcpt_DB_GUI_GEN_H
#define ioovcpt_DB_GUI_GEN_H

#include "DBBaseAutoGen/BaseDBInfo.h"
#include "DBBaseAutoGen/BaseDBWidget.h"
#include "DBBaseAutoGen/BaseDBWidgetHelper.h"
#include "DBBaseAutoGen/BaseDBMacro.h"
#include "DBDataAutoGen/ioovcptStruct.h"

namespace DBAG {
	DataStructDBGuiHelperClassDeclaration(ioovcptDBGenDao, ioovcpt);

	class ioovcptDBGenGui : public BaseDBWidget {
		Q_OBJECT
	public:

		ioovcptDBGenGui(BaseDBWidget* parent = nullptr);

		virtual ~ioovcptDBGenGui() = default;

		void onSearchBtonClicked() override;

		void onDeleteBtonClicked() override;

		std::optional<ioovcpt> getSelectRowObj(int row);

		std::string getSelectRowColumeText(int row, int column);

	protected:

		void loadDefaultTableHeader() override;

		ioovcptDBGenGuiHelper _helper;
	};
}

#endif
