#pragma once
// VST3 SDK�̃C���N���[�h�t�@�C��
#include "pluginterfaces\base\funknown.h"

// VST3�쐬�ɕK�v�Ȃ̖��O��Ԃ��g�p
namespace Steinberg {
	namespace Vst {

		// FUID�̐���
		static const FUID ProcessorUID( 0xB4B4505D, 0xF1E04033, 0x95C5BB1A, 0x39E73E5D );
		static const FUID ControllerUID(0x2522CB6A, 0x2A1143C6, 0xAC920FB0, 0x36F94DF7);
	}
} // namespace Steinberg��Vst�̏I���
