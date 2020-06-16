#include "Decoder.h"

#include "cinder/app/App.h"
#include "cinder/Log.h"

namespace ffmpegcpp {

	using namespace ci;
	using namespace ci::app;
	using namespace std;

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

		App::get()->getSignalUpdate().connect( bind( &Decoder::update, this ) );
	}

	void Decoder::connectEventHandler( const function<void( int32_t, AVFrame*, StreamData* )>& eventHandler )
	{
		mEventHandler = eventHandler;
	}

	void Decoder::disconnectEventHandler()
	{
		mEventHandler = nullptr;
	}

	void Decoder::run()
	{
		while ( mRunning ) {
			if ( mEventHandler != nullptr ) {
				if ( !mNewFrameAudio && 
					mStreamFrameSinkAudio != nullptr && 
					mStreamFrameSinkAudio->checkNewFrame() ) {
					mNewFrameAudio = true;
				}
				if ( !mNewFrameVideo && 
					mStreamFrameSinkVideo != nullptr && 
					mStreamFrameSinkVideo->checkNewFrame() ) {
					mNewFrameVideo = true;
				}
			}
			if ( mDemuxer != nullptr ) {
				try {
					mDemuxer->Step();
				} catch ( FFmpegException ex ) {
					mRunning = false;
				}
			}
		}
	}

	void Decoder::start()
	{
	   	stop();
		if ( mThread == nullptr ) {
			mNewFrameAudio	= false;
			mNewFrameVideo	= false;
			mRunning		= true;
			mThread			= ThreadRef( new thread( bind( &Decoder::run, this ) ) );
		}
	}

	void Decoder::stop()
	{
		mRunning = false;
		if ( mThread != nullptr  ) {
			if ( mThread->joinable() ) {
				mThread->join();
			}
			mThread.reset();
			mThread = nullptr;
		}
	}

	void Decoder::update()
	{
		if ( mEventHandler != nullptr ) {
			if ( mNewFrameAudio && mStreamFrameSinkAudio != nullptr ) {
				mEventHandler( mStreamFrameSinkAudio->getFrame().streamIndex, 
							   mStreamFrameSinkAudio->getFrame().frame, 
							   mStreamFrameSinkAudio->getFrame().streamData );
				mNewFrameAudio = false;
			}
			if ( mNewFrameVideo && mStreamFrameSinkVideo != nullptr ) {
				mEventHandler( mStreamFrameSinkVideo->getFrame().streamIndex, 
					mStreamFrameSinkVideo->getFrame().frame, 
					mStreamFrameSinkVideo->getFrame().streamData );
				mNewFrameVideo = false;
			}
		}
	}

}