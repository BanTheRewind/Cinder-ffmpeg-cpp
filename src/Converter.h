#pragma once

#include "cinder/Surface.h"
#include "ffmpegcpp.h"
#include "libswscale/swscale.h"
#include <functional>
#include <memory>

namespace ffmpegcpp {
	using ConverterRef			= std::shared_ptr<class Converter>;
	
	class Converter
	{
	public:
		class Options
		{
		public:

			Options() {};
			Options( const Options& rhs );
			Options&		operator=( const Options& rhs );

			Options&		flags( int32_t v );
			Options&		height( int32_t v );
			Options&		pixelFormat( AVPixelFormat t );
			Options&		width( int32_t v );

			void			setFlags( int32_t v ) { mFlags = v; }
			void			setHeight( int32_t v ) { mHeight = v; }
			void			setPixelFormat( AVPixelFormat t ) { mPixelFormat = t; }
			void			setWidth( int32_t v ) { mWidth = v; }
			
			int32_t			getFlags() const { return mFlags; }
			int32_t			getHeight() const { return mHeight; }
			AVPixelFormat	getPixelFormat() const { return mPixelFormat; }
			int32_t			getWidth() const { return mWidth; }
		private:
			int32_t			mFlags			{ SWS_BICUBIC };
			int32_t			mHeight			{ 0 };
			AVPixelFormat	mPixelFormat	{ AVPixelFormat::AV_PIX_FMT_RGBA };
			int32_t			mWidth			{ 0 };
		};

		static ConverterRef create( Options& options = Options() );
		~Converter();

		AVFrame*			convert( AVFrame* frame );
	private:
		Converter( Options& options );

		Options				mOptions;

		uint8_t*			mBuffer	{ nullptr };
		AVFrame*			mFrame	{ nullptr };
		SwsContext*			mSwsContext { nullptr };

		int32_t				mHeight			{ -1 };
		AVPixelFormat		mPixelFormat	{ AVPixelFormat::AV_PIX_FMT_NONE };
		int32_t				mWidth			{ -1 };

	};
}
