#pragma once

#include "ffmpegcpp.h"
#include "StreamFrameSink.h"
#include <functional>
#include <memory>
#include <thread>

namespace ffmpegcpp {
	using DecoderRef = std::shared_ptr<class Decoder>;

	class Decoder
	{
	public:
		using DemuxerRef = std::shared_ptr<Demuxer>;

		static DecoderRef create( const std::string& path );
		~Decoder();

		void				start();
		void				stop();

		template<typename T, typename Y> 
		inline void			connectEventHandler( T eventHandler, Y *obj )
		{
			connectEventHandler( std::bind( eventHandler, obj, std::placeholders::_1 ) );
		}
		void				connectEventHandler( const std::function<void( int32_t, AVFrame*, StreamData* )>& eventHandler );
		void				disconnectEventHandler();
	private:
		using ThreadRef = std::shared_ptr<std::thread>;

		Decoder( const std::string& path );

		std::function<void ( int32_t, AVFrame*, StreamData* )>	mEventHandler;

		void				run();
		virtual void		update();
	
		std::atomic_bool	mNewFrameAudio	{ false };
		std::atomic_bool	mNewFrameVideo	{ false };
		std::atomic_bool	mRunning		{ false };
		ThreadRef			mThread			{ nullptr };

		DemuxerRef			mDemuxer				{ nullptr };
		StreamFrameSinkRef	mStreamFrameSinkAudio	{ nullptr };
		StreamFrameSinkRef	mStreamFrameSinkVideo	{ nullptr };
		std::string			mPath					{ "" };
	};
}
