#ifndef BASE_DB_WIDGET_H
#define BASE_DB_WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QString>
#include "BaseDBData.h"
#include <string>

namespace Ui {
	class BaseDBWidget;
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

		virtual bool checkFieldSelectedInput();

		inline std::vector<FieldSelectedInfo>&& getSelectFieldInfo() {
			return std::move(_fieldSelectedInfo);
		}

		std::vector<int> getCheckBoxRowList();

		void setHeader(const QStringList& header);

		virtual void clearTable();
		virtual void addRowTable(const std::string& json);
		virtual void addRowTable(std::vector<std::string>& vec);

		std::pair<int,int> getCurrentSelectRowAndColmun();

		bool _add_checkbox;
		virtual void addRowEndCustom(QTableWidget* table, int row, int colume);

		QTableWidget* getTableWidget();

		//void parseTableConfig(const std::string& filePath);
		void parseTableConfig(const QString& filePath);

		const TableKey& getTableKey();
	public slots:
		//virtual void onRowDoubleClicked();
		virtual void onSearchBtonClicked();
		virtual void onDeleteBtonClicked();

		virtual void onBaseSearchBtonClicked();
		virtual void onBaseDeleteBtonClicked();


	protected:
		Ui::BaseDBWidget* ui;

		std::vector<std::string> _header;
		std::map<std::string, std::string> _header_en_name_map;//header name : cn-->en

		std::string _tableName;
		std::shared_ptr<TableConfig> _tableConfig{};
		std::string _tableConfigFilePath{};

		std::vector<std::shared_ptr<FieldSelectedInfo>> _selectInfos;
		std::vector<FieldSelectedInfo> _fieldSelectedInfo; //move to dao

		
	};

}
#endif