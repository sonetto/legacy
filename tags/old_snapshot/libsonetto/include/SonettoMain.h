/*-----------------------------------------------------------------------------
This source file is part of Sonetto RPG Engine.

Copyright (C) 2007,2008 Arthur Carvalho de Souza Lima, Guilherme Prá Vieira


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

#ifndef SONETTO_MAIN_H
#define SONETTO_MAIN_H

// If it's the client, then import the library from the dll, export otherwise.
#if defined( WIN32 )
#   if defined( SONETTO_DLL_BUILD )
#        define SONETTO_EXPORT __declspec( dllexport )
#   else
#       define SONETTO_EXPORT __declspec( dllimport )
#   endif
#else
#   define SONETTO_EXPORT
#endif

//#include <AL/al.h>
//#include <vorbis/vorbisfile.h>

#include <OgreVector2.h>
#include <OgreMaterial.h>

#include "SonettoException.h"

namespace Sonetto {
    enum ScreenMetricsMode {
        SMM_RELATIVE,
        SMM_RELATIVE_ASPECT_ADJUSTED
    };

    enum WindowType {
        WT_MENU,
        WT_MAIN,
        WT_ENEMY,
        WT_SYSTEM
    };

    struct SONETTO_EXPORT TexCoord {
        TexCoord():left(0.0f),right(0.0f),top(0.0f),bottom(0.0f) { }
        float left;
        float right;
        float top;
        float bottom;
    };

    struct SONETTO_EXPORT WindowTexCoord {
        TexCoord slim_left;
        TexCoord slim_center;
        TexCoord slim_right;
        TexCoord top_left;
        TexCoord top;
        TexCoord top_right;
        TexCoord left;
        TexCoord center;
        TexCoord right;
        TexCoord bottom_left;
        TexCoord bottom;
        TexCoord bottom_right;
        TexCoord tail_up;
        TexCoord tail_down;
        TexCoord cursor;
        TexCoord cursor_line;
    };

    /** @brief Structure used to store glyph data.
     *
     * This structure is used to store the texture coordinates and horizontal offset for each character.
     */
    struct SONETTO_EXPORT Glyphstruct {
        /// @brief This is the top-left texture UV coordinate for this glyph.
        Ogre::Vector2 texcoord0;
        /// @brief This is the top-right texture UV coordinate for this glyph.
        Ogre::Vector2 texcoord1;
        /// @brief This is the bottom-left texture UV coordinate for this glyph.
        Ogre::Vector2 texcoord2;
        /// @brief This is the bottom-right texture UV coordinate for this glyph.
        Ogre::Vector2 texcoord3;
        /// @brief This is the horizontal offset, the horizontal size for this glyph.
        float x_offset;
    };

    /** @brief Stores the number of glyphs in the font texture.
     *
     * This structure is used to store the texture coordinates and horizontal offset for each character.
     */
    struct SONETTO_EXPORT GlyphTable {
        /** @brief Default constructor.
        * @param nx is the number of horizontal glyphs in the texture.
        * @param ny is the number of vertical glyphs in the texture.
        */
        GlyphTable(unsigned long nx = 0, unsigned long ny = 0) : x(nx),y(ny) {}
        /// @brief Number of horizontal glyphs in the texture.
        Ogre::uint32 x;
        /// @brief Number of vertical glyphs in the texture.
        Ogre::uint32 y;
    };

    /** @brief ???
     *
     * Need to redo this, ignore.
     */
    struct SONETTO_EXPORT GlyphHeader {
        /// @brief Constructor.
        GlyphHeader() {}
        /// @brief Number of glyphs per line and number of lines.
        GlyphTable glyph_tbl;
        /// @brief Default Vertical Space for each new line.
        float default_y_space;
        /// @brief Total number of Glyphs
        Ogre::uint32 num_glyphs;
        /// @brief Offset value for Glyph Mapping
        Ogre::Vector2 glyph_coord_offset;
    };

    /** @brief Store the color change events in text (deprecated).
     *
     * Need to remove this, ignore.
     */
    struct SONETTO_EXPORT ColorTextEvent {
        size_t flag_position;
        size_t color_id;
    };

    enum FontChunkHeader
    {
        FONT_MAIN = 0xF0AA,
        FONT_GLYPH = 0xF0BB,
        FONT_COLOR = 0xF0FF
    };

    enum FontBlendMode
    {
        FBM_TRANSPARENT_ALPHA = 0x1010,
        FBM_TRANSPARENT_COLOR = 0x2010,
        FBM_ADD = 0x2020,
        FBM_MODULATE  = 0x20A0,
        FBM_REPLACE  = 0x3000
    };

    enum CompareFunction
    {
        SCF_ALWAYS_FAIL = 0x1000,
        SCF_ALWAYS_PASS = 0x10A0,
        SCF_LESS = 0x20A0,
        SCF_LESS_EQUAL = 0x20B0,
        SCF_EQUAL = 0x40A0,
        SCF_NOT_EQUAL = 0x40F0,
        SCF_GREATER_EQUAL = 0xA0A0,
        SCF_GREATER = 0xA0F0
    };

    enum FilterType
    {
        FT_NONE = 0x0000,
        FT_POINT = 0x1111,
        FT_LINEAR = 0x2222,
        FT_ANISOTROPIC = 0x3333
    };

    /** Struct containing Icon Frame data.
    @remarks
        This struct is used to store the dimensions and
        texture coordinates information for every frame of each icon.
    @remarks
        Usually you may want to keep the dimensions to 1.0f and keep the icons square.
    @remarks
        Note that this is only the dimensions, it will be scalled down depending
        on where it beign used, for instance, on a TextElement it will be scaled down
        to the text dimensions.
        (Actually, scaled to the Y dimensions of the text, as the text is not square either.)
    */
    struct IconSetFrame
    {
        /// Icon Horizontal Dimension, usually 1.0f.
        Ogre::Real x;
        /// Icon Vertical Dimension, usually 1.0f.
        Ogre::Real y;
        /// Icon Horizontal Texture Coordinate.
        Ogre::Real u1;
        /// Icon Vertical Texture Coordinate.
        Ogre::Real v1;
        /// Icon Horizontal Texture Coordinate.
        Ogre::Real u2;
        /// Icon Vertical Texture Coordinate.
        Ogre::Real v2;
    };

    /** Struct containing information about icon animation.
    @remarks
        This struct contain the animation frame order, and contains all
        the frames for each icon.
    */
    struct IconSetData
    {
        /** Icon Frame Order.
        @remarks
            This vector contains the order which the frames
            will show, if it is zero, then there will be no animation at all.
            You may use the same frame more than once, and the number of frame orders
            may be greater than the number of frames.
        */
        std::vector<size_t> iconFrameOrder;
        /** Icon Frames.
        @remarks
            Every Icon must contain at last one frame.
        */
        std::vector<IconSetFrame> iconFrames;
    };

    /** Icon Set
    @remarks
        IconSet is a small class containing information about Icons to be used ingame.
        Icons may contain animation frames, but everything must be contained inside one texture only.
    @remarks
        IconsSets only contains dimension, texture and material information about icons,
        Animation must be implemented by the classes going to use it.
    */
    class SONETTO_EXPORT IconSet
    {
    public:
        std::map<size_t, IconSetData> iconSetData;
        Ogre::MaterialPtr iconMaterial;
    };
}; // namespace

#endif // SONETTO_MAIN_H
