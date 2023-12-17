#include "BaseDBInfo.h"
#include <string>
#include <assert.h>

using namespace DBAG;

std::string FieldSelectedInfo::getSQLCond() {
    if (!checkSupportWhereCond(_type, _cond)) {
        DLOG(INFO) << "failed fieldInfo._type:" << static_cast<int>(_type) << " fieldInfo._cond: " << static_cast<int>(_cond);
        assert(false);
    }

    std::string s;
    switch (_cond)
    {
    case WhereCond::EQUAL:
        s = " {} {} = {}";
        break;
    case WhereCond::LESS:
        s = " {} {} < {}";
        break;
    case WhereCond::LESSEQUAL:
        s = " {} {} <= {}";
        break;
    case WhereCond::MORE:
        s = " {} {} > {}";
        break;
    case WhereCond::MOREEQUAL:
        s = " {} {} >= {}";
        break;
    case WhereCond::IN:
        s = " {} {} in ({})";
        break;
    case WhereCond::LIKE:
        s = " {} {} like '%{}%'";
        break;
    case WhereCond::EQUALSTRING:
        s = " {} {} = '{}'";
        break;

    case WhereCond::DATEEQUAL:
    case WhereCond::DATETIMEEQUAL:
        s = " {} {} = '{}'";
        break;
    case WhereCond::DATELESS:
    case WhereCond::DATETIMELESS:
        s = " {} {} < '{}'";
        break;
    case WhereCond::DATELESSEQUAL:
    case WhereCond::DATETIMELESSEQUAL:
        s = " {} {} <= '{}'";
        break;
    case WhereCond::DATEMORE:
    case WhereCond::DATETIMEMORE:
        s = " {} {} > '{}'";
        break;
    case WhereCond::DATEMOREEQUAL:
    case WhereCond::DATETIMEMOREEQUAL:
        s = " {} {} >= '{}'";
        break;
    default:
        assert(false);
        break;
    }
    return move(s);
}

std::string DBAG::BaseDBDao::genSelectSQL(const std::vector<FieldSelectedInfo>& infos)
{
    std::stringstream ss;
    //DLOG(INFO) << "tableName : " << getTableName();
    auto columnList = getColumnList();
    std::string selectColumn = "";
    if (!columnList.empty()) {
        for (auto& s : columnList) {
            selectColumn += s + ",";
        }
        selectColumn = selectColumn.substr(0, selectColumn.size() - 1);
    } else {
        selectColumn = "*";
    }

    std::string baseSQL = fmt::format("select {} from {} where 1 = 1", selectColumn,getTableName());
    //DLOG(INFO) << "Base Select SQL: " << baseSQL;

    ss << baseSQL;
    for (auto fieldInfo : infos) {
        //DLOG(INFO) << fieldInfo._name << " "  << static_cast<int>(fieldInfo._type);
        if (!fieldInfo._enable) continue;

        std::string wcond;
        switch (fieldInfo._type)
        {
        case FieldType::INT:
        case FieldType::LONGLONG:
        case FieldType::FLOAT:
        case FieldType::DOUBLE:
        case FieldType::DATE:
        case FieldType::DATETIME:
        case FieldType::STRING: {
            wcond = fmt::format(fieldInfo.getSQLCond(), fieldInfo._conn, fieldInfo._name, fieldInfo._value);
            break;
        }
       
        default: {
            DLOG(INFO) << "unknow fieldInfo._type:" << static_cast<int>(fieldInfo._type);
            assert(false);
            break;
        }
        }
        DLOG(INFO) << "genSelectSQL Select: " << wcond;
        ss << wcond;
    }

    std::string sql = ss.str();
    DLOG(INFO) << "Select SQL: " << sql;
    return move(sql);
}

int DBAG::BaseDBDao::execute(const std::string& sql)
{
    return 0;
}
