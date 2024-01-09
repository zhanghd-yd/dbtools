
#ifndef sstr_DB_GUI_GEN_H
#define sstr_DB_GUI_GEN_H

#include "DBBaseAutoGen/BaseDBInfo.h"
#include "DBBaseAutoGen/BaseDBWidget.h"
#include "DBBaseAutoGen/BaseDBWidgetHelper.h"
#include "DBBaseAutoGen/BaseDBMacro.h"
#include "DBDataAutoGen/sstrStruct.h"

namespace DBAG {
	DataStructDBGuiHelperClassDeclaration(sstrDBGenDao, sstr);

	class sstrDBGenGui : public BaseDBWidget {
		Q_OBJECT
	public:

		sstrDBGenGui(BaseDBWidget* parent = nullptr);

		virtual ~sstrDBGenGui() = default;

		void onSearchBtonClicked() override;

		void onDeleteBtonClicked() override;

		std::optional<sstr> getSelectRowObj(int row);

		std::string getSelectRowColumeText(int row, int column);

	protected:

		void loadDefaultTableHeader() override;

		sstrDBGenGuiHelper _helper;
	};
}

#endif
