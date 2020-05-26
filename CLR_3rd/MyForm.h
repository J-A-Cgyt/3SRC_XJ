#pragma once

namespace CLR3rd {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm 摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
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
	private: System::Windows::Forms::ToolStripStatusLabel^  帧速率;
	private: System::Windows::Forms::ToolStripStatusLabel^  Num_fps;
	private: System::Windows::Forms::ToolStripStatusLabel^  FPS;
	private: System::Windows::Forms::ToolStripStatusLabel^  视频分辨率;
	private: System::Windows::Forms::ToolStripStatusLabel^  cols;
	private: System::Windows::Forms::ToolStripStatusLabel^  乘;
	private: System::Windows::Forms::ToolStripStatusLabel^  rows;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  文件ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  新建ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  打开ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  保存ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  另存为ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  关闭ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  编辑ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  滤波强度调整ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  特征选择阈值ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  工具ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  信号源选择ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  参数组合测试ToolStripMenuItem;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->文件ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->编辑ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->工具ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->新建ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->打开ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->保存ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->另存为ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->关闭ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->滤波强度调整ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->特征选择阈值ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->信号源选择ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->参数组合测试ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->帧速率 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->Num_fps = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->FPS = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->视频分辨率 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->cols = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->乘 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->rows = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->statusStrip1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// statusStrip1
			// 
			this->statusStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->帧速率, this->Num_fps,
					this->FPS, this->视频分辨率, this->cols, this->乘, this->rows
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
				this->文件ToolStripMenuItem,
					this->编辑ToolStripMenuItem, this->工具ToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1114, 28);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// 文件ToolStripMenuItem
			// 
			this->文件ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->新建ToolStripMenuItem,
					this->打开ToolStripMenuItem, this->保存ToolStripMenuItem, this->另存为ToolStripMenuItem, this->关闭ToolStripMenuItem
			});
			this->文件ToolStripMenuItem->Name = L"文件ToolStripMenuItem";
			this->文件ToolStripMenuItem->Size = System::Drawing::Size(51, 24);
			this->文件ToolStripMenuItem->Text = L"文件";
			// 
			// 编辑ToolStripMenuItem
			// 
			this->编辑ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->滤波强度调整ToolStripMenuItem,
					this->特征选择阈值ToolStripMenuItem
			});
			this->编辑ToolStripMenuItem->Name = L"编辑ToolStripMenuItem";
			this->编辑ToolStripMenuItem->Size = System::Drawing::Size(51, 24);
			this->编辑ToolStripMenuItem->Text = L"编辑";
			// 
			// 工具ToolStripMenuItem
			// 
			this->工具ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->信号源选择ToolStripMenuItem,
					this->参数组合测试ToolStripMenuItem
			});
			this->工具ToolStripMenuItem->Name = L"工具ToolStripMenuItem";
			this->工具ToolStripMenuItem->Size = System::Drawing::Size(51, 24);
			this->工具ToolStripMenuItem->Text = L"工具";
			// 
			// 新建ToolStripMenuItem
			// 
			this->新建ToolStripMenuItem->Name = L"新建ToolStripMenuItem";
			this->新建ToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->新建ToolStripMenuItem->Text = L"新建";
			// 
			// 打开ToolStripMenuItem
			// 
			this->打开ToolStripMenuItem->Name = L"打开ToolStripMenuItem";
			this->打开ToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->打开ToolStripMenuItem->Text = L"打开";
			// 
			// 保存ToolStripMenuItem
			// 
			this->保存ToolStripMenuItem->Name = L"保存ToolStripMenuItem";
			this->保存ToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->保存ToolStripMenuItem->Text = L"保存";
			// 
			// 另存为ToolStripMenuItem
			// 
			this->另存为ToolStripMenuItem->Name = L"另存为ToolStripMenuItem";
			this->另存为ToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->另存为ToolStripMenuItem->Text = L"另存为";
			// 
			// 关闭ToolStripMenuItem
			// 
			this->关闭ToolStripMenuItem->Name = L"关闭ToolStripMenuItem";
			this->关闭ToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->关闭ToolStripMenuItem->Text = L"关闭";
			// 
			// 滤波强度调整ToolStripMenuItem
			// 
			this->滤波强度调整ToolStripMenuItem->Name = L"滤波强度调整ToolStripMenuItem";
			this->滤波强度调整ToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->滤波强度调整ToolStripMenuItem->Text = L"滤波强度调整";
			// 
			// 特征选择阈值ToolStripMenuItem
			// 
			this->特征选择阈值ToolStripMenuItem->Name = L"特征选择阈值ToolStripMenuItem";
			this->特征选择阈值ToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->特征选择阈值ToolStripMenuItem->Text = L"特征选择阈值";
			// 
			// 信号源选择ToolStripMenuItem
			// 
			this->信号源选择ToolStripMenuItem->Name = L"信号源选择ToolStripMenuItem";
			this->信号源选择ToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->信号源选择ToolStripMenuItem->Text = L"信号源选择";
			// 
			// 参数组合测试ToolStripMenuItem
			// 
			this->参数组合测试ToolStripMenuItem->Name = L"参数组合测试ToolStripMenuItem";
			this->参数组合测试ToolStripMenuItem->Size = System::Drawing::Size(216, 26);
			this->参数组合测试ToolStripMenuItem->Text = L"参数组合测试";
			// 
			// 帧速率
			// 
			this->帧速率->Name = L"帧速率";
			this->帧速率->Size = System::Drawing::Size(69, 20);
			this->帧速率->Text = L"帧速率：";
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
			// 视频分辨率
			// 
			this->视频分辨率->Margin = System::Windows::Forms::Padding(50, 3, 0, 2);
			this->视频分辨率->Name = L"视频分辨率";
			this->视频分辨率->Size = System::Drawing::Size(99, 20);
			this->视频分辨率->Text = L"视频分辨率：";
			// 
			// cols
			// 
			this->cols->Name = L"cols";
			this->cols->Size = System::Drawing::Size(45, 20);
			this->cols->Text = L"0000";
			// 
			// 乘
			// 
			this->乘->Name = L"乘";
			this->乘->Size = System::Drawing::Size(16, 20);
			this->乘->Text = L"*";
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
