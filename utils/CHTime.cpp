#include "CHTime.h"

#include <iostream>

void CHTime::pt()
{
    gettm(getTimeStamp());
}

void CHTime::pt(const char* tag)
{
    std::cout << tag << ": ";
    gettm(getTimeStamp());
}

std::string CHTime::gt()
{
    time_t milli = getTimeStamp() + (std::time_t)8 * 60 * 60 * 1000;
    auto mTime = std::chrono::milliseconds(milli);
    auto tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(mTime);
    auto tt = std::chrono::system_clock::to_time_t(tp);

    struct tm now;
    gmtime_s(&now, &tt);
    std::string result
        = std::to_string(now.tm_min) + ":"
        + std::to_string(now.tm_sec) + ":"
        + std::to_string(milli % 1000);
    return result;
}

std::time_t CHTime::getTimeStamp()
{
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
    std::time_t timestamp = tmp.count();
    //std::time_t timestamp = std::chrono::system_clock::to_time_t(tp);
    return timestamp;
}

std::tm* CHTime::gettm(std::time_t timestamp)
{
    std::time_t milli = timestamp + (std::time_t)8*60*60*1000;//�˴�ת��Ϊ����������ʱ�䣬���������ʱ����Ҫ�������޸�
    auto mTime = std::chrono::milliseconds(milli);
    auto tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(mTime);
    auto tt = std::chrono::system_clock::to_time_t(tp);

    struct tm now;
    gmtime_s(&now, &tt);
    printf("%02d:%02d:%02d.%03d\n", now.tm_hour, now.tm_min, now.tm_sec, (int)(milli % 1000));
    //printf("%03lld\n", milli);
    
    //std::tm* now = std::gmtime(&tt);
    //printf("%4d��%02d��%02d�� %02d:%02d:%02d.%d\n", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, milli % 1000);
    return &now;
}

int64_t CHTime::getTImeMicros()
{
#ifdef _WIN32
    // ��1601��1��1��0:0:0:000��1970��1��1��0:0:0:000��ʱ��(��λ100ns)
#define EPOCHFILETIME   (116444736000000000UL)
    FILETIME ft;
    LARGE_INTEGER li;
    int64_t tt = 0;
    GetSystemTimeAsFileTime(&ft);
    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;
    // ��1970��1��1��0:0:0:000�����ڵ�΢����(UTCʱ��)
    tt = (li.QuadPart - EPOCHFILETIME) / 10;
    return tt;
#else
    timeval tv;
    gettimeofday(&tv, 0);
    return (int64_t)tv.tv_sec * 1000000 + (int64_t)tv.tv_usec;
#endif // _WIN32
    return 0;
}