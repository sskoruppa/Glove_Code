/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.cpp
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
#include "Resource.h"
#include "BaseApplication.h"
#include <sstream>

//-------------------------------------------------------------------------------------
BaseApplication::BaseApplication(void)
    : m_pRoot(0),
    m_pCamera(0),
    m_pSceneMgr(0),
    m_pWindow(0),
    m_sResourcesCfg(Ogre::StringUtil::BLANK),
    m_sPluginsCfg(Ogre::StringUtil::BLANK),
    m_bCursorWasVisible(false),
    m_bShutDown(false),
    m_pInputManager(0),
    m_pMouse(0),
    m_pKeyboard(0),
	m_iCurrentPolygonRenderingMode(1)
{

}

//-------------------------------------------------------------------------------------
BaseApplication::~BaseApplication(void)
{
    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(m_pWindow, this);
    windowClosed(m_pWindow);
    delete m_pRoot;
}

//-------------------------------------------------------------------------------------
bool BaseApplication::configure(void)
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(!(m_pRoot->restoreConfig() || m_pRoot->showConfigDialog()))
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        //mWindow = m_Root->initialise(true, "5DT 3D Glove Demo");

        return false;
    }
    else
    {
		Ogre::RenderSystem *rs = m_pRoot->getRenderSystemByName("Direct3D9 Rendering Subsystem");
		// or use "OpenGL Rendering Subsystem"
		m_pRoot->setRenderSystem(rs);
		rs->setConfigOption("Full Screen", "No");
		rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");
		
		m_pWindow = m_pRoot->initialise(true, "5DT 3D Glove Demo");
		

		#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        HWND hwnd;
        m_pWindow->getCustomAttribute("WINDOW", (void*)&hwnd);
        LONG iconID   = (LONG)LoadIcon( GetModuleHandle(0), MAKEINTRESOURCE(IDI_ABC) );
        SetClassLong( hwnd, GCL_HICON, iconID );
		#endif
		
		return true;
	}

}

//-------------------------------------------------------------------------------------
void BaseApplication::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    m_pSceneMgr = m_pRoot->createSceneManager(Ogre::ST_GENERIC);
}

//-------------------------------------------------------------------------------------
void BaseApplication::createCamera(void)
{
    // Create the camera
    m_pCamera = m_pSceneMgr->createCamera("PlayerCam");
	
    // Position it at 500 in Z direction
    m_pCamera->setPosition(Ogre::Vector3(0,0,80));
    // Look back along -Z
    m_pCamera->lookAt(Ogre::Vector3(0,0,-300));
    m_pCamera->setNearClipDistance(5);

}

//-------------------------------------------------------------------------------------
void BaseApplication::createFrameListener(void)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    m_pWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    m_pInputManager = OIS::InputManager::createInputSystem( pl );

    m_pKeyboard = static_cast<OIS::Keyboard*>(m_pInputManager->createInputObject( OIS::OISKeyboard, true ));
    m_pMouse = static_cast<OIS::Mouse*>(m_pInputManager->createInputObject( OIS::OISMouse, true ));
	
    m_pMouse->setEventCallback(this);
    m_pKeyboard->setEventCallback(this);

    //Set initial mouse clipping size
    windowResized(m_pWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(m_pWindow, this);

	m_pRoot->addFrameListener(this);
	
}

//-------------------------------------------------------------------------------------
void BaseApplication::destroyScene(void)
{
}

//-------------------------------------------------------------------------------------
void BaseApplication::createViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = m_pWindow->addViewport(m_pCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    m_pCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	
}

//-------------------------------------------------------------------------------------
void BaseApplication::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(m_sResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}

//-------------------------------------------------------------------------------------
void BaseApplication::createResourceListener(void)
{

}

//-------------------------------------------------------------------------------------
void BaseApplication::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

//-------------------------------------------------------------------------------------
void BaseApplication::go(void)
{
#ifdef _DEBUG
    m_sResourcesCfg = "resources_d.cfg";
    m_sPluginsCfg = "plugins_d.cfg";
#else
    m_sResourcesCfg = "resources.cfg";
    m_sPluginsCfg = "plugins.cfg";
#endif

    if (!setup())
        return;
	
	m_pRoot->startRendering();

    // clean up
    destroyScene();
}

//-------------------------------------------------------------------------------------
bool BaseApplication::setup(void)
{
    m_pRoot = new Ogre::Root(m_sPluginsCfg);

    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    chooseSceneManager();
	
    createCamera();
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Create any resource listeners (for loading screens)
    createResourceListener();

    // Load resources
    loadResources();

    // Create the scene
    createScene();

    createFrameListener();
	
	setup_finished();
	
    return true;
};

//-------------------------------------------------------------------------------------
bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(m_pWindow->isClosed())
        return false;

    if(m_bShutDown)
        return false;

    // Need to capture/update each device
    m_pKeyboard->capture();
    m_pMouse->capture();			

    return true;
}

//-------------------------------------------------------------------------------------
bool BaseApplication::keyPressed( const OIS::KeyEvent &arg )
{
 
	if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        m_pWindow->writeContentsToTimestampedFile("screenshot", ".png");
    }
    else if (arg.key == OIS::KC_ESCAPE)
    {
        m_bShutDown = true;
    }

    return true;
}

//-------------------------------------------------------------------------------------
bool BaseApplication::keyReleased( const OIS::KeyEvent &arg )
{
    return true;
}

//-------------------------------------------------------------------------------------
bool BaseApplication::mouseMoved( const OIS::MouseEvent &arg )
{
    return true;
}

//-------------------------------------------------------------------------------------
bool BaseApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    return true;
}

//-------------------------------------------------------------------------------------
bool BaseApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    return true;
}

//-------------------------------------------------------------------------------------
//Adjust mouse clipping area
void BaseApplication::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = m_pMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

//-------------------------------------------------------------------------------------
//Unattach OIS before window shutdown (very important under Linux)
void BaseApplication::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == m_pWindow )
    {
        if( m_pInputManager )
        {
            m_pInputManager->destroyInputObject( m_pMouse );
            m_pInputManager->destroyInputObject( m_pKeyboard );

            OIS::InputManager::destroyInputSystem(m_pInputManager);
            m_pInputManager = 0;
        }
    }
}
