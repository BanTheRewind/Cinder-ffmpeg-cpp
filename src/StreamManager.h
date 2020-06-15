#pragma once

#include "ffmpegcpp.h"
#include <filesystem>
#include <memory>

namespace ffmpegcpp {
	enum : int32_t
	{
		AudioCodec_None, 
		AudioCodec_AAC, 
		AudioCodec_MP2
	} typedef AudioCodec;

	enum : int32_t
	{
		AudioFormat_Unknown,
		AudioFormat_alaw,
		AudioFormat_f32be,
		AudioFormat_f32le,
		AudioFormat_f64be,
		AudioFormat_f64le,
		AudioFormat_mulaw,
		AudioFormat_s16be,
		AudioFormat_s16le,
		AudioFormat_s24be,
		AudioFormat_s24le,
		AudioFormat_s32be,
		AudioFormat_s32le,
		AudioFormat_s8,
		AudioFormat_u16be,
		AudioFormat_u16le,
		AudioFormat_u24be,
		AudioFormat_u24le,
		AudioFormat_u32be,
		AudioFormat_u32le,
		AudioFormat_u8
	} typedef AudioFormat;

	enum : int32_t
	{
		VideoCodec_None, 
		VideoCodec_H264, 
		VideoCodec_H265, 
		VideoCodec_VP9
	} typedef VideoCodec;

	using StreamManagerRef = std::shared_ptr<class StreamManager>;

	class StreamManager
	{
	public:
		class Options
		{
		public:
			Options() {};
			Options( const Options& rhs );
			Options&						operator=( const Options& rhs );

			Options&						audioChannels( int32_t v );
			Options&						audioFormat( AudioFormat t );
			Options&						audioSampleRate( int32_t v );
			Options&						filterConfig( std::string& config );
			Options&						outputAudioCodec( AudioCodec t );
			Options&						outputPath( std::filesystem::path& path );
			Options&						outputVideoCodec( VideoCodec t );

			void							setAudioChannels( int32_t v ) { mAudioChannels = v; }
			void							setAudioFormat( AudioFormat t ) { mAudioFormat = t; }
			void							setAudioSampleRate( int32_t v ) { mAudioSampleRate = v; }
			void							setFilterConfig( std::string& config ) { mFilterConfig = config; }
			void							setOutputAudioCodec( AudioCodec t ) { mOutputAudioCodec = t; }
			void							setOutputPath( std::filesystem::path& path ) { mOutputPath = path; }
			void							setOutputVideoCodec( VideoCodec t ) { mOutputVideoCodec = t; }

			int32_t							getAudioChannels() const { return mAudioChannels; }
			AudioFormat						getAudioFormat() const { return mAudioFormat; }
			int32_t							getAudioSampleRate() const { return mAudioSampleRate; }
			const std::string&				getFilterConfig() const { return mFilterConfig; }
			AudioCodec						getOutputAudioCodec() const { return mOutputAudioCodec; }
			const std::filesystem::path&	getOutputPath() const { return mOutputPath; }
			VideoCodec						getOutputVideoCodec() const { return mOutputVideoCodec; }
		private:
			int32_t							mAudioChannels		= 2;
			AudioFormat						mAudioFormat		= AudioFormat_s16le;
			int32_t							mAudioSampleRate	= 44100;
			std::string						mFilterConfig		= "";
			AudioCodec						mOutputAudioCodec	= AudioCodec_AAC;
			std::filesystem::path			mOutputPath;
			VideoCodec						mOutputVideoCodec	= VideoCodec_H264;
		};

		static StreamManagerRef create( Options& options = Options() );
		~StreamManager();
	private:
		StreamManager( Options& options );

		Options		mOptions;

		InputSource* mInputSourceAudio = nullptr;
		InputSource* mInputSourceVideo = nullptr;
	};
}
