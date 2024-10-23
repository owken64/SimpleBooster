#pragma once
// VST3 SDKのインクルードファイル
#include "pluginterfaces\base\funknown.h"

// VST3作成に必要なの名前空間を使用
namespace Steinberg {
	namespace Vst {

		// FUIDの生成
		static const FUID ProcessorUID( 0xB4B4505D, 0xF1E04033, 0x95C5BB1A, 0x39E73E5D );
		static const FUID ControllerUID(0x2522CB6A, 0x2A1143C6, 0xAC920FB0, 0x36F94DF7);
	}
} // namespace SteinbergとVstの終わり
