#ifndef CommonMacro_H
#define CommonMacro_H
/*
#include "../situation/CommonMacro.h"
#include "CommonMacro.h"
*/
#define For(i,count) for (int i = 0; i < count; i++)
#define ForR(i,count) for (int i = count-1; i >= 0; i--)
#define ForEach(i,collection) for (auto& i : collection)
#define ForEachC(i,collection) for (const auto& i : collection)
#define ForEachKV(key,value,collection) for (auto& [key,value] : collection)
#define For_Each(it,object) for(auto it = object.begin(); it != object.end(); it++)
#define For_EachR(it,object) for(auto it = object.rbegin(); it != object.rend(); it++)

#define Has(collection,element) 	(collection.find(element) != collection.end())
#define HasNot(collection,element) 	(collection.find(element) == collection.end())
#define IfHas(collection,element) 	if(collection.find(element) != collection.end())
#define IfHasNot(collection,element) 	if(collection.find(element) == collection.end())


#define FoundIn(collection,element,it) auto it = collection.find(element); if (it != collection.end())
#define NotFoundIn(collection,element,it) auto it = collection.find(element); if (it == collection.end())


#define  IsIn00(a,b,c) ((a > b) && (a < c))
#define  IsIn10(a,b,c) ((a >= b) && (a < c))
#define  IsIn01(a,b,c) ((a > b) && (a <= c))
#define  IsIn11(a,b,c) ((a >= b) && (a <= c))
#define  IsOut00(a,b,c) ((a < b) || (a > c))
#define  IsOut10(a,b,c) ((a <= b) || (a > c))
#define  IsOut01(a,b,c) ((a < b) || (a >= c))
#define  IsOut11(a,b,c) ((a <= b) || (a >= c))

//#define ConstQStringRef const QString&  
//#define ConstStringRef const std::string&  
//#define ConstWStringRef const std::wstring&  

#define  PROPERTY_GET(type,Name,_name)  type get##Name(){ return _name;}
#define  PROPERTY_SET(type,Name,_name)  void set##Name(const type& p){ _name = p;}
#define  PROPERTY_BOTH(type,Name,_name)  PROPERTY_GET(type,Name,_name)  \
PROPERTY_SET(type,Name,_name)


#define  Q_PROPERTY_GET(type,Name,_name)  Q_PROPERTY(type Name READ get##Name)\
public:\
PROPERTY_GET(type,Name,_name)
#define  Q_PROPERTY_SET(type,Name,_name)   Q_PROPERTY(type Name WRITE set##Name)\
public:\
PROPERTY_SET(type, Name, _name)


#define  Q_PROPERTY_BOTH(type,Name,_name) Q_PROPERTY(type Name READ get##Name WRITE set##Name)\
public:\
PROPERTY_GET(type, Name, _name) \
PROPERTY_SET(type, Name, _name)

#endif // CommonMacro_H
