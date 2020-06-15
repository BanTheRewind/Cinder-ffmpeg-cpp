#pragma once

#include "ffmpegcpp.h"
#include <memory>

namespace ffmpegcpp {
	using EncoderRef = std::shared_ptr<class Encoder>;

	class Encoder
	{
	public:
		class Options
		{
		public:
			Options() {};
			Options( const Options& rhs );
			Options&			operator=( const Options& rhs );

			Options&			audioChannels( int32_t v );
			Options&			audioCodec( AudioCodec t );
			Options&			audioSampleFormat( AVSampleFormat t );
			Options&			audioSampleRate( int32_t v );
			Options&			filterConfig( std::string& config );
			Options&			outputPath( std::string& path );
			Options&			outputVideoCodec( VideoCodec t );

			void				setAudioChannels( int32_t v ) { mAudioChannels = v; }
			void				setAudioCodec( AudioCodec t ) { mAudioCodec = t; }
			void				setAudioSampleFormat( AVSampleFormat t ) { mAudioSampleFormat = t; }
			void				setAudioSampleRate( int32_t v ) { mAudioSampleRate = v; }
			void				setFilterConfig( std::string& config ) { mFilterConfig = config; }
			void				setOutputPath( std::string& path ) { mOutputPath = path; }
			void				setVideoCodec( VideoCodec t ) { mVideoCodec = t; }

			int32_t				getAudioChannels() const { return mAudioChannels; }
			AudioCodec			getAudioCodec() const { return mAudioCodec; }
			AVSampleFormat		getAudioSampleFormat() const { return mAudioSampleFormat; }
			int32_t				getAudioSampleRate() const { return mAudioSampleRate; }
			const std::string&	getFilterConfig() const { return mFilterConfig; }
			const std::string&	getOutputPath() const { return mOutputPath; }
			VideoCodec			getVideoCodec() const { return mVideoCodec; }
		private:
			int32_t				mAudioChannels		{ 2 };
			AudioCodec			mAudioCodec			{ AudioCodec { AVCodecID::AV_CODEC_ID_AAC } };
			AVSampleFormat		mAudioSampleFormat	{ AVSampleFormat::AV_SAMPLE_FMT_S16 };
			int32_t				mAudioSampleRate	{ 44100 };
			std::string			mFilterConfig		{ "" };
			std::string			mOutputPath;
			VideoCodec			mVideoCodec			{ H264NVEncCodec {} };
		};

		static EncoderRef create( Options& options = Options() );
		~Encoder();
	private:
		Encoder( Options& options );

		Options			mOptions;

		InputSource*	mInputSourceAudio { nullptr };
		InputSource*	mInputSourceVideo { nullptr };
	};
}
