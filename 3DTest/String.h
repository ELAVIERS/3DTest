#pragma once

class String
{
	char*	_string;
	size_t	_size;

public:
	String();
	String(const char*);
	String(const String&);

	~String();

	static const String Convert(char);
	static const String Convert(int);
	static const String Convert(float);

	//Getters
	inline const char* GetData() const { return _string; };
	inline const size_t GetLength() const { return _size - 1; };
	inline const size_t GetSize() const { return _size; };

	//Basic operator overloads
	String& operator--();
	String& operator=(const String& other);
	String& operator=(const char* other);
	String& operator+=(const String& other);
	String& operator+=(const char* other);
	String& operator+=(char other);

	template <class T>
	const String operator+(const T& other) const {
		String str(*this);
		str += other;
		return str;
	};

	friend const String operator+(const char* a, const String& b);

	bool operator==(const char * other) const;
	inline bool operator==(const String& other) const { return operator==(other._string); };

	bool operator>(const String& other) const;
	bool operator<(const String& other) const;
};

#define CSTR(STRING) (String)(STRING).GetData()
