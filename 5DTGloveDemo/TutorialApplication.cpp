/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "TutorialApplication.h"
#include <iostream>

using namespace Ogre;

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication():
	m_pPlatform(NULL),
	m_pGUI(NULL),
	m_ptxtFPS(NULL),
	m_ptxtRawVal(NULL),
	m_ptxtMaxCal(NULL),
	m_ptxtMinCal(NULL)
{
	m_iCurrentSensor = 1;
	mNumEntitiesInstanced = 0;

	// Set constants
	m_fRotateSpeed = 0.002;     // The rotate constant
	m_fRotateDecel = 0.001;     // The rotate deceleration constant
	m_fZoomSpeed = 2;			// The zoom constant
	m_fZoomDecel = 2;			// The zoom deceleration
	m_fMaxZoom = 10;
	m_fMinZoom = 100;
//	old_index_val = -10000;
	decreasing = false;
	tap = 0;
	collided = false;
	diff_val.open("diff");

	cube = 0;
	red = true;
	
	m_pGlove = NULL;
	thumb.open("thumb.txt");
	tapping.open("tap");

	prev_collided = 0.0f;

	position.open("pos");
	mesh_data.open("mesh");

	collision_test.open("collision");
	build_cube = false;

	sound_response = false;
	color_response = false;
	distort_color_response = false;
	distort_sound_response = false;

	distortion_time = 1.0f;
	curr_time = 0;

	prev_finger_val = -999999999999;
	distance.open("distance");
	//m_pRoot->loadPlugin("Plugin_CgProgramManager");
}

//-------------------------------------------------------------------------------------
void TutorialApplication::ConnectGlove(void)
{
	#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	int iPort = 0;
	m_pGlove = fdOpen("USB0");
	if (!m_pGlove)
		m_pGlove = fdOpen("COM0");
	//while (!m_pGlove && iPort < 10)
	//{
	//	std::stringstream out;
	//	out<<"COM"<<iPort;
	//	char tempChr[50];
	//	strncpy(tempChr, out.str().c_str(),strlen(out.str().c_str())+1);

	//	m_pGlove = fdOpen(tempChr);				
	//	iPort++;
	//}
	#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
		m_pGlove = fdOpen(""); // connect to first glove available
	#else // Linux
		m_pGlove = fdOpen("/dev/usb/hiddev0");
		if (!m_pGlove)
			m_pGlove = fdOpen("/dev/dev/ttyS0");
	#endif
			
	if (m_pGlove)
	{
		// try to automatically load the calibration file
		char cSerial[50];
		fdGetSerialNumber(m_pGlove, cSerial);
		std::string sFileName(cSerial);
		sFileName += ".fd";
		if (fdLoadCalibration(m_pGlove, sFileName.c_str()))
			int a = 3;

		// load the correct calibration GUI
		
		if (fdGetGloveType(m_pGlove)==FD_GLOVE14U || 
			fdGetGloveType(m_pGlove) == FD_GLOVE14UW ||
			fdGetGloveType(m_pGlove) == FD_GLOVE14U_USB)
			loadCalibrationGui(false);
		else
			loadCalibrationGui(true);
	}
}

//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
	m_pGUI->shutdown();
	delete m_pGUI;
	m_pGUI = 0;   
	m_pPlatform->shutdown();
	delete m_pPlatform;
	m_pPlatform = 0;
	m_pSceneMgr->destroyQuery(mRaySceneQuery);

	fdClose(m_pGlove);
}

void TutorialApplication::createFrameListener(void)
{
	BaseApplication::createFrameListener();
	mRaySceneQuery = m_pSceneMgr->createRayQuery(Ogre::Ray());
}

bool TutorialApplication::isCollision(const Ogre::Vector3& position, const Ogre::Vector3& direction, Ogre::Vector3 &result) 
{
    Ogre::Ray ray(position, direction);
    mRaySceneQuery->setRay(ray);
    Ogre::RaySceneQueryResult &result_query = mRaySceneQuery->execute();
    Ogre::RaySceneQueryResult::iterator itr;
	Ogre::Real closest_distance = -1.0f;
	Ogre::Vector3 closest_result;

    for (itr = result_query.begin(); itr != result_query.end(); itr++) {
        if (itr->movable->getName().compare("Cube") != 0 && itr->movable->getName().compare("manual1") != 0) 
		{
			Ogre::Entity *p_entity = static_cast<Ogre::Entity*>(itr->movable);
			//collision_test << itr->movable->getName() << " " << itr->distance << std::endl;
			size_t vertex_count;
            size_t index_count;
            Ogre::Vector3 *vertices;
            unsigned long *indices;

			//collision_test << "Test1" << std::endl;
			TutorialApplication::GetMeshInformation(p_entity, vertex_count, vertices, index_count, indices,             
                              p_entity->getParentNode()->_getDerivedPosition(),
                              p_entity->getParentNode()->_getDerivedOrientation(),
                              p_entity->getParentNode()->_getDerivedScale());
			//collision_test << "Test2" << std::endl;

			//collision_test << "vertex_count: " << vertex_count << std::endl;
			//collision_test << "index_count: " << index_count << std::endl;

			bool new_closest_found = false;

			/*
			for(int i = 0; i < vertex_count; i++)
			{
				mesh_data << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << std::endl;
			}
			mesh_data << "========" << std::endl;
			*/

            for (int i = 0; i < static_cast<int>(index_count); i += 3)
            {
                // check for a hit against this triangle
                std::pair<bool, Ogre::Real> hit = Ogre::Math::intersects(ray, vertices[indices[i]],
                    vertices[indices[i+1]], vertices[indices[i+2]], true, false);
				

                // if it was a hit check if its the closest
                if (hit.first)
                {
                    if ((closest_distance < 0.0f) ||
                        (hit.second < closest_distance))
                    {
						// this is the closest so far, save it off
						closest_distance = hit.second;
						new_closest_found = true;
						//collision_test << closest_distance << std::endl;
                    }
                }
            }

            // free the verticies and indicies memory
            delete[] vertices;
            delete[] indices;
 
            // if we found a new closest raycast for this object, update the
            // closest_result before moving on to the next object.
            if (new_closest_found)
            {
                closest_result = ray.getPoint(closest_distance);               
            }
        }       
    }
 
    // return the result
	distance << closest_distance << std::endl;
    if (closest_distance >= 0.0f && closest_distance < 1.1)
    {
        // raycast success
        result = closest_result;
        return (true);
    }
    else
    {
        // raycast failed
        return (false);
    } 
}

void TutorialApplication::GetMeshInformation(Ogre::Entity *entity,
                                size_t &vertex_count,
                                Ogre::Vector3* &vertices,
                                size_t &index_count,
                                unsigned long* &indices,
                                const Ogre::Vector3 &position,
                                const Ogre::Quaternion &orient,
                                const Ogre::Vector3 &scale)
{
	bool added_shared = false;
    size_t current_offset = 0;
    size_t shared_offset = 0;
    size_t next_offset = 0;
    size_t index_offset = 0;
    vertex_count = index_count = 0;
 
   Ogre::MeshPtr mesh = entity->getMesh();
 
   bool useSoftwareBlendingVertices = entity->hasSkeleton();
   entity->_updateAnimation();
   if (useSoftwareBlendingVertices)
   {
      entity->_updateAnimation();
   }
 
    // Calculate how many vertices and indices we're going to need
    for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
    {
        Ogre::SubMesh* submesh = mesh->getSubMesh( i );
 
        // We only need to add the shared vertices once
        if(submesh->useSharedVertices)
        {
            if( !added_shared )
            {
                vertex_count += mesh->sharedVertexData->vertexCount;
                added_shared = true;
            }
        }
        else
        {
            vertex_count += submesh->vertexData->vertexCount;
        }
 
        // Add the indices
        index_count += submesh->indexData->indexCount;
    }
 
 
    // Allocate space for the vertices and indices
    vertices = new Ogre::Vector3[vertex_count];
    indices = new unsigned long[index_count];
 
    added_shared = false;
 
    // Run through the submeshes again, adding the data into the arrays
    for ( unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
    {
        Ogre::SubMesh* submesh = mesh->getSubMesh(i);
 
      //----------------------------------------------------------------
      // GET VERTEXDATA
      //----------------------------------------------------------------
 
        //Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;
      Ogre::VertexData* vertex_data;
 
      //When there is animation:
      if(useSoftwareBlendingVertices)
         vertex_data = submesh->useSharedVertices ? entity->_getSkelAnimVertexData() : entity->getSubEntity(i)->_getSkelAnimVertexData();
      else
         vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;
 
 
        if((!submesh->useSharedVertices)||(submesh->useSharedVertices && !added_shared))
        {
            if(submesh->useSharedVertices)
            {
                added_shared = true;
                shared_offset = current_offset;
            }
 
            const Ogre::VertexElement* posElem =
                vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
 
            Ogre::HardwareVertexBufferSharedPtr vbuf =
                vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());
 
            unsigned char* vertex =
                static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
 
            // There is _no_ baseVertexPointerToElement() which takes an Ogre::Real or a double
            //  as second argument. So make it float, to avoid trouble when Ogre::Real will
            //  be comiled/typedefed as double:
            //      Ogre::Real* pReal;
            float* pReal;
 
            for( size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
            {
                posElem->baseVertexPointerToElement(vertex, &pReal);
 
                Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);
 
                vertices[current_offset + j] = (orient * (pt * scale)) + position;
            }
 
            vbuf->unlock();
            next_offset += vertex_data->vertexCount;
        }
 
 
        Ogre::IndexData* index_data = submesh->indexData;
        size_t numTris = index_data->indexCount / 3;
        Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;
 
        bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);
 
        unsigned long*  pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
        unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);
 
 
        size_t offset = (submesh->useSharedVertices)? shared_offset : current_offset;
        size_t index_start = index_data->indexStart;
        size_t last_index = numTris*3 + index_start;
 
        if (use32bitindexes)
            for (size_t k = index_start; k < last_index; ++k)
            {
                indices[index_offset++] = pLong[k] + static_cast<unsigned long>( offset );
            }
 
        else
            for (size_t k = index_start; k < last_index; ++k)
            {
                indices[ index_offset++ ] = static_cast<unsigned long>( pShort[k] ) +
                    static_cast<unsigned long>( offset );
            }
 
        ibuf->unlock();
        current_offset = next_offset;
    }
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    //ogre
	//Ogre::Entity *handEnt;//*handEntL, *handEntR;
	if (m_pGlove && fdGetGloveHand(m_pGlove) == FD_HAND_RIGHT)
		handEnt = m_pSceneMgr->createEntity("Hand", "5DTRHand.mesh");
	else
		handEnt = m_pSceneMgr->createEntity("Hand", "5DTRHand.mesh");

	Ogre::AxisAlignedBox handBox = handEnt->getBoundingBox();

	//m_pRoot->loadPlugin("Plugin_CgProgramManager");
	

	engine = createIrrKlangDevice();
	filename = "click2.wav";

	Ogre::Plane plane(Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("plane", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 200, 200, 20, 20, true, 1, 1, 1, Vector3::UNIT_Z);
	Ogre::Entity* entPlane = m_pSceneMgr->createEntity("entPlane", "plane");

	/*
	Ogre::MeshPtr pMesh = MeshManager::getSingleton().load("plane",
           ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,    
           HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY,
           HardwareBuffer::HBU_STATIC_WRITE_ONLY,
           true, true);
		   */

	unsigned short src, dest;
	if (!entPlane->getMesh()->suggestTangentVectorBuildParams(VES_TANGENT, src, dest))
     {
        entPlane->getMesh()->buildTangentVectors(VES_TANGENT, src, dest);
     }
	
	// generate tangent vectors for normal mapping
	//unsigned short src, dest;
	//if (!handEnt->getMesh()->suggestTangentVectorBuildParams(VES_TANGENT, src,dest))
	//	handEnt->getMesh()->buildTangentVectors(VES_TANGENT, src,dest);
	
	HandNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("HandNode",Ogre::Vector3(0,20,0));
	HandNode->setScale(Ogre::Vector3(10,10,10));
	handEnt->setCastShadows(true);
	HandNode->attachObject(handEnt);
	HandNode->showBoundingBox(true);
	
	position << HandNode->getPosition() << std::endl;
	
	//Ogre::SceneNode* node2 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("node2");
	node2 = HandNode->createChildSceneNode("node2");
	node2->translate(0,-0.4,0);
	node2->scale(0.1,0.1,0.1);
	node2->attachObject(entPlane);

	/*
	cube_node = node2->createChildSceneNode("node3");
	cube_node->translate(20,1,-6.0);
	cube_node->scale(2,2,2);
	cube = createCubeMesh("Cube", "Red50");
	cube->setCastShadows(true);
	cube_node->attachObject(cube);
	*/

	/*
	position << node2->_getDerivedPosition() << std::endl;
	position << cube_node->_getDerivedPosition() << std::endl;
	*/

	/*
	ManualObject* myManualObject =  m_pSceneMgr->createManualObject("manual1"); 
	SceneNode* myManualObjectNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("manual1_node"); 
	
	MaterialPtr myManualObjectMaterial = MaterialManager::getSingleton().create("manual1Material",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME); 
	myManualObjectMaterial->setReceiveShadows(false); 
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0,0,1,0); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0,0,1); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,1); 
	//myManualObjectMaterial->unload();
	
	myManualObject->begin("manual1Material", Ogre::RenderOperation::OT_LINE_LIST); 
	myManualObject->position(19.62,17.86,-4.7); 
	myManualObject->position(19.62,23.86,-4.7); 
	// etc 
	myManualObject->end(); 
 
	myManualObjectNode->attachObject(myManualObject);
	
	*/
	entPlane->setMaterialName("Wood");
	//entPlane->setMaterialName("Examples/BumpMapping/MultiLightSpecular");
	//entPlane->setMaterialName("MyMaterial");
	entPlane->setCastShadows(false);

	setupCamera();

    // Set ambient light
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5 ));
	//m_pSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_ADDITIVE);
	m_pSceneMgr->setShadowColour(ColourValue(0.7, 0.7, 0.7));
	m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	//m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);

	/*
	// Allow self shadowing (note: this only works in conjunction with the shaders defined above)
	 m_pSceneMgr->setShadowTextureSelfShadow(true);
	 // Set the caster material which uses the shaders defined above
	 m_pSceneMgr->setShadowTextureCasterMaterial("Ogre/DepthShadowmap/Caster/Float");
	 // Set the pixel format to floating point
	 m_pSceneMgr->setShadowTexturePixelFormat(Ogre::PF_FLOAT32_R);
	 // You can switch this on or off, I suggest you try both and see which works best for you
	 m_pSceneMgr->setShadowCasterRenderBackFaces(false);
	 // Finally enable the shadows using texture additive integrated
	 m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED);
	*/

    // Create a light
//	Ogre::SceneNode* light_node;
//	m_pSceneMgr->getRootSceneNode()->addChild(light_node);
	//light_node->setPosition(0,40,0);

    Ogre::Light* light = m_pSceneMgr->createLight("MainLight");
	light->setType(Ogre::Light::LT_POINT);
	light->setDiffuseColour(Ogre::ColourValue::White);
	light->setSpecularColour(Ogre::ColourValue::White);
    //light->setPosition(65,80,50);
	light->setPosition(0,40,0);
	light->setCastShadows(true);
	//light->setPosition(40,160,100);

	
	Ogre::Light* light2 = m_pSceneMgr->createLight("MainLight2");
	light2->setType(Ogre::Light::LT_POINT);
	light2->setDiffuseColour(Ogre::ColourValue(0.6f, 0.6f, 0.6f, 1.0f));
	light2->setSpecularColour(Ogre::ColourValue::Green);
    //light->setPosition(65,80,50);
	light2->setPosition(10,40,0);
	light2->setCastShadows(true);
	//light->setPosition(40,160,100);
	

	/*
	Ogre::Light* light3 = m_pSceneMgr->createLight("MainLight3");
	light3->setType(Ogre::Light::LT_POINT);
	light3->setDiffuseColour(Ogre::ColourValue(0.4f, 0.4f, 0.4f, 1.0f));
	light3->setSpecularColour(Ogre::ColourValue::Green);
    //light->setPosition(65,80,50);
	light3->setPosition(10,10,-5);
	light3->setCastShadows(true);
	//light->setPosition(40,160,100);
	*/


}

Ogre::ManualObject* TutorialApplication::createCubeMesh(Ogre::String name, Ogre::String matName) {

   Ogre::ManualObject* cube = new ManualObject(name);
   cube->begin(matName);
   
   cube->position(0.5,-0.5,1.0);cube->normal(0.408248,-0.816497,0.408248);cube->textureCoord(1,0);
   cube->position(-0.5,-0.5,0.0);cube->normal(-0.408248,-0.816497,-0.408248);cube->textureCoord(0,1);
   cube->position(0.5,-0.5,0.0);cube->normal(0.666667,-0.333333,-0.666667);cube->textureCoord(1,1);
   cube->position(-0.5,-0.5,1.0);cube->normal(-0.666667,-0.333333,0.666667);cube->textureCoord(0,0);
   cube->position(0.5,0.5,1.0);cube->normal(0.666667,0.333333,0.666667);cube->textureCoord(1,0);
   cube->position(-0.5,-0.5,1.0);cube->normal(-0.666667,-0.333333,0.666667);cube->textureCoord(0,1);
   cube->position(0.5,-0.5,1.0);cube->normal(0.408248,-0.816497,0.408248);cube->textureCoord(1,1);
   cube->position(-0.5,0.5,1.0);cube->normal(-0.408248,0.816497,0.408248);cube->textureCoord(0,0);
   cube->position(-0.5,0.5,0.0);cube->normal(-0.666667,0.333333,-0.666667);cube->textureCoord(0,1);
   cube->position(-0.5,-0.5,0.0);cube->normal(-0.408248,-0.816497,-0.408248);cube->textureCoord(1,1);
   cube->position(-0.5,-0.5,1.0);cube->normal(-0.666667,-0.333333,0.666667);cube->textureCoord(1,0);
   cube->position(0.5,-0.5,0.0);cube->normal(0.666667,-0.333333,-0.666667);cube->textureCoord(0,1);
   cube->position(0.5,0.5,0.0);cube->normal(0.408248,0.816497,-0.408248);cube->textureCoord(1,1);
   cube->position(0.5,-0.5,1.0);cube->normal(0.408248,-0.816497,0.408248);cube->textureCoord(0,0);
   cube->position(0.5,-0.5,0.0);cube->normal(0.666667,-0.333333,-0.666667);cube->textureCoord(1,0);
   cube->position(-0.5,-0.5,0.0);cube->normal(-0.408248,-0.816497,-0.408248);cube->textureCoord(0,0);
   cube->position(-0.5,0.5,1.0);cube->normal(-0.408248,0.816497,0.408248);cube->textureCoord(1,0);
   cube->position(0.5,0.5,0.0);cube->normal(0.408248,0.816497,-0.408248);cube->textureCoord(0,1);
   cube->position(-0.5,0.5,0.0);cube->normal(-0.666667,0.333333,-0.666667);cube->textureCoord(1,1);
   cube->position(0.5,0.5,1.0);cube->normal(0.666667,0.333333,0.666667);cube->textureCoord(0,0);

   cube->triangle(0,1,2);      cube->triangle(3,1,0);
   cube->triangle(4,5,6);      cube->triangle(4,7,5);
   cube->triangle(8,9,10);      cube->triangle(10,7,8);
   cube->triangle(4,11,12);   cube->triangle(4,13,11);
   cube->triangle(14,8,12);   cube->triangle(14,15,8);
   cube->triangle(16,17,18);   cube->triangle(16,19,17);
   cube->end(); 

   return cube;

}

//-------------------------------------------------------------------------------------
// setup intial states of camera
void TutorialApplication::setupCamera()
{
	// create a pivot at roughly the character's shoulder
	m_pCameraPivot = m_pCamera->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	m_pCameraPivot->setPosition(m_pSceneMgr->getSceneNode("HandNode")->getPosition()+Ogre::Vector3(12,0,0));
	//position << m_pCameraPivot->getPosition() << std::endl;

	// this is where the camera should be soon, and it spins around the pivot
	m_pCameraGoal = m_pCameraPivot->createChildSceneNode(Vector3(0, 0, 30));
	//position << m_pCameraGoal->getPosition() << std::endl;

	// this is where the camera actually is
	m_pCameraNode = m_pCamera->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	m_pCameraNode->setPosition(m_pCameraPivot->getPosition() + m_pCameraGoal->getPosition());
	//position << m_pCameraNode->getPosition() << std::endl;

	m_pCameraPivot->setFixedYawAxis(true);
	m_pCameraGoal->setFixedYawAxis(true);
	m_pCameraNode->setFixedYawAxis(true);

	// our model is quite small, so reduce the clipping planes
	//m_pCamera->setNearClipDistance(0.1);
	//m_pCamera->setFarClipDistance(100);
	m_pCameraNode->attachObject(m_pCamera);

	m_fPivotPitch = 0;

	if (m_pGlove && fdGetGloveHand(m_pGlove) == FD_HAND_RIGHT)
		updateCameraGoal(135, -45, 10);
	else
		updateCameraGoal(45, -45, 10);

	//position << m_pCameraGoal->getPosition() << std::endl;
	//position << m_pCamera->getDirection() << std::endl;
}

//-------------------------------------------------------------------------------------
// Execute while waiting for the GPU to flip the buffers
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	// call the base class method
	if (!BaseApplication::frameRenderingQueued(evt))
		return false;

	// update the camera
	UpdateCam(evt.timeSinceLastFrame);

	// update FPS display
	std::stringstream sFPStemp;
	sFPStemp<<m_pWindow->getAverageFPS();
	m_ptxtFPS->setCaption(sFPStemp.str());

	//if (Light* light = m_pSceneMgr->getLight("MainLight"))
	//{
	//	light->setPosition(m_pCamera->getDerivedPosition() + m_pCamera->getDerivedUp() * 20.0);
	//	light->setDirection(m_pCamera->getDerivedDirection());
	//}

	// update the glove, and if it is not connected, try to connect
	static float time = 2;
	static float activitytime = 0;
	
	time += evt.timeSinceLastFrame;
	activitytime += evt.timeSinceLastFrame;

	/*
	if(distort_color_response)
	{
		curr_time += evt.timeSinceLastFrame;
	}

	if(curr_time > distortion_time)
	{
		distort_color_response = false;
	}
	*/

	// if no activity for 1 second: reset glove
	if (m_pGlove && activitytime>1) // && !fdNewData(m_pGlove)
	{
		fdClose(m_pGlove);
		m_pGlove = 0;
		activitytime = -10; // allow 10 seconds to load glove
	}
	else if (m_pGlove && fdNewData(m_pGlove))
		activitytime = 0;


	if (m_pGlove)
	{
		if (fdGetGloveType(m_pGlove)==FD_GLOVE14U || 
			fdGetGloveType(m_pGlove) == FD_GLOVE14UW ||
			fdGetGloveType(m_pGlove) == FD_GLOVE14U_USB)
				Update14SensorGlove();
		else
			Update5SensorGlove();
	}
	else if (time>1) // check for connection each second
	{
		time = 0;
		ConnectGlove();

		if (m_pGlove)
		{
			m_pSceneMgr->destroyEntity("Hand");
			if (fdGetGloveHand(m_pGlove) == FD_HAND_RIGHT)
				m_pSceneMgr->createEntity("Hand", "5DTRHand.mesh");
			else
				m_pSceneMgr->createEntity("Hand", "5DTLHand.mesh");

			m_pSceneMgr->getSceneNode("HandNode")->attachObject(m_pSceneMgr->getEntity("Hand"));
		}
	}

	// update sensor information in the calibration gui
	if (m_pGlove)
	{
		std::stringstream sTemp;
		sTemp<<fdGetSensorRaw(m_pGlove, m_iCurrentSensor);
		m_ptxtRawVal->setCaption(sTemp.str());
		
		sTemp.str("");
		sTemp.precision(3);
		sTemp.setf(std::ios::fixed,std::ios::floatfield);
		sTemp<<fdGetSensorScaled(m_pGlove, m_iCurrentSensor);
		m_ptxtScaledVal->setCaption(sTemp.str());

		unsigned short MaxVal, MinVal;
		fdGetCalibration(m_pGlove, m_iCurrentSensor, &MaxVal, &MinVal);
		sTemp.str("");
		sTemp<<MaxVal;			
		m_ptxtMaxCal->setCaption(sTemp.str());
		
		sTemp.str("");
		sTemp<<MinVal;
		m_ptxtMinCal->setCaption(sTemp.str());
	}
	return true;
}

void wndCloseCrossPressed(MyGUI::WidgetPtr _widget, const std::string& _name)
{
	if (_name == "close") _widget->castType<MyGUI::Window>()->setVisibleSmooth(false);
}

void CloseWindow_Click(MyGUI::WidgetPtr _sender)
{
	_sender->getParent()->getParent()->castType<MyGUI::Window>()->setVisibleSmooth(false);
}

// --------------------------------------------------------------------------------------------
// save the calibration file
void TutorialApplication::btnSaveCalib_Click(MyGUI::WidgetPtr _sender)
{
	char cSerial[50];
	fdGetSerialNumber(m_pGlove, cSerial);
	std::string sFileName(cSerial);
	sFileName += ".fd";
	if (fdSaveCalibration(m_pGlove,sFileName.c_str()))

	MyGUI::Message::createMessageBox("Message", "Calibration Successfully Saved", "Current calibration information will be used the next time this glove is connected", MyGUI::MessageBoxStyle::IconInfo | MyGUI::MessageBoxStyle::Ok);

}

// --------------------------------------------------------------------------------------------
// handle the state of the advanced calibration window checkboxes - switches the state
void TutorialApplication::CalibCheckBox_Click(MyGUI::WidgetPtr _sender)
{
	m_pGUI->findWidget<MyGUI::Button>("chkSensor0")->setButtonPressed(false);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor1")->setButtonPressed(false);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor2")->setButtonPressed(false);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor3")->setButtonPressed(false);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor4")->setButtonPressed(false);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor5")->setButtonPressed(false);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor6")->setButtonPressed(false);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor7")->setButtonPressed(false);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor8")->setButtonPressed(false);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor9")->setButtonPressed(false);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor10")->setButtonPressed(false);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor11")->setButtonPressed(false);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor12")->setButtonPressed(false);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor13")->setButtonPressed(false);
		
	// flip the pressed state of the current checkbox
	_sender->castType<MyGUI::Button>()->setButtonPressed(!_sender->castType<MyGUI::Button>()->getButtonPressed());
	
	std::string a = _sender->getUserString("Index");
	m_iCurrentSensor = atoi(a.c_str());
}

// --------------------------------------------------------------------------------------------
// general function for all checkboxes - switches the state
void CheckBox_Click(MyGUI::WidgetPtr _sender)
{
	_sender->castType<MyGUI::Button>()->setButtonPressed(!_sender->castType<MyGUI::Button>()->getButtonPressed());
}

// --------------------------------------------------------------------------------------------
// show calibration settings window
void TutorialApplication::btnCalibrate_Click(MyGUI::WidgetPtr _sender)
{
	if (m_pGlove)
		m_pGUI->findWidget<MyGUI::Window>("wndCalibration")->setVisibleSmooth(true);
	else
		MyGUI::Message::createMessageBox("Message", "Error", "No Glove Connected", MyGUI::MessageBoxStyle::IconError | MyGUI::MessageBoxStyle::Ok);
}

// --------------------------------------------------------------------------------------------
// show graphics settings window
void TutorialApplication::btnGraphicsSettings_Click(MyGUI::WidgetPtr _sender)
{
	m_pGUI->findWidget<MyGUI::Window>("wndGraphicsSettings")->setVisibleSmooth(true);
}

// --------------------------------------------------------------------------------------------
// set calibration for a specific sensor: Min sensor value
void TutorialApplication::btnCalSetMin_Click(MyGUI::WidgetPtr _sender)
{
	unsigned short Lower, Upper;

	fdGetCalibration(m_pGlove, m_iCurrentSensor, &Upper, &Lower);
	fdSetCalibration(m_pGlove, m_iCurrentSensor, Upper, fdGetSensorRaw(m_pGlove, m_iCurrentSensor));
}

// --------------------------------------------------------------------------------------------
// set calibration for a specific sensor: Max sensor value
void TutorialApplication::btnCalSetMax_Click(MyGUI::WidgetPtr _sender)
{
	unsigned short Lower, Upper;

	fdGetCalibration(m_pGlove, m_iCurrentSensor, &Upper, &Lower);
	fdSetCalibration(m_pGlove, m_iCurrentSensor, fdGetSensorRaw(m_pGlove, m_iCurrentSensor), Lower);
}

// this function is called after the base application has finished with setup
void TutorialApplication::setup_finished(void)
{
	setupMyGUI();
}

// --------------------------------------------------------------------------------------------
// set calibration for fist pose
void TutorialApplication::btnFistCalib_Click(MyGUI::WidgetPtr _sender)
{
	bool bIs14SensorGlove = false;
	if (fdGetGloveType(m_pGlove)==FD_GLOVE14U || 
		fdGetGloveType(m_pGlove) == FD_GLOVE14UW ||
		fdGetGloveType(m_pGlove) == FD_GLOVE14U_USB)
	{
		bIs14SensorGlove = true;
	}

	unsigned short pCurrentData[20];
	unsigned short pLower[20];
	unsigned short pUpper[20];
	fdGetSensorRawAll(m_pGlove, pCurrentData);
	fdGetCalibrationAll(m_pGlove, pUpper, pLower);
		
	if (!bIs14SensorGlove)
		fdSetCalibrationAll(m_pGlove, pCurrentData, pLower);
	else
	{
		for (int i = 0; i<20; i++)
			if (i!=FD_THUMBINDEX && i != FD_INDEXMIDDLE && i != FD_MIDDLERING && i != FD_RINGLITTLE)
				fdSetCalibration(m_pGlove, i, pCurrentData[i], pLower[i]);
	}
}

// --------------------------------------------------------------------------------------------
// set calibration for open hand pose
void TutorialApplication::btnOpenHandCalib_Click(MyGUI::WidgetPtr _sender)
{
	bool bIs14SensorGlove = false;
	if (fdGetGloveType(m_pGlove)==FD_GLOVE14U || 
		fdGetGloveType(m_pGlove) == FD_GLOVE14UW ||
		fdGetGloveType(m_pGlove) == FD_GLOVE14U_USB)
	{
		bIs14SensorGlove = true;
	}

	unsigned short pCurrentData[20];
	unsigned short pLower[20];
	unsigned short pUpper[20];
	fdGetSensorRawAll(m_pGlove, pCurrentData);
	fdGetCalibrationAll(m_pGlove, pUpper, pLower);
		
	if (!bIs14SensorGlove)
		fdSetCalibrationAll(m_pGlove, pUpper, pCurrentData);
	else
	{
		for (int i = 0; i<20; i++)
			if (i!=FD_THUMBINDEX && i != FD_INDEXMIDDLE && i != FD_MIDDLERING && i != FD_RINGLITTLE)
				fdSetCalibration(m_pGlove, i, pUpper[i], pCurrentData[i]);
	}
}

// --------------------------------------------------------------------------------------------
// set calibration for flat hand
void TutorialApplication::btnFlatHandCalib_Click(MyGUI::WidgetPtr _sender)
{
	unsigned short pLower[20];
	unsigned short pUpper[20];
	fdGetCalibrationAll(m_pGlove, pUpper, pLower);

	fdSetCalibration(m_pGlove, FD_THUMBINDEX, fdGetSensorRaw(m_pGlove,FD_THUMBINDEX), pLower[FD_THUMBINDEX]);
	fdSetCalibration(m_pGlove, FD_INDEXMIDDLE, fdGetSensorRaw(m_pGlove,FD_INDEXMIDDLE), pLower[FD_INDEXMIDDLE]);
	fdSetCalibration(m_pGlove, FD_MIDDLERING, fdGetSensorRaw(m_pGlove,FD_MIDDLERING), pLower[FD_MIDDLERING]);
	fdSetCalibration(m_pGlove, FD_RINGLITTLE, fdGetSensorRaw(m_pGlove,FD_RINGLITTLE), pLower[FD_RINGLITTLE]);
}

// --------------------------------------------------------------------------------------------
// set calibration for spread fingers pose
void TutorialApplication::btnSpreadFingersCalib_Click(MyGUI::WidgetPtr _sender)
{
	unsigned short pLower[20];
	unsigned short pUpper[20];
	fdGetCalibrationAll(m_pGlove, pUpper, pLower);

	fdSetCalibration(m_pGlove, FD_THUMBINDEX, pUpper[FD_THUMBINDEX], fdGetSensorRaw(m_pGlove,FD_THUMBINDEX));
	fdSetCalibration(m_pGlove, FD_INDEXMIDDLE, pUpper[FD_INDEXMIDDLE], fdGetSensorRaw(m_pGlove,FD_INDEXMIDDLE));
	fdSetCalibration(m_pGlove, FD_MIDDLERING, pUpper[FD_MIDDLERING], fdGetSensorRaw(m_pGlove,FD_MIDDLERING));
	fdSetCalibration(m_pGlove, FD_RINGLITTLE, pUpper[FD_RINGLITTLE], fdGetSensorRaw(m_pGlove,FD_RINGLITTLE));
}

// --------------------------------------------------------------------------------------------
// Apply button clicked from the Graphics Swttings Window
void TutorialApplication::ApplyGraphicsSettings_Click(MyGUI::WidgetPtr _sender)
{
	std::string sCurResOption = m_pGUI->findWidget<MyGUI::ComboBox>("cmbResolution")->getCaption();
	std::string sCurAAOption = m_pGUI->findWidget<MyGUI::ComboBox>("cmbAA")->getCaption();
	
	std::string sWidth = sCurResOption.substr(0, sCurResOption.find('x')-1);
	std::string sHeight = sCurResOption.substr(sCurResOption.find('x') + 1,sCurResOption.find(' ',sCurResOption.find('x') + 1));
	
	bool bFullscreen = m_pGUI->findWidget<MyGUI::Button>("chkFullScreen")->getButtonPressed();

	if (sCurResOption!="Select Resolution")
		m_pRoot->getRenderSystem()->setConfigOption("Video Mode",sCurResOption);
	m_pRoot->getRenderSystem()->setConfigOption("FSAA",sCurAAOption);
	m_pRoot->getRenderSystem()->setConfigOption("Full Screen",bFullscreen ? "Yes": "No");
	m_pRoot->saveConfig();
	
	m_pGUI->findWidget<MyGUI::Window>("wndGraphicsSettings")->setVisibleSmooth(false);
	MyGUI::Message::createMessageBox("Message", "Graphics settings saved", "Graphics settings will be applied on next application start.", MyGUI::MessageBoxStyle::IconInfo | MyGUI::MessageBoxStyle::Ok);

}

// --------------------------------------------------------------------------------------------
// Reset button pressed from Advanced Calibration Window
void TutorialApplication::btnCalibReset_Click(MyGUI::WidgetPtr _sender)
{
	fdResetCalibration(m_pGlove);
}

// --------------------------------------------------------------------------------------------
// Show to save file dialogue
void TutorialApplication::btnSaveCal_Click(MyGUI::WidgetPtr _sender)
{
	mOpenSaveFileDialog->setVisible(true);	
}

//---------------------------------------------------------------------------------------------
// Export current calibration configuration
void TutorialApplication::notifyOpenSaveEndDialog(bool _result)
{
	if (_result)
	{
		std::string sFileName = mOpenSaveFileDialog->getFullPath();
		if (sFileName.find(".fd")==-1)
			sFileName.append(".fd");
		if (fdSaveCalibration(m_pGlove,sFileName.c_str()))
			MyGUI::Message::createMessageBox("Message", "Calibration File", "Calibration successfully exported", MyGUI::MessageBoxStyle::IconInfo | MyGUI::MessageBoxStyle::Ok);
		else
			MyGUI::Message::createMessageBox("Message", "Error", "Calibration file could not be exported", MyGUI::MessageBoxStyle::IconError | MyGUI::MessageBoxStyle::Ok);
		mOpenSaveFileDialog->setVisible(false);
	}
	else
	{
		mOpenSaveFileDialog->setVisible(false);
	}
}

// --------------------------------------------------------------------------------------------
// Setup MyGUI elements
void TutorialApplication::setupMyGUI(void)
{
	m_pPlatform = new MyGUI::OgrePlatform();
	m_pPlatform->initialise(m_pWindow, m_pSceneMgr); // mWindow is Ogre::RenderWindow*, mSceneManager is Ogre::SceneManager*
	m_pGUI = new MyGUI::Gui();
	m_pGUI->initialise();

	// load black/blue theme
	MyGUI::LanguageManager::getInstance().loadUserTags("core_theme_black_blue_tag.xml");
	m_pGUI->load("core_skin.xml");

	// load layout
	
	MyGUI::LayoutManager::getInstance().load("GloveDemoMainMenu.layout");
	MyGUI::ResourceManager::getInstance().load("ButtonImage.resource");
	MyGUI::LayoutManager::getInstance().load("GloveDemoCalibrationWindow.layout");
	

	// Set gui properties
	// main screen
	/*
	m_pGUI->findWidget<MyGUI::Button>("btnAbout")->eventMouseButtonClick = MyGUI::newDelegate(this, &TutorialApplication::btnAbout_Click);
	m_pGUI->findWidget<MyGUI::Button>("btnCalibrate")->eventMouseButtonClick = MyGUI::newDelegate(this, &TutorialApplication::btnCalibrate_Click);
	m_pGUI->findWidget<MyGUI::Button>("btnGraphicsSettings")->eventMouseButtonClick = MyGUI::newDelegate(this, &TutorialApplication::btnGraphicsSettings_Click);
	m_pGUI->findWidget<MyGUI::Button>("btnSaveCal")->eventMouseButtonClick = MyGUI::newDelegate(this, &TutorialApplication::btnSaveCal_Click);
	m_pGUI->findWidget<MyGUI::Button>("btnExit")->eventMouseButtonClick = MyGUI::newDelegate(this, &TutorialApplication::btnExit_Click);
	*/
	m_pGUI->findWidget<MyGUI::Widget>("pnlFPS")->setVisible(false);
	m_ptxtFPS = m_pGUI->findWidget<MyGUI::StaticText>("txtFPS");
	

	m_pGUI->findWidget<MyGUI::Button>("btnAbout")->setVisible(false);
	m_pGUI->findWidget<MyGUI::Button>("btnCalibrate")->setVisible(false);
	m_pGUI->findWidget<MyGUI::Button>("btnGraphicsSettings")->setVisible(false);
	m_pGUI->findWidget<MyGUI::Button>("btnSaveCal")->setVisible(false);
	m_pGUI->findWidget<MyGUI::Button>("btnExit")->setVisible(false);

	// about window
	
	MyGUI::WindowPtr pAboutWindow = m_pGUI->findWidget<MyGUI::Window>("wndAbout");
	pAboutWindow->setVisible(false);
	pAboutWindow->eventWindowButtonPressed = MyGUI::newDelegate(wndCloseCrossPressed);
	pAboutWindow->setPosition(m_pWindow->getWidth()/2.f - pAboutWindow->getWidth()/2.f ,m_pWindow->getHeight()/2.f - pAboutWindow->getHeight()/2.f);
	m_pGUI->findWidget<MyGUI::Button>("btnAboutExit")->eventMouseButtonClick = MyGUI::newDelegate(CloseWindow_Click);

	//Color response window
	
	MyGUI::WindowPtr pColorEnableWindow = m_pGUI->findWidget<MyGUI::Window>("wndColorEnable");
	pColorEnableWindow->setVisible(false);
	pColorEnableWindow->eventWindowButtonPressed = MyGUI::newDelegate(wndCloseCrossPressed);
	pColorEnableWindow->setPosition(m_pWindow->getWidth()/2.f - pColorEnableWindow->getWidth()/2.f ,m_pWindow->getHeight()/2.f - pColorEnableWindow->getHeight()/2.f);
	m_pGUI->findWidget<MyGUI::Button>("btnColorEnableExit")->eventMouseButtonClick = MyGUI::newDelegate(CloseWindow_Click);

	MyGUI::WindowPtr pColorDisableWindow = m_pGUI->findWidget<MyGUI::Window>("wndColorDisable");
	pColorDisableWindow->setVisible(false);
	pColorDisableWindow->eventWindowButtonPressed = MyGUI::newDelegate(wndCloseCrossPressed);
	pColorDisableWindow->setPosition(m_pWindow->getWidth()/2.f - pColorDisableWindow->getWidth()/2.f ,m_pWindow->getHeight()/2.f - pColorDisableWindow->getHeight()/2.f);
	m_pGUI->findWidget<MyGUI::Button>("btnColorDisableExit")->eventMouseButtonClick = MyGUI::newDelegate(CloseWindow_Click);
	
	MyGUI::WindowPtr pSoundEnableWindow = m_pGUI->findWidget<MyGUI::Window>("wndSoundEnable");
	pSoundEnableWindow->setVisible(false);
	pSoundEnableWindow->eventWindowButtonPressed = MyGUI::newDelegate(wndCloseCrossPressed);
	pSoundEnableWindow->setPosition(m_pWindow->getWidth()/2.f - pSoundEnableWindow->getWidth()/2.f ,m_pWindow->getHeight()/2.f - pSoundEnableWindow->getHeight()/2.f);
	m_pGUI->findWidget<MyGUI::Button>("btnSoundEnableExit")->eventMouseButtonClick = MyGUI::newDelegate(CloseWindow_Click);

	MyGUI::WindowPtr pSoundDisableWindow = m_pGUI->findWidget<MyGUI::Window>("wndSoundDisable");
	pSoundDisableWindow->setVisible(false);
	pSoundDisableWindow->eventWindowButtonPressed = MyGUI::newDelegate(wndCloseCrossPressed);
	pSoundDisableWindow->setPosition(m_pWindow->getWidth()/2.f - pSoundDisableWindow->getWidth()/2.f ,m_pWindow->getHeight()/2.f - pSoundDisableWindow->getHeight()/2.f);
	m_pGUI->findWidget<MyGUI::Button>("btnSoundDisableExit")->eventMouseButtonClick = MyGUI::newDelegate(CloseWindow_Click);

	MyGUI::WindowPtr pCubeWindow = m_pGUI->findWidget<MyGUI::Window>("wndCube");
	pCubeWindow->setVisible(false);
	pCubeWindow->eventWindowButtonPressed = MyGUI::newDelegate(wndCloseCrossPressed);
	pCubeWindow->setPosition(m_pWindow->getWidth()/2.f - pCubeWindow->getWidth()/2.f ,m_pWindow->getHeight()/2.f - pCubeWindow->getHeight()/2.f);
	m_pGUI->findWidget<MyGUI::Button>("btnCubeExit")->eventMouseButtonClick = MyGUI::newDelegate(CloseWindow_Click);

	// calibration window
	MyGUI::WindowPtr pCalibWindow = m_pGUI->findWidget<MyGUI::Window>("wndCalibration");
	pCalibWindow->setVisible(false);
	pCalibWindow->eventWindowButtonPressed = MyGUI::newDelegate(wndCloseCrossPressed);
	m_pGUI->findWidget<MyGUI::Button>("btnAdvCalibration")->eventMouseButtonClick = MyGUI::newDelegate(this, &TutorialApplication::btnAdvCalib_Click);
	m_pGUI->findWidget<MyGUI::Button>("btnCalibOK")->eventMouseButtonClick = MyGUI::newDelegate(CloseWindow_Click);
	m_pGUI->findWidget<MyGUI::Button>("btnCalibSave")->eventMouseButtonClick = MyGUI::newDelegate(this, &TutorialApplication::btnSaveCalib_Click);
	m_pGUI->findWidget<MyGUI::Button>("picFist")->eventMouseButtonClick = MyGUI::newDelegate(this, &TutorialApplication::btnFistCalib_Click);
	m_pGUI->findWidget<MyGUI::Button>("picOpenHand")->eventMouseButtonClick = MyGUI::newDelegate(this, &TutorialApplication::btnOpenHandCalib_Click);
	m_pGUI->findWidget<MyGUI::Button>("picSpreadFingers")->eventMouseButtonClick = MyGUI::newDelegate(this, &TutorialApplication::btnSpreadFingersCalib_Click);
	m_pGUI->findWidget<MyGUI::Button>("picFlatHand")->eventMouseButtonClick = MyGUI::newDelegate(this, &TutorialApplication::btnFlatHandCalib_Click);


	// advanced calibration window
	MyGUI::WindowPtr pAdvCalibWindow = m_pGUI->findWidget<MyGUI::Window>("wndAdvCalibration");
	pAdvCalibWindow->setVisible(false);
	pAdvCalibWindow->eventWindowButtonPressed = MyGUI::newDelegate(wndCloseCrossPressed);
	pAdvCalibWindow->setPosition(m_pWindow->getWidth()/2.f - pAdvCalibWindow->getWidth()/2.f ,m_pWindow->getHeight()/2.f - pAdvCalibWindow->getHeight()/2.f);
	pCalibWindow->setPosition(m_pWindow->getWidth()/2.f - pAdvCalibWindow->getWidth()/2.f ,m_pWindow->getHeight()/2.f - pAdvCalibWindow->getHeight()/2.f);
	m_pGUI->findWidget<MyGUI::Button>("btnCalSetMax")->eventMouseButtonClick = MyGUI::newDelegate(this, &TutorialApplication::btnCalSetMax_Click);
	m_pGUI->findWidget<MyGUI::Button>("btnCalSetMin")->eventMouseButtonClick = MyGUI::newDelegate(this, &TutorialApplication::btnCalSetMin_Click);
	m_pGUI->findWidget<MyGUI::Button>("btnAdvCalibOK")->eventMouseButtonClick = MyGUI::newDelegate(CloseWindow_Click);
	m_pGUI->findWidget<MyGUI::Button>("btnAdvCalibSave")->eventMouseButtonClick = MyGUI::newDelegate(this, &TutorialApplication::btnSaveCalib_Click);
	m_pGUI->findWidget<MyGUI::Button>("btnCalibReset")->eventMouseButtonClick = MyGUI::newDelegate(this, &TutorialApplication::btnCalibReset_Click);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor0")->eventMouseButtonClick =  MyGUI::newDelegate(this, &TutorialApplication::CalibCheckBox_Click);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor1")->eventMouseButtonClick =  MyGUI::newDelegate(this, &TutorialApplication::CalibCheckBox_Click);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor1")->setButtonPressed(true);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor2")->eventMouseButtonClick =  MyGUI::newDelegate(this, &TutorialApplication::CalibCheckBox_Click);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor3")->eventMouseButtonClick =  MyGUI::newDelegate(this, &TutorialApplication::CalibCheckBox_Click);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor4")->eventMouseButtonClick =  MyGUI::newDelegate(this, &TutorialApplication::CalibCheckBox_Click);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor5")->eventMouseButtonClick =  MyGUI::newDelegate(this, &TutorialApplication::CalibCheckBox_Click);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor6")->eventMouseButtonClick =  MyGUI::newDelegate(this, &TutorialApplication::CalibCheckBox_Click);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor7")->eventMouseButtonClick =  MyGUI::newDelegate(this, &TutorialApplication::CalibCheckBox_Click);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor8")->eventMouseButtonClick =  MyGUI::newDelegate(this, &TutorialApplication::CalibCheckBox_Click);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor9")->eventMouseButtonClick =  MyGUI::newDelegate(this, &TutorialApplication::CalibCheckBox_Click);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor10")->eventMouseButtonClick =  MyGUI::newDelegate(this, &TutorialApplication::CalibCheckBox_Click);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor11")->eventMouseButtonClick =  MyGUI::newDelegate(this, &TutorialApplication::CalibCheckBox_Click);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor12")->eventMouseButtonClick =  MyGUI::newDelegate(this, &TutorialApplication::CalibCheckBox_Click);
	m_pGUI->findWidget<MyGUI::Button>("chkSensor13")->eventMouseButtonClick =  MyGUI::newDelegate(this, &TutorialApplication::CalibCheckBox_Click);
	m_ptxtRawVal = m_pGUI->findWidget<MyGUI::StaticText>("txtRawVal");
	m_ptxtScaledVal = m_pGUI->findWidget<MyGUI::StaticText>("txtScaledVal");
	m_ptxtMaxCal = m_pGUI->findWidget<MyGUI::StaticText>("txtMaxCal");
	m_ptxtMinCal = m_pGUI->findWidget<MyGUI::StaticText>("txtMinCal");
	
	// Graphics settings window
	MyGUI::WindowPtr pGraphicsOptionsWindow = m_pGUI->findWidget<MyGUI::Window>("wndGraphicsSettings");
	pGraphicsOptionsWindow->setVisible(false);
	pGraphicsOptionsWindow->eventWindowButtonPressed = MyGUI::newDelegate(wndCloseCrossPressed);
	pGraphicsOptionsWindow->setPosition(m_pWindow->getWidth()/2.f - pGraphicsOptionsWindow->getWidth()/2.f ,m_pWindow->getHeight()/2.f - pGraphicsOptionsWindow->getHeight()/2.f);
	m_pGUI->findWidget<MyGUI::Button>("btnGraphicsOptionsApply")->eventMouseButtonClick = MyGUI::newDelegate(this, &TutorialApplication::ApplyGraphicsSettings_Click);
	m_pGUI->findWidget<MyGUI::Button>("chkFullScreen")->eventMouseButtonClick = MyGUI::newDelegate(CheckBox_Click);
	m_pGUI->findWidget<MyGUI::Button>("chkFullScreen")->setButtonPressed(m_pWindow->isFullScreen());
	
	MyGUI::ComboBoxPtr pResolutionsCombo = m_pGUI->findWidget<MyGUI::ComboBox>("cmbResolution");
	const Ogre::StringVector& videoModes = m_pRoot->getRenderSystem()->getConfigOptions()["Video Mode"].possibleValues;
	//pResolutionsCombo->addText("800 x 600");
	pResolutionsCombo->addItem("800 x 600 @ 32-bit colour");
	pResolutionsCombo->addItem("1024 x 768 @ 32-bit colour");
	pResolutionsCombo->addItem("1280 x 1024 @ 32-bit colour");
	pResolutionsCombo->addText("Select Resolution");
	//pResolutionsCombo->addText(Ogre::StringConverter::toString(m_pWindow->getWidth()) + " x " + Ogre::StringConverter::toString(m_pWindow->getHeight()) + " @ 32-bit");
	//for (Ogre::StringVector::const_iterator i=videoModes.begin(); i!=videoModes.end(); i++)
	//	pResolutionsCombo->addItem(*i);

	MyGUI::ComboBoxPtr pAACombo = m_pGUI->findWidget<MyGUI::ComboBox>("cmbAA");
	const Ogre::StringVector& AAModes = m_pRoot->getRenderSystem()->getConfigOptions()["FSAA"].possibleValues;
	pAACombo->addText(Ogre::StringConverter::toString(m_pWindow->getFSAA()));
	//pAACombo->addText("Select Anti Aliasing Level");
	for (Ogre::StringVector::const_iterator i=AAModes.begin(); i!=AAModes.end(); i++)
		pAACombo->addItem(*i);

	// save calibration file dialog
	mOpenSaveFileDialog = new common::OpenSaveFileDialog();
	mOpenSaveFileDialog->setVisible(false);
	mOpenSaveFileDialog->setDialogInfo("Save Calibration File","Save");
	mOpenSaveFileDialog->setFileMask("*.fd");
	mOpenSaveFileDialog->eventEndDialog = MyGUI::newDelegate(this, &TutorialApplication::notifyOpenSaveEndDialog);
	
}

// ----------------------------------------------------------------------------------------
// Advanced button clicked in calibration configuration window
void TutorialApplication::btnAdvCalib_Click(MyGUI::WidgetPtr _sender)
{
	m_pGUI->findWidget<MyGUI::Window>("wndAdvCalibration")->setVisibleSmooth(true);
	m_pGUI->findWidget<MyGUI::Window>("wndCalibration")->setVisibleSmooth(false);
}

// ----------------------------------------------------------------------------------------
// About button clicked in the main menu
void TutorialApplication::btnAbout_Click(MyGUI::WidgetPtr _sender)
{
	m_pGUI->findWidget<MyGUI::Window>("wndAbout")->setVisibleSmooth(true);	
}

// ----------------------------------------------------------------------------------------
// Close about window
void TutorialApplication::wndAboutButtonPressed(MyGUI::WidgetPtr _widget, const std::string& _name)
{
	std::string name = _name;

	if (_name == "close") _widget->castType<MyGUI::Window>()->setVisibleSmooth(false);
}

// ----------------------------------------------------------------------------------------
// Exit button clicked in the main menu
void TutorialApplication::btnExit_Click(MyGUI::WidgetPtr _sender)
{
	m_bShutDown = true;
}

// ----------------------------------------------------------------------------------------
// Load the correct calibration gui for the current glove
void TutorialApplication::loadCalibrationGui(bool b5SensorGlove)
{
	if (b5SensorGlove)
	{
		m_pGUI->findWidget<MyGUI::Window>("wndCalibration")->setSize(445,360);
		m_pGUI->findWidget<MyGUI::Widget>("picSpreadFingers")->setVisible(false);
		m_pGUI->findWidget<MyGUI::Widget>("picFlatHand")->setVisible(false);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor0")->setVisible(false);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor2")->setVisible(false);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor3")->setVisible(false);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor5")->setVisible(false);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor6")->setVisible(false);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor8")->setVisible(false);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor9")->setVisible(false);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor11")->setVisible(false);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor12")->setVisible(false);
	}
	else
	{
		m_pGUI->findWidget<MyGUI::Window>("wndCalibration")->setSize(445,560);
		m_pGUI->findWidget<MyGUI::Widget>("picSpreadFingers")->setVisible(true);
		m_pGUI->findWidget<MyGUI::Widget>("picFlatHand")->setVisible(true);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor0")->setVisible(true);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor2")->setVisible(true);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor3")->setVisible(true);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor5")->setVisible(true);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor6")->setVisible(true);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor8")->setVisible(true);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor9")->setVisible(true);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor11")->setVisible(true);
		m_pGUI->findWidget<MyGUI::Widget>("chkSensor12")->setVisible(true);
	}
}

//-------------------------------------------------------------------------------------
// OIS::KeyListener
bool TutorialApplication::keyPressed( const OIS::KeyEvent& evt )
{
	static std::string curMaterial = "basic1";

	BaseApplication::keyPressed(evt);
	
	m_pGUI->injectKeyPress(MyGUI::KeyCode::Enum(evt.key), evt.text);

	switch (evt.key)
    {
		case OIS::KC_C:
			if(color_response)
			{
				color_response = false;
				m_pGUI->findWidget<MyGUI::Window>("wndColorDisable")->setVisibleSmooth(true);
			}
			else
			{
				color_response = true;
				m_pGUI->findWidget<MyGUI::Window>("wndColorEnable")->setVisibleSmooth(true);
			}
			break;
		case OIS::KC_D:
			build_cube = true;
			m_pGUI->findWidget<MyGUI::Window>("wndCube")->setVisibleSmooth(true);
			cube_node = node2->createChildSceneNode("node3");
			cube_node->translate(20,1,-6.0);
			cube_node->scale(2,2,2);
			cube = createCubeMesh("Cube", "Red50");
			cube->setCastShadows(true);
			cube_node->attachObject(cube);
			break;
		case OIS::KC_S:
			if(sound_response)
			{
				sound_response = false;
				m_pGUI->findWidget<MyGUI::Window>("wndSoundDisable")->setVisibleSmooth(true);
			}
			else
			{
				sound_response = true;
				m_pGUI->findWidget<MyGUI::Window>("wndSoundEnable")->setVisibleSmooth(true);
			}
			break;
		case OIS::KC_1:
			if(distort_color_response)
				distort_color_response = false;
			else
				distort_color_response = true;
			curr_time = 0;
			break;
		case OIS::KC_2:
			if(distort_sound_response)
				distort_sound_response = false;
			else
				distort_sound_response = true;
			curr_time = 0;
			break;
		case OIS::KC_F:   // toggle visibility of advanced frame stats
		{
			MyGUI::WidgetPtr pPnl = m_pGUI->findWidget<MyGUI::Widget>("pnlFPS");
			if (pPnl->isVisible())
				pPnl->setVisible(false);
			else
				pPnl->setVisible(true);
		}

		case OIS::KC_F1:
			m_pGUI->findWidget<MyGUI::Window>("wndAbout")->setVisibleSmooth(true);
			break;
		case OIS::KC_Z:
			{
				if (m_pGlove)
					m_pGUI->findWidget<MyGUI::Window>("wndCalibration")->setVisibleSmooth(true);
				else
					MyGUI::Message::createMessageBox("Message", "Error", "No Glove Connected", MyGUI::MessageBoxStyle::IconError | MyGUI::MessageBoxStyle::Ok);
			}

		case OIS::KC_Y:
			{
				char cSerial[50];
				fdGetSerialNumber(m_pGlove, cSerial);
				std::string sFileName(cSerial);
				sFileName += ".fd";
				fdSaveCalibration(m_pGlove,sFileName.c_str());
			}
		default:
			break;
    }
    return true;
}

//-------------------------------------------------------------------------------------
bool TutorialApplication::keyReleased( const OIS::KeyEvent& evt )
{
	BaseApplication::keyReleased(evt);
	m_pGUI->injectKeyRelease(MyGUI::KeyCode::Enum(evt.key));
    return true;
}

//-------------------------------------------------------------------------------------
// OIS::MouseListener
bool TutorialApplication::mouseMoved( const OIS::MouseEvent& evt )
{
	m_pGUI->injectMouseMove(evt.state.X.abs, evt.state.Y.abs, evt.state.Z.abs);

	if (evt.state.buttonDown(OIS::MB_Right))
	{
		m_pGUI->setVisiblePointer(false);
		updateCameraGoal(-0.40f * evt.state.X.rel, -0.40f * evt.state.Y.rel, -0.001f * evt.state.Z.rel);
	}
	else
	{
		BaseApplication::mouseMoved( evt );
		updateCameraGoal(0, 0, -0.001f * evt.state.Z.rel);
	}
	
	return true;
}

//-------------------------------------------------------------------------------------
void TutorialApplication::updateCameraGoal(Real deltaYaw, Real deltaPitch, Real deltaZoom)
{
	m_pCameraPivot->yaw(Degree(deltaYaw), Node::TS_WORLD);

	// bound the pitch
	if (!(m_fPivotPitch + deltaPitch > 55 && deltaPitch > 0) &&
		!(m_fPivotPitch + deltaPitch < -60 && deltaPitch < 0))
	{
		m_pCameraPivot->pitch(Degree(deltaPitch), Node::TS_LOCAL);
		m_fPivotPitch += deltaPitch;
	}
		
	Real dist = m_pCameraGoal->_getDerivedPosition().distance(m_pCameraPivot->_getDerivedPosition());
	Real distChange = deltaZoom * dist;

	// bound the zoom
	if (!(dist + distChange < 8 && distChange < 0) &&
		!(dist + distChange > 55 && distChange > 0))
	{
		m_pCameraGoal->translate(0, 0, distChange, Node::TS_LOCAL);
	}
}

//-------------------------------------------------------------------------------------
bool TutorialApplication::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	BaseApplication::mousePressed( evt, id );
	
	if (id == OIS::MB_Right)
		m_pGUI->setVisiblePointer(false);

	m_pGUI->injectMousePress(evt.state.X.abs, evt.state.Y.abs, MyGUI::MouseButton::Enum(id));

	return true;
}

//-------------------------------------------------------------------------------------
bool TutorialApplication::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
	BaseApplication::mouseReleased( evt, id );

	m_pGUI->injectMouseRelease(evt.state.X.abs, evt.state.Y.abs, MyGUI::MouseButton::Enum(id));

	if (id == OIS::MB_Right)
		m_pGUI->setVisiblePointer(true);

	return true;
}

//-------------------------------------------------------------------------------------
void TutorialApplication::UpdateCam(Real deltaTime)
{
	// move the camera smoothly to the goal
	Vector3 goalOffset = m_pCameraGoal->_getDerivedPosition() - m_pCameraNode->getPosition();
	m_pCameraNode->translate(goalOffset * deltaTime * 9.0f);
	// always look at the pivot
	m_pCameraNode->lookAt(m_pCameraPivot->_getDerivedPosition(), Node::TS_WORLD);
}

//-------------------------------------------------------------------------------------
// Update 5 sensor glove
void TutorialApplication::Update5SensorGlove()
{
	Ogre::Skeleton* skel = m_pSceneMgr->getEntity("Hand")->getSkeleton();
	

	Ogre::Bone* mBone;

	// Thumb
	float fThumb = 90*fdGetSensorScaled(m_pGlove,FD_THUMBFAR)-10;
	
	//thumb << fdGetSensorScaled(m_pGlove,FD_THUMBFAR) << " ";
	//thumb << fThumb << " ";

	mBone = skel->getBone("Thumb.1");
    mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fThumb/3));
	//mBone->pitch(Ogre::Degree(-26.67));
	//mBone->pitch(Ogre::Degree(-(fThumb-40)/2));

	mBone = skel->getBone("Thumb.2");
	mBone->setManuallyControlled(true);
	mBone->reset();
	//mBone->pitch(Ogre::Degree(0));
	mBone->pitch(Ogre::Degree(-fThumb/2.5));

	mBone = skel->getBone("Thumb.3");
	mBone->setManuallyControlled(true);
	mBone->reset();
	//mBone->pitch(Ogre::Degree(0));
	mBone->pitch(Ogre::Degree(-fThumb/2));

	//thumb << -fThumb/3 << " " << -fThumb/2.5 << " " << -fThumb/2 << std::endl;

	// Index finger
	float fIndexFinger = 90*fdGetSensorScaled(m_pGlove,FD_INDEXFAR);
	//float diff = fIndexFinger - prev_finger_val;
	float diff = fIndexFinger - prev_collision_val;

	Ogre::Vector3 direction = Ogre::Vector3(0,1,0);
    //Ogre::Vector3 pos = cube_node->_getDerivedPosition();
	Ogre::Vector3 pos = Ogre::Vector3(19.62,16.86,-4.7);
	position << pos << std::endl;
	position << HandNode->_getDerivedPosition() << std::endl;
	position << skel->getBone("Index.1")->_getDerivedPosition() << std::endl;
	position << skel->getBone("Index.2")->_getDerivedPosition() << std::endl;
	position << skel->getBone("Index.3")->_getDerivedPosition() << std::endl;
	Ogre::Vector3 result;
	if(build_cube)
	{
		if(!collided)
		{
			if(isCollision(pos, direction, result))
			{
				collision_test << result << std::endl;
				collided = true;
				if(red && diff >= 0)
				{
					if(color_response)
					{
						/*
						if(distort_color_response)
						{
							if(curr_time >= distortion_time)
							{
								cube->setMaterialName(0, "Blue50");
								red = false;
								curr_time = 0;
							}
						}
						*/
						//else
						//{
							cube->setMaterialName(0, "Blue50");
							red = false;
						//}
					}
					if(sound_response)
					{
						engine->play2D(filename);
					}
				}
				else if(!red && diff >= 0)
				{
					if(color_response)
					{
						/*
						if(distort_color_response)
						{
							if(curr_time >= distortion_time)
							{
								cube->setMaterialName(0, "Red50");
								red = true;
								curr_time = 0;
							}
						}
						*/
						//else
						//{
							cube->setMaterialName(0, "Red50");
							red = true;
						//}
					}
					if(sound_response)
					{
						engine->play2D(filename);
					}
				}
			}
			prev_collision_val = fIndexFinger;
		}
		else if(collided && diff < -0.5)
		{
			collided = false;
		//	fIndexFinger = prev_collision_val + diff;	
		}
	}
	//collision_test << fIndexFinger << " " << diff << " " << collided << std::endl;
	diff_val << diff << std::endl;
	//collision_test << fIndexFinger << std::endl;
    if (!collided) 
	{
        mBone = skel->getBone("Index.1");
		mBone->setManuallyControlled(true);
		mBone->reset();
		mBone->pitch(Ogre::Degree(-fIndexFinger+20));
		//mBone->pitch(Ogre::Degree(-70));

		mBone = skel->getBone("Index.2");
		mBone->setManuallyControlled(true);
		mBone->reset();
		mBone->pitch(Ogre::Degree(-fIndexFinger));
		//mBone->pitch(Ogre::Degree(-90));

		mBone = skel->getBone("Index.3");
		mBone->setManuallyControlled(true);
		mBone->reset();
		mBone->pitch(Ogre::Degree(-fIndexFinger));
		//mBone->pitch(Ogre::Degree(-90));
    }

	prev_finger_val = fIndexFinger;
	
//	float diff = fIndexFinger - old_index_val;
	/*
	if(!decreasing && diff < 0 && fIndexFinger < 0.5)
	{
		decreasing = true;
		tap++;
		tapping << tap << std::endl;
	}

	if(diff > 0)
		decreasing = false;
	//if(diff > 0.1)
		thumb << fdGetSensorScaled(m_pGlove,FD_INDEXFAR) << std::endl;
	*/
//	old_index_val = fIndexFinger;

	float fMiddleFinger = 90*fdGetSensorScaled(m_pGlove,FD_MIDDLEFAR);


	mBone = skel->getBone("Middle.1");
    mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fMiddleFinger+20));

	mBone = skel->getBone("Middle.2");
	mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fMiddleFinger));

	mBone = skel->getBone("Middle.3");
	mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fMiddleFinger));

	float fRingFinger = 90*fdGetSensorScaled(m_pGlove,FD_RINGFAR);
	
	mBone = skel->getBone("Ring.1");
    mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fRingFinger+20));

	mBone = skel->getBone("Ring.2");
	mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fRingFinger));

	mBone = skel->getBone("Ring.3");
	mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fRingFinger));

	float fLittleFinger = 90*fdGetSensorScaled(m_pGlove,FD_LITTLEFAR);
	
	mBone = skel->getBone("Little.1");
    mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fLittleFinger+20));

	mBone = skel->getBone("Little.2");
	mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fLittleFinger));

	mBone = skel->getBone("Little.3");
	mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fLittleFinger));
}

//-------------------------------------------------------------------------------------
// Update 14 sensor glove
void TutorialApplication::Update14SensorGlove()
{
	Ogre::Skeleton* skel = m_pSceneMgr->getEntity("Hand")->getSkeleton();
	Ogre::Bone* mBone;

	int iSignMsg = 1;
	if (m_pSceneMgr->getEntity("Hand")->getMesh()->getName() == "5DTRHand.mesh")
		iSignMsg = -1;

	// Middle finger
	float fMiddleFingerNear = 90*fdGetSensorScaled(m_pGlove,FD_MIDDLENEAR)-10;

	mBone = skel->getBone("Middle.1");
    mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fMiddleFingerNear));

	float fMiddleFingerFar = 90*fdGetSensorScaled(m_pGlove,FD_MIDDLEFAR)-10;

	mBone = skel->getBone("Middle.2");
	mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fMiddleFingerFar));

	mBone = skel->getBone("Middle.3");
	mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fMiddleFingerFar));

	// Ring finger
	float fRingFingerNear = 90*fdGetSensorScaled(m_pGlove,FD_RINGNEAR)-10;
	float fMiddleRing = iSignMsg*(15*fdGetSensorScaled(m_pGlove,FD_MIDDLERING)-10);

	mBone = skel->getBone("Ring.1");
    mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fRingFingerNear));
	mBone->roll(Ogre::Degree(-fMiddleRing));

	float fRingFingerFar = 90*fdGetSensorScaled(m_pGlove,FD_RINGFAR)-10;

	mBone = skel->getBone("Ring.2");
	mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fRingFingerFar));

	mBone = skel->getBone("Ring.3");
	mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fRingFingerFar));

	//Thumb
	float fThumbNear = 90*fdGetSensorScaled(m_pGlove,FD_THUMBNEAR)-10;
	//float fThumbNear = 90*fdGetSensorScaled(m_pGlove,FD_THUMBNEAR)-50;
	float fTumbIndex = iSignMsg*(30*fdGetSensorScaled(m_pGlove,FD_THUMBINDEX)-30);
	//float fTumbIndex = 30*fdGetSensorScaled(m_pGlove,FD_THUMBINDEX)-30;
	mBone = skel->getBone("Thumb.1");
    mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fThumbNear/3));
	mBone->roll(Ogre::Degree(fTumbIndex));

	float fThumbFar = 90*fdGetSensorScaled(m_pGlove,FD_THUMBFAR)-10;
	mBone = skel->getBone("Thumb.2");
	mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fThumbFar/2.5));

	mBone = skel->getBone("Thumb.3");
	mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fThumbFar/2));
	
	// Index finger
	float fIndexFingerNear = 90*fdGetSensorScaled(m_pGlove,FD_INDEXNEAR)-10;
	float fIndexFingerMiddle = iSignMsg*(24*fdGetSensorScaled(m_pGlove,FD_INDEXMIDDLE)-12);
	
	mBone = skel->getBone("Index.1");
    mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fIndexFingerNear));
	mBone->roll(Ogre::Degree(fIndexFingerMiddle));

	float fIndexFingerFar = 90*fdGetSensorScaled(m_pGlove,FD_INDEXFAR)-10;

	mBone = skel->getBone("Index.2");
	mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fIndexFingerFar));

	mBone = skel->getBone("Index.3");
	mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fIndexFingerFar));

	// Little finger
	float fLittleFingerNear = 90*fdGetSensorScaled(m_pGlove,FD_LITTLENEAR)-10;
	float fRingLittle = iSignMsg*(30*fdGetSensorScaled(m_pGlove,FD_RINGLITTLE)-25);

	mBone = skel->getBone("Little.1");
    mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fLittleFingerNear));
	//mBone->roll(Ogre::Degree(-fRingLittle - fMiddleRing+10));
	mBone->roll(Ogre::Degree(-fRingLittle - fMiddleRing));

	float fLittleFingerFar = 90*fdGetSensorScaled(m_pGlove,FD_LITTLEFAR)-10;

	mBone = skel->getBone("Little.2");
	mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fLittleFingerFar));

	mBone = skel->getBone("Little.3");
	mBone->setManuallyControlled(true);
	mBone->reset();
	mBone->pitch(Ogre::Degree(-fLittleFingerFar));
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createCamera(void)
{
	m_pCamera = m_pSceneMgr->createCamera("PlayerCam");
	m_pCamera->setNearClipDistance(5);
	m_pCamera->setFixedYawAxis(true);

}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
