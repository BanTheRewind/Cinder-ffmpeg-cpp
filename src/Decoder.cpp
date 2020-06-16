#include "Decoder.h"

#include "cinder/Log.h"

namespace ffmpegcpp {

	using namespace ci;
	using namespace std;

	Channel8uRef toChannel( AVFrame* frame ) {
		return Channel8u::create( frame->width, frame->height, (uint32_t)frame->linesize[ 0 ], 1, frame->data[ 0 ] );
	}

	Surface8uRef toSurface( AVFrame* frame ) {
		return Surface8u::create( frame->data[ 0 ], frame->width, frame->height, frame->linesize[ 0 ], SurfaceChannelOrder::RGBA );
	}

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

	FrameSinkStream* StreamFrameSink::CreateStream()
	{
		if ( mStream == nullptr ) {
			mStream = new FrameSinkStream( this, 0 );
		}
		return mStream;
	}

	void StreamFrameSink::WriteFrame( int32_t streamIndex, AVFrame* frame, StreamData* streamData )
	{
		if ( mEventHandler != nullptr ) {
			mEventHandler( streamIndex, frame, streamData );
		}
	}

	void StreamFrameSink::Close( int32_t streamIndex )
	{
		if ( mStream != nullptr ) {
			delete mStream;
			mStream = nullptr;
		}
	}

	DecoderRef Decoder::create( const string& path )
	{
		return DecoderRef( new Decoder { path } );
	}

	Decoder::~Decoder()
	{
		disconnectEventHandler();
	}

	Decoder::Decoder( const string& path )
	{
		mPath = path;

		mDemuxer = DemuxerRef( new Demuxer( path.c_str() ) );

		mStreamFrameSinkAudio = StreamFrameSink::create( AVMediaType::AVMEDIA_TYPE_AUDIO );
		mStreamFrameSinkVideo = StreamFrameSink::create( AVMediaType::AVMEDIA_TYPE_VIDEO );

		mDemuxer->DecodeBestAudioStream( mStreamFrameSinkAudio.get() );
		mDemuxer->DecodeBestVideoStream( mStreamFrameSinkVideo.get() );
		mDemuxer->PreparePipeline();

	}

	void Decoder::connectEventHandler( const function<void( int32_t, AVFrame*, StreamData* )>& eventHandler )
	{
		if ( mStreamFrameSinkAudio != nullptr ) {
			mStreamFrameSinkAudio->mEventHandler = eventHandler;
		}
		if ( mStreamFrameSinkVideo != nullptr ) {
			mStreamFrameSinkVideo->mEventHandler = eventHandler;
		}
	}

	void Decoder::disconnectEventHandler()
	{
		if ( mStreamFrameSinkAudio != nullptr ) {
			mStreamFrameSinkAudio->mEventHandler = nullptr;
		}
		if ( mStreamFrameSinkVideo != nullptr ) {
			mStreamFrameSinkVideo->mEventHandler = nullptr;
		}
	}

	void Decoder::step()
	{
		if ( mDemuxer != nullptr && !mDemuxer->IsDone() ) {
			try {
				mDemuxer->Step();
				++mSteps;
			} catch ( FFmpegException ex ) {
				mSteps = 0;
			}
		} else {
			mSteps = 0;
		}
	}

}