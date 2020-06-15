#include "Decoder.h"

namespace ffmpegcpp {

using namespace std;

DecoderRef Decoder::create() {
	return DecoderRef( new Decoder() );
}

Decoder::~Decoder()
{
}

Decoder::Decoder()
{
}

}