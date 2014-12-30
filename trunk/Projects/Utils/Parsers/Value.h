
#ifndef Utils_Parsers_Value_h
#define Utils_Parsers_Value_h


// Library includes
#include <string>

// Project includes
#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>

// Forward declarations

// Namespace declarations


namespace Utils {


class Value
{
public:
	Value();
	Value(const std::string& v);
	Value(const std::string& t, const std::string& v);
	Value(const std::string& n, const std::string& t, const std::string& v);

public:
	const std::string& getName() const;
	const std::string& getType() const;
	const std::string& getValue() const;

	bool is(const std::string& name) const;
	bool is_(const std::string& name) const;

	bool isValid() const;

	bool ofType(const std::string& type) const;
	bool ofType_(const std::string& type) const;

	bool ofValue(const std::string& value) const;
	bool ofValue_(const std::string& value) const;

	bool toBool() const;
	double toDouble() const;
	float toFloat() const;
	int toInt() const;
	const std::string& toString() const;
	vector2f toVector2f();
	vector3f toVector3f();
	vector4f toVector4f();

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
