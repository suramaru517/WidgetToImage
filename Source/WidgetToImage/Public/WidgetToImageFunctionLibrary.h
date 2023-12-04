// Copyright 2023 Metaseven. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture.h"
#include "ImageWriteTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WidgetToImageFunctionLibrary.generated.h"

class SWidget;

UCLASS()
class WIDGETTOIMAGE_API UWidgetToImageFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void ExportWidgetAsImage(
		TSharedRef<SWidget> Widget,
		const FString& Filename,
		const FVector2D& DrawSize,
		const float Scale = 1.f,
		const EDesiredImageFormat Format = EDesiredImageFormat::PNG,
		const bool bOverwriteFile = true,
		const bool bAsync = true,
		const TextureFilter Filter = TF_Bilinear,
		const bool bUseGammaCorrection = true);

	UFUNCTION(BlueprintCallable, Category = "WidgetToImage", meta = (AdvancedDisplay = 4))
	static void ExportWidgetAsImage(
		UUserWidget* Widget,
		const FString Filename,
		const FVector2D DrawSize,
		const float Scale = 1.f,
		const EDesiredImageFormat Format = EDesiredImageFormat::PNG,
		const bool bOverwriteFile = true,
		const bool bAsync = true,
		const TextureFilter Filter = TF_Bilinear,
		const bool bUseGammaCorrection = true);
};
