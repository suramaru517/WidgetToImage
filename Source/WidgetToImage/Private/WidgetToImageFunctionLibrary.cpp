// Copyright 2023 Metaseven. All Rights Reserved.

#include "WidgetToImageFunctionLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Engine/TextureRenderTarget2D.h"
#include "ImageWriteBlueprintLibrary.h"
#include "RenderingThread.h"
#include "Slate/WidgetRenderer.h"

void UWidgetToImageFunctionLibrary::ExportWidgetAsImage(TSharedRef<SWidget> Widget, const FString& Filename, const FVector2D& DrawSize, const float Scale /*= 1.f*/, const EDesiredImageFormat Format /*= EDesiredImageFormat::PNG*/, const bool bOverwriteFile /*= true*/, const bool bAsync /*= true*/, const TextureFilter Filter /*= TF_Bilinear*/, const bool bUseGammaCorrection /*= true*/)
{
	FWidgetRenderer* WidgetRenderer = new FWidgetRenderer(bUseGammaCorrection, false);

	if (UTextureRenderTarget2D* RenderTarget = FWidgetRenderer::CreateTargetFor(DrawSize, Filter, bUseGammaCorrection))
	{
		if (bUseGammaCorrection)
		{
			RenderTarget->bForceLinearGamma = true;
			RenderTarget->UpdateResourceImmediate();
		}

		WidgetRenderer->DrawWidget(RenderTarget, Widget, Scale, DrawSize, 0.f);

		::FlushRenderingCommands();

		FImageWriteOptions Options;
		Options.Format = Format;
		Options.bOverwriteFile = bOverwriteFile;
		Options.bAsync = bAsync;

		UImageWriteBlueprintLibrary::ExportToDisk(RenderTarget, Filename, Options);
	}

	::BeginCleanup(WidgetRenderer);
}

void UWidgetToImageFunctionLibrary::ExportWidgetAsImage(UUserWidget* Widget, const FString Filename, const FVector2D DrawSize, const float Scale /*= 1.f*/, const EDesiredImageFormat Format /*= EDesiredImageFormat::PNG*/, const bool bOverwriteFile /*= true*/, const bool bAsync /*= true*/, const TextureFilter Filter /*= TF_Bilinear*/, const bool bUseGammaCorrection /*= true*/)
{
	ExportWidgetAsImage(Widget->TakeWidget(), Filename, DrawSize, Scale, Format, bOverwriteFile, bAsync, Filter, bUseGammaCorrection);
}
