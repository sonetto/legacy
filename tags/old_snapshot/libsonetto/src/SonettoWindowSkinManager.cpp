/*-----------------------------------------------------------------------------
This source file is part of Sonetto RPG Engine.

Copyright (C) 2007,2008 Arthur Carvalho de Souza Lima, Guilherme Pr� Vieira


Sonetto RPG Engine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Sonetto RPG Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA or go to
http://www.gnu.org/copyleft/lesser.txt
-----------------------------------------------------------------------------*/
#include "SonettoWindowSkinManager.h"
#include <OgreSingleton.h>

namespace Sonetto {
    //-----------------------------------------------------------------------------
    // Sonetto::WindowSkinManager implementation
    //-----------------------------------------------------------------------------
    template<> WindowSkinManager *Ogre::Singleton<WindowSkinManager>::ms_Singleton = 0;
    //-----------------------------------------------------------------------------
    WindowSkinManager * WindowSkinManager::getSingletonPtr()
    {
        return ms_Singleton;
    }
    //-----------------------------------------------------------------------------
    WindowSkinManager & WindowSkinManager::getSingleton()
    {
        assert(ms_Singleton);
        return(*ms_Singleton);
    }
    //-----------------------------------------------------------------------------
    WindowSkinManager::WindowSkinManager()
    {
        mResourceType = "WindowSkin";

        // low, because it will likely reference other resources
        mLoadOrder = 30.0f;

        // this is how we register the ResourceManager with OGRE
        Ogre::ResourceGroupManager::getSingleton()._registerResourceManager(mResourceType, this);
    }
    //-----------------------------------------------------------------------------
    WindowSkinManager::~WindowSkinManager()
    {
        // and this is how we unregister it
        Ogre::ResourceGroupManager::getSingleton()._unregisterResourceManager(mResourceType);
    }
    //-----------------------------------------------------------------------------
    WindowSkinPtr WindowSkinManager::load(const Ogre::String &name, const Ogre::String &group)
    {
        WindowSkinPtr  windowskinf = getByName(name);

        if (windowskinf.isNull())
            windowskinf = create(name, group);

        windowskinf->load();
        return windowskinf;
    }
    //-----------------------------------------------------------------------------
    Ogre::Resource * WindowSkinManager::createImpl(const Ogre::String &name, Ogre::ResourceHandle handle,
            const Ogre::String &group, bool isManual, Ogre::ManualResourceLoader *loader,
            const Ogre::NameValuePairList *createParams)
    {
        return new WindowSkin(this, name, handle, group, isManual, loader);
    }
    //-----------------------------------------------------------------------------
}; // namespace
