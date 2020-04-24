
#ifndef Utils_Parsers_Value_h
#define Utils_Parsers_Value_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace Utils {


class Value
{
public:
	Value();
	explicit Value(std::string v);
	Value(std::string t, std::string v);
	Value(std::string n, std::string t, std::string v);

public:
	const std::string& getName() const;
	const std::string& getType() const;
	const std::string& getValue() const;

	bool is(const std::string& name) const;
	bool isValid() const;

	bool ofType(const std::string& type) const;
	bool ofValue(const std::string& value) const;

	bool toBool() const;
	double toDouble() const;
	float toFloat() const;
	int toInt() const;
	const std::string& toString() const;

public:	// Array specifics
	bool isArray() const;
	size_t size() const;
	void size(size_t size);

protected:
	std::string	mName;
	std::string	mType;
	std::string mValue;

private:	// Array specifics
	bool	mIsArray;
	size_t	mSize;

private:

};


}


#endif
