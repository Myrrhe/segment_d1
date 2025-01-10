/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2017  <copyright holder> <email>
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

#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP
#include "StaticObject.hpp"
#include "Types.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

namespace segment_d1
{

class TextureManager final : public StaticObject
{
public:
    enum class IdTex : uint64_t
    {
        LOAD_BACK,
        NB_TEXTURE
    };

    enum class TexGr : uint32_t
    {
        LOADING_G,
        GEN_G,
        MENU_G,
        STAGE_G,
        STAGEMENU_G,
        BOSS1_G,
        BOSS2_G,
        BOSS3_G,
        BOSS4_G,
        BOSS5_G,
        BOSS6_G,
        BOSS7_G,
        CREDIT_G,
        ENDING_G
    };

    enum class TexFl : uint64_t
    {
        LOADING = 1,
        GEN = 1 << 1,
        MENU = 1 << 2,
        STAGE = 1 << 3,
        STAGEMENU = 1 << 4,
        BOSS1 = 1 << 5,
        BOSS2 = 1 << 6,
        BOSS3 = 1 << 7,
        BOSS4 = 1 << 8,
        BOSS5 = 1 << 9,
        BOSS6 = 1 << 10,
        BOSS7 = 1 << 11,
        CREDIT = 1 << 12,
        ENDING = 1 << 13
    };

    static void initialize();
    static void initializeStateTexture();
    static void setLoadTrue();
    static const sf::Texture &getTexture(const std::string &str);
    static const sf::Rect<int32_t> &getTextureRect(const std::string &str);
    static const sf::Texture *getPointerTexture(const std::string &str);
    static bool create(const std::string &str, const uint32_t width,
                       const uint32_t height);
    static sf::Texture &equalTexture(const std::string &str,
                                     const sf::Texture &newTexture);
    static void setTexture(sf::Sprite &sprite, const std::string &str);
    static void createTexture(const sf::Texture &texture,
                              const std::string &key);
    static void deleteAllTexture();
    static void loadOneTexture(const std::string &name);
    static void deleOneTexture(const std::string &name);
    static void getRamTexture();

    [[nodiscard]] static const std::string &getStrFileLoad();
    static const std::string &getFileTexturePath(const std::string &str);
    [[nodiscard]] static bool getIsLoadDelete();

    static bool loadUnloadOneTextureFile();
    static void loadUnloadAllTextureFile();
    static void manageOneTexture(const std::string &name, const bool load);
    static void manageTexture(const uint64_t newStateTexture);
    static void manageTexture(const TexFl newStateTexture);
    static void loadUnloadTexture(const TexGr texGr, const bool load);
    [[nodiscard]] static uint64_t getNbPixelToLoad();
    [[nodiscard]] static uint64_t getNbPixelLoaded();
    [[nodiscard]] static uint64_t getStateTexture();
    [[nodiscard]] static uint32_t getNbTextureTotal();
    static void deleteAll();

    static constexpr uint32_t nbGroupTextureMax = 14u;

    static const std::string nameGraph;

    static const uint64_t nbTimeUnitLoad;
    static const uint64_t nbTimeUnitDelete;

private:
    static void loadDir(const std::string &dir);
    static void loadDirEmpty(const std::string &dir);

    static uint64_t stateTexture;

    static uint32_t nbTextureTotal;
    static uint32_t nbTextureCurrent;
    static uint32_t nbTextureToLoad;
    static std::vector<std::string> vectorIdTexture;
    static std::vector<sf::Texture *> vectorPointerTexture;
    static std::shared_ptr<std::map<std::string, sf::Texture, std::less<>>>
        mapTexture;
    static std::map<std::string, sf::Rect<int32_t>, std::less<>> mapTextureRect;
    static std::map<std::string, bool, std::less<>> mapTextureLoaded;
    static std::map<std::string, std::string, std::less<>> mapTexturePath;
    static std::vector<std::string> textureToLoad;
    static std::vector<uint8_t> textureLoadUnload;
    static std::string strFileLoad;
    static bool isLoadDelete;
    static uint64_t nbPixelToLoad;
    static uint64_t nbPixelLoaded;
    static float64_t timeLoad;
    static float64_t timeDele;
    static uint64_t nbLoad;
    static uint64_t nbDele;
    static bool isLoading;
};

uint64_t operator|(const TextureManager::TexFl &texFl1,
                   const TextureManager::TexFl &texFl2);
uint64_t operator|(const uint64_t texFl1, const TextureManager::TexFl &texFl2);

} // namespace segment_d1

#endif // TEXTUREMANAGER_HPP
