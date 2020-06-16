#include "Converter.h"

#include "cinder/Log.h"

namespace ffmpegcpp {

	using namespace ci;
	using namespace std;

	Converter::Options::Options( const Converter::Options& rhs )
	{
		*this = rhs;
	}

	Converter::Options& Converter::Options::operator=( const Converter::Options& rhs )
	{
		mFlags			= rhs.mFlags;
		mHeight			= rhs.mHeight;
		mPixelFormat	= rhs.mPixelFormat;
		mWidth			= rhs.mWidth;
		return *this;
	}

	Converter::Options& Converter::Options::flags( int32_t v )
	{
		setFlags( v );
		return *this;
	}

	Converter::Options& Converter::Options::height( int32_t v )
	{
		setHeight( v );
		return *this;
	}

	Converter::Options& Converter::Options::pixelFormat( AVPixelFormat t )
	{
		setPixelFormat( t );
		return *this;
	}

	Converter::Options& Converter::Options::width( int32_t v )
	{
		setWidth( v );
		return *this;
	}

	ConverterRef Converter::create( Converter::Options& options )
	{
		return ConverterRef( new Converter( options ) );
	}

	Converter::Converter( Converter::Options& options )
	{
		mOptions = options;

		int32_t numBytes = av_image_get_buffer_size( mOptions.getPixelFormat(), mOptions.getWidth(), mOptions.getHeight(), 1 );

		mFrame	= av_frame_alloc();
		mBuffer	= (uint8_t*)av_malloc( numBytes );
		memset( mBuffer, 0, numBytes );

		mFrame->format = mOptions.getPixelFormat();
		mFrame->height = mOptions.getHeight();
		mFrame->width = mOptions.getWidth();
		av_image_fill_arrays( mFrame->data, mFrame->linesize, mBuffer, mOptions.getPixelFormat(), mOptions.getWidth(), mOptions.getHeight(), 1 );
	}

	Converter::~Converter()
	{
		if ( mBuffer != nullptr ) {
			av_free( mBuffer );
		}
		if ( mFrame != nullptr ) {
			av_frame_free( &mFrame );
		}
		if ( mSwsContext != nullptr ) {
			sws_freeContext( mSwsContext );
		}
	}

	AVFrame* Converter::convert( AVFrame* frame ) 
	{
		if ( mSwsContext != nullptr && (
			mHeight != frame->height || 
			mPixelFormat != (AVPixelFormat)frame->format || 
			mWidth != frame->width ) ) {
			sws_freeContext( mSwsContext );
		}
		if ( mSwsContext == nullptr ) {
			mSwsContext = sws_getContext( frame->width, frame->height, (AVPixelFormat)frame->format, 
				mOptions.getWidth(), mOptions.getHeight(), mOptions.getPixelFormat(), 
				mOptions.getFlags(), nullptr, nullptr, nullptr );
		}

		const int32_t result = sws_scale( mSwsContext, frame->data, frame->linesize, 0, frame->height, mFrame->data, mFrame->linesize );
		CI_LOG_V( mFrame->width );

		mHeight			= frame->height;
		mPixelFormat	= (AVPixelFormat)frame->format;
		mWidth			= frame->width;

		return mFrame;
	}

}