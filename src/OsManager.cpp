/*
 * This file manage the differences between several OS.
 * Copyright (C) 2020  Myrrhe <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "OsManager.hpp"
#include <iostream>
#include <istream>

#ifdef __linux__
#include <ctime>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>

#elif _WIN32
#include <Windows.h>
#include <direct.h>
#include <psapi.h>
#include <winnt.h>
#include <wtypes.h> // Need to be put before psapi.h

#elif _OSX

#endif // __linux__

namespace segment_d1
{

uint64_t OsManager::maxRAM;

#ifdef __linux__
const char OsManager::SlashC = '/';
const std::string OsManager::StrIcon = "iconl64.png";
const unsigned int OsManager::WidthIcon = 64;
const unsigned int OsManager::HeightIcon = 64;
#elif _WIN32
const char OsManager::SlashC = '\\';
const std::string OsManager::StrIcon = "iconw128.png";
const uint32_t OsManager::WidthIcon = 128;
const uint32_t OsManager::HeightIcon = 128;
#elif _OSX

#endif // __linux__

const std::string OsManager::Slash = std::string(1, OsManager::SlashC);

sf::Vector2<uint64_t> OsManager::getMonitorSize()
{
#ifdef __linux__
    Display *disp = XOpenDisplay(nullptr);
    Screen *scrn = DefaultScreenOfDisplay(disp);
    return sf::Vector2<uint64_t int>(static_cast<uint64_t>(scrn->width),
                                     static_cast<uint64_t>(scrn->height));
#elif _WIN32
    RECT desktop;
    auto res = sf::Vector2<uint64_t>(0, 0);
    if (::GetWindowRect(::GetDesktopWindow(), &desktop) != FALSE)
    {
        res = sf::Vector2<uint64_t>(static_cast<uint64_t>(desktop.bottom),
                                    static_cast<uint64_t>(desktop.right));
    }
    return res;
#elif _OSX

#endif // __linux__
}

float64_t OsManager::getWallTime()
{
#ifdef __linux__
    timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return static_cast<float64_t>(time.tv_sec) +
           static_cast<float64_t>(time.tv_nsec) * 0.000000001;
#elif _WIN32
    LARGE_INTEGER currTime;
    LARGE_INTEGER currFreq;
    float64_t res = 0;
    if ((TRUE == ::QueryPerformanceFrequency(&currFreq)) &&
        (TRUE == ::QueryPerformanceCounter(&currTime)))
    {
        res = static_cast<float64_t>(currTime.QuadPart) /
              static_cast<float64_t>(currFreq.QuadPart);
    }
    return res;
#elif _OSX

#endif // __linux__
}

float64_t OsManager::getCpuTime()
{
#ifdef __linux__
    return static_cast<double>(std::clock()) / CLOCKS_PER_SEC;
#elif _WIN32
    FILETIME a;
    FILETIME b;
    FILETIME c;
    FILETIME d;
    float64_t res = 0;
    if (::GetProcessTimes(::GetCurrentProcess(), &a, &b, &c, &d) != 0)
    {
        //  Returns total user time.
        //  Can be tweaked to include kernel times as well.
        res = static_cast<float64_t>(
                  d.dwLowDateTime |
                  (static_cast<uint64_t>(d.dwHighDateTime) << 32)) *
              0.0000001;
    }
    return res;
#elif _OSX

#endif // __linux__
}

int32_t OsManager::createDir(const std::string &str)
{
#ifdef __linux__
    return mkdir(str.c_str(), 01777);
#elif _WIN32
    return ::_mkdir(str.c_str());
#elif _OSX

#endif // __linux__
}

bool OsManager::sleep(const float64_t nbUsec)
{
#ifdef __linux__
    usleep(static_cast<__useconds_t>(nbUsec));
#elif _WIN32
    LARGE_INTEGER ft;
    ft.QuadPart = -static_cast<int64_t>(nbUsec);
    // Convert to 100 nanosecond interval,
    // negative value indicates relative time
    const HANDLE timer = CreateWaitableTimer(nullptr, TRUE, nullptr);
    const bool setOk =
        TRUE == ::SetWaitableTimer(timer, &ft, 0, nullptr, nullptr, 0);
    const bool waitOk = WAIT_OBJECT_0 == ::WaitForSingleObject(timer, INFINITE);
    const bool closeOk = TRUE == ::CloseHandle(timer);
    return setOk && waitOk && closeOk;
#elif _OSX

#endif // __linux__
}

void OsManager::initiateCoreFile()
{
#ifdef __linux__
    struct rlimit core_limits;
    core_limits.rlim_cur = core_limits.rlim_max = RLIM_INFINITY;
    setrlimit(RLIMIT_CORE, &core_limits);
#elif _WIN32

#elif _OSX

#endif // __linux__
}

uint64_t OsManager::getPhysicalMemoryUsed()
{
#ifdef __linux__
    struct sysinfo memInfo;
    sysinfo(&memInfo);
    uint64_t physMemUsed = memInfo.totalram - memInfo.freeram;
    // Multiply in next statement to avoid int overflow on right hand side...
    physMemUsed *= memInfo.mem_unit;
    return physMemUsed;
#elif _WIN32
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    uint64_t res = 0;
    if (TRUE == ::GlobalMemoryStatusEx(&memInfo))
    {
        res = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
    }
    return res;
#elif _OSX

#endif // __linux__
}

uint64_t OsManager::getPhysicalMemoryUsedProcess()
{
#ifdef __linux__
    // Note: this value is in kB !
    std::FILE *file = std::fopen("/proc/self/status", "r");
    uint64_t result = 0ul;
    char line[128];
    while (std::fgets(line, 128, file) != NULL)
    {
        if (std::strncmp(line, "VmRSS:", 6) == 0)
        {
            // This assumes that a digit will be found and the line ends
            // in " Kb".
            long unsigned int i = std::strlen(line);
            const char *p = line;
            while (*p < '0' || *p > '9')
            {
                p++;
            }
            line[i - 3] = '\0';
            result = std::strtoul(p, nullptr, 10);
            break;
        }
    }
    std::fclose(file);
    maxRAM = std::max(maxRAM, result); // Update the maximum RAM measured
    return result;
#elif _WIN32
    // Note: this value is in bits !
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (TRUE == ::GetProcessMemoryInfo(
                    ::GetCurrentProcess(),
                    reinterpret_cast<PROCESS_MEMORY_COUNTERS *>(&pmc),
                    sizeof(pmc)))
    {
        // Update the maximum RAM measured
        maxRAM = std::max(maxRAM, pmc.WorkingSetSize);
    }
    return pmc.WorkingSetSize;
#elif _OSX

#endif // __linux__
}

[[nodiscard]] uint64_t OsManager::getMaxRAM() { return maxRAM; }

} // namespace segment_d1
