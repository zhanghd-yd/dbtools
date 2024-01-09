
#ifndef ioovcpssda_DB_GUI_GEN_H
#define ioovcpssda_DB_GUI_GEN_H

#include "DBBaseAutoGen/BaseDBInfo.h"
#include "DBBaseAutoGen/BaseDBWidget.h"
#include "DBBaseAutoGen/BaseDBWidgetHelper.h"
#include "DBBaseAutoGen/BaseDBMacro.h"
#include "DBDataAutoGen/ioovcpssdaStruct.h"

namespace DBAG {
	DataStructDBGuiHelperClassDeclaration(ioovcpssdaDBGenDao, ioovcpssda);

	class ioovcpssdaDBGenGui : public BaseDBWidget {
		Q_OBJECT
	public:

		ioovcpssdaDBGenGui(BaseDBWidget* parent = nullptr);

		virtual ~ioovcpssdaDBGenGui() = default;

		void onSearchBtonClicked() override;

		void onDeleteBtonClicked() override;

		std::optional<ioovcpssda> getSelectRowObj(int row);

		std::string getSelectRowColumeText(int row, int column);

	protected:

		void loadDefaultTableHeader() override;

		ioovcpssdaDBGenGuiHelper _helper;
	};
}

#endif
