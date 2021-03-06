/*-----------------------------------------------------------------------------
Copyright (c) 2009, Sonetto Project Developers
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1.  Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
2.  Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
3.  Neither the name of the Sonetto Project nor the names of its contributors
    may be used to endorse or promote products derived from this software
    without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
-----------------------------------------------------------------------------*/

#include "SonettoFont.h"
#include "SonettoFontSerializer.h"

namespace Sonetto
{
    uint32 Font::mFourCC = MKFOURCC('S','F','N','T');
    // ----------------------------------------------------------------------
    Font::Font( Ogre::ResourceManager *creator, const Ogre::String &name,
                Ogre::ResourceHandle handle, const Ogre::String &group, bool isManual,
                Ogre::ManualResourceLoader *loader) :
                Ogre::Resource(creator, name, handle, group, isManual, loader)
    {
        mFontImage = NULL;
    }
    // ----------------------------------------------------------------------
    Font::~Font()
    {
        unload();
    }
    // ----------------------------------------------------------------------
    void Font::loadImpl()
    {
        FontSerializer serializer;
        Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(mName, mGroup, true, this);
        serializer.importFont(stream, this);
    }
    // ----------------------------------------------------------------------
    void Font::unloadImpl()
    {
        mColorList.clear();
        mGlyph.clear();
        delete mFontImage;
    }
    // ----------------------------------------------------------------------
    size_t Font::calculateSize() const
    {
        return 0;
    }
    // ----------------------------------------------------------------------
} // namespace
