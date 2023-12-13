#include "BaseDBInfo.h"
#include <string>
#include <assert.h>

using namespace DBAG;

std::string FieldInfo::getSQLCond() {
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

        //only support date(yyyy-MM-dd) !!
    case WhereCond::DATEEQUAL:
        s = " {} STR_TO_DATE({}, '%Y%m%d') = STR_TO_DATE('{}', '%Y-%m-%d')";
        break;
    case WhereCond::DATELESS:
        s = " {} STR_TO_DATE({}, '%Y%m%d') < STR_TO_DATE('{}', '%Y-%m-%d')";
        break;
    case WhereCond::DATELESSEQUAL:
        s = " {} STR_TO_DATE({}, '%Y%m%d') <= STR_TO_DATE('{}', '%Y-%m-%d')";
        break;
    case WhereCond::DATEMORE:
        s = " {} STR_TO_DATE({}, '%Y%m%d') > STR_TO_DATE('{}', '%Y-%m-%d')";
        break;
    case WhereCond::DATEMOREEQUAL:
        s = " {} STR_TO_DATE({}, '%Y%m%d') >= STR_TO_DATE('{}', '%Y-%m-%d')";
        break;

        //only support datetime(yyyy-MM-dd HH:mm:ss) !!
    case WhereCond::DATETIMEEQUAL:
        s = " {} to_date({}, 'yyyy-mm-dd hh24:mi:ss') = to_date('{}', 'yyyy-mm-dd hh24:mi:ss')";
        break;
    case WhereCond::DATETIMELESS:
        s = " {} to_date({}, 'yyyy-mm-dd hh24:mi:ss') < to_date('{}', 'yyyy-mm-dd hh24:mi:ss')";
        break;
    case WhereCond::DATETIMELESSEQUAL:
        s = " {} to_date({}, 'yyyy-mm-dd hh24:mi:ss') <= to_date('{}', 'yyyy-mm-dd hh24:mi:ss')";
        break;
    case WhereCond::DATETIMEMORE:
        s = " {} to_date({}, 'yyyy-mm-dd hh24:mi:ss') > to_date('{}', 'yyyy-mm-dd hh24:mi:ss')";
        break;
    case WhereCond::DATETIMEMOREEQUAL:
        s = " {} to_date({}, 'yyyy-mm-dd hh24:mi:ss') >= to_date('{}', 'yyyy-mm-dd hh24:mi:ss')";
        break;

    default:
        assert(true);
        break;
    }
    return move(s);
}

std::string DBAG::BaseDBDao::genSelectSQL(const std::vector<FieldInfo>& infos)
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
        std::string wcond;
        switch (fieldInfo._type)
        {
        case FieldType::INT: {
            if (fieldInfo._cond == WhereCond::IN) {
                wcond = fmt::format(fieldInfo.getSQLCond(), fieldInfo._conn, fieldInfo._name, std::any_cast<std::string>(fieldInfo._value));
            } else {
                wcond = fmt::format(fieldInfo.getSQLCond(), fieldInfo._conn, fieldInfo._name, std::any_cast<int>(fieldInfo._value));
            }
            break;
        }
        case FieldType::LONGLONG: {
            if (fieldInfo._cond == WhereCond::IN) {
                wcond = fmt::format(fieldInfo.getSQLCond(), fieldInfo._conn, fieldInfo._name, std::any_cast<std::string>(fieldInfo._value));
            } else {
                wcond = fmt::format(fieldInfo.getSQLCond(), fieldInfo._conn, fieldInfo._name, std::any_cast<long long>(fieldInfo._value));
            }
            break;
        }
        case FieldType::FLOAT: {
            if (fieldInfo._cond == WhereCond::IN) {
                wcond = fmt::format(fieldInfo.getSQLCond(), fieldInfo._conn, fieldInfo._name, std::any_cast<std::string>(fieldInfo._value));
            } else {
                wcond = fmt::format(fieldInfo.getSQLCond(), fieldInfo._conn, fieldInfo._name, std::any_cast<float>(fieldInfo._value));
            }
            break;
        }
        case FieldType::DOUBLE: {
            if (fieldInfo._cond == WhereCond::IN) {
                wcond = fmt::format(fieldInfo.getSQLCond(), fieldInfo._conn, fieldInfo._name, std::any_cast<std::string>(fieldInfo._value));
            } else {
                wcond = fmt::format(fieldInfo.getSQLCond(), fieldInfo._conn, fieldInfo._name, std::any_cast<double>(fieldInfo._value));
            }
            break;
        }
        case FieldType::STRING: {
            wcond = fmt::format(fieldInfo.getSQLCond(), fieldInfo._conn, fieldInfo._name, std::any_cast<std::string>(fieldInfo._value));
            break;
        }
        case FieldType::DATE: {
            wcond = fmt::format(fieldInfo.getSQLCond(), fieldInfo._conn, fieldInfo._name, std::any_cast<std::string>(fieldInfo._value));
            break;
        }
        case FieldType::DATETIME: {
            wcond = fmt::format(fieldInfo.getSQLCond(), fieldInfo._conn, fieldInfo._name, std::any_cast<std::string>(fieldInfo._value));
            break;
        }
        default: {
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
