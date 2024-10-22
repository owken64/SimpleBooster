#pragma once
// VST3 SDKのインクルードファイル
#include "pluginterfaces\base\funknown.h"

// VST3作成に必要なの名前空間を使用
namespace Steinberg {
	namespace Vst {

		// FUIDの生成
		static const FUID ProcessorUID( 0xB4B4505D, 0xF1E04033, 0x95C5BB1A, 0x39E73E5D );

	}
} // namespace SteinbergとVstの終わり
