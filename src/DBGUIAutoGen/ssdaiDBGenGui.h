
#ifndef ssdai_DB_GUI_GEN_H
#define ssdai_DB_GUI_GEN_H

#include "DBBaseAutoGen/BaseDBInfo.h"
#include "DBBaseAutoGen/BaseDBWidget.h"
#include "DBBaseAutoGen/BaseDBWidgetHelper.h"
#include "DBBaseAutoGen/BaseDBMacro.h"
#include "DBDataAutoGen/ssdaiStruct.h"

namespace DBAG {
	DataStructDBGuiHelperClassDeclaration(ssdaiDBGenDao, ssdai);

	class ssdaiDBGenGui : public BaseDBWidget {
		Q_OBJECT
	public:

		ssdaiDBGenGui(BaseDBWidget* parent = nullptr);

		virtual ~ssdaiDBGenGui() = default;

		void onSearchBtonClicked() override;

		void onDeleteBtonClicked() override;

		std::optional<ssdai> getSelectRowObj(int row);

		std::string getSelectRowColumeText(int row, int column);

	protected:

		void loadDefaultTableHeader() override;

		ssdaiDBGenGuiHelper _helper;
	};
}

#endif
