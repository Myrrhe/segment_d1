/*
 * The engine of the watch.
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

#include "ShaderManager.hpp"
#include "Func.hpp"
#include "Logger.hpp"
#include "OsManager.hpp"
#include "PathManager.hpp"
#include <filesystem>
#include <unordered_map>

namespace segment_d1
{

std::map<std::string, sf::Shader, std::less<>> ShaderManager::shaders;

void ShaderManager::initialize()
{
    std::unordered_map<std::string,
                       std::pair<std::filesystem::path, std::filesystem::path>>
        shaderFiles;

    for (const auto &entry : std::filesystem::directory_iterator(
             PathManager::getPath(PathManager::Dir::SHADER)))
    {
        if (entry.is_regular_file())
        {
            const std::filesystem::path filePath = entry.path();
            const std::string fileName = entry.path().stem().string();
            const std::string extension = entry.path().extension().string();

            // Ajouter le fichier au bon emplacement (vertex ou fragment)
            if (extension == ".vert")
            {
                shaderFiles[fileName].first = filePath;
            }
            else if (extension == ".frag")
            {
                shaderFiles[fileName].second = filePath;
            }
            else
            {
                // Nothing to do
            }
        }
    }

    for (const auto &[name, paths] : shaderFiles)
    {
        const auto &vertexPath = paths.first;
        const auto &fragmentPath = paths.second;

        if ((!vertexPath.empty()) && (!fragmentPath.empty()))
        {
            if (!shaders[name].loadFromFile(vertexPath, fragmentPath))
            {
                Logger().info("Failed to load combined shader: " + name);
            }
        }
        else if (!vertexPath.empty())
        {
            if (!shaders[name].loadFromFile(vertexPath,
                                            sf::Shader::Type::Vertex))
            {
                Logger().info("Failed to load vertex shader: " + name);
            }
        }
        else if (!fragmentPath.empty())
        {
            if (!shaders[name].loadFromFile(fragmentPath,
                                            sf::Shader::Type::Fragment))
            {
                Logger().info("Failed to load fragment shader: " + name);
            }
        }
        else
        {
            // Nothing to do
        }
    }
}

void ShaderManager::terminate()
{
    // Nothing to do
}

sf::Shader &ShaderManager::getShader(const std::string &key)
{
    return shaders[key];
}

} // namespace segment_d1
