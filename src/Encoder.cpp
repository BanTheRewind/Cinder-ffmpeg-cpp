#include "Encoder.h"

namespace ffmpegcpp {

using namespace std;

Encoder::Options::Options( const Encoder::Options& rhs )
{
	*this = rhs;
}

Encoder::Options& Encoder::Options::operator=( const Encoder::Options& rhs )
{
	mAudioChannels		= rhs.mAudioChannels;
	mAudioCodec			= rhs.mAudioCodec;
	mAudioSampleFormat	= rhs.mAudioSampleFormat;
	mAudioSampleRate	= rhs.mAudioSampleRate;
	mFilterConfig		= rhs.mFilterConfig;
	mOutputPath			= rhs.mOutputPath;
	mVideoCodec			= rhs.mVideoCodec;
	return *this;
}


Encoder::Options& Encoder::Options::audioChannels( int32_t v )
{
	setAudioChannels( v );
	return *this;
}

Encoder::Options& Encoder::Options::audioCodec( AudioCodec t )
{
	setAudioCodec( t );
	return *this;
}

Encoder::Options& Encoder::Options::audioSampleFormat( AVSampleFormat t )
{
	setAudioSampleFormat( t );
	return *this;
}

Encoder::Options& Encoder::Options::audioSampleRate( int32_t v )
{
	setAudioSampleRate( v );
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

Encoder::Options& Encoder::Options::outputVideoCodec( VideoCodec t )
{
	setVideoCodec( t );
	return *this;
}

EncoderRef Encoder::create( Encoder::Options& options ) {
	return EncoderRef( new Encoder( options ) );
}

Encoder::~Encoder()
{
}

Encoder::Encoder( Encoder::Options& options )
{
	mOptions = options;
}

}