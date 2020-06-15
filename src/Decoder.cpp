#include "Decoder.h"

namespace ffmpegcpp {

using namespace std;

DecoderRef Decoder::create( const string& path ) {
	return DecoderRef( new Decoder { path } );
}

Decoder::~Decoder()
{
}

Decoder::Decoder( const string& path )
{
	mPath = path;
}

}