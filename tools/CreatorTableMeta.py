# -*- coding:utf-8 -*-
import json
import os

## https://codebeautify.org/json-to-python-pojo-generator

from TableConfig import Selected, Column, Key, TableConfig
from TableConfig import tableconfig_from_dict, tableconfig_to_dict
from CppTemplate import cfile, cppFile,guihFile,guicppFile

from sqlalchemy import create_engine, MetaData
from sqlalchemy import inspect

engine = create_engine('mysql+pymysql://root:root@127.0.0.1:3306/hl_earth_biz_sat?charset=utf8mb3')
insp = inspect(engine)
tables_list = insp.get_table_names()

# 获取数据库连接
conn = engine.connect()

# 加载元数据
metadata = MetaData()

# 加载所有表的元数据
metadata.reflect(bind=engine)

# 遍历所有表，查看主键和表字段详细信息
for dbtable in metadata.tables.values():
    key = Key('', False)
    tableConfig: TableConfig = TableConfig('', key, [], 0)
    tableConfigFile: TableConfig = TableConfig('', key, [], 0)

    tableConfig.table = dbtable.key
    tableConfig.query_count = 0

    #########################################
    ## 拼接文件路径
    tableConfigPath = '../config/tableConfig/%s.json' % (tableConfig.table)
    ## 保留根据已有的文件的内容
    if os.path.exists(tableConfigPath):
        with open(tableConfigPath, 'r', encoding="utf-8") as f:
            tableConfigFile = tableconfig_from_dict(json.loads(f.read()))

    # 覆盖数据
    tableConfig.query_count = tableConfigFile.query_count

    ## 从数据库读取并生成Column数据
    for column in dbtable.columns:
        columnDict: Column = Column('', '', 0, 0, 0, False, 0, 0, '', [])

        columnDict.field = column.key
        column_type_name = type(column.type).__name__
        columnDict.type = column_type_name.lower()
        if column_type_name == 'INTEGER':
            columnDict.type = 'int'  ## 特殊处理
            columnDict.length = column.type.display_width
            columnDict.precision = 0
            columnDict.scale = 0
        elif column_type_name == 'VARCHAR' or column_type_name == 'CHAR':
            columnDict.type = 'string'  ## 特殊处理
            columnDict.length = column.type.length
            columnDict.precision = 0
            columnDict.scale = 0
        elif column_type_name == 'DOUBLE' or column_type_name == 'FLOAT':
            columnDict.length = 0
            columnDict.precision = column.type.precision
            columnDict.scale = column.type.scale
        else:
            columnDict.length = 0
            columnDict.precision = 0
            columnDict.scale = 0

        columnDict.max_number = float(9999.0)
        columnDict.min_number = float(0.0)
        columnDict.nullable = column.nullable
        columnDict.comment = '' if column.comment == None else column.comment
        columnDict.selected = []
        # column_default = column.default
        # column_unique = column.unique

        ## 覆盖数据
        columnDictFile = next((obj for obj in tableConfigFile.column if obj.field == columnDict.field),None)
        if columnDictFile != None:
            columnDict.selected = columnDictFile.selected
            if columnDictFile.max_number != None:
                columnDict.max_number = columnDictFile.max_number
            if columnDictFile.min_number != None:
                columnDict.min_number = columnDictFile.min_number


        tableConfig.column.append(columnDict)

    primary_key = dbtable.primary_key
    if primary_key:
        for column in primary_key:
            tableConfig.key.column = column.key
            tableConfig.key.increment = True if column.autoincrement == True else False
            break

    #################################################
    ## 生成c++代码
    cons = ""
    cppons = ""
    ikey = ''
    for item in tableConfig.column:
        itype = item.type.lower()
        ivalue = item.field
        cppons += f""".property("{ivalue}", &RegisterClassName::{ivalue})(rttr::metadata("cn",std::string("{item.comment}")))\n"""

        if "string" in itype or 'date' in itype:
            cons += f"std::string {ivalue};\n"
        elif "int" in itype:
            cons += f"int {ivalue};\n"
        elif "bigint" in itype:
            cons += f"long long {ivalue};\n"
        elif "double" in itype:
            cons += f"double {ivalue};\n"
        elif "float" in itype:
            cons += f"float {ivalue};\n"
        else:
            print("-==============================================error!!!!")

    temp_con = """
            struct %s {
                %s
            };""" % (tableConfig.table, cons)

    ikey = tableConfig.key.column

    table = tableConfig.table
    with open(f"../src/DBDataAutoGen/{table}Struct.h", 'w', encoding="utf-8") as f:
        f.write(cfile % (table, table, temp_con, table))

    with open(f"../src/DBDataAutoGen/{table}Struct.cpp", 'w', encoding="utf-8") as f:
        f.write(cppFile % (table, table, table, table, table, ikey, table, table, cppons))

    with open(f"../src/DBGUIAutoGen/{table}DBGenGui.h", 'w', encoding="utf-8") as f:
        f.write(guihFile % (table, table, table, table, table, table, table, table, table, table))

    with open(f"../src/DBGUIAutoGen/{table}DBGenGui.cpp", 'w', encoding="utf-8") as f:
        f.write(guicppFile % (table, table))

    #################################################

    ## 写入json
    json_str = json.dumps(tableconfig_to_dict(tableConfig), ensure_ascii=False)
    print(json_str)

    with open(tableConfigPath, 'w', encoding="utf-8") as f:
        f.write(json_str)

# 关闭数据库连接
conn.close()
