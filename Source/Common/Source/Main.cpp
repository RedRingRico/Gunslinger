#include <iostream>
#include <Game.hpp>
#include <GitVersion.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	std::cout << "Gunslinger" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "Build Information" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "\tVersion: " << GIT_BUILD_VERSION << std::endl;
	std::cout << "\tTag:     " << GIT_TAG_NAME << std::endl;
	std::cout << "\tBranch:  " << GIT_BRANCH << std::endl;
	std::cout << "\tDate:    " << GIT_COMMITTERDATE << std::endl;
	std::cout << "\tHash:    " << GIT_COMMITHASH << std::endl;

	Gunslinger::Game TheGame;

	if( TheGame.Initialise( ) != ZED_OK )
	{
		std::cout << "[Gunslinger::main] <ERROR> Failed to initialise the "
			"game" << std::endl;

		return ZED_FAIL;
	}

	return TheGame.Execute( );
}

