// 自作VST用のインクルードファイル
#include "myvst3fuid.h"
#include "processor.h"
#include "myvst3define.h"

// VST3作成に必要なの名前空間を使用
namespace Steinberg {
	namespace Vst {


		// =================================================================================
        // コンストラクタ
        // =================================================================================
		MyVSTProcessor::MyVSTProcessor()
		{
			// コントローラーのFUIDを設定する
			setControllerClass(ControllerUID);
		}

		// ===================================================================================
		// クラスを初期化する関数
		// ===================================================================================
		tresult PLUGIN_API MyVSTProcessor::initialize(FUnknown* context)
		{
			// まず継承元クラスの初期化を実施
			tresult result = AudioEffect::initialize(context);
			if (result == kResultTrue)
			{
				// 入力と出力を設定
				addAudioInput(STR16("AudioInput"), SpeakerArr::kStereo);
				addAudioOutput(STR16("AudioOutput"), SpeakerArr::kStereo);

				// 以下固有の初期化を実施。

				// 今回は何もしない
			}


			// 初期化が成功すればkResultTrueを返す。
			return result;
		}

		tresult PLUGIN_API MyVSTProcessor::setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts)
		{
			// inputとoutputのバスが1つずつで、かつinputとoutputの構成がステレオの場合
			if (numIns == 1 && numOuts == 1 && inputs[0] == SpeakerArr::kStereo && outputs[0] == SpeakerArr::kStereo)
			{
				return AudioEffect::setBusArrangements(inputs, numIns, outputs, numOuts);
			}

			// 対応していないバス構成の場合、kResultFalseを返す。
			return kResultFalse;
		}

		// ===================================================================================
		// 音声信号を処理する関数
		// ===================================================================================
		tresult PLUGIN_API MyVSTProcessor::process(ProcessData& data)
		{
			// パラメーター変更の処理
// 与えられたパラメーターがあるとき、dataのinputParameterChangesに
// IParameterChangesクラスへのポインタのアドレスが入る
			if (data.inputParameterChanges != NULL)
			{
				// 与えられたパラメーターの数を取得
				int32 paramChangeCount = data.inputParameterChanges->getParameterCount();

				// 与えられたパラメーター分、処理を繰り返す。
				for (int32 i = 0; i < paramChangeCount; i++)
				{
					// パラメーター変更のキューを取得
					// (処理するサンプル内に複数のパラメーター変更情報がある可能性があるため、
					// キューという形になっている。)
					IParamValueQueue* queue = data.inputParameterChanges->getParameterData(i);
					if (queue != NULL)
					{
						// どのパラメーターが変更されたか知るため、パラメーターtagを取得
						int32 tag = queue->getParameterId();

						// 変更された回数を取得
						int32 valueChangeCount = queue->getPointCount();
						ParamValue value;
						int32 sampleOffset;

						// 最後に変更された値を取得
						if (queue->getPoint(valueChangeCount - 1, sampleOffset, value) == kResultTrue)
						{
							// tagに応じた処理を実施
							switch (tag)
							{
							case PARAM1_TAG:
								// volumeはメンバー変数としてあらかじめ定義・初期化しておく。
								volume = value * 2.0f;
								break;

							case PARAM_TYPE_TAG:
								// typeを変更する。
								// StringListParameterで作成されたパラメーターも、プロセッサクラスに
								// 渡されるときは0.0〜1.0となってしまう。
								// 今回はリスト数は3つなので、Volume…0.0f、Tremolo…0.5f、Panning…1.0fとなる。
								// リストの数が4つの場合、0.0f、0.333…、0.666…、1.0fとなる。
								// 「1.0f / (リストの数 - 1)」で求められる。
								type = (int32)value;
								break;
							}
						}
					}
				}
			}

			// 入力・出力バッファのポインタをわかりやすい変数に格納
			// inputs[]、outputs[]はAudioBusの数だけある(addAudioInput()、addAudioOutput()で追加した分だけ)
			// 今回はAudioBusは1つだけなので 0 のみとなる
			// channelBuffers32は32bit浮動小数点型のバッファで音声信号のチャンネル数分ある
			// モノラル(kMono)なら 0 のみで、ステレオ(kStereo)なら 0(Left) と 1(Right) となる
			Sample32* inL = data.inputs[0].channelBuffers32[0];
			Sample32* inR = data.inputs[0].channelBuffers32[1];
			Sample32* outL = data.outputs[0].channelBuffers32[0];
			Sample32* outR = data.outputs[0].channelBuffers32[1];

			// numSamplesで示されるサンプル分、音声を処理する
			for (int32 i = 0; i < data.numSamples; i++)
			{
				switch (type)
				{
   				  case 0:
					outL[i] = volume * inL[i];;
					outR[i] = volume * inR[i];
					break;
				}
			}

			// 問題なければkResultTrueを返す(おそらく必ずkResultTrueを返す)
			return kResultTrue;
		}

	}
} // namespace SteinbergとVstの終わり
