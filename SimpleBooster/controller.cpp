// ����VST�p�̃C���N���[�h�t�@�C��
#include "myvst3define.h"
#include "myvst3fuid.h"
#include "controller.h"


// VST3�쐬�ɕK�v�Ȗ��O��Ԃ��g�p
namespace Steinberg {
	namespace Vst {


		// �N���X������������֐�(�K�{)
		tresult PLUGIN_API MyVSTController::initialize(FUnknown* context)
		{
			// �܂��p�����N���X�̏����������{
			tresult result = EditController::initialize(context);
			if (result == kResultTrue)
			{
				// �p�����[�^�[��ǉ�
				//parameters.addParameter(STR16("param1"), STR16("..."), 0, 1, ParameterInfo::kCanAutomate, PARAM1_TAG);
				// �͈̓p�����[�^�[���쐬
				RangeParameter* param1 = new RangeParameter(STR16("Volume"), PARAM1_TAG, STR16(""), 0.0f, 2.0f, 1.0f);
				param1->setPrecision(2); // �����扽�ʂ܂ŕ\�����邩
				// �͈̓p�����[�^�[���R���g���[���[�ɒǉ�
				parameters.addParameter(param1);

				// �����񃊃X�g�p�����[�^�[���쐬�A�ǉ�
				StringListParameter* param2 = new StringListParameter(STR16("Type"), PARAM_TYPE_TAG);
				param2->appendString(STR16("Volume"));  // ���X�g���ڂ�ǉ�
				// �����񃊃X�g�p�����[�^�[���R���g���[���[�ɒǉ�
				parameters.addParameter(param2);

				// �ȉ��ŗL�̏����������{�B

				// ����͉������Ȃ�
			}

			// �����������������kResultTrue��Ԃ��B
			result = kResultTrue;
			return result;
		}

		IPlugView* PLUGIN_API MyVSTController::createView(FIDString name)
		{
			if (strcmp(name, ViewType::kEditor) == 0)
			{
				return new VSTGUI::VST3Editor(this, "view", "myEditor.uidesc");
			}
			return 0;
		}
	}
} // namespace Steinberg��Vst�̏I���
