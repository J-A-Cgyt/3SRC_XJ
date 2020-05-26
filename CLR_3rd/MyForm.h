#pragma once

namespace CLR3rd {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm ժҪ
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  �ڴ˴���ӹ��캯������
			//
		}

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	protected:
	private: System::Windows::Forms::ToolStripStatusLabel^  ֡����;
	private: System::Windows::Forms::ToolStripStatusLabel^  Num_fps;
	private: System::Windows::Forms::ToolStripStatusLabel^  FPS;
	private: System::Windows::Forms::ToolStripStatusLabel^  ��Ƶ�ֱ���;
	private: System::Windows::Forms::ToolStripStatusLabel^  cols;
	private: System::Windows::Forms::ToolStripStatusLabel^  ��;
	private: System::Windows::Forms::ToolStripStatusLabel^  rows;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  �ļ�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �½�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ��ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ����ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ���ΪToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �ر�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �༭ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �˲�ǿ�ȵ���ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ����ѡ����ֵToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ����ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �ź�Դѡ��ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ������ϲ���ToolStripMenuItem;

	private:
		/// <summary>
		/// ����������������
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ�޸�
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
		/// </summary>
		void InitializeComponent(void)
		{
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->�ļ�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�༭ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�½�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���ΪToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�ر�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�˲�ǿ�ȵ���ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����ѡ����ֵToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�ź�Դѡ��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->������ϲ���ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->֡���� = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->Num_fps = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->FPS = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->��Ƶ�ֱ��� = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->cols = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->�� = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->rows = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->statusStrip1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// statusStrip1
			// 
			this->statusStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->֡����, this->Num_fps,
					this->FPS, this->��Ƶ�ֱ���, this->cols, this->��, this->rows
			});
			this->statusStrip1->Location = System::Drawing::Point(0, 697);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(1114, 25);
			this->statusStrip1->TabIndex = 0;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->�ļ�ToolStripMenuItem,
					this->�༭ToolStripMenuItem, this->����ToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1114, 28);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// �ļ�ToolStripMenuItem
			// 
			this->�ļ�ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->�½�ToolStripMenuItem,
					this->��ToolStripMenuItem, this->����ToolStripMenuItem, this->���ΪToolStripMenuItem, this->�ر�ToolStripMenuItem
			});
			this->�ļ�ToolStripMenuItem->Name = L"�ļ�ToolStripMenuItem";
			this->�ļ�ToolStripMenuItem->Size = System::Drawing::Size(51, 24);
			this->�ļ�ToolStripMenuItem->Text = L"�ļ�";
			// 
			// �༭ToolStripMenuItem
			// 
			this->�༭ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->�˲�ǿ�ȵ���ToolStripMenuItem,
					this->����ѡ����ֵToolStripMenuItem
			});
			this->�༭ToolStripMenuItem->Name = L"�༭ToolStripMenuItem";
			this->�༭ToolStripMenuItem->Size = System::Drawing::Size(51, 24);
			this->�༭ToolStripMenuItem->Text = L"�༭";
			// 
			// ����ToolStripMenuItem
			// 
			this->����ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->�ź�Դѡ��ToolStripMenuItem,
					this->������ϲ���ToolStripMenuItem
			});
			this->����ToolStripMenuItem->Name = L"����ToolStripMenuItem";
			this->����ToolStripMenuItem->Size = System::Drawing::Size(51, 24);
			this->����ToolStripMenuItem->Text = L"����";
			// 
			// �½�ToolStripMenuItem
			// 
			this->�½�ToolStripMenuItem->Name = L"�½�ToolStripMenuItem";
			this->�½�ToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->�½�ToolStripMenuItem->Text = L"�½�";
			// 
			// ��ToolStripMenuItem
			// 
			this->��ToolStripMenuItem->Name = L"��ToolStripMenuItem";
			this->��ToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->��ToolStripMenuItem->Text = L"��";
			// 
			// ����ToolStripMenuItem
			// 
			this->����ToolStripMenuItem->Name = L"����ToolStripMenuItem";
			this->����ToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->����ToolStripMenuItem->Text = L"����";
			// 
			// ���ΪToolStripMenuItem
			// 
			this->���ΪToolStripMenuItem->Name = L"���ΪToolStripMenuItem";
			this->���ΪToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->���ΪToolStripMenuItem->Text = L"���Ϊ";
			// 
			// �ر�ToolStripMenuItem
			// 
			this->�ر�ToolStripMenuItem->Name = L"�ر�ToolStripMenuItem";
			this->�ر�ToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->�ر�ToolStripMenuItem->Text = L"�ر�";
			// 
			// �˲�ǿ�ȵ���ToolStripMenuItem
			// 
			this->�˲�ǿ�ȵ���ToolStripMenuItem->Name = L"�˲�ǿ�ȵ���ToolStripMenuItem";
			this->�˲�ǿ�ȵ���ToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->�˲�ǿ�ȵ���ToolStripMenuItem->Text = L"�˲�ǿ�ȵ���";
			// 
			// ����ѡ����ֵToolStripMenuItem
			// 
			this->����ѡ����ֵToolStripMenuItem->Name = L"����ѡ����ֵToolStripMenuItem";
			this->����ѡ����ֵToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->����ѡ����ֵToolStripMenuItem->Text = L"����ѡ����ֵ";
			// 
			// �ź�Դѡ��ToolStripMenuItem
			// 
			this->�ź�Դѡ��ToolStripMenuItem->Name = L"�ź�Դѡ��ToolStripMenuItem";
			this->�ź�Դѡ��ToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->�ź�Դѡ��ToolStripMenuItem->Text = L"�ź�Դѡ��";
			// 
			// ������ϲ���ToolStripMenuItem
			// 
			this->������ϲ���ToolStripMenuItem->Name = L"������ϲ���ToolStripMenuItem";
			this->������ϲ���ToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->������ϲ���ToolStripMenuItem->Text = L"������ϲ���";
			// 
			// ֡����
			// 
			this->֡����->Name = L"֡����";
			this->֡����->Size = System::Drawing::Size(69, 20);
			this->֡����->Text = L"֡���ʣ�";
			// 
			// Num_fps
			// 
			this->Num_fps->Name = L"Num_fps";
			this->Num_fps->Size = System::Drawing::Size(27, 20);
			this->Num_fps->Text = L"00";
			// 
			// FPS
			// 
			this->FPS->Name = L"FPS";
			this->FPS->Size = System::Drawing::Size(35, 20);
			this->FPS->Text = L"FPS";
			// 
			// ��Ƶ�ֱ���
			// 
			this->��Ƶ�ֱ���->Margin = System::Windows::Forms::Padding(50, 3, 0, 2);
			this->��Ƶ�ֱ���->Name = L"��Ƶ�ֱ���";
			this->��Ƶ�ֱ���->Size = System::Drawing::Size(99, 20);
			this->��Ƶ�ֱ���->Text = L"��Ƶ�ֱ��ʣ�";
			// 
			// cols
			// 
			this->cols->Name = L"cols";
			this->cols->Size = System::Drawing::Size(45, 20);
			this->cols->Text = L"0000";
			// 
			// ��
			// 
			this->��->Name = L"��";
			this->��->Size = System::Drawing::Size(16, 20);
			this->��->Text = L"*";
			// 
			// rows
			// 
			this->rows->Name = L"rows";
			this->rows->Size = System::Drawing::Size(45, 20);
			this->rows->Text = L"0000";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1114, 722);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
