#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

class VideoPlayerApp : public ci::app::App 
{
public:
	VideoPlayerApp();
private:
	void draw() override;
	void update() override;	
};

using namespace ci;
using namespace ci::app;
using namespace std;

VideoPlayerApp::VideoPlayerApp()
{
}

void VideoPlayerApp::draw()
{
	gl::clear(); 
}

void VideoPlayerApp::update()
{
}

CINDER_APP( VideoPlayerApp, RendererGl )
