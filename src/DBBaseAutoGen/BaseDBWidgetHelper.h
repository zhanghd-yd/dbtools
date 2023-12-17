#ifndef BASE_DB_WIDGET_HEPLER_H
#define BASE_DB_WIDGET_HEPLER_H

#include <glog/logging.h>
#include <optional>

#include "BaseDBWidget.h"

namespace DBAG {

	template<class T, class D>
	class BaseDBWidgetHelper{
	public:
		explicit BaseDBWidgetHelper();
		virtual ~BaseDBWidgetHelper();

		void executeSelect(const std::vector<FieldSelectedInfo>& infos = std::vector<FieldSelectedInfo>());

		int deleteRowData(int row);

		int deleteRowData(const std::vector<int>&& rowList);

		void updateWidgetByCurrentSelectCond();

		void loadDefaultTableHeader();

		inline void setWidegt(BaseDBWidget* widget) {
			_widget = widget;
		}

		std::optional<D> getSelectRowObj(int row);

		std::string getSelectRowColumeText(int row,int colume);

	protected:
		T _dao;
		std::string _D_Name;
		BaseDBWidget* _widget;
		std::vector<std::shared_ptr<D>> _resultList;
		std::vector<FieldSelectedInfo> _currentCond;

	};

	template<class T, class D>
	inline BaseDBWidgetHelper<T, D>::BaseDBWidgetHelper()
	{}

	template<class T, class D>
	inline BaseDBWidgetHelper<T, D>::~BaseDBWidgetHelper()
	{}

	template<class T, class D>
	inline void BaseDBWidgetHelper<T, D>::executeSelect(const std::vector<FieldSelectedInfo>& infos)
	{
		_widget->clearTable();

		_currentCond = std::move(infos);
		_resultList = _dao.executeSelect<D>(infos);

		if (_resultList.empty()) return;

		auto& headerList = _widget->getHeaderList();
		auto& header_en_name_map = _widget->getHeaderMap();
		std::vector<std::string> rowData;
		rttr::type t = rttr::type::get<D>();
		for (const auto& obj : _resultList) {
			rowData.clear();
			for (const auto& header : headerList) {
				auto it = header_en_name_map.find(header);
				if (it == header_en_name_map.end()) {
					continue;
				}

				rttr::property prop = t.get_property(it->second);
				rttr::variant var = prop.get_value(*obj.get());

				if (prop.get_type() == rttr::type::get<bool>())
					rowData.emplace_back(std::to_string(static_cast<int>(var.to_bool())));
				else if (prop.get_type() == rttr::type::get<char>())
					rowData.emplace_back(std::to_string(static_cast<int>(var.to_bool())));
				else if (prop.get_type() == rttr::type::get<int8_t>())
					rowData.emplace_back(std::to_string(var.to_int8()));
				else if (prop.get_type() == rttr::type::get<int16_t>())
					rowData.emplace_back(std::to_string(var.to_int16()));
				else if (prop.get_type() == rttr::type::get<int32_t>())
					rowData.emplace_back(std::to_string(var.to_int32()));
				else if (prop.get_type() == rttr::type::get<int64_t>())
					rowData.emplace_back(std::to_string(var.to_int64()));
				else if (prop.get_type() == rttr::type::get<uint8_t>())
					rowData.emplace_back(std::to_string(var.to_uint8()));
				else if (prop.get_type() == rttr::type::get<uint16_t>())
					rowData.emplace_back(std::to_string(var.to_uint16()));
				else if (prop.get_type() == rttr::type::get<uint32_t>())
					rowData.emplace_back(std::to_string(var.to_uint32()));
				else if (prop.get_type() == rttr::type::get<uint64_t>())
					rowData.emplace_back(std::to_string(var.to_uint64()));
				else if (prop.get_type() == rttr::type::get<float>())
					rowData.emplace_back(std::to_string(var.to_float()));
				else if (prop.get_type() == rttr::type::get<double>())
					rowData.emplace_back(std::to_string(var.to_double()));
				else
					rowData.emplace_back(var.to_string());

				DLOG(INFO) << "rowData: " << rowData.back();
			}

			_widget->addRowTable(rowData);
		}
	}

	template<class T, class D>
	inline void BaseDBWidgetHelper<T, D>::updateWidgetByCurrentSelectCond()
	{
		executeSelect(_currentCond);
	}

	template<class T, class D>
	inline void BaseDBWidgetHelper<T, D>::loadDefaultTableHeader()
	{
		auto& header_en_name_map = _widget->getHeaderMap();
		auto& headerlist = _widget->getHeaderList();

		headerlist.emplace_back(std::string("选择"));
		
		rttr::type t = rttr::type::get<D>();
		for (auto& prop : t.get_properties()) {
			header_en_name_map.insert({ prop.get_metadata("cn").to_string(),prop.get_name().to_string() });
			headerlist.emplace_back(prop.get_metadata("cn").to_string());
		}

		headerlist.emplace_back(std::string("操作"));
	}

	template<class T, class D>
	inline std::optional<D> BaseDBWidgetHelper<T, D>::getSelectRowObj(int row)
	{
		if (row < 0 || row >= _resultList.size()) {
			return std::nullopt;
		}
		return *(_resultList.at(row).get());
	}

	template<class T, class D>
	inline std::string BaseDBWidgetHelper<T, D>::getSelectRowColumeText(int row, int colume)
	{
		std::string txt{};
		do {
			if (row < 0 || row >= _resultList.size()) {
				break;
			}

			auto& obj = getSelectRowObj(row);
			if (!obj.has_value()) {
				break;
			}

			auto& headerList = _widget->getHeaderList();
			if (colume < 0 || colume >= headerList.size()) {
				break;
			}

			auto& headerText = headerList.at(colume);
			auto& headerMap = _widget->getHeaderMap();
			auto& it = headerMap.find(headerText);
			if (it == headerMap.end()) {
				break;
			}

			auto& data = obj.value();
			auto prop = rttr::type::get(data).get_property(headerMap[headerText]);
			if (!prop.is_valid()) {
				break;
			}

			rttr::variant var = prop.get_value(data);
			if (prop.get_type() == rttr::type::get<bool>())
				txt = std::to_string(static_cast<int>(var.to_bool()));
			else if (prop.get_type() == rttr::type::get<char>())
				txt = std::to_string(static_cast<int>(var.to_bool()));
			else if (prop.get_type() == rttr::type::get<int8_t>())
				txt = std::to_string(var.to_int8());
			else if (prop.get_type() == rttr::type::get<int16_t>())
				txt = std::to_string(var.to_int16());
			else if (prop.get_type() == rttr::type::get<int32_t>())
				txt = std::to_string(var.to_int32());
			else if (prop.get_type() == rttr::type::get<int64_t>())
				txt = std::to_string(var.to_int64());
			else if (prop.get_type() == rttr::type::get<uint8_t>())
				txt = std::to_string(var.to_uint8());
			else if (prop.get_type() == rttr::type::get<uint16_t>())
				txt = std::to_string(var.to_uint16());
			else if (prop.get_type() == rttr::type::get<uint32_t>())
				txt = std::to_string(var.to_uint32());
			else if (prop.get_type() == rttr::type::get<uint64_t>())
				txt = std::to_string(var.to_uint64());
			else if (prop.get_type() == rttr::type::get<float>())
				txt = std::to_string(var.to_float());
			else if (prop.get_type() == rttr::type::get<double>())
				txt = std::to_string(var.to_double());
			else
				txt = var.to_string();

		} while (false);
		return txt;
	}

	template<class T, class D>
	inline int BaseDBWidgetHelper<T, D>::deleteRowData(int row)
	{
		int flag = -1;

		auto obj = getSelectRowObj(row);
		if (!obj.has_value()) return flag;
		auto& data = obj.value();

		std::string pKey = _dao.getPrimarykey();
		auto prop = rttr::type::get(data).get_property(pKey);
		if (!prop.is_valid()) return flag;

		rttr::variant var = prop.get_value(data);
		if (prop.get_type() == rttr::type::get<std::string>()) {
			flag = _dao.executeDelete<std::string>(var.to_string());
		} else if (prop.get_type() == rttr::type::get<int32_t>()) {
			flag = _dao.executeDelete<int>(var.to_int32());
		} else if (prop.get_type() == rttr::type::get<int64_t>()) {
			flag = _dao.executeDelete<long long>(var.to_int64());
		}

		updateWidgetByCurrentSelectCond();

		return flag;
	}
	template<class T, class D>
	inline int BaseDBWidgetHelper<T, D>::deleteRowData(const std::vector<int>&& rowList)
	{
		int flag = -1;

		if (rowList.empty()) return 0;

		std::string pKey = _dao.getPrimarykey();
		auto prop = rttr::type::get<D>().get_property(pKey);
		if (!prop.is_valid()) return flag;

		if (prop.get_type() == rttr::type::get<std::string>()) {
			std::vector<std::string> list;
			for (int row : rowList) {
				auto obj = getSelectRowObj(row);
				if (!obj.has_value()) continue;
				
				auto& data = obj.value();
				rttr::variant var = prop.get_value(data);
				list.emplace_back(var.to_string());
			}
			flag = _dao.executeBitchDelete<std::string>(list);
		} else if (prop.get_type() == rttr::type::get<int32_t>()) {
			std::vector<int> list;
			for (int row : rowList) {
				auto obj = getSelectRowObj(row);
				if (!obj.has_value()) continue;

				auto& data = obj.value();
				rttr::variant var = prop.get_value(data);
				list.emplace_back(var.to_int32());
			}
			flag = _dao.executeBitchDelete<int>(list);
		} else if (prop.get_type() == rttr::type::get<int64_t>()) {
			std::vector<long long> list;
			for (int row : rowList) {
				auto obj = getSelectRowObj(row);
				if (!obj.has_value()) continue;

				auto& data = obj.value();
				rttr::variant var = prop.get_value(data);
				list.emplace_back(var.to_int64());
			}
			flag = _dao.executeBitchDelete<long long>(list);
		}

		updateWidgetByCurrentSelectCond();

		return flag;
	}
}

#endif // !BASE_DB_WIDGET_H