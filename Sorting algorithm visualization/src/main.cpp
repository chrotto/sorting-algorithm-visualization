#include <iostream>
#include "Application.h"
using namespace std;

int main()
{
	try
	{
		Application app;
		app.run();
	}
	catch (exception& e)
	{
		cerr << "\nEXCEPTION: " << e.what() << endl;
	}

	return 0;
}