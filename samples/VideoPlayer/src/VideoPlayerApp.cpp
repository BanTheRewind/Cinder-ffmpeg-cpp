#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

#include "Decoder.h"

class VideoPlayerApp : public ci::app::App 
{
public:
	VideoPlayerApp();
private:
	void draw() override;
	void update() override;

	ffmpegcpp::DecoderRef	mDecoder { nullptr };
};

using namespace ci;
using namespace ci::app;
using namespace ffmpegcpp;
using namespace std;

VideoPlayerApp::VideoPlayerApp()
{
	static int32_t frameIndex = 0;
	mDecoder = Decoder::create( "https://holobooth.net/media/e111.mp4" );
	//mDecoder = Decoder::create( "D:\\Developer\\cinder_master\\blocks\\Cinder-ffmpeg-cpp\\ffmpeg-cpp\\samples\\big_buck_bunny.mp4" );
	mDecoder->connectEventHandler( [ & ]( int32_t streamIndex, AVFrame* frame, StreamData* streamData ) {
		CI_LOG_V( frameIndex );
		frameIndex++;
	} );
	mDecoder->start();
}

void VideoPlayerApp::draw()
{
	gl::clear(); 
}

void VideoPlayerApp::update()
{
}

CINDER_APP( VideoPlayerApp, RendererGl )
