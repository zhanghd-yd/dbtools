#ifndef STRING_TOOLS_H
#define STRING_TOOLS_H

#pragma warning(disable : 4018)//zhd

#ifndef ASSERT
#define ASSERT Q_ASSERT
#include <QDebug>
#endif
class CStringTool
{
public:
	template<class T> 
	static unsigned GetLength(const T* str)
	{
		if (!str)
		{
			return 0;
		}
		unsigned nLength = 0;
		while(*str++)
		{
			nLength++;
		}
		return nLength;
	}
	template<class T> 
	static bool HasChar(const T* str,T c)
	{
		while(*str)
		{
			if (*str++ == c)
			{
				return true;
			}
		}
		return false;
	}
	template<class T> 
	static bool StartWith(const T* src,T c)
	{
		return GetLength(src) ? *src == c : false;
	}
	template<class T> 
	static bool StartWith(const T* src,const T* str)
	{
		if (GetLength(src) && GetLength(str))
		{
			while(*src && *str)
			{
				if (*src++ != *str++)
				{
					return false;
				}
			}
			return *str == 0;
		}
		else
		{
			return false;
		}
	}
	template<class T> 
	static bool EndWith(const T* src,T c)
	{
		int length = GetLength(src);
		return length ? src[length-1] == c : false;
	}
	template<class T> 
	static bool EndWith(const T* src,const T* str)
	{
		int nSrcLength = GetLength(src);
		int nStrLength = GetLength(str);

		if (nSrcLength && nStrLength && nStrLength <= nSrcLength)
		{
			src += nSrcLength - nStrLength;
			while(nStrLength--)
			{
				if (*src++ != *str++)
				{
					return false;
				}
			}
			return  true;
		}
		else
		{
			return false;
		}
	}

	template<class T> 
	static int Find(const T* src,T c,unsigned from = 0)
	{
		if (from<GetLength(src))
		{
			src+=from;
			while(*src)
			{
				if (*src++ == c)
				{
					return from;
				}
				from++;
			}
		}
		return -1;
	}
	template<class T> 
	static int Find(const T* src,const T* str,unsigned from = 0)
	{
		int nSrcLength = GetLength(src);
		int nStrLength = GetLength(str);
		int left;
		int flag = 0;
		if (nStrLength && nSrcLength-from >= nStrLength)
		{
			left = nSrcLength-from - nStrLength+1;
			while(left && src[from])
			{
				flag = 0;
				while (src[from+flag] == str[flag])
				{
					flag++;
					if (flag == nStrLength)
					{
						return from;
					}
				}
				from++;
				left--;
			}
		}
		return -1;
	}
	template<class T> 
	static int ReverseFind(const T* src,T c) 
	{
		int length = GetLength(src);
		while(length)
		{
			if (src[--length] == c)
			{
				return length;
			}
		}
		return -1;
	}
	//count = 0查找成功 无字符 返回无效
	//count <0查找失败 无字符  返回无效
	//count >0 查找成功  有字符 返回有效
	template<class T> 
	static const T* PickIn(const T* src,T start,T end,int& count)
	{
		count = -1;
		int a = Find(src,start);
		if (a < 0)
		{
			return NULL;
		}
		int b = Find(src,end,a+1);
		if (b < a)
		{
			return NULL;
		}
		count = b-a-1;
		if (count)
		{
			return src+a+1;
		}
		return NULL;
	}

	template<class T> 
	static void CopyToCharArray(const T* src,T* array,unsigned max_size)
	{
		if (max_size == 0)
		{
			return;
		}
		unsigned length = GetLength(src);
		if (--max_size < length)
		{
			length = max_size;
		}
		if (length)
		{
			memcpy(array,src,length*sizeof(T));
		}
		array[length] = 0;
	}



	template<class T>
	inline bool ReadWord(T* pSource, T* pDestination, int& nStart)
	{
		T c;
		bool flag = false;
		int i = nStart;
		int j = 0;
		for (; i < 1024*1024; i++)
		{
			c = pSource[i];
			if (flag)//如果已经开始读入字符
			{
				if (c == ' ' || c == '\t' || c == 0)//碰到空白 返回|| c == '\r' || c == '\n'
				{
					pDestination[j] = 0;
					nStart = i;
					return true;
				}
				else//遇到字符  读入数据
				{
					pDestination[j] = pSource[i];
					j++;
					continue;
				}
			}
			else//如果没有开始读入字符
			{
				if (c == ' ' || c == '\t')//碰到空白 继续读入下一个字符 || c == '\r' || c == '\n'
				{
					continue;
				}
				else if (c == 0)
				{
					break;
				}
				else//遇到字符  读入数据
				{
					flag = true;
					pDestination[j] = pSource[i];
					j++;
					continue;
				}
			}
		}

		pDestination[j] = 0;
		return false;
	}
};

class CCharArray
{//不是一个健壮的类，慎用，小心数组越界
public:

	CCharArray()
	{
		m_array = NULL;
		m_size = 0;
	}
	CCharArray(char* array,unsigned size)
	{
		reset(array,size);
	}
	void reset(char* array,unsigned size)
	{
		ASSERT(size > 0 && array);
		m_array = array;
		m_size = size;

	}
	void initialize()
	{
		//int i = 0;
		//while(i<m_size)
		//{
		//	m_array[i++] = 0;
		//}
		int size = m_size;
		char* array = m_array;
		while(size--) *array++ = 0;
	}
	const char& operator []( unsigned nIndex ) const
	{
		ASSERT(nIndex <m_size);
		return m_array[nIndex];
	}
	char& operator []( unsigned nIndex )
	{
		ASSERT(nIndex <m_size);
		return m_array[nIndex];
	}
	operator const char * ( ) const
	{
		return m_array;
	}
	const char * c_str( ) const
	{
		return m_array;
	}
	const char * data( ) const
	{
		return m_array;
	}
	unsigned size()
	{
		return m_size;
	} 
	unsigned length()
	{
		int len = CStringTool::GetLength(m_array);
		if (len < m_size)
		{
			return len;
		}
		else
		{
			ASSERT(false);
			return 0;
		}
	} 

	const CCharArray& operator =( const CCharArray& str )
	{
		m_array = str.m_array;
		m_size = str.m_size;
		return *this;
	}
	const char * operator =( const char * str )
	{
		unsigned length = CStringTool::GetLength(str);
		CStringTool::CopyToCharArray(str,m_array,m_size);
		return m_array;
	}
	void operator += ( const char * str )
	{
		int len = length();
		CCharArray CharArray (m_array+len,m_size-len);
		CharArray = str;
	}
	bool operator == ( const char * str )
	{
		unsigned len = CStringTool::GetLength(str);
		if (len != length())
		{
			return false;
		}
		char* array = m_array;


		for (int i = 0; i < len; i++)
		{
			if (array[i] != str[i])
			{
				return false;
			}
		}
		return true;
	}
	bool operator != ( const char * str )
	{
		return !(*this == str);
	}



protected:
	char* m_array;
	unsigned m_size;
};

class CCharArrayW
{//不是一个健壮的类，慎用，小心数组越界
public:

	CCharArrayW(wchar_t* array, unsigned size)
	{
		reset(array, size);
	}
	void reset(wchar_t* array, unsigned size)
	{
		ASSERT(size > 0 && array);
		m_array = array;
		m_size = size;

	}
	void initialize()
	{
		//int i = 0;
		//while(i<m_size)
		//{
		//	m_array[i++] = 0;
		//}
		int size = m_size;
		wchar_t* array = m_array;
		while (size--) *array++ = 0;
	}
	const wchar_t& operator [](unsigned nIndex) const
	{
		ASSERT(nIndex < m_size);
		return m_array[nIndex];
	}
	wchar_t& operator [](unsigned nIndex)
	{
		ASSERT(nIndex < m_size);
		return m_array[nIndex];
	}
	operator const wchar_t * () const
	{
		return m_array;
	}
	const wchar_t * c_str() const
	{
		return m_array;
	}
	const wchar_t * data() const
	{
		return m_array;
	}
	unsigned size()
	{
		return m_size;
	}
	unsigned length()
	{
		int len = CStringTool::GetLength(m_array);
		if (len < m_size)
		{
			return len;
		}
		else
		{
			ASSERT(false);
			//int i = 1/0;
			return 0;
		}
	}

	const CCharArrayW& operator =(const CCharArrayW& str)
	{
		m_array = str.m_array;
		m_size = str.m_size;
		return *this;
	}
	const wchar_t * operator =(const wchar_t * str)
	{
		unsigned length = CStringTool::GetLength(str);
		CStringTool::CopyToCharArray(str, m_array, m_size);
		return m_array;
	}
	void operator += (const wchar_t * str)
	{
		int len = length();
		CCharArrayW CharArray(m_array + len, m_size - len);
		CharArray = str;
	}
	bool operator == (const wchar_t * str)
	{
		unsigned len = CStringTool::GetLength(str);
		if (len != length())
		{
			return false;
		}
		wchar_t* array = m_array;


		for (int i = 0; i < len; i++)
		{
			if (array[i] != str[i])
			{
				return false;
			}
		}
		return true;
	}
	bool operator != ( const wchar_t * str )
	{
		return !(*this == str);
	}
protected:
	wchar_t* m_array;
	unsigned m_size;
};

#endif