#pragma once
// VST3 SDK�̃C���N���[�h�t�@�C��
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

// VST3�쐬�ɕK�v�Ȃ̖��O��Ԃ��g�p
namespace Steinberg {
	namespace Vst {

		// ===================================================================================
		// �����M������������Processor�N���X
		// ===================================================================================
		class MyVSTProcessor : public AudioEffect
		{
		protected:
			ParamValue volume;
			int32 type;
		public:
			//�R���X�g���N�^
			MyVSTProcessor();

			// �N���X������������֐�(�K�{)
			tresult PLUGIN_API initialize(FUnknown* context);

			// �o�X�\����ݒ肷��֐��B
			tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts);

			// �����M������������֐�(�K�{)
			tresult PLUGIN_API process(ProcessData& data);

			// ����VST Processor�N���X�̃C���X�^���X���쐬���邽�߂̊֐�(�K�{)
			static FUnknown* createInstance(void*) { return (IAudioProcessor*)new MyVSTProcessor(); }
		};


	}

} // namespace Steinberg��Vst�̏I���