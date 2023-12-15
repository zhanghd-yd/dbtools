#ifndef BASE_DB_WIDGET_H
#define BASE_DB_WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QString>
#include "BaseDBData.h"
#include <string>

namespace Ui {
	class Form;
} // namespace Ui

namespace DBAG {
	class BaseDBWidget : public QWidget {
		Q_OBJECT
	public:
		
		BaseDBWidget(QWidget* parent = nullptr);
		virtual ~BaseDBWidget();

		void loadTableHeader(const std::string& filePath = std::string());

		inline std::map<std::string, std::string>& getHeaderMap() {
			return _header_en_name_map;
		}

		inline std::vector<std::string>& getHeaderList() {
			return _header;
		}

		virtual void loadDefaultTableHeader() = 0;

		std::vector<FieldInfo> getSelectFieldInfo();

		std::vector<int> getCheckBoxRowList();

		void setHeader(const QStringList& header);

		virtual void clearTable();
		virtual void addRowTable(const std::string& json);
		virtual void addRowTable(std::vector<std::string>& vec);

		std::pair<int,int> getCurrentSelectRowAndColmun();

		bool _add_checkbox;
		virtual void addRowEndCustom(QTableWidget* table, int row, int colume);

		QTableWidget* getTableWidget();

	public slots:
		//virtual void onRowDoubleClicked();
		virtual void onSearchBtonClicked();

		virtual void onDeleteBtonClicked();


	protected:
		Ui::Form* ui;

		std::vector<std::string> _header;
		std::map<std::string, std::string> _header_en_name_map;//header name : cn-->en

	};

}
#endif