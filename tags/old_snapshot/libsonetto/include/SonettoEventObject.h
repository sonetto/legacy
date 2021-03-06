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

#ifndef SONETTO_EVENTOBJECT_H
#define SONETTO_EVENTOBJECT_H

#include <vector>

// Forward declarations
namespace Sonetto
{
    class EventObject;

    /// A vector of EventObject pointers
    typedef std::vector<EventObject *> EventVector;
}

#include <Ogre.h>
#include "SonettoMain.h"

namespace Sonetto
{
    enum EventState {
        ES_NORMAL,
        ES_LOCKED,
        ES_SCRIPT
    };

    /** Represents a Event Object inside the game.

        Usually is used in maps to represent the Player, NPCs and other objects
        such as event triggers and wrap gateways (used to change maps).
        They may and may not contain visible models, but always contain position, orientation
        and collision objects.
    */
    class SONETTO_EXPORT EventObject
    {
    public:
        EventObject(const Ogre::String & name,
                    Ogre::SceneNode * parent,
                    Ogre::SceneManager * manager,
                    float height,float actRadius,
                    float colRadius,float speed,
                    bool noVisibleEntity = false,
                    const Ogre::String & modelname = "");
        virtual ~EventObject();

        /** Updates this Object.

        @param
            deltatime This is the value of 1.0f/FPS used for framerate-independent movement.
        */
        virtual void update(float deltatime);

        virtual const Ogre::String & getName(void) const;

        /** This function changes the actual object model

            note that this function change the actual entity internally.
        @param
            modelname The new model for this object.
        */
        virtual void changeModel(const Ogre::String & modelname);

        virtual void setPosition(const Ogre::Vector3 &pos);

        virtual void setPosition(float x, float y, float z);

        virtual const Ogre::Vector3 & getPosition(void) const;

        virtual void setOrientation(const Ogre::Quaternion &orientation);

        virtual void setOrientation(float w, float x, float y, float z);

        virtual const Ogre::Quaternion & getOrientation(void) const;

        virtual inline void setHeight(float height) { mHeight = height; }

        virtual inline void setActRadius(float radius) { mActRadius = radius; }

        virtual inline void setColRadius(float radius) { mColRadius = radius; }

        virtual inline void setSpeed(float speed) { mSpeed = speed; }

        virtual inline float getHeight() const { return mHeight; }

        virtual inline float getActRadius() const { return mActRadius; }

        virtual inline float getColRadius() const { return mColRadius; }

        virtual inline float getSpeed() const { return mSpeed; }

        /// Set the state for this event.
        virtual void setState(EventState state);

        /// Get the state for this event.
        virtual const EventState getState(void) const;

        /** Set the current collision flag.

            When true, the event will move freely through the map,
            withouth taking collisions in consideration, this is used
            by the Script to create flying objects without interference of the map.
        */
        virtual void setIgnoreCollision(bool mode);

        /// Return the current collision flag.
        virtual const bool getIgnoreCollision(void) const;

        /// Return whether this object has a visible entity or not.
        virtual bool isInvisible(void) const;

        /// Set a new parent node for this object.
        virtual void setParent(Ogre::SceneNode * parent);

        /// Return a pointer to this object's entity.
        virtual Ogre::Entity * getEntity(void) const;

        /// Return a pointer to this object's node.
        virtual Ogre::SceneNode * getNode(void);

        /// Return a pointer to this object's parent node.
        virtual const Ogre::SceneNode * getParent(void) const;

        /// Return a pointer to this object's scene manager.
        virtual const Ogre::SceneManager * getSceneManager(void) const;

        // Start of Script/Event function Section
        /// Completely erase the entire event list for this event.
        //virtual void clearEventList();
        /** Creates a walk list.

            A Walk list is a set of points this event will walk to.
            After creating you must imediatelly add walk points to the list,
            and then close it using "endWalkList()".
        */
        /*
        virtual void startWalkList();
        /// Ends an already created walklist.
        virtual void endWalkList();
        virtual void addWalkPoint();*/

    protected:
        /// This Event State
        EventState mEventState;
        /// Ignore Collisions Flag (Ghost / Fly Mode)
        bool mIgnoreCollisions;
        Ogre::String mName;
        Ogre::String mModelName;
        /** This Object flags, wheter has a visible model or not.
            (true for Triggers/Gateways, false for NPCs and Players)
        */
        bool mInvisible;
        /// This Object Entity. (Visible model)
        Ogre::Entity * mEntity;
        /// This Object Node. (Represent Position and Orientation)
        Ogre::SceneNode * mNode;
        /// This Object Node's Parent.
        Ogre::SceneNode * mParent;
        /// The SceneManager used to create and manage this object's objects.
        Ogre::SceneManager * mSceneManager;
        /// The desired position relative to current, reset at every frame.
        Ogre::Vector3 mTargetPosition;

        float mHeight;
        float mActRadius;
        float mColRadius;
        float mSpeed;
    };
}; // namespace


#endif // SONETTO_EVENTOBJECT_H
