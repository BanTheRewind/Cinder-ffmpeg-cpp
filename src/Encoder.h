#pragma once

#include "ffmpegcpp.h"
#include <memory>

namespace ffmpegcpp {
	using EncoderRef			= std::shared_ptr<class Encoder>;
	
	class Encoder
	{
	public:
		using FrameSinkRef		= std::shared_ptr<FrameSink>;
		using InputSourceRef	= std::shared_ptr<InputSource>;
		using MuxerRef			= std::shared_ptr<Muxer>;
		
		class Options
		{
		public:

			Options() {};
			Options( const Options& rhs );
			Options&			operator=( const Options& rhs );

			Options&			audioCodec( AudioCodec t );
			Options&			filterConfig( std::string& config );
			Options&			outputPath( std::string& path );
			Options&			videoCodec( VideoCodec t );
			
			void				setAudioCodec( AudioCodec t ) { mAudioCodec = t; }
			void				setFilterConfig( std::string& config ) { mFilterConfig = config; }
			void				setOutputPath( std::string& path ) { mOutputPath = path; }
			void				setVideoCodec( VideoCodec t ) { mVideoCodec = t; }
			
			AudioCodec			getAudioCodec() const { return mAudioCodec; }
			const std::string&	getFilterConfig() const { return mFilterConfig; }
			const std::string&	getOutputPath() const { return mOutputPath; }
			VideoCodec			getVideoCodec() const { return mVideoCodec; }
		private:
			AudioCodec			mAudioCodec			{ AudioCodec { AVCodecID::AV_CODEC_ID_AAC } };
			std::string			mFilterConfig		{ "" };
			std::string			mOutputPath;
			VideoCodec			mVideoCodec			{ H264NVEncCodec {} };
		};

		static EncoderRef		create( Options& options = Options {} );

		~Encoder();

		FrameSinkRef			getFrameSink() const { return mFrameSink; }
		const Options&			getOptions() const { return mOptions; }

		void					setAudioInputSource( InputSource* source ) { mInputSourceAudio = InputSourceRef { source }; }
		void					setVideoInputSource( InputSource* source ) { mInputSourceVideo = InputSourceRef { source }; }

		void					preparePipeline();
		void					step();
	private:
		using AudioEncoderRef	= std::shared_ptr<AudioEncoder>;
		using VideoEncoderRef	= std::shared_ptr<VideoEncoder>;

		Encoder( Options& options );

		AudioEncoderRef			mAudioEncoder		{ nullptr };
		FrameSinkRef			mFrameSink			{ nullptr };
		InputSourceRef			mInputSourceAudio	{ nullptr };
		InputSourceRef			mInputSourceVideo	{ nullptr };
		MuxerRef				mMuxer				{ nullptr };
		Options					mOptions;
		VideoEncoderRef			mVideoEncoder		{ nullptr };
	};
}
