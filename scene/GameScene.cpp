﻿#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete sprite_;
	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	textureHandle_ = TextureManager::Load("mario.jpg");
	textureHandle_2 = TextureManager::Load("mario.jpg");
	soundDataHandle_ = audio_->LoadWave("se_sad03.wav");

	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	model_ = Model::Create();

	worldTransform_.Initialize();

	viewProjection_.Initialize();

	audio_->PlayWave(soundDataHandle_, true);
}

void GameScene::Update() {
	XMFLOAT2 position = sprite_->GetPosition();

	position.x += 2.0f;
	position.y += 1.0f;

	value_++;

	sprite_->SetPosition(position);

	std::string strDebug = std::string("Value:") + std::to_string(value_);

	debugText_->Print("Kaizokuou ni oreha naru.", 50, 90, 1.0f);
	debugText_->SetPos(50, 70);
	debugText_->Printf("year:%d", 2001);
	debugText_->Print(strDebug, 50, 50, 1.0f);
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	model_->Draw(worldTransform_, viewProjection_, textureHandle_2);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	sprite_->Draw();

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
