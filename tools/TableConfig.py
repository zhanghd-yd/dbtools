# To use this code, make sure you
#
#     import json
#
# and then, to convert JSON from a string, do
#
#     result = tableconfig_from_dict(json.loads(json_string))

from typing import Any, Optional, List, TypeVar, Callable, Type, cast


T = TypeVar("T")


def from_str(x: Any) -> str:
    assert isinstance(x, str)
    return x


def from_int(x: Any) -> int:
    assert isinstance(x, int) and not isinstance(x, bool)
    return x


def from_bool(x: Any) -> bool:
    assert isinstance(x, int)
    return True if x > 0 else False


def from_float(x: Any) -> float:
    assert isinstance(x, (float, int)) and not isinstance(x, bool)
    return float(x)


def from_none(x: Any) -> Any:
    assert x is None
    return x


def from_union(fs, x):
    for f in fs:
        try:
            return f(x)
        except:
            pass
    assert False


def from_list(f: Callable[[Any], T], x: Any) -> List[T]:
    assert isinstance(x, list)
    return [f(y) for y in x]


def to_float(x: Any) -> float:
    assert isinstance(x, float)
    return x


def to_class(c: Type[T], x: Any) -> dict:
    assert isinstance(x, c)
    return cast(Any, x).to_dict()


class Selected:
    value: str
    cond: int
    table_row: int
    enable: bool

    def __init__(self, value: str, cond: int, table_row: int, enable: bool) -> None:
        self.value = value
        self.cond = cond
        self.table_row = table_row
        self.enable = enable

    @staticmethod
    def from_dict(obj: Any) -> 'Selected':
        assert isinstance(obj, dict)
        value = from_str(obj.get("Value"))
        cond = from_int(obj.get("Cond"))
        table_row = from_int(obj.get("TableRow"))
        enable = from_bool(obj.get("Enable"))
        return Selected(value, cond, table_row, enable)

    def to_dict(self) -> dict:
        result: dict = {}
        result["Value"] = from_str(self.value)
        result["Cond"] = from_int(self.cond)
        result["TableRow"] = from_int(self.table_row)
        result["Enable"] = from_bool(self.enable)
        return result


class Column:
    field: str
    type: str
    length: int
    precision: int
    scale: int
    max_number: Optional[float]
    min_number: Optional[float]
    nullable: bool
    comment: str
    selected: List[Selected]

    def __init__(self, field: str, type: str, length: int, precision: int, scale: int, max_number: Optional[float], min_number: Optional[float], nullable: bool, comment: str, selected: List[Selected]) -> None:
        self.field = field
        self.type = type
        self.length = length
        self.precision = precision
        self.scale = scale
        self.max_number = max_number
        self.min_number = min_number
        self.nullable = nullable
        self.comment = comment
        self.selected = selected

    @staticmethod
    def from_dict(obj: Any) -> 'Column':
        assert isinstance(obj, dict)
        field = from_str(obj.get("Field"))
        type = from_str(obj.get("Type"))
        length = from_int(obj.get("Length"))
        precision = from_int(obj.get("Precision"))
        scale = from_int(obj.get("Scale"))
        max_number = from_union([from_float, from_none], obj.get("MaxNumber"))
        min_number = from_union([from_float, from_none], obj.get("MinNumber"))
        nullable = from_bool(obj.get("Nullable"))
        comment = from_str(obj.get("Comment"))
        selected = from_list(Selected.from_dict, obj.get("Selected"))
        return Column(field, type, length, precision, scale, max_number, min_number, nullable, comment, selected)

    def to_dict(self) -> dict:
        result: dict = {}
        result["Field"] = from_str(self.field)
        result["Type"] = from_str(self.type)
        result["Length"] = from_int(self.length)
        result["Precision"] = from_int(self.precision)
        result["Scale"] = from_int(self.scale)
        result["MaxNumber"] = from_union([to_float, from_none], self.max_number)
        result["MinNumber"] = from_union([to_float, from_none], self.min_number)
        result["Nullable"] = from_bool(self.nullable)
        result["Comment"] = from_str(self.comment)
        result["Selected"] = from_list(lambda x: to_class(Selected, x), self.selected)
        return result


class Key:
    column: str
    increment: bool

    def __init__(self, column: str, increment: bool) -> None:
        self.column = column
        self.increment = increment

    @staticmethod
    def from_dict(obj: Any) -> 'Key':
        assert isinstance(obj, dict)
        column = from_str(obj.get("Column"))
        increment = from_bool(obj.get("Increment"))
        return Key(column, increment)

    def to_dict(self) -> dict:
        result: dict = {}
        result["Column"] = from_str(self.column)
        result["Increment"] = from_bool(self.increment)
        return result


class TableConfig:
    table: str
    key: Key
    column: List[Column]
    query_count: int

    def __init__(self, table: str, key: Key, column: List[Column], query_count: int) -> None:
        self.table = table
        self.key = key
        self.column = column
        self.query_count = query_count

    @staticmethod
    def from_dict(obj: Any) -> 'TableConfig':
        assert isinstance(obj, dict)
        table = from_str(obj.get("Table"))
        key = Key.from_dict(obj.get("Key"))
        column = from_list(Column.from_dict, obj.get("Column"))
        query_count = from_int(obj.get("QueryCount"))
        return TableConfig(table, key, column, query_count)

    def to_dict(self) -> dict:
        result: dict = {}
        result["Table"] = from_str(self.table)
        result["Key"] = to_class(Key, self.key)
        result["Column"] = from_list(lambda x: to_class(Column, x), self.column)
        result["QueryCount"] = from_int(self.query_count)
        return result


def tableconfig_from_dict(s: Any) -> TableConfig:
    return TableConfig.from_dict(s)


def tableconfig_to_dict(x: TableConfig) -> Any:
    return to_class(TableConfig, x)
