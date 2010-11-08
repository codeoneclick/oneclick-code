#pragma once


namespace GEgit {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::Panel^  MainViewport;

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
			this->MainViewport = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// MainViewport
			// 
			this->MainViewport->AutoSize = true;
			this->MainViewport->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->MainViewport->Location = System::Drawing::Point(12, 12);
			this->MainViewport->Name = L"MainViewport";
			this->MainViewport->Size = System::Drawing::Size(800, 600);
			this->MainViewport->TabIndex = 0;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1315, 793);
			this->Controls->Add(this->MainViewport);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MainForm";
			this->Text = L"GEdit";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}

