#pragma once
#include <highgui.h>
#include <cv.h>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

namespace HumanDetectionProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace cv;
	using namespace std;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Button^  button1;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

	private:
		int i;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(536, 30);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(32, 13);
			this->label1->TabIndex = 8;
			this->label1->Text = L"tinggi";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(479, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(51, 49);
			this->pictureBox1->TabIndex = 6;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(12, 67);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(984, 649);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 7;
			this->pictureBox2->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(422, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(51, 49);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Mulai";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click_1);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1008, 729);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		int tutup;
		int tinggiwebcam = -30;
private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 //load video background
			 VideoCapture cap("C:\\Users\\Rizky\\Desktop\\coba.mp4");
			 double fps = cap.get(CV_CAP_PROP_FPS);
			 cout << "Frame per seconds : " << fps << endl;

			 //akses kamera webcam
			 VideoCapture kamera(0);
			 kamera.set(CV_CAP_PROP_FRAME_WIDTH, 240);
			 kamera.set(CV_CAP_PROP_FRAME_HEIGHT, 144);

			 //membuat image container untuk webcam deteksi manusia
			 Mat img2;
			 HOGDescriptor hog;
			 hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

			 tutup = 0;
			 while (tutup == 0)
			 {
				 //membuat image container untuk video background
				 Mat background;
				 bool bSuccess = cap.read(background);

				 //webcam deteksi manusia
				 Mat img;
				 kamera >> img;
				 if (img.empty())
					 continue;

				 //convert to grayscale
				 cvtColor(img, img2, CV_BGR2GRAY);

				 vector<Rect> manusia, kotak_manusia;
				 hog.detectMultiScale(img2, manusia, 0, cv::Size(8, 8), cv::Size(20, 20), 1.05, 2);

				 size_t i, j;
				 for (i = 0; i<manusia.size(); i++)
				 {
					 Rect r = manusia[i];
					 for (j = 0; j<manusia.size(); j++)
					 if (j != i && (r & manusia[j]) == r)
						 break;
					 if (j == manusia.size())
						 kotak_manusia.push_back(r);
				 }

				 //membuat kotak menandai manusai
				 for (i = 0; i<kotak_manusia.size(); i++)
				 {
					 Rect r = kotak_manusia[i];
					 r.x += cvRound(r.width*0.25);
					 r.width = cvRound(r.width*0.5);
					 r.y += cvRound(r.height*0.1);
					 r.height = cvRound(r.height*0.75);
					 rectangle(img2, r.tl(), r.br(), Scalar(0, 0, 255), 0.25);

					 //menampilkan nilai y totak manusia di label
					 int tinggikotak = r.y;
					 int tinggi = -tinggikotak - tinggiwebcam;
					 int persamaan = 2 * tinggi;
					 this->label1->Text = L"tinggi : " + persamaan + " cm";
				 }

				 imshow("coba", img2);
				 //imshow("backgound", background);


				 //menampilkan webcam deteksi manusia di picturebox1
				 System::Drawing::Graphics^ graphics1 = pictureBox1->CreateGraphics();
				 System::IntPtr ptr1(img.ptr());
				 System::Drawing::Bitmap^ b1 = gcnew System::Drawing::Bitmap(img.cols,
					 img.rows, img.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr1);
				 System::Drawing::RectangleF rect1(0, 0, pictureBox1->Width, pictureBox1->Height);
				 graphics1->DrawImage(b1, rect1);

				 //menampilkan background di picturebox2
				 System::Drawing::Graphics^ graphics2 = pictureBox2->CreateGraphics();
				 System::IntPtr ptr2(background.ptr());
				 System::Drawing::Bitmap^ b2 = gcnew System::Drawing::Bitmap(background.cols,
					 background.rows, background.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr2);
				 System::Drawing::RectangleF rect2(0, 0, pictureBox2->Width, pictureBox2->Height);
				 graphics2->DrawImage(b2, rect2);

				 if (waitKey(1) >= 0)
					 break;

			 }
}
};
}

