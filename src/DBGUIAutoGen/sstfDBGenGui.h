
#ifndef sstf_DB_GUI_GEN_H
#define sstf_DB_GUI_GEN_H

#include "DBBaseAutoGen/BaseDBInfo.h"
#include "DBBaseAutoGen/BaseDBWidget.h"
#include "DBBaseAutoGen/BaseDBWidgetHelper.h"
#include "DBBaseAutoGen/BaseDBMacro.h"
#include "DBDataAutoGen/sstfStruct.h"

namespace DBAG {
	DataStructDBGuiHelperClassDeclaration(sstfDBGenDao, sstf);

	class sstfDBGenGui : public BaseDBWidget {
		Q_OBJECT
	public:

		sstfDBGenGui(BaseDBWidget* parent = nullptr);

		virtual ~sstfDBGenGui() = default;

		void onSearchBtonClicked() override;

		void onDeleteBtonClicked() override;

		std::optional<sstf> getSelectRowObj(int row);

		std::string getSelectRowColumeText(int row, int column);

	protected:

		void loadDefaultTableHeader() override;

		sstfDBGenGuiHelper _helper;
	};
}

#endif
