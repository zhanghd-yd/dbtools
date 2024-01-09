
#ifndef ioofcpt_DB_GUI_GEN_H
#define ioofcpt_DB_GUI_GEN_H

#include "DBBaseAutoGen/BaseDBInfo.h"
#include "DBBaseAutoGen/BaseDBWidget.h"
#include "DBBaseAutoGen/BaseDBWidgetHelper.h"
#include "DBBaseAutoGen/BaseDBMacro.h"
#include "DBDataAutoGen/ioofcptStruct.h"

namespace DBAG {
	DataStructDBGuiHelperClassDeclaration(ioofcptDBGenDao, ioofcpt);

	class ioofcptDBGenGui : public BaseDBWidget {
		Q_OBJECT
	public:

		ioofcptDBGenGui(BaseDBWidget* parent = nullptr);

		virtual ~ioofcptDBGenGui() = default;

		void onSearchBtonClicked() override;

		void onDeleteBtonClicked() override;

		std::optional<ioofcpt> getSelectRowObj(int row);

		std::string getSelectRowColumeText(int row, int column);

	protected:

		void loadDefaultTableHeader() override;

		ioofcptDBGenGuiHelper _helper;
	};
}

#endif
