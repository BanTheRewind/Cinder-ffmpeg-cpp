#pragma once

#include "cinder/Surface.h"
#include "ffmpegcpp.h"
#include <functional>
#include <memory>

namespace ffmpegcpp {
	ci::Channel8uRef		toChannel( AVFrame* frame );
	ci::Surface8uRef		toSurface( AVFrame* frame );

	using DecoderRef			= std::shared_ptr<class Decoder>;
	using StreamFrameSinkRef	= std::shared_ptr<class StreamFrameSink>;
	using FrameEventHandler		= std::function<void ( int32_t, AVFrame*, StreamData* )>;

	class StreamFrameSink : public FrameSink, public FrameWriter
	{
	public:
		static StreamFrameSinkRef	create( AVMediaType mediaType );
		~StreamFrameSink();

		void				Close( int32_t streamIndex );
		FrameSinkStream*	CreateStream();
		AVMediaType			GetMediaType() { return mMediaType; }
		bool				IsPrimed() { return true; }
		void				WriteFrame( int32_t streamIndex, AVFrame* frame, StreamData* streamData );
	private:
		StreamFrameSink( AVMediaType mediaType );

		FrameSinkStream*	mStream { nullptr };
		AVMediaType			mMediaType;
	protected:
		FrameEventHandler	mEventHandler { nullptr };

		friend class		Decoder;
	};

	class Decoder
	{
	public:
		using DemuxerRef = std::shared_ptr<Demuxer>;

		static DecoderRef create( const std::string& path );
		~Decoder();

		void				step();

		template<typename T, typename Y> 
		inline void			connectEventHandler( T eventHandler, Y *obj )
		{
			connectEventHandler( std::bind( eventHandler, obj, std::placeholders::_1 ) );
		}
		void				connectEventHandler( const std::function<void( int32_t, AVFrame*, StreamData* )>& eventHandler );
		void				disconnectEventHandler();
	private:
		Decoder( const std::string& path );

		DemuxerRef			mDemuxer				{ nullptr };
		StreamFrameSinkRef	mStreamFrameSinkAudio	{ nullptr };
		StreamFrameSinkRef	mStreamFrameSinkVideo	{ nullptr };
		std::string			mPath					{ "" };
		bool				mRunning				{ false };
	};
}
