/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
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
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"
#include "OpenSaveFileDialog.h"
#include <conio.h>
#include "fglove.h"
#include <fstream>

#include <irrKlang.h>
using namespace irrklang;

//#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll


class TutorialApplication : public BaseApplication
{

public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);

	void GetMeshInformation(Ogre::Entity *entity, size_t &vertex_count,Ogre::Vector3* &vertices,size_t &index_count,unsigned long* &indices,const Ogre::Vector3 &position,const Ogre::Quaternion &orient,const Ogre::Vector3 &scale);

protected:
	void ConnectGlove(void);

    virtual void createScene(void);
	virtual void createCamera(void);
	//virtual void createViewports(void);

	//virtual void createFrameListener(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	
	// OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent& evt );
    virtual bool keyReleased( const OIS::KeyEvent& evt );
    //OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent& evt );
    virtual bool mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id );
	
	void createFrameListener(void);

	bool isCollision(const Ogre::Vector3& position, const Ogre::Vector3& direction, Ogre::Vector3 &result);

	// Called when a any button of the GUI is clicked
	//virtual void buttonHit(OgreBites::Button* b);

	Ogre::Real m_fRotateSpeed;			// The rotate constant
	Ogre::Real m_fRotateDecel;			// The rotate deceleration constant
	Ogre::Real m_fZoomSpeed;			// The zoom constant
	Ogre::Real m_fZoomDecel;			// The zoom deceleration
	Ogre::Real m_fMaxZoom;				// Max zoom distance	
	Ogre::Real m_fMinZoom;				// Min zoom distance
	Ogre::Real m_fPivotPitch;			// Current pitch of the camera   
 	
	Ogre::SceneNode* m_pCameraNode;		// Current position of cam
	Ogre::SceneNode* m_pCameraGoal;		// Where the camera should be (for smoother movement)
	Ogre::SceneNode* m_pCameraPivot;	// Pivot around which cam will rotate
	Ogre::RaySceneQuery* mRaySceneQuery;
	Ogre::Entity *handEnt;
	Ogre::SceneNode* HandNode;
	
	

private:
	common::OpenSaveFileDialog* mOpenSaveFileDialog;

	void Update5SensorGlove();
	void Update14SensorGlove();
	void UpdateCam(Ogre::Real fdT);
	void setupCamera();
	Ogre::ManualObject* createCubeMesh(Ogre::String name, Ogre::String matName);
	void updateCameraGoal(Ogre::Real deltaYaw, Ogre::Real deltaPitch, Ogre::Real deltaZoom);

	fdGlove* m_pGlove;					// our one and only glove

	// MyGUI variables and methods
	virtual void setup_finished(void);
	void setupMyGUI(void);
	void btnAbout_Click(MyGUI::WidgetPtr _sender);
	void wndAboutButtonPressed(MyGUI::WidgetPtr _widget, const std::string& _name);
	void btnExit_Click(MyGUI::WidgetPtr _sender);
	void loadCalibrationGui(bool b5SensorGlove);
	void btnCalibrate_Click(MyGUI::WidgetPtr _sender);
	void btnAdvCalib_Click(MyGUI::WidgetPtr _sender);
	void CalibCheckBox_Click(MyGUI::WidgetPtr _sender);
	void btnCalSetMin_Click(MyGUI::WidgetPtr _sender);
	void btnCalSetMax_Click(MyGUI::WidgetPtr _sender);
	void btnSaveCalib_Click(MyGUI::WidgetPtr _sender);
	void btnFistCalib_Click(MyGUI::WidgetPtr _sender);
	void btnOpenHandCalib_Click(MyGUI::WidgetPtr _sender);
	void btnSpreadFingersCalib_Click(MyGUI::WidgetPtr _sender);
	void btnFlatHandCalib_Click(MyGUI::WidgetPtr _sender);
	void btnCalibReset_Click(MyGUI::WidgetPtr _sender);
	void btnGraphicsSettings_Click(MyGUI::WidgetPtr _sender);
	void ApplyGraphicsSettings_Click(MyGUI::WidgetPtr _sender);
	void notifyOpenSaveEndDialog(bool _result);
	void btnSaveCal_Click(MyGUI::WidgetPtr _sender);

	int m_iCurrentSensor;	// currently selected sensor in calibration menu
	MyGUI::OgrePlatform* m_pPlatform;
	MyGUI::Gui* m_pGUI;
	MyGUI::StaticTextPtr m_ptxtFPS;
	MyGUI::StaticTextPtr m_ptxtRawVal;
	MyGUI::StaticTextPtr m_ptxtScaledVal;
	MyGUI::StaticTextPtr m_ptxtMaxCal;
	MyGUI::StaticTextPtr m_ptxtMinCal;

	Ogre::ManualObject* cube;
	Ogre::SceneNode* node2;
	bool red;

	std::ofstream thumb;
	std::ofstream tapping;
	std::ofstream position;
	std::ofstream distance;

	bool sound_response;
	bool color_response;
	bool distort_color_response;
	bool distort_sound_response;

    int mNumEntitiesInstanced;

	bool decreasing;
	int tap;

	Ogre::SceneNode* cube_node;
	float prev_collided;
	float distortion_time;
	float curr_time;

	std::ofstream collision_test;
	std::ofstream mesh_data;
	bool collided;
	bool build_cube;

	float prev_finger_val;
	float prev_collision_val;

	std::ofstream diff_val;

	ISoundEngine* engine;
	const char* filename;
};

#endif // #ifndef __TutorialApplication_h_
