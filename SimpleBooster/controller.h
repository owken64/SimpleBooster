#pragma once
// VST3 SDK�̃C���N���[�h�t�@�C��
#include "public.sdk/source/vst/vsteditcontroller.h"

// VST3�G�f�B�^�[�̃C���N���[�h�t�@�C��
#include "vstgui\plugin-bindings/vst3editor.h"

// ����VST�p�̃C���N���[�h�t�@�C��
#include "myvst3define.h"


// VST3�쐬�ɕK�v�Ȗ��O��Ԃ��g�p
namespace Steinberg {
	namespace Vst {


		// ===================================================================================
		// VST�̃p�����[�^�[�𑀍삷�邽�߂�Controller�N���X
		// ===================================================================================
		class MyVSTController : public EditController
		{
		public:
			// �N���X������������֐�(�K�{)
			tresult PLUGIN_API initialize(FUnknown* context);

			// ����VST GUIEditor���쐬����֐�
			IPlugView* PLUGIN_API createView(const char* name);

			// ����VST Controller�N���X�̃C���X�^���X���쐬���邽�߂̊֐�(�K�{)
			static FUnknown* createInstance(void*) { return (IEditController*)new MyVSTController(); }

		};


	}
} // namespace Steinberg��Vst�̏I���
