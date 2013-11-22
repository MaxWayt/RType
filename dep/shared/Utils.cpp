/*
 * RType
 *
 */

#ifdef WIN32
# undef __STRICT_ANSI__
#define _USE_MATH_DEFINES
#endif

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#ifdef UNIX
# include <sys/time.h>
#else
# include <time.h>
# include <Winsock2.h>
# include <sys/types.h>
# include <sys/timeb.h>
#endif
#include <cmath>
#include <limits>

#include "Utils.hpp"

void IntToString(int in, std::string& val)
{
    std::stringstream ss;
    ss << in;
    ss >> val;
}

void split(std::string const& s, char c, std::vector<std::string> &elems)
{
    std::istringstream ss(s);
    std::string item;
    while (std::getline(ss, item, c))
        elems.push_back(trim(item));
}

static inline std::string &ltrim(std::string &s)
{
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

static inline std::string &rtrim(std::string &s)
{
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

std::string &trim(std::string &s)
{
        return ltrim(rtrim(s));
}

void trim_quote(std::string& s)
{
    if (s.size() < 2)
        return;
    if (s[0] == '"' && s[s.size() - 1] == '"')
        s = s.substr(1, s.size() - 2);
}

uint32 GetMSTime()
{
    timeval time;
#ifdef UNIX
    gettimeofday(&time, NULL);
#else
	struct _timeb timebuffer;
	_ftime_s (&timebuffer);
	time.tv_sec = (long)timebuffer.time;
	time.tv_usec = timebuffer.millitm * 1000;
#endif
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

uint32 GetMSTimeDiffToNow(uint32 time)
{
    return GetMSTimeDiff(time, GetMSTime());
}

uint32 GetMSTimeDiff(uint32 prev, uint32 now)
{
    return now - prev;
}

bool FuzzyCompare(float f1, float f2)
{
    if (std::fabs(f1 - f2) < std::numeric_limits<float>::epsilon())
        return true;
    return false;
}

void Mod2PI(float &angle)
{
    if (angle < 0.f)
        angle = (float)M_PI * 2 + angle;
    else if (angle > (float)M_PI * 2)
        angle -= (float)M_PI * 2;
}
