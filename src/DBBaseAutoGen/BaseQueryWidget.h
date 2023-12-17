#ifndef BASE_DB_QUERY_WIDGET_H
#define BASE_DB_QUERY_WIDGET_H

#include <memory>

#include <QWidget>
#include <QDialog>
#include "BaseDBData.h"

namespace Ui {
	class BaseQueryWidget;
} // namespace Ui


namespace DBAG {

	class BaseQueryWidget : public QDialog {
		Q_OBJECT
	public:
		explicit BaseQueryWidget(QWidget* parent = nullptr);
		virtual ~BaseQueryWidget() = default;

		void setTableConfig(std::shared_ptr<TableConfig> config);

		inline std::vector<FieldSelectedInfo>&& getSelectFieldInfo() {
			return std::move(_fieldSelectedInfo);
		}

	public slots:
		void addCondBtnOnClicked();
		void selectDataBtnOnClicked();

	protected:
		virtual void showEvent(QShowEvent* event) override;
		virtual void resizeEvent(QResizeEvent* event) override;
		void resizeTableWidth();

		Ui::BaseQueryWidget* ui;

		std::weak_ptr<TableConfig> _tableConfig;

		std::vector<FieldSelectedInfo> _fieldSelectedInfo; //move to dao

		bool _is_add_updateControl{ true };
	};
}

#endif // !BASE_DB_QUERY_WIDGET_H
