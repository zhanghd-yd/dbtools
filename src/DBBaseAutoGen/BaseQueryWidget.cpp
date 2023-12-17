#include "BaseQueryWidget.h"
#include "ui/ui_BaseQueryWidget.h"

#include <rttr/enumeration.h>
#include <type_traits>
#include <rttr/registration>
#include <glog/logging.h>

#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QCheckBox>

using namespace DBAG;

DBAG::BaseQueryWidget::BaseQueryWidget(QWidget* parent)
	:QDialog(parent), ui(new Ui::BaseQueryWidget)
{
	ui->setupUi(this);
	this->setWindowTitle("条件检索");
	this->resize(800, 600);

	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableWidget->setAlternatingRowColors(true);
	ui->tableWidget->verticalHeader()->setVisible(false);
	ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
	ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Custom);

	connect(ui->addCondBtn, &QPushButton::clicked, this, &BaseQueryWidget::addCondBtnOnClicked);
	connect(ui->selectDataBtn, &QPushButton::clicked, this, &BaseQueryWidget::selectDataBtnOnClicked);

}

void DBAG::BaseQueryWidget::showEvent(QShowEvent* event)
{
	resizeTableWidth();
}

void DBAG::BaseQueryWidget::resizeEvent(QResizeEvent* event)
{
	resizeTableWidth();
}

void DBAG::BaseQueryWidget::resizeTableWidth()
{
	int width = ui->tableWidget->width();
	ui->tableWidget->setColumnWidth(0, width * 0.08);
	ui->tableWidget->setColumnWidth(1, width * 0.3);
	ui->tableWidget->setColumnWidth(2, width * 0.15);
	ui->tableWidget->setColumnWidth(3, width * 0.15);
	ui->tableWidget->setColumnWidth(4, width * 0.20);
	ui->tableWidget->setColumnWidth(5, width * 0.1);
}

void DBAG::BaseQueryWidget::selectDataBtnOnClicked() {
	auto tableConfig = _tableConfig.lock();
	if (!tableConfig) {
		DLOG(INFO) << "_tableConfig.lock() is nullptr";
		return;
	}

	auto table = ui->tableWidget;
	int rowCount = table->rowCount();
	std::vector<FieldSelectedInfo>().swap(_fieldSelectedInfo);
	FieldSelectedInfo selectedInfo;

#define CheckEditNullptr(obj) if(!obj) continue;
	for (int row = 0; row < rowCount; row++) {
		{
			auto box = qobject_cast<QCheckBox*>(table->cellWidget(row, 0)->layout()->itemAt(0)->widget());
			selectedInfo._enable = box->isChecked();
		}

		{
			auto box = qobject_cast<QComboBox*>(table->cellWidget(row, 1)->layout()->itemAt(0)->widget());
			selectedInfo._name = box->currentData().toString().toStdString();
		}
		
		{
			selectedInfo._type = getFieldType(table->item(row, 2)->text().toStdString());
		}

		{
			auto box = qobject_cast<QComboBox*>(table->cellWidget(row, 3)->layout()->itemAt(0)->widget());
			selectedInfo._cond = static_cast<WhereCond>(box->currentData().toInt());
		}


		{
			auto editWidget = qobject_cast<QWidget*>(table->cellWidget(row, 4)->layout()->itemAt(0)->widget());
			DLOG(INFO) << "editWidget: " << editWidget->metaObject()->className();
			if (selectedInfo._type == FieldType::DATE) {
				QDateEdit* edit = qobject_cast<QDateEdit*>(editWidget);
				CheckEditNullptr(edit)
				selectedInfo._value = edit->date().toString("yyyy-MM-dd").toStdString();
			} else if (selectedInfo._type == FieldType::DATETIME) {
				QDateTimeEdit* edit = qobject_cast<QDateTimeEdit*>(editWidget);
				CheckEditNullptr(edit)
				selectedInfo._value = edit->dateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
			} else if (selectedInfo._type == FieldType::STRING) {
				QLineEdit* edit = qobject_cast<QLineEdit*>(editWidget);
				CheckEditNullptr(edit)
				selectedInfo._value = edit->text().toStdString();
			} else if (selectedInfo._type == FieldType::DOUBLE || selectedInfo._type == FieldType::FLOAT) {
				QDoubleSpinBox* edit = qobject_cast<QDoubleSpinBox*>(editWidget);
				CheckEditNullptr(edit)
				selectedInfo._value = edit->text().toStdString();
			} else {
				QSpinBox* edit = qobject_cast<QSpinBox*>(editWidget);
				CheckEditNullptr(edit)
				selectedInfo._value = edit->text().toStdString();
			}
		}
		_fieldSelectedInfo.emplace_back(selectedInfo);
	}
#undef CheckEditNullptr

	tableConfig->_query_table_rowcount = static_cast<int>(_fieldSelectedInfo.size());

	auto& fieldInfoList = tableConfig->_fields;
	for (auto& fieldInfo : fieldInfoList) {
		decltype(fieldInfo._selecteds)().swap(fieldInfo._selecteds);
		int tableRow = 0;
		for (auto& fieldSelectedInfo : _fieldSelectedInfo) {
			if (fieldSelectedInfo._name == fieldInfo._field) {
				FieldSelected fieldSelected(fieldSelectedInfo._value, static_cast<int>(fieldSelectedInfo._cond), 
					tableRow, fieldSelectedInfo._enable);
				fieldInfo._selecteds.emplace_back(fieldSelected);
			}
			tableRow++;
		}
	}

	accept();
}

void DBAG::BaseQueryWidget::setTableConfig(std::shared_ptr<TableConfig> config)
{
	if (!config) return;
	_tableConfig = config;
	
	auto& fields = config->_fields;
	if (fields.empty()) return;

	int rowCount = config->_query_table_rowcount;
	if (rowCount <= 0) return;
	
	_is_add_updateControl = false;
	for (int i = 0; i < rowCount; i++) {
		addCondBtnOnClicked();
	}
	QCoreApplication::processEvents();
	_is_add_updateControl = true;

#define CheckEditNullptr(obj) if(!obj) continue;
	auto table = ui->tableWidget;
	for (int fieldIndex = 0; fieldIndex < fields.size(); fieldIndex++) {
		auto& field = fields[fieldIndex];
		auto& selecteds = field._selecteds;
		if (selecteds.empty()) continue;

		for (auto& selected : selecteds) {

			QCheckBox* checkBox = qobject_cast<QCheckBox*>(table->cellWidget(selected._tablerow, 0)->layout()->itemAt(0)->widget());
			checkBox->setChecked(selected._enable);

			QComboBox* fieldbox = qobject_cast<QComboBox*>(table->cellWidget(selected._tablerow, 1)->layout()->itemAt(0)->widget());
			fieldbox->setCurrentIndex(fieldIndex);
			emit fieldbox->currentIndexChanged(fieldIndex);
			QCoreApplication::processEvents();

			QComboBox* condbox = qobject_cast<QComboBox*>(table->cellWidget(selected._tablerow , 3)->layout()->itemAt(0)->widget());
			auto whereCondTxt = getWhereCondWidgetText(static_cast<WhereCond>(selected._cond));
			condbox->setCurrentText(QString::fromStdString(whereCondTxt));

			std::string type = field._type;
			std::transform(type.begin(), type.end(), type.begin(), ::toupper);
			auto editWidget = qobject_cast<QWidget*>(table->cellWidget(selected._tablerow, 4)->layout()->itemAt(0)->widget());
			if (type == "DATE") {
				QDateEdit* edit = qobject_cast<QDateEdit*>(editWidget);
				CheckEditNullptr(edit)
				if(!selected._value.empty()) edit->setDate(QDate::fromString(QString::fromStdString(selected._value),"yyyy-MM-dd"));
			} else if (type == "DATETIME") {
				QDateTimeEdit* edit = qobject_cast<QDateTimeEdit*>(editWidget);
				CheckEditNullptr(edit)
				if (!selected._value.empty()) edit->setDateTime(QDateTime::fromString(QString::fromStdString(selected._value),"yyyy-MM-dd hh:mm:ss"));
			} else if (type == "STRING") {
				QLineEdit* edit = qobject_cast<QLineEdit*>(editWidget);
				CheckEditNullptr(edit)
				if (!selected._value.empty()) edit->setText(QString::fromStdString(selected._value));
			} else if (type == "DOUBLE" || field._type == "FLOAT") {
				QDoubleSpinBox* edit = qobject_cast<QDoubleSpinBox*>(editWidget);
				CheckEditNullptr(edit)
				if (!selected._value.empty()) edit->setValue(std::stod(selected._value));
			} else {
				QSpinBox* edit = qobject_cast<QSpinBox*>(editWidget);
				CheckEditNullptr(edit)
				if (!selected._value.empty()) edit->setValue(std::stoi(selected._value));
			}
		}
	}
#undef CheckEditNullptr
}

void DBAG::BaseQueryWidget::addCondBtnOnClicked() {
	auto tableConfig = _tableConfig.lock();
	if (!tableConfig) return;

	auto table = ui->tableWidget;
	int row = table->rowCount();
	table->insertRow(row);

	{
		auto box = new QCheckBox;
		box->setChecked(true);
		auto widget = new QWidget();
		auto layout = new QHBoxLayout();

		layout->setMargin(0);
		widget->setLayout(layout);
		layout->addWidget(box, 0, Qt::AlignCenter);
		table->setCellWidget(row, 0, widget);
	}

	QComboBox* fieldbox = nullptr;
	{
		fieldbox = new QComboBox;
		fieldbox->setProperty("row", row);
		for (auto& field : tableConfig->_fields) {
			fieldbox->addItem(QString::fromStdString(field._comment), QString::fromStdString(field._field.data()));
		}

		auto widget = new QWidget();
		auto layout = new QHBoxLayout();

		layout->setMargin(0);
		widget->setLayout(layout);
		layout->addWidget(fieldbox, 0, Qt::AlignCenter);
		table->setCellWidget(row, 1, widget);

		connect(fieldbox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this, fieldbox](int index) {
			auto tableConfig = _tableConfig.lock();
			if (!tableConfig) return;

			auto table = ui->tableWidget;
			int row = fieldbox->property("row").toInt();
			QString text = fieldbox->currentText();
			auto& field = tableConfig->_fields.at(index);
			std::string type = field._type;
			std::transform(type.begin(), type.end(), type.begin(), ::toupper);

			table->item(row, 2)->setText(QString::fromStdString(type));

			{
				QComboBox* condbox = qobject_cast<QComboBox*>(table->cellWidget(row, 3)->layout()->itemAt(0)->widget());
				condbox->clear();
				auto condList = getSupportWhereCond(type);
				for (auto cond : condList) {
					if (cond == WhereCond::IN) {
						//TODO
						continue;
					}
					auto whereCondTxt = getWhereCondWidgetText(cond);
					condbox->addItem(QString::fromStdString(whereCondTxt), static_cast<int>(cond));//save WhereCond type==>int
				}
			}
			
			{
				auto layout = table->cellWidget(row, 4)->layout();
				auto count = layout->count();
				for (int i = 0; i < count; i++) {
					auto item = layout->itemAt(i);
					layout->removeItem(layout->itemAt(i));
					if(item) delete item;
				}

				if (type == "DATE") {
					QDateEdit* edit = new QDateEdit;
					edit->setDate(QDate::currentDate());
					layout->addWidget(edit);
				} else if (type == "DATETIME") {
					QDateTimeEdit* edit = new QDateTimeEdit;
					edit->setDateTime(QDateTime::currentDateTime());
					layout->addWidget(edit);
				} else if (type == "STRING") {
					QLineEdit* edit = new QLineEdit;
					layout->addWidget(edit);
				} else if (type == "DOUBLE" || type == "FLOAT") {
					QDoubleSpinBox* edit = new QDoubleSpinBox;
					edit->setDecimals(field._scale);
					edit->setRange(field._min_value, field._max_value);
					layout->addWidget(edit);
				} else {
					QSpinBox* edit = new QSpinBox;
					edit->setRange(static_cast<int>(field._min_value), static_cast<int>(field._max_value));
					layout->addWidget(edit);
				}
			}
		});
	}

	{
		auto item = new QTableWidgetItem("");
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
		table->setItem(row, 2, item);
	}

	{
		QComboBox* condbox = new QComboBox;
		auto widget = new QWidget();
		auto layout = new QHBoxLayout();

		layout->addWidget(condbox, 0, Qt::AlignCenter);
		layout->setMargin(0);
		widget->setLayout(layout);
		table->setCellWidget(row, 3, widget);
	}

	{
		auto widget = new QWidget();
		auto layout = new QHBoxLayout();
		layout->setMargin(0);
		widget->setLayout(layout);
		table->setCellWidget(row, 4, widget);
	}

	{
		QPushButton* btn = new QPushButton("移除");
		connect(btn, &QPushButton::clicked, [this,btn]() {
			int x = btn->parentWidget()->frameGeometry().x();
			int y = btn->parentWidget()->frameGeometry().y();
			QModelIndex index = ui->tableWidget->indexAt(QPoint(x, y));
			int row = index.row();
			ui->tableWidget->removeRow(row);
		});
		auto widget = new QWidget();
		auto layout = new QHBoxLayout();
		layout->addWidget(btn);
		layout->setMargin(0);
		widget->setLayout(layout);
		table->setCellWidget(row, 5, widget);
	}

	if(_is_add_updateControl){
		emit fieldbox->currentIndexChanged(0);
	}
}