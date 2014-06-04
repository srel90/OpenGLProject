#include "stdafx.h"
#include "MainForm.h"
#include "imageloader.h"
#include "3dsLoader.h"
using namespace System;
using namespace System::IO;
namespace OpenGLProject
{
	MainForm::MainForm()
	{
		InitializeComponent();

	}
	MainForm::~MainForm()
	{
		if (components)
			delete components;
	}
	UINT SkyboxTexture[30];
	UINT ObjectTexture[6];
	UINT ModelTexture[10];
	C3dsLoader obj3dsLoader[5];
	
	XYZ PerspectiveEyePosition;
	XYZ PerspectiveViewDirection;
	XYZ PerspectiveUpVector;
	XYZ PerspectiveRightVector;
	

	Void MainForm::loadSkybox(UINT textureArray[], LPSTR strFileName,int ID) {
		if(!strFileName)	return;
		Images* image = loadBMP(strFileName);
		if(image == NULL)exit(0);
		glGenTextures(1, &textureArray[ID]);
		glBindTexture(GL_TEXTURE_2D, textureArray[ID]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image->width, image->height, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

		if (image)									
		{
			if (image->pixels)					
			{
				free(image->pixels);			
			}
			free(image);
		}

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

	}
	Void MainForm::loadTexture(UINT textureArray[], LPSTR strFileName,int ID) {
		if(!strFileName)	return;
		textureArray[ID]= SOIL_load_OGL_texture
        (
        strFileName,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS|SOIL_FLAG_TEXTURE_REPEATS|SOIL_FLAG_COMPRESS_TO_DXT|SOIL_FLAG_NTSC_SAFE_RGB|SOIL_FLAG_INVERT_Y
        );
	glBindTexture(GL_TEXTURE_2D, textureArray[ID]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	Void MainForm::ClearBackGround()
	{
		glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	Void MainForm::DrawTitle(Zolver::OpenGLControl^ GLControl, String^ Title)
	{
		if (!GLControl || String::IsNullOrEmpty(Title))
			return;

		// convert the managed string into char array
		char* str = (char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Title)).ToPointer();
		char* p = str;

		// disable the lightning
		glDisable(GL_LIGHTING);

		// Set up the Orthographic projection
		glViewport(0, 0, GLControl->Width, GLControl->Height);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, GLControl->Width, 0, GLControl->Height);
		glScalef(1, -1, 1);
		glTranslatef(0, -(GLfloat)GLControl->Height, 0);

		// draw the text
		glColor3f(0.78f, 0.78f, 0.78f);
		glRasterPos2f(4.0f, 12.0f);

		while (*p != '\0')
		{ 
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
		}	

		// release the allocated string
		Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)str));
	}
	Void MainForm::DrawText(Zolver::OpenGLControl^ GLControl, String^ Text)
	{
		if (!GLControl || String::IsNullOrEmpty(Text))
			return;

		// convert the managed string into char array
		char* str = (char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Text)).ToPointer();
		char* p = str;


		// Set up the Orthographic projection
		glViewport(0, 0, GLControl->Width, GLControl->Height);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, GLControl->Width, 0, GLControl->Height);
		glScalef(1, -1, 1);
		glTranslatef(0, -(GLfloat)GLControl->Height, 0);

		// draw the text
		glColor3d(red, green, blue);
		glRasterPos2f(4.0f, 36.0f);

		while (*p != '\0')
		{ 
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
		}	

		// release the allocated string
		Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)str));
	}
	Void MainForm::Normalise(XYZ% vector)
	{
		Single v_size = Math::Sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
		vector.x = vector.x/v_size;
		vector.y = vector.y/v_size;
		vector.z = vector.z/v_size;
	}
	Void MainForm::PerspectiveShowAxisCheckBox_CheckedChanged(Object^ sender, EventArgs^ e) 
	{
		PerspectiveShowAxis = PerspectiveShowAxisCheckBox->Checked;		
	}
	Void MainForm::PerspectiveShowGridCheckBox_CheckedChanged(Object^ sender, EventArgs^ e) 
	{
		PerspectiveShowGrid = PerspectiveShowGridCheckBox->Checked;
	}
	Void MainForm::PerspectiveShowWireframeCheckBox_CheckedChanged(Object^ sender, EventArgs^ e) 
	{
		PerspectiveShowWireFrame = PerspectiveShowWireframeCheckBox->Checked;
	}
	Void MainForm::PerspectiveShowFrameRateCheckBox_CheckedChanged(Object^ sender, EventArgs^ e) 
	{
		PerspectiveView->ShowFrameRate = PerspectiveShowFrameRateCheckBox->Checked;
	}
	Void MainForm::PerspectiveShowGroundCheckBox_CheckedChanged(Object^ sender, EventArgs^ e) 
	{
		PerspectiveShowGround = PerspectiveShowGroundCheckBox->Checked;
	}
	Void MainForm::PerspectiveView_OpenGLInit(Object^ sender, EventArgs^ e)
	{
		PerspectiveShowAxis = PerspectiveShowAxisCheckBox->Checked;
		PerspectiveShowGrid = PerspectiveShowGridCheckBox->Checked;
		PerspectiveShowWireFrame = PerspectiveShowWireframeCheckBox->Checked;
		PerspectiveCameraAngle = 90.0F;
		PerspectiveCameraNear = 0.1F;
		PerspectiveCameraFar = 500.0F;
		PerspectiveCameraFocus = 40.0;
		PerspectiveRotateX = 25;
		PerspectiveRotateY = 45;
		PerspectiveRotateX_old = PerspectiveRotateX;
		PerspectiveRotateY_old = PerspectiveRotateY;

		glShadeModel(GL_SMOOTH);
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_NORMALIZE);

		glEnable(GL_POINT_SMOOTH_HINT);
		glEnable(GL_LINE_SMOOTH_HINT);
		glEnable(GL_POLYGON_SMOOTH_HINT);
		glEnable(GL_PERSPECTIVE_CORRECTION_HINT);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);

		
		
		
		ModelNum=0;
		ModelTex=0;
		SceneNum=0;
		SceneNumPOV=0;
		color=1;
		
		loadSkybox(SkyboxTexture,"data/texture/front.bmp",0);
		loadSkybox(SkyboxTexture,"data/texture/back.bmp",1);
		loadSkybox(SkyboxTexture,"data/texture/left.bmp",2);
		loadSkybox(SkyboxTexture,"data/texture/right.bmp",3);
		loadSkybox(SkyboxTexture,"data/texture/up.bmp",4);
		loadSkybox(SkyboxTexture,"data/texture/down.bmp",5);

		loadSkybox(SkyboxTexture,"data/texture/front_1.bmp",6);
		loadSkybox(SkyboxTexture,"data/texture/back_1.bmp",7);
		loadSkybox(SkyboxTexture,"data/texture/left_1.bmp",8);
		loadSkybox(SkyboxTexture,"data/texture/right_1.bmp",9);
		loadSkybox(SkyboxTexture,"data/texture/up_1.bmp",10);
		loadSkybox(SkyboxTexture,"data/texture/down_1.bmp",11);

		loadSkybox(SkyboxTexture,"data/texture/jajlands1_ft.bmp",12);
		loadSkybox(SkyboxTexture,"data/texture/jajlands1_bk.bmp",13);
		loadSkybox(SkyboxTexture,"data/texture/jajlands1_lf.bmp",14);
		loadSkybox(SkyboxTexture,"data/texture/jajlands1_rt.bmp",15);
		loadSkybox(SkyboxTexture,"data/texture/jajlands1_up.bmp",16);
		loadSkybox(SkyboxTexture,"data/texture/jajlands1_dn.bmp",17);

		loadSkybox(SkyboxTexture,"data/texture/front_2.bmp",18);
		loadSkybox(SkyboxTexture,"data/texture/back_2.bmp",19);
		loadSkybox(SkyboxTexture,"data/texture/left_2.bmp",20);
		loadSkybox(SkyboxTexture,"data/texture/right_2.bmp",21);
		loadSkybox(SkyboxTexture,"data/texture/up_2.bmp",22);
		loadSkybox(SkyboxTexture,"data/texture/down_2.bmp",23);

		loadSkybox(SkyboxTexture,"data/texture/front_3.bmp",24);
		loadSkybox(SkyboxTexture,"data/texture/back_3.bmp",25);
		loadSkybox(SkyboxTexture,"data/texture/left_3.bmp",26);
		loadSkybox(SkyboxTexture,"data/texture/right_3.bmp",27);
		loadSkybox(SkyboxTexture,"data/texture/up_3.bmp",28);
		loadSkybox(SkyboxTexture,"data/texture/down_3.bmp",29);

		loadTexture(ObjectTexture,"data/texture/vtr.bmp",0);
		loadTexture(ObjectTexture,"data/texture/grass.bmp",1);

		loadTexture(ModelTexture,"data/model/dolphin/color1.png",0);
		loadTexture(ModelTexture,"data/model/dolphin/color2.png",1);
		obj3dsLoader[0].Init_3ds("data/model/dolphin/dolphin.3ds","data/model/dolphin/%s");
		
		loadTexture(ModelTexture,"data/model/shark/color1.png",2);
		loadTexture(ModelTexture,"data/model/shark/color2.png",3);		
		obj3dsLoader[1].Init_3ds("data/model/shark/shark.3ds","data/model/shark/%s");

		loadTexture(ModelTexture,"data/model/deer/color1.png",4);
		loadTexture(ModelTexture,"data/model/deer/color2.png",5);
		obj3dsLoader[2].Init_3ds("data/model/deer/deer.3ds","data/model/deer/%s");

		loadTexture(ModelTexture,"data/model/cat/color1.tga",6);
		loadTexture(ModelTexture,"data/model/cat/color2.tga",7);
		obj3dsLoader[3].Init_3ds("data/model/cat/cat.3ds","data/model/cat/%s");

		loadTexture(ModelTexture,"data/model/robot/headhunt.tga",8);
		loadTexture(ModelTexture,"data/model/robot/headhunt1.tga",9);
		obj3dsLoader[4].Init_3ds("data/model/robot/headhunter1.3ds","data/model/robot/%s");
		

	}
	Void MainForm::PerspectiveView_OpenGLRender(Object^ sender, EventArgs^ e) 
	{
		ClearBackGround();		
		SetPerspectiveCamera(PerspectiveCameraAngle, PerspectiveCameraFocus, (Single)PerspectiveView->Width, (Single)PerspectiveView->Height, PerspectiveCameraNear, PerspectiveCameraFar);	
		GLfloat light0_position[] = { -15.0, -15.0, 15.0, 0.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

		if(PerspectiveShowWireFrame){
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		}else{
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		}


		glEnable(GL_TEXTURE_2D);	
	
		switch(ModelNum){
		case 0:
		glColor3ub(255, 255, 255);
		glBindTexture(GL_TEXTURE_2D, ModelTexture[ModelTex]);
		glPushMatrix();
		glTranslatef(0,0,10);
		glScalef(0.5f,0.5f,0.5f);
		obj3dsLoader[ModelNum].Render_3ds();		
		glPopMatrix();
		break;
		case 1:
		glColor3ub(255, 255, 255);
		glBindTexture(GL_TEXTURE_2D, ModelTexture[ModelTex]);
		glPushMatrix();
		glTranslatef(0,0,10);
		glScalef(5.0f,5.0f,5.0f);
		obj3dsLoader[ModelNum].Render_3ds();
		glPopMatrix();
		break;
		case 2:
		glColor3ub(255, 255, 255);
		glBindTexture(GL_TEXTURE_2D, ModelTexture[ModelTex]);
		glPushMatrix();
		glScalef(10.0f,10.0f,10.0f);
		obj3dsLoader[ModelNum].Render_3ds();
		glPopMatrix();
		break;
		case 3:
		glColor3ub(255, 255, 255);
		glBindTexture(GL_TEXTURE_2D, ModelTexture[ModelTex]);
		glPushMatrix();
		glScalef(1.0f,1.0f,1.0f);	
		obj3dsLoader[ModelNum].Render_3ds();
		glPopMatrix();
		break;
		case 4:
		glColor3ub(255, 255, 255);
		glBindTexture(GL_TEXTURE_2D, ModelTexture[ModelTex]);
		glPushMatrix();
		glScalef(0.15f,0.15f,0.15f);
		glTranslatef(0,0,120);
		obj3dsLoader[ModelNum].Render_3ds();
		glPopMatrix();
		break;

		}
			
		
		Draw_Skybox(0,0,0,300,300,300);

		if(PerspectiveShowGround)
		Draw_Ground();
		
		glDisable(GL_TEXTURE_2D);

		if (PerspectiveShowGrid)
			DrawPerspectiveGrid();

		if (PerspectiveShowAxis)
			DrawPerspectiveAxis();

		DrawTitle(PerspectiveView, PerspectiveView->Text);
		DrawText(PerspectiveView,ScreenText);	
	}
	Void MainForm::vScrollBar1_Changed(Object^ sender, ScrollEventArgs^ e)
	{
		PerspectiveCameraFocus=vScrollBar1->Value;
	}
	Void MainForm::PerspectiveView_OpenGLMouseDown(Object^ sender, MouseEventArgs^ e)
	{

		PerspectiveLastPosition = e->Location;

		PerspectiveRotateX_old = PerspectiveRotateX;
		PerspectiveRotateY_old = PerspectiveRotateY;
	}
	Void MainForm::PerspectiveView_OpenGLMouseMove(Object^ sender, MouseEventArgs^ e)
	{
		if (e->Button == Windows::Forms::MouseButtons::Right)
		{
			Int32 RotateXi = Convert::ToInt32(PerspectiveRotateY_old + (PerspectiveLastPosition.X - e->Location.X));
			Int32 RotateYi = Convert::ToInt32(PerspectiveRotateX_old + (e->Location.Y - PerspectiveLastPosition.Y));
			PerspectiveRotateY =  RotateXi  %  360;	
			PerspectiveRotateX =  RotateYi  %  360;

			if (PerspectiveRotateY < 0.0F) 
				PerspectiveRotateY += 360.0F;

			if (PerspectiveRotateX < 0.0F) 
				PerspectiveRotateX += 360.0F;
		}

		
		
	}
	Void MainForm::PerspectiveView_OpenGLMouseUp(Object^ sender, MouseEventArgs^ e)
	{
		PerspectiveRotateX_old = PerspectiveRotateX;
		PerspectiveRotateY_old = PerspectiveRotateY;
	}
	Void MainForm::PerspectiveView_OpenGLMouseWheel(Object^ sender, MouseEventArgs^ e)
	{
		PerspectiveCameraFocus -= e->Delta/240.0F;
		
		if (PerspectiveCameraFocus < 2.0F)
			PerspectiveCameraFocus = 2.0;
	}
	Void MainForm::DrawPerspectiveGrid()
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LINE_SMOOTH);

		glLineWidth(1.0f);
		glBegin(GL_LINES);
		glColor3f(0.1f, 0.1f, 0.1f);

		Int32 size = 10;
		if (PerspectiveCameraFocus > size)
			size = (Int32)PerspectiveCameraFocus;

		for(int x = -(size/2); x <= (size/2); x++)
		{
			glVertex3f( x*2, -size, 0.0f );
			glVertex3f( x*2, size, 0.0f );
		}
		for(int y = -(size/2); y <= (size/2); y++)
		{
			glVertex3f( -size, y*2, 0.0f );
			glVertex3f( size, y*2, 0.0f );
		}

		glEnd();
	}
	Void MainForm::DrawPerspectiveAxis()
	{
		SetPerspectiveCamera(30.0F, 4.0F, 80.0F, 80.0F, 1.0F, 10.0F);

		glDisable(GL_LIGHTING);
		glMatrixMode(GL_MODELVIEW);
		glScalef(0.23f, 0.23f, 0.23f);
		glLineWidth(0.5f);

		glBegin(GL_LINES);
			// XAxis
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(3.5f, 0.0f, 0.0f);

			// YAxis
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 3.5f, 0.0f);

			// ZAxis
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 3.5f);
		glEnd();

		// XAxis
		glPushMatrix();
		glTranslatef(3.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glutSolidCone(0.5f, 1.5f, 8, 1);
		glPopMatrix();
		glRasterPos3f(4.0f, 0.0f, 1.0f);	
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, 'X');	

		// YAxis
		glPushMatrix();
		glTranslatef(0.0f, 3.0f, 0.0f);	
		glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glutSolidCone(0.5f, 1.5f, 8, 1);
		glPopMatrix();
		glRasterPos3f(0.0f, 4.0f, 1.0f);	
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, 'Y');	

		// ZAxis
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 3.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glutSolidCone(0.5f, 1.5f, 8, 1);
		glPopMatrix();
		glRasterPos3f(1.0f, 0.0f, 4.0f);	
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, 'Z');
	}
	Void MainForm::SetPerspectiveCamera(Single glAngle, Single glDistance, Single glWidth, Single glHeight, Single glNear, Single glFar)
	{
		

		PerspectiveEyePosition.x = Math::Cos(PerspectiveRotateY*Math::PI/180)*Math::Cos(PerspectiveRotateX*Math::PI/180)*glDistance;;
		PerspectiveEyePosition.y = Math::Sin(PerspectiveRotateY*Math::PI/180)*Math::Cos(PerspectiveRotateX*Math::PI/180)*glDistance;
		PerspectiveEyePosition.z = Math::Sin(PerspectiveRotateX*Math::PI/180)*glDistance;

		PerspectiveViewDirection.x = -PerspectiveEyePosition.x;	
		PerspectiveViewDirection.y = -PerspectiveEyePosition.y;
		PerspectiveViewDirection.z = -PerspectiveEyePosition.z;

		Normalise(PerspectiveViewDirection);

		if ((PerspectiveRotateX > 90.0F)&&(PerspectiveRotateX <= 270.0F))
		{
			PerspectiveRightVector.x = PerspectiveViewDirection.y;	
			PerspectiveRightVector.y = -PerspectiveViewDirection.x;
			PerspectiveRightVector.z = 0.0;
		}else
		{
			PerspectiveRightVector.x = -PerspectiveViewDirection.y;
			PerspectiveRightVector.y = PerspectiveViewDirection.x;
			PerspectiveRightVector.z = 0.0;
		}

		PerspectiveUpVector.x = PerspectiveViewDirection.y*PerspectiveRightVector.z - PerspectiveViewDirection.z*PerspectiveRightVector.y;
		PerspectiveUpVector.y = PerspectiveViewDirection.z*PerspectiveRightVector.x - PerspectiveViewDirection.x*PerspectiveRightVector.z;
		PerspectiveUpVector.z = PerspectiveViewDirection.x*PerspectiveRightVector.y - PerspectiveViewDirection.y*PerspectiveRightVector.x;

		Normalise(PerspectiveUpVector);

		glViewport(0, 0, glWidth, glHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(glAngle, glWidth/glHeight, glNear, glFar);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();			
		gluLookAt(	PerspectiveEyePosition.x,	PerspectiveEyePosition.y,	PerspectiveEyePosition.z, 
			PerspectiveViewDirection.x, PerspectiveViewDirection.y, PerspectiveViewDirection.z,
			PerspectiveUpVector.x,		PerspectiveUpVector.y,		PerspectiveUpVector.z);
	}
	Void MainForm::Draw_Skybox(float x, float y, float z, float width, float height, float length)
	{
		// Center the Skybox around the given x,y,z position
		x = x - width  / 2;
		y = y - height / 2;
		z = z - length / 2;
		glPushMatrix();	
		
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		// Draw Front side
		glBindTexture(GL_TEXTURE_2D, SkyboxTexture[0+SceneNum]);
		glBegin(GL_QUADS);	
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height, z+length);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length); 
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length);
		glEnd();

		// Draw Back side
		glBindTexture(GL_TEXTURE_2D, SkyboxTexture[1+SceneNum]);
		glBegin(GL_QUADS);		
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z); 
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
		glEnd();

		// Draw Left side
		glBindTexture(GL_TEXTURE_2D, SkyboxTexture[2+SceneNum]);
		glBegin(GL_QUADS);		
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);	
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z+length); 
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z+length);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z);		
		glEnd();

		// Draw Right side
		glBindTexture(GL_TEXTURE_2D, SkyboxTexture[3+SceneNum]);
		glBegin(GL_QUADS);		
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length); 
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z);
		glEnd();

		// Draw Up side
		glBindTexture(GL_TEXTURE_2D, SkyboxTexture[4+SceneNum]);
		glBegin(GL_QUADS);		
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
		glEnd();

		// Draw Down side
		glBindTexture(GL_TEXTURE_2D, SkyboxTexture[5+SceneNum]);
		glBegin(GL_QUADS);		
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length); 
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
		glEnd();
		glPopMatrix();

	}
	Void MainForm::Draw_Ground()
	{

		glPushMatrix();
		glScaled(50, 50, 100);
		glBindTexture(GL_TEXTURE_2D, ObjectTexture[1]);
		glBegin(GL_QUADS);		
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,-1.0f, 0.0f); 
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
		glEnd();
		glPopMatrix();
	}
	Void MainForm::DrawPerspectiveTeapot()
	{	
		
		glPushMatrix();
		glColor3ub(255, 255, 255);
		glBindTexture(GL_TEXTURE_2D, ModelTexture[ModelTex]);

		glTranslatef(0.0f, 0.0f, 3.75f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

		if(PerspectiveShowWireFrame){
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		}else{
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		}
		glutSolidTeapot(5.0f);
		glPopMatrix();
	}
	Void MainForm::Model1_click(Object^ sender, EventArgs^ e)
	{

		ModelNum=0;
		ModelTex=0;
	}
	Void MainForm::Model2_click(Object^ sender, EventArgs^ e)
	{

		ModelNum=1;
		ModelTex=2;
	}
	Void MainForm::Model3_click(Object^ sender, EventArgs^ e)
	{

		ModelNum=2;
		ModelTex=4;
	}
	Void MainForm::Model4_click(Object^ sender, EventArgs^ e)
	{
		
		ModelNum=3;
		ModelTex=6;
	}
	Void MainForm::Model5_click(Object^ sender, EventArgs^ e)
	{
		
		ModelNum=4;
		ModelTex=8;
	}
	Void MainForm::btnfont_Click(Object^ sender, EventArgs^ e)
	{
		ScreenText=textBox1->Text; 
	}
	Void MainForm::btncolor_Click(Object^ sender, EventArgs^ e)
	{
		if(colorDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
      {
		  System::Drawing::Color col = colorDialog1->Color;
         red = col.R;
		 green = col.G;
		 blue = col.B;
      }
	}
	Void MainForm::Texture1_click(Object^ sender, EventArgs^ e)
	{
		
		switch(ModelNum)
		{
		case 0:ModelTex=0;break;
		case 1:ModelTex=2;break;
		case 2:ModelTex=4;break;
		case 3:ModelTex=6;break;
		case 4:ModelTex=8;break;
		}
		color=1;
	}
	Void MainForm::Texture2_click(Object^ sender, EventArgs^ e)
	{
		switch(ModelNum)
		{
		case 0:ModelTex=1;break;
		case 1:ModelTex=3;break;
		case 2:ModelTex=5;break;
		case 3:ModelTex=7;break;
		case 4:ModelTex=9;break;
		}
		color=2;
	}
	Void MainForm::btnrender_Click(Object^ sender, EventArgs^ e)
	{
		std::string path,filename,image_map,skyfront,skyback,skyleft,skyright,skyup,skydown;
		
		switch(ModelNum){
					case 0:path="data\\model\\dolphin\\dolphin.png";filename="data/model/dolphin/dolphin.pov";
						if(color==1){
						image_map="data/model/dolphin/color1.png";
						}else{
						image_map="data/model/dolphin/color2.png";
						}
						break;
					case 1:path="data\\model\\shark\\shark.png";filename="data/model/shark/shark.pov";
						if(color==1){
						image_map="data/model/shark/color1.png";
						}else{
						image_map="data/model/shark/color2.png";
						}
						break;
					case 2:path="data\\model\\deer\\deer.png";filename="data/model/deer/deer.pov";
						if(color==1){
						image_map="data/model/deer/color1.png";
						}else{
						image_map="data/model/deer/color2.png";
						}
						break;
					case 3:path="data\\model\\cat\\cat.png";filename="data/model/cat/cat.pov";
						if(color==1){
						image_map="data/model/cat/color1.png";
						}else{
						image_map="data/model/cat/color2.png";
						}
						break;
					case 4:path="data\\model\\rhino\\rhino.png";filename="data/model/rhino/rhino.pov";
						if(color==1){
						image_map="data/model/rhino/color1.png";
						}else{
						image_map="data/model/rhino/color2.png";
						}
						break;
					}
				StreamWriter^ sw = gcnew StreamWriter(gcnew String(filename.c_str()));
				sw->WriteLine("#include \"colors.inc\"");
				sw->WriteLine("camera {perspective");
				sw->WriteLine("angle "+PerspectiveCameraAngle);
				sw->WriteLine("location <"+PerspectiveEyePosition.x+","+PerspectiveEyePosition.y+","+PerspectiveEyePosition.z+">");
				sw->WriteLine("sky<"+PerspectiveUpVector.x+","+PerspectiveUpVector.y+","+PerspectiveUpVector.z+">");
				//sw->WriteLine("right<"+PerspectiveRightVector.x+","+PerspectiveRightVector.y+","+PerspectiveRightVector.z+">");
				sw->WriteLine("direction <"+PerspectiveViewDirection.x+","+PerspectiveViewDirection.y+","+PerspectiveViewDirection.z+">");
				sw->WriteLine("look_at <0, 0, 0>");
				
				sw->WriteLine("}");
				sw->WriteLine("background { color White*2 }"); 
				sw->WriteLine("light_source {<0.000000, 5.000000, -5.000000>color rgb <1.000000,1.000000,1.000000>parallel point_at <0,0,0>rotate <15.000000,15.000000,15.000000>}");
				sw->WriteLine("light_source {<16.000000,50.000000,16.000000>color rgb <0.300000,0.300000,0.300000>area_light <10, 0, 0>, <0, 0, 10>, 10,10 adaptive 1 jitter}");
				sw->WriteLine("light_source {<0.000000,30.000000,32.000000>color rgb <0.300000,0.300000,0.300000>area_light <5, 0, 0>, <0, 0, 5>, 5,5 adaptive 1 jitter}");
				sw->WriteLine("light_source {<32.000000,30.000000,-0.000000>color rgb <0.300000,0.300000,0.300000>area_light <5, 0, 0>, <0, 0, 5>, 5,5 adaptive 1 jitter}");
				sw->WriteLine("light_source {<32.000000,30.000000,32.000000>color rgb <0.300000,0.300000,0.300000>area_light <5, 0, 0>, <0, 0, 5>, 5,5 adaptive 1	jitter}");
				sw->WriteLine("light_source {<0.000000,30.000000,-0.000000>color rgb <0.300000,0.300000,0.300000>area_light <5, 0, 0>, <0, 0, 5>, 5,5 adaptive 1 jitter}");
				
				float x=0,y=0,z=0,width=2,height=2,length=2;
				x = x - width  / 2;
				y = y - height / 2;
				z = z - length / 2;

				switch(SceneNumPOV)
				{
				case 0:
					skyfront="data/texture/front.bmp";
					skyback="data/texture/back.bmp";
					skyleft="data/texture/left.bmp";
					skyright="data/texture/right.bmp";
					skyup="data/texture/up.bmp";
					skydown="data/texture/down.bmp";
					break;
				case 1:
					skyfront="data/texture/front_1.bmp";
					skyback="data/texture/back_1.bmp";
					skyleft="data/texture/left_1.bmp";
					skyright="data/texture/right_1.bmp";
					skyup="data/texture/up_1.bmp";
					skydown="data/texture/down_1.bmp";
					break;
				case 2:
					skyfront="data/texture/jajlands1_ft.bmp";
					skyback="data/texture/jajlands1_bk.bmp";
					skyleft="data/texture/jajlands1_lf.bmp";
					skyright="data/texture/jajlands1_rt.bmp";
					skyup="data/texture/jajlands1_up.bmp";
					skydown="data/texture/jajlands1_dn.bmp";
					break;
				case 3:
					skyfront="data/texture/front_2.bmp";
					skyback="data/texture/back_2.bmp";
					skyleft="data/texture/left_2.bmp";
					skyright="data/texture/right_2.bmp";
					skyup="data/texture/up_2.bmp";
					skydown="data/texture/down_2.bmp";
					break;
				case 4:
					skyfront="data/texture/front_3.bmp";
					skyback="data/texture/back_3.bmp";
					skyleft="data/texture/left_3.bmp";
					skyright="data/texture/right_3.bmp";
					skyup="data/texture/up_3.bmp";
					skydown="data/texture/down_3.bmp";
					break;
				}
				
				sw->WriteLine("box{ <0,0,0>,<1,0,1>texture { pigment{ image_map{ bmp \""+gcnew String(skyfront.c_str())+"\" interpolate 2}rotate<-90,180,0> } finish { ambient 1 diffuse 0} } scale <300,300,300>translate<-150,-150,-150> }");
				sw->WriteLine("box{ <0,0,0>,<1,0,1>texture { pigment{ image_map{ bmp \""+gcnew String(skyleft.c_str())+"\" interpolate 2}rotate<-90,-180,0> } finish { ambient 1 diffuse 0} } scale <300,300,300>translate<-150,-150,-150>rotate<0,0,-90>}");
				sw->WriteLine("box{ <0,0,0>,<1,0,1>texture { pigment{ image_map{ bmp \""+gcnew String(skydown.c_str())+"\" interpolate 2}rotate<-90,-90,0>} finish { ambient 1 diffuse 0} } scale <300,300,300>translate<-150,-150,-150>rotate<90,0,0>}");
				sw->WriteLine("box{ <0,0,0>,<1,0,1>texture { pigment{ image_map{ bmp \""+gcnew String(skyup.c_str())+"\" interpolate 2}rotate<-90,90,0>} finish { ambient 1 diffuse 0} } scale <300,300,300>translate<-150,-150,-150>rotate<-90,0,0>} ");
				sw->WriteLine("box{ <0,0,0>,<1,0,1>texture { pigment{ image_map{ bmp \""+gcnew String(skyright.c_str())+"\" interpolate 2}rotate<-90,-180,0>} finish { ambient 1 diffuse 0} } scale <300,300,300>translate<-150,-150,-150>rotate<0,0,90>}");
				sw->WriteLine("box{ <0,0,0>,<1,0,1>texture { pigment{ image_map{ bmp \""+gcnew String(skyback.c_str())+"\" interpolate 2}rotate<-90,-90,0>} finish { ambient 1 diffuse 0} } scale <300,300,300>translate<-150,-150,-150>rotate<-90,-90,-90>}");


				if(PerspectiveShowGround)
					sw->WriteLine("polygon{4,<-1, 1, 0>,<1, 1, 0> ,<1, -1, 0>,<-1, -1, 0> texture {pigment{  image_map{ bmp \"data/texture/grass.bmp\"  interpolate 4}}} scale <50,50,100>}");
				

				for(int i = 0; i < obj3dsLoader[ModelNum].m3DModel.numOfObjects; i++)
				{	
					if(obj3dsLoader[ModelNum].m3DModel.pObject.size() <= 0) break;
					t3DObject *pObject = &obj3dsLoader[ModelNum].m3DModel.pObject[i];
					
					sw->WriteLine("mesh {");
					for(int j = 0; j < pObject->numOfFaces; j++)
					{	
						sw->WriteLine("smooth_triangle {");	
						
						for(int whichVertex = 0; whichVertex < 3; whichVertex++)
						{
							int index = pObject->pFaces[j].vertIndex[whichVertex];

							sw->WriteLine("<"+pObject->pVerts[ index ].x+","+pObject->pVerts[ index ].y+","+pObject->pVerts[ index ].z+">,");
							if(whichVertex!=2){
								sw->WriteLine("<"+pObject->pNormals[ index ].x+","+pObject->pNormals[ index ].y+","+pObject->pNormals[ index ].z+">,");
							}else{
								sw->WriteLine("<"+pObject->pNormals[ index ].x+","+pObject->pNormals[ index ].y+","+pObject->pNormals[ index ].z+">");

							}

						}
						sw->Write("uv_vectors");
						for(int whichVertex = 0; whichVertex < 3; whichVertex++)
						{
							int index = pObject->pFaces[j].vertIndex[whichVertex];
							
							if(pObject->bHasTexture) {					
								if(pObject->pTexVerts) {
									if(whichVertex!=2){
										sw->Write("<"+pObject->pTexVerts[ index ].x+","+pObject->pTexVerts[ index ].y+">,");
									}else{
										sw->WriteLine("<"+pObject->pTexVerts[ index ].x+","+pObject->pTexVerts[ index ].y+">");

									}
									
								}
							}

						}
						
						
						sw->WriteLine("}");
						
					}
					sw->WriteLine("texture{uv_mapping pigment{  image_map{ png \""+gcnew String(image_map.c_str())+"\"  interpolate 4}}finish { ambient 1 diffuse 0}}");
					switch(ModelNum){
					case 0:sw->WriteLine("scale 0.5");sw->WriteLine("translate <0,0,10>");break;
					case 1:sw->WriteLine("scale 5");sw->WriteLine("translate <0,0,10>");break;
					case 2:sw->WriteLine("scale 10");break;
					case 3:sw->WriteLine("scale 1");break;
					case 4:sw->WriteLine("scale 0.7");sw->WriteLine("translate <50,-50,0>");break;
					}
					//sw->WriteLine("rotate<"+PerspectiveRightVector.x+","+PerspectiveRightVector.y+","+PerspectiveRightVector.z+">");
					sw->WriteLine("}");
					
				}

				sw->Close();
				System::Windows::Forms::MessageBox::Show("Complete");
				filename="\"C:\\Program Files\\POV-Ray\\v3.7\\bin\\pvengine.exe\" \+I"+filename+" +W1024 +H768  /EXIT";
				system(filename.c_str());
				system(path.c_str());
				
		
		
	}
	Void MainForm::Scene1_click(Object^ sender, EventArgs^ e)
	{
		SceneNum=0;
		SceneNumPOV=0;
	}
	Void MainForm::Scene2_click(Object^ sender, EventArgs^ e)
	{
		SceneNum=6;
		SceneNumPOV=1;
	}
	Void MainForm::Scene3_click(Object^ sender, EventArgs^ e)
	{
		SceneNum=12;
		SceneNumPOV=2;
	}
	Void MainForm::Scene4_click(Object^ sender, EventArgs^ e)
	{
		SceneNum=18;
		SceneNumPOV=3;
	}
	Void MainForm::Scene5_click(Object^ sender, EventArgs^ e)
	{
		SceneNum=24;
		SceneNumPOV=4;
	}

	

}