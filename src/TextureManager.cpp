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

#include "TextureManager.hpp"
#include "Constants.hpp"
#include "Func.hpp"
#include "OsManager.hpp"
#include <cstring>
#include <dirent.h>

#define ALL_TEXTURE_SMOOTH false
#define DEBUG_TEXTURE_LOAD false

namespace segment_d1
{

uint64_t TextureManager::stateTexture;

uint32_t TextureManager::nbTextureTotal;
uint32_t TextureManager::nbTextureCurrent;
uint32_t TextureManager::nbTextureToLoad;
std::vector<std::string> TextureManager::vectorIdTexture;
std::vector<sf::Texture *> TextureManager::vectorPointerTexture;
std::shared_ptr<std::map<std::string, sf::Texture, std::less<>>>
    TextureManager::mapTexture;
std::map<std::string, sf::Rect<int32_t>, std::less<>>
    TextureManager::mapTextureRect;
std::map<std::string, bool, std::less<>> TextureManager::mapTextureLoaded;
std::map<std::string, std::string, std::less<>> TextureManager::mapTexturePath;
std::vector<std::string> TextureManager::textureToLoad;
std::vector<uint8_t> TextureManager::textureLoadUnload;
std::string TextureManager::strFileLoad;
bool TextureManager::isLoadDelete;
uint64_t TextureManager::nbPixelToLoad;
uint64_t TextureManager::nbPixelLoaded;
float64_t TextureManager::timeLoad;
float64_t TextureManager::timeDele;
uint64_t TextureManager::nbLoad;
uint64_t TextureManager::nbDele;
bool TextureManager::isLoading;

#if USE_SCALER
const std::string TextureManager::nameGraph = "graphics33";
#else
const std::string TextureManager::nameGraph = "graphics100";
#endif // USE_SCALER
const uint64_t TextureManager::nbTimeUnitLoad = 300;
const uint64_t TextureManager::nbTimeUnitDelete = 1;

void TextureManager::loadDir(const std::string &dir)
{
    OsManager::loadTextureR(dir, mapTexture, &vectorIdTexture,
                            &nbTextureCurrent);
}

void TextureManager::loadDirEmpty(const std::string &dir)
{
    OsManager::loadTextureEmptyR(
        dir, mapTexture, &mapTextureRect, &mapTextureLoaded, &mapTexturePath,
        &vectorIdTexture, &vectorPointerTexture, &nbTextureTotal);
}

void TextureManager::initialize()
{
    nbTextureCurrent = 0u;
    nbTextureToLoad = 0u;
    timeLoad = 0.0;
    timeDele = 0.0;
    nbLoad = 0;
    nbDele = 0;
    std::vector<std::string> vecDir{};
    const uint64_t nbDir = vecDir.size();

    for (uint64_t i = 0; i < nbDir; ++i)
    {
        loadDirEmpty(OsManager::getPath() + OsManager::Slash + nameGraph +
                     OsManager::Slash + vecDir[i]);
    }

#if ALL_TEXTURE_SMOOTH
    long unsigned int vecPoSize = vectorPointerTexture.size();
    for (long unsigned int i = 0ul; i < vecPoSize; i++)
    {
        vectorPointerTexture[i]->setSmooth(true);
    }
#endif // ALL_TEXTURE_SMOOTH
}

void TextureManager::initializeStateTexture()
{
    mapTexture =
        std::make_unique<std::map<std::string, sf::Texture, std::less<>>>();
    nbTextureTotal = 0u;
    loadDirEmpty(OsManager::getPath() + OsManager::Slash + nameGraph +
                 OsManager::Slash + "load");
    loadDirEmpty(OsManager::getPath() + OsManager::Slash + nameGraph +
                 OsManager::Slash + "icon");
    isLoading = false;
    stateTexture = 0;
    strFileLoad = "";
    isLoadDelete = false;
}

const sf::Texture &TextureManager::getTexture(const std::string &str)
{
    return (*mapTexture)[str + std::string(ImgExtension)];
}

const sf::Rect<int32_t> &TextureManager::getTextureRect(const std::string &str)
{
    return mapTextureRect[str + std::string(ImgExtension)];
}

const sf::Texture *TextureManager::getPointerTexture(const std::string &str)
{
    return &(*mapTexture)[str + std::string(ImgExtension)];
}

bool TextureManager::create(const std::string &str, const uint32_t width,
                            const uint32_t height)
{
    return (*mapTexture)[str + std::string(ImgExtension)].resize(
        sf::Vector2<uint32_t>(width, height));
}

sf::Texture &TextureManager::equalTexture(const std::string &str,
                                          const sf::Texture &newTexture)
{
    (*mapTexture)[str + std::string(ImgExtension)] = newTexture;
    return (*mapTexture)[str + std::string(ImgExtension)];
}

void TextureManager::setTexture(sf::Sprite &sprite, const std::string &str)
{
    sprite.setTexture((*mapTexture)[str + std::string(ImgExtension)], false);
}

void TextureManager::createTexture(const sf::Texture &texture,
                                   const std::string &key)
{
    const bool newTexture =
        mapTexture->find(key + std::string(ImgExtension)) == mapTexture->end();
    (*mapTexture)[key + std::string(ImgExtension)] = texture;
    if (newTexture)
    {
        vectorPointerTexture.push_back(
            &(*mapTexture)[key + std::string(ImgExtension)]);
        vectorIdTexture.push_back(key + std::string(ImgExtension));
        ++nbTextureTotal;
    }
}

void TextureManager::deleteAllTexture()
{
    for (uint32_t i = 0u; i < nbTextureTotal; ++i)
    {
        (*mapTexture)[vectorIdTexture[i]] = sf::Texture();
    }
}

void TextureManager::loadOneTexture(const std::string &name)
{
    OsManager::loadOneTexture(
        OsManager::getPath() + OsManager::Slash + nameGraph, mapTexture,
        &vectorIdTexture, &nbTextureCurrent, name);
}

void TextureManager::deleOneTexture(const std::string &name)
{
    (*mapTexture)[name + std::string(ImgExtension)] = sf::Texture();
    --nbTextureCurrent;
}

void TextureManager::manageOneTexture(const std::string &name, const bool load)
{
    textureToLoad.push_back(name);
    textureLoadUnload.push_back(load);
    ++nbTextureToLoad;
    if (load)
    {
        nbPixelToLoad += nbTimeUnitLoad;
    }
    else
    {
        nbPixelToLoad += nbTimeUnitDelete;
    }
}

bool TextureManager::loadUnloadOneTextureFile()
{
    bool res = false;
    if (textureToLoad.empty())
    {
        OsManager::getPhysicalMemoryUsedProcess();
        OsManager::getVirtualMemoryUsedProcess();
    }
    else
    {
        strFileLoad = textureToLoad[textureToLoad.size() - 1];
        isLoadDelete = textureLoadUnload[textureLoadUnload.size() - 1];
        if (0 != textureLoadUnload[textureLoadUnload.size() - 1])
        {
#if DEBUG && DEBUG_TEXTURE_LOAD
            double cIni = OsManager::get_cpu_time();
#endif // DEBUG && DEBUG_TEXTURE_LOAD
            loadOneTexture(textureToLoad[textureToLoad.size() - 1]);
            nbPixelLoaded += nbTimeUnitLoad;
#if DEBUG && DEBUG_TEXTURE_LOAD
            // double cFin = OsManager::get_cpu_time() - cIni;
            timeLoad += OsManager::get_cpu_time() - cIni;
            nbLoad++;
#endif // DEBUG && DEBUG_TEXTURE_LOAD
        }
        else
        {
#if DEBUG && DEBUG_TEXTURE_LOAD
            double cIni = OsManager::get_cpu_time();
#endif // DEBUG && DEBUG_TEXTURE_LOAD
            deleOneTexture(textureToLoad[textureToLoad.size() - 1]);
            nbPixelLoaded += nbTimeUnitDelete;
#if DEBUG && DEBUG_TEXTURE_LOAD
            timeDele += OsManager::get_cpu_time() - cIni;
            nbDele++;
#endif // DEBUG && DEBUG_TEXTURE_LOAD
        }
        textureToLoad.pop_back();
        textureLoadUnload.pop_back();
        --nbTextureToLoad;
        if (textureToLoad.empty())
        {
            OsManager::getPhysicalMemoryUsedProcess();
            OsManager::getVirtualMemoryUsedProcess();
        }
        else
        {
            res = true;
        }
    }
    return res;
}

void TextureManager::loadUnloadAllTextureFile()
{
    while (loadUnloadOneTextureFile())
    {
        // Nothing to do
    }
}

void TextureManager::manageTexture(const uint64_t newStateTexture)
{
    nbPixelToLoad = 0;
    nbPixelLoaded = 0;
    isLoading = true;
    for (uint32_t i = 0u; i < nbGroupTextureMax; ++i)
    {
        if (((newStateTexture >> i) & 1) != ((stateTexture >> i) & 1))
        {
            loadUnloadTexture(static_cast<TexGr>(i),
                              (newStateTexture >> i) & 1);
        }
    }
    stateTexture = newStateTexture;
    isLoading = false;
}

void TextureManager::manageTexture(const TexFl newStateTexture)
{
    manageTexture(static_cast<uint64_t>(newStateTexture));
}

void TextureManager::loadUnloadTexture(const TexGr texGr, const bool load)
{
    switch (texGr)
    {
    case TexGr::LOADING_G: {
        manageOneTexture("loadBack", load);
        manageOneTexture("particleLoad", load);
        manageOneTexture("loadBarBox", load);
        manageOneTexture("loadBar", load);
        manageOneTexture("iconL64", load);
        manageOneTexture("iconW128", load);
        break;
    }
    case TexGr::GEN_G: {

        break;
    }
    case TexGr::MENU_G: {
        manageOneTexture("menu", load);
        manageOneTexture("circle", load);
        manageOneTexture("lineMenu", load);
        manageOneTexture("charFirst", load);
        for (uint64_t i = 0; i < 15; ++i)
        {
            manageOneTexture("flashFirst" + std::to_string(i), load);
        }
        manageOneTexture("cursor", load);
        for (uint64_t i = 0; i < 3; ++i)
        {
            manageOneTexture("cursor" + std::to_string(i + 1), load);
        }
        manageOneTexture("exampleSpellBorder", load);
        for (uint64_t i = 0; i < 39; ++i)
        {
            manageOneTexture("exampleSpell" + std::to_string(i), load);
        }
        manageOneTexture("achGlow", load);
        manageOneTexture("achNull", load);
        break;
    }
    case TexGr::STAGE_G: {
        manageOneTexture("armory", load);
        manageOneTexture("spiral", load);
        manageOneTexture("tableParticles0", load);
        manageOneTexture("tableParticles1", load);
        manageOneTexture("particleGraze", load);
        manageOneTexture("particleBossDamage", load);
        manageOneTexture("particleEnnemi", load);
        manageOneTexture("particleLossLife", load);
        manageOneTexture("particleWhite", load);
        manageOneTexture("bossIndicator", load);
        manageOneTexture("bombSym", load);
        manageOneTexture("lifeSym", load);
        manageOneTexture("hud", load);
        manageOneTexture("pause", load);
        manageOneTexture("dialog3", load);
        manageOneTexture("spellName", load);
        manageOneTexture("chapter", load);
        manageOneTexture("collectItem", load);
        manageOneTexture("back0", load);
        manageOneTexture("back00", load);
        for (uint64_t i = 0; i < 120; ++i)
        {
            manageOneTexture("player" + std::to_string(i), load);
        }
        for (uint64_t i = 0; i < 3; ++i)
        {
            manageOneTexture("hitbox" + std::to_string(i), load);
        }
        manageOneTexture("charBack0", load);
        manageOneTexture("gearBig", load);
        manageOneTexture("gearRack", load);
        manageOneTexture("gearPlanet", load);
        manageOneTexture("gearRing", load);
        manageOneTexture("gearSun", load);
        for (uint64_t i = 0; i < 120; ++i)
        {
            manageOneTexture("ennemi" + std::to_string(i), load);
        }
        manageOneTexture("areaDist", load);
        for (uint64_t i = 0; i < 3; ++i)
        {
            manageOneTexture("targetMouse" + std::to_string(i + 1), load);
        }
        manageOneTexture("lifeEater0", load);
        manageOneTexture("lifeEat00", load);
        manageOneTexture("lifeEat01", load);
        manageOneTexture("lifeEat10", load);
        manageOneTexture("lifeEat11", load);
        manageOneTexture("lifeEat20", load);
        manageOneTexture("lifeEat21", load);
        manageOneTexture("laser0_red", load);
        manageOneTexture("laser0_orange", load);
        manageOneTexture("laser0_yellow", load);
        manageOneTexture("laser0_green", load);
        manageOneTexture("laser0_blue", load);
        manageOneTexture("laser0_indigo", load);
        manageOneTexture("laser0_purple", load);
        manageOneTexture("laser0_black", load);
        manageOneTexture("laser0_white", load);
        manageOneTexture("laser1_red", load);
        manageOneTexture("laser1_orange", load);
        manageOneTexture("laser1_yellow", load);
        manageOneTexture("laser1_green", load);
        manageOneTexture("laser1_blue", load);
        manageOneTexture("laser1_indigo", load);
        manageOneTexture("laser1_purple", load);
        manageOneTexture("laser1_black", load);
        manageOneTexture("laser1_white", load);
        manageOneTexture("laser2_red", load);
        manageOneTexture("laser2_orange", load);
        manageOneTexture("laser2_yellow", load);
        manageOneTexture("laser2_green", load);
        manageOneTexture("laser2_blue", load);
        manageOneTexture("laser2_indigo", load);
        manageOneTexture("laser2_purple", load);
        manageOneTexture("laser2_black", load);
        manageOneTexture("laser2_white", load);
        manageOneTexture("laser3_red", load);
        manageOneTexture("laser3_orange", load);
        manageOneTexture("laser3_yellow", load);
        manageOneTexture("laser3_green", load);
        manageOneTexture("laser3_blue", load);
        manageOneTexture("laser3_indigo", load);
        manageOneTexture("laser3_purple", load);
        manageOneTexture("laser3_black", load);
        manageOneTexture("laser3_white", load);
        manageOneTexture("chain", load);
        manageOneTexture("laserPlayer", load);
        manageOneTexture("shotPlayer", load);
        manageOneTexture("shotPlayerInverted", load);
        manageOneTexture("fill0_red", load);
        manageOneTexture("fill0_orange", load);
        manageOneTexture("fill0_yellow", load);
        manageOneTexture("fill0_green", load);
        manageOneTexture("fill0_blue", load);
        manageOneTexture("fill0_indigo", load);
        manageOneTexture("fill0_purple", load);
        manageOneTexture("fill0_black", load);
        manageOneTexture("fill0_white", load);
        break;
    }
    case TexGr::STAGEMENU_G: {
        for (uint64_t i = 0; i < 20; ++i)
        {
            manageOneTexture("ach" + std::to_string(i + 1), load);
        }
        manageOneTexture("sealEasy", load);
        manageOneTexture("sealNormal", load);
        manageOneTexture("sealHard", load);
        manageOneTexture("sealDeadly", load);
        manageOneTexture("sealExtra", load);
        for (uint64_t i = 0; i < 7; ++i)
        {
            for (uint64_t j = 0; j < 10; ++j)
            {
                manageOneTexture("boss" + std::to_string(i + 1) + "-" +
                                     std::to_string(j + 1),
                                 load);
            }
        }
        for (uint64_t i = 0; i < 10; ++i)
        {
            manageOneTexture("player" + static_cast<std::string>("-") +
                                 std::to_string(i + 1),
                             load);
        }
        manageOneTexture("bomb", load);
        manageOneTexture("bombEmpty", load);
        manageOneTexture("life", load);
        manageOneTexture("lifeEmpty", load);
        manageOneTexture("itemPointBig", load);
        manageOneTexture("itemPointSmall", load);
        manageOneTexture("itemPowerBig", load);
        manageOneTexture("itemPowerSmall", load);
        manageOneTexture("itemBombBig", load);
        manageOneTexture("itemBombSmall", load);
        manageOneTexture("itemLifeBig", load);
        manageOneTexture("itemLifeSmall", load);
        manageOneTexture("itemLifeSmallNegative", load);
        manageOneTexture("itemLifeBigNegative", load);
        manageOneTexture("fullPower", load);
        manageOneTexture("bonus", load);
        manageOneTexture("slideMusic", load);
        manageOneTexture("circleMusic", load);
        manageOneTexture("uiSeal", load);
        manageOneTexture("mainTitle5", load);
        manageOneTexture("secoTitle2", load);
        break;
    }
    case TexGr::BOSS1_G: {
        manageOneTexture("back1", load);
        manageOneTexture("back01", load);
        for (uint64_t i = 0; i < 120; ++i)
        {
            manageOneTexture("boss1_" + std::to_string(i), load);
        }
        manageOneTexture("charBack1", load);
        for (uint64_t i = 0; i < 2; ++i)
        {
            manageOneTexture("ringBoss0" + std::to_string(i), load);
        }
        break;
    }
    case TexGr::BOSS2_G: {
        manageOneTexture("back2", load);
        manageOneTexture("back02", load);
        for (uint64_t i = 0; i < 120; ++i)
        {
            manageOneTexture("boss2_" + std::to_string(i), load);
        }
        manageOneTexture("charBack2", load);
        for (uint64_t i = 0; i < 4; ++i)
        {
            manageOneTexture("ringBoss1" + std::to_string(i), load);
        }
        break;
    }
    case TexGr::BOSS3_G: {
        manageOneTexture("back3", load);
        manageOneTexture("back03", load);
        for (uint64_t i = 0; i < 120; ++i)
        {
            manageOneTexture("boss3_" + std::to_string(i), load);
        }
        manageOneTexture("charBack3", load);
        for (uint64_t i = 0; i < 3; ++i)
        {
            manageOneTexture("ringBoss2" + std::to_string(i), load);
        }
        break;
    }
    case TexGr::BOSS4_G: {
        manageOneTexture("back4", load);
        manageOneTexture("back04", load);
        for (uint64_t i = 0; i < 120; ++i)
        {
            manageOneTexture("boss4_" + std::to_string(i), load);
        }
        manageOneTexture("charBack4", load);
        for (uint64_t i = 0; i < 2; ++i)
        {
            manageOneTexture("ringBoss3" + std::to_string(i), load);
        }
        break;
    }
    case TexGr::BOSS5_G: {
        manageOneTexture("back5", load);
        manageOneTexture("back05", load);
        for (uint64_t i = 0; i < 120; ++i)
        {
            manageOneTexture("boss5_" + std::to_string(i), load);
        }
        manageOneTexture("charBack5", load);
        for (uint64_t i = 0; i < 2; ++i)
        {
            manageOneTexture("ringBoss4" + std::to_string(i), load);
        }
        break;
    }
    case TexGr::BOSS6_G: {
        manageOneTexture("back6", load);
        manageOneTexture("back06", load);
        for (uint64_t i = 0; i < 120; ++i)
        {
            manageOneTexture("boss6_" + std::to_string(i), load);
        }
        manageOneTexture("charBack6", load);
        for (uint64_t i = 0; i < 6; ++i)
        {
            manageOneTexture("ringBoss5" + std::to_string(i), load);
        }
        break;
    }
    case TexGr::BOSS7_G: {
        manageOneTexture("back7", load);
        manageOneTexture("back07", load);
        for (uint64_t i = 0; i < 120; ++i)
        {
            manageOneTexture("boss7_" + std::to_string(i), load);
        }
        manageOneTexture("charBack7", load);
        for (uint64_t i = 0; i < 3; ++i)
        {
            manageOneTexture("ringBoss6" + std::to_string(i), load);
        }
        break;
    }
    case TexGr::CREDIT_G: {
        manageOneTexture("rectCredit", load);
        manageOneTexture("audacity", load);
        manageOneTexture("gimp", load);
        manageOneTexture("inkscape", load);
        manageOneTexture("lmms", load);
        manageOneTexture("sfml", load);
        manageOneTexture("sublimeText", load);
        manageOneTexture("circleBack04", load);
        manageOneTexture("circleBack05", load);
        manageOneTexture("circleBack14", load);
        manageOneTexture("circleBack15", load);
        manageOneTexture("circleBack23", load);
        manageOneTexture("circleBack24", load);
        manageOneTexture("circleBack25", load);
        manageOneTexture("circleBack30", load);
        manageOneTexture("circleBack31", load);
        manageOneTexture("circleBack32", load);
        manageOneTexture("circleBack33", load);
        manageOneTexture("circleBack34", load);
        manageOneTexture("circleBack35", load);
        manageOneTexture("circleBack40", load);
        manageOneTexture("circleBack41", load);
        manageOneTexture("circleBack42", load);
        manageOneTexture("circleBack43", load);
        manageOneTexture("circleBack44", load);
        manageOneTexture("circleBack45", load);
        manageOneTexture("circleBack50", load);
        manageOneTexture("circleBack51", load);
        manageOneTexture("circleBack52", load);
        manageOneTexture("circleBack53", load);
        manageOneTexture("circleBack54", load);
        manageOneTexture("creditBack04", load);
        manageOneTexture("creditBack05", load);
        manageOneTexture("creditBack14", load);
        manageOneTexture("creditBack15", load);
        manageOneTexture("creditBack23", load);
        manageOneTexture("creditBack24", load);
        manageOneTexture("creditBack25", load);
        manageOneTexture("creditBack30", load);
        manageOneTexture("creditBack31", load);
        manageOneTexture("creditBack32", load);
        manageOneTexture("creditBack33", load);
        manageOneTexture("creditBack34", load);
        manageOneTexture("creditBack35", load);
        manageOneTexture("creditBack40", load);
        manageOneTexture("creditBack41", load);
        manageOneTexture("creditBack42", load);
        manageOneTexture("creditBack43", load);
        manageOneTexture("creditBack44", load);
        manageOneTexture("creditBack45", load);
        manageOneTexture("creditBack50", load);
        manageOneTexture("creditBack51", load);
        manageOneTexture("creditBack52", load);
        manageOneTexture("creditBack53", load);
        manageOneTexture("creditBack54", load);
        break;
    }
    case TexGr::ENDING_G: {
        for (uint64_t i = 0; i < 4; ++i)
        {
            manageOneTexture("ed" + std::to_string(i), load);
        }
        break;
    }
    default: {
        DEBUG_LOG("default reached");
        break;
    }
    }
}

uint64_t TextureManager::getNbPixelToLoad() { return nbPixelToLoad; }

uint64_t TextureManager::getNbPixelLoaded() { return nbPixelLoaded; }

uint64_t TextureManager::getStateTexture() { return stateTexture; }

void TextureManager::setLoadTrue() { isLoading = true; }

uint32_t TextureManager::getNbTextureTotal() { return nbTextureTotal; }

void TextureManager::getRamTexture()
{
    // Nothing to do
}

const std::string &TextureManager::getStrFileLoad() { return strFileLoad; }

const std::string &TextureManager::getFileTexturePath(const std::string &str)
{
    return mapTexturePath[str];
}

bool TextureManager::getIsLoadDelete() { return isLoadDelete; }

uint64_t operator|(const TextureManager::TexFl &texFl1,
                   const TextureManager::TexFl &texFl2)
{
    return static_cast<uint64_t>(texFl1) | static_cast<uint64_t>(texFl2);
}

uint64_t operator|(const uint64_t texFl1, const TextureManager::TexFl &texFl2)
{
    return texFl1 | static_cast<uint64_t>(texFl2);
}

void TextureManager::deleteAll()
{
    mapTextureRect.clear();
    mapTextureLoaded.clear();
    mapTexturePath.clear();
    vectorIdTexture.clear();
    textureToLoad.clear();
    textureLoadUnload.clear();
#if DEBUG
    std::cout << "Mean load = " << timeLoad / static_cast<double>(nbLoad)
              << std::endl;
    std::cout << "Mean dele = " << timeDele / static_cast<double>(nbDele)
              << std::endl;
#endif // DEBUG
}

} // namespace segment_d1
