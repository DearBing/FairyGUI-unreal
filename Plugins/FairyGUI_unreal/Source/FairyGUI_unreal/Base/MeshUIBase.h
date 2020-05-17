// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "MeshUIBase.generated.h"

/**
 * 
 */
UCLASS()
class FAIRYGUI_UNREAL_API UMeshUIBase : public UWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChartConfig", Meta = (DisplayName = "������"))
		UMaterialInterface* Materrial;

public:
	UMeshUIBase();

	//~ Begin UWidget Interface
	virtual void SynchronizeProperties() override;
	//~ End UWidget Interface

protected:
	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//~ End UWidget Interface
	virtual void OnPopulateMesh(const FGeometry& AllottedGeometry);
	void PushUpdateVertext(const FVector2D& Position, float Scale);

	TArray<FSlateVertex> VertexData;
	TArray<SlateIndex> IndexData;

	float FirstX;//��һ��Xֵ
	float FirstY;//��һ��Yֵ
	float Width;//���ֵ
	float Height;//�߶�ֵ
private:

	TSharedPtr<class SUIMeshWidget> MyMesh;
	friend class SUIMeshWidget;

#if WITH_EDITOR
public:
	// UWidget interface
	virtual const FText GetPaletteCategory() override;
	// End UWidget interface
#endif
};
