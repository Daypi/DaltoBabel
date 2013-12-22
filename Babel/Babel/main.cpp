#include	"AudioManager.hh"
#include	<iostream>

int	main(void)
{
/*  PortAudioIO	audiomanager;

  if (!audiomanager.init())
	  std::cerr << "error initializing " << std::endl;
  audiomanager.startRecording();
  audiomanager.cleanup();
  */
	AudioManager	mgr;
	std::cout << "LOOP" << std::endl; 
	mgr.mainLoop();
}
