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
            static const std::vector<std::string> getMimeAppsInfoPaths();
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
            struct AppItem {
                std::string key;
                std::vector<std::string> apps;
            };
            struct MimeItem {
                std::string type;
                std::string icon;
                std::vector<std::string> alias;
                std::vector<std::string> apps;
                std::vector<std::string> files;
            };
            /*struct LangItem {
                std::string lang;
                std::string value;
            };*/
            struct DesktopItem {
                std::string entry;
                std::string name;
                //std::vector<DesktopKit::Core::Mime::LangItem> names;
                std::string generic;
                //std::vector<DesktopKit::Core::Mime::LangItem> generics;
                std::string comment;
                //std::vector<DesktopKit::Core::Mime::LangItem> comments;
                std::string exec;
                std::string icon;
                std::string type;
                bool terminal = false;
                bool display = true;
                std::vector<std::string> categories;
                std::vector<std::string> mimes;
                std::vector<std::string> actions;
                std::vector<std::string> keywords;
                std::vector<DesktopKit::Core::Mime::DesktopItem> actionItems;
                std::vector<std::string> onlyShowIn;
                bool startupNotify = false;
            };
            static const std::string getType(const std::string &filename);
            static const std::vector<DesktopKit::Core::Mime::MimeItem> getItems(bool incAlias = true,
                                                                                bool incGlobs = true,
                                                                                bool incApps = true);
            static const std::vector<DesktopKit::Core::Mime::IconItem> getIcons();
            static const std::vector<DesktopKit::Core::Mime::IconItem> getGenericIcons();
            static const std::vector<DesktopKit::Core::Mime::IconItem> getGlobs();
            static const std::vector<DesktopKit::Core::Mime::IconItem> getAlias();
            static const std::vector<DesktopKit::Core::Mime::AppItem> getAppsInfo();
            static const std::vector<std::string> getAppsForMime(const std::string &mime);
            static const std::string getIconForMime(const std::string &mime);
            static const std::vector<std::string> getApplications();
            static const std::vector<DesktopKit::Core::Mime::DesktopItem> getApplicationItems();
        private:
            static const std::vector<DesktopKit::Core::Mime::IconItem> getMimeIconsFromFile( const std::string &filename,
                                                                                             const std::string &splitter = std::string(":") );
            static bool containsInStrings(const std::vector<std::string> &items,
                                          const std::string &search);
            static bool containsIconItem(const std::vector<DesktopKit::Core::Mime::IconItem> &items,
                                         const std::string &search,
                                         bool searchInKey = true);
            static bool containsAppItem(const std::vector<DesktopKit::Core::Mime::AppItem> &items,
                                        const std::string &search);
            static bool containsMimeItem(const std::vector<DesktopKit::Core::Mime::MimeItem> &items,
                                         const std::string &search);
            static const std::string getValueFromIconItems(const std::vector<DesktopKit::Core::Mime::IconItem> &items,
                                                           const std::string &key);
            static const std::string getKeyFromIconItems(const std::vector<DesktopKit::Core::Mime::IconItem> &items,
                                                         const std::string &value);
            static const std::vector<DesktopKit::Core::Mime::MimeItem> findMimeItems(const std::vector<DesktopKit::Core::Mime::IconItem> &items,
                                                                                     bool incAlias = true,
                                                                                     bool incGlobs = true,
                                                                                     bool incApps = true);
        };
    }
}

#endif // DK_CORE_H
