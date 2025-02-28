/******************************************************************/
/*!
	@file	S3D.h
	@brief	Header for using 3D library
	@note
	@todo
	@bug

	@author	Naoto Nakamura
	@date	Mar. 10, 2020
*/
/******************************************************************/

#ifndef S3D_S3D_H
#define S3D_S3D_H

#include "S3D/Common.h"

#include "S3D/Foundation/CPU.h"
#include "S3D/Foundation/IO.h"
#include "S3D/Foundation/FileIO.h"
#include "S3D/Foundation/Lock.h"
#include "S3D/Foundation/Timer.h"
#include "S3D/Foundation/Thread.h"
#include "S3D/Foundation/QueueThread.h"
#include "S3D/Foundation/QueueThreadPool.h"
#include "S3D/Foundation/Resource.h"
#include "S3D/Foundation/ResourceDatabase.h"

#include "S3D/Graphics/Math/MathematicsTypes.h"

#include "S3D/Graphics/GeometricNode.h"
#include "S3D/Graphics/Camera.h"
#include "S3D/Graphics/Light.h"
#include "S3D/Graphics/Material.h"
#include "S3D/Graphics/Mesh.h"
#include "S3D/Graphics/Renderer.h"
#include "S3D/Graphics/RenderFrame.h"
#include "S3D/Graphics/Shader.h"
#include "S3D/Graphics/ShaderParameters.h"
#include "S3D/Graphics/Texture.h"

#include "S3D/Graphics/Mesh/Rectangle.h"
#include "S3D/Graphics/Mesh/FrameRectangle.h"
#include "S3D/Graphics/Mesh/Cuboid.h"

#include "S3D/Game/Entity.h"
#include "S3D/Game/RenderList.h"
#include "S3D/Game/Content.h"

#include "S3D/Game/Function/EntityFunction.h"
#include "S3D/Game/Function/CameraFunction.h"
#include "S3D/Game/Function/MeshFunction.h"
#include "S3D/Game/Function/MeshRendererFunction.h"


#endif // S3D_S3D_H
