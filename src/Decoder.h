#pragma once

#include "ffmpegcpp.h"
#include <filesystem>
#include <memory>

namespace ffmpegcpp {
	using DecoderRef			= std::shared_ptr<class Decoder>;

	class Decoder
	{
	public:
		using DemuxerRef		= std::shared_ptr<Demuxer>;

		static DecoderRef		create( const std::string& path );
		~Decoder();
	private:
		class StreamFrameSink : public FrameSink, public FrameWriter
		{
		public:
			FrameSinkStream*	mStream { nullptr };
			AVMediaType			mMediaType;

			AVMediaType GetMediaType() { return mMediaType; }

			FrameSinkStream* CreateStream()
			{
				mStream = new FrameSinkStream( this, 0 );
				return mStream;
			}

			void WriteFrame(int streamIndex, AVFrame* frame, StreamData* streamData)
			{
				// TODO send buffer
			}

			void Close(int streamIndex)
			{
				delete mStream;
			}
		};

		using StreamFrameSinkRef	= std::shared_ptr<StreamFrameSink>;
		
		Decoder( const std::string& path );

		DemuxerRef				mDemuxerAudio	{ nullptr };
		DemuxerRef				mDemuxerVideo	{ nullptr };
		StreamFrameSinkRef		mFrameSinkAudio	{ nullptr };
		StreamFrameSinkRef		mFrameSinkVideo	{ nullptr };
		std::string				mPath			{ "" };
	};
}
