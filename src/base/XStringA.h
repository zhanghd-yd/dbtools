#ifndef XSTRING_A_H
#define XSTRING_A_H

#pragma warning(disable:4786) 
#pragma warning(disable:4275) 
#pragma warning(disable : 4996)//zhd
#pragma warning(disable : 4267)//zhd
#include <iostream>
#include <Iterator>
#include <List>
#include <deque>
#include <map>
#include <numeric>     //accumulate
#include <set>
#include <stack>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <fstream>
#include <memory>
#include <queue>
#include <complex>
//#include <sstream>
#include <cctype>   //isalpha()
#include <new>
#include <cstdarg>  //number not knowing arguments.such as :pringf
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "XStringW.h"

//#define _min(a,b) ((a)<(b)?(a):(b))
//#define _max(a,b) ((a)>(b)?(a):(b))
//#define bzero(ptr,n) memset(ptr,0,n)
//////////以下是一个string的包装类/////////////////////
class  XStringA : public std::string  
{	
public:
	int Delete( int nIndex, int nCount = 1 )
	{
		this->erase(nIndex,nCount);
		return this->GetLength();
	}
	int Insert( int nIndex, const char * pstr )
	{
		this->insert(nIndex,pstr);
		return this->GetLength();	
	}
	int Insert( int nIndex, char ch )
	{	
		XStringA strTmp(ch);
		this->insert(nIndex,strTmp);
		strTmp.Empty();
		return this->GetLength();
	}
	int Remove( char ch )
	{
		XStringA::iterator iter;
		int count = 0;
		for(iter = this->begin(); iter != this->end();iter ++)
		{
			if(*iter == ch)
			{
				this->erase(iter);count++;
			}
		}
		return count;
	}
	void RemoveFrom(int index)
	{
		if (length() > index)
		{
			erase(index,length()-index);
		}
	}
	void MakeReverse( )
	{
		XStringA strTmp;
		XStringA::iterator iter;
		iter=this->end();
		iter--;
		for(; iter != this->begin(); iter--)
		{
			strTmp += *iter;
		}
		strTmp += *iter;
		*this = strTmp;
		strTmp.Empty();
	}
	int Find( char ch ) const
	{
		return this->find(ch);
	}
	int Find( const char * lpszSub ) const
	{
		return this->find(lpszSub);
	}
	int Find( char ch, int nStart ) const
	{
		return this->find(ch,nStart);
	}
	int Find( const char * pstr, int nStart ) const
	{
		return this->find(pstr,nStart);
	}
	int ReverseFind( char ch ) const
	{
		return this->find_last_of(ch);	
	}
	int FindOneOf( const char * lpszCharSet ) const
	{
		return this->find_first_of(lpszCharSet);
	}

	bool Contains(const char* sub, bool caseSensitive = true)
	{
		if (caseSensitive)
		{
			return find(sub) != -1;
		}
		else
		{
			XStringA low = std::move(Lower()); 
			XStringA lowSub = sub;
			lowSub.MakeLower();
			return low.find(lowSub.data()) != -1;
		}
	}



	int Format2(const char* pstrFormat, ... )
	{///本函数仅仅支持ANSI标准字符集 '%[flags] [width] [.precision] [{h | l | I64 | L}]type'	 	
		clear();
		assert(pstrFormat!=NULL);
		va_list argList;
		va_start(argList,pstrFormat); 
		int nMaxLen = 0;
		bool bInt64 = false;

		for (const char * p = pstrFormat; *p != '\0';p++ )
		{
			if (*p != '%' || *(++p) == '%')
			{// 如果不是'%'就直接累计长度，如果是'%%'也使长度加1
				nMaxLen += 1;
				continue;
			}
			int nItemLen = 0; //用来保存每个参数的长度
			int nWidth = 0; //用来保存每一项的宽度
			for (; *p != '\0'; p ++)
			{
				if (*p == '#')
					nMaxLen += 2;   // 处理 '0x'
				else if (*p == '*')
					nWidth = va_arg(argList, int);  //如：'%5f' 中的5
				else if (*p == '-' || *p == '+' || *p == '0'|| *p == ' ')
					;  //忽略该符号
				else // 不是标志字符就退出循环
					break;
			}
			if (nWidth == 0)
			{ //提取宽度
				nWidth = atoi(p);
				for (; *p != '\0' && isdigit(*p); p ++)
					;
			}
			assert(nWidth >= 0);//有效宽度
			int nPrecision = 0; //精度位数
			if (*p == '.')
			{
				p++;// 跳过 '.'字符 (宽度.精度)			
				if (*p == '*')
				{ //有参数给出
					nPrecision = va_arg(argList, int);
					p ++;// 取得精度，跳过字符
				}
				else
				{ //在格式串中有宽度
					nPrecision = atoi(p);
					for (; *p != '\0' && isdigit(*p);	p ++)
						;
				}
				assert(nPrecision >= 0);//有效宽度
			}
			switch (*p)
			{
			case 'h':     //short int 型
				p ++;
				break;
			case 'l':	 //long double 型
				p ++;
				if (*p == 'l')
				{//支持"%lld" 处理 __int64
					p++;
					bInt64 = true;
				}
				break;
			case 'F':	 //近指针
			case 'N':	//远指针	
			case 'L':	//long double 型
				p++;
				break;
			}
			switch (*p)
			{
			case 'c':   //// 单个字符
			case 'C':
				nItemLen = 2;
				va_arg(argList, char);
				break;
			case 's':	//// 字符串
			case 'S':
				nItemLen = strlen(va_arg(argList, const char*));
				nItemLen = ((1) > (nItemLen)) ? (1) : (nItemLen);//如果是空串就使用1 即保存'\0'
				break;
			}
			if (nItemLen != 0)		
			{
				nItemLen = ((nItemLen) > (nWidth)) ? (nItemLen) : (nWidth);//使用大者
				if (nPrecision != 0)
					nItemLen = ((nItemLen) < (nPrecision)) ? (nItemLen) : (nPrecision);
			}
			else
			{
				switch (*p)
				{
				case 'd':    //整数的处理
				case 'i':
				case 'u':
				case 'x':
				case 'X':
				case 'o':
					if (bInt64)
					{
						va_arg(argList, __int64); 
					}
					else
					{
						va_arg(argList, int);
					}
					nItemLen = 32;  //四字节
					nItemLen = ((nItemLen) > (nWidth+nPrecision)) ? (nItemLen) : (nWidth+nPrecision);//使用大者
					break;
				case 'e':	//浮点数
				case 'f':
				case 'g':
				case 'G':
					va_arg(argList, double);
					nItemLen = 32;//四字节
					nItemLen = ((nItemLen) > (nWidth+nPrecision)) ? (nItemLen) : (nWidth+nPrecision);//使用大者;
					break;
				case 'p':	//指针
					va_arg(argList, void*);
					nItemLen = 32;
					nItemLen = ((nItemLen) > (nWidth+nPrecision)) ? (nItemLen) : (nWidth+nPrecision);//使用大者;
					break;
				case 'n':
					va_arg(argList, int*); //指向整数的指针,见BorlanderC++3.1库函数P352
					break;
				default:
					assert(false);  //不能处理的格式，给出警告
				}
			}
			bInt64 = false;
			nMaxLen += nItemLen;//把该项的长度累计
		}
		va_end(argList);
		va_start(argList, pstrFormat);  // 重新开始提取参数
		char* ch = new char[nMaxLen+1]; //分配内存
		//sprintf_s(ch, nMaxLen + 1, pstrFormat, argList);
		//vsprintf(ch, pstrFormat, argList);
		vsprintf_s(ch, nMaxLen + 1, pstrFormat, argList);
		//assert(vsprintf(ch, pstrFormat, argList) <= nMaxLen);
		this->append(ch); //加到string的尾部
		delete[] ch; //释放内存
		va_end(argList);
#ifdef _DEBUG
		if (debug_length(data()) > nMaxLen)
		{
			ASSERT(false);
		}
#endif
		return nMaxLen;
	}
	XStringA& Format(const char* pstrFormat, ...)
	{
		va_list ParamList;
		va_start(ParamList, pstrFormat);

		FormatInner(pstrFormat, ParamList);

		va_end(ParamList);

		return *this;

	}

	XStringA& FormatInner(const char* pstrFormat, va_list ParamList)
	{
		//首先测试获取结果长度
		int iLength = _vscprintf(pstrFormat, ParamList);
		//resize(iLength + 1);
		resize(iLength);
		vsprintf_s((char*)(void*)data(), iLength + 1, pstrFormat, ParamList);

		return *this;
	}

	unsigned debug_length(const char* str)
	{
		if (!str)
		{
			return 0;
		}
		unsigned nLength = 0;
		while (*str++)
		{
			nLength++;
		}
		return nLength;
	}

	int GetLength() const
	{
		return this->length();
	}
	XStringA Left(int nCount) const
	{
		if (nCount <=0) 
			return XStringA("");	
		XStringA strTmp;
		strTmp = this->substr(0,nCount);
		return strTmp;
	}
	XStringA Right(int nCount) const
	{
		if (nCount <=0) 
			return XStringA("");
		XStringA strTmp;
		if (nCount > GetLength())
			strTmp = this->substr(0);
		else
			strTmp = this->substr(GetLength()-nCount);
		return strTmp;
	}
	XStringA RightFrom(int nIndex) const
	{
		return Right(size() - nIndex);
	}
	XStringA Mid(int nFirst) const
	{
		XStringA strTmp;
		if (nFirst >= GetLength())
			return XStringA("");
		if (nFirst <= 0)
			strTmp = this->substr(0);
		else
			strTmp = this->substr(nFirst);
		return strTmp;		
	}
	XStringA Mid( int nFirst, int nCount) const
	{
		if (nCount <= 0) 
			return XStringA("");
		if (nFirst >= GetLength())
			return XStringA("");
		XStringA strTmp;
		if (nFirst <= 0)
			strTmp = this->substr(0,nCount);
		else
			strTmp = this->substr(nFirst,nCount);
		return strTmp;				
	}
	XStringA PickIn(char start,char end)
	{
		XStringA sub;
		int count;
		const char* pos = CStringTool::PickIn(c_str(),start,end,count);
		if (count > 0)
		{
			sub.assign(pos,count);
		}
		return sub;
	}
	XStringA& operator=(const std::string& str)
	{
		if (this->compare(str) == 0) return *this;
		this->assign(str);
		return *this;
	}
	XStringA& operator=(const XStringA& str)
	{
		if (this->compare(str) == 0) return *this;
		this->assign(str);
		return *this;
	}
	XStringA& operator=(XStringA&& str)
	{
		swap(str);
		return *this;
	}
	XStringA& operator=(std::string&& str)
	{
		swap(str);
		return *this;
	}
	XStringA& operator=(char ch)
	{
		this->Empty();
		this->insert(this->begin(),ch);
		return *this;
	}
	XStringA& operator =( const char * lpsz )
	{
		this->Empty();
		if (lpsz)
		{
			this->append(lpsz);
		}
		return *this;
	}
	//把自己全部大写然后返回
	XStringA& MakeUpper()
	{
		std::transform(this->begin (),
			this->end (),this->begin (),
			toupper);
		return *this;
	}
	//把自己全部小写然后返回
	XStringA& MakeLower()
	{
		std::transform(this->begin (),
			this->end (),this->begin (),
			tolower);
		return *this;
	}
	void ToUpper()
	{
		std::transform(this->begin(),
			this->end(), this->begin(),
			toupper);
	}
	void ToLower()
	{
		std::transform(this->begin(),
			this->end(), this->begin(),
			tolower);
	}
	//返回大写,自己不变
	XStringA Upper()
	{
		XStringA u = data();
		return std::move(u.MakeUpper());
	}
	//返回小写,自己不变
	XStringA Lower()
	{
		XStringA l = data();
		return std::move(l.MakeLower());
	}
	bool IsEmpty( ) const
	{
		return this->empty(); 
	}
	bool NotEmpty( ) const
	{
		return !this->empty(); 
	}
	void Empty( )
	{//清除
		this->erase(this->begin(),this->end());
	}
	char GetAt( int nIndex ) const
	{
		return this->at(nIndex);
	}
	const char& operator []( int nIndex ) const
	{
		return this->at(nIndex);
	}
	char& operator []( int nIndex )
	{
		return this->at(nIndex);
	}
	void SetAt( int nIndex, char ch )
	{
		this->at(nIndex) = ch;
	}
	operator const char * ( ) const
	{
		return this->c_str();
	}
	friend XStringA operator + (const XStringA& string1, const XStringA& string2)
	{
		XStringA str;
		str.append(string1);
		str.append(string2);
		return str;
	}
	friend XStringA operator + ( const XStringA& string1,const char ch )
	{
		XStringA str;
		str.append(string1);
		str.insert(str.end(),ch);
		return str;
	}
	friend XStringA operator + (const char ch, const XStringA& string1 )
	{
		XStringA str;
		str.insert(str.end(),ch);
		str.append(string1);
		return str;
	}
	friend XStringA operator + ( const XStringA& string1,const char* ch )
	{
		XStringA str;
		str.append(string1);
		str.append(ch);
		return str;
	}
	friend XStringA operator + (const char* ch, const XStringA& string1 )
	{
		XStringA str;
		str.append(ch);
		str.append(string1);
		return str;
	}

	int Compare( const char * lpsz ) const
	{
		XStringA str;
		str.append(lpsz);
		return this->compare(str);
	}
	int Compare( const XStringA& string1 ) const
	{
		return this->compare(string1);
	}
	int CompareNoCase( const char * lpsz ) const
	{
		XStringA str,strThis;
		str.append(lpsz);
		strThis = (*this);
		str.MakeLower();
		strThis.MakeLower();
		return strThis.compare(str);
	}
	int CompareNoCase( const XStringA& string1 ) const
	{
		XStringA str,strThis;
		str = string1;
		strThis = (*this);
		str.MakeLower();
		strThis.MakeLower();
		return strThis.compare(str);
	}
	void Trim()
	{
		TrimLeft();
		TrimRight();
	}
	void TrimRight( )
	{
		TrimRight(' ');
		TrimRight('\t');
		TrimRight('\r');
		TrimRight('\n');
	}
	void TrimLeft( )
	{
		TrimLeft(' ');
		TrimLeft('\t');
		TrimLeft('\r');
		TrimLeft('\n');
	}
	void TrimLeft( char chTarget )
	{
		if (empty())
		{
			return;
		}
		std::string::size_type pos;
		pos = this->find_first_not_of(chTarget);
		if (pos == 0) return; 

		if (pos == std::string::npos)
		{
			this->clear();
			return; 
		}
		this->erase(this->begin(), this->begin() + pos);

	}
	void TrimRight( char chTarget )
	{
		if (empty())
		{
			return;
		}
		std::string::size_type pos;
		pos = this->find_last_not_of(chTarget);

		if (pos == std::string::npos)
		{
			this->clear();
			return;
		}
		++pos;
		if (pos == this->GetLength())
			return; 
		this->erase(this->begin()+pos,this->end());		
	}
	void Replace( char chOld, char chNew )
	{
		for(int i=0;i<this->GetLength();i++)
		{
			if (this->at(i) == chOld)
				this->at(i) = chNew;
		}		
	}
	void Replace(const char* chOld,const char* chNew )
	{
		int new_size = 0;
		while (chNew[new_size])
		{
			new_size++;
		}
		int index = this->find(chOld);
		while (index > -1)
		{
			this->erase(index,strlen(chOld));
			this->insert(index,chNew);
			index = this->find(chOld, index + new_size);
		}
	}		
	char * GetBuffer( int nMinBufLength = 0)
	{
		if (nMinBufLength > 0)
		{
			this->resize(nMinBufLength);
		}
		return &(*(this->begin()));
	}
	void ReleaseBuffer( int nNewLength = -1 )
	{
		XStringA s = data();
		this->swap(s);
		//this->TrimRight('\0');
	}
	bool StartWith(char c) const
	{
		return empty()? false : at(0) == c;
	}
	bool StartWith(const char* str) const
	{
		if (empty() || !str || *str == 0)
		{
			return false;
		}
		const char* src = c_str();
		while(*src && *str)
		{
			if (*src++ != *str++)
			{
				return false;
			}
		}
		return  *str == 0;
	}
	bool StartWith(const XStringA& str) const
	{
		if (str.empty())
		{
			return false;
		}
		return  StartWith(str.c_str());
	}
	bool EndWith(char c) const
	{
		if (empty())
		{
			return false;
		}
		return back() == c;
	}
	bool EndWith(const char* str) const
	{
		if (empty() || !str || *str == 0)
		{
			return false;
		}
		int nStrLength = CStringTool::GetLength(str);
		int nSrcLength = length();
		if (nStrLength > nSrcLength)
		{
			return false;
		}
		const char* src = c_str() + nSrcLength - nStrLength;
		while(nStrLength--)
		{
			if (*src++ != *str++)
			{
				return false;
			}
		}
		return  true;
	}
	bool EndWith(const XStringA& str) const
	{
		if (str.empty())
		{
			return false;
		}
		return  EndWith(str.c_str());
	}
	bool HasChar(char c)
	{
		return empty()? false : CStringTool::HasChar(c_str(),c);
	}
	void Split(std::vector<XStringA>& StringArray,const XStringA& strSeperator,bool bRemoveEmptyString = true) const
	{
		StringArray.clear();
		if (strSeperator.empty())
		{
			return;
		}
		const char* src = c_str();
		const char* seperator = strSeperator.c_str();
		char c;
		XStringA str;
		while(c = *src++)
		{
			if (CStringTool::HasChar(seperator,c))
			{
				if (str.length()>0 || (!bRemoveEmptyString))
				{
					StringArray.push_back(str);
					str.clear();
				}
			}
			else
			{
				str.push_back(c);
			}
		}
		if (str.length()>0 || (!bRemoveEmptyString))
		{
			StringArray.push_back(str);
		}
	}
	void Split(std::vector<XStringA>& StringArray,const char* strSeperator,bool bRemoveEmptyString = true) const
	{
		StringArray.clear();
		if (!strSeperator || !*strSeperator)
		{
			return;
		}
		const char* src = c_str();
		char c;
		XStringA str;
		while(c = *src++)
		{
			if (CStringTool::HasChar(strSeperator,c))
			{
				if (str.length()>0 || (!bRemoveEmptyString))
				{
					StringArray.push_back(str);
					str.clear();
				}
			}
			else
			{
				str.push_back(c);
			}
		}
		if (str.length()>0 || (!bRemoveEmptyString))
		{
			StringArray.push_back(str);
		}
	}
	std::vector<XStringA> Split(const char* strSeperator, bool bRemoveEmptyString = true) const
	{
		std::vector<XStringA> StringArray;
		Split(StringArray, strSeperator, bRemoveEmptyString);
		return std::move(StringArray);
	}
	static void Split(std::vector<XStringA>& StringArray,const char* strSource,const char* strSeperator,bool bRemoveEmptyString = true) 
	{
		StringArray.clear();
		if (!strSource || !*strSource || !strSeperator || !*strSeperator)
		{
			return;
		}
		char c;
		XStringA str;
		while(c = *strSource++)
		{
			if (CStringTool::HasChar(strSeperator, c))
			{
				if (str.length()>0 || (!bRemoveEmptyString))
				{
					StringArray.push_back(str);
					str.clear();
				}
			}
			else
			{
				str.push_back(c);
			}
		}
		if (str.length()>0 || (!bRemoveEmptyString))
		{
			StringArray.push_back(str);
		}
	}
	void CopyToCharArray(char* array,unsigned max_size) const
	{
		if (max_size == 0)
		{
			return;
		}
		unsigned length = this->length();
		if (--max_size < length)
		{
			length = max_size;
		}
		if (length)
		{
			memcpy(array,c_str(),length);
		}
		array[length] = 0;
	}
	//XStringA& GBToUTF8()
	//{
	//	this->swap(GBToUTF8(data()));
	//	return *this;
	//}
	//XStringA& UTF8ToGB()
	//{
	//	this->swap(UTF8ToGB(data()));
	//	return *this;
	//}

	std::string&& RightValueRef()
	{
		return std::move(*this);
	}

	static XStringA& toStringRef(std::string& str)
	{
/*
		String& sss = String::toStringRef(ssss);
*/
		XStringA& s = *(XStringA*)(void*)(&str);
		return s;
	}
	static const XStringA& toConstStringRef(const std::string& str)
	{
		/*
				const String& sss = String::toConstStringRef(ssss);
		*/
		const XStringA& s = *(const XStringA*)(void*)(&str);
		return s;
	}

	static XStringW UTF8ToUnicode(const std::string& str)
	{
		static std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
		try
		{
			return std::move(cvt.from_bytes(str));
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return XStringW();
		}
	}

	static XStringA UnicodeToUTF8(const std::wstring& wstr)
	{
		static std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
		try
		{
			return std::move(cvt.to_bytes(wstr));
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return XStringA();
		}
	}

	static XStringA UnicodeToLocale(const std::wstring& wstr, const std::locale& locale)
	{
		return std::move(UnicodeToLocale(wstr, locale.name()));
	}

	static XStringA UnicodeToLocale(const std::wstring& wstr, const std::string& localeName)
	{
		using F = std::codecvt_byname<wchar_t, char, std::mbstate_t>;
		std::wstring_convert<F> cvt(new F(localeName));
		try
		{
			return std::move(cvt.to_bytes(wstr));
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return XStringA();
		}
	}

	static XStringW LocaleToUnicode(const std::string& str, const std::locale& locale)
	{
		return std::move(LocaleToUnicode(str, locale.name()));
	}

	static std::wstring LocaleToUnicode(const std::string& str, const std::string& localeName)
	{
		using F = std::codecvt_byname<wchar_t, char, std::mbstate_t>;
		std::wstring_convert<F> cvt(new F(localeName));
		try
		{
			return std::move(cvt.from_bytes(str));
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return std::wstring();
		}
	}

	static std::string UnicodeToANSI(const std::wstring& wstr)
	{
		return std::move(UnicodeToLocale(wstr, ""));
	}

	static std::wstring ANSIToUniCode(const std::string& str)
	{
		return std::move(LocaleToUnicode(str, ""));
	}


	static std::string UTF8ToANSI(const std::string& str)
	{
		return std::move(UnicodeToANSI(UTF8ToUnicode(str)));
	}

	static std::string ANSIToUTF8(const std::string& str)
	{
		return std::move(UnicodeToUTF8(ANSIToUniCode(str)));
	}

	static XStringA GBToUTF8(const char* ansiStr)
	{

		return std::move(UnicodeToUTF8(ANSIToUniCode(ansiStr)));
	}

	static XStringA UTF8ToGB(const char* utf8Str)
	{

		return std::move(UnicodeToANSI(UTF8ToUnicode(utf8Str)));
	}

	XStringA(const XStringA& string1)
	{
		this->append(string1);
	}
	XStringA(XStringA&& string1)
	{
		this->swap(string1);
	}
	XStringA(std::string&& string1)
	{
		this->swap(string1);
	}
	XStringA(const std::string& string1)
	{
		this->append(string1);
	}
	XStringA(const char *ch)
	{
		if(ch)
		{
			this->append(ch);
		}
	}
	XStringA(const char ch)
	{
		*this += ch;
	}
	XStringA()
	{}
};

typedef XStringA StringA;


#ifdef _UNICODE
typedef XStringW     String;
//#define  ConstString const XStringW&
typedef   const String& ConstStringRef;
#else
typedef XStringA     String;
//#define  ConstStringRef const XStringA&
typedef   const String& ConstStringRef;
#endif

typedef   const XStringW& ConstStringWRef;
typedef   const XStringA& ConstStringARef;


#define  Copy_To_CharArray(a)   CopyToCharArray(a,sizeof(a))

#endif