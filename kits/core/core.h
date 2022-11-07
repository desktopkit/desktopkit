/*
#
# DesktopKit
# <https://desktopkit.org>
# <https://github.com/desktopkit>
#
# Copyright (c) 2022, Ole-André Rodlie <https://github.com/rodlie>
# All rights reserved.
#
# DesktopKit is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# DesktopKit is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#
*/

#ifndef DK_CORE_H
#define DK_CORE_H

#include <string>
#include <vector>

namespace DesktopKit
{
    namespace Core
    {
        class Common
        {
        public:
            static const std::string getEnv(const std::string &key);
            static bool setEnv(const std::string &key,
                               const std::string &value);
        };
        class BaseDir
        {
        public:
            static const std::vector<std::string> getApplicationsPaths();
            static const std::string getCachePath();
            static const std::string getConfigPath();
            static const std::vector<std::string> getColorProfilesPaths();
            static const std::string getDataPath();
            static const std::vector<std::string> getDataPaths();
            static const std::string getDesktopPath();
            static const std::string getDocumentsPath();
            static const std::string getDownloadPath();
            static const std::vector<std::string> getFontsPaths();
            static const std::vector<std::string> getIconsPaths();
            static const std::vector<std::string> getMimeIconsPaths();
            static const std::vector<std::string> getMimeGenericIconsPaths();
            static const std::vector<std::string> getMimeGlobsPaths();
            static const std::vector<std::string> getMimeTypePaths();
            static const std::vector<std::string> getMimeAliasPaths();
            static const std::string getMusicPath();
            static const std::string getPicturesPath();
            static const std::vector<std::string> getPixmapsPaths();
            static const std::string getTempPath();
            static const std::string getThumbnailsPath();
            static const std::string getTrashPath();
            static const std::string getVideosPath();
            static bool isAppDir(const std::string &filename);
        private:
            enum BaseDirPath {
                pathCache,
                pathConfig,
                pathData,
                pathDesktop,
                pathDocuments,
                pathDownload,
                pathMusic,
                pathPictures,
                pathTemp,
                pathVideos
            };
            static const std::string getPath( int type,
                                              const std::string &suffix = std::string(),
                                              const std::string &fallback = std::string() );
        };
        class Cache
        {
        public:
        };
        class Mime
        {
        public:
            struct IconItem {
                std::string key;
                std::string value;
            };
            static const std::string getType(const std::string &filename);
            static const std::vector<DesktopKit::Core::Mime::IconItem> getIcons();
            static const std::vector<DesktopKit::Core::Mime::IconItem> getGenericIcons();
            static const std::vector<DesktopKit::Core::Mime::IconItem> getGlobs();
        private:
            static const std::vector<DesktopKit::Core::Mime::IconItem> getMimeIconsFromFile( const std::string &filename,
                                                                                             const std::string &splitter = std::string(":") );
            static bool containsIconItem(const std::vector<DesktopKit::Core::Mime::IconItem> &items,
                                         const std::string &search,
                                         bool searchInKey = true);
        };
    }
}

#endif // DK_CORE_H
