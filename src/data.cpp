#include "data.h"


Data::Data(time_t a): t(a)
{

}

Data::Data(std::string s)
{
	struct std::tm tm = {};
	std::istringstream ss(s.c_str());
	ss >> std::get_time(&tm, "%Y-%m-%d");
	t = mktime(&tm);
}


unsigned long int Data::diff(const Data& d) const
{
	return std::difftime(d.getT(), t);
}



std::string Data::toStdString() const
{
	std::stringstream s;
	s<<*this;
	return s.str();
}

time_t Data::getT() const
{
	return t;
}

std::ostream& operator<<(std::ostream& os, const Data& dt)
{
	os<<std::put_time(localtime(&(dt.t)), "%Y-%m-%d");

	return os;
}
