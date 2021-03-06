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
#ifndef SONETTOFONT_H_INCLUDED
#define SONETTOFONT_H_INCLUDED

#include "SonettoMain.h"

#include <OgreResourceManager.h>
#include <OgreMaterialManager.h>
#include <OgreTextureManager.h>
#include <OgreTechnique.h>
#include "SonettoMain.h"

namespace Sonetto {
    /** @brief This is a class that stores the texture font data.
    *
    * This class is used to set up a Font Texture for use with Sonetto::SonettoTextElement.
    */
    class SONETTO_EXPORT Font : public Ogre::Resource
    {
    public:
        /// @brief Number of glyphs per line and number of lines.
        GlyphTable glyph_tbl;
        /// @brief Default Vertical Space for each new line.
        float default_y_space;
        /// @brief Number of Glyphs.
        Ogre::uint32 num_glyphs;
        /// @brief Offset value for Glyph Mapping.
        Ogre::Vector2 glyph_coord_offset;
        /// @brief Name of the current texture used on this font. (deprecated?)
        Ogre::String font_texture_name;

        Ogre::uint16 font_blend_mode;

        Ogre::uint16 font_alpha_reject_settings;

        Ogre::uint16 alpha_rejection;

        Ogre::uint16 font_filtering_mode;

        /// @brief Glyph structure List.
        std::vector<Glyphstruct > glyphs;
        /// @brief Glyph structure List Iterator.
        std::vector<Glyphstruct >::iterator glyph_itr;
        /// @brief Color List.
        std::vector<Ogre::ColourValue> mColorList;
        /// @brief Color List Iterator.
        std::vector<Ogre::ColourValue>::iterator mColorList_itr;

        /// @brief Pointer to the material for this font.
        Ogre::MaterialPtr font_material;
        /// @brief Pointer to the font material's texture.
        Ogre::TexturePtr font_texture;

        /// @brief If the font material exist or not.
        bool materialExist;


    protected:

        // must implement these from the Ogre::Resource interface
        void loadImpl();
        void unloadImpl();
        size_t calculateSize() const;

    public:
        /// @brief Constructor.
        Font(Ogre::ResourceManager *creator, const Ogre::String &name,
                    Ogre::ResourceHandle handle, const Ogre::String &group, bool isManual = false,
                    Ogre::ManualResourceLoader *loader = 0);
        /// @brief Destructor.
        virtual ~Font();

        // Manual Custom Font file creation methods
        /** @brief Set up the font
        *
        * This function initialise the font.
        * @param x is the number of horizontal glyphs in the texture.
        * @param y is the number of vertical glyphs in the texture.
        * @param default_space is the default vertical space between the letters.
        * @param name is the texture name for this font.
        */
        void setUpFont(unsigned long x, unsigned long y, float default_space, const Ogre::String &name);
        /// @brief Calculate the Glyph coords for a new font texture.
        void calculateGlyphCoords();
        /** @brief Set the horizontal space for a specifig glyph.
        *
        * @param glyph is the Glyph ID.
        * @param spcWidth is the horizontal space for this glyph.
        */
        void setSpaceWidth(size_t glyph, float spcWidth)
        {
            glyphs[glyph].x_offset = spcWidth;
        }

        /** @brief Create the font material.
        *
        * @return Whether the material was sucessfully created.
        */
        bool createMaterial();
        /** @brief Destroy/Delete font material from memory.
        *
        * @return Whether the material was sucessfully deleted.
        */
        bool deleteMaterial();     // Destroy/Delete font material from memory

        /// @brief Set the font texture name
        void setTextureName(const Ogre::String &name_a);

        /// @brief Get the font texture name.
        const Ogre::String & getTextureName();

    };

    class SONETTO_EXPORT FontPtr : public Ogre::SharedPtr<Font>
    {
    public:
        FontPtr() : Ogre::SharedPtr<Font>() {}
        explicit FontPtr(Font *rep) : Ogre::SharedPtr<Font>(rep) {}
        FontPtr(const FontPtr &r) : Ogre::SharedPtr<Font>(r) {}
        FontPtr(const Ogre::ResourcePtr &r) : Ogre::SharedPtr<Font>()
        {
            // lock & copy other mutex pointer
            OGRE_LOCK_MUTEX(*r.OGRE_AUTO_MUTEX_NAME)
            OGRE_COPY_AUTO_SHARED_MUTEX(r.OGRE_AUTO_MUTEX_NAME)
            pRep = static_cast<Font*>(r.getPointer());
            pUseCount = r.useCountPointer();
            if (pUseCount)
            {
                ++(*pUseCount);
            }
        }

        /// @brief Operator used to convert a ResourcePtr to a FontPtr
        FontPtr& operator=(const Ogre::ResourcePtr& r)
        {
            if (pRep == static_cast<Font*>(r.getPointer()))
                return *this;
            release();
            // lock & copy other mutex pointer
            OGRE_LOCK_MUTEX(*r.OGRE_AUTO_MUTEX_NAME)
            OGRE_COPY_AUTO_SHARED_MUTEX(r.OGRE_AUTO_MUTEX_NAME)
            pRep = static_cast<Font*>(r.getPointer());
            pUseCount = r.useCountPointer();
            if (pUseCount)
            {
                ++(*pUseCount);
            }
            return *this;
        }
    };

} // namespace
#endif // SONETTOFONT_H_INCLUDED
