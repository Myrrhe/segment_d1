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
#include "Constants.hpp"
#include "Func.hpp"
#include "Logger.hpp"
#include <GL/glu.h>
#include <codecvt>
#include <cstring>
#include <fstream>
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

#include <Shcore.h>

namespace segment_d1
{

uint64_t OsManager::maxRAM;
uint64_t OsManager::maxVirtualMemory;

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

std::vector<ScreenConnected> OsManager::screens;
std::vector<std::wstring> OsManager::displayDeviceNames;
std::vector<std::string> OsManager::envPath;
std::string OsManager::path;
std::string OsManager::protoPath;
std::string OsManager::cwd;
std::string OsManager::argv0;
std::string OsManager::card;
std::string OsManager::vendor;
std::string OsManager::glVer;
std::string OsManager::glslVer;
bool OsManager::firstTextureRead;

std::string OsManager::stdVer;
std::uint64_t OsManager::RAM;
std::string OsManager::processor;
std::string OsManager::OS;
std::string OsManager::verOS;
std::string OsManager::archOS;

bool OsManager::colorOn;

std::wstring OsManager::strTowstr(const std::string &str)
{
    return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t,
                                std::allocator<wchar_t>, std::allocator<char>>()
        .from_bytes(str);
}

std::string OsManager::wstrTostr(const std::wstring &wstr)
{
    return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t,
                                std::allocator<wchar_t>, std::allocator<char>>()
        .to_bytes(wstr);
}

void OsManager::initialize()
{
    initializeVer();
    initializeListScreen();
    colorOn = true;
}

void OsManager::initializeVer()
{
#ifdef __linux__
    long int numPages = sysconf(_SC_PHYS_PAGES);
    long int pageSize = sysconf(_SC_PAGE_SIZE);
    // convert to MiB from B
    RAM = static_cast<std::uint64_t>(numPages * pageSize /**1000*/ /
                                     (1024l * 1024l /**1024l*/));
    std::array<int, 12ul> model;
    /*auto*/ unsigned int callId = 0x80000002;
    asm volatile("cpuid"
                 : "=a"(model[0]), "=b"(model[1]), "=c"(model[2]),
                   "=d"(model[3])
                 : "a"(callId));
    ++callId;
    asm volatile("cpuid"
                 : "=a"(model[4]), "=b"(model[5]), "=c"(model[6]),
                   "=d"(model[7])
                 : "a"(callId));
    ++callId;
    asm volatile("cpuid"
                 : "=a"(model[8]), "=b"(model[9]), "=c"(model[10]),
                   "=d"(model[11])
                 : "a"(callId));
    // model is null-terminated
    processor =
        static_cast<std::string>(reinterpret_cast<const char *>(&model[0]));
    // remove leading spaces (string is provided right-justified
    processor.erase(0, processor.find_first_not_of(' '));
    utsname linuxInfo;
    if (uname(&linuxInfo) == -1)
    {
        OS = /*""*/ "Unknown";
        verOS = /*""*/ "Unknown";
        archOS = /*""*/ "Unknown";
    }
    else
    {
        OS = static_cast<std::string>(linuxInfo.sysname) + " " +
             static_cast<std::string>(linuxInfo.version);
        verOS = static_cast<std::string>(linuxInfo.release);
        archOS = static_cast<std::string>(linuxInfo.machine);
    }
    stdVer = "C++" + std::to_string((__cplusplus / 100) % 100);
    card = static_cast<std::string>(
        reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
    vendor = static_cast<std::string>(
        reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
    glVer = static_cast<std::string>(
        reinterpret_cast<const char *>(glGetString(GL_VERSION)));
    glslVer = static_cast<std::string>(reinterpret_cast<const char *>(
        glGetString(GL_SHADING_LANGUAGE_VERSION)));
#elif _WIN32
    RAM = 0;
    processor = "Unknown";
    OS = "Windows";
    // It work
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    if (TRUE == GetVersionEx(reinterpret_cast<OSVERSIONINFO *>(&osvi)))
    {
        std::basic_ostringstream<char, std::char_traits<char>,
                                 std::allocator<char>>
            oss;
        oss << osvi.dwMajorVersion << '.' << osvi.dwMinorVersion << '.'
            << osvi.dwBuildNumber;
        oss << " SP" << osvi.wServicePackMajor << '.' << osvi.wServicePackMinor;
        verOS = oss.str();
    }
    archOS = "Unknwown";
    const int64_t startVerCpp = 100;
    const int64_t lenVerCpp = 100;
    stdVer = "C++" + std::to_string((__cplusplus / startVerCpp) % lenVerCpp);
    card = static_cast<std::string>(
        reinterpret_cast<const char *>(::glGetString(GL_RENDERER)));
    vendor = static_cast<std::string>(
        reinterpret_cast<const char *>(::glGetString(GL_VENDOR)));
    glVer = static_cast<std::string>(
        reinterpret_cast<const char *>(::glGetString(GL_VERSION)));
    glslVer = "Unknown";
#elif _OSX
#endif // __linux__
}

void OsManager::initializeListScreen()
{
#ifdef __linux__
    Display *disp = XOpenDisplay(nullptr);
    screens.resize(static_cast<long unsigned int>(XScreenCount(disp)));
    displayDeviceNames.resize(screens.size());
    for (long unsigned int i = 0ul; i < screens.size(); i++)
    {
        Screen screen = *XScreenOfDisplay(disp, static_cast<int>(i));
        Window root = RootWindow(disp, i);
        XRRScreenResources *ressource = XRRGetScreenResources(disp, root);
        XRROutputInfo *output =
            XRRGetOutputInfo(disp, ressource, *(ressource->outputs));
        std::string strName = static_cast<std::string>(output->name);
        // Make room for characters
        screens[i].name = /*L""*/ std::wstring(strName.length(), L' ');
        // Copy string to wstring.
        std::copy(strName.begin(), strName.end(), screens[i].name.begin());
        displayDeviceNames[i] = /*screens[i].name*/ L"Unknown";
        screens[i].bounds =
            sf::Rect<float>(0.0f, 0.0f, static_cast<float>(screen.width),
                            static_cast<float>(screen.height));
        XRRScreenConfiguration *conf = XRRGetScreenInfo(disp, root);
        screens[i].refreshRate =
            static_cast<unsigned int>(XRRConfigCurrentRate(conf));
        screens[i].dpi = sf::Vector2<unsigned int>(
            static_cast<unsigned int>(screen.width / (screen.mwidth / 25.4)),
            static_cast<unsigned int>(screen.height / (screen.mheight / 25.4)));
    }
#elif _WIN32
    ScreenConnected primaryScreen;
    std::wstring primaryScreenDeviceName;
    // Enumerate all available screen
    DISPLAY_DEVICE displayDevice;
    std::memset(&displayDevice, 0, sizeof(displayDevice));
    displayDevice.cb = sizeof(displayDevice);
    uint32_t count = 0;
    while (TRUE == EnumDisplayDevices(nullptr, count, &displayDevice, 0))
    {
        ++count;
        // check if the screen is not mirrored and there is actually a screen
        // attached
        if ((0 ==
             (displayDevice.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER)) &&
            (0 !=
             (displayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)))
        {
            // try to get the screens current desktop video mode
            // to access its position and dimension in the virtual screen space
            DEVMODE win32Mode;
            std::memset(&win32Mode, 0, sizeof(win32Mode));
            win32Mode.dmSize = sizeof(win32Mode);

            if (FALSE == ::EnumDisplaySettingsA(displayDevice.DeviceName,
                                                ENUM_CURRENT_SETTINGS,
                                                &win32Mode))
            {
                Logger().info("Couldn't get settings of screen: " +
                              std::string(displayDevice.DeviceName));
                break;
            }

            // get the screens real name
            DISPLAY_DEVICE nameDD;
            std::memset(&nameDD, 0, sizeof(nameDD));
            nameDD.cb = sizeof(nameDD);

            if (FALSE == EnumDisplayDevices(displayDevice.DeviceName, 0,
                                            &nameDD,
                                            EDD_GET_DEVICE_INTERFACE_NAME))
            {
                Logger().info("Error loading screen.");
            }

            // get the DPI
            sf::Vector2<uint32_t> dpi;

            // Since windows 8.1 you can get the DPI on a per monitor basis
            //=================================================================
            if (const HMODULE hShcore = LoadLibrary(/*L*/ "Shcore.dll");
                nullptr != hShcore)
            {
                typedef HRESULT(WINAPI * GetDpiForMonitorFuncType)(
                    HMONITOR hmonitor, int32_t dpiType, UINT * dpiX,
                    UINT * dpiY);

                // GetDpiForMonitor function address
                if (auto *const pGetDpiForMonitor =
                        reinterpret_cast<GetDpiForMonitorFuncType>(
                            ::GetProcAddress(hShcore, "GetDpiForMonitor"));
                    nullptr != pGetDpiForMonitor)
                {
                    // Handle to monitor
                    if (const HMONITOR hMonitor = ::MonitorFromPoint(
                            POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
                        nullptr != hMonitor)
                    {
                        UINT dpiX = 0;
                        UINT dpiY = 0;
                        const HRESULT hr = pGetDpiForMonitor(
                            hMonitor, /*MDT_Effective_DPI*/ 0, &dpiX, &dpiY);
                        if (!FAILED(hr))
                        {
                            dpi = sf::Vector2<uint32_t>(dpiX, dpiY);
                        }
                    }
                }
                if (FALSE == ::FreeLibrary(hShcore))
                {
                    Logger().info("Error freeing libraries");
                }
            }
            //=================================================================

            // If the library loading failed (library not available or windows
            // version < 8.1) use the old way of getting the DPI (one value for
            // all monitors)
            if (dpi == sf::Vector2<uint32_t>())
            {
                const HDC hdc = CreateDC(displayDevice.DeviceName, nullptr,
                                         nullptr, nullptr);
                if (nullptr != hdc)
                {
                    dpi = sf::Vector2<uint32_t>(
                        static_cast<uint32_t>(::GetDeviceCaps(hdc, LOGPIXELSX)),
                        static_cast<uint32_t>(
                            ::GetDeviceCaps(hdc, LOGPIXELSY)));
                }
            }

            // save the data
            ScreenConnected screen;
            screen.name =
                strTowstr(static_cast<std::string>(nameDD.DeviceString));
            screen.bounds = sf::Rect<float32_t>(
                static_cast<float32_t>(win32Mode.dmPosition.x),
                static_cast<float32_t>(win32Mode.dmPosition.y),
                static_cast<float32_t>(win32Mode.dmPelsWidth),
                static_cast<float32_t>(win32Mode.dmPelsHeight));
            screen.refreshRate = win32Mode.dmDisplayFrequency;
            screen.dpi = dpi;

            // sort any additional screen is from left to right
            if (0 != (displayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE))
            {
                primaryScreen = screen;
                primaryScreenDeviceName = strTowstr(
                    static_cast<std::string>(displayDevice.DeviceName));
                continue;
            }
            else
            {
                std::size_t index = screens.size();
                const std::size_t screensSize = screens.size();
                for (std::size_t i = 0; i < screensSize; ++i)
                {
                    if (screens[i].bounds.left > screen.bounds.left)
                    {
                        index = i;
                        break;
                    }
                }
                screens.insert(screens.begin() + static_cast<int64_t>(index),
                               screen);
                displayDeviceNames.insert(
                    displayDeviceNames.begin() + static_cast<int64_t>(index),
                    strTowstr(
                        static_cast<std::string>(displayDevice.DeviceName)));
            }
        }
    }

    // the primary screen is always at index [0]
    screens.insert(screens.begin(), primaryScreen);
    displayDeviceNames.insert(displayDeviceNames.begin(),
                              primaryScreenDeviceName);
#elif _OSX
#endif // __linux__
}

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

uint64_t OsManager::getVirtualMemoryUsedProcess()
{
#ifdef __linux__
    // Note: this value is in kB !
    std::FILE *file = std::fopen("/proc/self/status", "r");
    uint64_t result = 0ul;
    char line[128];
    while (std::fgets(line, 128, file) != NULL)
    {
        if (std::strncmp(line, "VmSize:", 7) == 0)
        {
            // This assumes that a digit will be found and the line ends in "
            // Kb".
            uint64_t i = std::strlen(line);
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
    maxVirtualMemory = std::max(maxVirtualMemory, result);
    return result;
#elif _WIN32
    uint64_t res = 0;
    if (PROCESS_MEMORY_COUNTERS_EX pmc;
        TRUE == ::K32GetProcessMemoryInfo(
                    ::GetCurrentProcess(),
                    reinterpret_cast<PROCESS_MEMORY_COUNTERS *>(&pmc),
                    sizeof(pmc)))
    {
        maxVirtualMemory = std::max(maxVirtualMemory, pmc.PrivateUsage);
        res = pmc.PrivateUsage;
    }
    return res;
#elif _OSX

#endif // __linux__
}

uint64_t OsManager::getMaxRAM() { return maxRAM; }

void OsManager::setPath(const std::string_view &newArgv0)
{
    envPath = {std::getenv("PATH")};
    std::array<char, PATH_MAX> buff;
    cwd = "";
    if (nullptr != ::getcwd(&buff[0], PATH_MAX))
    {
        cwd = std::string(&buff[0]);
    }
    argv0 = newArgv0;
    path = newArgv0;
    while ((path[path.size() - 1] != SlashC) && (path != ""))
    {
        path = path.substr(0, path.size() - 1);
    }
    protoPath = path;
    path += "gamefiles";
}

const std::string &OsManager::getPath() { return path; }

sf::Vector2<uint32_t> OsManager::getSizePng(const std::string &file)
{
#ifdef __linux__
    std::ifstream in(file);
    // ntohl(width) -> unsigned int
    uint32_t width = 0;
    uint32_t height = 0;
    in.seekg(16);
    in.read(reinterpret_cast<char *>(&width), 4);
    in.read(reinterpret_cast<char *>(&height), 4);
    return sf::Vector2<uint32_t>(::ntohl(width), ::ntohl(height));
#elif _WIN32
    auto res = sf::Vector2<uint32_t>(0, 0);
    uint32_t width = 0;
    uint32_t height = 0;
    if (std::ifstream in(file, std::ios::binary); in.seekg(16))
    {
        std::array<char, 8> buffer;
        if (in.read(buffer.data(), sizeof(buffer)))
        {
            std::memcpy(&width, buffer.data(), sizeof(width));
            std::memcpy(&height, buffer.data() + sizeof(width), sizeof(height));
            res = sf::Vector2<uint32_t>(::ntohl(width), ::ntohl(height));
        }
    }
    return res;
#elif _OSX

#endif // __linux__
}

void OsManager::loadTextureR(
    const std::string &dir,
    std::shared_ptr<std::map<std::string, sf::Texture, std::less<>>>
        &mapTexture,
    const std::vector<std::string> *const vectorIdTexture,
    uint32_t *const nbTextureCurrent)
{
#ifdef __linux__
    struct dirent *read;
    DIR *rep;
    rep = opendir(dir.c_str());
    if (rep == nullptr)
    {
        std::perror(dir.c_str());
        return;
    }
    while ((read = readdir(rep)) != nullptr)
    {
        if (read->d_type == DT_DIR)
        {
            if ('.' != read->d_name[0])
            {
                loadTextureR(dir + Slash + read->d_name, mapTexture,
                             vectorIdTexture, nbTextureCurrent);
            }
        }
        else
        {
            if (static_cast<std::string>(
                    &read->d_name[std::strlen(read->d_name) -
                                  imgExtension.size()]) == imgExtension)
            {
                (*mapTexture)[read->d_name] =
                    loadTexture(dir + Slash + read->d_name);
                ++(*nbTextureCurrent);
            }
        }
    }
    closedir(rep);
#elif _WIN32
    std::string tmp = dir + Slash + "*";
    WIN32_FIND_DATA file;
    const HANDLE searchHandle = FindFirstFile(tmp.c_str(), &file);
    if (searchHandle != INVALID_HANDLE_VALUE)
    {
        std::vector<std::string> directories;
        do
        {
            if (((file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0) &&
                ((0 == lstrcmp(file.cFileName, ".")) ||
                 (0 == lstrcmp(file.cFileName, ".."))))
            {
                continue;
            }

            tmp = dir + Slash + static_cast<std::string>(file.cFileName);

            if ((tmp.size() > 3) &&
                (tmp.substr(tmp.size() - ImgExtension.size(),
                            ImgExtension.size()) == ImgExtension))
            {
                (*mapTexture)[static_cast<std::string>(file.cFileName)] =
                    Func::loadTexture(tmp);
                ++(*nbTextureCurrent);
            }

            if ((file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0)
            {
                directories.push_back(tmp);
            }
        } while (TRUE == FindNextFile(searchHandle, &file));
        if (TRUE == ::FindClose(searchHandle))
        {
            const auto end = directories.end();
            for (auto iter = directories.begin(); iter != end; ++iter)
            {
                loadTextureR(*iter, mapTexture, vectorIdTexture,
                             nbTextureCurrent);
            }
        }
    }
#elif _OSX

#endif // __linux__
}

void OsManager::loadTextureEmptyR(
    const std::string &dir,
    const std::shared_ptr<std::map<std::string, sf::Texture, std::less<>>>
        &mapTexture,
    std::map<std::string, sf::Rect<int32_t>, std::less<>> *const mapTextureRect,
    std::map<std::string, bool, std::less<>> *const mapTextureLoaded,
    std::map<std::string, std::string, std::less<>> *const mapTexturePath,
    std::vector<std::string> *const vectorIdTexture,
    std::vector<sf::Texture *> *const vectorPointerTexture,
    uint32_t *const nbTextureTotal)
{
#ifdef __linux__
    struct dirent *read;
    DIR *rep;
    rep = opendir(dir.c_str());
    if (rep == nullptr)
    {
        std::perror(dir.c_str());
        return;
    }
    while ((read = readdir(rep)) != nullptr)
    {
        if (read->d_type == DT_DIR)
        {
            if ('.' != read->d_name[0])
            {
                loadTextureEmptyR(dir + Slash + read->d_name, mapTexture,
                                  mapTextureRect, mapTextureLoaded,
                                  mapTexturePath, vectorIdTexture,
                                  vectorPointerTexture, nbTextureTotal);
            }
        }
        else
        {
            if (static_cast<std::string>(
                    &read->d_name[std::strlen(read->d_name) -
                                  imgExtension.size()]) == imgExtension)
            {
                std::size_t i;
                for (i = 0ul; i < bigTexture.size(); i++)
                {
                    if (bigTexture[i] ==
                        static_cast<std::string>(read->d_name)
                            .substr(0, std::strlen(read->d_name) -
                                           imgExtension.size()))
                    {
                        break;
                    }
                }
#if DISPLAY_TEXTURE_SIZE && DEBUG
                std::cout << read->d_name << " : "
                          << getSizePng(dir + Slash + read->d_name)
                          << std::endl;
#endif // DISPLAY_TEXTURE_SIZE && DEBUG
#if !DISPLAY_TEXTURE_SIZE && WARNING_SIZE_1024 && DEBUG
                if (getSizePng(dir + Slash + read->d_name).x >= 1024 ||
                    getSizePng(dir + Slash + read->d_name).y >= 1024)
                {
                    std::cout << read->d_name << " : "
                              << getSizePng(dir + Slash + read->d_name)
                              << std::endl;
                }
#endif // !DISPLAY_TEXTURE_SIZE && WARNING_SIZE_1024 && DEBUG
                if (i < bigTexture.size())
                {
                    for (std::size_t j = 0ul; j < rectBigTexture[i].size(); j++)
                    {
                        (*mapTexture)[static_cast<std::string>(read->d_name)
                                          .substr(0, std::strlen(read->d_name) -
                                                         imgExtension.size()) +
                                      std::to_string(j) + imgExtension] =
                            sf::Texture();
                        (*mapTextureRect)[static_cast<std::string>(read->d_name)
                                              .substr(
                                                  0, std::strlen(read->d_name) -
                                                         imgExtension.size()) +
                                          std::to_string(j) + imgExtension] =
                            scaleri(rectBigTexture[i][j]);
                        (*mapTextureLoaded)
                            [static_cast<std::string>(read->d_name)
                                 .substr(0, std::strlen(read->d_name) -
                                                imgExtension.size()) +
                             std::to_string(j) + imgExtension] = false;
                        vectorIdTexture->push_back(
                            static_cast<std::string>(read->d_name)
                                .substr(0, std::strlen(read->d_name) -
                                               imgExtension.size()) +
                            std::to_string(j) + imgExtension);
                        vectorPointerTexture->push_back(&(
                            *mapTexture)[static_cast<std::string>(read->d_name)
                                             .substr(0,
                                                     std::strlen(read->d_name) -
                                                         imgExtension.size()) +
                                         std::to_string(j) + imgExtension]);
                    }
                }
                else
                {
                    (*mapTexture)[read->d_name] = sf::Texture();
                    sf::Vector2<unsigned int> newRect =
                        getSizePng(dir + Slash + read->d_name);
                    (*mapTextureRect)[read->d_name] =
                        sf::Rect<int>(0, 0, static_cast<int>(newRect.x),
                                      static_cast<int>(newRect.y));
                    (*mapTextureLoaded)[read->d_name] = false;
                    vectorIdTexture->push_back(read->d_name);
                    vectorPointerTexture->push_back(
                        &(*mapTexture)[read->d_name]);
                }
                (*mapTexturePath)[read->d_name] = dir + Slash + read->d_name;
                ++(*nbTextureTotal);
            }
        }
    }
    closedir(rep);
#elif _WIN32
    std::string tmp = dir + Slash + "*";
    WIN32_FIND_DATA file;
    const HANDLE searchHandle = FindFirstFile(tmp.c_str(), &file);
    if (searchHandle != INVALID_HANDLE_VALUE)
    {
        std::vector<std::string> directories;
        do
        {
            if (((file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0) &&
                ((0 == lstrcmp(file.cFileName, ".")) ||
                 (0 == lstrcmp(file.cFileName, ".."))))
            {
                continue;
            }

            tmp = dir + Slash + static_cast<std::string>(file.cFileName);

            if ((tmp.size() > 3) &&
                (tmp.substr(tmp.size() - ImgExtension.size(),
                            ImgExtension.size()) == ImgExtension))
            {
                (*mapTexture)[static_cast<std::string>(file.cFileName)] =
                    sf::Texture();
                const sf::Vector2<uint32_t> newRect = getSizePng(tmp);
                (*mapTextureRect)[static_cast<std::string>(file.cFileName)] =
                    sf::Rect<int32_t>(0, 0, static_cast<int32_t>(newRect.x),
                                      static_cast<int32_t>(newRect.y));
                (*mapTextureLoaded)[static_cast<std::string>(file.cFileName)] =
                    false;
                vectorIdTexture->push_back(
                    static_cast<std::string>(file.cFileName));
                vectorPointerTexture->push_back(
                    &(*mapTexture)[static_cast<std::string>(file.cFileName)]);
                (*mapTexturePath)[static_cast<std::string>(file.cFileName)] =
                    tmp;
            }

            if ((file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0)
            {
                directories.push_back(tmp);
            }
        } while (TRUE == FindNextFile(searchHandle, &file));
        if (TRUE == ::FindClose(searchHandle))
        {
            const auto end = directories.end();
            for (auto iter = directories.begin(); iter != end; ++iter)
            {
                loadTextureEmptyR(*iter, mapTexture, mapTextureRect,
                                  mapTextureLoaded, mapTexturePath,
                                  vectorIdTexture, vectorPointerTexture,
                                  nbTextureTotal);
            }
        }
    }
#elif _OSX

#endif // __linux__
}

void OsManager::loadOneTexture(
    const std::string &dir,
    const std::shared_ptr<std::map<std::string, sf::Texture, std::less<>>>
        &mapTexture,
    std::vector<std::string> *const vectorIdTexture,
    uint32_t *const nbTextureCurrent, const std::string &name)
{
#ifdef __linux__
    struct dirent *read;
    DIR *rep;
    rep = opendir(dir.c_str());
    if (rep == nullptr)
    {
        std::perror(dir.c_str());
        return;
    }
    while ((read = readdir(rep)) != nullptr)
    {
        if (read->d_type == DT_DIR)
        {
            if ('.' != read->d_name[0])
            {
                loadOneTexture(dir + Slash + read->d_name, mapTexture,
                               vectorIdTexture, nbTextureCurrent, name);
            }
        }
        else
        {
            if (static_cast<std::string>(
                    &read->d_name[std::strlen(read->d_name) -
                                  imgExtension.size()]) == imgExtension &&
                name + imgExtension == read->d_name)
            {
                std::size_t i;
                for (i = 0ul; i < bigTexture.size(); i++)
                {
                    if (bigTexture[i] ==
                        static_cast<std::string>(read->d_name)
                            .substr(0, std::strlen(read->d_name) -
                                           imgExtension.size()))
                    {
                        break;
                    }
                }
                if (i < bigTexture.size())
                {
                    for (std::size_t j = 0ul; j < rectBigTexture[i].size(); j++)
                    {
                        (*mapTexture)[static_cast<std::string>(read->d_name)
                                          .substr(0, std::strlen(read->d_name) -
                                                         imgExtension.size()) +
                                      std::to_string(j) + imgExtension] =
                            loadTexture(dir + Slash + read->d_name,
                                        scaleri(rectBigTexture[i][j]));
                        vectorIdTexture->push_back(
                            static_cast<std::string>(read->d_name)
                                .substr(0, std::strlen(read->d_name) -
                                               imgExtension.size()) +
                            std::to_string(j) + imgExtension);
                        (*nbTextureCurrent)++;
                    }
                }
                else
                {
                    (*mapTexture)[read->d_name] =
                        loadTexture(dir + Slash + read->d_name);
                    vectorIdTexture->push_back(read->d_name);
                    (*nbTextureCurrent)++;
                }
            }
        }
    }
    closedir(rep);
#elif _WIN32
    std::string tmp = dir + Slash + "*";
    WIN32_FIND_DATA file;
    const HANDLE searchHandle = FindFirstFile(tmp.c_str(), &file);
    if (searchHandle != INVALID_HANDLE_VALUE)
    {
        std::vector<std::string> directories;
        do
        {
            if (((file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0) &&
                ((0 == lstrcmp(file.cFileName, ".")) ||
                 (0 == lstrcmp(file.cFileName, ".."))))
            {
                continue;
            }
            tmp = dir + Slash + static_cast<std::string>(file.cFileName);
            if ((tmp.size() > 3) &&
                (tmp.substr(tmp.size() - ImgExtension.size(),
                            ImgExtension.size()) == ImgExtension) &&
                ((name + ImgExtension) ==
                 static_cast<std::string>(file.cFileName)))
            {
                (*mapTexture)[static_cast<std::string>(file.cFileName)] =
                    Func::loadTexture(tmp);
                vectorIdTexture->push_back(
                    static_cast<std::string>(file.cFileName));
                ++(*nbTextureCurrent);
            }
            if (0 != (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                directories.push_back(tmp);
            }
        } while (TRUE == FindNextFile(searchHandle, &file));
        if (TRUE == ::FindClose(searchHandle))
        {
            const auto end = directories.end();
            for (auto iter = directories.begin(); iter != end; ++iter)
            {
                loadOneTexture(*iter, mapTexture, vectorIdTexture,
                               nbTextureCurrent, name);
            }
        }
    }
#elif _OSX

#endif // __linux__
}

void OsManager::loadOneTextureEmpty(
    const std::string &dir,
    std::map<std::string, sf::Texture, std::less<>> *const mapTexture,
    std::map<std::string, sf::Rect<int32_t>, std::less<>> *const mapTextureRect,
    std::map<std::string, bool, std::less<>> *const mapTextureLoaded,
    std::map<std::string, std::string, std::less<>> *const mapTexturePath,
    std::vector<std::string> *const vectorIdTexture,
    std::vector<sf::Texture *> *const vectorPointerTexture,
    uint32_t *const nbTextureTotal, const std::string &name)
{
#ifdef __linux__
    struct dirent *read;
    DIR *rep;
    rep = opendir(dir.c_str());
    if (rep == nullptr)
    {
        std::perror(dir.c_str());
        return;
    }
    while ((read = readdir(rep)) != nullptr)
    {
        if (read->d_type == DT_DIR)
        {
            // if (std::strcmp(read->d_name, ".")!=0 &&
            // std::strcmp(read->d_name, "..")!=0)
            if ('.' != read->d_name[0])
            {
                loadOneTextureEmpty(dir + Slash + read->d_name, mapTexture,
                                    mapTextureRect, mapTextureLoaded,
                                    mapTexturePath, vectorIdTexture,
                                    vectorPointerTexture, nbTextureTotal, name);
            }
        }
        else
        {
            if (static_cast<std::string>(
                    &read->d_name[std::strlen(read->d_name) -
                                  imgExtension.size()]) == imgExtension &&
                name + imgExtension == read->d_name)
            {
                std::size_t i;
                for (i = 0ul; i < bigTexture.size(); i++)
                {
                    if (bigTexture[i] ==
                        static_cast<std::string>(read->d_name)
                            .substr(0, std::strlen(read->d_name) -
                                           imgExtension.size()))
                    {
                        break;
                    }
                }
                if (i < bigTexture.size())
                {
                    for (std::size_t j = 0ul; j < rectBigTexture[i].size(); j++)
                    {
                        (*mapTexture)[static_cast<std::string>(read->d_name)
                                          .substr(0, std::strlen(read->d_name) -
                                                         imgExtension.size()) +
                                      std::to_string(j) + imgExtension] =
                            sf::Texture();
                        (*mapTextureRect)[static_cast<std::string>(read->d_name)
                                              .substr(
                                                  0, std::strlen(read->d_name) -
                                                         imgExtension.size()) +
                                          std::to_string(j) + imgExtension] =
                            scaleri(rectBigTexture[i][j]);
                        (*mapTextureLoaded)
                            [static_cast<std::string>(read->d_name)
                                 .substr(0, std::strlen(read->d_name) -
                                                imgExtension.size()) +
                             std::to_string(j) + imgExtension] = false;
                        vectorIdTexture->push_back(
                            static_cast<std::string>(read->d_name)
                                .substr(0, std::strlen(read->d_name) -
                                               imgExtension.size()) +
                            std::to_string(j) + imgExtension);
                        vectorPointerTexture->push_back(&(
                            *mapTexture)[static_cast<std::string>(read->d_name)
                                             .substr(0,
                                                     std::strlen(read->d_name) -
                                                         imgExtension.size()) +
                                         std::to_string(j) + imgExtension]);
                    }
                }
                else
                {
                    (*mapTexture)[read->d_name] = sf::Texture();
                    sf::Vector2<unsigned int> newRect =
                        getSizePng(dir + Slash + read->d_name);
                    (*mapTextureRect)[read->d_name] =
                        sf::Rect<int>(0, 0, static_cast<int>(newRect.x),
                                      static_cast<int>(newRect.y));
                    (*mapTextureLoaded)[read->d_name] = false;
                    vectorIdTexture->push_back(read->d_name);
                    vectorPointerTexture->push_back(
                        &(*mapTexture)[read->d_name]);
                }
                (*mapTexturePath)[read->d_name] = dir + Slash + read->d_name;
            }
        }
    }
    closedir(rep);
#elif _WIN32
    std::string tmp = dir + Slash + "*";
    WIN32_FIND_DATA file;
    const HANDLE searchHandle = FindFirstFile(tmp.c_str(), &file);
    if (searchHandle != INVALID_HANDLE_VALUE)
    {
        std::vector<std::string> directories;
        do
        {
            if (((file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0) &&
                ((0 == lstrcmp(file.cFileName, ".")) ||
                 (0 == lstrcmp(file.cFileName, ".."))))
            {
                continue;
            }
            tmp = dir + Slash + static_cast<std::string>(file.cFileName);
            if ((tmp.size() > 3) &&
                (tmp.substr(tmp.size() - ImgExtension.size(),
                            ImgExtension.size()) == ImgExtension) &&
                ((name + ImgExtension) ==
                 static_cast<std::string>(file.cFileName)))
            {
                (*mapTexture)[static_cast<std::string>(file.cFileName)] =
                    sf::Texture();
                const sf::Vector2<uint32_t> newRect = getSizePng(tmp);
                (*mapTextureRect)[static_cast<std::string>(file.cFileName)] =
                    sf::Rect<int32_t>(0, 0, static_cast<int32_t>(newRect.x),
                                      static_cast<int32_t>(newRect.y));
                (*mapTextureLoaded)[static_cast<std::string>(file.cFileName)] =
                    false;
                vectorIdTexture->push_back(
                    static_cast<std::string>(file.cFileName));
                vectorPointerTexture->push_back(
                    &(*mapTexture)[static_cast<std::string>(file.cFileName)]);
                (*mapTexturePath)[static_cast<std::string>(file.cFileName)] =
                    tmp;
            }
            if ((file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0)
            {
                directories.push_back(tmp);
            }
        } while (TRUE == FindNextFile(searchHandle, &file));
        if (TRUE == ::FindClose(searchHandle))
        {
            const auto end = directories.end();
            for (auto iter = directories.begin(); iter != end; ++iter)
            {
                loadOneTextureEmpty(*iter, mapTexture, mapTextureRect,
                                    mapTextureLoaded, mapTexturePath,
                                    vectorIdTexture, vectorPointerTexture,
                                    nbTextureTotal, name);
            }
        }
    }
#elif _OSX

#endif // __linux__
}

} // namespace segment_d1
