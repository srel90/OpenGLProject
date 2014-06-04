#pragma once

namespace OpenGLProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;

	

	value class XYZ
	{
	public:
		Single x;
		Single y;
		Single z;
	};


	value class RGBColor
	{
	public:
		Single r;
		Single g;
		Single b;
	};
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		// constructor
		MainForm();

	protected:
		// destructor
		~MainForm();
	private:
		// methods
		Void DrawTitle(Zolver::OpenGLControl^ GLControl, String^ Title);
		Void DrawText(Zolver::OpenGLControl^ GLControl, String^ Text);
		Void Normalise(XYZ% vector);
		Void ClearBackGround();	
		// perspective methods
		Void PerspectiveShowAxisCheckBox_CheckedChanged(Object^ sender, EventArgs^ e);
		Void PerspectiveShowGridCheckBox_CheckedChanged(Object^ sender, EventArgs^ e);
		Void PerspectiveShowWireframeCheckBox_CheckedChanged(Object^ sender, EventArgs^ e);
		Void PerspectiveShowFrameRateCheckBox_CheckedChanged(Object^ sender, EventArgs^ e);
		Void PerspectiveShowGroundCheckBox_CheckedChanged(Object^ sender, EventArgs^ e);
		Void PerspectiveView_OpenGLInit(Object^ sender, EventArgs^ e);
		Void PerspectiveView_OpenGLRender(Object^ sender, EventArgs^ e);
		Void PerspectiveView_OpenGLMouseDown(Object^ sender, MouseEventArgs^ e);
		Void PerspectiveView_OpenGLMouseMove(Object^ sender, MouseEventArgs^ e);
		Void PerspectiveView_OpenGLMouseUp(Object^ sender, MouseEventArgs^ e);
		Void PerspectiveView_OpenGLMouseWheel(Object^ sender, MouseEventArgs^ e);
		Void vScrollBar1_Changed(Object^ sender, ScrollEventArgs^ e);
		Void SetPerspectiveCamera(Single glAngle, Single glDistance, Single glWidth, Single glHeight, Single glNear, Single glFar);
		Void loadSkybox(UINT textureArray[], LPSTR strFileName,int ID);
		Void loadTexture(UINT textureArray[], LPSTR strFileName,int ID);
		Void Draw_Skybox(float x, float y, float z, float width, float height, float length);
		Void Draw_Ground();
		Void DrawPerspectiveGrid();
		Void DrawPerspectiveAxis();
		Void Model1_click(Object^ sender, EventArgs^ e);
		Void Model2_click(Object^ sender, EventArgs^ e);
		Void Model3_click(Object^ sender, EventArgs^ e);
		Void Model4_click(Object^ sender, EventArgs^ e);
		Void Model5_click(Object^ sender, EventArgs^ e);

		Void Texture1_click(Object^ sender, EventArgs^ e);
		Void Texture2_click(Object^ sender, EventArgs^ e);

		Void Scene1_click(Object^ sender, EventArgs^ e);
		Void Scene2_click(Object^ sender, EventArgs^ e);
		Void Scene3_click(Object^ sender, EventArgs^ e);
		Void Scene4_click(Object^ sender, EventArgs^ e);
		Void Scene5_click(Object^ sender, EventArgs^ e);

		Void btnfont_Click(Object^  sender, EventArgs^  e);
		Void btncolor_Click(Object^  sender, EventArgs^  e);

		Void btnrender_Click(Object^ sender,EventArgs^ e);

		Void DrawPerspectiveTeapot();


		// perspective members
		Boolean PerspectiveShowAxis;
		Boolean PerspectiveShowGrid;
		Boolean PerspectiveShowWireFrame;
		Boolean PerspectiveShowGround;
		Single PerspectiveRotateX;
		Single PerspectiveRotateY;
		Single PerspectiveCameraAngle;
		Single PerspectiveCameraNear;
		Single PerspectiveCameraFar;
		Single PerspectiveCameraFocus;
		Point PerspectiveLastPosition;
		Single PerspectiveRotateX_old;	
		Single PerspectiveRotateY_old;

		Int16 ModelNum;
		Int16 ModelTex;
		Int16 SceneNum;
		Int16 SceneNumPOV;
		Int16 color;

		String^ ScreenText;
		
		Int16 red,green,blue;
		







	private: Zolver::OpenGLControl^  PerspectiveView;
	private: System::Windows::Forms::Button^  btncolor;



	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Button^  btnfont;
	private: System::Windows::Forms::Button^  btnrender;
















	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::Button^  Model2;
	private: System::Windows::Forms::Button^  Model1;
	private: System::Windows::Forms::Button^  Model5;
	private: System::Windows::Forms::Button^  Model4;
	private: System::Windows::Forms::Button^  Model3;
	private: System::Windows::Forms::Button^  Scene1;
	private: System::Windows::Forms::Button^  Scene2;
	private: System::Windows::Forms::VScrollBar^  vScrollBar1;
	private: System::Windows::Forms::CheckBox^  PerspectiveShowAxisCheckBox;
	private: System::Windows::Forms::CheckBox^  PerspectiveShowGridCheckBox;
	private: System::Windows::Forms::CheckBox^  PerspectiveShowWireframeCheckBox;
	private: System::Windows::Forms::CheckBox^  PerspectiveShowFrameRateCheckBox;
	private: System::Windows::Forms::Button^  Scene3;
	private: System::Windows::Forms::Button^  Scene4;
	private: System::Windows::Forms::CheckBox^  PerspectiveShowGroundCheckBox;
	private: System::Windows::Forms::Button^  Scene5;
private: System::Windows::Forms::Button^  Texture1;
private: System::Windows::Forms::Button^  Texture2;
private: System::Windows::Forms::TextBox^  textBox1;
private: System::Windows::Forms::ColorDialog^  colorDialog1;














			 	
	protected: 

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->PerspectiveView = (gcnew Zolver::OpenGLControl());
			this->btncolor = (gcnew System::Windows::Forms::Button());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->Model5 = (gcnew System::Windows::Forms::Button());
			this->Model4 = (gcnew System::Windows::Forms::Button());
			this->Model3 = (gcnew System::Windows::Forms::Button());
			this->Model2 = (gcnew System::Windows::Forms::Button());
			this->Model1 = (gcnew System::Windows::Forms::Button());
			this->btnfont = (gcnew System::Windows::Forms::Button());
			this->btnrender = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->Texture2 = (gcnew System::Windows::Forms::Button());
			this->Texture1 = (gcnew System::Windows::Forms::Button());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->Scene5 = (gcnew System::Windows::Forms::Button());
			this->Scene4 = (gcnew System::Windows::Forms::Button());
			this->Scene3 = (gcnew System::Windows::Forms::Button());
			this->Scene2 = (gcnew System::Windows::Forms::Button());
			this->Scene1 = (gcnew System::Windows::Forms::Button());
			this->vScrollBar1 = (gcnew System::Windows::Forms::VScrollBar());
			this->PerspectiveShowAxisCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->PerspectiveShowGridCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->PerspectiveShowWireframeCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->PerspectiveShowFrameRateCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->PerspectiveShowGroundCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->SuspendLayout();
			// 
			// PerspectiveView
			// 
			this->PerspectiveView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->PerspectiveView->AutomaticSwapBuffer = true;
			this->PerspectiveView->AverageFrameRateBase = 25;
			this->PerspectiveView->Cursor = System::Windows::Forms::Cursors::Default;
			this->PerspectiveView->Location = System::Drawing::Point(12, 12);
			this->PerspectiveView->MaxFrameRate = 60;
			this->PerspectiveView->Name = L"PerspectiveView";
			this->PerspectiveView->PreciseTiming = false;
			this->PerspectiveView->RenderStyle = Zolver::ERenderStyle::Auto;
			this->PerspectiveView->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->PerspectiveView->ShowFrameRate = false;
			this->PerspectiveView->Size = System::Drawing::Size(531, 437);
			this->PerspectiveView->TabIndex = 2;
			this->PerspectiveView->Text = L"Perspective";
			this->PerspectiveView->OpenGLMouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::PerspectiveView_OpenGLMouseWheel);
			this->PerspectiveView->OpenGLMouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::PerspectiveView_OpenGLMouseUp);
			this->PerspectiveView->OpenGLMouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::PerspectiveView_OpenGLMouseMove);
			this->PerspectiveView->OpenGLMouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::PerspectiveView_OpenGLMouseDown);
			this->PerspectiveView->OpenGLRender += gcnew System::EventHandler(this, &MainForm::PerspectiveView_OpenGLRender);
			this->PerspectiveView->OpenGLInit += gcnew System::EventHandler(this, &MainForm::PerspectiveView_OpenGLInit);
			// 
			// btncolor
			// 
			this->btncolor->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btncolor->Location = System::Drawing::Point(709, 406);
			this->btncolor->Name = L"btncolor";
			this->btncolor->Size = System::Drawing::Size(66, 22);
			this->btncolor->TabIndex = 5;
			this->btncolor->Text = L"Pick Color";
			this->btncolor->UseVisualStyleBackColor = true;
			this->btncolor->Click += gcnew System::EventHandler(this, &MainForm::btncolor_Click);
			// 
			// groupBox3
			// 
			this->groupBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox3->Controls->Add(this->Model5);
			this->groupBox3->Controls->Add(this->Model4);
			this->groupBox3->Controls->Add(this->Model3);
			this->groupBox3->Controls->Add(this->Model2);
			this->groupBox3->Controls->Add(this->Model1);
			this->groupBox3->Location = System::Drawing::Point(575, 12);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(99, 357);
			this->groupBox3->TabIndex = 6;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Select Model";
			// 
			// Model5
			// 
			this->Model5->Location = System::Drawing::Point(9, 284);
			this->Model5->Name = L"Model5";
			this->Model5->Size = System::Drawing::Size(75, 60);
			this->Model5->TabIndex = 0;
			this->Model5->Text = L"Head Hunter";
			this->Model5->UseVisualStyleBackColor = true;
			this->Model5->Click += gcnew System::EventHandler(this, &MainForm::Model5_click);
			// 
			// Model4
			// 
			this->Model4->Location = System::Drawing::Point(9, 218);
			this->Model4->Name = L"Model4";
			this->Model4->Size = System::Drawing::Size(75, 60);
			this->Model4->TabIndex = 0;
			this->Model4->Text = L"Cat";
			this->Model4->UseVisualStyleBackColor = true;
			this->Model4->Click += gcnew System::EventHandler(this, &MainForm::Model4_click);
			// 
			// Model3
			// 
			this->Model3->Location = System::Drawing::Point(9, 152);
			this->Model3->Name = L"Model3";
			this->Model3->Size = System::Drawing::Size(75, 60);
			this->Model3->TabIndex = 0;
			this->Model3->Text = L"Antelope";
			this->Model3->UseVisualStyleBackColor = true;
			this->Model3->Click += gcnew System::EventHandler(this, &MainForm::Model3_click);
			// 
			// Model2
			// 
			this->Model2->Location = System::Drawing::Point(9, 86);
			this->Model2->Name = L"Model2";
			this->Model2->Size = System::Drawing::Size(75, 60);
			this->Model2->TabIndex = 0;
			this->Model2->Text = L"Shark";
			this->Model2->UseVisualStyleBackColor = true;
			this->Model2->Click += gcnew System::EventHandler(this, &MainForm::Model2_click);
			// 
			// Model1
			// 
			this->Model1->Location = System::Drawing::Point(9, 20);
			this->Model1->Name = L"Model1";
			this->Model1->Size = System::Drawing::Size(75, 60);
			this->Model1->TabIndex = 0;
			this->Model1->Text = L"Dolphin";
			this->Model1->UseVisualStyleBackColor = true;
			this->Model1->Click += gcnew System::EventHandler(this, &MainForm::Model1_click);
			// 
			// btnfont
			// 
			this->btnfont->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnfont->Location = System::Drawing::Point(640, 406);
			this->btnfont->Name = L"btnfont";
			this->btnfont->Size = System::Drawing::Size(63, 22);
			this->btnfont->TabIndex = 5;
			this->btnfont->Text = L"Set Font";
			this->btnfont->UseVisualStyleBackColor = true;
			this->btnfont->Click += gcnew System::EventHandler(this, &MainForm::btnfont_Click);
			// 
			// btnrender
			// 
			this->btnrender->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnrender->Location = System::Drawing::Point(680, 465);
			this->btnrender->Name = L"btnrender";
			this->btnrender->Size = System::Drawing::Size(95, 86);
			this->btnrender->TabIndex = 5;
			this->btnrender->Text = L"Render";
			this->btnrender->UseVisualStyleBackColor = true;
			this->btnrender->Click += gcnew System::EventHandler(this, &MainForm::btnrender_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox4->Controls->Add(this->Texture2);
			this->groupBox4->Controls->Add(this->Texture1);
			this->groupBox4->Location = System::Drawing::Point(680, 12);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(95, 357);
			this->groupBox4->TabIndex = 6;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Select Style";
			// 
			// Texture2
			// 
			this->Texture2->Location = System::Drawing::Point(6, 86);
			this->Texture2->Name = L"Texture2";
			this->Texture2->Size = System::Drawing::Size(75, 60);
			this->Texture2->TabIndex = 0;
			this->Texture2->Text = L"Style II";
			this->Texture2->UseVisualStyleBackColor = true;
			this->Texture2->Click += gcnew System::EventHandler(this, &MainForm::Texture2_click);
			// 
			// Texture1
			// 
			this->Texture1->Location = System::Drawing::Point(6, 19);
			this->Texture1->Name = L"Texture1";
			this->Texture1->Size = System::Drawing::Size(75, 60);
			this->Texture1->TabIndex = 0;
			this->Texture1->Text = L"Style I";
			this->Texture1->UseVisualStyleBackColor = true;
			this->Texture1->Click += gcnew System::EventHandler(this, &MainForm::Texture1_click);
			// 
			// groupBox5
			// 
			this->groupBox5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox5->Controls->Add(this->Scene5);
			this->groupBox5->Controls->Add(this->Scene4);
			this->groupBox5->Controls->Add(this->Scene3);
			this->groupBox5->Controls->Add(this->Scene2);
			this->groupBox5->Controls->Add(this->Scene1);
			this->groupBox5->Location = System::Drawing::Point(12, 455);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(417, 94);
			this->groupBox5->TabIndex = 6;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Select Scene";
			// 
			// Scene5
			// 
			this->Scene5->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"Scene5.Image")));
			this->Scene5->Location = System::Drawing::Point(329, 19);
			this->Scene5->Name = L"Scene5";
			this->Scene5->Size = System::Drawing::Size(75, 60);
			this->Scene5->TabIndex = 0;
			this->Scene5->Text = L"Scene 5";
			this->Scene5->UseVisualStyleBackColor = true;
			this->Scene5->Click += gcnew System::EventHandler(this, &MainForm::Scene5_click);
			// 
			// Scene4
			// 
			this->Scene4->ForeColor = System::Drawing::Color::White;
			this->Scene4->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"Scene4.Image")));
			this->Scene4->Location = System::Drawing::Point(249, 19);
			this->Scene4->Name = L"Scene4";
			this->Scene4->Size = System::Drawing::Size(75, 60);
			this->Scene4->TabIndex = 0;
			this->Scene4->Text = L"Scene 4";
			this->Scene4->UseVisualStyleBackColor = true;
			this->Scene4->Click += gcnew System::EventHandler(this, &MainForm::Scene4_click);
			// 
			// Scene3
			// 
			this->Scene3->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"Scene3.Image")));
			this->Scene3->Location = System::Drawing::Point(168, 19);
			this->Scene3->Name = L"Scene3";
			this->Scene3->Size = System::Drawing::Size(75, 60);
			this->Scene3->TabIndex = 0;
			this->Scene3->Text = L"Scene 3";
			this->Scene3->UseVisualStyleBackColor = true;
			this->Scene3->Click += gcnew System::EventHandler(this, &MainForm::Scene3_click);
			// 
			// Scene2
			// 
			this->Scene2->ForeColor = System::Drawing::Color::White;
			this->Scene2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"Scene2.Image")));
			this->Scene2->Location = System::Drawing::Point(87, 19);
			this->Scene2->Name = L"Scene2";
			this->Scene2->Size = System::Drawing::Size(75, 60);
			this->Scene2->TabIndex = 0;
			this->Scene2->Text = L"Scene 2";
			this->Scene2->UseVisualStyleBackColor = true;
			this->Scene2->Click += gcnew System::EventHandler(this, &MainForm::Scene2_click);
			// 
			// Scene1
			// 
			this->Scene1->ForeColor = System::Drawing::Color::White;
			this->Scene1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"Scene1.Image")));
			this->Scene1->Location = System::Drawing::Point(6, 19);
			this->Scene1->Name = L"Scene1";
			this->Scene1->Size = System::Drawing::Size(75, 60);
			this->Scene1->TabIndex = 0;
			this->Scene1->Text = L"Scene 1";
			this->Scene1->UseVisualStyleBackColor = true;
			this->Scene1->Click += gcnew System::EventHandler(this, &MainForm::Scene1_click);
			// 
			// vScrollBar1
			// 
			this->vScrollBar1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->vScrollBar1->Location = System::Drawing::Point(552, 12);
			this->vScrollBar1->Maximum = 1000;
			this->vScrollBar1->Minimum = 2;
			this->vScrollBar1->Name = L"vScrollBar1";
			this->vScrollBar1->Size = System::Drawing::Size(20, 437);
			this->vScrollBar1->TabIndex = 7;
			this->vScrollBar1->Value = 40;
			this->vScrollBar1->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MainForm::vScrollBar1_Changed);
			// 
			// PerspectiveShowAxisCheckBox
			// 
			this->PerspectiveShowAxisCheckBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->PerspectiveShowAxisCheckBox->AutoSize = true;
			this->PerspectiveShowAxisCheckBox->Checked = true;
			this->PerspectiveShowAxisCheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->PerspectiveShowAxisCheckBox->Location = System::Drawing::Point(435, 465);
			this->PerspectiveShowAxisCheckBox->Name = L"PerspectiveShowAxisCheckBox";
			this->PerspectiveShowAxisCheckBox->Size = System::Drawing::Size(75, 17);
			this->PerspectiveShowAxisCheckBox->TabIndex = 9;
			this->PerspectiveShowAxisCheckBox->Text = L"Show Axis";
			this->PerspectiveShowAxisCheckBox->UseVisualStyleBackColor = true;
			this->PerspectiveShowAxisCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainForm::PerspectiveShowAxisCheckBox_CheckedChanged);
			// 
			// PerspectiveShowGridCheckBox
			// 
			this->PerspectiveShowGridCheckBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->PerspectiveShowGridCheckBox->AutoSize = true;
			this->PerspectiveShowGridCheckBox->Checked = true;
			this->PerspectiveShowGridCheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->PerspectiveShowGridCheckBox->Location = System::Drawing::Point(435, 488);
			this->PerspectiveShowGridCheckBox->Name = L"PerspectiveShowGridCheckBox";
			this->PerspectiveShowGridCheckBox->Size = System::Drawing::Size(75, 17);
			this->PerspectiveShowGridCheckBox->TabIndex = 8;
			this->PerspectiveShowGridCheckBox->Text = L"Show Grid";
			this->PerspectiveShowGridCheckBox->UseVisualStyleBackColor = true;
			this->PerspectiveShowGridCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainForm::PerspectiveShowGridCheckBox_CheckedChanged);
			// 
			// PerspectiveShowWireframeCheckBox
			// 
			this->PerspectiveShowWireframeCheckBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->PerspectiveShowWireframeCheckBox->AutoSize = true;
			this->PerspectiveShowWireframeCheckBox->Location = System::Drawing::Point(435, 509);
			this->PerspectiveShowWireframeCheckBox->Name = L"PerspectiveShowWireframeCheckBox";
			this->PerspectiveShowWireframeCheckBox->Size = System::Drawing::Size(104, 17);
			this->PerspectiveShowWireframeCheckBox->TabIndex = 11;
			this->PerspectiveShowWireframeCheckBox->Text = L"Show Wireframe";
			this->PerspectiveShowWireframeCheckBox->UseVisualStyleBackColor = true;
			this->PerspectiveShowWireframeCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainForm::PerspectiveShowWireframeCheckBox_CheckedChanged);
			// 
			// PerspectiveShowFrameRateCheckBox
			// 
			this->PerspectiveShowFrameRateCheckBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->PerspectiveShowFrameRateCheckBox->AutoSize = true;
			this->PerspectiveShowFrameRateCheckBox->Location = System::Drawing::Point(435, 532);
			this->PerspectiveShowFrameRateCheckBox->Name = L"PerspectiveShowFrameRateCheckBox";
			this->PerspectiveShowFrameRateCheckBox->Size = System::Drawing::Size(108, 17);
			this->PerspectiveShowFrameRateCheckBox->TabIndex = 10;
			this->PerspectiveShowFrameRateCheckBox->Text = L"Show FrameRate";
			this->PerspectiveShowFrameRateCheckBox->UseVisualStyleBackColor = true;
			this->PerspectiveShowFrameRateCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainForm::PerspectiveShowFrameRateCheckBox_CheckedChanged);
			// 
			// PerspectiveShowGroundCheckBox
			// 
			this->PerspectiveShowGroundCheckBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->PerspectiveShowGroundCheckBox->AutoSize = true;
			this->PerspectiveShowGroundCheckBox->Location = System::Drawing::Point(542, 465);
			this->PerspectiveShowGroundCheckBox->Name = L"PerspectiveShowGroundCheckBox";
			this->PerspectiveShowGroundCheckBox->Size = System::Drawing::Size(91, 17);
			this->PerspectiveShowGroundCheckBox->TabIndex = 10;
			this->PerspectiveShowGroundCheckBox->Text = L"Show Ground";
			this->PerspectiveShowGroundCheckBox->UseVisualStyleBackColor = true;
			this->PerspectiveShowGroundCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainForm::PerspectiveShowGroundCheckBox_CheckedChanged);
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->Location = System::Drawing::Point(575, 381);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(197, 20);
			this->textBox1->TabIndex = 12;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->PerspectiveShowGroundCheckBox);
			this->Controls->Add(this->PerspectiveShowWireframeCheckBox);
			this->Controls->Add(this->PerspectiveShowFrameRateCheckBox);
			this->Controls->Add(this->PerspectiveShowAxisCheckBox);
			this->Controls->Add(this->PerspectiveShowGridCheckBox);
			this->Controls->Add(this->vScrollBar1);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->btnrender);
			this->Controls->Add(this->btnfont);
			this->Controls->Add(this->btncolor);
			this->Controls->Add(this->PerspectiveView);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Pet Creator Program";
			this->groupBox3->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->groupBox5->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

};
}
