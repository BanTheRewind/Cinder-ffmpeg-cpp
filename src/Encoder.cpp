#include "Encoder.h"

namespace ffmpegcpp {

using namespace std;

Encoder::Options::Options( const Encoder::Options& rhs )
{
	*this = rhs;
}

Encoder::Options& Encoder::Options::operator=( const Encoder::Options& rhs )
{
	mAudioCodec		= rhs.mAudioCodec;
	mFilterConfig	= rhs.mFilterConfig;
	mOutputPath		= rhs.mOutputPath;
	mVideoCodec		= rhs.mVideoCodec;
	return *this;
}

Encoder::Options& Encoder::Options::audioCodec( AudioCodec t )
{
	setAudioCodec( t );
	return *this;
}

Encoder::Options& Encoder::Options::filterConfig( std::string& config )
{
	setFilterConfig( config );
	return *this;
}

Encoder::Options& Encoder::Options::outputPath( std::string& path )
{
	setOutputPath( path );
	return *this;
}

Encoder::Options& Encoder::Options::videoCodec( VideoCodec t )
{
	setVideoCodec( t );
	return *this;
}

EncoderRef Encoder::create( Encoder::Options& options ) {
	return EncoderRef( new Encoder( options ) );
}

Encoder::~Encoder()
{
	if ( mMuxer != nullptr ) {
		mMuxer->Close();
	}
}

Encoder::Encoder( Encoder::Options& options )
{
	mOptions = options;

	if ( !mOptions.getOutputPath().empty() ) {
		mMuxer = MuxerRef( new Muxer( mOptions.getOutputPath().c_str() ) );

		mAudioEncoder = AudioEncoderRef( new AudioEncoder( &mOptions.getAudioCodec(), mMuxer.get() ) );
		mVideoEncoder = VideoEncoderRef( new VideoEncoder( &mOptions.getVideoCodec(), mMuxer.get() ) );
		if ( mOptions.getFilterConfig().empty() ) {
			mFrameSink = FrameSinkRef( new Filter( mOptions.getFilterConfig().c_str(), mVideoEncoder.get() ) );
		} else {
			mFrameSink = mVideoEncoder;
		}
	}
}

void Encoder::preparePipeline()
{
	if ( mInputSourceAudio != nullptr ) {
		mInputSourceAudio->PreparePipeline();
	}
	if ( mInputSourceVideo != nullptr ) {
		mInputSourceVideo->PreparePipeline();
	}
}

void Encoder::step()
{
	if ( mInputSourceAudio != nullptr ) {
		mInputSourceAudio->Step();
	}
	if ( mInputSourceVideo != nullptr ) {
		mInputSourceVideo->Step();
	}
}

}