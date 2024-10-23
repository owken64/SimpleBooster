// 自作VST用のインクルードファイル
#include "myvst3define.h"
#include "myvst3fuid.h"
#include "controller.h"


// VST3作成に必要な名前空間を使用
namespace Steinberg {
	namespace Vst {


		// クラスを初期化する関数(必須)
		tresult PLUGIN_API MyVSTController::initialize(FUnknown* context)
		{
			// まず継承元クラスの初期化を実施
			tresult result = EditController::initialize(context);
			if (result == kResultTrue)
			{
				// パラメーターを追加
				//parameters.addParameter(STR16("param1"), STR16("..."), 0, 1, ParameterInfo::kCanAutomate, PARAM1_TAG);
				// 範囲パラメーターを作成
				RangeParameter* param1 = new RangeParameter(STR16("Volume"), PARAM1_TAG, STR16(""), 0.0f, 2.0f, 1.0f);
				param1->setPrecision(2); // 小数第何位まで表示するか
				// 範囲パラメーターをコントローラーに追加
				parameters.addParameter(param1);

				// 文字列リストパラメーターを作成、追加
				StringListParameter* param2 = new StringListParameter(STR16("Type"), PARAM_TYPE_TAG);
				param2->appendString(STR16("Volume"));  // リスト項目を追加
				// 文字列リストパラメーターをコントローラーに追加
				parameters.addParameter(param2);

				// 以下固有の初期化を実施。

				// 今回は何もしない
			}

			// 初期化が成功すればkResultTrueを返す。
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
} // namespace SteinbergとVstの終わり
