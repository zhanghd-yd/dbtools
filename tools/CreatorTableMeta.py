# -*- coding:utf-8 -*-
import json
import os

from sqlalchemy import create_engine,MetaData
from sqlalchemy import inspect

engine = create_engine('mysql+pymysql://root:root@127.0.0.1:3306/hl_earth_eiea?charset=utf8mb3')
insp = inspect(engine)
tables_list = insp.get_table_names()

# 获取数据库连接
conn = engine.connect()

# 加载元数据
metadata = MetaData()

# 加载所有表的元数据
metadata.reflect(bind=engine)
tableDict = {}
columnList = []
# 遍历所有表，查看主键和表字段详细信息
for table in metadata.tables.values():
    table_name = table.key
    print("Table:", table)
    for column in table.columns:
        columnDict = {}
        columnDict['Field'] = column.key
        column_type_name = type(column.type).__name__
        columnDict['Type'] = column_type_name.lower()
        if column_type_name == 'INTEGER':
            columnDict['Type'] = 'int' ## 特殊处理
            columnDict['Length'] = column.type.display_width
            columnDict['Precision'] = 0
            columnDict['Scale'] = 0
        elif column_type_name == 'VARCHAR' or column_type_name == 'CHAR':
            columnDict['Type'] = 'string' ## 特殊处理
            columnDict['Length'] = column.type.length
            columnDict['Precision'] = 0
            columnDict['Scale'] = 0
        elif  column_type_name == 'DOUBLE' or column_type_name == 'FLOAT':
            columnDict['Length'] = 0
            columnDict['Precision'] = column.type.precision
            columnDict['Scale'] = column.type.scale
        else:
            columnDict['Length'] = 0
            columnDict['Precision'] = 0
            columnDict['Scale'] = 0

        columnDict['Nullable'] = column.nullable
        columnDict['Comment'] = '' if column.comment == None else column.comment
        columnDict['Selected'] = []
        #column_default = column.default
        #column_unique = column.unique
        columnList.append(columnDict)
    ## 所有的列字段
    tableDict['Column'] = columnList

    pKey = {}
    primary_key = table.primary_key
    if primary_key:
        for column in primary_key:
            pKey['Column'] = column.key
            pKey['Increment'] =  True if column.autoincrement == True else False
            break

    tableDict['Key'] = pKey
    tableDict['Table'] = table_name

    #################################################
    json_str = json.dumps(tableDict, ensure_ascii=False)
    print(json_str)

    tableConfigPath = '../config/tableConfig/%s.json' % (table_name)
    with open(tableConfigPath, 'w',encoding="utf-8") as f:
        f.write(json_str)

# 关闭数据库连接
conn.close()