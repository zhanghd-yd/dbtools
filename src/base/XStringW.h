#ifndef XSTRING_W_H
#define XSTRING_W_H

//#ifndef _CRT_NON_CONFORMING_SWPRINTFS
//#define _CRT_NON_CONFORMING_SWPRINTFS	1
//#endif

#pragma warning(disable:4786) 
#pragma warning(disable:4275) 
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
#include <xstring>
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
#include "StringTool.h"
#include <xlocbuf>
#include <codecvt>

#ifndef _T
#ifdef _UNICODE
#define _T(x) L ## x
#else
#define _T(x) x
#endif
#endif


//#ifndef TCHAR
//#ifdef _UNICODE
//typedef wchar_t     TCHAR;
//#else
//typedef char     TCHAR;
//#endif
//#endif
//#define _min(a,b) ((a)<(b)?(a):(b))
//#define _max(a,b) ((a)>(b)?(a):(b))
//#define bzero(ptr,n) memset(ptr,0,n)
//////////以下是一个string的包装类/////////////////////
// #ifndef L
// #define L(x)      L ## x
// #endif
class  XStringW : public std::wstring  
{	
public:
	int Delete( int nIndex, int nCount = 1 )
	{
		this->erase(nIndex,nCount);
		return this->GetLength();
	}
	int Insert( int nIndex, const wchar_t * pstr )
	{
		this->insert(nIndex,pstr);
		return this->GetLength();	
	}
	int Insert( int nIndex, wchar_t ch )
	{	
		XStringW strTmp(ch);
		this->insert(nIndex,strTmp);
		strTmp.Empty();
		return this->GetLength();
	}
	int Remove( wchar_t ch )
	{
		XStringW::iterator iter;
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
		XStringW strTmp;
		XStringW::iterator iter;
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
	int Find( wchar_t ch ) const
	{
		return this->find(ch);
	}
	int Find( const wchar_t * lpszSub ) const
	{
		return this->find(lpszSub);
	}
	int Find( wchar_t ch, int nStart ) const
	{
		return this->find(ch,nStart);
	}
	int Find( const wchar_t * pstr, int nStart ) const
	{
		return this->find(pstr,nStart);
	}
	int ReverseFind( wchar_t ch ) const
	{
		return this->find_last_of(ch);	
	}
	int FindOneOf( const wchar_t * lpszCharSet ) const
	{
		return this->find_first_of(lpszCharSet);
	}
	int Format2(const wchar_t* pstrFormat, ... )
	{///本函数仅仅支持ANSI标准字符集 '%[flags] [width] [.precision] [{h | l | I64 | L}]type'	 	
		clear();
		assert(pstrFormat!=NULL);
		va_list argList;
		va_start(argList,pstrFormat); 
		int nMaxLen = 0;
		for (const wchar_t * p = pstrFormat; *p != L'\0';p++ )
		{
			if (*p != L'%' || *(++p) == L'%')
			{// 如果不是L'%'就直接累计长度，如果是'%%'也使长度加1
				nMaxLen += 1;
				continue;
			}
			int nItemLen = 0; //用来保存每个参数的长度
			int nWidth = 0; //用来保存每一项的宽度
			for (; *p != L'\0'; p ++)
			{
				if (*p == L'#')
					nMaxLen += 2;   // 处理 '0x'
				else if (*p == L'*')
					nWidth = va_arg(argList, int);  //如：'%5f' 中的5
				else if (*p == L'-' || *p == L'+' || *p == L'0'|| *p == L' ')
					;  //忽略该符号
				else // 不是标志字符就退出循环
					break;
			}
			if (nWidth == 0)
			{ //提取宽度
				nWidth = _wtoi(p);
				for (; *p != L'\0' && isdigit(*p); p ++)
					;
			}
			assert(nWidth >= 0);//有效宽度
			int nPrecision = 0; //精度位数
			if (*p == L'.')
			{
				p++;// 跳过 L'.'字符 (宽度.精度)			
				if (*p == L'*')
				{ //有参数给出
					nPrecision = va_arg(argList, int);
					p ++;// 取得精度，跳过字符
				}
				else
				{ //在格式串中有宽度
					nPrecision = _wtoi(p);
					for (; *p != L'\0' && isdigit(*p);	p ++)
						;
				}
				assert(nPrecision >= 0);//有效宽度
			}
			switch (*p)
			{
			case L'h':     //short int 型
				p ++;
				break;
			case L'l':	 //long double 型
				p++;
				if (*p == L'l')
				{//支持"%lld" 处理 __int64
					p++;
				}
				break;
			case L'F':	 //近指针
			case L'N':	//远指针	
			case L'L':	//long double 型
				p++;
				break;
			}
			switch (*p)
			{
			case L'c':   //// 单个字符
			case L'C':
				nItemLen = 2;
				va_arg(argList, wchar_t);
				break;
			case L's':	//// 字符串
			case L'S':
				nItemLen = wcslen(va_arg(argList, const wchar_t*));
				nItemLen = ((1) > (nItemLen)) ? (1) : (nItemLen);//如果是空串就使用1 即保存L'\0'
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
				case L'd':    //整数的处理
				case L'i':
				case L'u':
				case L'x':
				case L'X':
				case L'o':
					va_arg(argList, int);
					nItemLen = 32;  //四字节
					nItemLen = ((nItemLen) > (nWidth+nPrecision)) ? (nItemLen) : (nWidth+nPrecision);//使用大者
					break;
				case L'e':	//浮点数
				case L'f':
				case L'g':
				case L'G':
					va_arg(argList, double);
					nItemLen = 32;//四字节
					nItemLen = ((nItemLen) > (nWidth+nPrecision)) ? (nItemLen) : (nWidth+nPrecision);//使用大者;
					break;
				case L'p':	//指针
					va_arg(argList, void*);
					nItemLen = 32;
					nItemLen = ((nItemLen) > (nWidth+nPrecision)) ? (nItemLen) : (nWidth+nPrecision);//使用大者;
					break;
				case L'n':
					va_arg(argList, int*); //指向整数的指针,见BorlanderC++3.1库函数P352
					break;
				default:
					assert(false);  //不能处理的格式，给出警告
				}
			}
			nMaxLen += nItemLen;//把该项的长度累计
		}
		va_end(argList);
		va_start(argList, pstrFormat);  // 重新开始提取参数
		wchar_t* ch = new wchar_t[nMaxLen+1]; //分配内存
		//vswprintf(ch, pstrFormat, argList);
		vswprintf_s(ch, nMaxLen + 1, pstrFormat, argList);
		//swprintf_s(ch, nMaxLen + 1,pstrFormat, argList);
		//assert(vswprintf(ch, pstrFormat, argList) <= nMaxLen);
		this->append(ch); //加到string的尾部
		delete[] ch; //释放内存
		va_end(argList);
		return nMaxLen;
	}

	XStringW& Format(const wchar_t* pstrFormat, ...)
	{
		va_list ParamList;
		va_start(ParamList, pstrFormat);

		FormatInner(pstrFormat, ParamList);

		va_end(ParamList);

		return *this;

	}

	XStringW& FormatInner(const wchar_t* pstrFormat, va_list ParamList)
	{
		//首先测试获取结果长度
		int iLength = _vscwprintf(pstrFormat, ParamList);
		//resize(iLength + 1);
		resize(iLength);
		vswprintf_s((wchar_t*)(void*)data(), iLength + 1, pstrFormat, ParamList);

		return *this;
	}
	int GetLength() const
	{
		return this->length();
	}
	XStringW& operator=(const std::wstring& str)
	{
		if (this->compare(str) == 0) return *this;
		this->assign(str);
		return *this;
	}
	XStringW& operator=(const XStringW& str)
	{
		if (this->compare(str) == 0) return *this;
		this->assign(str);
		return *this;
	}
	XStringW& operator=(XStringW&& str)
	{
		swap(str);
		return *this;
	}
	XStringW& operator=(std::wstring&& str)
	{
		swap(str);
		return *this;
	}
	XStringW& operator=(wchar_t ch)
	{
		this->Empty();
		this->insert(this->begin(),ch);
		return *this;
	}
	XStringW& operator =( const wchar_t * lpsz )
	{
		this->Empty();
		if (lpsz)
		{
			this->append(lpsz);
		}
		return *this;
	}	
	XStringW Left(int nCount) const
	{
		if (nCount <=0) 
			return XStringW(L"");	
		XStringW strTmp;
		strTmp = this->substr(0,nCount);
		return strTmp;
	}
	XStringW Right(int nCount) const
	{
		if (nCount <=0) 
			return XStringW(L"");
		XStringW strTmp;
		if (nCount > GetLength())
			strTmp = this->substr(0);
		else
			strTmp = this->substr(GetLength()-nCount);
		return strTmp;
	}
	XStringW RightFrom(int nIndex) const
	{
		return Right(size() - nIndex);
	}
	XStringW Mid(int nFirst) const
	{
		XStringW strTmp;
		if (nFirst >= GetLength())
			return XStringW(L"");
		if (nFirst <= 0)
			strTmp = this->substr(0);
		else
			strTmp = this->substr(nFirst);
		return strTmp;		
	}
	XStringW Mid( int nFirst, int nCount) const
	{
		if (nCount <= 0) 
			return XStringW(L"");
		if (nFirst >= GetLength())
			return XStringW(L"");
		XStringW strTmp;
		if (nFirst <= 0)
			strTmp = this->substr(0,nCount);
		else
			strTmp = this->substr(nFirst,nCount);
		return strTmp;				
	}

	XStringW& MakeUpper()
	{
		std::transform(this->begin (),
			this->end (),this->begin (),
			toupper);
		return *this;
	}
	XStringW& MakeLower()
	{
		std::transform(this->begin (),
			this->end (),this->begin (),
			tolower);
		return *this;
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
	wchar_t GetAt( int nIndex ) const
	{
		return this->at(nIndex);
	}
	const wchar_t& operator []( int nIndex ) const
	{
		return this->at(nIndex);
	}
	wchar_t& operator []( int nIndex )
	{
		return this->at(nIndex);
	}

	void SetAt( int nIndex, wchar_t ch )
	{
		this->at(nIndex) = ch;
	}
	operator const wchar_t * ( ) const
	{
		return this->c_str();
	}
	friend XStringW operator + (const XStringW& string1, const XStringW& string2)
	{
		XStringW str;
		str.append(string1);
		str.append(string2);
		return str;
	}
	friend XStringW operator + ( const XStringW& string1,const wchar_t ch )
	{
		XStringW str;
		str.append(string1);
		str.insert(str.end(),ch);
		return str;
	}
	friend XStringW operator + (const wchar_t ch, const XStringW& string1 )
	{
		XStringW str;
		str.insert(str.end(),ch);
		str.append(string1);
		return str;
	}
	friend XStringW operator + ( const XStringW& string1,const wchar_t* ch )
	{
		XStringW str;
		str.append(string1);
		str.append(ch);
		return str;
	}
	friend XStringW operator + (const wchar_t* ch, const XStringW& string1 )
	{
		XStringW str;
		str.append(ch);
		str.append(string1);
		return str;
	}
	int Compare( const wchar_t * lpsz ) const
	{
		XStringW str;
		str.append(lpsz);
		return this->compare(str);
	}
	int Compare( const XStringW& string1 ) const
	{
		return this->compare(string1);
	}
	int CompareNoCase( const wchar_t * lpsz ) const
	{
		XStringW str,strThis;
		str.append(lpsz);
		strThis = (*this);
		str.MakeLower();
		strThis.MakeLower();
		return strThis.compare(str);
	}
	int CompareNoCase( const XStringW& string1 ) const
	{
		XStringW str,strThis;
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
	void TrimRight()
	{
		TrimRight(L' ');
		TrimRight(L'\t');
		TrimRight(L'\r');
		TrimRight(L'\n');
	}
	void TrimLeft()
	{
		TrimLeft(L' ');
		TrimLeft(L'\t');
		TrimLeft(L'\r');
		TrimLeft(L'\n');
	}
	void TrimLeft( wchar_t chTarget )
	{
		if (empty())
		{
			return;
		}
		std::wstring::size_type pos;
		pos = this->find_first_not_of(chTarget);
		if (pos == std::wstring::npos)
		{
			this->clear();
			return;
		}
		if (pos == 0) return; 
		this->erase(this->begin(),this->begin()+pos);		
	}
	void TrimRight( wchar_t chTarget )
	{
		if (empty())
		{
			return;
		}
		std::wstring::size_type pos;
		pos = this->find_last_not_of(chTarget);
		if (pos == std::wstring::npos)
		{
			this->clear();
			return;
		}
		++pos;
		if (pos == this->GetLength())
			return; 
		this->erase(this->begin()+pos,this->end());		
	}
	void Replace( wchar_t chOld, wchar_t chNew )
	{
		for(int i=0;i<this->GetLength();i++)
		{
			if (this->at(i) == chOld)
				this->at(i) = chNew;
		}		
	}
	void Replace(const wchar_t* chOld,const wchar_t* chNew )
	{
		int new_size = 0;
		while (chNew[new_size])
		{
			new_size++;
		}
		int index = this->find(chOld);
		while (index > -1)
		{
			this->erase(index, wcslen(chOld));
			this->insert(index, chNew);
			index = this->find(chOld, index + new_size);
		}
		//int index = this->find(chOld);
		//while (index > -1)
		//{
		//	this->erase(index,wcslen(chOld));
		//	this->insert(index,chNew);
		//	index = this->find(chOld);
		//}
	}		
	wchar_t * GetBuffer( int nMinBufLength )
	{
		this->resize(nMinBufLength);
		return &(*(this->begin()));
	}
	void ReleaseBuffer( int nNewLength = -1 )
	{
		this->TrimRight(L'\0');
	}

	bool StartWith(wchar_t c)
	{
		return CStringTool::StartWith(c_str(),c);
	}
	bool StartWith(const wchar_t* str)
	{
		return CStringTool::StartWith(c_str(),str);
	}
	bool StartWith(const XStringW& str)
	{
		return CStringTool::StartWith(c_str(),str.c_str());
	}
	bool EndWith(wchar_t c)
	{
		return CStringTool::EndWith(c_str(),c);
	}
	bool EndWith(const wchar_t* str)
	{
		return CStringTool::EndWith(c_str(),str);
	}
	bool EndWith(const XStringW& str)
	{
		return CStringTool::EndWith(c_str(),str.c_str());
	}
	bool HasChar(wchar_t c)
	{
		return CStringTool::HasChar(c_str(),c);
	}
	void Split(std::vector<XStringW>& StringArray,const XStringW& strSeperator,bool bRemoveEmptyString = true) const
	{
		StringArray.clear();
		if (strSeperator.empty())
		{
			return;
		}
		const wchar_t* src = c_str();
		const wchar_t* seperator = strSeperator.c_str();
		wchar_t c;
		XStringW str;
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
	void Split(std::vector<XStringW>& StringArray,const wchar_t* strSeperator,bool bRemoveEmptyString = true) const
	{
		StringArray.clear();
		if (!strSeperator || !*strSeperator)
		{
			return;
		}
		const wchar_t* src = c_str();
		wchar_t c;
		XStringW str;
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

	std::vector<XStringW> Split(const wchar_t* strSeperator, bool bRemoveEmptyString = true) const
	{
		std::vector<XStringW> StringArray;
		Split(StringArray, strSeperator, bRemoveEmptyString);
		return std::move(StringArray);
	}
	static void Split(std::vector<XStringW>& StringArray,const wchar_t* strSource,const wchar_t* strSeperator,bool bRemoveEmptyString = true) 
	{
		StringArray.clear();
		if (!strSource || !*strSource || !strSeperator || !*strSeperator)
		{
			return;
		}
		wchar_t c;
		XStringW str;
		while(c = *strSource++)
		{
			if (CStringTool::HasChar(strSource,c))
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
	void CopyToCharArray(wchar_t* array,unsigned max_size) const
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
			memcpy(array,c_str(),length*sizeof(wchar_t));
		}
		array[length] = 0;
	}

	std::wstring&& RightValueRef()
	{
		return std::move(*this);
	}
	XStringW(const XStringW& string1)
	{
		this->append(string1);
	}
	XStringW(const std::wstring& string1)
	{
		this->append(string1);
	}
	XStringW(const wchar_t *ch)
	{
		if (ch)
		{
			this->append(ch);
		}
	}
	XStringW(const wchar_t ch)
	{
		*this += ch;
	}
	XStringW(XStringW&& string1)
	{
		this->swap(string1);
	}
	XStringW(std::wstring&& string1)
	{
		this->swap(string1);
	}
	XStringW()
	{}


};


typedef XStringW StringW;


#endif