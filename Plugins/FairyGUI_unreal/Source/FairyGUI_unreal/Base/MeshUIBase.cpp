// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshUIBase.h"
#include "Slate/SMeshWidget.h"
#include "Slate/SlateVectorArtInstanceData.h"
#include "Rendering/DrawElements.h"
#include "Styling/SlateBrush.h"
#include "Materials/MaterialInterface.h"
#include "Modules/ModuleManager.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Framework/Application/SlateApplication.h"
#include "SlateMaterialBrush.h"
#include "Runtime/SlateRHIRenderer/Public/Interfaces/ISlateRHIRendererModule.h"
#include "UObject/ConstructorHelpers.h"
#include "Slate/SMeshWidget.h"

#define LOCTEXT_NAMESPACE "FairGUI"

class SUIMeshWidget : public SMeshWidget
{
public:
	SLATE_BEGIN_ARGS(SUIMeshWidget) { }
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& Args, UMeshUIBase& InThis)
	{
		This = &InThis;
	}

	void SetRenderData()
	{
		if (RenderData.Num() == 0)
		{
			RenderData.Add(FRenderData());
			EnableInstancing(0, 1);
		}
	}

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override
	{
		float Scale = 1.f;
		float B = 1;
		float C = 1;
		float D = 1;
		AllottedGeometry.GetAccumulatedRenderTransform().GetMatrix().GetMatrix(Scale, B, C, D);
		Scale = Scale < D ? Scale : D;
		This->FirstX = -AllottedGeometry.Size.X / 2;
		This->FirstY = AllottedGeometry.Size.Y / 2;
		This->Width = AllottedGeometry.Size.X;
		This->Height = AllottedGeometry.Size.Y;

		FVector2D TrailOriginWindowSpace = AllottedGeometry.LocalToAbsolute(AllottedGeometry.GetLocalSize() * 0.5f);
		This->PushUpdateVertext(TrailOriginWindowSpace, Scale);
		FSlateMaterialBrush brush = FSlateMaterialBrush(*(This->Materrial), FVector2D(256, 256));
		FSlateResourceHandle handle = FSlateApplication::Get().GetRenderer()->GetResourceHandle(brush);
		This->OnPopulateMesh(AllottedGeometry);
		for (int i = 0; i < This->VertexData.Num(); i++)
		{
			This->VertexData[i].TexCoords[0] = (This->VertexData[i].Position.X - This->FirstX) / This->Width;
			This->VertexData[i].TexCoords[1] = (This->FirstY + This->VertexData[i].Position.Y) / This->Height;
			FLinearColor lc = FLinearColor::FromSRGBColor(This->VertexData[i].Color);
			lc *= InWidgetStyle.GetColorAndOpacityTint();
			This->VertexData[i].Color = lc.ToFColor(true);
		}
		//绘制顶点数据
		FSlateDrawElement::MakeCustomVerts(OutDrawElements, LayerId, handle, This->VertexData,
			This->IndexData, RenderData[0].PerInstanceBuffer.Get(),
			0, RenderData[0].PerInstanceBuffer->GetNumInstances());
		return LayerId;
	}
public:
	UMeshUIBase* This;
};


UMeshUIBase::UMeshUIBase()
{
	if (Materrial == NULL)
	{
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/FairyGUI_unreal/Material/MeshUIBaseMaterial.MeshUIBaseMaterial"));

		if (MaterialAsset.Succeeded())
		{
			Materrial = MaterialAsset.Object;
		}
	}
}

void UMeshUIBase::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	MyMesh->SetRenderData();
}

TSharedRef<SWidget> UMeshUIBase::RebuildWidget()
{
	if (MyMesh != nullptr)
	{
		MyMesh.Reset();
	}
	MyMesh = SNew(SUIMeshWidget, *this);
	return MyMesh.ToSharedRef();
}

void UMeshUIBase::OnPopulateMesh(const FGeometry& AllottedGeometry)
{
	VertexData.Empty();
	IndexData.Empty();
	float HalfW = AllottedGeometry.Size.X / 2;
	float HalfH = AllottedGeometry.Size.Y / 2;
	FSlateVertex F1;
	F1.Color = FColor::White;
	F1.Position = FVector2D(-HalfW, HalfH);

	FSlateVertex F2;
	F2.Color = FColor::White;
	F2.Position = FVector2D(HalfW, HalfH);

	FSlateVertex F3;
	F3.Color = FColor::White;
	F3.Position = FVector2D(HalfW, -HalfH);

	FSlateVertex F4;
	F4.Color = FColor::White;
	F4.Position = FVector2D(-HalfW, -HalfH);
	VertexData.Add(F1);
	VertexData.Add(F2);
	VertexData.Add(F3);
	VertexData.Add(F4);

	IndexData.Add(0);
	IndexData.Add(1);
	IndexData.Add(2);

	IndexData.Add(2);
	IndexData.Add(3);
	IndexData.Add(0);
}

void UMeshUIBase::PushUpdateVertext(const FVector2D& Position, float Scale)
{
	FSlateVectorArtInstanceData Data;
	Data.SetPosition(Position);
	Data.SetScale(Scale);
	Data.SetBaseAddress(0);
	FSlateInstanceBufferData PerInstanceData;
	PerInstanceData.Add(Data.GetData());
	if (MyMesh != nullptr)
		MyMesh->UpdatePerInstanceBuffer(0, PerInstanceData);
}

#if WITH_EDITOR
#include "UMGStyle.h"
const FText UMeshUIBase::GetPaletteCategory()
{
	return LOCTEXT("FairGUIPaletteCategory", "FairGUI");
}
#endif
#undef LOCTEXT_NAMESPACE