#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

#include "Converter.h"
#include "Decoder.h"

class VideoPlayerApp : public ci::app::App 
{
public:
	VideoPlayerApp();
private:
	void 					draw() override;
	void					update() override;
	
	ffmpegcpp::ConverterRef	mConverter	{ nullptr };
	ffmpegcpp::DecoderRef	mDecoder	{ nullptr };

	ci::gl::Texture2dRef	mTexture { nullptr };
};

using namespace ci;
using namespace ci::app;
using namespace ffmpegcpp;
using namespace std;

VideoPlayerApp::VideoPlayerApp()
{
	mConverter = Converter::create( Converter::Options()
		.height( getWindowHeight() )
		.width( getWindowWidth() ) );
	mDecoder = Decoder::create( "https://holobooth.net/media/e111.mp4" );
	mDecoder->connectEventHandler( [ & ]( int32_t streamIndex, AVFrame* frame, StreamData* streamData ) {
		if ( streamData->type == AVMediaType::AVMEDIA_TYPE_VIDEO ) {
			AVFrame* rgbFrame = mConverter->convert( frame );
			Surface8uRef surf = toSurface( rgbFrame );
			mTexture = gl::Texture2d::create( *surf );
		}
	} );
}

void VideoPlayerApp::draw()
{
	gl::clear();
	if ( mTexture != nullptr ) {
		gl::draw( mTexture, mTexture->getBounds(), getWindowBounds() );
	}
}

void VideoPlayerApp::update()
{
	if ( mDecoder != nullptr ) {
		mDecoder->step();
	}
}

CINDER_APP( VideoPlayerApp, RendererGl, []( App::Settings* settings )
{
	settings->setWindowSize( 1080 / 2, 1920 / 2 );
} )
