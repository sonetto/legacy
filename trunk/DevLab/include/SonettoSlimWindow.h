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
#ifndef SONETTO_SLIMWINDOW_H_
#define SONETTO_SLIMWINDOW_H_
#include <OgreOverlayContainer.h>
#include <OgreVector2.h>
#include "SonettoMain.h"
namespace Sonetto
{
    class SlimBorderRenderable;
#define SLIM_NUM_VERTEX 18
    //66
    class SlimWindow : public Ogre::OverlayContainer
    {
        friend class SlimBorderRenderable;
    public:
        /// Constructor.
        SlimWindow(const Ogre::String& name);
        /// Destructor.
        virtual ~SlimWindow();
        /// Initialise
        virtual void initialise (void);
        /// Tells this element how to interpret the position and dimension values it is given.
        void setScrMetricsMode(ScreenMetricsMode smm);
        /** Set the border size.
        * @param sizeX The border width
        * @param sizeY The border height
        */
        void setBorderSize(const Ogre::Real sizeX, const Ogre::Real sizeY);
        /** Set the border size.
        * @param size The border size
        */
        void setBorderSize(const Ogre::Real size);
        /** Get the border size.
        * @return The border size (X and Y)
        */
        const Ogre::Vector2 getBorderSize();
        /** Set the Border and Mask texture coordinates.
        *
        * @remarks This function copies all the content from the address to the class.
        */
        void setTexCoords(WindowTexCoord * texcoord);
        /** Set the background tile mode.
        * @param mode The way this SlimWindow will texturize the background
        * False: Stretch the texture to the border of the object
        * True: This will map the baground based on the screen
        * (note: the result depends upon the Screen Metrics Mode for this object)
        */
        void setTileMode(bool mode);
        /// Get the tile mode.
        bool getTileMode();
        /// Set the number of times the texture will tile.
        void setTiling(const Ogre::Real tileX, const Ogre::Real tileY);
        /// Set the number of times the texture will tile.
        void setTiling(const Ogre::Vector2 tile);
        /// Get the number of times the texture will tile.
        Ogre::Vector2 getTiling();
        /// Set the SlimWindow background color.
        void setBackgroundColor(const Ogre::ColourValue& col);
        /// Set the SlimWindow background color.
        void setBackgroundColor(const Ogre::Real r = 1.0f,const Ogre::Real g = 1.0f,const Ogre::Real b = 1.0f,const Ogre::Real a = 1.0f);
        /// Get the SlimWindow background color.
        const Ogre::ColourValue& getBackgroundColor();
        /// Set the SlimWindow border color.
        void setBorderColor(const Ogre::ColourValue& col);
        /// Set the SlimWindow border color.
        void setBorderColor(const Ogre::Real r = 1.0f,const Ogre::Real g = 1.0f,const Ogre::Real b = 1.0f,const Ogre::Real a = 1.0f);
        /// Get the SlimWindow border color.
        const Ogre::ColourValue& getBorderColor();
        /** Sets the name of the material to use for the borders. */
        void setBorderMaterialName(const Ogre::String& name);
        /** Gets the name of the material to use for the borders. */
        const Ogre::String& getBorderMaterialName(void) const;
        /** See OverlayElement. */
        virtual const Ogre::String& getTypeName(void) const;
        /** See Renderable. */
        void getRenderOperation(Ogre::RenderOperation& op);
        /** Overridden from OverlayElement */
        void setMaterialName(const Ogre::String& matName);
        /** Overridden from OverlayContainer */
        void _updateRenderQueue(Ogre::RenderQueue* queue);
        /// Visit Renderables
        void visitRenderables(Ogre::Renderable::Visitor* visitor,
                              bool debugRenderables = false);
        /** Overridden from OverlayContaienr */
        void _update(void);
    protected:
        bool mUpdateBorderColors;
        bool mUpdateBackgroundColors;
        /// Border Renderable Pointer
        SlimBorderRenderable * mBorderRenderable;
        /// Border Material Name
        Ogre::String mBorderMaterialName;
        /// Border Material Pointer
        Ogre::MaterialPtr mpBorderMaterial;
        /// Border Size
        Ogre::Vector2 mBorderSize;
        /// Background Color
        Ogre::ColourValue mBackgroundColor;
        /// Border Color
        Ogre::ColourValue mBorderColor;
        /// Background Tile Mode
        bool mTileMode;
        /// Background Tiling
        Ogre::Vector2 mTiling;
        /// SlimWindow vertex coordinates
        Ogre::Vector2 mPosCoord[SLIM_NUM_VERTEX];
        /// Border and Mask coordinates
        WindowTexCoord * mTexCoord0;
        /// Background coordinates
        Ogre::Vector2 mTexCoord1[SLIM_NUM_VERTEX];
        /// Screen Metrics Mode
        ScreenMetricsMode mScrMetricsMode;
        /// Viewport Aspect Ratio
        Ogre::Real mAspectRatio;
        /// Background Render Operation
        Ogre::RenderOperation mRenderOp;
        /// Border Render Operation
        Ogre::RenderOperation mRenderOp2;
        /// Type Name
        static Ogre::String msTypeName;
        /// internal method for setting up geometry, called by OverlayElement::update
        virtual void updatePositionGeometry(void);
        /// Called to update the texture coords.
        virtual void updateTextureGeometry(void);
        /// Called to update the border colors.
        void updateBorderColors(void);
        /// Called to update the background colors.
        void updateBackgroundColors(void);
        /// Called to calculate the SlimWindow's vertexes
        void calculatePosition(void);
        /// Called to calculate the SlimWindow's background texture coordinates
        void calculateTexCoord(void);
    };
    /** Class for rendering the border of a SlimWindow.
    * @remarks
    * We need this because we have to render twice, once with the inner panel's repeating
    * material (handled by superclass) and once for the border's separate meterial.
    */
    class SlimBorderRenderable : public Ogre::Renderable
    {
    protected:
        SlimWindow* mParent;
    public:
        /** Constructed with pointers to parent. */
        SlimBorderRenderable(SlimWindow* parent) : mParent(parent)
        {
            mUseIdentityProjection = true;
            mUseIdentityView = true;
        }
        const Ogre::MaterialPtr& getMaterial(void) const
        {
            return mParent->mpBorderMaterial;
        }
        void getRenderOperation(Ogre::RenderOperation& op)
        {
            op = mParent->mRenderOp2;
        }
        void getWorldTransforms(Ogre::Matrix4* xform) const
        {
            mParent->getWorldTransforms(xform);
        }
        unsigned short getNumWorldTransforms(void) const
        {
            return 1;
        }
        Ogre::Real getSquaredViewDepth(const Ogre::Camera* cam) const
        {
            return mParent->getSquaredViewDepth(cam);
        }
        const Ogre::LightList& getLights(void) const
        {
            // N/A, panels are not lit
            static Ogre::LightList ll;
            return ll;
        }
        bool getPolygonModeOverrideable(void) const
        {
            return mParent->getPolygonModeOverrideable();
        }
    };
} // namespace
#endif //SONETTO_SLIMWINDOW_H