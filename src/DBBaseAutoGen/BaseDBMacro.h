#ifndef BASE_DB_MACRO_H
#define BASE_DB_MACRO_H

#define DataStructDBGuiHelperClassDeclaration(DataStructDao,DataStruct)\
	class DataStruct##DBGenGuiHelper : public BaseDBWidgetHelper<DataStructDao, DataStruct>\
	{\
	public:\
		inline decltype(auto) getDao() { return BaseDBWidgetHelper<DataStructDao, DataStruct>::_dao; }\
	};\

//#define DataStructDBGuiClassDeclaration(DataStruct)\
//	class DataStruct##DBGenGui : public BaseDBWidget {\
//		Q_OBJECT\
//	public:\
//		DataStruct##DBGenGui(BaseDBWidget* parent = nullptr);\
//		virtual ~##DataStruct##DBGenGui();\
//		void onSearchBtonClicked() override;\
//		void onDeleteBtonClicked() override;\
//		std::optional<DataStruct> getSelectRowObj(int row);\
//		std::string getSelectRowColumeText(int row, int column);\
//	protected:\
//		void loadDefaultTableHeader() override;\
//		DataStruct##DBGenGuiHelper _helper;\
//	};\

#define DataStructDBGuiClassDefinition(DataStruct)\
	DBAG::DataStruct##DBGenGui::##DataStruct##DBGenGui(BaseDBWidget* parent)\
		:BaseDBWidget(parent)\
	{\
		_helper.setWidegt(this);\
	}\
	void DBAG::DataStruct##DBGenGui::onSearchBtonClicked() {\
		BaseDBWidget::onSearchBtonClicked();\
		std::vector<FieldInfo> info = getSelectFieldInfo();\
		_helper.executeSelect(info);\
	}\
	void DBAG::DataStruct##DBGenGui::onDeleteBtonClicked() {\
		BaseDBWidget::onDeleteBtonClicked();\
		auto list = getCheckBoxRowList();\
		_helper.deleteRowData(list);\
	}\
	void DBAG::DataStruct##DBGenGui::loadDefaultTableHeader() {\
		_helper.loadDefaultTableHeader();\
	}\
	std::optional<DBAG::DataStruct> DBAG::DataStruct##DBGenGui::getSelectRowObj(int row) {\
		return _helper.getSelectRowObj(row);\
	}\
	std::string DBAG::DataStruct##DBGenGui::getSelectRowColumeText(int row, int column) {\
		return _helper.getSelectRowColumeText(row, column);\
	}

/* example:
	
	DataStructDBGuiHelperClassDeclaration(env_dataDBGenDao, env_data)：

	class env_dataDBGenGuiHelper : public BaseDBWidgetHelper<env_dataDBGenDao, env_data>
	{
		public:
			inline decltype(auto) getDao() { return BaseDBWidgetHelper<env_dataDBGenDao, env_data>::_dao; }
	};

	DataStructDBGuiClassDefinition(env_data)：
	inline env_dataDBGenGui::env_dataDBGenGui(BaseDBWidget* parent)
		:BaseDBWidget(parent)
	{
		_helper.setWidegt(this);
	}
	
	inline void env_dataDBGenGui::onSearchBtonClicked(){
		BaseDBWidget::onSearchBtonClicked();
		std::vector<FieldInfo> info = getSelectFieldInfo();
		_helper.executeSelect(info);
	}
	
	inline void env_dataDBGenGui::onDeleteBtonClicked() {
		BaseDBWidget::onDeleteBtonClicked();
		auto list = getCheckBoxRowList();
		_helper.deleteRowData(list);
	}
	
	inline void env_dataDBGenGui::loadDefaultTableHeader() {
		_helper.loadDefaultTableHeader();
	}
	
	inline std::optional<env_data> env_dataDBGenGui::getSelectRowObj(int row) {
		return _helper.getSelectRowObj(row);
	}
	
	inline std::string env_dataDBGenGui::getSelectRowColumeText(int row, int column) {
		return _helper.getSelectRowColumeText(row, column);
	}

*/








#endif // BASE_DB_MACRO_H
