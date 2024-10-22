// ����VST�p�̃C���N���[�h�t�@�C��
#include "myvst3fuid.h"
#include "processor.h"


// VST3�쐬�ɕK�v�Ȃ̖��O��Ԃ��g�p
namespace Steinberg {
	namespace Vst {


		// ===================================================================================
		// �N���X������������֐�
		// ===================================================================================
		tresult PLUGIN_API MyVSTProcessor::initialize(FUnknown* context)
		{
			// �܂��p�����N���X�̏����������{
			tresult result = AudioEffect::initialize(context);
			if (result == kResultTrue)
			{
				// ���͂Əo�͂�ݒ�
				addAudioInput(STR16("AudioInput"), SpeakerArr::kStereo);
				addAudioOutput(STR16("AudioOutput"), SpeakerArr::kStereo);

				// �ȉ��ŗL�̏����������{�B

				// ����͉������Ȃ�
			}


			// �����������������kResultTrue��Ԃ��B
			return result;
		}

		tresult PLUGIN_API MyVSTProcessor::setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts)
		{
			// input��output�̃o�X��1���ŁA����input��output�̍\�����X�e���I�̏ꍇ
			if (numIns == 1 && numOuts == 1 && inputs[0] == SpeakerArr::kStereo && outputs[0] == SpeakerArr::kStereo)
			{
				return AudioEffect::setBusArrangements(inputs, numIns, outputs, numOuts);
			}

			// �Ή����Ă��Ȃ��o�X�\���̏ꍇ�AkResultFalse��Ԃ��B
			return kResultFalse;
		}

		// ===================================================================================
		// �����M������������֐�
		// ===================================================================================
		tresult PLUGIN_API MyVSTProcessor::process(ProcessData& data)
		{
			// ���́E�o�̓o�b�t�@�̃|�C���^���킩��₷���ϐ��Ɋi�[
			// inputs[]�Aoutputs[]��AudioBus�̐���������(addAudioInput()�AaddAudioOutput()�Œǉ�����������)
			// �����AudioBus��1�����Ȃ̂� 0 �݂̂ƂȂ�
			// channelBuffers32��32bit���������_�^�̃o�b�t�@�ŉ����M���̃`�����l����������
			// ���m����(kMono)�Ȃ� 0 �݂̂ŁA�X�e���I(kStereo)�Ȃ� 0(Left) �� 1(Right) �ƂȂ�
			Sample32* inL = data.inputs[0].channelBuffers32[0];
			Sample32* inR = data.inputs[0].channelBuffers32[1];
			Sample32* outL = data.outputs[0].channelBuffers32[0];
			Sample32* outR = data.outputs[0].channelBuffers32[1];

			// numSamples�Ŏ������T���v�����A��������������
			for (int32 i = 0; i < data.numSamples; i++)
			{
				outL[i] = inL[i];
				outR[i] = inR[i];
			}

			// ���Ȃ����kResultTrue��Ԃ�(�����炭�K��kResultTrue��Ԃ�)
			return kResultTrue;
		}

	}
} // namespace Steinberg��Vst�̏I���
