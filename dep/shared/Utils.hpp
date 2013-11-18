/*
 * RType
 *
 */

#ifndef UTILS_H_
# define UTILS_H_

#include <sstream>
#include <vector>
#include "SharedDefines.h"

template<class T>
T to(char const* buff)
{
    T val;
    std::stringstream ss;
    ss << buff;
    ss >> val;
    return val;
}

template<class T>
T to(std::string const& str)
{
    return to<T>(str.c_str());
}

void IntToString(int in, std::string& val);

void split(std::string const& s, char c, std::vector<std::string> &elems);
std::string &trim(std::string &s);
void trim_quote(std::string& s);

uint32 GetMSTime();
uint32 GetMSTimeDiffToNow(uint32 prev);
uint32 GetMSTimeDiff(uint32 prev, uint32 now);
bool FuzzyCompare(float f1, float f2);
void Mod2PI(float &angle);

#endif /* !UTILS_H_ */
