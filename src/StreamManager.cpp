#include "StreamManager.h"

namespace ffmpegcpp {

using namespace std;

StreamManager::Options::Options( const StreamManager::Options& rhs )
{
	*this = rhs;
}

StreamManager::Options& StreamManager::Options::operator=( const StreamManager::Options& rhs )
{
	mAudioChannels		= rhs.mAudioChannels;
	mAudioFormat		= rhs.mAudioFormat;
	mAudioSampleRate	= rhs.mAudioSampleRate;
	mFilterConfig		= rhs.mFilterConfig;
	mOutputAudioCodec	= rhs.mOutputAudioCodec;
	mOutputPath			= rhs.mOutputPath;
	mOutputVideoCodec	= rhs.mOutputVideoCodec;
	return *this;
}


StreamManager::Options& StreamManager::Options::audioChannels( int32_t v )
{
	setAudioChannels( v );
	return *this;
}

StreamManager::Options& StreamManager::Options::audioFormat( AudioFormat t )
{
	setAudioFormat( t );
	return *this;
}

StreamManager::Options& StreamManager::Options::audioSampleRate( int32_t v )
{
	setAudioSampleRate( v );
	return *this;
}

StreamManager::Options& StreamManager::Options::filterConfig( std::string& config )
{
	setFilterConfig( config );
	return *this;
}

StreamManager::Options& StreamManager::Options::outputAudioCodec( AudioCodec t )
{
	setOutputAudioCodec( t );
	return *this;
}

StreamManager::Options& StreamManager::Options::outputPath( std::filesystem::path& path )
{
	setOutputPath( path );
	return *this;
}

StreamManager::Options& StreamManager::Options::outputVideoCodec( VideoCodec t )
{
	setOutputVideoCodec( t );
	return *this;
}

StreamManagerRef StreamManager::create( StreamManager::Options& options ) {
	return StreamManagerRef( new StreamManager( options ) );
}

StreamManager::~StreamManager()
{
}

StreamManager::StreamManager( StreamManager::Options& options )
{
	mOptions = options;
}

}