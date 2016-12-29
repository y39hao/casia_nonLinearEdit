#pragma once

namespace NonLinearEdit {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ChooseFpsuseForm
	/// </summary>
	public ref class ChooseFpsuseForm : public System::Windows::Forms::Form
	{
	public:
		ChooseFpsuseForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			fpsUse = 0;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ChooseFpsuseForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  pnl_fpsChange;
	protected: 
	private: DevComponents::DotNetBar::LabelX^  labelX1;
	private: System::Windows::Forms::Button^  btn_fpsCancel;
	private: System::Windows::Forms::Button^  btn_FpsApply;
	public: System::Windows::Forms::TextBox^  txtbx_fpsUse;
	public: float fpsUse;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ChooseFpsuseForm::typeid));
			this->pnl_fpsChange = (gcnew System::Windows::Forms::Panel());
			this->btn_fpsCancel = (gcnew System::Windows::Forms::Button());
			this->btn_FpsApply = (gcnew System::Windows::Forms::Button());
			this->txtbx_fpsUse = (gcnew System::Windows::Forms::TextBox());
			this->labelX1 = (gcnew DevComponents::DotNetBar::LabelX());
			this->pnl_fpsChange->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnl_fpsChange
			// 
			this->pnl_fpsChange->BackColor = System::Drawing::Color::SteelBlue;
			this->pnl_fpsChange->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pnl_fpsChange.BackgroundImage")));
			this->pnl_fpsChange->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pnl_fpsChange->Controls->Add(this->btn_fpsCancel);
			this->pnl_fpsChange->Controls->Add(this->btn_FpsApply);
			this->pnl_fpsChange->Controls->Add(this->txtbx_fpsUse);
			this->pnl_fpsChange->Controls->Add(this->labelX1);
			this->pnl_fpsChange->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnl_fpsChange->Location = System::Drawing::Point(0, 0);
			this->pnl_fpsChange->Name = L"pnl_fpsChange";
			this->pnl_fpsChange->Size = System::Drawing::Size(377, 194);
			this->pnl_fpsChange->TabIndex = 0;
			// 
			// btn_fpsCancel
			// 
			this->btn_fpsCancel->BackColor = System::Drawing::Color::SteelBlue;
			this->btn_fpsCancel->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->btn_fpsCancel->ForeColor = System::Drawing::Color::White;
			this->btn_fpsCancel->Location = System::Drawing::Point(219, 137);
			this->btn_fpsCancel->Name = L"btn_fpsCancel";
			this->btn_fpsCancel->Size = System::Drawing::Size(75, 23);
			this->btn_fpsCancel->TabIndex = 3;
			this->btn_fpsCancel->Text = L"取消";
			this->btn_fpsCancel->UseVisualStyleBackColor = false;
			this->btn_fpsCancel->Click += gcnew System::EventHandler(this, &ChooseFpsuseForm::btn_fpsCancel_Click);
			// 
			// btn_FpsApply
			// 
			this->btn_FpsApply->BackColor = System::Drawing::Color::SteelBlue;
			this->btn_FpsApply->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->btn_FpsApply->ForeColor = System::Drawing::Color::White;
			this->btn_FpsApply->Location = System::Drawing::Point(51, 137);
			this->btn_FpsApply->Name = L"btn_FpsApply";
			this->btn_FpsApply->Size = System::Drawing::Size(75, 23);
			this->btn_FpsApply->TabIndex = 2;
			this->btn_FpsApply->Text = L"确定";
			this->btn_FpsApply->UseVisualStyleBackColor = false;
			this->btn_FpsApply->Click += gcnew System::EventHandler(this, &ChooseFpsuseForm::btn_FpsApply_Click);
			// 
			// txtbx_fpsUse
			// 
			this->txtbx_fpsUse->Location = System::Drawing::Point(216, 74);
			this->txtbx_fpsUse->Name = L"txtbx_fpsUse";
			this->txtbx_fpsUse->Size = System::Drawing::Size(100, 21);
			this->txtbx_fpsUse->TabIndex = 4;
			// 
			// labelX1
			// 
			this->labelX1->BackColor = System::Drawing::Color::Transparent;
			// 
			// 
			// 
			this->labelX1->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->labelX1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->labelX1->ForeColor = System::Drawing::Color::White;
			this->labelX1->Location = System::Drawing::Point(34, 67);
			this->labelX1->Name = L"labelX1";
			this->labelX1->Size = System::Drawing::Size(176, 36);
			this->labelX1->TabIndex = 0;
			this->labelX1->Text = L"请设置间隔帧数 ：";
			// 
			// ChooseFpsuseForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(377, 194);
			this->Controls->Add(this->pnl_fpsChange);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"ChooseFpsuseForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"ChooseFpsuseForm";
			this->pnl_fpsChange->ResumeLayout(false);
			this->pnl_fpsChange->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion




private: System::Void txtbx_fpsUse_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode == Keys::Enter && !e->Control)
			 {
				 try{
					 int fpsInterval = Convert::ToInt32(txtbx_fpsUse->Text);
					 if ((fpsInterval<20)||(fpsInterval>100))
					 {
						 MessageBox::Show("输入无效，请输入20到100范围内的整数。");
					 }
					 else
					 {
						 fpsUse = fpsInterval;
					
					 }
				 }
				 catch(System::Exception^ e)
				 {
					 String ^ i = e->ToString();
					 MessageBox::Show(i);
					 txtbx_fpsUse->Clear();
				 }
			 }
		 }
private: System::Void btn_FpsApply_Click(System::Object^  sender, System::EventArgs^  e) {
			 fpsUse =  Convert::ToInt32(txtbx_fpsUse->Text);
			 this->Close();
		 }
private: System::Void btn_fpsCancel_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
};
}
