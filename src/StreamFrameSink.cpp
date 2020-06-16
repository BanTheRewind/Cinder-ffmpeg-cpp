#include "StreamFrameSink.h"

namespace ffmpegcpp {
	StreamFrameSinkRef StreamFrameSink::create( AVMediaType mediaType )
	{
		return StreamFrameSinkRef( new StreamFrameSink( mediaType ) );
	}

	StreamFrameSink::StreamFrameSink( AVMediaType mediaType )
	{
		mMediaType = mediaType;
	}

	StreamFrameSink::~StreamFrameSink()
	{
		Close( 0 );
	}

	bool StreamFrameSink::checkNewFrame() 
	{
		bool newFrame { mNewFrame };
		mNewFrame = false;
		return newFrame; 
	}

	FrameSinkStream* StreamFrameSink::CreateStream()
	{
		if ( mStream == nullptr ) {
			mStream = new FrameSinkStream( this, 0 );
		}
		return mStream;
	}

	void StreamFrameSink::WriteFrame( int32_t streamIndex, AVFrame* frame, StreamData* streamData )
	{
		if ( !mNewFrame ) {
			mFrame.frame		= frame;
			mFrame.streamData	= streamData;
			mFrame.streamIndex	= streamIndex;
			mNewFrame			= true;
		}
	}

	void StreamFrameSink::Close( int32_t streamIndex )
	{
		if ( mStream != nullptr ) {
			delete mStream;
			mStream = nullptr;
		}
	}
}
 