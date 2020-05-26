#include "MyForm.h"

using namespace CLR3rd;

[STAThreadAttribute]

int main(cli::array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MyForm());

	return 0;
}