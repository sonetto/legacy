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
#ifndef __SONETTO_PLANE__
#define __SONETTO_PLANE__

#include "SonettoMain.h"

#include <OgreOverlayContainer.h>
#include "SonettoMain.h"

namespace Sonetto {
    /** OverlayElement representing a flat, single-material plane which can contain other elements.
    @remarks
        This class subclasses OverlayContainer because it can contain other elements. Like other
        containers, if hidden it's contents are also hidden, if moved it's contents also move etc.
        The plane itself is a 2D rectangle which is rendered with a single material and independent alpha
        abd vertex colors.
        The texture(s) on the plane can be tiled depending on your requirements.
    @par
        This component is suitable for backgrounds and grouping other elements.
    @par
        Note that the material can have all the usual effects applied to it like multiple texture
        layers, scrolling / animated textures etc. For multiple texture layers, you have to set
        the tiling level for each layer.
    */
    class SONETTO_EXPORT Plane : public Ogre::OverlayContainer
    {
    public:
        /// Constructor
        Plane(const Ogre::String &name);
        /// Destructor
        virtual ~Plane();

        /// Initialise
        void initialise(void);

        /// Sets the texture coordinates for the plane.
        void setUV(Ogre::Real u1, Ogre::Real v1, Ogre::Real u2, Ogre::Real v2);

        /// Get the uv coordinates for the plane.
        void getUV(Ogre::Real& u1, Ogre::Real& v1, Ogre::Real& u2, Ogre::Real& v2) const;

        /// Set the vertex colors (and alpha).
        void setColors(Ogre::Real r, Ogre::Real g, Ogre::Real b, Ogre::Real a);

        /// Set the Colour for this element.
        virtual void setColour(const Ogre::ColourValue& col);

        /// Gets the colour for this element.
        virtual const Ogre::ColourValue& getColour(void) const;

        /// See OverlayElement.
        virtual const Ogre::String& getTypeName(void) const;
        /// See Renderable.
        void getRenderOperation(Ogre::RenderOperation& op);
        /// Overridden from OverlayElement.
        void setMaterialName(const Ogre::String& matName);
        /// Overridden from OverlayContainer.
        void _updateRenderQueue(Ogre::RenderQueue* queue);
        /// Overridden from OverlayElement.
        virtual void _update(void);

    protected:
        /// Update color.
        bool mUpdateColors;
        /// Aspect Ratio
        Ogre::Real mAspectRatio;

        ScreenMetricsMode mScrMetricsMode;

        /// Number of Texture Coordinates in the buffer.
        size_t mNumTexCoordsInBuffer;

        /// UV Coordinates.
        Ogre::Real mU1, mV1, mU2, mV2;

        /// Render Operation.
        Ogre::RenderOperation mRenderOp;

        /// internal method for setting up geometry, called by OverlayElement::update
        virtual void updatePositionGeometry(void);

        /// Called to update the texture coords when layers change
        virtual void updateTextureGeometry(void);

        /// Called to update the colours
        virtual void updateColors(void);

        /// Typename for identification.
        static Ogre::String msTypeName;
    };
}; // namespace Sonetto

#endif // __SONETTO_PLANE__