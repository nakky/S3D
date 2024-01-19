

#include "S3D/Math/GeometricNode.h"

#include <sstream>

namespace S3D
{
	//////////////////////////////////////////////////////////////////
	//						GeometricObject							//
	//////////////////////////////////////////////////////////////////

	/****************************************/
	/*!
		@brief	Determine if object exists
				as descendant of "this".
		@note

		@param	object target object

		@author	Naoto Nakamura
		@date	Apl. 2, 2009
	*/
	/****************************************/
	void GeometricNode::cleanup()
	{
		while (mChildList.size() > 0)
		{
			cutOffRelationToChild(*mChildList.begin());
		}

		if (mParent != NULL)
			mParent->cutOffRelationToChild(this);
	}

	/****************************************/
	/*!
		@brief	Determine if object exists
				as descendant of "this".
		@note

		@param	object target object

		@author	Naoto Nakamura
		@date	Apl. 2, 2009
	*/
	/****************************************/
	bool GeometricNode::isExistAsDescendant(GeometricNode *object)
	{
		if (this == object)
			return true;

		std::list<GeometricNode *>::iterator ite = mChildList.begin();
		while (ite != mChildList.end())
		{
			if ((*ite)->isExistAsDescendant(object))
				return true;
			ite++;
		}

		return false;
	}

	/****************************************/
	/*!
		@brief	Set relationship to parent object
		@note	private

		@param	parent parent object

		@author	Naoto Nakamura
		@date	Apl. 2, 2009
	*/
	/****************************************/
	void GeometricNode::_setRelationToParent(GeometricNode *parent)
	{
		mParent = parent;
	}

	/****************************************/
	/*!
		@brief	Cut off relationship to parent object
		@note	private

		@author	Naoto Nakamura
		@date	Apl. 2, 2009
	*/
	/****************************************/
	void GeometricNode::_cutOffRelationToParent()
	{
		mParent = NULL;
	}

	/****************************************/
	/*!
		@brief	Set relationship to child object
		@note

		@param	child child object

		@author	Naoto Nakamura
		@date	Apl. 2, 2009
	*/
	/****************************************/
	bool GeometricNode::setRelationToChild(GeometricNode *child)
	{
		if (child->isExistAsDescendant(this))
			return false;
		else if (isExistAsDescendant(child))
			return false;

		child->calculateGlobalState();

		if (child->mParent != NULL)
			child->mParent->cutOffRelationToChild(child);

		mChildList.push_back(child);
		child->_setRelationToParent(this);

		// Update local state
		child->adjustLocalStateToParentObject();
		return true;
	}

	/****************************************/
	/*!
		@brief	Cut off relationship to child object
		@note

		@param	child child object

		@author	Naoto Nakamura
		@date	Apl. 2, 2009
	*/
	/****************************************/
	bool GeometricNode::cutOffRelationToChild(GeometricNode *child)
	{
		std::list<GeometricNode *>::iterator ite = mChildList.begin();
		while (ite != mChildList.end())
		{
			if (*ite == child)
			{
				// recaluculate materix
				if (child != NULL)
				{
					child->copyGlobalStateToLocalState();
				}

				(*ite)->_cutOffRelationToParent();
				mChildList.erase(ite);
				return true;
			}
			ite++;
		}
		return false;
	}

	/****************************************/
	/*!
		@brief	Set relationship to child object
		@note

		@param	child child object

		@author	Naoto Nakamura
		@date	Apl. 2, 2009
	*/
	/****************************************/
	bool GeometricNode::setRelationToChildWithoutLocalStateAdjusting(GeometricNode *child)
	{
		if (child->isExistAsDescendant(this))
			return false;
		else if (isExistAsDescendant(child))
			return false;

		if (child->mParent != NULL)
			child->mParent->cutOffRelationToChild(child);
		mChildList.push_back(child);
		child->_setRelationToParent(this);
		return true;
	}

	/****************************************/
	/*!
		@brief	Cut off relationship to child object
		@note

		@param	child child object

		@author	Naoto Nakamura
		@date	Apl. 2, 2009
	*/
	/****************************************/
	bool GeometricNode::cutOffRelationToChildWithoutLocalStateAdjusting(GeometricNode *child)
	{
		std::list<GeometricNode *>::iterator ite = mChildList.begin();
		while (ite != mChildList.end())
		{
			if (*ite == child)
			{
				(*ite)->_cutOffRelationToParent();
				mChildList.erase(ite);
				return true;
			}
		}

		return false;
	}

	/****************************************/
	/*!
		@brief	Caluculate global state from local state
		@note

		@author	Naoto Nakamura
		@date	Mar. 30, 2009
	*/
	/****************************************/
	void GeometricNode::calculateGlobalState()
	{
		if (mParent != NULL)
		{
			// update position
			Matrix44 qm;
			Vector3 vec;

			multiplyVector3Vector3(vec, mParent->mGlobal.scale, mLocal.position);

			mParent->mGlobal.orientation.toMatrix44(qm);

			multiplyMatrix44Vector3(vec, qm, vec);

			addVector3Vector3(mGlobal.position, mParent->mGlobal.position, vec);

			// update scaling
			multiplyVector3Vector3(mGlobal.scale, mParent->mGlobal.scale, mLocal.scale);

			// update orientation
			multiplyQuaternion4Quaternion4(mGlobal.orientation, mParent->mGlobal.orientation, mLocal.orientation);
		}
		else
		{
			mGlobal.position = mLocal.position;
			mGlobal.orientation = mLocal.orientation;
			mGlobal.scale = mLocal.scale;
		}
	}

	/****************************************/
	/*!
		@brief	Caluculate global state recursively
		@note

		@author	Naoto Nakamura
		@date	Mar. 30, 2009
	*/
	/****************************************/
	void GeometricNode::calculateGlobalStateDescendants()
	{
		std::list<GeometricNode *> mNodeList;
		mNodeList.push_back(this);
		GeometricNode *node = NULL;

		while (mNodeList.size() != 0)
		{
			node = *mNodeList.begin();

			node->calculateGlobalState();

			std::list<GeometricNode *>::iterator ite = node->mChildList.begin();

			while (ite != node->mChildList.end())
			{
				mNodeList.push_back(*ite);
				ite++;
			}

			ite = mNodeList.begin();
			mNodeList.erase(ite);
		}
	}

	/****************************************/
	/*!
		@brief	Adjust local state to difference of global state
				between parent object and "this".
		@note

		@author	Naoto Nakamura
		@date	Mar. 30, 2009
	*/
	/****************************************/
	void GeometricNode::adjustLocalStateToParentObject()
	{
		if (mParent != NULL)
		{
			Quaternion4 dq = mParent->mGlobal.orientation;
			dq.inverse();

			// calculation of orientation difference
			multiplyQuaternion4Quaternion4(mLocal.orientation, mGlobal.orientation, dq);

			// calculation of scaling difference
			divideVector3Vector3(mLocal.scale, mGlobal.scale, mParent->mGlobal.scale);

			// calculation of position difference
			Vector3 vec;
			subtractVector3Vector3(vec, mGlobal.position, mParent->mGlobal.position);
			convertVector3WithQuaternion4(mLocal.position, dq, vec);
		}
		else
		{
			mLocal.position = mGlobal.position;
			mLocal.orientation = mGlobal.orientation;
			mLocal.scale = mGlobal.scale;
		}
	}

	/****************************************/
	/*!
		@brief	Copy global state to local state
		@note

		@author	Naoto Nakamura
		@date	Mar. 30, 2009
	*/
	/****************************************/
	void GeometricNode::copyGlobalStateToLocalState()
	{
		mLocal.position = mGlobal.position;
		mLocal.orientation = mGlobal.orientation;
		mLocal.scale = mGlobal.scale;
	}

}; // namespace S3D
