/******************************************************************/
/*!
	@file	GeometricNode.h
	@brief	Object class for geometry
	@note
	@todo
	@bug

	@author	Naoto Nakamura
	@date	Apl. 1, 2020
*/
/******************************************************************/

#ifndef S3D_MATH_GEOMETRICNODE_H
#define S3D_MATH_GEOMETRICNODE_H

#include "S3D/Common.h"
#include "S3D/Graphics/Math/MathematicsTypes.h"

#include <list>

namespace S3D
{
	//////////////////////////////////////////////////////
	//				forward declarations				//
	//////////////////////////////////////////////////////
	// implemented
	class GeometricNode;

	//required
	class Entity;

	//////////////////////////////////////////////////////
	//				class declarations					//
	//////////////////////////////////////////////////////

	struct GeometricState
	{
	public:
		GeometricState()
			: position(0.0f, 0.0f, 0.0f),
			  rotation(0.0f, 0.0f, 0.0f, 1.0f),
			  scale(1.0f, 1.0f, 1.0f)
		{
		}

		GeometricState(
			const Vector3 &position,
			const Quaternion4 &orientation,
			const Vector3 &scale)
			: position(position),
			  rotation(orientation),
			  scale(scale)
		{
		}

	public:
		ATTRIBUTE_ALIGN(16)
		Vector3 position;
		ATTRIBUTE_ALIGN(16)
		Quaternion4 rotation;
		ATTRIBUTE_ALIGN(16)
		Vector3 scale;
	};

	/****************************************/
	/*!
		@class	GeometricNode
		@brief	Abstract class for 3D Node
		@note
		@author	Naoto Nakamura
		@date	Apl. 1, 2009
	*/
	/****************************************/
	class GeometricNode
	{
	public:
		GeometricNode() 
		: mParent(NULL),
		mIsDirty(true)
		{
		}

		virtual ~GeometricNode() {}

	private:
		void _setRelationToParent(GeometricNode *parent);
		void _cutOffRelationToParent();

	public:
		virtual void init() {}
		virtual void cleanup();

		// Parent-child relationship
		GeometricNode *getParent() const { return mParent; }

		std::list<GeometricNode *> &getChildList() { return mChildList; }

		bool isExistAsDescendant(GeometricNode *target);

		virtual bool setRelationToChild(GeometricNode *child);
		virtual bool cutOffRelationToChild(GeometricNode *child);

		virtual bool setRelationToChildWithoutLocalStateAdjusting(GeometricNode *child);
		virtual bool cutOffRelationToChildWithoutLocalStateAdjusting(GeometricNode *child);

		// State
		const GeometricState *getLocalState() const { return &mLocal; }

		const Vector3 *getLocalPosition() const { return &mLocal.position; }
		void setLocalPosition(const Vector3 &position) { mLocal.position = position; mIsDirty = true; }

		const Quaternion4 *getLocalOrientation() const { return &mLocal.rotation; }
		void setLocalOrientation(const Quaternion4 &orientation) { mLocal.rotation = orientation; mIsDirty = true; }

		const Vector3 *getLocalScale() const { return &mLocal.scale; }
		void setLocalScale(const Vector3 &scale) { mLocal.scale = scale; mIsDirty = true; }

		const GeometricState *getGlobalState() const { return &mGlobal; }

		const Vector3 *getGlobalPosition() const { return &mGlobal.position; }
		const Quaternion4 *getGlobalOrientation() const { return &mGlobal.rotation; }
		const Vector3 *getGlobalScale() const { return &mGlobal.scale; }

		void copyGlobalStateToLocalState();

		virtual void calculateGlobalState();

		void adjustLocalStateToParentObject();

		Entity *getEntity() { return mEntity; }
		void setEntity(Entity *entity) { mEntity = entity; }

		bool isDirty() const { return mIsDirty; }
		void resetDirty() { mIsDirty = false; }

	protected:
		GeometricState mLocal;
		GeometricState mGlobal;

		GeometricNode *mParent;				   //<! Parent object pointer
		std::list<GeometricNode *> mChildList; //<! Child object pointers

		bool mIsDirty;

		Entity *mEntity;
	};

}; // namespace S3D

#endif // S3D_MATH_GEOMETRICNODE_H
