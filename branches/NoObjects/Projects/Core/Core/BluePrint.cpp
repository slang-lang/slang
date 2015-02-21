
// Header
#include "BluePrint.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


BluePrint::BluePrint()
: Interface("<unknown type>", "<none>"),
  mVisibility(Visibility::Public)
{
}

BluePrint::BluePrint(const std::string& type, const std::string& filename)
: Interface(type, filename),
  mVisibility(Visibility::Public)
{
}

BluePrint::~BluePrint()
{
}

const BluePrint::Ancestors& BluePrint::getAncestors() const
{
	return mAncestors;
}

Visibility::E BluePrint::getVisibility() const
{
	return mVisibility;
}

void BluePrint::setAncestors(const Ancestors& ancestors)
{
	mAncestors = ancestors;
}

void BluePrint::setVisibility(Visibility::E v)
{
	mVisibility = v;
}


}
